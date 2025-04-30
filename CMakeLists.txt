CMAKE_MINIMUM_REQUIRED (VERSION 3.5...3.30)

PROJECT(symEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

find_package(Boost REQUIRED COMPONENTS numeric_odeint)
find_package(SymEngine CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)
pkg_check_modules(gmpxx REQUIRED IMPORTED_TARGET gmpxx)
    
add_executable(symTest main.cpp)
if (APPLE)
   target_include_directories(symTest PRIVATE /opt/homebrew/include)
   target_link_directories(symTest PRIVATE /opt/homebrew/lib)
endif (APPLE)
target_include_directories(symTest PRIVATE ${SYMENGINE_INCLUDE_DIRS})
target_link_libraries(symTest PRIVATE Boost::numeric_odeint)
target_link_libraries(symTest PRIVATE ${SYMENGINE_LIBRARIES})
target_link_libraries(symTest PRIVATE flint)
target_link_libraries(symTest PRIVATE PkgConfig::gmp)
target_link_libraries(symTest PRIVATE PkgConfig::gmpxx)

