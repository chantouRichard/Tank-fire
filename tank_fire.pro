QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SettingWindow.cpp \
    bullet.cpp \
    enemybullet.cpp \
    enemytank.cpp \
    global.cpp \
    historyscorewindow.cpp \
    level.cpp \
    level1.cpp \
    level2.cpp \
    level3.cpp \
    level4.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mygraphicspicitem.cpp \
    passWindow.cpp \
    simplebutton.cpp \
    tank.cpp

HEADERS += \
    SettingWindow.h \
    bullet.h \
    enemybullet.h \
    enemytank.h \
    global.h \
    historyscorewindow.h \
    level.h \
    level1.h \
    level2.h \
    level3.h \
    level4.h \
    loginwindow.h \
    mainwindow.h \
    mygraphicspicitem.h \
    passWindow.h \
    simplebutton.h \
    tank.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

# MATERIAL-SDK
LIBS += -L$$PWD/libs -lcomponents
INCLUDEPATH += $$PWD/libs/Include
