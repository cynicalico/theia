#include "theia/io.hpp"
#include "theia/logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::tuple<std::vector<std::byte>, int, int> theia::read_image_bytes(const std::filesystem::path &path) {
    int width, height, channels;
    constexpr int desired_channels = 4; // Force RGBA
    unsigned char *data = stbi_load(path.string().c_str(), &width, &height, &channels, desired_channels);

    if (!data) {
        THEIA_LOG_ERROR("Failed to load image '{}': {}", path.string(), stbi_failure_reason());
        return {};
    }

    std::vector bytes(reinterpret_cast<std::byte *>(data),
                      reinterpret_cast<std::byte *>(data) + width * height * desired_channels);

    stbi_image_free(data);
    return {bytes, width, height};
}
