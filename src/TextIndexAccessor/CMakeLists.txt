set(target_name TextIndexAccessor)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_library(
    ${target_name}
    STATIC
        TextIndexAccessor.cpp
        ${path_header_deps}/IndexAccessor/TextIndexAccessor.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PUBLIC
        picosha2
        NgramParser
        TextIndexWriter
        ConfigParser
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Testing part

set(target_name_tests TextIndexAccessor.test)

add_executable(${target_name_tests})

target_sources(
    ${target_name_tests}
    PRIVATE
    TextIndexAccessor.test.cpp
)

set_compile_options(${target_name_tests})

target_link_libraries(
    ${target_name_tests}
    PUBLIC
        gtest_main
        NgramParser
        ConfigParser
        TextIndexWriter
)

target_include_directories(
    ${target_name_tests}
    PUBLIC
        ${path_header_deps}
)

include(GoogleTest)
gtest_discover_tests(${target_name_tests})
