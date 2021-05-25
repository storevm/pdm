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
    src/message.cpp \
    src/namespace.cpp \
    src/producer.cpp \
    src/pulsarmessage.cpp \
    src/qjsonwebtoken.cpp \
    src/qmulticombobox.cpp \
    src/role.cpp \
    src/services/baseservice.cpp \
    src/services/clusterservice.cpp \
    src/services/namespaceservice.cpp \
    src/services/tenantservice.cpp \
    src/sink.cpp \
    src/source.cpp \
    src/subscription.cpp \
    src/table.cpp \
    src/tenant.cpp \
    src/topic.cpp \
    src/widgets/mainwindow.cpp \
    src/widgets/newclusterwindow.cpp

HEADERS += \
    src/basefunction.h \
    src/cluster.h \
    src/constants.h \
    src/consumer.h \
    src/cursor.h \
    src/function.h \
    src/functioninstance.h \
    src/httpclient.h \
    src/message.h \
    src/namespace.h \
    src/producer.h \
    src/pulsarmessage.h \
    src/qjsonwebtoken.h \
    src/qmulticombobox.h \
    src/role.h \
    src/services/baseservice.h \
    src/services/clusterservice.h \
    src/services/namespaceservice.h \
    src/services/tenantservice.h \
    src/sink.h \
    src/source.h \
    src/subscription.h \
    src/table.h \
    src/tenant.h \
    src/topic.h \
    src/widgets/mainwindow.h \
    src/widgets/newclusterwindow.h

DESTDIR = $$PWD/build

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resources.qrc

unix:macx { # OSX
    TARGET = "PDM"
    ICON = $$PWD/src/icons/logo.icns
}
