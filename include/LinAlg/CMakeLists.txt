# ---------------------------------------------------------------------------------------
# Add library
# ---------------------------------------------------------------------------------------
add_library(${PROJECT_NAME})

add_subdirectory(Matrix)

# the include directories are different when building and when using the installed version, so we
# need to specify that
target_include_directories(Matrix
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> # when building use this directory
         $<INSTALL_INTERFACE:include/LinAlg>
) # but for the installed version use this directory

target_sources(${PROJECT_NAME} PUBLIC FILE_SET linalgInterface TYPE CXX_MODULES FILES LinAlg.mpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Matrix)

set(installable_targets ${PROJECT_NAME} compiler_flags)
# set(installable_header_files ${headers})

# ---------------------------------------------------------------------------------------
# Install the library and headers
# ---------------------------------------------------------------------------------------
include(GNUInstallDirs) # make cache variables for install destinations
install(
  TARGETS ${installable_targets}
  EXPORT ${PROJECT_NAME}Targets # this is the name of the export var. containing info to reuse the
                                # targets in other projects
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
  FILE_SET linalgInterface DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
)
# install(FILES ${installable_header_files} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

# Create a cmake file that, when included with include(), will make the targets available in other
# projects----------------------------------------------------------------------
install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
# To use the above created file in other projects we need to know where it is. We can create a
# Config.cmake instructing CMake where to find it ------------------------------ Generate a
# configuration file in the build directory. Also, tell him where it will be installed
include(CMakePackageConfigHelpers) # helper functions to create configuration files
configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/../../Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
# Generate a version file. This file will contain the version of the project. It provides
# information about compatibility with the requested version from the other projects ----
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)
# Install the configuration and version file -------------------------------------------- Basically,
# the configuration file will perform the include of the above targets file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
# The next is to make available the targets when building this project as dependency of another one.
# Hence without installing first
export(
  EXPORT ${PROJECT_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
  NAMESPACE ${PROJECT_NAME}::
)
# Create alias targets with the namespace included in the name. To ensure that the same target names
# are available when using the Config files or when includin the project with CPMAAddPackage
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_library(${PROJECT_NAME}::compiler_flags ALIAS compiler_flags)
# ---------------------------------------------------------------------------------------
