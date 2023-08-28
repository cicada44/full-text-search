set(target_name fts)

add_library(
    ${target_name}
    STATIC
        sum.cpp
        ../../include/libmath/sum.h
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Add testing

set(target_name_tests fts_tests)

add_executable(${target_name_tests})

target_sources(
    ${target_name_tests}
    PRIVATE
        sum.test.cpp
)

set_compile_options(${target_name_tests})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(
    ${target_name_tests}
    PUBLIC
        ${GTEST_LIBRARIES}
        pthread
        fts
)

target_include_directories(
    ${target_name_tests}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
