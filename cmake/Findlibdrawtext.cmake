########################
# Author: Cerek Hillen #
# Date  : 1/26/2014    #
########################

# Setting the search paths.
set(LIBDRAWTEXT_SEARCH_PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

# Finding the header.
find_path(LIBDRAWTEXT_INCLUDE_DIR drawtext.h
  HINTS
  PATH_SUFFIXES include
  PATHS ${LIBDRAWTEXT_SEARCH_PATHS}
)

# Finding the library.
find_library(LIBDRAWTEXT_LIBRARY libdrawtext.a
  HINTS
  PATH_SUFFIXES lib lib64
  PATHS ${LIBDRAWTEXT_SEARCH_PATHS}
)

# Doing everything :)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  libdrawtext
  REQUIRED_VARS
    LIBDRAWTEXT_LIBRARY
    LIBDRAWTEXT_INCLUDE_DIR
)
