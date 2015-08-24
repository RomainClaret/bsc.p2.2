#include "t_charactermover.h"

#include "p_penguin.h"
#include "g_gameboard.h"

t_CharacterMover::t_CharacterMover(P_Penguin* character, QObject *parent) : QThread(parent)
{
    this->character = character;

    speed = 1000;
    gs = G_Gameboard::getGameSquares();
}

void t_CharacterMover::moveCharacter(char orientation)
{
    lock.lock();
    this->orientation = orientation;
    this->startPos = QPointF(character->pos().x(),character->pos().y());
    this->start();
}
void t_CharacterMover::run()
{
     int i=0;
        switch (orientation) {
        case 'r':

            while(character->pos().x() < startPos.x() + gs)
            {
                i++;
                character->moveByPixel(1,0);
                usleep(speed);
                qDebug() << "move---" << i;
                qDebug() << character->pos();
            }

            break;
        case 'l':
            while(character->pos().x() > startPos.x() - gs)
            {
                character->moveBy(-1,0);
                usleep(speed);
            }

            break;
        case 'b':

            while(character->pos().y() < startPos.y() + gs)
            {
                character->moveBy(0,1);
                usleep(speed);
            }

            break;
        case 't':

            while(character->pos().y() > startPos.y() - gs)
            {
                character->moveBy(0,-1);
                usleep(speed);
            }

            break;
        default:
            break;
        }

        lock.unlock();

    }
