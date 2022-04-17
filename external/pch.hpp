// defs
#define JM_XORSTR_DISABLE_AVX_INTRINSICS
#define NOMINMAX

// global incs
#include <iostream>
#include <thread>

#include <Windows.h>

using namespace std::chrono_literals;

// incs
#include "xorstr.hpp"
#include "lazy_importer.hpp"
#include "console.hpp"
#include "utils.hpp"
#include "keybind.hpp"
#include "var.hpp"
