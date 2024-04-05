# Index builder

set(target_name IndexBuilder)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_library(
    ${target_name}
    STATIC
        IndexBuilder.cpp
        ${path_header_deps}/Indexer/IndexBuilder.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PUBLIC
        NgramParser
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Index writer

set(target_name TextIndexWriter)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_library(
    ${target_name}
    STATIC
        TextIndexWriter.cpp
        ${path_header_deps}/Indexer/IndexWriter.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PUBLIC
        picosha2
        NgramParser
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Testing part

set(target_name_tests Indexer.test)

add_executable(${target_name_tests})

target_sources(
    ${target_name_tests}
    PRIVATE
        IndexBuilder.test.cpp
)

set_compile_options(${target_name_tests})

target_link_libraries(
    ${target_name_tests}
    PUBLIC
        gtest_main
        NgramParser
        IndexBuilder
)

target_include_directories(
    ${target_name_tests}
    PUBLIC
        ${path_header_deps}
)

include(GoogleTest)
gtest_discover_tests(${target_name_tests})
