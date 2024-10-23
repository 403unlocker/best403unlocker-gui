cmake_minimum_required(VERSION 3.15)
project(request CXX)

set(CMAKE_CXX_STANDARD, 20)
set(CMAKE_CXX_STANDARD_REQUIRED, True)

find_package(CURL REQUIRED)
find_package(wxWidgets REQUIRED)
find_package(tomlplusplus REQUIRED)

set(SRC_FILES
  src/main.cpp
  src/main_frame.cpp
  src/downloads.cpp
  src/config.cpp
)

if(MSVC)
  add_definitions("-DUNICODE")
  add_definitions("-D_UNICODE")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

if (DEFINED WIN32)
  add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
else()
  add_executable(${PROJECT_NAME} ${SRC_FILES})
endif()

target_link_libraries(${PROJECT_NAME} CURL::libcurl wxWidgets::wxWidgets tomlplusplus::tomlplusplus)
