cmake_minimum_required(VERSION 3.8)

find_package(Eigen3 REQUIRED)
find_package(pybind11 REQUIRED)

file(GLOB HEADERS_SDK ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h)

aux_source_directory(. SOURCES)

add_library(Matplotlib ${SOURCES} ${HEADERS_SDK})

set_target_properties(Matplotlib PROPERTIES
	CXX_STANDARD 17
)

target_include_directories(Matplotlib PUBLIC
	${EIGEN3_INCLUDE_DIR}
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
	$<INSTALL_INTERFACE:include>
)

target_link_libraries(Matplotlib PUBLIC
	pybind11::embed
)

INSTALL(TARGETS Matplotlib EXPORT matplotlibTargets DESTINATION lib)
INSTALL(FILES ${HEADERS_SDK} DESTINATION include)
