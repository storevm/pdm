QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += sdk_no_version_check

include($$PWD/libs/Log4qt/Log4qt.pri)
include($$PWD/libs/QCA/qca.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cluster.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/cluster.h \
    src/constants.h \
    src/mainwindow.h

DESTDIR = $$PWD/build

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resources.qrc
