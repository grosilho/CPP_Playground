# Export rules -------------------------------------------------------------------------------
# Export the targets so that after installation tey can still be used in other projects
# So far, in subdirectories, we packaged all the target information to be exported, but we still need to create a *.cmake files that will be used by other projects to find and use this library with find_package()
# here we export the target information to a file called ${PROJECT_NAME}Targets.cmake
install(EXPORT "${PROJECT_NAME}Targets"
        DESTINATION "lib/cmake/${PROJECT_NAME}"
        NAMESPACE "${PROJECT_NAME}::" # add a namespace to the targets
        FILE "${PROJECT_NAME}Targets.cmake"
)
include(CMakePackageConfigHelpers)
# create the main config file. It will take the content of the Config.cmake.in file and replace the @PACKAGE_INIT@ with relative paths. The result will be saved in ${PROJECT_NAME}Config.cmake file.
# Config.cmake.in contains a reference to the target's *.cmake files. This info will be copied in the main config file.
configure_package_config_file("${CMAKE_CURRENT_LIST_DIR}/../Config.cmake.in"
                                "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                                INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
                                NO_SET_AND_CHECK_MACRO
                                NO_CHECK_REQUIRED_COMPONENTS_MACRO
                                )
# create the version file. It will take the version from the project and save it in ${PROJECT_NAME}ConfigVersion.cmake file. It provides information about compatibility with the requested version from the other projects.
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}"
                                 COMPATIBILITY AnyNewerVersion
                                 )                        
# install the config files
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "lib/cmake/${PROJECT_NAME}"
        )
# So far we generated info that can be used by the installed library. 
# To use it from a build directory we need to generate ${PROJECT_NAME}Targets.cmake in the build directory so that it can be used by the ${PROJECT_NAME}Config.cmake file there.
export(EXPORT "${PROJECT_NAME}Targets"
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
        NAMESPACE "${PROJECT_NAME}::"
        )
