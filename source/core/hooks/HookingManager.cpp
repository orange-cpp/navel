//
// Created by Vlad on 05.09.2024.
//
#include "HookingManager.h"
#include <MinHook.h>
#include "utils/memory.h"

namespace navel::core
{
    HookingManager &navel::core::HookingManager::Get()
    {
        static HookingManager obj;

        return obj;
    }

    HookingManager::HookingManager()
    {
        MH_Initialize();
    }

    HookingManager::~HookingManager()
    {
        MH_Uninitialize();
    }

    bool HookingManager::Attach()
    {

        return true;
    }

    bool HookingManager::Detach()
    {
        MH_RemoveHook(MH_ALL_HOOKS);
        return true;
    }

    std::optional<uintptr_t> HookingManager::FindCreatemove()
    {
        static auto addr = utils::FindPattern("client.dll", "55 8B EC 56 8D 75 04 8B");

        return addr;
    }

    std::optional<uintptr_t> HookingManager::FindDrawIndexedPrimitive()
    {
        static auto addr = utils::FindPattern("d3d9.dll", "8B FF 55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 28");
        return addr;
    }

    std::optional<uintptr_t> HookingManager::FindRenderGlowEffects()
    {
        static auto addr = utils::FindPattern("client.dll", "55 8B EC A1 ? ? ? ? 83 EC 18 57");

        return addr;
    }

    std::optional<uintptr_t> HookingManager::FindPresent()
    {
        static auto addr = utils::FindPattern("d3d9.dll", "?? ?? ?? ?? ?? 83 E4 F8 51 51 56 8B 75 08 8B CE F7 D9 57 1B C9 8D 46 04 23 C8 6A ?? 51 8D 4C 24 10 E8 ?? ?? ?? ?? F7 46 ?? ?? ?? ?? ?? 74 07 BF ?? ?? ?? ?? EB 17");

        return addr;
    }

    std::optional<uintptr_t> HookingManager::GetForceAttack()
    {
        static auto addr = *(uintptr_t*)(utils::FindPattern("client.dll", "89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04").value() + 2);

        return addr;
    }
}
