cmake_minimum_required(VERSION 3.16)

project(lingmo-videoplayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(GNUInstallDirs)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Core Gui Quick OpenGL DBus Widgets LinguistTools)
find_package(Libmpv REQUIRED)

qt_add_dbus_interface(screensaver_inhibit_SRCS ./org.freedesktop.ScreenSaver.xml screensaverdbusinterface)

set(PROJECT_SOURCES
    src/main.cpp
    src/application.cpp
    src/playlistmodel.cpp
    src/playlistitem.cpp
    src/track.cpp
    src/tracksmodel.cpp
    src/mpvobject.cpp
    src/qthelper.h
    src/lockmanager.cpp
    src/mpris2/mediaplayer2.cpp
    src/mpris2/mediaplayer2player.cpp
    qml.qrc
    ${screensaver_inhibit_SRCS}
)

add_executable(lingmo-videoplayer
    ${PROJECT_SOURCES}
)

target_link_libraries(lingmo-videoplayer
  PRIVATE
  Qt6::Core
  Qt6::Gui
  Qt6::Quick
  Qt6::OpenGL
  Qt6::DBus
  Qt6::Widgets
  Libmpv::Libmpv
)

install(TARGETS lingmo-videoplayer DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    lingmo-videoplayer.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
    COMPONENT Runtime
)

file(GLOB TS_FILES translations/*.ts)
foreach(filepath ${TS_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND ts_files_replaced ${filename})
endforeach()
qt_add_translation(QM_FILES ${ts_files_replaced})
add_custom_target(translations ALL DEPENDS ${QM_FILES} SOURCES ${TS_FILES})

install(FILES ${QM_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/lingmo-videoplayer/translations)
