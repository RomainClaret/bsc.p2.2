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

QT       += core gui xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JG_Banane_Sacrees
TEMPLATE = app
macx:ICON = $${PWD}/icons/logo.icns
win32:RC_FILE = winIcon.rc

SOURCES += \
    main.cpp \
    g_npc.cpp \
    g_gameboard.cpp \
    g_level.cpp \
    g_maingame.cpp \
    g_object.cpp \
    observer_npc.cpp \
    g_player.cpp \
    g_profil.cpp \
    menu/w_menu.cpp \
    menu/w_menubonus.cpp \
    menu/w_menupause.cpp \
    menu/w_menustart.cpp \
    menu/w_menucode.cpp \
    surface/b_movable.cpp \
    surface/b_wall.cpp \
    surface/b_water.cpp \
    surface/g_surface.cpp \
    surface/s_dialog.cpp \
    surface/s_door.cpp \
    surface/s_ice.cpp \
    surface/s_snow.cpp \
    surface/s_viewblocknpc.cpp \
    surface/factory_surface.cpp \
    character/e_fox.cpp \
    character/e_wolf.cpp \
    character/factory_character.cpp \
    character/p_penguin.cpp \
    state/state_npcpatrol.cpp \
    state/state_npcpause.cpp \
    state/state_npcsleep.cpp \
    widget/w_life.cpp \
    widget/w_object.cpp \
    menu/w_menucode_lineedit.cpp \
    menu/w_menucredits.cpp \
    tools/verticalscrollarea.cpp \
    character/g_character.cpp \
    character/t_charactermover.cpp \
    character/t_charactertimermover.cpp \
    widget/dialog/w_dialog.cpp \
    widget/dialog/w_dialog_image.cpp \
    widget/dialog/w_dialog_text.cpp \
    widget/dialog/w_dialog_container.cpp \
    surface/b_movable_simple.cpp \
    surface/b_movable_throw.cpp \
    character/e_walrus.cpp \
    state/state_enemywalrus.cpp \
    t_movesurface.cpp \
    character/c_ai.cpp \
    surface/s_fire.cpp

HEADERS  += \
    g_gameboard.h \
    g_level.h \
    g_maingame.h \
    g_object.h \
    g_profil.h \
    observer_npc.h \
    menu/w_menu.h \
    menu/w_menubonus.h \
    menu/w_menupause.h \
    menu/w_menustart.h \
    menu/w_menucode.h \
    surface/b_movable.h \
    surface/b_wall.h \
    surface/b_water.h \
    surface/g_surface.h \
    surface/s_door.h \
    surface/s_ice.h \
    surface/s_snow.h \
    surface/s_viewblocknpc.h \
    surface/factory_surface.h \
    character/c_enemy.h \
    character/c_player.h \
    character/e_fox.h \
    character/e_wolf.h \
    character/factory_character.h \
    character/p_penguin.h \
    state/state_enemy.h \
    state/state_enemypatrol.h \
    state/state_enemypause.h \
    state/state_enemysleep.h \
    widget/w_dialog.h \
    widget/w_life.h \
    widget/w_object.h \
    menu/w_menucode_lineedit.h \
    menu/w_menucredits.h \
    tools/verticalscrollarea.h \
    character/g_character.h \
    character/t_charactermover.h \
    character/t_charactertimermover.h \
    widget/dialog/w_dialog.h \
    widget/dialog/w_dialog_image.h \
    widget/dialog/w_dialog_text.h \
    widget/dialog/w_dialog_container.h \
    surface/b_movable_simple.h \
    surface/b_movable_throw.h \
    character/e_walrus.h \
    state/state_enemywalrus.h \
    t_movesurface.h \
   character/c_ai.h \
    surface/s_fire.h

RESOURCES += \
    images.qrc \
    ItemsPopulation.qrc \
    icons.qrc \
    music.qrc
