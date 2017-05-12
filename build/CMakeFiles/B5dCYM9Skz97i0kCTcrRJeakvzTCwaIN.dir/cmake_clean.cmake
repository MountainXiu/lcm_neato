file(REMOVE_RECURSE
  "../lcmtypes/c"
  "../lcmtypes/cpp"
  "../lcmtypes/java"
  "../lcmtypes/python"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/B5dCYM9Skz97i0kCTcrRJeakvzTCwaIN.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
