set(target_name ConfigParser)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_library(
    ${target_name}
    STATIC
        ConfigParser.cpp
        ${path_header_deps}/ConfigParser/ConfigParser.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PUBLIC
        pugixml
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${path_header_deps}
)
