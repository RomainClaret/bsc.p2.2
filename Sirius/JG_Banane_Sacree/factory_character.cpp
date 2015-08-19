#include "factory_character.h"

#include <QGraphicsScene>

#include "g_gameboard.h"
#include "c_enemy.h"
#include "e_fox.h"
#include "e_wolf.h"
#include "c_player.h"
#include "observer_npc.h"

QString Factory_Character::ENEMY_WOLF = "WOLF";
QString Factory_Character::ENEMY_FOX = "FOX";

C_Enemy* Factory_Character::createEnemy(QString type, QList<QPoint> path, G_Gameboard *g, Observer_NPC* observer, QGraphicsScene* scene)
{
    if(type == ENEMY_WOLF)
    {
        E_Wolf* wolf = new E_Wolf(path, g);
        observer->addNPCObserver(wolf);
        wolf->addToScene(scene);
        return wolf;
    }
    else if(type == ENEMY_FOX)
    {
        E_Fox* fox = new E_Fox(path, g);
        observer->addNPCObserver(fox);
        fox->addToScene(scene);
        return fox;
    }
    else
    {
        return NULL;
    }
}

C_Player* Factory_Character::createPlayer(QGraphicsScene* scene)
{
    C_Player* player = new C_Player();
    scene->addItem(player);
    return player;
}
