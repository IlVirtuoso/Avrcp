
project(NetAnalysis)

set(CMAKE_CXX_STANDARD 20)


#find_package(Qt6 REQUIRED COMPONENTS Core Charts Gui Widgets PrintSupport )
find_package(Qt5 REQUIRED COMPONENTS Core Charts Gui Widgets PrintSupport )


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(networkit) 
FIND_PACKAGE(Boost 1.79 REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Charts Widgets PrintSupport DataVisualization)
message(STATUS NETWORKIT: ${NETWORKIT_INCLUDE_DIR})
message(STATUS NETWORKIT: ${NETWORKIT_LINK_DIR})
add_executable(NetAnalysis  "./src/main.cpp" "./src/Centralities.cpp"  "./src/GraphAnalyzer.cpp" "./src/Plotter.cpp" "./include/qcustomplot.h" "./src/qcustomplot.cpp" "src/Communities.cpp" "src/GraphVisualizer.cpp")

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
Qt5::Core Qt5::Gui Qt5::Charts Qt5::Widgets Qt5::PrintSupport Qt5::DataVisualization ${ADDITIONAL_LIBRARIES} networkit ${Boost_LIBRARIES} cgraph gvc
)


target_include_directories(NetAnalysis PRIVATE include ${NETWORKIT_INCLUDE_DIR} ${Boost_INCLUDE_DIR} )
if(WIN32)
add_custom_command(TARGET NetAnalysis
COMMAND windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NetAnalysis.exe)
endif()
configure_file(doc/musae_git_edges.csv ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/musae_git_edges.csv COPYONLY)
