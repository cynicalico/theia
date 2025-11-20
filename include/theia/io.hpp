#pragma once

#include <filesystem>
#include <vector>

namespace theia {
std::tuple<std::vector<std::byte>, int, int> read_image_bytes(const std::filesystem::path &path);
}