set(target_name fts-csl)

set(path_header_deps ${PROJECT_SOURCE_DIR}/include)

add_executable(
    ${target_name}
)

target_sources(
    ${target_name}
    PRIVATE
        main.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PRIVATE
        ConfigParser
        NgramParser
        IndexBuilder
        TextIndexWriter
        TextIndexAccessor
        Searcher
        Filter
        CLI11::CLI11
        replxx
        csv
        ${qt_include_deps}
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/${FolderSource}
  ${csv_SOURCE_DIR}/single_include
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${path_header_deps}
)
