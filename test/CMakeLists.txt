cmake_minimum_required(VERSION 3.8)

aux_source_directory(. SOURCES)

add_executable(plottest ${SOURCES})

set_target_properties(plottest PROPERTIES
	CXX_STANDARD 14
)

target_link_libraries(plottest PUBLIC
	Matplotlib
)
