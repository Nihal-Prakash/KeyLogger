cmake_minimum_required(VERSION 3.16)
project(c_folder LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

file(GLOB C_SOURCES CONFIGURE_DEPENDS "*.c")
if(NOT C_SOURCES)
  message(FATAL_ERROR "No .c files found in ${CMAKE_CURRENT_SOURCE_DIR}")
endif()

set(COMMON_WARN
  -Wall -Wextra -Wpedantic
  -Wshadow -Wformat=2 -Wundef
  -Wconversion -Wsign-conversion
  -Wstrict-prototypes -Wmissing-prototypes
  -Werror=implicit-function-declaration
)

set(COMMON_OPT
  -O3
  -march=native -mtune=native
  -fno-common
  -pipe
)

foreach(src ${C_SOURCES})
  get_filename_component(base ${src} NAME_WE)
  set(target "${base}.exe")

  add_executable(${target} ${src})

  set_target_properties(${target} PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

  target_compile_options(${target} PRIVATE
    ${COMMON_WARN}
    ${COMMON_OPT}
  )
endforeach()
