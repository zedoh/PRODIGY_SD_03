# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\ContactManager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ContactManager_autogen.dir\\ParseCache.txt"
  "ContactManager_autogen"
  )
endif()
