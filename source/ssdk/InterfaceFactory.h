//
// Created by Vlad on 05.09.2024.
//

#pragma once
#include <string_view>
#include <Windows.h>


namespace ssdk
{
    class InterfaceFactory final
    {
    public:
        InterfaceFactory() = delete;


        template <typename T>
        T* CreateInterface(const std::string_view& dllname, const std::string_view& interfaceName)
        {
            typedef void* (__cdecl* tCreateInterface)(const char* name, int* returncode);
            const auto CreateInterFace = reinterpret_cast<tCreateInterface>(GetProcAddress(GetModuleHandleA(dllname.data()), "CreateInterface"));

            int returnCode = 0;

            return static_cast<T*>(CreateInterFace(interfaceName.data(), &returnCode));
        }
    };

} // ssdk