PROJECT(space-game)

cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES(
#   ${CMAKE_SOURCE_DIR}
#   "${CMAKE_SOURCE_DIR}/src"
#   ${CMAKE_CURRENT_SOURCE_DIR}
#   ${CMAKE_CURRENT_BINARY_DIR}
#  "/usr/local/include/OGRE/"
  #"include/OGRE"
  "/usr/include/OGRE/"
  "/usr/include/OIS/"
  #"/home/joachim/Desktop/projects/space-game/ogre/Samples/Common/include"
  #"/home/joachim/Desktop/projects/space-game/ogre/OgreMain/include"

  #"/home/billy/ogre/ogre/Samples/Common/include"
  #"/home/billy/ogre/ogre/OgreMain/include"
  "/usr/include/SDL"
  #"/home/billy/projects/hihi/src"
)

ADD_EXECUTABLE(space-game 
  src/myoverlays.cpp
  src/spielfeldumrandung.cpp
  src/metheor.cpp
  src/game.cpp
  src/main.cpp
  src/movableobject.cpp
  src/movobjchangednotifier.cpp
  src/notifier.cpp
  src/notifyable.cpp
  src/player.cpp
  src/projectile.cpp
  src/spacecontroller.cpp
  src/spaceview.cpp
  src/updatesceneframelistener.cpp
  src/joystick.cpp
)
link_directories("lib/ lib/OGRE/")

TARGET_LINK_LIBRARIES( space-game "-DOGRE_GUI_gtk -DOGRE_THREAD_SUPPORT=2 -pthread -DOGRE_CONFIG_LITTLE_ENDIAN -Iinclude/OGRE -I/usr/include/OIS  -L/usr/lib -lOgreMain -lboost_thread -lOIS -lSDL -lpthread" )
