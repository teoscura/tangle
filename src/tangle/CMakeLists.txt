file(GLOB_RECURSE TANGLE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}
    *.cc)

add_executable(tangle
    ${TANGLE_SRC}
)

target_include_directories(tangle PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)