
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
add_executable(NetAnalysis main.cpp   "GraphAnalyzer.cpp"  "Routines.cpp" "qcustomplot.cpp" "./include/qcustomplot.h" )

target_link_libraries(NetAnalysis PRIVATE ${NETWORKIT_LINK_DIR} 
#Qt6::Core Qt6::Gui Qt6::Charts Qt6::Widgets ${ADDITIONAL_LIBRARIES}
Qt5::Core Qt5::Gui Qt5::Charts Qt5::Widgets Qt5::PrintSupport ${ADDITIONAL_LIBRARIES}
COIN OGDF networkit
)


target_include_directories(NetAnalysis PUBLIC ./include ${NETWORKIT_INCLUDE_DIR} )
if(WIN32)
add_custom_command(TARGET NetAnalysis
COMMAND windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NetAnalysis.exe)
endif()
configure_file(input/lastfm_asia_edges.csv ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lastfm_asia_edges.csv COPYONLY)