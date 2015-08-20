#ifndef W_MENUCREDITS_H
#define W_MENUCREDITS_H

#include <QWidget>
#include "../tools/verticalscrollarea.h"

class W_Menu;
class QPushButton;
class QFormLayout;
class QTimer;
class QLabel;

class W_MenuCredits: public QWidget
{
    Q_OBJECT
public:
    W_MenuCredits(QWidget *parent);
    void setTitleParent();

    void showEvent(QShowEvent*);

private:
    QFormLayout *layoutMenuPause;
    QPushButton *btnBonusReturn;
    W_Menu* parent;

    QLabel* textCredits;
    VerticalScrollArea* scrollArea;
    QTimer* timer;

public slots:
        void moveCredits();
};

#endif // W_MENUCREDITS_H
