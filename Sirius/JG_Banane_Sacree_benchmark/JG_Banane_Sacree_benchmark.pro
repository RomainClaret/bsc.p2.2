#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T15:02:40
#
#-------------------------------------------------

QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JG_Banane_Sacree_benchmark
TEMPLATE = app


SOURCES += main.cpp\
        t_level.cpp \
    ../JG_Banane_Sacree/b_movable.cpp \
    ../JG_Banane_Sacree/b_wall.cpp \
    ../JG_Banane_Sacree/b_water.cpp \
    ../JG_Banane_Sacree/e_fox.cpp \
    ../JG_Banane_Sacree/e_wolf.cpp \
    ../JG_Banane_Sacree/factory_surface.cpp \
    ../JG_Banane_Sacree/g_character.cpp \
    ../JG_Banane_Sacree/g_gameboard.cpp \
    ../JG_Banane_Sacree/g_level.cpp \
    ../JG_Banane_Sacree/g_maingame.cpp \
    ../JG_Banane_Sacree/g_npc.cpp \
    ../JG_Banane_Sacree/g_object.cpp \
    ../JG_Banane_Sacree/g_player.cpp \
    ../JG_Banane_Sacree/g_profil.cpp \
    ../JG_Banane_Sacree/g_surface.cpp \
    ../JG_Banane_Sacree/observer_npc.cpp \
    ../JG_Banane_Sacree/p_penguin.cpp \
    ../JG_Banane_Sacree/s_dialog.cpp \
    ../JG_Banane_Sacree/s_door.cpp \
    ../JG_Banane_Sacree/s_ice.cpp \
    ../JG_Banane_Sacree/s_snow.cpp \
    ../JG_Banane_Sacree/s_viewblocknpc.cpp \
    ../JG_Banane_Sacree/state_npcpatrol.cpp \
    ../JG_Banane_Sacree/state_npcpause.cpp \
    ../JG_Banane_Sacree/state_npcsleep.cpp \
    ../JG_Banane_Sacree/w_dialog.cpp \
    ../JG_Banane_Sacree/w_life.cpp \
    ../JG_Banane_Sacree/w_menustart.cpp \
    ../JG_Banane_Sacree/w_object.cpp \
    ../JG_Banane_Sacree/w_pause.cpp \
    ../JG_Banane_Sacree_V1/s_snow_v1.cpp \
    ../JG_Banane_Sacree_V1/s_ice_v1.cpp \
    ../JG_Banane_Sacree_V1/p_penguin_v1.cpp \
    ../JG_Banane_Sacree_V1/s_dialog_v1.cpp \
    ../JG_Banane_Sacree_V1/b_movable_v1.cpp \
    ../JG_Banane_Sacree_V1/b_wall_v1.cpp \
    ../JG_Banane_Sacree_V1/b_water_v1.cpp \
    ../JG_Banane_Sacree_V1/w_dialog_v1.cpp \
    ../JG_Banane_Sacree_V1/w_life_v1.cpp \
    ../JG_Banane_Sacree_V1/w_object_v1.cpp \
    ../JG_Banane_Sacree_V1/g_gameboard_v1.cpp \
    ../JG_Banane_Sacree_V1/g_level_v1.cpp \
    ../JG_Banane_Sacree_V1/w_menustart_v1.cpp \
    ../JG_Banane_Sacree_V1/w_menupause_v1.cpp \
    ../JG_Banane_Sacree_V1/g_maingame_v1.cpp \
    ../JG_Banane_Sacree_V1/g_object_v1.cpp \
    ../JG_Banane_Sacree_V1/g_profil_v1.cpp \
    ../JG_Banane_Sacree_V1/s_door_v1.cpp \
    ../JG_Banane_Sacree_V1/g_surface_v1.cpp \
    ../JG_Banane_Sacree_V1/e_fox_v1.cpp \
    ../JG_Banane_Sacree_V1/e_wolf_v1.cpp \
    ../JG_Banane_Sacree_V1/c_enemy_v1.cpp \
    ../JG_Banane_Sacree_V1/c_player_v1.cpp

HEADERS  += t_level.h \
    ../JG_Banane_Sacree/b_movable.h \
    ../JG_Banane_Sacree/b_wall.h \
    ../JG_Banane_Sacree/b_water.h \
    ../JG_Banane_Sacree/c_enemy.h \
    ../JG_Banane_Sacree/c_player.h \
    ../JG_Banane_Sacree/e_fox.h \
    ../JG_Banane_Sacree/e_wolf.h \
    ../JG_Banane_Sacree/factory_surface.h \
    ../JG_Banane_Sacree/g_character.h \
    ../JG_Banane_Sacree/g_gameboard.h \
    ../JG_Banane_Sacree/g_level.h \
    ../JG_Banane_Sacree/g_maingame.h \
    ../JG_Banane_Sacree/g_object.h \
    ../JG_Banane_Sacree/g_profil.h \
    ../JG_Banane_Sacree/g_surface.h \
    ../JG_Banane_Sacree/observer_npc.h \
    ../JG_Banane_Sacree/p_penguin.h \
    ../JG_Banane_Sacree/s_dialog.h \
    ../JG_Banane_Sacree/s_door.h \
    ../JG_Banane_Sacree/s_ice.h \
    ../JG_Banane_Sacree/s_snow.h \
    ../JG_Banane_Sacree/s_viewblocknpc.h \
    ../JG_Banane_Sacree/state_enemy.h \
    ../JG_Banane_Sacree/state_enemypatrol.h \
    ../JG_Banane_Sacree/state_enemypause.h \
    ../JG_Banane_Sacree/state_enemysleep.h \
    ../JG_Banane_Sacree/w_dialog.h \
    ../JG_Banane_Sacree/w_life.h \
    ../JG_Banane_Sacree/w_menupause.h \
    ../JG_Banane_Sacree/w_menustart.h \
    ../JG_Banane_Sacree/w_object.h \
    ../JG_Banane_Sacree_V1/s_door_v1.h \
    ../JG_Banane_Sacree_V1/b_movable_v1.h \
    ../JG_Banane_Sacree_V1/b_wall_v1.h \
    ../JG_Banane_Sacree_V1/b_water_v1.h \
    ../JG_Banane_Sacree_V1/e_fox_v1.h \
    ../JG_Banane_Sacree_V1/e_wolf_v1.h \
    ../JG_Banane_Sacree_V1/g_gameboard_v1.h \
    ../JG_Banane_Sacree_V1/g_level_v1.h \
    ../JG_Banane_Sacree_V1/g_maingame_v1.h \
    ../JG_Banane_Sacree_V1/g_object_v1.h \
    ../JG_Banane_Sacree_V1/g_profil_v1.h \
    ../JG_Banane_Sacree_V1/p_penguin_v1.h \
    ../JG_Banane_Sacree_V1/s_dialog_v1.h \
    ../JG_Banane_Sacree_V1/s_ice_v1.h \
    ../JG_Banane_Sacree_V1/s_snow_v1.h \
    ../JG_Banane_Sacree_V1/g_surface_v1.h \
    ../JG_Banane_Sacree_V1/w_dialog_v1.h \
    ../JG_Banane_Sacree_V1/w_life_v1.h \
    ../JG_Banane_Sacree_V1/w_menupause_v1.h \
    ../JG_Banane_Sacree_V1/w_menustart_v1.h \
    ../JG_Banane_Sacree_V1/w_object_v1.h \
    ../JG_Banane_Sacree_V1/c_enemy_v1.h \
    ../JG_Banane_Sacree_V1/c_player_v1.h
