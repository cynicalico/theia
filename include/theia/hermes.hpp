#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <ranges>
#include <span>
#include <unordered_map>
#include <vector>

namespace murmur {
namespace internal {
constexpr std::uint32_t rotl32(std::uint32_t x, std::int8_t r);
constexpr std::uint32_t getblock32(const char *p, std::uint32_t i);
constexpr std::uint32_t fmix32(std::uint32_t h);
constexpr std::uint32_t hash_x86_32(const char *key, std::uint32_t len, std::uint32_t seed);
} // namespace internal

template <uint64_t N>
constexpr std::uint32_t x86_32(const char (&s)[N], const std::uint32_t seed) {
    return internal::hash_x86_32(s, N - 1, seed);
}
} // namespace murmur

#define MAKE_HERMES_ID(name) constexpr static std::uint32_t HERMES_ID{murmur::x86_32(#name, 0)};

namespace theia {
template <typename T>
concept HashHermesId = std::same_as<decltype(T::HERMES_ID), const std::uint32_t>;

class Hermes {
    using Payload = std::span<std::byte>;
    using Receiver = std::function<void(Payload)>;

public:
    using ID = std::size_t;

    static Hermes &instance();

    ID get_id();
    void release_id(ID id);

    template <typename T, typename Func>
        requires HashHermesId<T> and std::invocable<Func, T *>
    void subscribe(ID id, Func &&f);

    template <typename T>
        requires HashHermesId<T>
    void unsubscribe(ID id);

    template <typename T, typename... Args>
        requires HashHermesId<T>
    void publish(Args &&...args);

    template <typename T>
        requires HashHermesId<T>
    void capture(ID id);

    template <typename T>
        requires HashHermesId<T>
    void uncapture(ID id, bool force = false);

private:
    ID next_id_ = 0;
    std::vector<ID> recycled_ids_{};

    std::unordered_map<std::uint32_t, std::optional<ID>> captures_;
    std::unordered_map<std::uint32_t, std::vector<Receiver>> receivers_;

    template <typename T, typename... Args>
    std::span<std::byte> make_payload_(Args &&...args);
};
} // namespace theia

inline theia::Hermes &theia::Hermes::instance() {
    static Hermes instance;
    return instance;
}

inline theia::Hermes::ID theia::Hermes::get_id() {
    if (recycled_ids_.empty()) return next_id_++;

    const auto id = recycled_ids_.back();
    recycled_ids_.pop_back();
    return id;
}

inline void theia::Hermes::release_id(const ID id) {
    for (auto &receivers : receivers_ | std::views::values)
        if (receivers.size() > id) receivers[id] = nullptr;

    for (auto &capture : captures_ | std::views::values)
        if (capture && *capture == id) capture.reset();

    recycled_ids_.push_back(id);
}

template <typename T, typename Func>
    requires theia::HashHermesId<T> and std::invocable<Func, T *>
void theia::Hermes::subscribe(ID id, Func &&f) {
    auto &receivers = receivers_[T::HERMES_ID];
    if (receivers.size() <= id) receivers.resize(id + 1);
    receivers[id] = [f = std::forward<Func>(f)](const Payload buffer) { f(reinterpret_cast<T *>(buffer.data())); };
}

template <typename T>
    requires theia::HashHermesId<T>
void theia::Hermes::unsubscribe(ID id) {
    auto &receivers = receivers_[T::HERMES_ID];
    if (receivers.size() > id) receivers[id] = nullptr;
}

template <typename T, typename... Args>
    requires theia::HashHermesId<T>
void theia::Hermes::publish(Args &&...args) {
    const auto payload = make_payload_<T>(std::forward<Args>(args)...);
    if (auto cap_id_opt = captures_[T::HERMES_ID]; cap_id_opt) {
        if (receivers_[T::HERMES_ID].size() > *cap_id_opt) {
            if (auto &r = receivers_[T::HERMES_ID][*cap_id_opt]; r) r(payload);
        }
    } else {
        for (auto &r : receivers_[T::HERMES_ID])
            if (r) r(payload);
    }
    operator delete(payload.data(), payload.size());
}

template <typename T>
    requires theia::HashHermesId<T>
void theia::Hermes::capture(ID id) {
    captures_[T::HERMES_ID] = id;
}

template <typename T>
    requires theia::HashHermesId<T>
void theia::Hermes::uncapture(ID id, bool force) {
    if (force || captures_[T::HERMES_ID] && *captures_[T::HERMES_ID] == id) captures_[T::HERMES_ID].reset();
}

template <typename T, typename... Args>
std::span<std::byte> theia::Hermes::make_payload_(Args &&...args) {
    return std::span(reinterpret_cast<std::byte *>(new T{std::forward<Args>(args)...}), sizeof(T));
}

namespace murmur::internal {
constexpr std::uint32_t rotl32(const std::uint32_t x, const std::int8_t r) { return x << r | x >> (32 - r); }

constexpr std::uint32_t getblock32(const char *p, const std::uint32_t i) {
    return static_cast<uint32_t>(p[0 + i * 4]) << 0 | static_cast<uint32_t>(p[1 + i * 4]) << 8 |
           static_cast<uint32_t>(p[2 + i * 4]) << 16 | static_cast<uint32_t>(p[3 + i * 4]) << 24;
}

constexpr std::uint32_t fmix32(std::uint32_t h) {
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

constexpr std::uint32_t hash_x86_32(const char *key, const std::uint32_t len, const std::uint32_t seed) {
    const std::uint32_t n_blocks = len / 4;

    std::uint32_t h1 = seed;

    constexpr uint32_t C1 = 0xcc9e2d51;
    constexpr uint32_t C2 = 0x1b873593;

    // body

    for (std::uint32_t i = 0; i < n_blocks; i++) {
        std::uint32_t k1 = getblock32(key, i);
        k1 = rotl32(k1 * C1, 15) * C2;
        h1 = rotl32(h1 ^ k1, 13) * 5 + 0xe6546b64;
    }

    // tail

    std::uint32_t k1 = 0;

    const std::uint32_t tail_start = len - len % 4;
    switch (len & 3) {
    case 3:
        k1 ^= key[tail_start + 2] << 16;
    case 2:
        k1 ^= key[tail_start + 1] << 8;
    case 1:
        k1 ^= key[tail_start + 0];
        k1 = rotl32(k1 * C1, 15) * C2;
        h1 ^= k1;
        break;
    default:;
    }

    // finalization

    h1 ^= len;
    h1 = fmix32(h1);

    return h1;
}
} // namespace murmur::internal
