include(FetchContent)

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.0.0  # Replace with the desired release tag or commit hash
)

FetchContent_MakeAvailable(cli11)
