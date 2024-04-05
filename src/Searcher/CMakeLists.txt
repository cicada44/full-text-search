set(target_name Searcher)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_library(
    ${target_name}
    STATIC
        Searcher.cpp
        ${path_header_deps}/Searcher/Searcher.hpp
)

add_library(
    Result
    STATIC
        Result.cpp
        ${path_header_deps}/Searcher/Result.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PUBLIC
        picosha2
        NgramParser
        IndexBuilder
        ConfigParser
        Result
        TextIndexAccessor
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(
    Result
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Testing part

set(target_name_tests Searcher.test)

add_executable(${target_name_tests})

target_sources(
    ${target_name_tests}
    PRIVATE
        Searcher.test.cpp
)

set_compile_options(${target_name_tests})

target_link_libraries(
    ${target_name_tests}
    PUBLIC
        gtest_main
        NgramParser
        ConfigParser
        Searcher
)

target_include_directories(
    ${target_name_tests}
    PUBLIC
        ${path_header_deps}
)

include(GoogleTest)
gtest_discover_tests(${target_name_tests})
