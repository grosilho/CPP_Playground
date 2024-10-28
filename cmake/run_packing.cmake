# Packaging rules ----------------------------------------------------------------------------
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/../LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
