project(uv-mu-server  C)

cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig REQUIRED)

set(CMAKE_C_FLAGS  -fms-extensions)

pkg_check_modules(LUA  REQUIRED  lua5.1)
include_directories(${LUA_INCLUDE_DIRS})
link_directories(${LUA_LIBRARY_DIRS})


pkg_check_modules(LIBUV  REQUIRED  libuv)
include_directories(${LIBUV_INCLUDE_DIRS})
link_directories(${LIBUV_LIBRARY_DIRS})


add_executable(tcpserver main.c luaoci.c)
add_executable(worker worker.c)
target_link_libraries(tcpserver uv)
target_link_libraries(worker uv)

add_executable(memblock_test  memblock_test.c )
add_executable(memhash_test   memhash_test.c memhash.c)

