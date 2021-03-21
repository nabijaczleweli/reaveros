file(GLOB sources *.cpp)

add_library(crypto STATIC
    ${sources}
)

set(install_dir ${CMAKE_INSTALL_PREFIX}/usr/lib)

install(TARGETS crypto
    DESTINATION ${install_dir}
)

link_libraries(freestanding)
