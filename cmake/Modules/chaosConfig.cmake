INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CHAOS chaos)

FIND_PATH(
    CHAOS_INCLUDE_DIRS
    NAMES chaos/api.h
    HINTS $ENV{CHAOS_DIR}/include
        ${PC_CHAOS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CHAOS_LIBRARIES
    NAMES gnuradio-chaos
    HINTS $ENV{CHAOS_DIR}/lib
        ${PC_CHAOS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CHAOS DEFAULT_MSG CHAOS_LIBRARIES CHAOS_INCLUDE_DIRS)
MARK_AS_ADVANCED(CHAOS_LIBRARIES CHAOS_INCLUDE_DIRS)

