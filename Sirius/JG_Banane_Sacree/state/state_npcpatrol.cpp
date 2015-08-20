#include "state_enemypatrol.h"
#include "character/c_enemy.h"

State_EnemyPatrol::State_EnemyPatrol() : State_Enemy()
{
}

/**
 * @details Calculate the direction and move the ennemi with his view. Take care that "StateEnnemi_Patrol" is a Friend of "Ennemi"
 */
void State_EnemyPatrol::step(C_Enemy* ennemi)
{
    //En supprimant ces deux appels on optimise grandement le programme
    //viewBlocActif(); //désactive les blocs obstrués par un mur
    //pinguinDetection(); //test la détection du pingouin

    if(ennemi->time % ennemi->speed == 0 && !ennemi->detectPlayableCharacter)
    {
        ennemi->time = 0;
        QPoint posEnnemi = ennemi->convertPosPoint(ennemi->pos());

        //1 on trouve son orientation
        char direction = ennemi->orientation;
        if(ennemi->path.at(ennemi->iDestPoint).x() > posEnnemi.x())
        {
            direction = 'r'; // la direction voulu avant de marcher
        }
        else if(ennemi->path.at(ennemi->iDestPoint).x() < posEnnemi.x())
        {
            direction = 'l';
        }
        else if(ennemi->path.at(ennemi->iDestPoint).y() > posEnnemi.y())
        {
            direction = 'b';
        }
        else if(ennemi->path.at(ennemi->iDestPoint).y() < posEnnemi.y())
        {
            direction = 't';
        }

        if(direction != ennemi->orientation) //l'orientation n'est pas bonne
        {
            //le point est a ma gauche ou a ma droite ?
               if(ennemi->orientation == 't')
               {
                   if(ennemi->path.at(ennemi->iDestPoint).x() > posEnnemi.x())
                   {
                       //tourne a droite
                       ennemi->setOrientation_right();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).x() < posEnnemi.x())
                   {
                       //tourne a gauche
                       ennemi->setOrientation_left();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).y() > posEnnemi.y())
                   {
                       //on se retourne ( toujours par la droite )
                       ennemi->setOrientation_right();
                   }
               }
               else if(ennemi->orientation=='b')
               {
                   if(ennemi->path.at(ennemi->iDestPoint).x() > posEnnemi.x())
                   {
                       //tourne a SA gauche
                       ennemi->setOrientation_right();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).x() < posEnnemi.x())
                   {
                       //tourne a SA droite
                       ennemi->setOrientation_left();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).y() < posEnnemi.y())
                   {
                       //on se retourne ( toujours par SA droite )
                       ennemi->setOrientation_left();
                   }
               }
               else if(ennemi->orientation=='r')
               {
                   if(ennemi->path.at(ennemi->iDestPoint).x() < posEnnemi.x())
                   {
                       //on se retourne ( toujours par SA droite )
                       ennemi->setOrientation_bottom();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).y() < posEnnemi.y())
                   {
                       //tourne a SA gauche
                       ennemi->setOrientation_top();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).y() > posEnnemi.y())
                   {
                       //tourne a SA droite
                       ennemi->setOrientation_bottom();
                   }
               }
               else if(ennemi->orientation=='l')
               {
                   if(ennemi->path.at(ennemi->iDestPoint).x() > posEnnemi.x())
                   {
                       //on se retourne ( toujours par SA droite )
                       ennemi->setOrientation_top();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).y() < posEnnemi.y())
                   {
                       //tourne a SA droite
                       ennemi->setOrientation_top();
                   }
                   else if(ennemi->path.at(ennemi->iDestPoint).y() > posEnnemi.y())
                   {
                       //tourne a SA droite
                       ennemi->setOrientation_bottom();
                   }
               }
        }
        else
        {
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
        }

        ennemi->viewBlockActive(); //désactive les blocs obstrués par un mur
        ennemi->playableCharacterDetection(); //test la détection du pingouin

    }
    ennemi->time ++;
}
