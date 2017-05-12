file(REMOVE_RECURSE
  "../lcmtypes/c"
  "../lcmtypes/cpp"
  "../lcmtypes/java"
  "../lcmtypes/python"
  "CMakeFiles/lcmtypes_lcm_scan_jar"
  "lcmtypes_lcm_scan.jar"
  "../lcmtypes/java/lidar/lidar_t.class"
  "../lcmtypes/java/exlcm/example_t.class"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/lcmtypes_lcm_scan_jar.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
