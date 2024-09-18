cmake_minimum_required(VERSION 3.15)
project(request CXX)

find_package(CURL REQUIRED)
find_package(wxWidgets REQUIRED)
file(GLOB SRC_FILES src/*.cpp src/**/*.cpp)

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

target_link_libraries(${PROJECT_NAME} CURL::libcurl wxWidgets::wxWidgets)
