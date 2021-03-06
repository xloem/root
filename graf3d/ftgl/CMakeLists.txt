############################################################################
# CMakeLists.txt file for building ROOT graf3d/ftgl package
############################################################################

include_directories(${OPENGL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})

if(MACOSX_GLU_DEPRECATED)
  add_definitions(-Wno-deprecated-declarations)
endif()

ROOT_LINKER_LIBRARY(FTGL
    src/FTBitmapGlyph.cxx
    src/FTCharmap.cxx
    src/FTContour.cxx
    src/FTExtrdGlyph.cxx
    src/FTFace.cxx
    src/FTFont.cxx
    src/FTGLBitmapFont.cxx
    src/FTGLExtrdFont.cxx
    src/FTGLOutlineFont.cxx
    src/FTGLPixmapFont.cxx
    src/FTGLPolygonFont.cxx
    src/FTGLTextureFont.cxx
    src/FTGlyphContainer.cxx
    src/FTGlyph.cxx
    src/FTLibrary.cxx
    src/FTOutlineGlyph.cxx
    src/FTPixmapGlyph.cxx
    src/FTPoint.cxx
    src/FTPolyGlyph.cxx
    src/FTSize.cxx
    src/FTTextureGlyph.cxx
    src/FTVectoriser.cxx
  LIBRARIES
    ${OPENGL_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ZLIB::ZLIB
  BUILTINS
    FREETYPE
)

ROOT_INSTALL_HEADERS()
