QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ingame.cpp \
    main.cpp \
    inicio.cpp \
    settings.cpp

HEADERS += \
    ingame.h \
    inicio.h \
    settings.h

FORMS += \
    ingame.ui \
    inicio.ui \
    settings.ui


ASM_FILES += main_asm.asm

asm_cl.output  = main_asm.o
asm_cl.commands = nasm -g -felf64 ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
asm_cl.input = ASM_FILES
asm_cl.variable_out = OBJECTS

# Configuración para enlazar los archivos de objeto
OBJECTS += main_asm.o

QMAKE_EXTRA_COMPILERS += asm_cl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/Credits.qrc \
    images/difficulty.qrc \
    images/gameGode.qrc \
    images/gameUI.qrc \
    images/heart.qrc \
    images/menuBackground.qrc \
    images/nice-heart.qrc \
    images/settingsMenu.qrc \
    scores/classicScores.txt \
    scores/survivalScores.txt

DISTFILES +=

QMAKE_LFLAGS += -no-pie
