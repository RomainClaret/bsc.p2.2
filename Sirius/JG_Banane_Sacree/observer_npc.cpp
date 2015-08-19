#include "observer_npc.h"
#include "g_gameboard.h"
#include <QDebug>

#include "state/state_enemypatrol.h"
#include "state/state_enemypause.h"
#include "state/state_enemysleep.h"
/**
 * @details Desactivate the view of the ennemi at the first run and do nothing after
 */

QString Observer_NPC::STATE_PATROL = "patrol";
QString Observer_NPC::STATE_PAUSE = "pause";
QString Observer_NPC::STATE_SLEEP = "sleep";

Observer_NPC::Observer_NPC()
{
}

Observer_NPC::~Observer_NPC()
{
    foreach (C_Enemy* enemy, list_ennemisObserver)
    {
        delete enemy;
    }
}

/**
 * @details addEnnemiObserver add ennemi as observer
 */
void Observer_NPC::addNPCObserver(C_Enemy* ennemi)
{
    this->list_ennemisObserver.append(ennemi);
}

/**
 * @details changeEnnemiState change the state of the ennemis in the LEVEL PHASE
 */
void Observer_NPC::changeNPCState(QString state, QPoint posPlayer)
{
    //find the player's zone
    int gameX = G_Gameboard::getSizeX();
    int gameY = G_Gameboard::getSizeY();

    int phaseX = 1;
    while(posPlayer.x() > phaseX*gameX)
    {
        phaseX++;
    }
    int phaseY = 1;
    while(posPlayer.y() > phaseY*gameY)
    {
        phaseY++;
    }

    //  1,1  2,1  3,1
    //  1,2  2,2  3,2

    //change the state of the enemies in this zone
    foreach (C_Enemy* enemy, list_ennemisObserver)
    {
        QPoint posEnemy = enemy->getNPCPos();

        if((posEnemy.x() < phaseX*gameX && posEnemy.x() > (phaseX-1)*gameX)
                && (posEnemy.y() < phaseY*gameY && posEnemy.y() > (phaseY-1)*gameY))
        {
            qDebug() << "---Change one state in pos " << phaseX << ", " << phaseY << " to "<< state;


            if(state == STATE_PATROL)
            {
                enemy->changeState(new State_EnemyPatrol());
            }
            else if(state == STATE_PAUSE)
            {
                enemy->changeState(new State_EnemyPause());
            }
            else if(state == STATE_SLEEP)
            {
                enemy->changeState(new State_EnemySleep());
            }
        }
    }
}

/**
 * @details changeEnnemiState change the state of all ennemis in the LEVEL
 */
void Observer_NPC::changeNPCState(QString state)
{
    foreach (C_Enemy* enemy, list_ennemisObserver) {
        qDebug() << "---Change one state in the lvl" << " to "<< state;

        if(state == STATE_PATROL)
        {
            enemy->changeState(new State_EnemyPatrol());
        }
        else if(state == STATE_PAUSE)
        {
            enemy->changeState(new State_EnemyPause());
        }
        else if(state == STATE_SLEEP)
        {
            enemy->changeState(new State_EnemySleep());
        }
    }
}

void Observer_NPC::clear()
{
    foreach (C_Enemy* enemy, list_ennemisObserver)
    {
        delete enemy;
    }
    list_ennemisObserver.clear();
}
