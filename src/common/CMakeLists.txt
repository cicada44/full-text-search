set(target_name NgramParser)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_library(
    ${target_name}
    STATIC
        NgramParser.cpp
        ${path_header_deps}/NgramParser/NgramParser.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Testing part

set(target_name_tests NgramParser.test)

add_executable(${target_name_tests})

target_sources(
    ${target_name_tests}
    PRIVATE
        NgramParser.test.cpp
)

set_compile_options(${target_name_tests})

target_link_libraries(
    ${target_name_tests}
    PUBLIC
        gtest_main
        NgramParser
)

target_include_directories(
    ${target_name_tests}
    PUBLIC
        ${path_header_deps}
)

include(GoogleTest)
gtest_discover_tests(${target_name_tests})
