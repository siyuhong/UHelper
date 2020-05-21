QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 版本信息
VERSION = 1.0.0.0
# 图标
RC_ICONS = "ico/ico_UHelper.ico"
# 产品名称
QMAKE_TARGET_PRODUCT = "UHelper"
# 文件说明
QMAKE_TARGET_DESCRIPTION = "UHelper"
# 版权信息
QMAKE_TARGET_COPYRIGHT = "Apache License 2.0"
# 中文（简体）
RC_LANG = 0x0004

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
    main.cpp \
    mainwindow.cpp \
    mycombobox.cpp \
    ascii_table.cpp

HEADERS += \
    mainwindow.h \
    mycombobox.h \
    ascii_table.h

FORMS += \
    mainwindow.ui \
    ascii_table.ui

TRANSLATIONS += \
    UHelper_zh_CN.ts

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

