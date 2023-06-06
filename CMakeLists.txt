cmake_minimum_required(VERSION 3.2)

project(observable LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(GNUInstallDirs)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(observable STATIC
  observable_global.h
  observable.h
)

target_include_directories(observable
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(observable PUBLIC Qt6::Core)
target_compile_definitions(observable PRIVATE OBSERVABLE_LIBRARY)

# Generate the export file
install(TARGETS observable
  EXPORT observable
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)


# Export the project
install(EXPORT observable
  FILE observable.cmake
  NAMESPACE observable::
  DESTINATION lib/cmake/observable
)

# Install the header files to the installation directory
install(FILES observable.h observable_global.h DESTINATION include)

# Install config file
install(FILES observable-config.cmake DESTINATION lib/cmake/observable)
