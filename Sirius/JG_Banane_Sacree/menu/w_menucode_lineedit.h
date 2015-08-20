#ifndef W_MENUCODE_LINEEDIT_H
#define W_MENUCODE_LINEEDIT_H

#include <QLineEdit>
#include <QWidget>

/**
 * @brief LineEdit special for the MenuCode
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 20 August 2015
 */
class W_MenuCode_LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent
     */
    explicit W_MenuCode_LineEdit(QWidget *parent = 0);

    /**
     * @brief Receive KeyPressEvent and sent it to QLineEdit parent
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:

};

#endif // W_MENUCODE_LINEEDIT_H
