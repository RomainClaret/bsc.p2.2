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
#include "character/p_penguin.h"
#include "surface/b_wall.h"
#include "surface/b_movable.h"
#include "surface/b_movable_simple.h"
#include "surface/b_movable_throw.h"
#include "surface/b_water.h"
#include "surface/s_stone.h"
#include "g_object.h"
#include "surface/s_door.h"
#include "surface/s_viewblocknpc.h"
#include "surface/s_snow.h"
#include "surface/s_ice.h"
#include "surface/s_dialog.h"
#include "surface/s_fire.h"
#include "surface/b_wall_alone.h"
#include "surface/b_wall_group.h"
#include "character/e_otter.h"
#include "g_level.h"
#include "character/c_enemy.h"
#include "character/e_fox.h"
#include "character/e_wolf.h"
#include "character/e_walrus.h"
#include "g_profil.h"
#include "menu/w_menustart.h"
#include "menu/w_menubonus.h"
#include "menu/w_menupause.h"
#include "menu/w_menu.h"
#include "singleton_audio.h"
#include "surface/s_footstep.h"

#include "character/factory_character.h"

#include "memento.h"

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

#include <QPropertyAnimation>

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
    audioSingleton = Singleton_Audio::getInstance();

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
    playableCharacter = new P_Penguin(this);
    checkpoint = new QPoint(0,0);
    playerProfil = new G_Profil();

    observerEnemy = new Observer_Enemy();
    currentLevel = new G_Level(0, observerEnemy, this);

    playerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setProxy();

    isSliding = false;
    isMoving = false;
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

    //OPEN GL
//    QGLWidget* w = new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering));
//    playerView->setViewport(w);
//    playerView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

//    setWindowOpacity(0.99);
}

void G_Gameboard::slideBlock()
{
    for(int i=0; i<listSlindingBlocks.size(); i++)
    {
        B_MovableSimple* MovingBlock = listSlindingBlocks.at(i).slidingMovable;
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
                    removeBloc = false;
                }

                break;

            case 'b':
                if(MovingBlock->isMovableToBottom())
                {
                    MovingBlock->moveBy(0,1);
                    fixMovable(MovingBlock);
                    removeBloc = false;
                }
                break;

            case 'l':
                if(MovingBlock->isMovableToLeft())
                {
                    MovingBlock->moveBy(-1,0);
                    fixMovable(MovingBlock);
                    removeBloc = false;
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
        audioSingleton->playSoundBlockStopSliding();
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
            checkPositionEvents('t');
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
            checkPositionEvents('b');
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
            checkPositionEvents('l');
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
           checkPositionEvents('r');
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
        audioSingleton->playSoundPlayerSlidingStop();
        checkPositionEvents(directionPlayableCharacter);
        checkChangeView(directionPlayableCharacter);
        timerPlayableCharacterSlide->stop();
        isSliding=false;
        movable = NULL;
    }
}

G_Gameboard::~G_Gameboard(){

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
void G_Gameboard::fixMovable(B_MovableSimple *b)
{
    QList<QGraphicsItem *> CollidingItems = b->collidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        QPoint p = b->getPos();
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            audioSingleton->playSoundSunk();
            S_Snow *sunk = new S_Snow(p.x(),p.y(), mainScene);
            sunk->setMovableSunk(b);

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));
            mainScene->addItem(sunk);

            Memento::getInstance()->addSpecialEventSurface(sunk);
            Memento::getInstance()->addRemovedSurface(b);
            Memento::getInstance()->addRemovedSurface((B_Water*)CollidingItems.at(i));
            Memento::getInstance()->removePosSurface(b);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Door).name())
        {
            audioSingleton->playSoundEventLostLevel();
            QString text = tr("Tu as bloqué ta sortie!");
            showDialog(text,"");

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));


            B_Wall_Alone *wall = new B_Wall_Alone(p.x(),p.y());
            wall->setColor("gray");
            mainScene->addItem(wall);

            Memento::getInstance()->addSpecialEventSurface(wall);
            Memento::getInstance()->addRemovedSurface(b);
            Memento::getInstance()->removePosSurface(b);
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
                showDialog(text,"");
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


void G_Gameboard::checkPositionEvents(char sens)
{
    QList<QGraphicsItem *> CollidingItems = playableCharacter->CollidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(G_Object).name())
        {
            G_Object *objet = dynamic_cast<G_Object*>(CollidingItems.at(i));
            playableCharacter->addObjectToBag(new G_Object(objet->getName()));
            mainScene->removeItem(CollidingItems.at(i));

            if(objet->getName() == G_Object::OBJECT_FISH)
            {
                audioSingleton->playSoundGetObject();
            }
            else if(objet->getName() == G_Object::OBJECT_SHOES)
            {
                playableCharacter->setSlideAble(false);
            }
            else if(objet->getName() == G_Object::OBJECT_EGG)
            {
                if(playerProfil->getNbLive()<G_Profil::NBMAXVIE)
                {
                    audioSingleton->playSoundGetObject();
                    playerProfil->setNbLive(playerProfil->getNbLive()+1);
                    lifeList->updateHearts(playerProfil->getNbLive());
                }
                else
                {
                    QString text(tr("Le nombre de vies maximum de %1 a été atteint").arg(G_Profil::NBMAXVIE));
                    audioSingleton->playSoundInteraction();
                    showDialog(text, "");
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

            audioSingleton->playSoundInteraction();

            showDialog(item->getText(),item->getImageName());
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            QString text = "Plouf, dans l'eau! Tu recommences au dernier checkpoint";
            restartEnigma(text, "water_fall");
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Fire).name())
        {
            restartEnigma();

            QString text = "Chaud! Chaud! Le feu est dangereux pour les pieds de notre pingouin";
            showDialog(text,"");
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(E_Fox).name()
                || typeid(*CollidingItems.at(i)).name() == typeid(E_Wolf).name()
                || typeid(*CollidingItems.at(i)).name() == typeid(E_Walrus).name())
        {
            disconnectTimer();

            C_Enemy* enemy = (C_Enemy*)CollidingItems.at(i);
            enemy->setDetectPlayableCharacter(false);

            restartEnigma();

            QString text = "Tu t'es fait repéré par un ennemi";
            showDialog(text,"");
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_MovableThrow).name())
        {
            disconnectTimer();
            restartEnigma();

            QString text = "Tu t'es fait assomé par un bloc de glace";
            showDialog(text,"");
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewBlockNPC).name()) //collision avec le champs de vue d'un ennemi
        {
            //The player moved into an enemy's viewblock

            S_ViewBlockNPC *vb;
            vb = dynamic_cast<S_ViewBlockNPC*>(CollidingItems.at(i));

            if(typeid(vb->owner).name() == typeid(E_Otter).name())
            {
                vb->playableCharacterOn();
            }
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Snow).name())
        {
            //The player moved into an enemy's viewblock
           S_Snow *snow;
           snow = dynamic_cast<S_Snow*>(CollidingItems.at(i));

           S_Footstep* step = snow->showFootPrint(sens);
           mainScene->addItem(step);
       }
    }
    if(playableCharacter->x() == currentLevel->getUnlockEndPoint().x() && playableCharacter->y() == currentLevel->getUnlockEndPoint().y())
    {
        qDebug() << "UNLOCKEND";
        currentLevel->unlock();
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

                    Memento::getInstance()->saveCheckpoint();
                }
                else if(bloc->isNeedingItem() && playableCharacter->checkObjectSacoche(bloc->getNeededItem(), bloc->getNbItem()))
                {
                    if(playableCharacter->checkObjectSacoche(G_Object::OBJECT_SHOES))
                    {
                        playableCharacter->removeObjectFromSacoche(G_Object::OBJECT_SHOES);
                        playableCharacter->setSlideAble(true);
                    }

                    changeView(sens);

                    Memento::getInstance()->saveCheckpoint();
                }
                else
                {
                    QString text = tr("Il te faut ");
                    text.append(QString::number(bloc->getNbItem()));
                    text.append(tr("x l'objet \""));
                    text.append((bloc->getNeededItem()));
                    text.append(tr("\" pour aller plus loin ;) "));

                    showDialog(text,"");

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
    Memento::getInstance()->saveCheckpoint();
    saveCheckpoint();
    playableCharacter->emptyTempBag();

    qDebug() << "CHANGE TO PAUSE IN THE OLD VIEW";
    observerEnemy->switchToState(Observer_Enemy::STATE_PAUSE, viewRequested);

    qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();

    if(sens == 't')
    {
        this-> checkpoint->setY(checkpoint->y()-gameSquares);
        viewRequested.setY(viewRequested.y()-1);
    }
    if(sens == 'b')
    {
        this->checkpoint->setY(checkpoint->y()+gameSquares);
        viewRequested.setY(viewRequested.y()+1);
    }
    if(sens == 'l')
    {
        this->checkpoint->setX(checkpoint->x()-gameSquares);
        viewRequested.setX(viewRequested.x()-1);
    }
    if(sens == 'r')
    {
        this->checkpoint->setX(checkpoint->x()+gameSquares);
        viewRequested.setX(viewRequested.x()+1);
    }

    qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();
    loadCheckpoint();

    checkPositionEvents(directionPlayableCharacter);

    setViewPosition();
    playerView->setSceneRect(viewPositionX,viewPositionY,windowSizeX,windowSizeY);

    objectList->reloadObjectList(playableCharacter->getBag());
    setWidgetPositionBottomRight(objectList);
    setWidgetPositionCenter(dialog);
    setWidgetPositionTopLeft(lifeList);

//    observerEnemy->changeNPCState(Observer_Enemy::STATE_PAUSE); //all in pause
//    observerEnemy->changeNPCState(Observer_Enemy::STATE_PATROL, playableCharacter->getPosOnGame()); //the current in action

    qDebug() << "RESTORE TO ORIGINAL IN THE CURRENT VIEW";
    observerEnemy->switchBackToState(viewRequested);
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

B_MovableSimple* G_Gameboard::getMovable()
{
    return movable;
}

/**
 * @details Directions: "l":left, "r":right, "t":top, "b":bottom.
 */
void G_Gameboard::moveBlock(char sens)
{
//    switch(sens)
//    {
//        case 't':
//            movable->moveBy(0,-1);
//        break;
//        case 'b':
//            movable->moveBy(0,1);
//        break;
//        case 'l':
//            movable->moveBy(-1,0);
//        break;
//        case 'r':
//            movable->moveBy(1,0);
//        break;
//    }

    
    fixMovable(movable);

    if(movable->isSlide())
    {
        audioSingleton->playSoundBlockSliding();
        SlidingBlock sb;
        sb.slidingMovable = movable;
        sb.direction = sens;

        listSlindingBlocks.append(sb);

        timerBlockDisplacementSlide->start(SLIDE_SPEED);
    }
    else
    {
        audioSingleton->playSoundBlockSliding();
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
void G_Gameboard::setIsMoving(bool isMoving)
{
    this->isMoving = isMoving;
}

//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void G_Gameboard::keyPressEvent(QKeyEvent *event)
{
    if(!toggleMenuPause && !isSliding && !isMoving)
    {
        if(!dialogToogle)
        {
            if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
            {
                playableCharacter->setPlayerOrientation('t'); //definir l'orientation du joueur

                if(movePlayableCharacterPingouinToTop())
                {
                    //playableCharacter->moveBy(0, -1);
                    playableCharacter->moveWithTimer('t');
//                    checkPositionEvents();
//                    checkChangeView('t');

//                    if(movable != NULL)
//                    {
//                        moveBlock('t');
//                    }
//                    if(playableCharacter->isSlide())
//                    {
//                        isSliding=true;
//                        directionPlayableCharacter = 't';
//                        timerPlayableCharacterSlide->start(SLIDE_SPEED);
//                    }
                }
            }
            if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
            {
                playableCharacter->setPlayerOrientation('b');

                if(movePlayableCharacterToBottom())
                {
                    //playableCharacter->moveBy(0, 1);
                    playableCharacter->moveWithTimer('b');
//                    checkPositionEvents();
//                    checkChangeView('b');
//                    if(movable != NULL)
//                    {
//                        moveBlock('b');
//                    }
//                    if(playableCharacter->isSlide())
//                    {
//                        isSliding=true;
//                        directionPlayableCharacter = 'b';
//                        timerPlayableCharacterSlide->start(SLIDE_SPEED);
//                    }
                }
            }
            if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
            {
                playableCharacter->setPlayerOrientation('l');

                if(movePlayableCharacterPingouinToLeft())
                {
                    //playableCharacter->moveBy(-1, 0);
                    playableCharacter->moveWithTimer('l');
//                        checkPositionEvents();
//                        checkChangeView('l');
//                        if(movable != NULL)
//                        {
//                            moveBlock('l');
//                        }
//                        if(playableCharacter->isSlide())
//                        {
//                            isSliding=true;
//                            directionPlayableCharacter = 'l';
//                            timerPlayableCharacterSlide->start(SLIDE_SPEED);
//                        }
                }
            }
            if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
            {
                playableCharacter->setPlayerOrientation('r');

                if(movePlayableCharacterPingouinToRight())
                {
                    //playableCharacter->moveBy(1, 0);
                    playableCharacter->moveWithTimer('r');

//                        checkPositionEvents();
//                        checkChangeView('r');
//                        if(movable != NULL)
//                        {
//                            moveBlock('r');
//                        }
//                        if(playableCharacter->isSlide())
//                        {
//                            isSliding=true;
//                            directionPlayableCharacter = 'r';
//                            timerPlayableCharacterSlide->start(SLIDE_SPEED);
//                        }
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

                audioSingleton->playSoundInteraction();
                dialogProxy->hide();
                dialogToogle = false;
            }
        }
    }
    else
    {
        menuPauseInGame->keyPressEvent(event);
    }
    if(event->key() == Qt::Key_Escape)
    {
        pauseMenu();
    }
}

bool G_Gameboard::isMovableSet()
{
    return (movable != NULL);
}

void G_Gameboard::endMoveCheck(char sens)
{
    checkPositionEvents(sens);
    checkChangeView(sens);
    if(movable != NULL)
    {
        moveBlock(sens);
    }
    if(playableCharacter->isSlide())
    {
        audioSingleton->playSoundPlayerSliding();
        isSliding=true;
        directionPlayableCharacter = sens;
        timerPlayableCharacterSlide->start(SLIDE_SPEED);
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

        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall_Alone).name() || typeid(*CollidingItems.at(i)).name() == typeid(B_Wall_Group).name())
        {
            bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_MovableSimple).name())
        {
            B_MovableSimple *b;
            b = dynamic_cast<B_MovableSimple*>(CollidingItems.at(i));

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
        else if(typeid(*CollidingItems.at(i)).name() == typeid(S_Stone).name())
        {
            bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(E_Otter).name())
        {
            bMove = false;
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
        audioSingleton->playMusicPlaylistMenu();
        audioSingleton->pauseMusicPlaylist();
        //observerEnemy->changeNPCState(Observer_Enemy::STATE_PAUSE, playableCharacter->getPosOnGame());
        observerEnemy->switchToState(Observer_Enemy::STATE_PAUSE, viewRequested);

        timerPlayableCharacterSlide->stop();
        menuPauseInGame->setUnableMenu(currentLevel->getLevelNumber());
        setWidgetPositionCenter(menuPauseInGame);
        proxy->show();
        toggleMenuPause = true;
    }else{
        audioSingleton->pauseMusicPlaylistMenu();
        audioSingleton->playMusicPlaylist();
        proxy->hide();
        toggleMenuPause = false;
        timerPlayableCharacterSlide->start(SLIDE_SPEED);

        //observerEnemy->changeNPCState(Observer_Enemy::STATE_PATROL, playableCharacter->getPosOnGame());
        observerEnemy->switchBackToState(viewRequested);
    }
}

void G_Gameboard::resumeGame()
{
    pauseMenu();
}

void G_Gameboard::restartEnigma()
{
    qDebug() << "RESTART ENIGMA";
    if(playerProfil->getNbLive()>0)
    {
        playableCharacter->disconnectTimer();
        disconnectTimer();
        Memento::getInstance()->restartLevel(mainScene);
        loadCheckpoint();
        playableCharacter->removeTempFromSacoche();

        lifeList->updateHearts(playerProfil->getNbLive());

        showProxy();
        setTimer();
	playableCharacter->setTimer();	audioSingleton->playSoundEventRestartCheckpoint();    }
    else
    {


        playerProfil->setNbLive(4);
        restartLevel();

        QString text = "Tu as perdu toutes tes vies! Tu recommences au début du niveau.";

        showDialog(text,"");
        audioSingleton->playSoundEventLostLevel();
    }

    //observerEnemy->changeNPCState(Observer_Enemy::STATE_PATROL, playableCharacter->getPosOnGame());
}


void G_Gameboard::restartEnigma(QString text, QString sound)
{

    qDebug() << "RESTART ENIGMA";
    if(playerProfil->getNbLive()>0)
    {
        disconnectTimer();
        Memento::getInstance()->restartLevel(mainScene);
        loadCheckpoint();

        playableCharacter->removeTempFromSacoche();

        playerProfil->setNbLive(playerProfil->getNbLive()-1);
        lifeList->updateHearts(playerProfil->getNbLive());

        audioSingleton->playSoundEventRestartCheckpoint();
        setTimer();
    }
    else
    {
        playerProfil->setNbLive(4);
        restartLevel();

        text = "Tu as perdu toutes tes vies! Tu recommences au début du niveau.";

        showDialog(text,"");
        audioSingleton->playSoundEventLostLevel();
    }

    //observerEnemy->changeNPCState(Observer_Enemy::STATE_PATROL, playableCharacter->getPosOnGame());
}

void G_Gameboard::restartLevel()
{
    disconnectTimer();

    playableCharacter->emptySacoche();
    setLevel(currentLevel->getLevelNumber());
    setProxy();
//    linkProxy();
//    showProxy();
//    checkPositionEvents();

    playerProfil->setNbLive(playerProfil->getNbLive()-1);
    lifeList->updateHearts(playerProfil->getNbLive());

    Memento::getInstance()->saveCheckpoint();
    setTimer();
}

void G_Gameboard::loadBonus()
{
    qDebug() << "LOAD BONUS";

//    delete widgetBonus;
//    widgetBonus = new W_MenuBonus(this);

//    setWidgetPositionCenter(widgetBonus);
//    proxy = mainScene->addWidget(widgetBonus);
//    proxy->show();
//    proxy->setZValue(100);
//    toggleMenuPause = true;
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
        currentLevel->clearScene();
        W_MenuStart::saveGame(playerProfil);
        close();
        audioSingleton->playMusicPlaylistMenu();
        break;
    case QMessageBox::RejectRole:
        qDebug() << "Reject";
        break;
    case QMessageBox::DestructiveRole:
        qDebug() << "Destruct";
        currentLevel->clearScene();
        close();
        audioSingleton->playMusicPlaylistMenu();
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
    playableCharacter->setPlayerOrientation('b');
}

void G_Gameboard::setProxy()
{
    menuPauseInGame = new W_Menu(this);
    setWidgetPositionCenter(menuPauseInGame);
    proxy = mainScene->addWidget(menuPauseInGame);
    proxy->hide();
    proxy->setZValue(100);
    toggleMenuPause = false;

    objectList = new W_Object(this);
    objectList->reloadObjectList(playableCharacter->getBag());
    setWidgetPositionBottomRight(objectList);
    objectListProxy = mainScene->addWidget(objectList);
    objectListProxy->setZValue(8);
    objectListProxy->show();

    lifeList = new W_Life(this);
    lifeList->updateHearts(playerProfil->getNbLive());
    setWidgetPositionTopLeft(lifeList);
    lifeListProxy = mainScene->addWidget(lifeList);
    lifeListProxy->setZValue(8);
    lifeListProxy->show();

    dialog = new W_Dialog(this);
    dialogProxy = mainScene->addWidget(dialog);
    dialogProxy->setZValue(90);
    dialogProxy->hide();

    audioSingleton->setPlayableSounds(true); //activate sounds after the proxy got shown and hidden
    setWidgetPositionCenter(dialog);
    dialogToogle = false;


    checkPositionEvents(directionPlayableCharacter);
}

void G_Gameboard::showProxy()
{
    proxy->hide();
    toggleMenuPause = false;
    objectListProxy->show();
    lifeListProxy->show();
    dialogProxy->hide();
    dialogToogle = false;

    setWidgetPositionBottomRight(objectList);

    checkPositionEvents(directionPlayableCharacter);
}

void G_Gameboard::linkProxy()
{
    proxy = mainScene->addWidget(menuPauseInGame);
    objectListProxy = mainScene->addWidget(objectList);
    lifeListProxy = mainScene->addWidget(lifeList);
    dialogProxy = mainScene->addWidget(dialog);
}

/**
 * @details -2 StartMenu, -1 tutorial, 0 main island, 1 level-1, 2 level-2, 3 level-3, 4 level-4, 5 level-5, 6 level-6, 7 final-level
 */
void G_Gameboard::setLevel(int value)
{
    audioSingleton->stopMusicPlaylist();
    //delete currentLevel;
    //playerProfil->setLevel(value);
    currentLevel->loadLevel(value);
    observerEnemy->clear();
    mainScene = currentLevel->populateScene();

    playableCharacter = new P_Penguin(this);
    playableCharacter->setPos(currentLevel->getStartingPoint()->x(),currentLevel->getStartingPoint()->y());
    playableCharacter->addToScene(mainScene);
    playableCharacter->removeTempFromSacoche();
    playableCharacter->setPlayerOrientation('b');

    viewRequested = currentLevel->getViewStart();

    playerProfil->setLevel(value);
    W_MenuStart::saveGame(playerProfil);

    saveCheckpoint();
    Memento::getInstance()->saveCheckpoint();

    audioSingleton->playSoundEventStartGame();
    audioSingleton->playMusicPlaylist(value);

    setViewPosition();
    playerView->setScene(mainScene);
    playerView->setSceneRect(viewPositionX,viewPositionY,sizeX*gameSquares,sizeY*gameSquares);

    //observerEnemy->changeNPCState(Observer_Enemy::STATE_PATROL, playableCharacter->getPosOnGame());
    //observerEnemy->switchBackToState(viewRequested);

    //start with all the enemies in pause
    observerEnemy->switchAllToPause();
    observerEnemy->switchBackToState(viewRequested);
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

bool G_Gameboard::isSlidingBloc(B_MovableSimple* bloc)
{
    bool isSliding = false;
    foreach (SlidingBlock slidingBloc, listSlindingBlocks) {
        if(slidingBloc.slidingMovable == bloc)
        {
            isSliding = true;
        }
    }
    return isSliding;
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

void G_Gameboard::showDialog(QString text, QString image)
{
    dialog->setText(text,1);
    dialog->setImage(image);
    setWidgetPositionCenter(dialog);
    dialogProxy->show();
    dialogToogle = true;
}

QGraphicsScene* G_Gameboard::getGraphicsScene()
{
    return this->mainScene;
}

void G_Gameboard::deleteGame()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Suppression de la partie"));
    msgBox.setInformativeText(tr("Voulez-vous vraiment supprimer cette partie?"));
    msgBox.addButton(tr("Supprimer"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("Annuler"), QMessageBox::RejectRole);

    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::AcceptRole:
        W_MenuStart::deleteGame(playerProfil);
        emit(refreshMenu());
        close();
        break;
    case QMessageBox::RejectRole:
        break;
    default:
        // should never be reached
        break;
    }
}
