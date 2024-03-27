include(GenerateExportHeader)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

add_library(${PROJECT_NAME} SHARED src/Utils.cpp src/Cpu.cpp src/Memory.cpp)

add_library(myproject::nemu ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE myproject::myproject_options myproject::myproject_warnings)

target_include_directories(
  ${PROJECT_NAME} ${WARNING_GUARD}
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/private_headers>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/public_headers>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/configured_files/include/>)

target_link_system_libraries(
  ${PROJECT_NAME}
  PRIVATE
  fmt::fmt
  spdlog::spdlog
  elf)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

# Strip target if option enabled AND is release
if(myproject_STRIP_TARGETS AND CMAKE_BUILD_TYPE STREQUAL "Release")
  # Strip binary for release builds
  message("Striping targe.")
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>)
endif()

# Testing support
enable_testing()
add_subdirectory(tests)

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME
                       ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}Export.h)

target_include_directories(${PROJECT_NAME} ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/>)

# Installation
include(GNUInstallDirs)

# Install targets
install(TARGETS ${PROJECT_NAME})

# Install direcotories
install(DIRECTORY src/public_headers/${PROJECT_NAME} DESTINATION include)

# Install individual header files
install(FILES ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}Export.h
              # More files can me here...
        DESTINATION include/${PROJECT_NAME})
