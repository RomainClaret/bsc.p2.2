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

    connect(btnBonusReturn, SIGNAL(clicked()),this, SLOT(close()));

    textCredits = new QLabel("Bonjour à tous !\n\n "
                             "MUSIC\nPenguin Party by Magne Djupvik");
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

    audioSingleton = Singleton_Audio::getInstance();
//    audioSingleton->setMusic("Penguin_Party");
    audioSingleton->setMusic("");
//    audioSingleton->setMusicPlaylist("");

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

void W_MenuCredits::showEvent(QShowEvent *)
{
    audioSingleton->playMusic();
//    audioSingleton->playMusicPlaybackWithIntro();
    scrollArea->verticalScrollBar()->setValue(0);
    timer->start(100);
}

void W_MenuCredits::hideEvent(QHideEvent *)
{
    audioSingleton->stopMusic();
    timer->stop();
}

void W_MenuCredits::close()
{
    audioSingleton->stopMusic();
    parent->loadBonus();
}
