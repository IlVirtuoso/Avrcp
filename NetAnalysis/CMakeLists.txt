
project(NetAnalysis)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("netanalyst")
find_package(networkit) 
find_package(drogon) 
find_package(ROOT)
message(STATUS NETWORKIT: ${NETWORKIT_INCLUDE_DIR})
message(STATUS NETWORKIT: ${NETWORKIT_LINK_DIR})


add_executable(NetAnalysis main.cpp  ./include/Analyzers.hpp "Analyzers.cpp"  )
target_link_libraries(NetAnalysis PRIVATE Drogon::Drogon   ${NETWORKIT_LINK_DIR} ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(NetAnalysis PUBLIC ./include ${NETWORKIT_INCLUDE_DIR} )
