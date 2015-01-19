# Setting the set of locations to search for FTGL.
set(FTGL_SEARCH_PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

# Finding the include directory for FTGL.
find_path(FTGL_INCLUDE_DIR ftgl.h
  HINTS
  $ENV{FTGLDIR}
  PATH_SUFFIXES include/FTGL include
  PATHS ${FTGL_SEARCH_PATHS}
)

# Finding the library for FTGL.
find_library(FTGL_LIBRARY_TEMP
  NAMES FTGL
  HINTS
  $ENV{FTGLDIR}
  PATH_SUFFIXES lib64 lib
  PATHS ${FTGL_SEARCH_PATHS}
)
