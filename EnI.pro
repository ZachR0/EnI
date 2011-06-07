########################################
#EnI Game Engine Project
#QtCreator Project Config
#Zach Rogers <zachrog@gmail.com>
########################################

#Remove Qt crap that we don't need
QT       -= core
QT       -= gui

#Set the name build target
TARGET = EnI

#Console App only
CONFIG   += console

#OSX Configuration
macx {

#No .app bullshit when building under osx
CONFIG   -= app_bundle
TEMPLATE -= app

#libs for osx
LIBS += ../src/Lua/5.1.4_osx/liblua5.1.dylib
LIBS += -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -I/System/Library/Frameworks/OpenGL.framework/Headers ../src/SDLMain.m -framework SDL -framework SDL_image -framework SDL_ttf -framework Cocoa -framework OpenGL

#Include paths
INCLUDEPATH += Code/Lua/5.1.4_osx/include
INCLUDEPATH += /Library/Frameworks/SDL.framework/Headers
INCLUDEPATH += /Library/Frameworks/SDL_image.framework/Headers
INCLUDEPATH += /Library/Frameworks/SDL_ttf.framework/Headers
INCLUDEPATH += /System/Library/Frameworks/OpenGL.framework/Headers
}


#Code and whatnot
SOURCES += \
    Video.cpp \
    TTF.cpp \
    Surfaces.cpp \
    Rendering.cpp \
    main.cpp \
    Lua.cpp \
    Events.cpp

OTHER_FILES += \
    SDLMain.m

HEADERS += \
    Video.h \
    TTF.h \
    Surfaces.h \
    SDLMain.h \
    Rendering.h \
    Lua.h \
    Global.h \
    Events.h \
    Config.h
