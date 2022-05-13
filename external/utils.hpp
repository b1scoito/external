#pragma once

namespace timer
{
    // For some reason llvm-obfuscator's bogus control flow doesn't like my timer sleep function on clang-12
    // inline void sleep(float ms) __attribute((__annotate__(("nobcf"))));

    inline void sleep( float ms )
    {
        static HMODULE ntdll = NULL;
        if ( !ntdll )
            ntdll = GetModuleHandle( xorstr( L"ntdll.dll" ) );

        typedef NTSTATUS( WINAPI* fnNtDelayExecution )(BOOL Alertable, PLARGE_INTEGER DelayInterval);
        static fnNtDelayExecution oNtDelayExecution = NULL;

        if ( !oNtDelayExecution )
            oNtDelayExecution = (fnNtDelayExecution)LI_FN( GetProcAddress ).cached()(ntdll, xorstr( "NtDelayExecution" ));

        typedef NTSTATUS( WINAPI* fnZwSetTimerResolution )(IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution);
        static fnZwSetTimerResolution oZwSetTimerResolution = NULL;

        if ( !oZwSetTimerResolution )
            oZwSetTimerResolution = (fnZwSetTimerResolution)LI_FN( GetProcAddress ).cached()(ntdll, xorstr( "ZwSetTimerResolution" ));

        static std::once_flag flag;
        std::call_once( flag, []()
        {
            ULONG current;
            oZwSetTimerResolution( (ULONG)(0.5f * 10000.f), true, &current );
        } );

        if ( ms < 0.5f )
            ms = 0.5f;

        LARGE_INTEGER time = {};
        time.QuadPart = -1 * (LONGLONG)(ms * 10000.f);

        oNtDelayExecution( false, &time );
    }
}

namespace string
{
    inline std::vector<std::string> split( std::string s, std::string delimiter )
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ( (pos_end = s.find( delimiter, pos_start )) != std::string::npos )
        {
            token = s.substr( pos_start, pos_end - pos_start );
            pos_start = pos_end + delim_len;
            res.push_back( token );
        }

        res.push_back( s.substr( pos_start ) );
        return res;
    }
}

namespace random
{
    template <typename T>
    T range( T start, T end )
    {
        std::random_device rd = {};
        std::mt19937_64 rng( rd() );
        std::uniform_real_distribution<T> uni( start, end );

        return (T)uni( rng );
    }
}