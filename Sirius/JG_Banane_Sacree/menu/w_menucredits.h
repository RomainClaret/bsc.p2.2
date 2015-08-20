#ifndef W_MENUCREDITS_H
#define W_MENUCREDITS_H

#include <QWidget>
#include "../tools/verticalscrollarea.h"

class W_Menu;
class QPushButton;
class QFormLayout;
class QTimer;
class QLabel;
class QMediaPlayer;

class W_MenuCredits: public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent
     */
    W_MenuCredits(QWidget *parent);

    /**
     * @brief Set the W_Menu title and subtitle
     */
    void setTitleParent();

    /**
     * @brief showEvent
     */
    void showEvent(QShowEvent*);

    /**
     * @brief hideEvent
     */
    void hideEvent(QHideEvent *);

private:
    // Layout
    QFormLayout *layoutMenuPause;

    // Element
    QPushButton *btnBonusReturn;
    QLabel* textCredits;
    VerticalScrollArea* scrollArea;
    QTimer* timer;
    QMediaPlayer* player;

    // Parent
    W_Menu* parent;

public slots:
    /**
     * @brief SLOT: Move the credits
     */
    void moveCredits();

    void close();
};

#endif // W_MENUCREDITS_H
