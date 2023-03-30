#-------------------------------------------------
#
# Project created by 2nd Year SBME TEAM 1
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintFigure
TEMPLATE = app


SOURCES += main.cpp\
    src\ui\about.cpp \
    src\ui\welcomewindow.cpp \
    src\ui\messagedialog.cpp \
    src\ui\paintwindow.cpp \
    src\shapes\circle.cpp \
    src\shapes\line.cpp \
    src\shapes\rectangle.cpp \
    src\shapes\figure.cpp \
    src\shapes\triangle.cpp \
    src\drawing\painttable.cpp \
    src\drawing\paintscene.cpp \
    src\utils\commands.cpp \
    src\utils\json_utilities.cpp \


HEADERS  += \
    src\ui\about.h \
    src\ui\welcomewindow.h \
    src\ui\messagedialog.h \
    src\ui\paintwindow.h \
    src\shapes\circle.h \
    src\shapes\line.h \
    src\shapes\rectangle.h \
    src\shapes\figure.h \
    src\shapes\triangle.h \
    src\drawing\painttable.h \
    src\drawing\paintscene.h \
    src\utils\commands.h \
    src\utils\json_utilities.h \


FORMS    += \
    src\ui\about.ui \
    src\ui\messagedialog.ui \
    src\ui\paintwindow.ui \
    src\ui\welcomewindow.ui

RESOURCES += \
    resources.qrc

RC_ICONS = icon.ico
