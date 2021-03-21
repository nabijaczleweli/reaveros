file(GLOB includes crypto/*.h)

set(install_dir ${CMAKE_INSTALL_PREFIX}/usr/include/crypto)

install(FILES ${includes}
    DESTINATION ${install_dir}
)
