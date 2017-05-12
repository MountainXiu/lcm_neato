find_package(Boost REQUIRED COMPONENTS system)
add_executable(publishscan publishscan.cpp)
pods_use_pkg_config_packages(publishscan lcm_scan)
target_link_libraries(publishscan ${Boost_LIBRARIES})

add_executable(subscribescan subscribescan.cpp)
pods_use_pkg_config_packages(subscribescan lcm_scan)
target_link_libraries(publishscan ${Boost_LIBRARIES})
pods_use_pkg_config_packages(subscribescan opencv)
