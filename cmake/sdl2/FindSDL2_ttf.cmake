# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#  Copyright 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
#  Copyright 2000-2019 Kitware, Inc. and Contributors
#  All rights reserved.

#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:

#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.

#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.

#  * Neither the name of Kitware, Inc. nor the names of Contributors
#    may be used to endorse or promote products derived from this
#    software without specific prior written permission.

#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


# SDL2 Library required
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
  set(SDL2_TTF_SDL2_NOT_FOUND "Could NOT find SDL2 (SDL2 is required by SDL2_ttf).")
  if(SDL2_ttf_FIND_REQUIRED)
    message(FATAL_ERROR ${SDL2_TTF_SDL2_NOT_FOUND})
  else()
      if(NOT SDL2_ttf_FIND_QUIETLY)
        message(STATUS ${SDL2_TTF_SDL2_NOT_FOUND})
      endif()
    return()
  endif()
  unset(SDL2_TTF_SDL2_NOT_FOUND)
endif()


# Define options for searching SDL2_ttf Library in a custom path

set(SDL2_TTF_PATH "" CACHE STRING "Custom SDL2_ttf Library path")

set(_SDL2_TTF_NO_DEFAULT_PATH OFF)
if(SDL2_TTF_PATH)
  set(_SDL2_TTF_NO_DEFAULT_PATH ON)
endif()

set(SDL2_TTF_NO_DEFAULT_PATH ${_SDL2_TTF_NO_DEFAULT_PATH}
    CACHE BOOL "Disable search SDL2_ttf Library in default path")
unset(_SDL2_TTF_NO_DEFAULT_PATH)

set(SDL2_TTF_NO_DEFAULT_PATH_CMD)
if(SDL2_TTF_NO_DEFAULT_PATH)
  set(SDL2_TTF_NO_DEFAULT_PATH_CMD NO_DEFAULT_PATH)
endif()

# Search for the SDL2_ttf include directory
find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
  HINTS
    ENV SDL2TTFDIR
    ENV SDL2DIR
    ${SDL2_TTF_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES SDL2
                # path suffixes to search inside ENV{SDL2DIR}
                # and ENV{SDL2TTFDIR}
                include/SDL2 include
  PATHS ${SDL2_TTF_PATH}
  DOC "Where the SDL2_ttf headers can be found"
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

# Search for the SDL2_ttf library
find_library(SDL2_TTF_LIBRARY
  NAMES SDL2_ttf
  HINTS
    ENV SDL2TTFDIR
    ENV SDL2DIR
    ${SDL2_TTF_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
  PATHS ${SDL2_TTF_PATH}
  DOC "Where the SDL2_ttf Library can be found"
)

# Read SDL2_ttf version
if(SDL2_TTF_INCLUDE_DIR AND EXISTS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h")
  file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MAJOR "${SDL2_TTF_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MINOR "${SDL2_TTF_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_PATCH "${SDL2_TTF_VERSION_PATCH_LINE}")
  set(SDL2_TTF_VERSION_STRING ${SDL2_TTF_VERSION_MAJOR}.${SDL2_TTF_VERSION_MINOR}.${SDL2_TTF_VERSION_PATCH})
  unset(SDL2_TTF_VERSION_MAJOR_LINE)
  unset(SDL2_TTF_VERSION_MINOR_LINE)
  unset(SDL2_TTF_VERSION_PATCH_LINE)
  unset(SDL2_TTF_VERSION_MAJOR)
  unset(SDL2_TTF_VERSION_MINOR)
  unset(SDL2_TTF_VERSION_PATCH)
endif()

set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_ttf
                                  REQUIRED_VARS SDL2_TTF_LIBRARIES SDL2_TTF_INCLUDE_DIRS
                                  VERSION_VAR SDL2_TTF_VERSION_STRING)


mark_as_advanced(SDL2_TTF_PATH
                 SDL2_TTF_NO_DEFAULT_PATH
                 SDL2_TTF_LIBRARY
                 SDL2_TTF_INCLUDE_DIR)


if(SDL2_TTF_FOUND)

  # SDL2::TTF target
  if(SDL2_TTF_LIBRARY AND NOT TARGET SDL2::TTF)
    add_library(SDL2::TTF UNKNOWN IMPORTED)
    set_target_properties(SDL2::TTF PROPERTIES
                          IMPORTED_LOCATION "${SDL2_TTF_LIBRARY}"
                          INTERFACE_INCLUDE_DIRECTORIES "${SDL2_TTF_INCLUDE_DIR}"
                          INTERFACE_LINK_LIBRARIES SDL2::Core)
  endif()
endif()
