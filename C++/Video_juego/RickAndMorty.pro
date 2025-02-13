QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemigos.cpp \
    items.cpp \
    main.cpp \
    mainwindow.cpp \
    morty.cpp \
    nivelesjump.cpp \
    nivelespersecucion.cpp \
    plataformas.cpp \
    proyectil.cpp \
    proyectilparabolico.cpp \
    rick.cpp

HEADERS += \
    enemigos.h \
    items.h \
    mainwindow.h \
    morty.h \
    nivelesjump.h \
    nivelespersecucion.h \
    plataformas.h \
    proyectil.h \
    proyectilparabolico.h \
    rick.h

FORMS += \
    mainwindow.ui \
    nivelesjump.ui \
    nivelespersecucion.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Imagenes.qrc

DISTFILES += \
    Imagenes/71Zk38XCpKSYKeBus (2).jpg \
    Imagenes/Redimiension saltos.jpg \
    Imagenes/priteDiamond (1).png
