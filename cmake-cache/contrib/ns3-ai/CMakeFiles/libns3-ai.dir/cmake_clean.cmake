file(REMOVE_RECURSE
  "../../../build/lib/libns3-dev-ns3-ai-debug.pdb"
  "../../../build/lib/libns3-dev-ns3-ai-debug.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/libns3-ai.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
