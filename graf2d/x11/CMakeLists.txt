############################################################################
# CMakeLists.txt file for building ROOT graf2d/x11 package
# @author Pere Mato, CERN
############################################################################

ROOT_STANDARD_LIBRARY_PACKAGE(GX11
  HEADERS
    TGX11.h
  SOURCES
    src/gifdecode.c
    src/gifencode.c
    src/gifquantize.c
    src/GX11Gui.cxx
    src/Rotated.cxx
    src/TGX11.cxx
  DICTIONARY_OPTIONS
    -writeEmptyRootPCM
  LIBRARIES
    ${X11_LIBRARIES}
    ${X11_Xpm_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
  DEPENDENCIES
    Core
  INSTALL_OPTIONS
    FILTER "inc/X11/"
    FILTER "X11$"
)

target_include_directories(GX11 PRIVATE ${X11_INCLUDE_DIR})

if(AIX)
  target_include_directories(GX11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
endif()
