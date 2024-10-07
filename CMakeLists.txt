cmake_minimum_required(VERSION 3.29)
project(SMP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        MultimediaWidgets
        REQUIRED)

add_executable(SMP main.cpp
        src/playerwidget.cpp
        src/videoplayer.cpp
        src/videowidget.cpp

        include/playerwidget.h
        include/videoplayer.h
        include/videowidget.h
        include/mainwindow.h
        src/mainwindow.cpp
)
target_link_libraries(SMP
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        Qt::MultimediaWidgets
)

include_directories(${SMP_SOURCE_DIR}/include)