include(FetchContent)
FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true)
FetchContent_MakeAvailable(googletest)

add_executable(tests 
  test_grid_init.cpp
  test_grid_candidates.cpp
  test_naked_single.cpp
  test_hidden_single.cpp
  test_pointing_elimination.cpp
  test_hidden_pair.cpp
  test_claiming_pair.cpp
)
target_link_libraries(tests PRIVATE core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)

