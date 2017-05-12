cmake_minimum_required(VERSION 2.6.0)

set(POD_NAME lcm_scan)
include(cmake/pods.cmake)

#system find
find_package(PkgConfig REQUIRED)

pkg_check_modules(LCM lcm)
if(NOT LCM_FOUND)
    message("LCM not found.  Disabling LCM support")
    add_definitions(-DNO_LCM)
else()
    # automatically build LCM types.  This also defines a number of CMake
    # variables, see cmake/lcmtypes.cmake for details
    include(cmake/lcmtypes.cmake)
    lcmtypes_build()
    set(REQUIRED_DEPENDENCIES    lcm lcmtypes_lcm_scan)
    set(REQUIRED_LIBS -lz)  
endif(NOT LCM_FOUND)

pods_install_pkg_config_file(lcm_scan
    LIBS     ${REQUIRED_LIBS}
    REQUIRES ${REQUIRED_DEPENDENCIES}
    VERSION 0.0.1)

add_subdirectory(src)
