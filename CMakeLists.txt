cmake_minimum_required(VERSION 3.0)

project(smk VERSION 0.0.0)


##############################################################################
### Plocies...
##
cmake_policy(SET CMP0053 OLD)

##############################################################################
### Options
##
option(${PROJECT_NAME}_BUILD_TESTS "Build tests for ${PROJECT_NAME}" ON)
if(${PROJECT_NAME}_BUILD_TESTS)
  enable_testing()
  message(STATUS "Tests have been enabled.")
endif()

##############################################################################
### Definitions
##
add_definitions(-D${PROJECT_NAME}_VERSION="${${PROJECT_NAME}_VERSION}")

##############################################################################
### Language
##
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##############################################################################
### Module path
##
set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH}
  )

##############################################################################
### Find packages
##
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(Docopt REQUIRED)
include(${Docopt_USE_FILE})


##############################################################################
### Files listing
##
set(CPP_FILES
  main.cpp
  smkCommandBase.cpp
  )

set(TEMPLATE_FILES
  smkCommandInfo.hpp
  )

set(HEADER_FILES
  smkIO.h
  smkCommandBase.h
  smkCommandInfo.h
  smkIO.h
  smkImageTypeHelpers.h
  )

set(PROJECT_FILES
  ${CPP_FILES}
  ${TEMPLATE_FILES}
  ${HEADER_FILES}
  )

##############################################################################
### Target definitiions
##
add_executable(${PROJECT_NAME}
  ${PROJECT_FILES}
  )

target_link_libraries(${PROJECT_NAME}
  docopt
  ${ITK_LIBRARIES}
  )
