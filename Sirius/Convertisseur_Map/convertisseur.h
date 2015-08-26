#ifndef CONVERTISSEUR_H
#define CONVERTISSEUR_H

#include <QWidget>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QList>
#include <QPoint>

#include <QString>

class QLabel;
class QPushButton;
class QSpinBox;

class Convertisseur : public QWidget
{
    Q_OBJECT
public:
    explicit Convertisseur(QWidget *parent = 0);
    QDomElement findElement(QDomDocument doc, QDomElement parent, QString element, QString attribute, QString value);
    void readFile();
    void readXML(QDomDocument doc, QDomElement lvlElement);

signals:

public slots:
    void selectHeader();
    void selectTiled();
    void convert();
    void selectXML();

private:
    QLabel* labelHeaderFile;
    QPushButton* headerFile;
    QString headerName;

    QLabel* labelTiledFile;
    QPushButton* tiledFile;
    QString tiledName;

    QLabel* labelLevelNumber;
    QSpinBox* levelNumber;

    QLabel* labelXMLFusion;
    QPushButton* XMLFusionFile;
    QString XMLName;

    QPushButton* convertButton;
    QPushButton* cancelButton;


};

#endif // CONVERTISSEUR_H
