##-*****************************************************************************
##
## Copyright (c) 2009-2015,
##  Sony Pictures Imageworks Inc. and
##  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
##
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are
## met:
## *       Redistributions of source code must retain the above copyright
## notice, this list of conditions and the following disclaimer.
## *       Redistributions in binary form must reproduce the above
## copyright notice, this list of conditions and the following disclaimer
## in the documentation and/or other materials provided with the
## distribution.
## *       Neither the name of Industrial Light & Magic nor the names of
## its contributors may be used to endorse or promote products derived
## from this software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
## "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
## LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
## A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
## OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
## LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
## DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
## THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
## OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
##-*****************************************************************************

IF (NOT DEFINED LIBPYTHON_VERSION)
    IF (APPLE)
        SET(LIBPYTHON_VERSION 2.7)
    ELSE()
        SET(LIBPYTHON_VERSION 2.6)
    ENDIF()
ENDIF()

SET(LIBPYTHON python${LIBPYTHON_VERSION})
OPTION(USE_LIB64 "Search for deps in lib64 vs lib" ON)

# find python lib dir and include files
IF (${CMAKE_HOST_UNIX})
    SET(LIBPYTHON_FILE "lib${LIBPYTHON}.a")
    IF(${DARWIN})
        SET(OSX_PYTHON_ROOT
            "/System/Library/Frameworks/Python.framework/Versions/${LIBPYTHON_VERSION}")
        SET(PYTHON_INCLUDE_DIR "${OSX_PYTHON_ROOT}/include/${LIBPYTHON}" )
        SET(ALEMBIC_PYTHON_ROOT "${OSX_PYTHON_ROOT}/Python")
    ELSE()
        SET(PYTHON_INCLUDE_DIR "/usr/include/${LIBPYTHON}")
        IF (USE_LIB64)
            SET(ALEMBIC_PYTHON_ROOT "/usr/lib64/${LIBPYTHON}/config")
        ELSE()
            SET(ALEMBIC_PYTHON_ROOT "/usr/lib/${LIBPYTHON}/config")
        ENDIF()
    ENDIF()
ELSE()
    SET(LIBPYTHON_FILE "${LIBPYTHON}.dll")
    IF (${WINDOWS})
        SET(ALEMBIC_PYTHON_ROOT "C:/Python${LIBPYTHON_VERSION}/libs")
    ELSE()
        SET(ALEMBIC_PYTHON_ROOT NOTFOUND)
    ENDIF()
ENDIF()

MESSAGE(STATUS "LIBPYTHON_FILE: ${LIBPYTHON_FILE}")
MESSAGE(STATUS "ALEMBIC_PYTHON_ROOT: ${ALEMBIC_PYTHON_ROOT}")

# find the python lib file
FIND_FILE(ALEMBIC_PYTHON_LIBRARY ${LIBPYTHON_FILE}
          PATHS ${ALEMBIC_PYTHON_ROOT}
)

MESSAGE(STATUS "ALEMBIC_PYTHON_LIBRARY: ${ALEMBIC_PYTHON_LIBRARY}")
MESSAGE(STATUS "Boost_PYTHON_LIBRARY: ${Boost_PYTHON_LIBRARY}")
MESSAGE(STATUS "PYTHON_INCLUDE_DIR:" ${PYTHON_INCLUDE_DIR})

IF (Boost_PYTHON_LIBRARY AND ALEMBIC_PYTHON_LIBRARY)

  MESSAGE(STATUS "Found libboost_python: ${Boost_PYTHON_LIBRARY}")
  SET(PLIBS ${ALEMBIC_PYTHON_LIBRARY} ${Boost_PYTHON_LIBRARY})

  SET(CPP_FILES
      PyAlembicOpenGL.cpp
      main.cpp
  )

  LINK_LIBRARIES(${CORE_LIBS}
                 AlembicAbcOpenGL
                 ${PLIBS}
                 ${ALEMBIC_PYILMBASE_PYIMATH_LIB}
  )

  INCLUDE_DIRECTORIES("/usr/include/python${LIBPYTHON_VERSION}" "${ALEMBIC_SOURCE_DIR}/lib"
      "${ALEMBIC_SOURCE_DIR}/python/PyAbcOpenGL")

  ADD_LIBRARY(alembicglmodule SHARED ${CPP_FILES})

  # to get rid of the "lib" prefix from cmake
  SET_TARGET_PROPERTIES(alembicglmodule PROPERTIES PREFIX "")

  # macosx python modules have the .so suffix
  IF (${DARWIN})
    SET_TARGET_PROPERTIES(alembicglmodule PROPERTIES SUFFIX ".so")
  ENDIF()

  INSTALL(TARGETS alembicglmodule
          LIBRARY DESTINATION lib/python${LIBPYTHON_VERSION}/site-packages)

ELSE()
    MESSAGE( FATAL_ERROR "Unable to find Python libs" )
ENDIF()
