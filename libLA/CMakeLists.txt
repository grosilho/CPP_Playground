
add_library(libLA)

target_include_directories(libLA PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(libLA PUBLIC compiler_flags)

target_sources(libLA PRIVATE Matrix.cpp)
