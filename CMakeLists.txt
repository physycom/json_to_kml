cmake_minimum_required (VERSION 3.1)
project (json_to_kml)
set (CMAKE_CXX_STANDARD 11)

### Set output directories on a per-configuration base
# Single configuration
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{HOME}/bin )
# Multi configuration
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    if( OUTPUTCONFIG STREQUAL "RELEASE" )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} $ENV{HOME}/bin )
    else()
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG} )
    endif()
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(JSONCONS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/jsoncons/src)
set(RAPIDXML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/rapidxml/src)

if(MSVC)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${JSONCONS_INCLUDE_DIR} ${RAPIDXML_INCLUDE_DIR})

add_executable(json_to_kml ${CMAKE_SOURCE_DIR}/src/json_to_kml.cpp)
add_executable(kml_to_json ${CMAKE_SOURCE_DIR}/src/kml_to_json.cpp)
install (TARGETS json_to_kml kml_to_json DESTINATION ${CMAKE_SOURCE_DIR}/bin)
