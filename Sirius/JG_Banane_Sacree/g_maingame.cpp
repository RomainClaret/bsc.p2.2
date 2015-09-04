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

#include "g_maingame.h"
#include "g_profil.h"
#include "observer_enemy.h"
#include "singleton_audio.h"
#include <time.h>

#include <QGraphicsView>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QResizeEvent>
#include <QPushButton>
#include <QFormLayout>
#include <QGLWidget>
#include <QtCore>
#include <QTimer>
#include <QList>
#include <QString>


G_MainGame::G_MainGame(QWidget *parent) : QWidget(parent)
{
    audioSingleton = Singleton_Audio::getInstance();
    audioSingleton->playMusicPlaylistMenu(-2);

    toggleGameCreated = false;
    toggleFirstStart = true;

    theGame = NULL;

    currentLevel = new G_Level(-1, new Observer_Enemy(), NULL);

    // Default variables from the game
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = theGame->sizeX*G_Gameboard::getGameSquares();
    windowSizeY = theGame->sizeY*G_Gameboard::getGameSquares();

    menuSizeX = 400;
    menuSizeY = 280;

    quitBtnSizeX = menuSizeX-20;
    quitBtnSizeY = 50;

    titleSizeX = 479;
    titleSizeY = 30;

    this->setWindowTitle(windowTitle);
    this->setMinimumSize(windowSizeX,windowSizeY);

    gameScene = currentLevel->populateScene();
    gameScene->setParent(this);

    viewPositionX=0;
    viewPositionY=0;

    gameView = new QGraphicsView(this);
    gameView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setSceneRect(viewPositionX,viewPositionY,theGame->sizeX*G_Gameboard::getGameSquares(),theGame->sizeY*G_Gameboard::getGameSquares());

    timerSplash = new QTimer();
    connect(timerSplash, SIGNAL(timeout()), this, SLOT(splashScreenShow()));
    timerSplash->start(3000); //3 secondes

    QGraphicsScene *sceneSplash = new QGraphicsScene(this);
    QList<QString> *splashList = new QList<QString>();
    splashList->append(":/splashs/splashs/00Gouin.png");
    splashList->append(":/splashs/splashs/darthGouin.jpg");
    splashList->append(":/splashs/splashs/frozenGouin.JPG");
    splashList->append(":/splashs/splashs/mexicanGouin.png");
    splashList->append(":/splashs/splashs/nerdGouin.png");
    splashList->append(":/splashs/splashs/ninjaGouin.JPG");
    splashList->append(":/splashs/splashs/peaceAndGouin.JPG");
    splashList->append(":/splashs/splashs/spaceGouin.png");

    srand(time(NULL));
    int splashNumber = rand() % splashList->size();

    sceneSplash->addPixmap(QPixmap(splashList->at(splashNumber)));
    gameView->setScene(sceneSplash);



    //Set the view position
    //gameView->setViewport(new QGLWidget);
    //gameView->setScene(gameScene);


//    gameView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//    gameView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));


    gameTitle = new QLabel(this);
    gameTitle->setText(tr("James Gouin et la Banane Sacrée"));

    gameTitle->setStyleSheet(
                        "color: #2e2e2e;"
                        "font: bold 29px;"
                        "font-family: Century Gothic;"
                        );

    gameTitle->setGeometry(windowSizeX/2-titleSizeX/2,windowSizeY/2-menuSizeY/2-50,titleSizeX,titleSizeY);
    gameTitle->hide();
    refreshGameMenu();
    menuStart->hide();

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
    quitGame->hide();
    btnSoundMuter = new QPushButton(this);
    btnSoundMuter->setStyleSheet("background: transparent;");
    QPixmap pixmap(":/icons/audio_on60x60.png");
    QIcon ButtonIcon(pixmap);
    btnSoundMuter->setIcon(ButtonIcon);
    btnSoundMuter->setIconSize(pixmap.rect().size());
    btnSoundMuter->hide();

    connect(btnSoundMuter, SIGNAL (released()), this, SLOT (soundMuter()));
}

void G_MainGame::splashScreenShow()
{
    timerSplash->stop();
    gameView->setScene(gameScene);
    gameTitle->show();
    quitGame->show();
    btnSoundMuter->show();
    menuStart->show();
}

G_MainGame::~G_MainGame()
{

}

void G_MainGame::startGame(G_Profil* user)
{
    audioSingleton->pauseMusicPlaylistMenu();
    theGame = new G_Gameboard();
    connect(theGame,SIGNAL(refreshMenu()),this,SLOT(refreshGameMenu()));
    refreshGameMenu();
    theGame->setParent(this);
    theGame->setPlayerProfil(user);
    audioSingleton->setMusicsVolume(user->getMusicsVolume());
    audioSingleton->setSoundsVolume(user->getSoundsVolume());
    theGame->show();
    theGame->setGeometry(this->size().width()/2-windowSizeX/2,this->size().height()/2-windowSizeY/2,windowSizeX,windowSizeY);
    toggleGameCreated = true;

    //OPEN GL
//    w = new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering));
//    gameView->setViewport(w);
//    gameView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
//    gameView->update();
//    w->updateGL();
}


void G_MainGame::refreshGameMenu()
{
    if (!toggleFirstStart)
    {
        delete menuStart;
        menuStart = NULL;
    }
    toggleFirstStart = false;
    menuStart = new W_MenuStart(this);
    connect(menuStart,SIGNAL(startGame(G_Profil*)),this, SLOT(startGame(G_Profil*)));
    connect(menuStart,SIGNAL(refreshGameMenu()),this, SLOT(refreshGameMenu()));

    menuStart->setGeometry(this->size().width()/2-menuSizeX/2,this->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
    menuStart->show();
}

void G_MainGame::soundMuter()
{

    if(audioSingleton->getUsableMusicsPlaylistMenu())
    {
        QPixmap pixmapOff(":/icons/audio_off60x60.png");
        QIcon ButtonIconOff(pixmapOff);
        btnSoundMuter->setIcon(ButtonIconOff);
        audioSingleton->setUsableMusicPlaylistMenu(false);
        audioSingleton->pauseMusicPlaylistMenu();
    }
    else
    {
        QPixmap pixmapOn(":/icons/audio_on60x60.png");
        QIcon ButtonIconOn(pixmapOn);
        btnSoundMuter->setIcon(ButtonIconOn);
        audioSingleton->setUsableMusicPlaylistMenu(true);
        audioSingleton->playMusicPlaylistMenu();
    }

}

void G_MainGame::resizeEvent(QResizeEvent * event) {

    if (event->size().width() >= windowSizeX || event->size().height() >= windowSizeX)
    {
        gameView->resize(event->size().width(),event->size().height());
        menuStart->setGeometry(event->size().width()/2-menuSizeX/2,event->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
        gameTitle->setGeometry(event->size().width()/2-titleSizeX/2,event->size().height()/2-menuSizeY/2-50,titleSizeX,titleSizeY);
        quitGame->setGeometry(event->size().width()/2-quitBtnSizeX/2,event->size().height()/2+menuSizeY/2+35,quitBtnSizeX,quitBtnSizeY);
        menuStart->setGeometry(event->size().width()/2-menuSizeX/2,event->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
        btnSoundMuter->setGeometry(event->size().width()/2+menuSizeX/2+40,event->size().height()/2+menuSizeY/2+30,60,60);
        if (toggleGameCreated)
        {
            theGame->setGeometry(event->size().width()/2-windowSizeX/2,event->size().height()/2-windowSizeY/2,windowSizeX,windowSizeY);
        }
    }
}

void G_MainGame::closeEvent (QCloseEvent *event)
{
    if(theGame != NULL)
    {
        event->ignore();
        theGame->exitGame();
    }
    else
    {
        event->accept();
    }
}

void G_MainGame::exitGame()
{
    theGame = NULL;
}
