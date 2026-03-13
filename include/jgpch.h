#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <mutex>
#include <algorithm>
#include <utility>
#include <functional>
#include <random>
#include <chrono>
#include <thread>
#include <typeindex>
#include <exception>
#include <stdexcept>
#include <optional>

#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <csignal>

#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define U8_MAX UINT8_MAX
#define U16_MAX UINT16_MAX
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX

using namespace std::string_literals;
using namespace std::string_view_literals;
