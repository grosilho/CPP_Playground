# ---------------------------------------------------------------------------------------
# Add library
# ---------------------------------------------------------------------------------------
add_library(Matrix)

target_include_directories(Matrix
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> 
         $<INSTALL_INTERFACE:include/LinAlg/Matrix>
)

target_link_libraries(Matrix PUBLIC compiler_flags std::mdspan)

file(
  GLOB_RECURSE modules_interfaces
  RELATIVE "${CMAKE_CURRENT_LIST_DIR}"
  CONFIGURE_DEPENDS "*.mpp"
)
file(
  GLOB_RECURSE modules_implementation
  RELATIVE "${CMAKE_CURRENT_LIST_DIR}"
  CONFIGURE_DEPENDS "*.cpp"
)

target_sources(Matrix PUBLIC FILE_SET matrixInterface TYPE CXX_MODULES FILES ${modules_interfaces} PRIVATE ${modules_implementation})

install(
  TARGETS Matrix
  EXPORT ${PROJECT_NAME}Targets # this is the name of the export var. containing info to reuse the
                                # targets in other projects
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
  FILE_SET matrixInterface DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/Matrix"
)
