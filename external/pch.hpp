#ifdef __clang__
// warning: precompiled header uses __DATE__ or __TIME__
#pragma clang diagnostic ignored "-Wpch-date-time"
#endif

// defs
#define JM_XORSTR_DISABLE_AVX_INTRINSICS
#define NOMINMAX

// global incs
#include <iostream>
#include <random>
#include <string_view>
#include <algorithm>
#include <thread>
#include <vector>
#include <cstddef>
#include <functional>
#include <future>
#include <map>

#include <Windows.h>

// incs
#include "xorstr.hpp"
#include "lazy_importer.hpp"
#include "console.hpp"
#include "structs.hpp"
#include "vector.hpp"
#include "memory.hpp"
#include "keybind.hpp"
#include "var.hpp"
#include "utils.hpp"
#include "sdk.hpp"