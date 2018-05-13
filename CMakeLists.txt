project(Siliconverter)
cmake_minimum_required(VERSION 3.2.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#include(GNUInstallDirs)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set (CMAKE_CXX_STANDARD 11)

if ("${LIB64}" STREQUAL "TRUE")
	set(LIBSUFFIX 64)
else()
	set(LIBSUFFIX "")
endif()

set(INSTALL_LIB_DIR lib${LIBSUFFIX} CACHE PATH "Installation directory for libraries")
mark_as_advanced(INSTALL_LIB_DIR)
set(CMAKE_AUTOMOC ON)

#add_subdirectory(tech_reader)
add_subdirectory(def)
add_subdirectory(lef)
#add_subdirectory(schematics)
#add_subdirectory(schematics_reader)
#add_subdirectory(qschematics)
#add_subdirectory(magic)
#add_subdirectory(magic3d)
#add_subdirectory(contacts)
#add_subdirectory(vcd)
#add_subdirectory(vcd_reader)
#add_subdirectory(tech)
#add_subdirectory(blif)
#add_subdirectory(cmap_reader)
#add_subdirectory(gds2)
#add_subdirectory(helpers)
#add_subdirectory(symbol_reader)
#add_subdirectory(symbols)
#add_subdirectory(coriolis)

set(CMAKE_CXX_FLAGS "-std=c++14 -g3 -Wall")

#add_executable(lef src/main.cpp src/lef.cpp src/lefdef_parser.cpp src/lefparser.cpp)
