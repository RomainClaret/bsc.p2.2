#include "b_wall_alone.h"
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QHash>
#include <QList>

B_Wall_Alone::B_Wall_Alone(int xpos, int ypos, QGraphicsItem *parent) : B_Wall(xpos, ypos, parent)
{
    setDesign();
}

/**
 * @details No other choice that use FICTIVE positions x and y. Here set at 0.
 */
B_Wall_Alone::B_Wall_Alone(QGraphicsItem *parent) : B_Wall(parent)
{
    setDesign();
}

void B_Wall_Alone::setDesign()
{
    QBrush brush;
    //brush.setStyle(Qt::SolidPattern);
    QHash<QString, int> hashRatioTexture;

    hashRatioTexture[":/surfaces/surfaces/wall_rock02.png"] = 3;
    hashRatioTexture[":/surfaces/surfaces/wall_rock03.png"] = 1;
    hashRatioTexture[":/surfaces/surfaces/wall_rock04.png"] = 7;

    int total = 0;
    foreach (int val, hashRatioTexture.values())
    {
        total += val;
    }

    int iRand = rand() % total;

    int i = 0;
    QString pixRand;
    QHashIterator<QString, int> it(hashRatioTexture);
    while (it.hasNext()) {
        it.next();

        if(i <= iRand)
        {
            pixRand = it.key();
        }
        i+=it.value();
    }

    brush.setTexture(QPixmap(pixRand));
    //brush.setColor(Qt::gray);

    setBrush(brush);

    setZValue(4);
}

void B_Wall_Alone::calculateTextures(int** mapSurfaces, int width, int height)
{
    //rien
}
