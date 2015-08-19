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

#include "g_gameboard.h"
#include "p_penguin.h"
#include "b_wall.h"
#include "b_movable.h"
#include "b_water.h"
#include "w_menustart.h"
#include "g_object.h"
#include "s_door.h"
#include "S_ViewBlockNPC.h"
#include "s_snow.h"
#include "s_ice.h"
#include "s_dialog.h"
#include "g_level.h"
#include "c_enemy.h"
#include "e_fox.h"
#include "e_wolf.h"
#include "g_profil.h"

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

int G_Gameboard::gameSquares = 32;
int G_Gameboard::sizeX = 20;
int G_Gameboard::sizeY = 15;

G_Gameboard::G_Gameboard(QWidget *parent) : QWidget(parent)
{
    // Default variables of the game
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
    playableCharacter = new P_Penguin();
    checkpoint = new QPoint(0,0);
    playerProfil = new G_Profil();

    observerEnemy = new Observer_NPC();
    currentLevel = new G_Level(0, observerEnemy, this);

    playerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setProxy();

    isSliding = false;
    movable = NULL;
    endable = false;

    //initializion of timers
    timerPlayableCharacterSlide = new QTimer();
    timerBlockDisplacementSlide = new QTimer();
    connect(timerPlayableCharacterSlide, SIGNAL(timeout()), this, SLOT(slidePlayableCharacter()));
    connect(timerBlockDisplacementSlide, SIGNAL(timeout()), this, SLOT(slideBlock()));

    //for the animation
    timer = new QTimer();
    setTimer();
    timer->start(100); //10 fois par sec
}

void G_Gameboard::slideBlock()
{
    for(int i=0; i<listSlindingBlocks.size(); i++)
    {
        B_Movable* MovingBlock = listSlindingBlocks.at(i).slidingMovable;
        bool removeBloc = true;

        if(MovingBlock->isSlide())
        {
            switch (listSlindingBlocks.at(i).direction)
            {
            case 't':

                if(MovingBlock->isMovableToTop())
                {
                    MovingBlock->moveBy(0,-1);
                    fixMovable(MovingBlock);
//                    if(checkPosition(MovingBlock))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'b':

                if(MovingBlock->isMovableToBottom())
                {
                    MovingBlock->moveBy(0,1);
                    fixMovable(MovingBlock);
//                    if(checkPosition(MovingBlock))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'l':

                if(MovingBlock->isMovableToLeft())
                {
                    MovingBlock->moveBy(-1,0);
                    fixMovable(MovingBlock);
//                    if(checkPosition(MovingBlock))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'r':

                if(MovingBlock->isMovableToRight())
                {
                    MovingBlock->moveBy(1,0);
                    fixMovable(MovingBlock);
//                    if(checkPosition(MovingBlock))
//                    {
                        removeBloc = false;
//                    }
                }

                break;
            }
        }

        if(removeBloc)
        {
            listSlindingBlocks.removeAt(i);
        }
    }

    if(listSlindingBlocks.size() == 0)
    {
        timerBlockDisplacementSlide->stop();
    }
}

void G_Gameboard::slidePlayableCharacter()
{
    bool endSlide = true;

    switch (directionPlayableCharacter)
    {
    case 't':

        if(movePlayableCharacterPingouinToTop() && playableCharacter->isSlide())
        {
            playableCharacter->moveBy(0, -1);
            checkPositionEvents();
            checkChangeView(directionPlayableCharacter);

            if(movable != NULL)
            {
                movable->moveBy(0,-1);
                fixMovable(movable);
                movable = NULL;
            }
             endSlide = false;

        }

        break;

    case 'b':

        if(movePlayableCharacterToBottom() && playableCharacter->isSlide())
        {
            checkPositionEvents();
            playableCharacter->moveBy(0, 1);
            checkChangeView(directionPlayableCharacter);

            if(movable != NULL)
            {
                movable->moveBy(0,1);
                fixMovable(movable);
                movable = NULL;
            }

            endSlide = false;
        }
        break;

    case 'l':

        if(movePlayableCharacterPingouinToLeft() && playableCharacter->isSlide())
        {
            playableCharacter->moveBy(-1, 0);
            checkPositionEvents();
            checkChangeView(directionPlayableCharacter);

            if(movable != NULL)
            {
                movable->moveBy(-1,0);
                fixMovable(movable);
                movable = NULL;
            }

           endSlide = false;
        }
        break;

    case 'r':

        if(movePlayableCharacterPingouinToRight() && playableCharacter->isSlide())
        {
           playableCharacter->moveBy(1, 0);
           checkPositionEvents();
           checkChangeView(directionPlayableCharacter);

           if(movable != NULL)
            {
                movable->moveBy(1,0);
                fixMovable(movable);
                movable = NULL;
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
        checkChangeView(directionPlayableCharacter);
        timerPlayableCharacterSlide->stop();
        isSliding=false;
        movable = NULL;
    }
}

G_Gameboard::~G_Gameboard(){
    removeAllItems();
}


void G_Gameboard::setViewPosition()
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


/**
 * @details Called at each block displacement.
 * Used mainly when block is moving.
 * Check if collides with B_Water, S_Door, B_Wall, Object, S_ViewBlocEnnemi.
 */
void G_Gameboard::fixMovable(B_Movable *b)
{
    QList<QGraphicsItem *> CollidingItems = b->collidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        QPoint p = b->getPos();
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            qDebug() << "Sink it ! : " << p.x() << " " << p.y();

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            S_Snow *sunk = new S_Snow(p.x(),p.y());
            sunk->setColor("white");
            mainScene->addItem(sunk);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Door).name())
        {
            QString text = tr("Tu as bloqué ta sortie!");
            showDialog(text);

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            B_Wall *wall = new B_Wall(p.x(),p.y());
            wall->setColor("gray");
            mainScene->addItem(wall);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(G_Object).name())
        {
            mainScene->removeItem(CollidingItems.at(i));

            G_Object *objet = dynamic_cast<G_Object*>(CollidingItems.at(i));

            if(objet->getName() != G_Object::OBJECT_EGG)
            {
                restartEnigma();

                QString text = tr("OUCH! Ce bloc vient d'écraser un ");
                text.append(objet->getName());
                text.append(tr("! Tu recommences au dernier checkpoint! "));
                showDialog(text);
            }
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewBlockNPC).name()) //collision avec le champs de vue d'un ennemi
        {
            S_ViewBlockNPC *vb;
            vb = dynamic_cast<S_ViewBlockNPC*>(CollidingItems.at(i));
            vb->blockOn();
            //qDebug() << "---- un bloc obstrue la vue";
        }

    }
}

void G_Gameboard::checkPositionEvents()
{
    QList<QGraphicsItem *> CollidingItems = playableCharacter->CollidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(G_Object).name())
        {
            G_Object *objet = dynamic_cast<G_Object*>(CollidingItems.at(i));
            qDebug() << objet->getName();
            playableCharacter->addObjectToBag(new G_Object(objet->getName()));
            mainScene->removeItem(CollidingItems.at(i));

            if(objet->getName() == G_Object::OBJECT_SHOES)
            {
                playableCharacter->setSlideAble(false);
            }
            else if(objet->getName() == G_Object::OBJECT_EGG)
            {
                if(playerProfil->getNbLive()<G_Profil::NBMAXVIE)
                {
                    playerProfil->setNbLive(playerProfil->getNbLive()+1);
                    lifeList->updateHearts(playerProfil->getNbLive());
                }
                else
                {
                    QString text(tr("Le nombre de vies maximum de %1 a été atteint").arg(G_Profil::NBMAXVIE));
                    showDialog(text);
                }
            }

            objectList->reloadObjectList(playableCharacter->getBag());
            setWidgetPositionBottomRight(objectList);
            objectList->show();
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Dialog).name())
        {
            S_Dialog *item = dynamic_cast<S_Dialog*>(CollidingItems.at(i));
            mainScene->removeItem(CollidingItems.at(i));

            showDialog(item->getText());

            qDebug() << "DIALOG";
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            restartEnigma();

            QString text = "Plouf, dans l'eau! Tu recommences au dernier checkpoint";
            showDialog(text);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(E_Fox).name() || typeid(*CollidingItems.at(i)).name() == typeid(E_Wolf).name())
        {
            restartEnigma();

            QString text = "Tu t'es fait repéré par un ennemi";
            showDialog(text);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewBlockNPC).name()) //collision avec le champs de vue d'un ennemi
        {
            S_ViewBlockNPC *vb;
            vb = dynamic_cast<S_ViewBlockNPC*>(CollidingItems.at(i));

            vb->playableCharacterOn();
            //qDebug() << "---------Je me suis déplacé sur le champs de vue d'un ennemi";
        }
    }
    if(playableCharacter->x() == currentLevel->getUnlockEndPoint().x() && playableCharacter->y() == currentLevel->getUnlockEndPoint().y())
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

/**
 * @details Directions: "l":left, "r":right, "t":top, "b":bottom.
 */
void G_Gameboard::checkChangeView(char sens)
{
    QList<QGraphicsItem *> CollidingItems = playableCharacter->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Door).name())
        {
            qDebug() << "TRANSITION!";
            S_Door *bloc = dynamic_cast<S_Door*>(CollidingItems.at(i));
            if(bloc->isEndLevel() && endable)
            {
                endable = false;
                playableCharacter->emptySacoche();
                setLevel(bloc->getNextLevel());
                setProxy();
                //setFirstDialog();
            }
            else if(bloc->isEndLevel())
            {
                playableCharacter->moveBack();
            }
            else
            {
                if(!bloc->isNeedingItem())
                {
                    if(playableCharacter->checkObjectSacoche(G_Object::OBJECT_SHOES))
                    {
                        playableCharacter->removeObjectFromSacoche(G_Object::OBJECT_SHOES);
                        playableCharacter->setSlideAble(true);
                    }

                    changeView(sens);
                }
                else if(bloc->isNeedingItem() && playableCharacter->checkObjectSacoche(bloc->getNeededItem(), bloc->getNbItem()))
                {
                    if(playableCharacter->checkObjectSacoche(G_Object::OBJECT_SHOES))
                    {
                        playableCharacter->removeObjectFromSacoche(G_Object::OBJECT_SHOES);
                        playableCharacter->setSlideAble(true);
                    }

                    changeView(sens);
                }
                else
                {
                    QString text = tr("Il te faut ");
                    text.append(QString::number(bloc->getNbItem()));
                    text.append(tr("x l'objet \""));
                    text.append((bloc->getNeededItem()));
                    text.append(tr("\" pour aller plus loin ;) "));

                    showDialog(text);

                    playableCharacter->moveBack();
                }
            }
        }
    }
}

/**
 * @details Directions: "l":left, "r":right, "t":top, "b":bottom.
 */
void G_Gameboard::changeView(char sens)
{
    saveCheckpoint();
    playableCharacter->emptyTempBag();

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
    checkPositionEvents();

    setViewPosition();
    playerView->setSceneRect(viewPositionX,viewPositionY,windowSizeX,windowSizeY);

    objectList->reloadObjectList(playableCharacter->getBag());
    setWidgetPositionBottomRight(objectList);
    setWidgetPositionCenter(dialog);
    setWidgetPositionTopLeft(lifeList);
}

void G_Gameboard::setWidgetPositionBottomRight(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX+gameSquares*(sizeX)-width,viewPositionY+gameSquares*(sizeY)-height,width,height);
}

void G_Gameboard::setWidgetPositionCenter(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX+(gameSquares*(sizeX)-width)/2,viewPositionY+(gameSquares*(sizeY)-height)/2,width,height);
}

void G_Gameboard::setWidgetPositionTopLeft(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX,viewPositionY,width,height);
}

/**
 * @details Directions: "l":left, "r":right, "t":top, "b":bottom.
 */
void G_Gameboard::moveBlock(char sens)
{
    switch(sens)
    {
        case 't':
            movable->moveBy(0,-1);
        break;
        case 'b':
            movable->moveBy(0,1);
        break;
        case 'l':
            movable->moveBy(-1,0);
        break;
        case 'r':
            movable->moveBy(1,0);
        break;
    }

    fixMovable(movable);


    if(movable->isSlide())
    {
        SlidingBlock sb;
        sb.slidingMovable = movable;
        sb.direction = sens;


        listSlindingBlocks.append(sb);

        timerBlockDisplacementSlide->start(SLIDE_SPEED);
    }

    movable = NULL;
}

bool G_Gameboard::checkPosition(QGraphicsItem *object)
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
void G_Gameboard::keyPressEvent(QKeyEvent *event)
{
    if(!toggleMenuPause && !isSliding)
    {
        if(!dialogToogle)
        {
            if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
            {
                playableCharacter->setPlayerOrientation('t'); //definir l'orientation du joueur

                if(movePlayableCharacterPingouinToTop())
                {
                    playableCharacter->moveBy(0, -1);

                    checkPositionEvents();
                    checkChangeView('t');

                    if(movable != NULL)
                    {
                        moveBlock('t');
                    }
                    if(playableCharacter->isSlide())
                    {
                        isSliding=true;
                        directionPlayableCharacter = 't';
                        timerPlayableCharacterSlide->start(SLIDE_SPEED);
                    }
                }
            }
            if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
            {
                playableCharacter->setPlayerOrientation('b');

                if(movePlayableCharacterToBottom())
                {
                    playableCharacter->moveBy(0, 1);

                    checkPositionEvents();
                    checkChangeView('b');
                    if(movable != NULL)
                    {
                        moveBlock('b');
                    }
                    if(playableCharacter->isSlide())
                    {
                        isSliding=true;
                        directionPlayableCharacter = 'b';
                        timerPlayableCharacterSlide->start(SLIDE_SPEED);
                    }
                }
            }
            if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
            {
                playableCharacter->setPlayerOrientation('l');

                if(movePlayableCharacterPingouinToLeft())
                {
                    playableCharacter->moveBy(-1, 0);


                        checkPositionEvents();
                        checkChangeView('l');
                        if(movable != NULL)
                        {
                            moveBlock('l');
                        }
                        if(playableCharacter->isSlide())
                        {
                            isSliding=true;
                            directionPlayableCharacter = 'l';
                            timerPlayableCharacterSlide->start(SLIDE_SPEED);
                        }
                }
            }
            if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
            {
                playableCharacter->setPlayerOrientation('r');

                if(movePlayableCharacterPingouinToRight())
                {
                    playableCharacter->moveBy(1, 0);


                        checkPositionEvents();
                        checkChangeView('r');
                        if(movable != NULL)
                        {
                            moveBlock('r');
                        }
                        if(playableCharacter->isSlide())
                        {
                            isSliding=true;
                            directionPlayableCharacter = 'r';
                            timerPlayableCharacterSlide->start(SLIDE_SPEED);
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

bool G_Gameboard::movePlayableCharacterPingouinToLeft()
{
    return movePlayableCharacter(playableCharacter->CollidesLeft(), 'l');
}

bool G_Gameboard::movePlayableCharacterPingouinToRight()
{
    return movePlayableCharacter(playableCharacter->CollidesRight(), 'r');
}

bool G_Gameboard::movePlayableCharacterPingouinToTop()
{
    return movePlayableCharacter(playableCharacter->CollidesTop(), 't');
}

bool G_Gameboard::movePlayableCharacterToBottom()
{
    return movePlayableCharacter(playableCharacter->CollidesBottom(), 'b');
}

/**
 * @details Uses the cross of boxes.
 * Directions: "l":left, "r":right, "t":top, "b":bottom.
 */
bool G_Gameboard::movePlayableCharacter(QList<QGraphicsItem *> CollidingItems, char direction)
{
    bool bMove = true;
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall).name())
        {
            bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())
        {
            B_Movable *b;
            b = dynamic_cast<B_Movable*>(CollidingItems.at(i));

            if(direction == 'l' && b->isMovableToLeft() && checkPosition(b->getCollideBlocPosition(direction)))
            {
                movable = b;
                bMove = true;
            }
            else if(direction == 'r' && b->isMovableToRight() && checkPosition(b->getCollideBlocPosition(direction)))
            {
                movable = b;
                bMove = true;
            }
            else if(direction == 't' && b->isMovableToTop() && checkPosition(b->getCollideBlocPosition(direction)))
            {
                movable = b;
                bMove = true;
            }
            else if(direction == 'b' && b->isMovableToBottom()  && checkPosition(b->getCollideBlocPosition(direction)))
            {
                movable = b;
                bMove = true;
            }
            else{
                bMove=false;
            }
        } 
        else if(typeid(*CollidingItems.at(i)).name() == typeid(S_Door).name())
        {
            bMove = true;
        }
    }
    if(bMove && (!checkPosition(playableCharacter->getCollideBloc(direction))))
    {
        bMove=false;
    }
    return bMove;
}

int G_Gameboard::getGameSquares()
{
    return gameSquares;
}

void G_Gameboard::pauseMenu()
{
    if(!toggleMenuPause)
    {
        timerPlayableCharacterSlide->stop();
        menuPauseInGame->setUnableMenu(currentLevel->getLevelNumber());
        setWidgetPositionCenter(menuPauseInGame);
        proxy->show();
        toggleMenuPause = true;
    }else{
        proxy->hide();
        toggleMenuPause = false;
        timerPlayableCharacterSlide->start(SLIDE_SPEED);
    }
}

void G_Gameboard::resumeGame()
{
    pauseMenu();
}

void G_Gameboard::restartEnigma()
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

        QString text = "Tu as perdu toutes tes vies! Tu recommences au début du niveau.";
        showDialog(text);
    }
}

void G_Gameboard::restartLevel()
{
    removeAllItems();
    disconnectTimer();

    playableCharacter->emptySacoche();

    setLevel(currentLevel->getLevelNumber());
    setProxy();

    playerProfil->setNbLive(playerProfil->getNbLive()-1);
    lifeList->updateHearts(playerProfil->getNbLive());

    //setFirstDialog();
}



void G_Gameboard::returnIsland()
{
    mainScene->removeItem(proxy);
    mainScene->removeItem(objectListProxy);
    mainScene->removeItem(lifeListProxy);
    mainScene->removeItem(dialogProxy);

    playableCharacter->emptySacoche();

    setLevel(1);
    setProxy();
    //setFirstDialog();

    objectListProxy->hide();
    lifeListProxy->hide();
}

void G_Gameboard::exitGame()
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
        W_MenuStart::saveGame(playerProfil);
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


void G_Gameboard::saveCheckpoint()
{
    checkpoint->setX(playableCharacter->x());
    checkpoint->setY(playableCharacter->y());
}

void G_Gameboard::loadCheckpoint()
{
    playableCharacter->setPos((checkpoint->x()+gameSquares)/gameSquares,(checkpoint->y()+gameSquares)/gameSquares);
}

void G_Gameboard::setProxy()
{
    menuPauseInGame = new W_MenuPause(this);
    setWidgetPositionCenter(menuPauseInGame);
    proxy = mainScene->addWidget(menuPauseInGame);
    proxy->hide();
    proxy->setZValue(100);
    toggleMenuPause = false;

    objectList = new W_Object(this);
    objectList->reloadObjectList(playableCharacter->getBag());
    setWidgetPositionBottomRight(objectList);
    objectListProxy = mainScene->addWidget(objectList);
    objectListProxy->show();

    lifeList = new W_Life(this);
    lifeList->updateHearts(playerProfil->getNbLive());
    setWidgetPositionTopLeft(lifeList);
    lifeListProxy = mainScene->addWidget(lifeList);
    lifeListProxy->show();

    dialog = new W_Dialog(this);
    dialogProxy = mainScene->addWidget(dialog);
    dialogProxy->setZValue(90);
    dialogProxy->hide();
    setWidgetPositionCenter(dialog);
    dialogToogle = false;

    qDebug() << "PROXY";
    checkPositionEvents();
}

/**
 * @details -2 StartMenu, -1 tutorial, 0 main island, 1 level-1, 2 level-2, 3 level-3, 4 level-4, 5 level-5, 6 level-6, 7 final-level
 */
void G_Gameboard::setLevel(int value)
{
    delete currentLevel;
    playerProfil->setLevel(value);

    delete this->observerEnemy;
    this->observerEnemy = new Observer_NPC();

    currentLevel = new G_Level(value, observerEnemy, this);
    playableCharacter->setPos(currentLevel->getStartingPoint()->x(),currentLevel->getStartingPoint()->y());
    viewRequested = currentLevel->getViewStart();
    W_MenuStart::saveGame(playerProfil);
    saveCheckpoint();
    loadLevel();
}

void G_Gameboard::loadLevel()
{
    mainScene = currentLevel->populateScene();
    setViewPosition();

    playerView->setScene(mainScene);
    playerView->setSceneRect(viewPositionX,viewPositionY,sizeX*gameSquares,sizeY*gameSquares);

    playableCharacter->addToScene(mainScene);

    playableCharacter->removeTempFromSacoche();
    playableCharacter->setPlayerOrientation('b');
    loadCheckpoint();
    setTimer();
}

void G_Gameboard::setTimer()
{
    QObject::connect(timer, SIGNAL(timeout()), mainScene, SLOT(advance()));
}

void G_Gameboard::disconnectTimer()
{
    QObject::disconnect(timer, SIGNAL(timeout()), mainScene, SLOT(advance()));
}

void G_Gameboard::setPlayerProfil(G_Profil *playerProfil)
{
    this->playerProfil = playerProfil;
    setLevel(playerProfil->getLevel());
    setProxy();
    setTimer();
}

void G_Gameboard::setFirstDialog()
{
    setWidgetPositionCenter(dialog);
    dialogProxy->show();
    dialog->setText("OK",1);
    dialogToogle = true;
}

void G_Gameboard::removeAllItems()
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

/**
 * @details return the size X
 */
int G_Gameboard::getSizeX()
{
    return sizeX;
}
/**
 * @details return the size Y
 */
int G_Gameboard::getSizeY()
{
    return sizeY;
}

void G_Gameboard::showDialog(QString text)
{
    qDebug() << "DIALOG SHOW";
    setWidgetPositionCenter(dialog);
    dialogProxy->show();
    dialog->setText(text,1);
    dialogToogle = true;
}
