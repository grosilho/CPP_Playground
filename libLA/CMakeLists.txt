
add_library(libLA)

# the include directories are different when building and when using the installed version, so we need to specify that
target_include_directories(libLA
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> # when building use this directory
                                  $<INSTALL_INTERFACE:include>) # but for the installed version use this directory

target_link_libraries(libLA PUBLIC compiler_flags)

target_sources(libLA PRIVATE Matrix.cpp)

set(installable_libs libLA compiler_flags)
set(installable_files LA.h Matrix.h)
install(TARGETS ${installable_libs} 
        EXPORT libLATargets # export the targets so that it can be used by other projects
        DESTINATION lib)
install(FILES ${installable_files} 
        DESTINATION "include/libLA")
