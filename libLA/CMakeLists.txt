
add_library(libLA)

target_include_directories(libLA PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(libLA PUBLIC compiler_flags)

target_sources(libLA PRIVATE Matrix.cpp)

set(installable_libs libLA compiler_flags)
set(installable_files LA.h Matrix.h)
install(TARGETS ${installable_libs} DESTINATION lib)
install(FILES ${installable_files} DESTINATION include)
