cmake_minimum_required(VERSION 3.8)

find_package(Eigen3 REQUIRED)
find_package(pybind11 REQUIRED)

file(GLOB CONFIGURE_DEPENDS HEADERS ../include/*.h)

aux_source_directory(. SOURCES)

add_library(Matplotlib ${SOURCES} ${HEADERS})

set_target_properties(Matplotlib PROPERTIES
	CXX_STANDARD 17
)

target_include_directories(Matplotlib PUBLIC
	${EIGEN3_INCLUDE_DIR}
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

target_link_libraries(Matplotlib PUBLIC
	pybind11::embed
)
