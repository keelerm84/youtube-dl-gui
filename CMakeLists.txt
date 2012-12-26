cmake_minimum_required(VERSION 2.8)
# set project's name
PROJECT( youtube-dl-gui )

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/Modules)
LIST(APPEND CMAKE_MODULE_PATH /usr/local/share/apps/cmake/modules)

# with SET() command you can change variables or define new ones
# here we define DESKTOP_APP_SRCS variable that contains a list of all .cpp files
# note that we don't need \ at the end of line
 SET( DESKTOP_APP_SRCS
 ./lib/downloadproperties.cpp
 ./lib/youtubedl.cpp
 ./lib/youtubetitleretriever.cpp
 ./lib/youtubefiledownloader.cpp
 ./main.cpp
 ./ui/downloaditem.cpp
 ./ui/downloadqueue.cpp
 ./ui/preferences.cpp
 ./ui/youtubedlgui.cpp
 ./util/downloadmanager.cpp
 ./util/settings.cpp
)

# another list, this time it includes all header files that should be treated with moc
SET( DESKTOP_APP_MOC_HDRS
  ./lib/youtubedl.h
  ./lib/youtubetitleretriever.h
  ./lib/youtubefiledownloader.h
  ./ui/downloadqueue.h
  ./ui/preferences.h
  ./ui/youtubedlgui.h
  ./util/downloadmanager.h
)

# some .ui files
SET( DESKTOP_APP_UIS
  ./ui/preferences.ui
  ./ui/youtubedlgui.ui
)

# and finally a resource file
SET( DESKTOP_APP_RCS
  ./res/resources.qrc
)

# enable warnings
ADD_DEFINITIONS( -Wall )

# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
SET( QT_USE_QTNETWORK TRUE )
SET( QT_USE_QTSQL TRUE )

# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
FIND_PACKAGE( Qt4 REQUIRED )

# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
INCLUDE( ${QT_USE_FILE} )

# this command will generate rules that will run rcc on all files from DESKTOP_APP_RCS
# in result DESKTOP_APP_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES( DESKTOP_APP_RC_SRCS ${DESKTOP_APP_RCS} )

# this will run uic on .ui files:
QT4_WRAP_UI( DESKTOP_APP_UI_HDRS ${DESKTOP_APP_UIS} )

# and finally this will run moc:
QT4_WRAP_CPP( DESKTOP_APP_MOC_SRCS ${DESKTOP_APP_MOC_HDRS} )

# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} . )

# here we instruct CMake to build "sample" executable from all of the source files
ADD_EXECUTABLE( youtube-dl-gui ${DESKTOP_APP_SRCS} ${DESKTOP_APP_MOC_SRCS} ${DESKTOP_APP_RC_SRCS} ${DESKTOP_APP_UI_HDRS} )

# last thing we have to do is to tell CMake what libraries our executable needs,
# luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
TARGET_LINK_LIBRARIES( youtube-dl-gui ${QT_LIBRARIES} ${QJSON_LIBRARIES} )
