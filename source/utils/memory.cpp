//
// Created by Vlad on 05.09.2024.
//
#include "memory.h"
#include <vector>
#include <cstdint>
#include <cctype>
#include <Windows.h>


uint8_t GetBit(char chr)
{
    chr = std::tolower(chr);

    if ('a' <= chr and chr <= 'z')
        return chr - 'a' + 10;
    return chr - '0';

}
std::vector<uint8_t> GetSignatureBytes(const std::string_view &str)
{
    std::vector<uint8_t> bytes;
    const auto length = str.size();

    for (size_t i = 0; i < length;)
    {
        if (str[i] == ' ')
        {
            i += 1;
            continue;
        }
        if (str[i] == '?')
        {
            bytes.push_back('\?');
            i+1 < length and str[i+1] == '?' ? i += 2 : i++;
            continue;
        }

        bytes.push_back(GetBit(str[i]) * 16 + GetBit(str[i + 1]));
        i += 2;
    }

    return bytes;
}

namespace navel::utils
{

    std::optional<uintptr_t> FindPattern(const std::string_view &moduleName, const std::string_view &signature)
    {
        const auto base = (uintptr_t)GetModuleHandleA(moduleName.data());

        const auto imageNTHeaders = (PIMAGE_NT_HEADERS)(base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);


        const auto pattern = GetSignatureBytes(signature);

        // Define .code segment as scan area
        const auto start    = imageNTHeaders->OptionalHeader.BaseOfCode;
        const auto scanSize = imageNTHeaders->OptionalHeader.SizeOfCode;

        for (uintptr_t i = start; i < scanSize - pattern.size(); i++)
        {
            bool found = true;

            for (uintptr_t j = 0; j < pattern.size(); j++)
            {
                found = pattern[j] == '\?' || pattern[j] == *(BYTE*)(base + i + j);
                if (!found) break;
            }
            if (found)
                return base + i;
        }
        return std::nullopt;
    }
}