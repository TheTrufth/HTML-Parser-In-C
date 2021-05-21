cmake_minimum_required(VERSION 3.19)
project(HTML_Parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(HTML_Parser
        file.html
        html
        html.c)
