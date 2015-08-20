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

#include "g_level_v1.h"
#include "g_gameboard_v1.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>

#include "b_wall_v1.h"
#include "b_water_v1.h"
#include "b_movable_v1.h"
#include "s_snow_v1.h"
#include "s_ice_v1.h"
#include "s_door_v1.h"
#include "s_dialog_v1.h"
#include "g_object_v1.h"

#include "e_wolf_v1.h"
#include "e_fox_v1.h"

#include <QPoint>
#include <QDebug>
#include <QList>

G_Level_v1::G_Level_v1(int levelNumber, G_Gameboard_v1 *game)
{
    this->game = game;
    this->levelNumber = levelNumber;

    maxBlocksHeight = 2*G_Gameboard_v1::sizeY;
    maxBlocksWidth = 3*G_Gameboard_v1::sizeX;

    startingPoint = new QPoint(0,0);
    viewStart = new QPoint(0,0);
    unlockEnd = new QPoint(0,0);

    dialogValue = 0;

    getSceneSize();
}

QPoint* G_Level_v1::getStartingPoint()
{
    return this->startingPoint;
}

QGraphicsScene* G_Level_v1::populateScene()
{
    QGraphicsScene* scene = new QGraphicsScene();

    getSceneSize();
    getSceneDialog();

    int Mat_Walls_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Movable_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Items[maxBlocksWidth][maxBlocksHeight];
    int Mat_Bonus[maxBlocksWidth][maxBlocksHeight];
    int Mat_Enemies[maxBlocksWidth][maxBlocksHeight];
    int Mat_Scene_End[maxBlocksWidth][maxBlocksHeight];
    int Mat_Doors[maxBlocksWidth][maxBlocksHeight];
    int Mat_Water_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Snow_Surface[maxBlocksWidth][maxBlocksHeight];
    int Mat_Ice_Surface[maxBlocksWidth][maxBlocksHeight];
    int Mat_Item_Shoes[maxBlocksWidth][maxBlocksHeight];
    int Mat_Dialog[maxBlocksWidth][maxBlocksHeight];

    for (int matY = 0; matY < maxBlocksHeight; matY++)
    {
        for (int matX = 0; matX < maxBlocksWidth; matX++)
        {
            Mat_Walls_Blocks[matX][matY] = 0;
            Mat_Movable_Blocks[matX][matY] = 0;
            Mat_Items[matX][matY] = 0;
            Mat_Bonus[matX][matY] = 0;
            Mat_Doors[matX][matY] = 0;
            Mat_Water_Blocks[matX][matY] = 0;
            Mat_Snow_Surface[matX][matY] = 0;
            Mat_Ice_Surface[matX][matY] = 0;
            Mat_Item_Shoes[matX][matY] = 0;
            Mat_Enemies[matX][matY] = 0;
            Mat_Scene_End[matX][matY] = 0;
            Mat_Dialog[matX][matY] = 0;

        }
    }

    QString background = ":/maps/maps/";
    background.append(QString("%1").arg(levelNumber));
    background.append(".png");
    QPixmap pixmapBackground(background);
    scene->setBackgroundBrush(pixmapBackground);

    QString map = ":/maps/maps/";
    map.append(QString("%1").arg(levelNumber));
    map.append(".txt");

    QFile f(map);

    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&f);
        t.setCodec("UTF-8");
        QString line[1000];
        QString s;
        int line_count=0;

        int matX, matY;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();

            if(line[line_count].contains("[ennemi]"))
            {
                line_count++;
                line[line_count] = t.readLine();
                QStringList listEnnemi = line[line_count].split("//");

                for(int j = 0; j < listEnnemi.size(); j++)
                {
                    QStringList listPoint = listEnnemi.at(j).split(",");
                    QList<QPoint> listeDePoints;
                    for(int i = 0; i < listPoint.size(); i++)
                    {
                        QStringList point = listPoint.at(i).split("-");
                        listeDePoints.append(QPoint(point.at(0).toInt(),point.at(1).toInt()));
                    }
                    ennemi.append(listeDePoints);
                }
            }

            if(line[line_count].contains("type=Walls_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Solid_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Movable_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Movable_Blocks[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Items"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Items[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Bonus"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Bonus[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Enemies"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Enemies[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Scene_End"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Scene_End[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Doors"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Doors[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Water_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Water_Blocks[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=NoMoves_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }


            if(line[line_count].contains("type=Snow_Surface"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Snow_Surface[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Ice_Surface"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Ice_Surface[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Item_Shoes"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Item_Shoes[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Dialogs"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Dialog[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
        }
        f.resize(0);
        t << s;
        f.close();
    }
    else
    {
        qDebug() << "Fichier non ouvert";
    }

    int k = 0;
    // Populate scene
    for (int i = 0; i < maxBlocksWidth; i++)
    {
        for (int j = 0; j < maxBlocksHeight; j++)
        {
            if (Mat_Walls_Blocks[i][j] != 0)
            {
                B_Wall_v1 *item = new B_Wall_v1();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Movable_Blocks[i][j] != 0)
            {
                B_Movable_v1 *item = new B_Movable_v1(i,j);
                item->addToScene(scene);
            }
            if (Mat_Items[i][j] != 0)
            {
                G_Object_v1 *item = new G_Object_v1(QString("Poisson"));
                item->setPos(i, j);
                scene->addItem(item);
            }
            if (Mat_Bonus[i][j] != 0)
            {
                G_Object_v1 *item = new G_Object_v1("Oeuf");
                item->setPos(i, j);
                scene->addItem(item);
            }
            if(Mat_Item_Shoes[i][j] != 0)
            {
                G_Object_v1 *item = new G_Object_v1("Chaussure");
                item->setPos(i, j);
                scene->addItem(item);
            }
            if (Mat_Enemies[i][j] != 0)
            {
                switch(Mat_Enemies[i][j])
                {
                case 1: {
                    E_Fox_v1 *item2 = new E_Fox_v1(ennemi.at(k), game);
                    item2->addToScene(scene);
                    break;
                }
                case 2: {
                    E_Wolf_v1 *item2 = new E_Wolf_v1(ennemi.at(k), game);
                    item2->addToScene(scene);
                    break;
                    }
                default:break;
                }

                k++;
            }
            if (Mat_Scene_End[i][j] != 0)
            {
                S_Door_v1 *item = new S_Door_v1();
                item->setLevelEnd(true);
                item->setPos(i, j);

                item->setNextLevel(Mat_Scene_End[i][j]);

                scene->addItem(item);
            }
            if (Mat_Doors[i][j] != 0)
            {
                S_Door_v1 *item = new S_Door_v1();
                item->setPos(i,j);
                item->setLevelEnd(false);

                if(Mat_Doors[i][j] > 20 && Mat_Doors[i][j] < 30)
                {
                    item->setNbItem(Mat_Doors[i][j]%20);
                    item->setNeededItem("Poisson");
                }

                scene->addItem(item);
            }
            if (Mat_Water_Blocks[i][j] != 0)
            {
                B_Water_v1 *item = new B_Water_v1();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Snow_Surface[i][j] != 0)
            {
                S_Snow_v1 *item = new S_Snow_v1();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Ice_Surface[i][j] != 0)
            {
                S_Ice_v1 *item = new S_Ice_v1();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Dialog[i][j] != 0)
            {
                S_Dialog_v1 *item = new S_Dialog_v1();
                item->setPos(i,j);
                item->setDialogNumber(Mat_Dialog[i][j]);
                scene->addItem(item);
            }
        }
    }
    return scene;
}


void G_Level_v1::getSceneSize()
{
    QString map = ":/maps/maps/";
    map.append(QString("%1").arg(levelNumber));
    map.append("header.txt");

    QFile f(map);

    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&f);
        QString line[1000];
        int line_count=0;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();
            if(line[line_count].contains("[header]"))
            {
                line_count++;
                line[line_count] = t.readLine();
                QStringList valueWidth = line[line_count].split("=");
                maxBlocksWidth = valueWidth.at(1).toInt();

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueHeight = line[line_count].split("=");
                maxBlocksHeight = valueHeight.at(1).toInt();

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueViewX = line[line_count].split("=");
                viewStart->setX(valueViewX.at(1).toInt());

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueViewY = line[line_count].split("=");
                viewStart->setY(valueViewY.at(1).toInt());

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueStartX = line[line_count].split("=");
                startingPoint->setX(valueStartX.at(1).toInt());

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueStartY = line[line_count].split("=");
                startingPoint->setY(valueStartY.at(1).toInt());

                line_count++;
                line[line_count] = t.readLine();
                QStringList unlockEndX = line[line_count].split("=");
                unlockEnd->setX(unlockEndX.at(1).toInt()*G_Gameboard_v1::getGameSquares());

                line_count++;
                line[line_count] = t.readLine();
                QStringList unlockEndY = line[line_count].split("=");
                unlockEnd->setY(unlockEndY.at(1).toInt()*G_Gameboard_v1::getGameSquares());
            }
        }
    }
    f.close();
 }

void G_Level_v1::getSceneDialog()
{
    QString map = ":/maps/maps/";
    map.append(QString("%1").arg(levelNumber));
    map.append("texte.txt");

    QFile f(map);

    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&f);
        t.setCodec("UTF-8");
        QString line[1000];
        int line_count=0;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();
            dialogList.append(line[line_count]);
        }
    }
    f.close();
 }

QPoint G_Level_v1::getViewStart()
{
    return *(this->viewStart);
}

QPoint G_Level_v1::getUnlockEndPoint()
{
    return *(this->unlockEnd);
}

int G_Level_v1::getLevelNumber()
{
    return this->levelNumber;
}

QString G_Level_v1::getDialogText(int value)
{
    if(value<=dialogList.size())
    {
        return dialogList.at(value-1);
    }
    else
    {
        qDebug() << "ERREUR - PAS DE TEXTE POUR CE DIALOG : " << dialogValue;
        return "";
    }
}
