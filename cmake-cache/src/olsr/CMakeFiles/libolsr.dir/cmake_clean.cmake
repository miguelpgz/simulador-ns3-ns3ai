file(REMOVE_RECURSE
  "../../../build/lib/libns3-dev-olsr-debug.pdb"
  "../../../build/lib/libns3-dev-olsr-debug.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/libolsr.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
