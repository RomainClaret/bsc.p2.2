#ifndef VERTICALSCROLLAREA_H
#define VERTICALSCROLLAREA_H

#include <QScrollArea>

/**
 * @brief Vertical ScrollArea only
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 20 August 2015
 */
class VerticalScrollArea : public QScrollArea
{
Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent
     */
    explicit VerticalScrollArea(QWidget *parent = 0);

    /**
     * @brief eventFilter
     * @param o
     * @param e
     * @return Boolean
     */
    virtual bool eventFilter(QObject *o, QEvent *e);

};

#endif // VERTICALSCROLLAREA_H
