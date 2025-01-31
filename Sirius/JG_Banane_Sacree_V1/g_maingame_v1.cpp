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

#include "g_maingame_v1.h"
#include "g_profil_v1.h"

#include <QGraphicsView>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QResizeEvent>
#include <QPushButton>
#include <QFormLayout>



G_MainGame_v1::G_MainGame_v1(QWidget *parent) : QWidget(parent)
{
//    connect(this,SIGNAL(closeEvent()),this,SLOT(Gameboard::exitGame()));

    toggleGameCreated = false;
    toggleFirstStart = true;

    currentLevel = new G_Level_v1(-1, NULL);

    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = theGame->sizeX*G_Gameboard_v1::getGameSquares();
    windowSizeY = theGame->sizeY*G_Gameboard_v1::getGameSquares();

    menuSizeX = 400;
    menuSizeY = 280;

    quitBtnSizeX = menuSizeX-20;
    quitBtnSizeY = 50;

    titleSizeX = 479;
    titleSizeY = 30;

    this->setWindowTitle(windowTitle);
    this->setMinimumSize(windowSizeX,windowSizeY);

    gameScene = new QGraphicsScene(this);
    gameScene = currentLevel->populateScene();

    viewPositionX=0;
    viewPositionY=0;

    gameView = new QGraphicsView(this);

    gameView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setSceneRect(viewPositionX,viewPositionY,theGame->sizeX*G_Gameboard_v1::getGameSquares(),theGame->sizeY*G_Gameboard_v1::getGameSquares());

    //On position la vue
    gameView->setScene(gameScene);

    gameTitle = new QLabel(this);
    gameTitle->setText(tr("James Gouin et la Banane Sacrée"));


    gameTitle->setStyleSheet(
                        "color: #2e2e2e;"
                        "font: bold 29px;"
                        "font-family: Century Gothic;"
                        );

    gameTitle->setGeometry(windowSizeX/2-titleSizeX/2,windowSizeY/2-menuSizeY/2-50,titleSizeX,titleSizeY);

    refreshGameMenu();

    quitGame = new QPushButton(tr("Quitter le jeu"), this);

    quitGame->setStyleSheet( "border-style: none;"
                             "border-radius: 5px;"
                             "padding: 6px;"
                             "margin: 5px;"
                              "font-family: Century Gothic;"
                              "background-color: white;"
                              "color: #2e2e2e;"
                              "font-weight: bold;"
                              "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #f2f2f2);"
);

    QObject::connect(quitGame,SIGNAL(clicked()),this,SLOT(close()));
    quitGame->setGeometry(windowSizeX/2-quitBtnSizeX/2,windowSizeY/2+menuSizeY/2+35,quitBtnSizeX,quitBtnSizeY);
}

G_MainGame_v1::~G_MainGame_v1()
{

}

void G_MainGame_v1::startGame(G_Profil_v1* user)
{
    theGame = new G_Gameboard_v1();
    refreshGameMenu();
    theGame->setParent(this);
    theGame->setPlayerProfil(user);
    theGame->show();
    theGame->setGeometry(this->size().width()/2-windowSizeX/2,this->size().height()/2-windowSizeY/2,windowSizeX,windowSizeY);
    toggleGameCreated = true;
}

void G_MainGame_v1::refreshGameMenu()
{
    if (!toggleFirstStart)
    {
        delete menuStart;
        menuStart = NULL;
    }
    toggleFirstStart = false;
    menuStart = new W_MenuStart_v1(this);
    connect(menuStart,SIGNAL(startGame(G_Profil_v1*)),this, SLOT(startGame(G_Profil_v1*)));
    connect(menuStart,SIGNAL(refreshGameMenu()),this, SLOT(refreshGameMenu()));

    menuStart->setGeometry(this->size().width()/2-menuSizeX/2,this->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
    menuStart->show();
}

void G_MainGame_v1::resizeEvent(QResizeEvent * event) {

    if (event->size().width() >= windowSizeX || event->size().height() >= windowSizeX)
    {
        gameView->resize(event->size().width(),event->size().height());
        menuStart->setGeometry(event->size().width()/2-menuSizeX/2,event->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
        gameTitle->setGeometry(event->size().width()/2-titleSizeX/2,event->size().height()/2-menuSizeY/2-50,titleSizeX,titleSizeY);
        quitGame->setGeometry(event->size().width()/2-quitBtnSizeX/2,event->size().height()/2+menuSizeY/2+35,quitBtnSizeX,quitBtnSizeY);
        menuStart->setGeometry(event->size().width()/2-menuSizeX/2,event->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
        if (toggleGameCreated)
        {
            theGame->setGeometry(event->size().width()/2-windowSizeX/2,event->size().height()/2-windowSizeY/2,windowSizeX,windowSizeY);
        }

    }
}

void G_MainGame_v1::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::warning( this, tr("Quitter de cette manière?"),
                                                                tr("En quittant de ce manière, vous allez perdre votre progression. Si vous souhaitez sauvegarder votre partie, annulez et quittez depuis le menu Escape.\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}
