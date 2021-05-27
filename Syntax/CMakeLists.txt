target_include_directories(Interp PUBLIC Printer Nodes)

target_sources(Interp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Printer/Printer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Printer/Printer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Nodes/STNodeData.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Nodes/STNode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Nodes/STNode.h
        SyntaxAnalizer.cpp
        SyntaxAnalizer.h
)  
