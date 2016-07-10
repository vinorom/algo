file(GLOB ALL_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(source_file ${ALL_SOURCES})
    string(REPLACE ".cpp" "" exec_file ${source_file})
    add_executable(${exec_file} ${source_file})
endforeach(source_file ${ALL_SOURCES})
