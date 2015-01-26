########################
# Author: Cerek Hillen #
# Date  : 1/26/2014    #
########################

# Setting the search paths.
set(LIBDRAWTEXT_SEARCH_PATHS
  /usr/local
)

# Finding the header.
find_path(LIBDRAWTEXT_INCLUDE_DIR drawtext.h
  HINTS
  PATH_SUFFIXES include
  PATHS ${LIBDRAWTEXT_SEARCH_PATHS}
)

# Finding the library.
find_path(LIBDRAWTEXT_LIBRARY libdrawtext.a
  HINTS
  PATH_SUFFIXES lib
  PATHS ${LIBDRAWTEXT_SEARCH_PATHS}
)

# Doing everything :)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBDRAWTEXT REQUIRED_VARS LIBDRAWTEXT_LIBRARY LIBDRAWTEXT_INCLUDE_DIR)
