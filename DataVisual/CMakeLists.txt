project(datavisual)

add_custom_target(datavisual
COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/StudentsApproach
COMMAND npm build
)
