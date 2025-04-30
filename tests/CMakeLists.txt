
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
include(CTest)
include(Catch)

add_executable(test_symengine test_symengine.cpp)
if (APPLE)
   target_include_directories(test_symengine PRIVATE /opt/homebrew/include)
   target_link_directories(test_symengine PRIVATE /opt/homebrew/lib)
endif (APPLE)
target_include_directories(test_symengine PRIVATE ${SYMENGINE_INCLUDE_DIRS})
target_link_libraries(test_symengine PRIVATE Boost::numeric_odeint)
target_link_libraries(test_symengine PRIVATE ${SYMENGINE_LIBRARIES})
target_link_libraries(test_symengine PRIVATE flint)
target_link_libraries(test_symengine PRIVATE PkgConfig::gmp)
target_link_libraries(test_symengine PRIVATE PkgConfig::gmpxx)
target_link_libraries(test_symengine PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(test_symengine)

