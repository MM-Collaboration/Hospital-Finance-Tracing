QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connectdatabasedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    statchart.cpp

HEADERS += \
    connectdatabasedialog.h \
    mainwindow.h \
    statchart.h

FORMS += \
    connectdatabasedialog.ui \
    mainwindow.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ui_base/main_window.py \
    ui_base/preview_img/preview_01.png \
    ui_base/preview_img/preview_02.png \
    ui_base/preview_img/preview_03.png \
    ui_base/preview_img/preview_04.png \
    ui_base/preview_img/preview_05.png \
    ui_base/preview_img/preview_06.png \
    ui_base/preview_img/preview_07.png \
    ui_base/preview_img/preview_08.png \
    ui_base/preview_img/preview_09.png

RESOURCES += \
    assets/icons/resources.qrc
