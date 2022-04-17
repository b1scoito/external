#pragma once

namespace timer 
{
	inline void sleep(float ms)
	{
        static HMODULE ntdll = NULL;
        if (!ntdll)
            ntdll = GetModuleHandle(xorstr(L"ntdll.dll"));

        typedef NTSTATUS(WINAPI* fnNtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval);
        static fnNtDelayExecution oNtDelayExecution = NULL;

        if (!oNtDelayExecution)
            oNtDelayExecution = (fnNtDelayExecution)LI_FN(GetProcAddress).cached()(ntdll, xorstr("NtDelayExecution"));

        typedef NTSTATUS(WINAPI* fnZwSetTimerResolution)(IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution);
        static fnZwSetTimerResolution oZwSetTimerResolution = NULL;

        if (!oZwSetTimerResolution)
            oZwSetTimerResolution = (fnZwSetTimerResolution)LI_FN(GetProcAddress).cached()(ntdll, xorstr("ZwSetTimerResolution"));

        static std::once_flag flag;
        std::call_once(flag, []()
            {
                ULONG current;
                oZwSetTimerResolution((ULONG)(0.5f * 10000.f), true, &current);
            });

        if (ms < 0.5f)
            ms = 0.5f;

        LARGE_INTEGER time = { 0 };
        time.QuadPart = -1 * (LONGLONG)(ms * 10000.f);

        oNtDelayExecution(false, &time);
	}
}

namespace string
{
    inline std::wstring to_lower(std::wstring str)
    {
        std::transform(str.begin(), str.end(), str.begin(), static_cast<int(*)(int)>(::tolower));
        return str;
    }
}