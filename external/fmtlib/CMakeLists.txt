include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG origin/master
)

FetchContent_MakeAvailable(fmt)
