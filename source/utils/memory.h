//
// Created by Vlad on 05.09.2024.
//

#pragma once
#include <cstdint>
#include <optional>
#include <string_view>


namespace navel::utils
{
    [[nodiscard]]
    std::optional<uintptr_t> FindPattern(const std::string_view& moduleName, const std::string_view& signature);
}