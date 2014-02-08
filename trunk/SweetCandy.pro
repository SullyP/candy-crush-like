# Add more folders to ship with the application, here
folder_01.source = qml/SweetCandy
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    bonbon.cpp \
    niveau.cpp \
    case.cpp \
    vue.cpp \
    controleur.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/SweetCandy/main.qml \
    qml/SweetCandy/case.qml

HEADERS += \
    bonbon.h \
    niveau.h \
    case.h \
    vue.h \
    controleur.h

RESOURCES += \
    ressources.qrc
