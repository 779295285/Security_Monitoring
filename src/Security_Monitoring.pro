#-------------------------------------------------
#
# Project created by QtCreator 2021-06-06T17:05:29
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Security_Monitoring
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        view/loginwidget.cpp \
        model/usermodel.cpp \
        model/singeldb.cpp \
        controller/usercontrol.cpp \
        view/registerwidget.cpp \
        ffmpeg/encodetoh264.cpp \
    view/beginwidget.cpp \
    view/myitem.cpp \
    view/setwidget.cpp \
    view/main_monitorwidget.cpp \
    model/setmodel.cpp \
    controller/setcontrol.cpp \
    view/main_widget.cpp \
    view/main_replaywidget.cpp \
    ffmpeg/decode.cpp \
    model/videomodel.cpp \
    controller/videocontrol.cpp \
    controller/imagecontrol.cpp \
    model/imagemodel.cpp \
    view/play_widget.cpp \
    ffmpeg/decode_replay.cpp \
    ffmpeg/ftrancetomp4.cpp \
    view/image_widegt.cpp


HEADERS += \
        view/loginwidget.h \
        model/usermodel.h \
        model/singeldb.h \
        controller/usercontrol.h \
        view/registerwidget.h \
        ffmpeg/encodetoh264.h \
    view/beginwidget.h \
    view/myitem.h \
    view/setwidget.h \
    view/main_monitorwidget.h \
    view/main_widget.h \
    model/setmodel.h \
    controller/setcontrol.h \
    view/main_replaywidget.h \
    ffmpeg/decode.h \
    model/videomodel.h \
    controller/videocontrol.h \
    controller/imagecontrol.h \
    model/imagemodel.h \
    view/play_widget.h \
    ffmpeg/decode_replay.h \
    ffmpeg/ftrancetomp4.h \
    view/image_widegt.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS=$$PWD/lib/sqlite3.lib
DESTDIR+=bin

INCLUDEPATH += $$PWD/ffmpeglib/include
LIBS += $$PWD/ffmpeglib/lib/avcodec.lib  \
        $$PWD/ffmpeglib/lib/avdevice.lib  \
        $$PWD/ffmpeglib/lib/avfilter.lib  \
        $$PWD/ffmpeglib/lib/avformat.lib  \
        $$PWD/ffmpeglib/lib/avutil.lib  \
        $$PWD/ffmpeglib/lib/swresample.lib  \
        $$PWD/ffmpeglib/lib/swscale.lib

RESOURCES += \
    image.qrc










