# Try to find the docopt library and header
# Once done this will define

# Docopt_FOUND           - system has docopt and it can be used
# Docopt_INCLUDE_DIRS    - directory where the header file can be found
# Docopt_LIBRARY_DIRS    - Path where docopt required libs file can be found

set(Docopt_FOUND FALSE)

##############################################################################
### Find headers
##
find_path(Docopt_INCLUDE_DIR docopt.h "")

set(Docopt_INCLUDE_DIRS
  ${Docopt_INCLUDE_DIR}
  )

##############################################################################
### Find libraries
##
if(UNIX)
  find_path(Docopt_shared_LIBRARY_DIR libdocopt.so "")
  find_path(Docopt_static_LIBRARY_DIR libdocopt.a "")

  set(Docopt_LIBRARY_DIRS
    ${Docopt_shared_LIBRARY_DIR}
    ${Docopt_static_LIBRARY_DIR}
    )
endif()

##############################################################################
### Update 'Docopt_FOUND'
##
if(Docopt_INCLUDE_DIRS AND
  Docopt_LIBRARY_DIRS
  )
  set(Docopt_FOUND TRUE)
  set(Docopt_USE_FILE ${CMAKE_CURRENT_LIST_DIR}/USEDocopt.cmake)
endif()
