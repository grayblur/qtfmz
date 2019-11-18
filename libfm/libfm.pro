include($${top_srcdir}/share/qtfm.pri)

QT += widgets concurrent

TARGET = QtFM
VERSION = $${QTFM_MAJOR}.$${QTFM_MINOR}.$${QTFM_PATCH}
TEMPLATE = lib

SOURCES += \
    applicationdialog.cpp \
    customactionsmanager.cpp \
    desktopfile.cpp \
    fileutils.cpp \
    mimeutils.cpp \
    properties.cpp \
    icondlg.cpp \
    mymodel.cpp \
    mymodelitem.cpp \
    propertiesdlg.cpp \
    processdialog.cpp \
    common.cpp \
    completer.cpp \
    sortmodel.cpp \
    iconview.cpp \
    iconlist.cpp \
    fm.cpp \
    bookmarkmodel.cpp \
    dfmqtreeview.cpp \
    dfmqstyleditemdelegate.cpp \
    addcommon.cpp

HEADERS += \
    applicationdialog.h \
    customactionsmanager.h \
    desktopfile.h \
    fileutils.h \
    mimeutils.h \
    properties.h \
    common.h \
    processdialog.h \
    icondlg.h \
    mymodel.h \
    mymodelitem.h \
    propertiesdlg.h \
    iconview.h \
    iconlist.h \
    completer.h \
    sortmodel.h \
    fm.h \
    bookmarkmodel.h \
    dfmqtreeview.h \
    dfmqstyleditemdelegate.h \
    addcommon.h

# qtcopydialog
INCLUDEPATH += qtcopydialog
SOURCES += qtcopydialog/qtcopydialog.cpp \
           qtcopydialog/qtfilecopier.cpp
HEADERS += qtcopydialog/qtcopydialog.h \
           qtcopydialog/qtfilecopier.h
FORMS   += qtcopydialog/qtcopydialog.ui \
           qtcopydialog/qtoverwritedialog.ui \
           qtcopydialog/qtotherdialog.ui

unix:!macx {
    DESTDIR = $${top_builddir}/lib$${LIBSUFFIX}
    OBJECTS_DIR = $${DESTDIR}/.obj_libfm
    MOC_DIR = $${DESTDIR}/.moc_libfm
    RCC_DIR = $${DESTDIR}/.qrc_libfm

    !CONFIG(no_dbus) {
        SOURCES += \
                disks.cpp \
                udisks2.cpp
        HEADERS += \
                disks.h \
                udisks2.h \
                service.h
        QT += dbus
    }
    CONFIG(with_includes): CONFIG += create_prl no_install_prl create_pc

    target.path = $${LIBDIR}
    docs.path = $${DOCDIR}
    docs.files += \
                $${top_srcdir}/LICENSE \
                $${top_srcdir}/README.md \
                $${top_srcdir}/AUTHORS \
                $${top_srcdir}/ChangeLog

    CONFIG(with_includes) {
        target_inc.path = $${PREFIX}/include/lib$${TARGET}
        target_inc.files = $${HEADERS}
        QMAKE_PKGCONFIG_NAME = lib$${TARGET}
        QMAKE_PKGCONFIG_DESCRIPTION = $${TARGET} library
        QMAKE_PKGCONFIG_LIBDIR = $$target.path
        QMAKE_PKGCONFIG_INCDIR = $$target_inc.path
        QMAKE_PKGCONFIG_DESTDIR = pkgconfig
    }

    INSTALLS += docs
    !CONFIG(staticlib): INSTALLS += target
    CONFIG(with_includes): INSTALLS += target_inc
}

CONFIG(with_magick): include($${top_srcdir}/share/imagemagick.pri)
CONFIG(with_ffmpeg): include($${top_srcdir}/share/ffmpeg.pri)

#unix: LIBS += -L$$PWD/libs/ -lfmapiv100
#unix: LIBS += -L/home/zbzle/Downloads/gitspace/build-qtfm-Desktop_Qt_5_8_0_GCC_64bit-Debug/bin/libs/ -lfmapiv100
#unix: LIBS += -L/home/zbzle/Downloads/gitspace/build-qtfm-Desktop_Qt_5_8_0_GCC_64bit-Debug/bin/libs/ -lS2JAPI
#unix: LIBS += -L/home/zbzle/Downloads/gitspace/build-qtfm-Desktop_Qt_5_8_0_GCC_64bit-Debug/bin/libs/ -lSFLAPI

#unix:LIBS += -L$${top_builddir}/lib$${LIBSUFFIX} -lSFLAPI
unix: LIBS += -L$$PWD/../lib -lSFLAPI
#unix: LIBS += /root/gitspace/qtfm/lib/libSFLAPI.so

#DEPENDPATH += $${top_builddir}/lib$${LIBSUFFIX}
INCLUDEPATH += ../includes
