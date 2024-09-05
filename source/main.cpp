//
// Created by Vlad on 19.07.2024.
//
#include <Windows.h>
#include <thread>


namespace navel
{
    void MainThread(const HMODULE moduleHandle)
    {
        while (true)
        {
            if (GetAsyncKeyState(VK_END) & 0x8000)
                break;
            
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
        FreeLibrary(moduleHandle);
    }
}
extern "C" BOOL WINAPI DllMain(const HMODULE moduleHandle, const DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
        std::thread(navel::MainThread, moduleHandle).detach();
    return TRUE;
}