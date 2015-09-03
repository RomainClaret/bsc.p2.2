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

    textCredits = new QLabel(tr("James Gouin et la Banane Sacrée"
                                "\n\n"
                                "Jeux vidéo de types puzzle game et infiltration."
                                "\n\n"
                                "Developpé derant l'année de Bacholor 2 à la HE-Arc."
                                "\n\n"
                                "Banana Rocket, l'équipe de developpeurs, est formé de:"
                                "\n\n"
                                "Claret Romain : romain@bananarocket.ch"
                                "\n"
                                "Divernois Margaux : margaux@bananarocket.ch"
                                "\n"
                                "Visinand Steve : steve@bananarocket.ch"
                                "\n\n\n"
                                "MUSIQUES"
                                "\n"
                                "Penguin Party by Magne Djupvik (CC->BY&SA)"
                                "\n"
                                "Sound Loops BGM by Christoph Schade (CC->BY&NC&ND)"
                                "\n"
                                "Joyful Jubilee by Kara Square (CC->BY&NC)"
                                "\n"
                                "Star Wars - Cantina (8bit) by crig (SoundCloud free)"
                                "\n"
                                "Star Wars Imperial March by Emre Arisev (SoundCloud free)"
                                "\n\n\n"
                                "SONS"
                                "\n"
                                "Spin Jump by Brandino480 (Public Domain)"
                                "\n"
                                "A Tone by His Self (Public Domain)"
                                "\n"
                                "Winning Triumphal Fanfare by John Stracke (3.0)"
                                "\n"
                                "Glass Break by stephan (3.0)"
                                "\n"
                                "Tornado Siren II by Delilah (3.0)"
                                "\n"
                                "Walking On Gravel by Caroline Ford (3.0)"
                                "\n"
                                "Pitch Baseball by Mike Koenig (3.0)"
                                "\n"
                                "Shooting Star by Mike Koenig (3.0)"
                                "\n"
                                "Walking In Snow by Mike Koenig (3.0)"
                                "\n"
                                "Water Splash by Mike Koenig (3.0)"
                                "\n"
                                "Spit Splat 2 by Mike Koenig (3.0)"
                                "\n"
                                "Water Drop by Mike Koenig (3.0)"
                                "\n"
                                "Water Drop Low by Mike Koenig (3.0)"
                                "\n"
                                "Bubbles by Mike Koenig (3.0)"
                                "\n"
                                "Kung Fu Punch by Mike Koenig (3.0)"
                                "\n"
                                "Blop by Mark DiAngelo (3.0)"
                                "\n"
                                "Page Turn by Mark DiAngelo (3.0)"
                                "\n"
                                "Woosh by Mark DiAngelo (3.0)"
                                "\n"
                                "Page Turn by Mark DiAngelo (3.0)"
                                ""
                                ));
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
    audioSingleton->setMusic("credits");

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
//    audioSingleton->setMusic("Penguin_Party");
    audioSingleton->playMusic();
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
