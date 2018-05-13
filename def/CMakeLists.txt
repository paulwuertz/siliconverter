set(TARGET "DEF")

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

BISON_TARGET(DEFParser def_parser.yy ${CMAKE_CURRENT_BINARY_DIR}/src/def_parser.cpp)
FLEX_TARGET(DEFScanner def_scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/src/def_scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(DEFScanner DEFParser)

include_directories(
	"${CMAKE_CURRENT_BINARY_DIR}/../helpers"
	"${CMAKE_CURRENT_BINARY_DIR}/include"
	"${CMAKE_CURRENT_BINARY_DIR}/src"
	${CMAKE_CURRENT_BINARY_DIR}
)

set(SOURCES
	src/defdata.cpp
	src/defdatapin.cpp
	src/defmoduleinfo.cpp
	src/defrouteinfo.cpp
	src/defscanner.cpp
	../helpers/PointF.cpp
)

add_library(${TARGET} SHARED
	${BISON_DEFParser_OUTPUTS}
	${FLEX_DEFScanner_OUTPUTS}
	${SOURCES}
)
