include(FindPkgConfig)
pkg_check_modules(SNDFILE REQUIRED sndfile>=1.2.2)
file(GLOB_RECURSE MUZA_SOURCES "Muza/Source/*.c")
add_executable(Muza ${MUZA_SOURCES})
target_compile_options(Muza PRIVATE -std=gnu23 -Wall -Wextra -Wpedantic
                                    -Wfatal-errors)
target_link_directories(Muza PRIVATE ${SNDFILE_LIBRARY_DIRS})
target_include_directories(Muza PRIVATE "Muza/Include")
target_link_libraries(Muza m ${SNDFILE_LIBRARIES})
