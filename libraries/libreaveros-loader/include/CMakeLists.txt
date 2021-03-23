file(GLOB includes reaveros/loader/*.h)

set(install_dir ${CMAKE_INSTALL_PREFIX}/usr/include/reaveros/loader)

install(FILES ${includes}
    DESTINATION ${install_dir}
)
