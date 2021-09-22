cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project("bridge" CXX)

find_package(RapidJSON)
find_package(GTest)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    list(APPEND DDSJSON_MSVC_FLAGS
      "/W3"
      "/DNOMINMAX"
      "/DWIN32_LEAN_AND_MEAN"
      "/D_CRT_SECURE_NO_WARNINGS"
      "/D_SCL_SECURE_NO_WARNINGS"
  )

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
endif()

set(EXTERNAL_MODULES ${CMAKE_CURRENT_LIST_DIR}/external)

list(
    APPEND
    CMAKE_MODULE_PATH
    ${EXTERNAL_MODULES}
)

add_subdirectory(${EXTERNAL_MODULES}/googletest)

enable_testing()

add_subdirectory(bridge)