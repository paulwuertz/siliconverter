set(TARGET "LEF")

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

BISON_TARGET(LEFParser lef_parser.yy ${CMAKE_CURRENT_BINARY_DIR}/src/lef_parser.cpp)
FLEX_TARGET(LEFScanner lef_scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/src/lef_scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(LEFScanner LEFParser)

include_directories(
	"${CMAKE_CURRENT_BINARY_DIR}/../helpers"
	"${CMAKE_CURRENT_BINARY_DIR}/include"
	"${CMAKE_CURRENT_BINARY_DIR}/src"
	${CMAKE_CURRENT_BINARY_DIR}
)

set(SOURCES
	src/lefdata.cpp
	src/leflayer.cpp
	src/leflayerinfo.cpp
	src/lefmacro.cpp
	src/lefobstruction.cpp
	src/lefpin.cpp
	src/lefport.cpp
	src/lefscanner.cpp
	src/lefvia.cpp
	../helpers/PointF.cpp
)

add_library(${TARGET} SHARED
	${BISON_LEFParser_OUTPUTS}
	${FLEX_LEFScanner_OUTPUTS}
	${SOURCES}
)
