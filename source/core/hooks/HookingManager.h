//
// Created by Vlad on 05.09.2024.
//

#pragma once

#include <cstdint>
#include <optional>


namespace navel::core
{
    class HookingManager final
    {
    public:
        static HookingManager& Get();

        [[nodiscard]]
        bool Attach();

        [[nodiscard]]
        bool Detach();

        ~HookingManager();
    private:
        HookingManager();

        [[nodiscard]]
        static std::optional<uintptr_t> FindCreatemove() ;


        [[nodiscard]]
        static std::optional<uintptr_t> FindDrawIndexedPrimitive() ;
        [[nodiscard]]
        static std::optional<uintptr_t> FindRenderGlowEffects() ;
        [[nodiscard]]
        static std::optional<uintptr_t> FindPresent() ;

        [[nodiscard]]
        static std::optional<uintptr_t> GetForceAttack() ;
    };
}