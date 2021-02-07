QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = terminal-finances

TEMPLATE = app

SOURCES += \
    accountslist.cpp \
    filesave.cpp \
    gendoc.cpp \
    initial.cpp \
    main.cpp \
    model.cpp \
    start.cpp \
    terminalfinances.cpp \
    tools.cpp \
    updatefields.cpp \
    views.cpp

HEADERS += \
    accountslist.h \
    filesave.h \
    gendoc.h \
    initial.h \
    model.h \
    start.h \
    terminalfinances.h \
    tools.h \
    updatefields.h \
    views.h

FORMS += \
    terminalfinances.ui \
    updatefields.ui

RESOURCES += assets/images.qrc

TRANSLATIONS += \
    terminalfinances/TerminalFinances_en_US.ts \
    terminalfinances/TerminalFinances_es_ES.ts

CONFIG+=lrelease

shortcut.path = /usr/share/applications
shortcut.files = terminal-finances.desktop

configs.path = /etc/xdg
configs.files = terminalfinances

trans.path = = /etc/xdg/terminalfinances
trans.commands = @mv .qm/* /etc/xdg/terminalfinances

target.path = /usr/local/bin

INSTALLS += target shortcut configs trans

