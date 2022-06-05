project(netanalyst)


add_custom_target( netanalyst ALL
COMMAND cd /D ${CMAKE_CURRENT_SOURCE_DIR}
COMMAND npm run build
COMMAND ${CMAKE_COMMAND} -E copy_directory dist ${CMAKE_BINARY_DIR}/bin/netanalyst
)
