QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../control/controller.cc \
    ../../model/credit_calc.cc \
    ../../model/date.cc \
    ../../model/deposit_calc.cc \
    ../../model/polish.cc \
    deposit_input.cc \
    main.cc \
    mainwindow.cc \
    qcustomplot.cc \
    withdrawals_input.cc

HEADERS += \
    ../../control/controller.h \
    ../../model/credit_calc.h \
    ../../model/date.h \
    ../../model/deposit_calc.h \
    ../../model/polish.h \
    deposit_input.h \
    mainwindow.h \
    qcustomplot.h \
    withdrawals_input.h

FORMS += \
    deposit_input.ui \
    mainwindow.ui \
    withdrawals_input.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
