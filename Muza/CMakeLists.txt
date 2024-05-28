file(GLOB_RECURSE MUZA_SOURCES "Muza/Source/*.c")
add_executable(Muza ${MUZA_SOURCES})
target_compile_options(Muza PRIVATE -std=gnu23 -Wall -Wextra -Wpedantic
                                    -Wfatal-errors -pthread)
target_include_directories(Muza PRIVATE Muza/Include)
target_include_directories(
  Muza PRIVATE /usr/include/opus /usr/include/glib-2.0
               /usr/lib64/glib-2.0/include /usr/include/sysprof-6)
target_link_libraries(
  Muza
  m
  pthread
  glib-2.0
  sndfile
  asound
  portmidi
  portaudio)
