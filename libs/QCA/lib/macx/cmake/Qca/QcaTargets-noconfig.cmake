#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qca" for configuration ""
set_property(TARGET qca APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(qca PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/Users/tanxiangqing/tools/library/qca-2.3.2/build/dist/lib/qca.framework/Versions/2/qca"
  IMPORTED_SONAME_NOCONFIG "/Users/tanxiangqing/tools/library/qca-2.3.2/build/dist/lib/qca.framework/Versions/2/qca"
  )

list(APPEND _IMPORT_CHECK_TARGETS qca )
list(APPEND _IMPORT_CHECK_FILES_FOR_qca "/Users/tanxiangqing/tools/library/qca-2.3.2/build/dist/lib/qca.framework/Versions/2/qca" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
