PROJECT(space-game)

cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES(
#   ${CMAKE_SOURCE_DIR}
#   "${CMAKE_SOURCE_DIR}/src"
#   ${CMAKE_CURRENT_SOURCE_DIR}
#   ${CMAKE_CURRENT_BINARY_DIR}
#   "/usr/share/doc/ogre-1.6.3/Samples/Common/include"
#   "/usr/share/doc/ogre-1.6.3/OgreMain/include"
  "/usr/include/OGRE/"
  "/usr/include/OIS/"
  "/home/billy/ogre/ogre/Samples/Common/include"
  "/home/billy/ogre/ogre/OgreMain/include"
  #"/home/billy/projects/hihi/src"
)

ADD_EXECUTABLE(space-game
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
)

TARGET_LINK_LIBRARIES( space-game "-lOIS -lOgreMain" )
