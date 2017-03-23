if(NOT Docopt_USE_FILE_INCLUDED)
  set(Docopt_USE_FILE_INCLUDED 1)
  # Add include directories needed to use docopt.
  include_directories(${Docopt_INCLUDE_DIRS})
  # TODO is it the right way to do it? Isn't it inadequate
  # with the new 'target_include_directories' command?


  # Add link directories needed to use docopt.
  link_directories(${Docopt_LIBRARY_DIRS})
endif()
