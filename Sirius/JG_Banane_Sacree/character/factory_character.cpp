#include "factory_character.h"

#include <QGraphicsScene>

#include "../g_gameboard.h"
#include "../character/c_enemy.h"
#include "../character/e_fox.h"
#include "../character/e_wolf.h"
#include "../character/e_walrus.h"
#include "../character/c_player.h"
#include "../observer_npc.h"
#include "../state/state_enemywalrus.h"

QString Factory_Character::ENEMY_WOLF = "WOLF";
QString Factory_Character::ENEMY_FOX = "FOX";
QString Factory_Character::ENEMY_WALRUS = "WALRUS";

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
    else if(type == ENEMY_WALRUS)
    {
        E_Walrus* walrus = new E_Walrus(path, g);
        observer->addNPCObserver(walrus);
        walrus->addToScene(scene);
        return walrus;
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
