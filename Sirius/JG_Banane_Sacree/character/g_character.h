#ifndef G_CHARACTER_H
#define G_CHARACTER_H

#include <QGraphicsObject>

/**
 * @brief The Character class
 * @details Abstract class
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 19 august 2015
 */
class G_Character : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    G_Character();
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

    void moveWithTimer(char orientation);
    virtual void moveByPixel(int x, int y)=0;
protected:
    QString leftSkin;
    QString rightSkin;
    QString upSkin;
    QString downSkin;

    char orientation;

    //Skins are the pictures given to self
    QBrush *skin;

private slots:
    void stepMove();

private:

    QTimer* timerMover;
    QPointF startCurrentMove;
    char currentMove;


};

#endif // G_CHARACTER_H
