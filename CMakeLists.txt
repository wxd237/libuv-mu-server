project(uv-mu-server  C)

cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig REQUIRED)

pkg_check_modules(LUA  REQUIRED  lua)
include_directories(${LUA_INCLUDE_DIRS})
link_directories(${LUA_LIBRARY_DIRS})


pkg_check_modules(LIBUV  REQUIRED  libuv)
include_directories(${LIBUV_INCLUDE_DIRS})
link_directories(${LIBUV_LIBRARY_DIRS})


add_executable(tcpserver main.c)
add_executable(worker worker.c)
target_link_libraries(tcpserver uv)
target_link_libraries(worker uv)
