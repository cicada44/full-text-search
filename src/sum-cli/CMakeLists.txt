set(target_name sum)

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
        fts
        CLI11::CLI11
)

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
