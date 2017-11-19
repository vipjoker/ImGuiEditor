
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 3.1)

set(APP_NAME MyGame)
project(${APP_NAME})


find_library(COCOA_LIBRARY Cocoa)
find_library(OpenGL_LIBRARY OpenGL)
find_library(IOKIT_LIBRARY IOKit)
find_library(COREVIDEO_LIBRARY CoreVideo)
FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox)
FIND_LIBRARY(OPENAL_LIBRARY OpenAL)
FIND_LIBRARY(QUARTZCORE_LIBRARY QuartzCore)
FIND_LIBRARY(APPLICATIONSERVICES_LIBRARY ApplicationServices)
FIND_LIBRARY(IOKIT_LIBRARY IOKit)
FIND_LIBRARY(FOUNDATION_LIBRARY Foundation)
FIND_LIBRARY(ICONV_LIBRARY iconv)


find_library(GLFW3 glfw3)
set(EXTRA_LIBS ${GLFW3} ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
        ${AUDIOTOOLBOX_LIBRARY}
        ${OPENAL_LIBRARY}
        ${QUARTZCORE_LIBRARY}
        ${APPLICATIONSERVICES_LIBRARY}
        ${IOKIT_LIBRARY}
        ${FOUNDATION_LIBRARY}
        ${ICONV_LIBRARY})

#set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)
set(COCOS2D_ROOT /Users/oleh/Documents/tools/cocos2d-x-3.15.1/)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)
#include(CocosUsePrebuiltLibs )

if (MACOSX OR APPLE)
    ADD_DEFINITIONS(-DCC_TARGET_OS_MAC)
    ADD_DEFINITIONS(-DUSE_FILE32API)
    set(PLATFORM_FOLDER mac)
elseif (LINUX)
    ADD_DEFINITIONS(-DLINUX)
    set(PLATFORM_FOLDER linux)
elseif (ANDROID)
    ADD_DEFINITIONS(-DUSE_FILE32API)
    set(PLATFORM_FOLDER android)
else ()
    message(FATAL_ERROR "Unsupported platform, CMake will exit")
endif ()


# Compiler options
if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:libcmt")
    else ()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")
    endif ()
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
            -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
            -wd4514 -wd4056 -wd4996 -wd4099)
else ()
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        ADD_DEFINITIONS(-DCOCOS2D_DEBUG=1)
    endif ()
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
    if (CLANG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif ()
endif (MSVC)

set(PLATFORM_SPECIFIC_SRC)
set(PLATFORM_SPECIFIC_HEADERS)

if (MACOSX OR APPLE)
    set(PLATFORM_SPECIFIC_SRC
            proj.ios_mac/mac/main.cpp
            )
elseif (LINUX)
    set(PLATFORM_SPECIFIC_SRC
            proj.linux/main.cpp
            )

elseif (ANDROID)
    set(PLATFORM_SPECIFIC_SRC
            proj.android-studio/app/jni/hellocpp/main.cpp
            )
endif ()

include_directories(
        /usr/local/include/GLFW
        /usr/include/GLFW
        ${COCOS2D_ROOT}
        ${COCOS2D_ROOT}/cocos
        ${COCOS2D_ROOT}/external
        ${COCOS2D_ROOT}/cocos/platform
        ${COCOS2D_ROOT}/cocos/audio/include/
        Classes
        Classes/ImGUI
)
set(IMGUI_SRC
        Classes/ImGUI/CCIMGUI.cpp
        Classes/ImGUI/imgui.cpp
        Classes/ImGUI/imgui_demo.cpp
        Classes/ImGUI/imgui_draw.cpp
        Classes/ImGUI/imgui_impl_glfw_mac.cpp
        Classes/ImGUI/IMGUIGLViewImpl.cpp
        Classes/ImGUI/ImGuiLayer.cpp
        )
set(IMGUI_INC
        Classes/ImGUI/CCIMGUI.h
        Classes/ImGUI/imconfig.h
        Classes/ImGUI/imgui_impl_glfw.h
        Classes/ImGUI/imgui_internal.h
        Classes/ImGUI/IMGUIGLViewImpl.h
        Classes/ImGUI/ImGuiLayer.h
        Classes/ImGUI/stb_rect_pack.h
        Classes/ImGUI/stb_textedit.h
        Classes/ImGUI/stb_truetype.h
        )

set(GAME_SRC
        Classes/AppDelegate.cpp
        Classes/MainScene.cpp
        ${IMGUI_SRC}
        ${PLATFORM_SPECIFIC_SRC}
        )

#file(GLOB_RECURSE SOURCES "Classes/*.cpp")
#file(GLOB_RECURSE HEADERS "Classes/*.h" "Classes/*.hpp")
#file(GLOB_RECURSE SOURCES_IMGUI "Classes/ImGUI/*.cpp" "Classes/ImGUI/*.h")


set(GAME_HEADERS
        Classes/AppDelegate.h
        Classes/MainScene.h
        Classes/EditorRoot_generated.h
        ${IMGUI_INC}
        ${PLATFORM_SPECIFIC_HEADERS}
        Classes/ModelLoader.cpp Classes/ModelLoader.h)


# Configure libcocos2d
set(BUILD_CPP_EMPTY_TEST OFF CACHE BOOL "turn off build cpp-empty-test")
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua related targets")
set(BUILD_JS_LIBS OFF CACHE BOOL "turn off build js related targets")

#add_subdirectory(${COCOS2D_ROOT})


# MyGame
if (ANDROID)
    add_library(${APP_NAME} SHARED ${GAME_SRC} ${GAME_HEADERS})
    IF (CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF ()
else ()
    add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
endif ()

target_link_libraries(
        ${APP_NAME}
        ${EXTRA_LIBS}
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libbullet.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcocos2d.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcocos2dInternal.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/librecast.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libtinyxml2.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libunzip.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libxxhash.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libpng.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libz.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreetype.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libjpeg.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libchipmunk.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libtiff.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libwebp.a
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

if (ANDROID)

else ()
    pre_build(${APP_NAME}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
            )

endif ()
message(ndk $ENV{COCOS_X_ROOT})