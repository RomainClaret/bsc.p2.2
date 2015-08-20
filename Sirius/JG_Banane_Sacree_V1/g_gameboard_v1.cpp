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

#include "g_gameboard_v1.h"
#include "p_penguin_v1.h"
#include "b_wall_v1.h"
#include "b_movable_v1.h"
#include "b_water_v1.h"
#include "w_menustart_v1.h"
#include "g_object_v1.h"
#include "s_door_v1.h"
#include "s_snow_v1.h"
#include "s_ice_v1.h"
#include "s_dialog_v1.h"
#include "g_level_v1.h"
#include "c_enemy_v1.h"
#include "e_fox_v1.h"
#include "e_wolf_v1.h"
#include "g_profil_v1.h"

#include <QtWidgets>
#include <QList>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QApplication>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QFile>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPoint>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QGraphicsProxyWidget>

#define SLIDE_SPEED (80)

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

int G_Gameboard_v1::gameSquares = 32;
int G_Gameboard_v1::sizeX = 20;
int G_Gameboard_v1::sizeY = 15;

G_Gameboard_v1::G_Gameboard_v1(QWidget *parent) : QWidget(parent)
{
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = sizeX*gameSquares;
    windowSizeY = sizeY*gameSquares;

    setFocus();
    grabKeyboard();
    this->setWindowTitle(windowTitle);
    this->setFixedSize(windowSizeX,windowSizeY);
    this->resize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    playerView = new QGraphicsView(this);
    pingouin = new P_Penguin_v1();
    checkpoint = new QPoint(0,0);
    playerProfil = new G_Profil_v1();
    currentLevel = new G_Level_v1(0, this);

    playerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setProxy();

    isSliding = false;
    moveBloc = NULL;
    endable = false;

    //initialisation des timer
    timerPingouinSlide = new QTimer();
    timerBlocDeplSlide = new QTimer();
    connect(timerPingouinSlide, SIGNAL(timeout()), this, SLOT(SlidePingouin()));
    connect(timerBlocDeplSlide, SIGNAL(timeout()), this, SLOT(SlideBloc()));

    //pour annimer !
    timer = new QTimer();
    setTimer();
    timer->start(100); //10 fois par sec
}

void G_Gameboard_v1::SlideBloc()
{
    for(int i=0; i<listSlindingBlocs.size(); i++)
    {
        B_Movable_v1* SlidingBloc = listSlindingBlocs.at(i).slidingMovable;
        bool removeBloc = true;

        if(SlidingBloc->isSlide())
        {
            switch (listSlindingBlocs.at(i).sens)
            {
            case 't':

                if(SlidingBloc->IsMovableToTop())
                {
                    SlidingBloc->moveBy(0,-1);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'b':

                if(SlidingBloc->IsMovableToBottom())
                {
                    SlidingBloc->moveBy(0,1);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'l':

                if(SlidingBloc->IsMovableToLeft())
                {
                    SlidingBloc->moveBy(-1,0);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'r':

                if(SlidingBloc->IsMovableToRight())
                {
                    SlidingBloc->moveBy(1,0);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

                break;
            }
        }

        if(removeBloc)
        {
            listSlindingBlocs.removeAt(i);
        }
    }

    if(listSlindingBlocs.size() == 0)
    {
        timerBlocDeplSlide->stop();
    }
}

void G_Gameboard_v1::SlidePingouin()
{
    bool endSlide = true;

    switch (cSensPingouinSlide)
    {
    case 't':

        if(MovePingouinToTop() && pingouin->isSlide())
        {
            pingouin->moveBy(0, -1);
            checkPositionEvents();
            checkChangeView(cSensPingouinSlide);

            if(moveBloc != NULL)
            {
                moveBloc->moveBy(0,-1);
                fixeMovable(moveBloc);
                moveBloc = NULL;
            }
             endSlide = false;

        }

        break;

    case 'b':

        if(MovePingouinToBottom() && pingouin->isSlide())
        {
            checkPositionEvents();
            pingouin->moveBy(0, 1);
            checkChangeView(cSensPingouinSlide);

            if(moveBloc != NULL)
            {
                moveBloc->moveBy(0,1);
                fixeMovable(moveBloc);
                moveBloc = NULL;
            }

            endSlide = false;
        }
        break;

    case 'l':

        if(MovePingouinToLeft() && pingouin->isSlide())
        {
            pingouin->moveBy(-1, 0);
            checkPositionEvents();
            checkChangeView(cSensPingouinSlide);

            if(moveBloc != NULL)
            {
                moveBloc->moveBy(-1,0);
                fixeMovable(moveBloc);
                moveBloc = NULL;
            }

           endSlide = false;
        }
        break;

    case 'r':

        if(MovePingouinToRight() && pingouin->isSlide())
        {
           pingouin->moveBy(1, 0);
           checkPositionEvents();
           checkChangeView(cSensPingouinSlide);

           if(moveBloc != NULL)
            {
                moveBloc->moveBy(1,0);
                fixeMovable(moveBloc);
                moveBloc = NULL;
           }

           endSlide = false;
        }
        break;
    default:
        break;
    }

    if(endSlide)
    {
        checkPositionEvents();
        checkChangeView(cSensPingouinSlide);
        timerPingouinSlide->stop();
        isSliding=false;
        moveBloc = NULL;
    }
}

G_Gameboard_v1::~G_Gameboard_v1(){

}


void G_Gameboard_v1::setViewPosition()
{
    int x = viewRequested.x();
    int y = viewRequested.y();

    if(x==1) { viewPositionX = 1; }
    else
    {
        viewPositionX = (x-1)*20*gameSquares;
    }

    if(y==1)
    {
        viewPositionY = 1;
    }
    else
    {
        viewPositionY = (y-1)*15*gameSquares;
    }
}

void G_Gameboard_v1::fixeMovable(B_Movable_v1 *b)
{
    QList<QGraphicsItem *> CollidingItems = b->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        QPoint p = b->getPos();
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water_v1).name())
        {
            qDebug() << "Sink it ! : " << p.x() << " " << p.y();

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            S_Snow_v1 *sunk = new S_Snow_v1(p.x(),p.y());
            sunk->setColor("white");
            mainScene->addItem(sunk);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Door_v1).name())
        {
            QString text = tr("Tu as bloqué ta sortie!");
            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText(text,2);

            dialogToogle = true;

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            B_Wall_v1 *wall = new B_Wall_v1(p.x(),p.y());
            wall->setColor("gray");
            mainScene->addItem(wall);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(G_Object_v1).name())
        {
            mainScene->removeItem(CollidingItems.at(i));

            G_Object_v1 *objet = dynamic_cast<G_Object_v1*>(CollidingItems.at(i));

            if(objet->getName() != "Oeuf")
            {
                restartEnigma();

                QString text = tr("OUCH! Ce bloc vient d'écraser un ");
                text.append(objet->getName());
                text.append(tr("! Tu recommences au dernier checkpoint! "));
                setPositionCenter(dialog);
                dialogProxy->show();
                dialog->setText(text,2);
                dialogToogle = true;
            }
        }
    }
}

void G_Gameboard_v1::checkPositionEvents()
{
    QList<QGraphicsItem *> CollidingItems = pingouin->CollidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(G_Object_v1).name())
        {
            G_Object_v1 *objet = dynamic_cast<G_Object_v1*>(CollidingItems.at(i));
            qDebug() << objet->getName();
            pingouin->addObjectToSacoche(new G_Object_v1(objet->getName()));
            mainScene->removeItem(CollidingItems.at(i));

            if(objet->getName() == "Chaussure")
            {
                pingouin->setSlideAble(false);
            }
            else if(objet->getName() == "Oeuf")
            {
                if(playerProfil->getNbLive()<G_Profil_v1::NBMAXVIE)
                {
                    playerProfil->setNbLive(playerProfil->getNbLive()+1);
                    lifeList->updateHearts(playerProfil->getNbLive());
                }
                else
                {
                    QString text(tr("Le nombre de vies maximum de %1 a été atteint").arg(G_Profil_v1::NBMAXVIE));
                    setPositionCenter(dialog);
                    dialogProxy->show();
                    dialog->setText(text,2);
                    dialogToogle = true;
                }
            }

            objectList->reloadObjectList(pingouin->getSacoche());
            setPositionBottom(objectList);
            objectList->show();
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Dialog_v1).name())
        {
            S_Dialog_v1 *item = dynamic_cast<S_Dialog_v1*>(CollidingItems.at(i));
            mainScene->removeItem(CollidingItems.at(i));

            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText(currentLevel->getDialogText(item->getDialogNumber()),1);
            dialogToogle = true;
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water_v1).name())
        {
            restartEnigma();

            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText("Plouf, dans l'eau! Tu recommences au dernier checkpoint",2);
            dialogToogle = true;
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(E_Fox_v1).name() || typeid(*CollidingItems.at(i)).name() == typeid(E_Wolf_v1).name())
        {
            restartEnigma();

            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText("Tu t'es fait repéré par un ennemi",2);
            dialogToogle = true;
        }
    }
    if(pingouin->x() == currentLevel->getUnlockEndPoint().x() && pingouin->y() == currentLevel->getUnlockEndPoint().y())
    {
        qDebug() << "UNLOCKEND";

        int levelNumber = currentLevel->getLevelNumber();
        QString background = ":/maps/maps/";
        background.append(QString("%1").arg(levelNumber));
        background.append("Ouvert");
        background.append(".png");
        QPixmap pixmapBackground(background);

        if(!pixmapBackground.isNull())
        {
            mainScene->setBackgroundBrush(pixmapBackground);
        }

        endable = true;
    }
}

void G_Gameboard_v1::checkChangeView(char sens)
{
    QList<QGraphicsItem *> CollidingItems = pingouin->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Door_v1).name())
        {
            S_Door_v1 *bloc = dynamic_cast<S_Door_v1*>(CollidingItems.at(i));
            if(bloc->isEndLevel() && endable)
            {
                endable = false;
                pingouin->emptySacoche();
                setLevel(bloc->getNextLevel());
                setProxy();
                setFirstDialog();
            }
            else if(bloc->isEndLevel())
            {
                pingouin->moveBack();
            }
            else
            {
                if(!bloc->isNeedingItem())
                {
                    if(pingouin->checkObjectSacoche(QString("Chaussure")))
                    {
                        pingouin->removeObjectFromSacoche(QString("Chaussure"));
                        pingouin->setSlideAble(true);
                    }

                    ChangeView(sens);
                }
                else if(bloc->isNeedingItem() && pingouin->checkObjectSacoche(bloc->getNeededItem(), bloc->getNbItem()))
                {
                    if(pingouin->checkObjectSacoche(QString("Chaussure")))
                    {
                        pingouin->removeObjectFromSacoche(QString("Chaussure"));
                        pingouin->setSlideAble(true);
                    }

                    ChangeView(sens);
                }
                else
                {
                    QString text = tr("Il te faut ");
                    text.append(QString::number(bloc->getNbItem()));
                    text.append(tr("x l'objet \""));
                    text.append((bloc->getNeededItem()));
                    text.append(tr("\" pour aller plus loin ;) "));

                    setPositionCenter(dialog);
                    dialogProxy->show();
                    dialog->setText(text,2);

                    dialogToogle = true;

                    pingouin->moveBack();
                }
            }
        }
    }
}

void G_Gameboard_v1::ChangeView(char sens)
{
    saveCheckpoint();
    pingouin->emptyTempSacoche();

    qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();

    if(sens == 't')
    {
        qDebug() << "Up";
        this-> checkpoint->setY(checkpoint->y()-gameSquares);
        viewRequested.setY(viewRequested.y()-1);
    }
    if(sens == 'b')
    {
        qDebug() << "Down";
        this->checkpoint->setY(checkpoint->y()+gameSquares);
        viewRequested.setY(viewRequested.y()+1);
    }
    if(sens == 'l')
    {
        qDebug() << "Left";
        this->checkpoint->setX(checkpoint->x()-gameSquares);
        viewRequested.setX(viewRequested.x()-1);
    }
    if(sens == 'r')
    {
        qDebug() << "Right";

        this->checkpoint->setX(checkpoint->x()+gameSquares);
        viewRequested.setX(viewRequested.x()+1);
    }

    qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();
    loadCheckpoint();

    setViewPosition();
    playerView->setSceneRect(viewPositionX,viewPositionY,windowSizeX,windowSizeY);

    objectList->reloadObjectList(pingouin->getSacoche());
    setPositionBottom(objectList);
    setPositionCenter(dialog);
    setPositionTop(lifeList);
}

void G_Gameboard_v1::setPositionBottom(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX+gameSquares*(sizeX)-width,viewPositionY+gameSquares*(sizeY)-height,width,height);
}

void G_Gameboard_v1::setPositionCenter(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX+(gameSquares*(sizeX)-width)/2,viewPositionY+(gameSquares*(sizeY)-height)/2,width,height);
}

void G_Gameboard_v1::setPositionTop(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX,viewPositionY,width,height);
}

void G_Gameboard_v1::MoveBloc(char sens)
{
    switch(sens)
    {
        case 't':
            moveBloc->moveBy(0,-1);
        break;
        case 'b':
            moveBloc->moveBy(0,1);
        break;
        case 'l':
            moveBloc->moveBy(-1,0);
        break;
        case 'r':
            moveBloc->moveBy(1,0);
        break;
    }

    fixeMovable(moveBloc);


    if(moveBloc->isSlide())
    {
        slideBloc sb;
        sb.slidingMovable = moveBloc;
        sb.sens = sens;


        listSlindingBlocs.append(sb);

        timerBlocDeplSlide->start(SLIDE_SPEED);
    }

    moveBloc = NULL;
}

bool G_Gameboard_v1::checkPosition(QGraphicsItem *object)
{
    if(object->y() < (viewRequested.y()-1)*15*gameSquares+1)
    {
        qDebug() << "Déplacement Impossible : " << object->y() << " < " << (viewRequested.y()-1)*15*gameSquares;
        return false;
    }

    if(object->y() > viewRequested.y()*15*gameSquares-gameSquares+1)
    {
        qDebug() << "Déplacement Impossible : " << object->y() << " > " << viewRequested.y()*15*gameSquares-gameSquares;
        return false;
    }

    if(object->x() < (viewRequested.x()-1)*20*gameSquares+1)
    {
        qDebug() << "Déplacement Impossible : " << object->x() << " < " << (viewRequested.x()-1)*20*gameSquares;
        return false;
    }

    if(object->x() > viewRequested.x()*20*gameSquares-gameSquares+1)
    {
        qDebug() << "Déplacement Impossible : " << object->x() << " > " << viewRequested.x()*20*gameSquares-gameSquares;
        return false;
    }

    return true;
}

//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void G_Gameboard_v1::keyPressEvent(QKeyEvent *event)
{
    if(!toggleMenuPause && !isSliding)
    {
        if(!dialogToogle)
        {
            if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
            {
                pingouin->setPlayerOrientation("up"); //definir l'orientation du joueur

                if(MovePingouinToTop())
                {
                    pingouin->moveBy(0, -1);

                    checkPositionEvents();
                    checkChangeView('t');

                    if(moveBloc != NULL)
                    {
                        MoveBloc('t');
                    }
                    if(pingouin->isSlide())
                    {
                        isSliding=true;
                        cSensPingouinSlide = 't';
                        timerPingouinSlide->start(SLIDE_SPEED);
                    }
                }
            }
            if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
            {
                pingouin->setPlayerOrientation("down");

                if(MovePingouinToBottom())
                {
                    pingouin->moveBy(0, 1);

                    checkPositionEvents();
                    checkChangeView('b');
                    if(moveBloc != NULL)
                    {
                        MoveBloc('b');
                    }
                    if(pingouin->isSlide())
                    {
                        isSliding=true;
                        cSensPingouinSlide = 'b';
                        timerPingouinSlide->start(SLIDE_SPEED);
                    }
                }
            }
            if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
            {
                pingouin->setPlayerOrientation("left");

                if(MovePingouinToLeft())
                {
                    pingouin->moveBy(-1, 0);


                        checkPositionEvents();
                        checkChangeView('l');
                        if(moveBloc != NULL)
                        {
                            MoveBloc('l');
                        }
                        if(pingouin->isSlide())
                        {
                            isSliding=true;
                            cSensPingouinSlide = 'l';
                            timerPingouinSlide->start(SLIDE_SPEED);
                        }
                }
            }
            if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
            {
                pingouin->setPlayerOrientation("right");

                if(MovePingouinToRight())
                {
                    pingouin->moveBy(1, 0);


                        checkPositionEvents();
                        checkChangeView('r');
                        if(moveBloc != NULL)
                        {
                            MoveBloc('r');
                        }
                        if(pingouin->isSlide())
                        {
                            isSliding=true;
                            cSensPingouinSlide = 'r';
                            timerPingouinSlide->start(SLIDE_SPEED);
                        }
                }
            }
            if(event->key() == Qt::Key_0)
            {
                restartEnigma();
            }
        }
        else
        {
            if(event->key() == Qt::Key_Space)
            {
                dialogProxy->hide();
                dialogToogle = false;
            }
        }
    }
    if(event->key() == Qt::Key_Escape)
    {
        pauseMenu();
    }
}

bool G_Gameboard_v1::MovePingouinToLeft()
{
    return MovePingouin(pingouin->CollidesLeft(), 'l');
}

bool G_Gameboard_v1::MovePingouinToRight()
{
    return MovePingouin(pingouin->CollidesRight(), 'r');
}

bool G_Gameboard_v1::MovePingouinToTop()
{
    return MovePingouin(pingouin->CollidesTop(), 't');
}

bool G_Gameboard_v1::MovePingouinToBottom()
{
    return MovePingouin(pingouin->CollidesBottom(), 'b');
}

bool G_Gameboard_v1::MovePingouin(QList<QGraphicsItem *> CollidingItems, char sensDepl)
{
    bool bMove = true;
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall_v1).name())
        {
            bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable_v1).name())
        {
            B_Movable_v1 *b;
            b = dynamic_cast<B_Movable_v1*>(CollidingItems.at(i));

            if(sensDepl == 'l' && b->IsMovableToLeft() && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 'r' && b->IsMovableToRight() && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 't' && b->IsMovableToTop() && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 'b' && b->IsMovableToBottom()  && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
                moveBloc = b;
                bMove = true;
            }
            else{
                bMove=false;
            }
        } 
        else if(typeid(*CollidingItems.at(i)).name() == typeid(S_Door_v1).name())
        {
            bMove = true;
        }
    }
    if(bMove && (!checkPosition(pingouin->getCollideBloc(sensDepl))))
    {
        bMove=false;
    }
    return bMove;
}

int G_Gameboard_v1::getGameSquares()
{
    return gameSquares;
}

void G_Gameboard_v1::pauseMenu()
{
    if(!toggleMenuPause)
    {
        timerPingouinSlide->stop();
        menuPauseInGame->setUnableMenu(currentLevel->getLevelNumber());
        setPositionCenter(menuPauseInGame);
        proxy->show();
        toggleMenuPause = true;
    }else{
        proxy->hide();
        toggleMenuPause = false;
        timerPingouinSlide->start(SLIDE_SPEED);
    }
}

void G_Gameboard_v1::resumeGame()
{
    pauseMenu();
}

void G_Gameboard_v1::restartEnigma()
{
    if(playerProfil->getNbLive()>0)
    {
        removeAllItems();
        disconnectTimer();

        playerProfil->setNbLive(playerProfil->getNbLive()-1);
        lifeList->updateHearts(playerProfil->getNbLive());

        loadLevel();
        setProxy();
    }
    else
    {
        playerProfil->setNbLive(4);
        restartLevel();

        setPositionCenter(dialog);
        dialogProxy->show();
        dialog->setText(tr("Tu as perdu toutes tes vies! Tu recommences au début du niveau."),1);
        dialogToogle = true;
    }
}

void G_Gameboard_v1::restartLevel()
{
    removeAllItems();
    disconnectTimer();

    pingouin->emptySacoche();

    setLevel(currentLevel->getLevelNumber());
    setProxy();

    playerProfil->setNbLive(playerProfil->getNbLive()-1);
    lifeList->updateHearts(playerProfil->getNbLive());

    setFirstDialog();
}



void G_Gameboard_v1::returnIsland()
{
    mainScene->removeItem(proxy);
    mainScene->removeItem(objectListProxy);
    mainScene->removeItem(lifeListProxy);
    mainScene->removeItem(dialogProxy);

    pingouin->emptySacoche();

    setLevel(1);
    setProxy();
    setFirstDialog();

    objectListProxy->hide();
    lifeListProxy->hide();
}

void G_Gameboard_v1::exitGame()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Vous êtes sur le point de quitter le jeu"));
    msgBox.setInformativeText(tr("Voulez vous sauvegarder ?"));
    msgBox.addButton(tr("Sauvegarder"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("Annuler"), QMessageBox::RejectRole);
    msgBox.addButton(tr("Ne pas Sauvegarder"), QMessageBox::DestructiveRole);


    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::AcceptRole:
        qDebug() << "Accept";
        W_MenuStart_v1::saveGame(playerProfil);
        close();
        break;
    case QMessageBox::RejectRole:
        qDebug() << "Reject";
        break;
    case QMessageBox::DestructiveRole:
        qDebug() << "Destruct";
        close();
        break;
    default:
        // should never be reached
        break;
    }
}


void G_Gameboard_v1::saveCheckpoint()
{
    checkpoint->setX(pingouin->x());
    checkpoint->setY(pingouin->y());
}

void G_Gameboard_v1::loadCheckpoint()
{
    pingouin->setPos((checkpoint->x()+gameSquares)/gameSquares,(checkpoint->y()+gameSquares)/gameSquares);
    checkPositionEvents();
}

void G_Gameboard_v1::setProxy()
{
    menuPauseInGame = new W_MenuPause_v1(this);
    setPositionCenter(menuPauseInGame);
    proxy = mainScene->addWidget(menuPauseInGame);
    proxy->hide();
    proxy->setZValue(100);
    toggleMenuPause = false;

    objectList = new W_Object_v1(this);
    objectList->reloadObjectList(pingouin->getSacoche());
    setPositionBottom(objectList);
    objectListProxy = mainScene->addWidget(objectList);
    objectListProxy->show();

    lifeList = new W_Life_v1(this);
    lifeList->updateHearts(playerProfil->getNbLive());
    setPositionTop(lifeList);
    lifeListProxy = mainScene->addWidget(lifeList);
    lifeListProxy->show();

    dialog = new W_Dialog_v1(this);
    dialogProxy = mainScene->addWidget(dialog);
    dialogProxy->setZValue(90);
    dialogProxy->hide();
    setPositionCenter(dialog);
    dialogToogle = false;
}

void G_Gameboard_v1::setLevel(int value)
{
    playerProfil->setLevel(value);
    currentLevel = new G_Level_v1(value, this);
    pingouin->setPos(currentLevel->getStartingPoint()->x(),currentLevel->getStartingPoint()->y());
    viewRequested = currentLevel->getViewStart();
    W_MenuStart_v1::saveGame(playerProfil);
    saveCheckpoint();
    loadLevel();
}

void G_Gameboard_v1::loadLevel()
{
    mainScene = currentLevel->populateScene();
    setViewPosition();

    playerView->setScene(mainScene);
    playerView->setSceneRect(viewPositionX,viewPositionY,sizeX*gameSquares,sizeY*gameSquares);

    pingouin->addToScene(mainScene);

    pingouin->removeTempFromSacoche();
    pingouin->setPlayerOrientation("down");
    loadCheckpoint();
    setTimer();
}

void G_Gameboard_v1::setTimer()
{
    QObject::connect(timer, SIGNAL(timeout()), mainScene, SLOT(advance()));
}

void G_Gameboard_v1::disconnectTimer()
{
    QObject::disconnect(timer, SIGNAL(timeout()), mainScene, SLOT(advance()));
}

void G_Gameboard_v1::setPlayerProfil(G_Profil_v1 *playerProfil)
{
    this->playerProfil = playerProfil;
    setLevel(playerProfil->getLevel());
    setProxy();
    setTimer();

    setFirstDialog();
}

void G_Gameboard_v1::setFirstDialog()
{
    setPositionCenter(dialog);
    dialogProxy->show();
    dialog->setText(currentLevel->getDialogText(1),1);
    dialogToogle = true;
}

void G_Gameboard_v1::removeAllItems()
{
    QList<QGraphicsItem*> itemsList = mainScene->items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    while(iter != end)
    {
        QGraphicsItem* item = (*iter);
        mainScene->removeItem(item);
        iter++;
    }
    mainScene->clear();
}
