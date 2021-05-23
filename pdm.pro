QT       += core gui sql network

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
    src/consumer.cpp \
    src/cursor.cpp \
    src/function.cpp \
    src/httpclient.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/message.cpp \
    src/namespace.cpp \
    src/producer.cpp \
    src/pulsarmessage.cpp \
    src/qjsonwebtoken.cpp \
    src/qmulticombobox.cpp \
    src/role.cpp \
    src/subscription.cpp \
    src/tenant.cpp \
    src/topic.cpp

HEADERS += \
    src/basefunction.h \
    src/cluster.h \
    src/constants.h \
    src/consumer.h \
    src/cursor.h \
    src/function.h \
    src/functioninstance.h \
    src/httpclient.h \
    src/mainwindow.h \
    src/message.h \
    src/namespace.h \
    src/producer.h \
    src/pulsarmessage.h \
    src/qjsonwebtoken.h \
    src/qmulticombobox.h \
    src/role.h \
    src/subscription.h \
    src/tenant.h \
    src/topic.h

DESTDIR = $$PWD/build

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resources.qrc
