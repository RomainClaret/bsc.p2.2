#ifndef G_CHARACTER_H
#define G_CHARACTER_H

#include <QGraphicsObject>

class Singleton_Audio;
class G_Gameboard;

/**
 * @brief The Character class
 * @details Abstract class
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 26 august 2015
 */
class G_Character : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    G_Character(G_Gameboard* game);
    virtual ~G_Character(){}
    /**
     * @brief boundingRect must be implement to be a QGraphicsItem
     * @return the size of the colliding zone
     */
    QRectF boundingRect() const;

    /**
     * @brief paint must be implement to be a QGraphicsItem
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief moveWithTimer move the character with a annimation, start timer on stepMove();
     * @param orientation direction of the move
     */
    void moveWithTimer(char orientation);

    /**
     * @brief moveByPixel move the character by nb pixel
     * @param x x pixels
     * @param y y pixels
     */
    virtual void moveByPixel(int x, int y)=0;

    void setTimer();
    void disconnectTimer();

    virtual void setPosition(int xpos, int ypos);
    bool isMoving();

protected:
    QString leftSkin;
    QString rightSkin;
    QString upSkin;
    QString downSkin;

    char orientation;

    //Skins are the pictures given to self
    QBrush *skin;

    QPointF startCurrentMove;
    char currentMove;
    QTimer* timerMover;

    G_Gameboard* game;

private slots:
    /**
     * @brief stepMove connect the timer on it and call stepMoveCharacter() (different in each character)
     */
    void stepMove();

private:
    /**
     * @brief stepMoveCharactera step of the character
     */
    virtual void stepMoveCharacter()=0;

    Singleton_Audio *audioSingleton;

};

#endif // G_CHARACTER_H
