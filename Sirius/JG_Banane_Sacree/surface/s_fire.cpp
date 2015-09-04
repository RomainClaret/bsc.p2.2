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

#include "../surface/s_fire.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

S_Fire::S_Fire(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent) : S_SurfaceAutoTexture(xpos, ypos, game, parent)
{
    setDesign();
}
/**
 * @details No other choice that use FICTIVE positions x and y. Here set at 0.
 */
S_Fire::S_Fire(G_Gameboard* game, QGraphicsItem *parent) : S_SurfaceAutoTexture(0, 0, game, parent)
{
    setDesign();
}

void S_Fire::setDesign()
{
    texture_init = QPixmap(":/surfaces/surfaces/fire_init_01.png");
    texturesAnim.append(QPixmap(":/surfaces/surfaces/fire_init_02.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/fire_init_03.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/fire_init_04.png"));

    texturesAnim.append(texture_init);

    QBrush brush;
    brush.setTexture(texture_init);
    setBrush(brush);

    setZValue(4);
}

void S_Fire::calculateTextures(int**, int, int)
{
    //rien
}
