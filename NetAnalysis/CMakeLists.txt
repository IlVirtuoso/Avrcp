
project(NetAnalysis)

set(CMAKE_CXX_STANDARD 20)



set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(networkit) 
find_package(ogdf)
find_package(Qt6 COMPONENTS Core Charts Gui Widgets PrintSupport )
message(STATUS NETWORKIT: ${NETWORKIT_INCLUDE_DIR})
message(STATUS NETWORKIT: ${NETWORKIT_LINK_DIR})

add_executable(NetAnalysis main.cpp  ./include/Analyzers.hpp "Analyzers.cpp" ./include/Routines.hpp "Routines.cpp"   "Plotter.cpp")

target_link_libraries(NetAnalysis PRIVATE ${NETWORKIT_LINK_DIR} 
Qt6::Core Qt6::Gui Qt6::Charts Qt6::Widgets ${ADDITIONAL_LIBRARIES}
 COIN OGDF
)
target_include_directories(NetAnalysis PUBLIC ./include ${NETWORKIT_INCLUDE_DIR} )
