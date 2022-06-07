
project(NetAnalysis)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory("netanalyst")
find_package(networkit) 
find_package(Drogon) 
#find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport )
message(STATUS NETWORKIT: ${NETWORKIT_INCLUDE_DIR})
message(STATUS NETWORKIT: ${NETWORKIT_LINK_DIR})

add_executable(NetAnalysis main.cpp  ./include/Analyzers.hpp "Analyzers.cpp" ./include/Routines.hpp  )
target_link_libraries(NetAnalysis PRIVATE Drogon::Drogon   ${NETWORKIT_LINK_DIR} 
#Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport ${ADDITIONAL_LIBRARIES}
)
target_include_directories(NetAnalysis PUBLIC ./include ${NETWORKIT_INCLUDE_DIR} )
