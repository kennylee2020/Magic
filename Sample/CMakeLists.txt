# 1、Sample executable
add_executable(Sample "")

# 2、add sources
file(GLOB_RECURSE srcs
	${CMAKE_CURRENT_LIST_DIR}/src/*.h
	${CMAKE_CURRENT_LIST_DIR}/src/*.hpp
 	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)

target_sources(Sample
PRIVATE
 	${srcs}
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${srcs})

# 3、Link
target_link_libraries(Sample
PRIVATE
	Magic
)