file(GLOB sources *.cpp)

add_library(reaveros-loader STATIC
    ${sources}
)

set(install_dir ${CMAKE_INSTALL_PREFIX}/usr/lib)

install(TARGETS reaveros-loader
    DESTINATION ${install_dir}
)
