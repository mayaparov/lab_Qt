QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



SOURCES += \
    editor.cpp \
    highlight.cpp \
    main.cpp \
    mainwindow.cpp \
    window.cpp

HEADERS += \
    editor.h \
    highlight.h \
    mainwindow.h \
    window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc

