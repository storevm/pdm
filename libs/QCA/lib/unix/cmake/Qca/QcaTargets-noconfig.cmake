#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qca" for configuration ""
set_property(TARGET qca APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(qca PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/admin/qca-2.3.2/build/dist/lib/libqca.so.2.3.2"
  IMPORTED_SONAME_NOCONFIG "libqca.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS qca )
list(APPEND _IMPORT_CHECK_FILES_FOR_qca "/home/admin/qca-2.3.2/build/dist/lib/libqca.so.2.3.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
