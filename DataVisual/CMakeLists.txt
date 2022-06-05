
project(DataVisual)

set(CMAKE_CXX_STANDARD 20)
find_package(networkit) 
find_package(Drogon) 

add_executable(DataVisual main.cpp )
target_link_libraries(DataVisual PRIVATE Drogon::Drogon)
