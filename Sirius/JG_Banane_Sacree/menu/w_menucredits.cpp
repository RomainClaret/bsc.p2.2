#include "w_menucredits.h"
#include "../menu/w_menu.h"
#include <QPushButton>
#include <QFormLayout>

#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>
#include <QTimer>

W_MenuCredits::W_MenuCredits(QWidget *parent)
{
    this->parent = (W_Menu*)parent;
    setTitleParent();

    btnBonusReturn = new QPushButton(tr("Retourner aux bonus"));
    btnBonusReturn->setStyleSheet(W_Menu::styleBtn);

    connect(btnBonusReturn, SIGNAL(clicked()),parent, SLOT(loadBonus()));

    textCredits = new QLabel("Bonjour à tous ! adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis faucibus. Nullam quis ante. Etiam sit amet orci eget eros faucibus tincidunt. Duis leo. Sed fringilla mauris sit amet nibh. Donec sodales sagittis magna. Sed consequat, leo eget bibendum sodales, augue velit cursus nunc,adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet.");
    textCredits->setWordWrap(true);
    textCredits->setAlignment(Qt::AlignCenter);

    scrollArea = new VerticalScrollArea;
    scrollArea->setWidget(textCredits);
    scrollArea->setStyleSheet("border: none;");
    scrollArea->setMaximumHeight(200);
    scrollArea->setMaximumWidth(350);
    scrollArea->setFocusPolicy(Qt::NoFocus);

//    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setEnabled(false);

    layoutMenuPause = new QFormLayout;
    layoutMenuPause->addRow(scrollArea);
    layoutMenuPause->addRow(btnBonusReturn);

     this->resize(400,400);
     this->setLayout(layoutMenuPause);

    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveCredits()));
}

void W_MenuCredits::setTitleParent()
{
    parent->setTitle(tr("Crédits"));
    parent->setSubTitle(tr("Merci de votre participation au jeu!"));
}

void W_MenuCredits::moveCredits()
{
    QScrollBar* scrollBar = scrollArea->verticalScrollBar();

    scrollBar->setValue(scrollBar->value()+1);

    if(scrollBar->value() >= scrollBar->maximum())
    {
        timer->stop();
    }
}

void W_MenuCredits::showEvent(QShowEvent*)
{
    if(this->isVisible())
    {
        scrollArea->verticalScrollBar()->setValue(0);
        timer->start(100);
    }
    else
    {
        timer->stop();
    }
}
