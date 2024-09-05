//
// Created by Vlad on 05.09.2024.
//
#include "UserCmd.h"
#include <omath/Angles.h>


namespace ssdk
{
    fix_usercmd::fix_usercmd(UserCmd *pUserCmd)
    {
        m_pUserCmd = pUserCmd;
        m_oldUserCmd = *pUserCmd;
    }

    fix_usercmd::~fix_usercmd()
    {
        float fDeltaYaw;
        float f1;
        float f2;

        if (m_oldUserCmd.m_vecViewAngles.y < 0.f)
            f1 = 360.f + m_oldUserCmd.m_vecViewAngles.y;
        else
            f1 = m_oldUserCmd.m_vecViewAngles.y;


        if (m_pUserCmd->m_vecViewAngles.y < 0.f)
            f2 = 360.f + m_pUserCmd->m_vecViewAngles.y;
        else
            f2 = m_pUserCmd->m_vecViewAngles.y;

        if (f2 < f1)
            fDeltaYaw = abs(f2 - f1);
        else
            fDeltaYaw = 360.f - abs(f1 - f2);

        fDeltaYaw = 360.f - fDeltaYaw;

        m_pUserCmd->m_fForwardMove =
                std::cos(omath::angles::DegreesToRadians(fDeltaYaw)) * m_oldUserCmd.m_fForwardMove +
                cos(omath::angles::DegreesToRadians(fDeltaYaw + 90.f)) * m_oldUserCmd.m_fSideMove;
        m_pUserCmd->m_fSideMove = std::sin(omath::angles::DegreesToRadians(fDeltaYaw)) * m_oldUserCmd.m_fForwardMove +
                                  sin(omath::angles::DegreesToRadians(fDeltaYaw + 90.f)) * m_oldUserCmd.m_fSideMove;
    }
}