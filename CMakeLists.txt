cmake_minimum_required(VERSION 3.21)
project(shotten LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FILE(GLOB src shotten/*.cpp shotten/*.h)
ADD_EXECUTABLE(shotten ${src})

target_link_libraries(shotten PRIVATE sfml-graphics)
target_compile_features(shotten PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET shotten POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:shotten> $<TARGET_FILE_DIR:shotten> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS shotten)


