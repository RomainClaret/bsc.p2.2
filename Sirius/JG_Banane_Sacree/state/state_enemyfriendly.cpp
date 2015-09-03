#include "state_enemyfriendly.h"
#include "character/c_enemy.h"

State_EnemyFriendly::State_EnemyFriendly() : State_Enemy()
{
}

/**
 * @details Calculate the direction and move the ennemi with his view. Take care that "StateEnnemi_Patrol" is a Friend of "Ennemi"
 */
void State_EnemyFriendly::step(C_Enemy* ennemi)
{
    if(ennemi->time % ennemi->speed == 0 && !ennemi->detectPlayableCharacter)
    {
        ennemi->time = 0;
        QPoint posEnnemi = ennemi->convertPosPoint(ennemi->pos());

            //toujours déplacement en x en premier puis en y
            if(ennemi->path.at(ennemi->iDestPoint).x() > posEnnemi.x())
            {
                if(!ennemi->collide())
                {
                    ennemi->moveBy(1,0);
                }
                else //inversion du sens de la ronde
                {
                    ennemi->direction = !ennemi->direction;
                    ennemi->iDestPoint = ennemi->nextPoint();
                }
            }
            else if(ennemi->path.at(ennemi->iDestPoint).x() < posEnnemi.x())
            {
                if(!ennemi->collide())
                {
                    ennemi->moveBy(-1,0);
                }
                else
                {
                    ennemi->direction = !ennemi->direction;
                    ennemi->iDestPoint = ennemi->nextPoint();
                }
            }
            else if(ennemi->path.at(ennemi->iDestPoint).y() > posEnnemi.y())
            {
                if(!ennemi->collide())
                {
                    ennemi->moveBy(0,1);
                }
                else
                {
                    ennemi->direction = !ennemi->direction;
                    ennemi->iDestPoint = ennemi->nextPoint();
                }
            }
            else if(ennemi->path.at(ennemi->iDestPoint).y() < posEnnemi.y())
            {
                if(!ennemi->collide())
                {
                    ennemi->moveBy(0,-1);
                }
                else
                {
                    ennemi->direction = !ennemi->direction;
                    ennemi->iDestPoint = ennemi->nextPoint();
                }
            }
            else //on est arrivé sur le point de destination
            {
                ennemi->iDestPoint = ennemi->nextPoint();
            }

        ennemi->playableCharacterDetection(); //test la détection du pingouin
        ennemi->action();
    }
    ennemi->time++;
    ennemi->checkPenguin();
}
