cmake_minimum_required(VERSION 3.15...3.23)

project(Nemu_tests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(myproject CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET myproject_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(${PROJECT_NAME} Utils_tests.cpp Cpu_tests.cpp Memory_tests.cpp)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE myproject::myproject_warnings
          myproject::myproject_options
          Nemu
          Catch2::Catch2WithMain)

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(${PROJECT_NAME})
