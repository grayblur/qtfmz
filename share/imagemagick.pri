DEFINES += WITH_MAGICK
CONFIG(oldmagick): DEFINES += OLDMAGICK
MAGICK_CONFIG = Magick++
!isEmpty(MAGICK_PC): MAGICK_CONFIG = $${MAGICK}
PKGCONFIG += $${MAGICK_CONFIG}
CONFIG(deploy): LIBS += `pkg-config --libs --static $${MAGICK_CONFIG}`