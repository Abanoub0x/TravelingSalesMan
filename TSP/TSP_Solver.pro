QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TSP_Solver  # This is the name of your project
TEMPLATE = app  # This is a Qt application (not a library)

# Add your source files here
SOURCES += main.cpp \
           mainwindow.cpp \


HEADERS += mainwindow.h \
           city.h


FORMS += mainwindow.ui


