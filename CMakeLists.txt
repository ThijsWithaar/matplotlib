cmake_minimum_required(VERSION 3.0)

project(matplotlib-cpp)
set(MPL_VERSION_MAJOR 0)
set(MPL_VERSION_MINOR 1)

add_subdirectory(src)
add_subdirectory(test)

#-- packaging --

if(EXISTS "/etc/debian_version")
	set(DEBIAN TRUE CACHE BOOL "Enable .deb generation")
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/matplotlibConfigVersion.cmake"
    VERSION "${MPL_VERSION_MAJOR}.${MPL_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/matplotlibConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/matplotlibConfig.cmake"
    INSTALL_DESTINATION lib/cmake/matplotlib
)

install(EXPORT matplotlibTargets NAMESPACE "Matplotlib::" DESTINATION lib/cmake/matplotlib)
install(FILES "${PROJECT_BINARY_DIR}/matplotlibConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/matplotlibConfig.cmake"
        DESTINATION lib/cmake/matplotlib)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ wrapper for python's matplotlib")
set(CPACK_PACKAGE_CONTACT "thijs.withaar@gmail.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${MPL_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${MPL_VERSION_MINOR})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "python, libeigen3-dev")
set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "python-dev, pybind11-dev")

if(DEBIAN)
	set(CPACK_GENERATOR "DEB")
endif()

INCLUDE(CPack)
