# PanXML - a tool to create XML files for DOI registration of publications in the catalog DataCite of the German National Library of Science and Technology
# Rainer Sieger
# Alfred Wegener Institute, Bremerhaven, Germany
# last change: 2014-10-04

macx {
    # creating cache file
    cache()

    # Set SDK
    QMAKE_MAC_SDK = macosx10.11

    # Only Intel binaries are accepted so force this
    CONFIG += x86_64

    # Minimum OS X version for submission is 10.6.6
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6

    # Icon has been downloaded from http://www.large-icons.com/stock-icons/free-social-media-icons.htm
    ICON = ./Resources/icon/Application.icns

    # Replace default Info.plist
    QMAKE_INFO_PLIST = ./Resources/Info.plist

    QMAKE_CFLAGS += -gdwarf-2
    QMAKE_CXXFLAGS += -gdwarf-2
    QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_OBJECTIVE_CFLAGS_RELEASE =  $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
}

win32 {
    # Icon
    RC_FILE = ./Resources/Application.rc
}

linux-g++ {
}

TARGET = PanXML
TEMPLATE = app

QT += widgets network

INCLUDEPATH += ./Headers

HEADERS = ./Headers/Application.h \
    ./Headers/Globals.h \
    ./Headers/Webfile.h \
    ./Forms/AboutDialog/AboutDialog.h \
    ./Forms/CreateSingleDoiXmlDialog/CreateSingleDoiXmlDialog.h \
#   ./Forms/CreateSimpleEPicXmlDialog/CreateSimpleEPicXmlDialog.h \
    ./Forms/SetOptionsDialog/SetOptionsDialog.h

SOURCES = ./Sources/ApplicationInit.cpp \
    ./Sources/ApplicationMainWindow.cpp \
    ./Sources/ApplicationErrors.cpp \
    ./Sources/ApplicationPreferences.cpp \
    ./Sources/ApplicationCreateMenu.cpp \
    ./Sources/BuildXmlEntry.cpp \
    ./Sources/CreateAmdXml.cpp \
    ./Sources/CreateDoiXml.cpp \
#   ./Sources/CreateEPicXml.cpp \
    ./Sources/Webfile.cpp \
    ./Forms/AboutDialog/AboutDialog.cpp \
    ./Forms/CreateSingleDoiXmlDialog/CreateSingleDoiXmlDialog.cpp \
#   ./Forms/CreateSimpleEPicXmlDialog/CreateSimpleEPicXmlDialog.cpp \
    ./Forms/SetOptionsDialog/SetOptionsDialog.cpp

FORMS = ./Forms/AboutDialog/aboutdialog.ui \
    ./Forms/CreateSingleDoiXmlDialog/createsingledoixmldialog.ui \
#   ./Forms/CreateSimpleEPicXmlDialog/createsimpleepicxmldialog.ui \
    ./Forms/SetOptionsDialog/setoptionsdialog.ui
