#pragma once

namespace timer 
{
    // For some reason llvm-obfuscator's bogus control flow doesn't like my timer sleep function
#ifdef __clang__
    inline void sleep(float ms) __attribute((__annotate__(("nobcf"))));
#endif

	inline void sleep(float ms)
	{
        static HMODULE ntdll = NULL;
        if (!ntdll)
            ntdll = GetModuleHandle(xorstr("ntdll.dll"));

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

        LARGE_INTEGER time = {};
        time.QuadPart = -1 * (LONGLONG)(ms * 10000.f);

        oNtDelayExecution(false, &time);
	}
}