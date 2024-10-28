
add_library(${PROJECT_NAME})

# the include directories are different when building and when using the installed version, so we need to specify that
target_include_directories(${PROJECT_NAME}
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..> # when building use this directory
                                  $<INSTALL_INTERFACE:include>) # but for the installed version use this directory

target_link_libraries(${PROJECT_NAME} PUBLIC compiler_flags)

file(GLOB_RECURSE headers RELATIVE "${CMAKE_CURRENT_LIST_DIR}" CONFIGURE_DEPENDS "*.hpp")
file(GLOB_RECURSE sources RELATIVE "${CMAKE_CURRENT_LIST_DIR}" CONFIGURE_DEPENDS "*.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${sources})

set(installable_libs ${PROJECT_NAME} compiler_flags)
set(installable_files ${headers})
install(TARGETS ${installable_libs} 
        EXPORT "${PROJECT_NAME}Targets" # export the targets so that it can be used by other projects
        DESTINATION lib)
install(FILES ${installable_files} 
        DESTINATION "include/${PROJECT_NAME}")
