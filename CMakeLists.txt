CMAKE_MINIMUM_REQUIRED (VERSION 3.18)

PROJECT(michael VERSION 2.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS numeric_odeint)
find_package(SymEngine CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)
pkg_check_modules(gmpxx REQUIRED IMPORTED_TARGET gmpxx)
    
add_executable(symTest main.cpp)
target_include_directories(symTest PRIVATE ${SYMENGINE_INCLUDE_DIRS})
target_link_libraries(symTest PRIVATE Boost::numeric_odeint)
target_link_libraries(symTest PRIVATE ${SYMENGINE_LIBRARIES})
target_link_libraries(symTest PRIVATE flint)
target_link_libraries(symTest PRIVATE PkgConfig::gmp)
target_link_libraries(symTest PRIVATE PkgConfig::gmpxx)

