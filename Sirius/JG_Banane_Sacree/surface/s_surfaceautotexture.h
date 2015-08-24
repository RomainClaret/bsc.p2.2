#ifndef S_SURFACEAUTOTEXTURE_H
#define S_SURFACEAUTOTEXTURE_H
#include "g_surface.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QVector>

/**
 * @brief SurfaceAutoTexure is a inteligent surface, it can determinate the type of the environnents surfaces to construct its skin ans play annimation
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.42
 * @date 24 august 2015
 */
class S_SurfaceAutoTexture : public G_Surface
{
public:
    S_SurfaceAutoTexture(int xpos, int ypos,QGraphicsItem *parent = 0);
    virtual ~S_SurfaceAutoTexture(){}

    /**
     * @brief calculateTextures Calculate the textures
     * @param mapSurfaces
     * @param width
     * @param height
     */
    virtual void calculateTextures(int** mapSurfaces, int width, int height)=0;

    /**
     * @brief addToScene to add a S_SurfaceAuto to the scene
     * @param scene
     */
    void addToScene(QGraphicsScene *scene);

protected:
    /**
     * @brief texture_init is the initial texture of the surface
     */
    QPixmap texture_init;

    /**
     * @brief texturesAnim this list contain the Pixmap for the annimation
     */
    QVector<QPixmap> texturesAnim;

    /**
     * @brief iCurrentTexture index for the animation
     */
    int iCurrentTexture;

    /**
     * @brief speed speed of the animation
     */
    int speed;

    /**
     * @brief advance called by the scene, used for the annimation
     * @param step
     */
    void advance(int step);

    /**
     * @brief collideLeft determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideLeft(int type, int** mapSurfaces);
    /**
     * @brief collideRight determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideRight(int type, int** mapSurfaces, int width);
    /**
     * @brief collideTop determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideTop(int type, int** mapSurfaces);
    /**
     * @brief collideBottom determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideBottom(int type, int** mapSurfaces, int height);
    /**
     * @brief collideLeftTop determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideLeftTop(int type, int** mapSurfaces);
    /**
     * @brief collideLeftBottom determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideLeftBottom(int type, int** mapSurfaces, int height);
    /**
     * @brief collideRightTop determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideRightTop(int type, int** mapSurfaces, int width);
    /**
     * @brief collideRightBottom determinate, with the generated matrix, if the left bloc is a bloc of "type"
     * @param type type of the bloc
     * @param mapSurfaces generated matrix
     * @param width width of the matrix
     * @param height height of the matrix
     * @return true if a bloc of "type" is here
     */
    bool collideRightBottom(int type, int** mapSurfaces, int width, int height);

    /**
     * @brief addTexture add texture on the bloc
     * @param pixmap
     */
    void addTexture(QPixmap pixmap);

//    void destroyCollidingBoxes();

//    QPixmap texture_l_Collide;
//    QPixmap texture_lb_Collide; //angle
//    QPixmap texture_b_Collide;
//    QPixmap texture_rb_Collide; //angle
//    QPixmap texture_r_Collide;
//    QPixmap texture_rt_Collide; //angle
//    QPixmap texture_t_Collide;
//    QPixmap texture_lt_Collide; //angle

//    QGraphicsRectItem *leftCollideBox;
//    QGraphicsRectItem *leftTopCollideBox;
//    QGraphicsRectItem *rightCollideBox;
//    QGraphicsRectItem *rightTopCollideBox;
//    QGraphicsRectItem *bottomCollideBox;
//    QGraphicsRectItem *rightBottomCollideBox;
//    QGraphicsRectItem *topCollideBox;
//    QGraphicsRectItem *leftBottomCollideBox;

private:
    /**
     * @brief addedTextures list of the textures added on the bloc
     */
    QList<QGraphicsRectItem*> addedTextures;
    QGraphicsScene* scene;
    int time;

};

#endif // S_SURFACEAUTOTEXTURE_H
