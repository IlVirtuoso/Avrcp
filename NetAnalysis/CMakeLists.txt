
project(NetAnalysis)

set(CMAKE_CXX_STANDARD 20)


#find_package(Qt6 REQUIRED COMPONENTS Core Charts Gui Widgets PrintSupport )
find_package(Qt5 REQUIRED COMPONENTS Core Charts Gui Widgets PrintSupport )


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(networkit) 
find_package(ogdf)

message(STATUS NETWORKIT: ${NETWORKIT_INCLUDE_DIR})
message(STATUS NETWORKIT: ${NETWORKIT_LINK_DIR})
file(GLOB_RECURSE INCLUDE_FILES ./include/*)
file(GLOB_RECURSE SOURCE_FILES ./src/*)
add_executable(NetAnalysis  ${SOURCE_FILES} ${INCLUDE_FILES} )

if(WIN32)
set(GRAPHVIZ_DIR "" CACHE PATH "")
set(GRAPHVIZ_INCLUDE_DIR ${GRAPHVIZ_DIR}/include) 
set(GRAPHVIZ_LIB_DIRS ${GRAPHVIZ_DIR}/lib)
message(STATUS GRAPHVIZ_DIR: ${GRAPHVIZ_DIR})
message(STATUS GRAPHVIZ_INCLUDE_DIR ${GRAPHVIZ_INCLUDE_DIR})
message(STATUS NETWORKIT: ${NETWORKIT_LINK_DIR})
target_link_directories(NetAnalysis PRIVATE ${GRAPHVIZ_LIB_DIRS})
target_link_libraries(NetAnalysis PRIVATE ${GRAPHVIZ_LIB_DIRS})
target_include_directories(NetAnalysis PRIVATE ${GRAPHVIZ_INCLUDE_DIR})
endif()

target_link_libraries(NetAnalysis PRIVATE ${NETWORKIT_LINK_DIR} 
#Qt6::Core Qt6::Gui Qt6::Charts Qt6::Widgets ${ADDITIONAL_LIBRARIES}
Qt5::Core Qt5::Gui Qt5::Charts Qt5::Widgets Qt5::PrintSupport ${ADDITIONAL_LIBRARIES} networkit cgraph gvc
)


target_include_directories(NetAnalysis PUBLIC ./include ${NETWORKIT_INCLUDE_DIR}  )
if(WIN32)
add_custom_command(TARGET NetAnalysis
COMMAND windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NetAnalysis.exe)
endif()
configure_file(input/lastfm_asia_edges.csv ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lastfm_asia_edges.csv COPYONLY)
