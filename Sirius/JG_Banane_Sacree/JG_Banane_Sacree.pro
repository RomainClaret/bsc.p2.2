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
    main.cpp \
    b_movable.cpp \
    s_snow.cpp \
    b_wall.cpp \
    b_water.cpp \
    s_ice.cpp \
    w_object.cpp \
    s_dialog.cpp \
    w_dialog.cpp \
    w_life.cpp \
    g_npc.cpp \
    g_gameboard.cpp \
    g_level.cpp \
    g_maingame.cpp \
    g_object.cpp \
    observer_npc.cpp \
    g_player.cpp \
    g_profil.cpp \
    s_viewblocknpc.cpp \
    s_door.cpp \
    state_npcpause.cpp \
    state_npcpatrol.cpp \
    state_npcsleep.cpp \
    factory_surface.cpp \
    g_surface.cpp \
    e_fox.cpp \
    e_wolf.cpp \
    g_character.cpp \
    factory_character.cpp \
    p_penguin.cpp \
    menu/w_menu.cpp \
    menu/w_menubonus.cpp \
    menu/w_menupause.cpp \
    menu/w_menustart.cpp \
    menu/w_menucode.cpp
HEADERS  += \
    b_movable.h \
    b_wall.h \
    s_snow.h \
    b_water.h \
    s_ice.h \
    w_object.h \
    s_dialog.h \
    w_dialog.h \
    w_life.h \
    s_door.h \
    s_viewblocknpc.h \
    factory_surface.h \
    g_gameboard.h \
    g_level.h \
    g_maingame.h \
    g_object.h \
    g_profil.h \
    g_surface.h \
    observer_npc.h \
    e_fox.h \
    e_wolf.h \
    p_penguin.h \
    c_enemy.h \
    c_player.h \
    state_enemy.h \
    state_enemypatrol.h \
    state_enemypause.h \
    g_character.h \
    state_enemysleep.h \
factory_character.h \     menu/w_menu.h \
    menu/w_menubonus.h \
    menu/w_menupause.h \
    menu/w_menustart.h \
    menu/w_menucode.h
RESOURCES += \
    images.qrc \
    ItemsPopulation.qrc \
    icons.qrc
