#*********************************************************************************
# Copyright © Haute-Ecole ARC - All Rights Reserved
# Copyright © Banana Rocket - All Rights Reserved
#
# This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
#
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
# Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
# Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
#**********************************************************************************/

#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T15:48:29
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JG_Banane_Sacree
TEMPLATE = app
macx:ICON = $${PWD}/icons/logo.icns
win32:RC_FILE = winIcon.rc


SOURCES += \
    player.cpp \
    surface.cpp \
    gameboard.cpp \
    main.cpp \
    b_movable.cpp \
    s_snow.cpp \
    s_viewtransition.cpp \
    b_wall.cpp \
    p_penguin.cpp \
    b_water.cpp \
    profil.cpp \
    m_menustart.cpp \
    object.cpp \
    m_pause.cpp \
    s_ice.cpp \
    level.cpp \
    maingame.cpp \
    w_object.cpp \
    e_renard.cpp \
    e_loup.cpp \
    s_dialog.cpp \
    w_dialog.cpp \
    w_life.cpp \
    s_viewblocennemi.cpp \
    observablesennemis.cpp \
    stateennemi_patrol.cpp \
    stateennemi_sleep.cpp \
    stateenemy_pause.cpp \
    surfacefactory.cpp \
    enemy.cpp

HEADERS  += \
    player.h \
    surface.h \
    gameboard.h \
    b_movable.h \
    b_wall.h \
    s_viewtransition.h \
    s_snow.h \
    p_penguin.h \
    b_water.h \
    profil.h \
    m_menustart.h \
    object.h \
    m_pause.h \
    s_ice.h \
    level.h \
    maingame.h \
    w_object.h \
    s_dialog.h \
    w_dialog.h \
    w_life.h \
    stateenemy_pause.h \
    surfacefactory.h \
    enemy.h \
    stateenemy.h \
    stateenemy_patrol.h \
    stateenemy_sleep.h \
    observablesenemy.h \
    e_wolf.h \
    e_fox.h \
    s_viewblockenemy.h

RESOURCES += \
    images.qrc \
    ItemsPopulation.qrc \
    icons.qrc
