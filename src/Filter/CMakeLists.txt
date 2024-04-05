set(target_name Filter)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_library(
    ${target_name}
    STATIC
        Filter.cpp
        ${path_header_deps}/Filter/Filter.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PUBLIC
        csv
        Result
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
