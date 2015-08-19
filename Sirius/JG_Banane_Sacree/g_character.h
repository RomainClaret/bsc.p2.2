#ifndef G_CHARACTER_H
#define G_CHARACTER_H

#include <QGraphicsItem>

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
class G_Character : public QGraphicsItem
{
public:
    G_Character();

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

protected:
    QString leftSkin;
    QString rightSkin;
    QString upSkin;
    QString downSkin;

    char orientation;

    //Skins are the pictures given to self
    QBrush *skin;

};

#endif // G_CHARACTER_H
