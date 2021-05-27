cmake_minimum_required(VERSION 3.19)

project(Interp)

set(CMAKE_BUILD_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cbuild})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Interp ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_link_libraries(Interp ${CMAKE_DL_LIBS})

target_include_directories(Interp PUBLIC MemoryManager LexAnalizer Visitor Syntax Evaluator CmdHistoryManager Interpreter)

add_subdirectory(MemoryManager)
add_subdirectory(LexAnalizer)
add_subdirectory(Visitor)
add_subdirectory(Syntax)
add_subdirectory(Evaluator)
add_subdirectory(Interpreter)
add_subdirectory(CmdHistoryManager)




