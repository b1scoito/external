#ifdef __clang__
// warning: precompiled header uses __DATE__ or __TIME__
#pragma clang diagnostic ignored "-Wpch-date-time"
#endif

// defs
#define JM_XORSTR_DISABLE_AVX_INTRINSICS
#define NOMINMAX

// global incs
#include <string_view>
#include <functional>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <random>
#include <thread>
#include <vector>
#include <future>
#include <string>
#include <format>
#include <array>
#include <map>

#include <Windows.h>

// external libs
#include <valve-bsp-parser/bsp_parser.hpp>

// incs
#include "xorstr.hpp"
#include "lazy_importer.hpp"
#include "structs.hpp"
#include "vector.hpp"
#include "qangle.hpp"
#include "memory.hpp"
#include "keybind.hpp"
#include "var.hpp"
#include "utils.hpp"
#include "sdk.hpp"
#include "config.hpp"
#include "math.hpp"