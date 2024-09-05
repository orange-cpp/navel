//
// Created by Vlad on 05.09.2024.
//
#include "BaseEntity.h"

namespace ssdk
{
    omath::Vector3 BaseEntity::GetBonePosition(const int bone) const
    {
        uintptr_t pBone = m_pBoneMatrix;
        omath::Vector3 position;

        position.x = *(float *) ((pBone + 0x30 * bone + 0x0C));
        position.y = *(float *) ((pBone + 0x30 * bone + 0x1C));
        position.z = *(float *) ((pBone + 0x30 * bone + 0x2C));

        return position;
    }

    float BaseEntity::CalcDistanceToEntity(const BaseEntity *entity) const
    {
        return (m_vecOrigin + m_vecViewOffset).DistTo(entity->GetBonePosition(8));
    }

    omath::Color BaseEntity::GetColorBasedOnHealth() const
    {
        const auto healthRatio = GetHealthPercent() / 100.f;

        return omath::Color::Red().Blend(omath::Color::Green(),healthRatio);
    }

    omath::Vector3 BaseEntity::GetCameraPosition() const
    {
        return m_vecOrigin + m_vecViewOffset;
    }

    bool BaseEntity::IsAlive() const
    {
        return m_iHealth > 0;
    }

    float BaseEntity::GetHealthPercent() const
    {
        return 100.f * m_iHealth / m_iMaxHealth;
    }

    const ClientClass*BaseEntity::GetClientClass() const
    {
        typedef ClientClass *(__cdecl *GetClientClass_t)();

        // Get addr of fucntion with index  2 from vtable with index 2
        auto funcAdrr = ((GetClientClass_t **) this)[2][2];
        return funcAdrr();
    }
}