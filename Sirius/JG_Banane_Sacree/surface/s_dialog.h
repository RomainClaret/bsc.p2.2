/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#ifndef S_DIALOG_H
#define S_DIALOG_H

#include "g_surface.h"

class QGraphicsItem;


/**
 * @brief Dialog blocks.
 * @details Surface with a dialog to interact with the player.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */
class S_Dialog : public G_Surface
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    S_Dialog(int xpos, int ypos, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup.
     * @param parent QGraphicsItem to depend on
     */
    S_Dialog(QGraphicsItem *parent = 0);

    /**
     * @brief Set the number of the dialog.
     * @param value
     */
    void setDialogNumber(int value);

    /**
     * @brief Get the number of the dialog of self.
     * @param value
     */
    int getDialogNumber();

    /**
     * @brief Set the dialog of self.
     * @param text
     */
    void addDialogText(QString text);

    /**
     * @brief Get the dialog of self.
     * @return text of the dialog
     */
    QString getText();

private:
    /**
     * @brief Set the design of self.
     */
    void setDesign();

    int dialogNumber;
    QString text;

};

#endif // S_DIALOG_H
