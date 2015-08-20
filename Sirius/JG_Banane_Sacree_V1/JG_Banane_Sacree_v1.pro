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

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JG_Banane_Sacree
TEMPLATE = app
macx:ICON = $${PWD}/icons/logo.icns
win32:RC_FILE = winIcon.rc


SOURCES += \
    c_player_v1.cpp \
    g_surface_v1.cpp \
    g_gameboard_v1.cpp \
    main.cpp \
    b_movable_v1.cpp \
    s_snow_v1.cpp \
    s_door_v1.cpp \
    b_wall_v1.cpp \
    p_penguin_v1.cpp \
    b_water_v1.cpp \
    g_profil_v1.cpp \
    w_menustart_v1.cpp \
    g_object_v1.cpp \
    w_menupause_v1.cpp \
    c_enemy_v1.cpp \
    s_ice_v1.cpp \
    g_level_v1.cpp \
    g_maingame_v1.cpp \
    w_object_v1.cpp \
    e_fox_v1.cpp \
    e_wolf_v1.cpp \
    s_dialog_v1.cpp \
    w_dialog_v1.cpp \
    w_life_v1.cpp

HEADERS  += \
    c_player_v1.h \
    g_surface_v1.h \
    g_gameboard_v1.h \
    b_movable_v1.h \
    s_door_v1.h \
    b_wall_v1.h \
    s_snow_v1.h \
    p_penguin_v1.h \
    b_water_v1.h \
    g_profil_v1.h \
    w_menustart_v1.h \
    g_object_v1.h \
    w_menupause_v1.h \
    c_enemy_v1.h \
    s_ice_v1.h \
    g_level_v1.h \
    g_maingame_v1.h \
    w_object_v1.h \
    e_fox_v1.h \
    e_wolf_v1.h \
    s_dialog_v1.h \
    w_dialog_v1.h \
    w_life_v1.h
RESOURCES += \
    images_v1.qrc \
    ItemsPopulation_v1.qrc \
    icons_v1.qrc
