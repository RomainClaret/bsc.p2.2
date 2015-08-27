/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#ifndef C_PLAYER_H
#define C_PLAYER_H
#include "../character/g_character.h"
#include <QGraphicsItem>
class QPainter;
class QRectF;
class G_Gameboard;

/**
 * @brief Playable characters.
 * @details Contains the skin, orientation, and position.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */

class C_Player : public G_Character
{

public:
    C_Player(G_Gameboard* game);

    void setPlayerOrientation(char orientation);
    char getPlayerOrientation();
    QPoint *getPos();
    QPoint getPosOnGame();

    void moveByPixel(int x, int y) = 0;
    void stepMoveCharacter() = 0;
protected:
    int xPos;
    int yPos;
    G_Gameboard *game;

private:
    //Les skins sont les images attribué au personnage


};

#endif // C_PLAYER_H
