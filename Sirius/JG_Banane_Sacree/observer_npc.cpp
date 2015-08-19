#include "observer_npc.h"
#include "g_gameboard.h"

/**
 * @details Desactivate the view of the ennemi at the first run and do nothing after
 */
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
void Observer_NPC::changeNPCState(State_Enemy* state, QPoint posPlayer)
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
            enemy->changeState(state);
        }
    }
}

/**
 * @details changeEnnemiState change the state of all ennemis in the LEVEL
 */
void Observer_NPC::changeNPCState(State_Enemy* state)
{
    foreach (C_Enemy* enemy, list_ennemisObserver) {
        enemy->changeState(state);
    }
}
