#include "factory_character.h"

#include <QGraphicsScene>

#include "../g_gameboard.h"

#include "../character/c_player.h"
#include "../character/c_enemy.h"

#include "../character/e_fox.h"
#include "../character/e_wolf.h"
#include "../character/e_walrus.h"
#include "../character/e_otter.h"

#include "../observer_enemy.h"
#include "../state/state_enemywalrus.h"

#include "memento.h"

#include <QDebug>

QString Factory_Character::ENEMY_WOLF = "WOLF";
QString Factory_Character::ENEMY_FOX = "FOX";
QString Factory_Character::ENEMY_WALRUS = "WALRUS";
QString Factory_Character::ENEMY_OTTER = "OTTER";


C_Enemy* Factory_Character::createEnemy(QString type, QString position, QPoint* startPoint, QList<QPoint> path, G_Gameboard *g, Observer_Enemy* observer, QGraphicsScene* scene)
{
    if(type == ENEMY_WOLF)
    {
        E_Wolf* wolf = new E_Wolf(position, path, g);
        observer->addNPCObserver(wolf);
        wolf->addToScene(scene);
        Memento::getInstance()->setPosCharacter(wolf,startPoint);
        return wolf;
    }
    else if(type == ENEMY_FOX)
    {
        E_Fox* fox = new E_Fox(position, path, g);
        observer->addNPCObserver(fox);
        fox->addToScene(scene);
        Memento::getInstance()->setPosCharacter(fox,startPoint);
        return fox;
    }
    else if(type == ENEMY_WALRUS)
    {
        E_Walrus* walrus = new E_Walrus(position, path, g);
        observer->addNPCObserver(walrus);
        walrus->addToScene(scene);
        Memento::getInstance()->setPosCharacter(walrus,startPoint);
        return walrus;
    }
    else if(type == ENEMY_OTTER)
    {
        E_Otter* otter = new E_Otter(position, path, g);
        observer->addNPCObserver(otter);
        otter->addToScene(scene);
        Memento::getInstance()->setPosCharacter(otter,startPoint);
        return otter;
    }
    else
    {
        return NULL;
    }
}


C_Player* Factory_Character::createPlayer(int x, int y, QGraphicsScene* scene, G_Gameboard* game)
{
    P_Penguin* player = new P_Penguin(game);
    player->setPos(x,y);
    scene->addItem(player);
    //Memento::getInstance()->setPosCharacter(player,new QPoint(x,y));
    return player;
}
