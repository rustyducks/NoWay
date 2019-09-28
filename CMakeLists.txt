cmake_minimum_required(VERSION 3.0.0)
project(NoWay VERSION 0.1.0)

include(CTest)
enable_testing()
set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig)
pkg_check_modules(HIREDIS REQUIRED hiredis)

include_directories(include)

add_executable(NoWay src/main.cpp src/PBMReader.cpp src/Node.cpp src/ThetaStar.cpp src/Redis.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if (HIREDIS_FOUND)
  include_directories(${HIREDIS_INCLUDE_DIRS})
  target_link_libraries (NoWay ${HIREDIS_LIBRARIES})
endif (HIREDIS_FOUND)

target_compile_options(NoWay PRIVATE -Werror -Wall -Wextra)
