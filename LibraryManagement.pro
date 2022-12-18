QT       += core gui

QT += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/about.cpp \
    src/books/addbook.cpp \
    src/users/adduser.cpp \
    src/calendar.cpp \
    src/books/classificationno.cpp \
    src/dialog_box/criticalmsgbox.cpp \
    src/csvconvertor.cpp \
    src/books/editbook.cpp \
    src/users/edituser.cpp \
    src/transactions/issuebook.cpp \
    src/dialog_box/messagebox.cpp \
    src/mydb.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/print.cpp \
    src/transactions/returnbook.cpp \
    src/books/searchbook.cpp \
    src/transactions/searchissuedbook.cpp \
    src/users/searchuser.cpp

HEADERS += \
    include/about.h \
    include/books/addbook.h \
    include/users/adduser.h \
    include/calendar.h \
    include/books/classificationno.h \
    include/dialog_box/criticalmsgbox.h \
    include/csvconvertor.h \
    include/books/editbook.h \
    include/users/edituser.h \
    include/transactions/issuebook.h \
    include/dialog_box/messagebox.h \
    include/mydb.h \
    include/mainwindow.h \
    include/print.h \
    include/transactions/returnbook.h \
    include/books/searchbook.h \
    include/transactions/searchissuedbook.h \
    include/users/searchuser.h

FORMS += \
    ui/about.ui \
    ui/books/addbook.ui \
    ui/users/adduser.ui \
    ui/books/classificationno.ui \
    ui/dialog_box/criticalmsgbox.ui \
    ui/csvconvertor.ui \
    ui/books/editbook.ui \
    ui/users/edituser.ui \
    ui/transactions/issuebook.ui \
    ui/mainwindow.ui \
    ui/dialog_box/messagebox.ui \
    ui/print.ui \
    ui/transactions/returnbook.ui \
    ui/books/searchbook.ui \
    ui/transactions/searchissuedbook.ui \
    ui/users/searchuser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data/resource.qrc

DISTFILES +=
