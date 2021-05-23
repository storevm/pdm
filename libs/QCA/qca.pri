
INCLUDEPATH += $$PWD/include

QCA_WIN32_ROOT = $$PWD/lib/win32
QCA_UNIX_ROOT = $$PWD/lib/unix
QCA_MACX_ROOT = $$PWD/lib/macx

win32:CONFIG(release, debug|release): LIBS += -L$${QCA_WIN32_ROOT} -lqca
else:win32:CONFIG(debug, debug|release): LIBS += -L$${QCA_WIN32_ROOT} -lqca
else:unix:!macx: LIBS += -L$${QCA_UNIX_ROOT} -lqca
else:unix:macx: LIBS += -F$${LOG4QT_MACX_ROOT} -framework qca
