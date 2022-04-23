#ifdef __clang__
// warning: precompiled header uses __DATE__ or __TIME__
#pragma clang diagnostic ignored "-Wpch-date-time"
#endif

// defs
#define JM_XORSTR_DISABLE_AVX_INTRINSICS
#define NOMINMAX

// global incs
#include <iostream>
#include <string_view>
#include <algorithm>
#include <thread>
#include <vector>
#include <cstddef>

#include <Windows.h>

// incs
#include "xorstr.hpp"
#include "lazy_importer.hpp"
#include "console.hpp"
#include "vector.hpp"
#include "keybind.hpp"
#include "var.hpp"
#include "utils.hpp"
