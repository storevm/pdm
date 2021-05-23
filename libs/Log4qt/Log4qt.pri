INCLUDEPATH += $$PWD/include

LOG4QT_WIN32_ROOT = $$PWD/lib/win32
LOG4QT_UNIX_ROOT = $$PWD/lib/unix
LOG4QT_MACX_ROOT = $$PWD/lib/macx

win32:CONFIG(release, debug|release): LIBS += -L$${LOG4QT_WIN32_ROOT} -llog4qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$${LOG4QT_WIN32_ROOT} -llog4qt
else:unix:!macx: LIBS += -L$${LOG4QT_UNIX_ROOT} -llog4qt
else:unix:macx: LIBS += -L$${LOG4QT_MACX_ROOT} -llog4qt
