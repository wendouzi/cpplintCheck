DEFINES += CPPLINTCHECK_LIBRARY \
            QT_CLUCENE_SUPPORT

QT += network
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += printsupport
    !isEmpty(QT.webkitwidgets.name): QT += webkitwidgets webkit
    else: DEFINES += QT_NO_WEBKIT
} else {
    CONFIG += help
    contains(QT_CONFIG, webkit): QT += webkit
}

include(../../qtcreatorplugin.pri)

INCLUDEPATH += $$PWD

HEADERS += \
    cpplintCheck.h \
    cpplintplugin.h \
    Constants.h

SOURCES += \
    cpplintCheck.cpp \
    cpplintplugin.cpp

FORMS += \

RESOURCES += cpplintCheck.qrc

