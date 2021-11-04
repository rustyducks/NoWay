cmake_minimum_required(VERSION 3.14.0)
project(NoWay VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(PkgConfig)
pkg_check_modules(HIREDIS REQUIRED hiredis)

add_library(NoWay STATIC src/Node.cpp src/PBMReader.cpp src/ThetaStar.cpp)
target_include_directories(NoWay PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib)
)
set_target_properties(NoWay PROPERTIES PUBLIC_HEADER "include/NoWay/ThetaStar.hpp;include/NoWay/Pathfinder.hpp;include/NoWay/PBMReader.hpp")
target_compile_options(NoWay PRIVATE -Werror -pedantic -Wall -Wextra)


add_executable(NoWay-redis src/main.cpp src/Redis.cpp)
target_include_directories(NoWay-redis PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (HIREDIS_FOUND)
  include_directories(${HIREDIS_INCLUDE_DIRS})
  target_link_libraries (NoWay-redis PUBLIC ${HIREDIS_LIBRARIES})
endif (HIREDIS_FOUND)
target_link_libraries(NoWay-redis PUBLIC NoWay)

target_compile_options(NoWay-redis PRIVATE -Werror -pedantic -Wall -Wextra)

### Packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

### Install
install(TARGETS NoWay
        EXPORT NoWayTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
        PUBLIC_HEADER DESTINATION include/NoWay

)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    NoWayConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT NoWayTargets
        FILE NoWayTargets.cmake
        NAMESPACE NoWay::
        DESTINATION lib/cmake/NoWay
)

configure_file(cmake/NoWayConfig.cmake.in NoWayConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/NoWayConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/NoWayConfigVersion.cmake"
        DESTINATION lib/cmake/NoWay
        )