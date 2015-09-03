#include "observer_enemy.h"
#include "g_gameboard.h"
#include <QDebug>

#include "state/state_enemypatrol.h"
#include "state/state_enemypause.h"
#include "state/state_enemysleep.h"
#include "state/state_enemywalrus.h"

#include "character/e_walrus.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

/**
 * @details Desactivate the view of the ennemi at the first run and do nothing after
 */

QString Observer_Enemy::STATE_PATROL = "patrol";
QString Observer_Enemy::STATE_PAUSE = "pause";
QString Observer_Enemy::STATE_SLEEP = "sleep";

Observer_Enemy::Observer_Enemy()
{
}

Observer_Enemy::~Observer_Enemy()
{
//    foreach (C_Enemy* enemy, list_ennemisObserver)
//    {
//        delete enemy;
//    }
}

/**
 * @details addEnnemiObserver add ennemi as observer
 */
void Observer_Enemy::addNPCObserver(C_Enemy* ennemi)
{
    this->list_ennemisObserver.append(ennemi);
    hash_enemyPreviousState[ennemi] = ennemi->getEnemyState();
}

void Observer_Enemy::removeNPCObserver(C_Enemy* ennemi)
{
    this->list_ennemisObserver.removeOne(ennemi);
    this->hash_enemyPreviousState.remove(ennemi);
}

/**
 * @details changeEnnemiState change the state of the ennemis in the LEVEL PHASE
 */
void Observer_Enemy::changeNPCState(QString state, QPoint phase)
{
    //find the player's zone
    int phaseX = phase.x();
    int phaseY = phase.y();

    int gameX = G_Gameboard::getSizeX();
    int gameY = G_Gameboard::getSizeY();

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

            State_Enemy* oldState;
            if(state == STATE_PATROL)
            {
                 oldState = enemy->changeState(new State_EnemyPatrol());
                 delete oldState;
            }
            else if(state == STATE_PAUSE)
            {
                oldState = enemy->changeState(new State_EnemyPause());
                delete oldState;
            }
            else if(state == STATE_SLEEP)
            {
                oldState = enemy->changeState(new State_EnemySleep());
                delete oldState;
            }
        }
    }
}

/**
 * @details changeEnnemiState change the state of all ennemis in the LEVEL
 */
void Observer_Enemy::changeNPCState(QString state)
{
    foreach (C_Enemy* enemy, list_ennemisObserver) {
        qDebug() << "---Change one state in the lvl" << " to "<< state;

        State_Enemy* oldState;
        if(state == STATE_PATROL)
        {
            oldState = enemy->changeState(new State_EnemyPatrol());
            delete oldState;
        }
        else if(state == STATE_PAUSE)
        {
            oldState = enemy->changeState(new State_EnemyPause());
            delete oldState;
        }
        else if(state == STATE_SLEEP)
        {
            oldState = enemy->changeState(new State_EnemySleep());
            delete oldState;
        }
    }
}

void Observer_Enemy::switchToState(QString state, QPoint phase)
{
    int phaseX = phase.x();
    int phaseY = phase.y();

    int gameX = G_Gameboard::getSizeX();
    int gameY = G_Gameboard::getSizeY();

     qDebug() << "phaseX" << phaseX;
     qDebug() << "phaseY" << phaseY;

    //  1,1  2,1  3,1
    //  1,2  2,2  3,2
    //change the state of the enemies in this zone
    foreach (C_Enemy* enemy, list_ennemisObserver)
    {
        QPoint posEnemy = enemy->getNPCPos();

        if((posEnemy.x() < phaseX*gameX && posEnemy.x() > (phaseX-1)*gameX)
                && (posEnemy.y() < phaseY*gameY && posEnemy.y() > (phaseY-1)*gameY))
        {
            qDebug() << "---Save one state and change it in pos " << phaseX << ", " << phaseY << " to "<< state;

            //save the state
            hash_enemyPreviousState[enemy] = enemy->getEnemyState();

            //change to a new
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

void Observer_Enemy::switchAllToPause()
{
    foreach (C_Enemy* enemy, list_ennemisObserver)
    {
         qDebug() << "---Save one state and change it to Pause (ALL)";

         State_Enemy* OldState = hash_enemyPreviousState[enemy];

         hash_enemyPreviousState[enemy] = enemy->getEnemyState();
         enemy->changeState(new State_EnemySleep());

         if(OldState != NULL && hash_enemyPreviousState[enemy]  != OldState){
             delete OldState;
         }
    }
}

void Observer_Enemy::switchBackToState(QPoint phase)
{
    int phaseX = phase.x();
    int phaseY = phase.y();

    int gameX = G_Gameboard::getSizeX();
    int gameY = G_Gameboard::getSizeY();

    QHashIterator<C_Enemy*, State_Enemy*> it(hash_enemyPreviousState);
    while (it.hasNext())
    {
        it.next();
        QPoint posEnemy = it.key()->getNPCPos();
        if((posEnemy.x() < phaseX*gameX && posEnemy.x() > (phaseX-1)*gameX)
                && (posEnemy.y() < phaseY*gameY && posEnemy.y() > (phaseY-1)*gameY))
        {
            qDebug() << "---Switch back to a saved state " << phaseX << ", " << phaseY;

            State_Enemy* state = it.key()->changeState(it.value());

            if(state != it.value())
            {
                delete state;
            }
        }
    }
}


void Observer_Enemy::clear()
{
//    foreach (C_Enemy* enemy, list_ennemisObserver)
//    {
//        try {
//            delete enemy;
//        }
//        catch(...)
//        {
//            // DO NOTHING
//        }
//    }
    list_ennemisObserver.clear();

    QList<State_Enemy*> listStates = hash_enemyPreviousState.values();
    foreach (State_Enemy* state, listStates)
    {
        delete state;
    }

    hash_enemyPreviousState.clear();
}

void Observer_Enemy::setSpecialTexture(bool value)
{
    foreach (C_Enemy* enemy, list_ennemisObserver)
    {
        enemy->setSpecialTexture(value);
    }
}
