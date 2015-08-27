#include "convertisseur.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QSpinBox>

#include <QTextCodec>

#include <QMessageBox>

Convertisseur::Convertisseur(QWidget *parent) : QWidget(parent)
{
    labelHeaderFile = new QLabel("Header* : ");
    headerFile = new QPushButton("Sélectionner un fichier");

    labelTiledFile = new QLabel("Fichier Tiled* : ");
    tiledFile = new QPushButton("Sélectionner un fichier");

    labelLevelNumber = new QLabel("Level Number* : ");
    levelNumber = new QSpinBox();

    labelXMLFusion = new QLabel("XML Fusion : ");
    XMLFusionFile = new QPushButton("Sélectionner un fichier");

    convertButton = new QPushButton("Convertir");
    cancelButton = new QPushButton("Annuler");

    QFormLayout* layout = new QFormLayout();
    layout->addRow(labelHeaderFile,headerFile);
    layout->addRow(labelTiledFile, tiledFile);
    layout->addRow(labelLevelNumber,levelNumber);
    layout->addRow(labelXMLFusion,XMLFusionFile);
    layout->addRow(convertButton, cancelButton);
    setLayout(layout);

    QObject::connect(headerFile,SIGNAL(clicked()),this,SLOT(selectHeader()));
    QObject::connect(tiledFile,SIGNAL(clicked()),this,SLOT(selectTiled()));
    QObject::connect(convertButton,SIGNAL(clicked()),this,SLOT(convert()));
    QObject::connect(XMLFusionFile,SIGNAL(clicked()),this,SLOT(selectXML()));
    QObject::connect(cancelButton,SIGNAL(clicked()),qApp,SLOT(quit()));
}

QDomElement Convertisseur::findElement(QDomDocument doc, QDomElement parent, QString element, QString attribute, QString value)
{
  for(QDomElement elem = parent.firstChildElement(); !elem.isNull(); elem = elem.nextSiblingElement())
  {
    if(elem.tagName()==element)
    {
        if(elem.attribute(attribute) == value)
        {
            return elem;
        }
    }
  }

  QDomElement e = doc.createElement(element);
  e.setAttribute(attribute,value);
  return e;
}

void Convertisseur::selectHeader()
{
    this->headerName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"), "/", QObject::tr("Text files (*.cpp *.txt)"));
    if(!headerName.isEmpty())
    {
        headerFile->setText("Changer de fichier");
    }
}

void Convertisseur::selectTiled()
{
    this->tiledName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"), "/", QObject::tr("Text files (*.cpp *.txt)"));
    if(!tiledName.isEmpty())
    {
        tiledFile->setText("Changer de fichier");
    }
}

void Convertisseur::selectXML()
{
    this->XMLName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"), "/", QObject::tr("Text files (*.xml)"));
    if(!XMLName.isEmpty())
    {
        XMLFusionFile->setText("Changer de fichier");
    }
}

void Convertisseur::convert()
{
    if(!headerName.isEmpty() && !tiledName.isEmpty())
    {

        QString newFileName = QFileDialog::getExistingDirectory();
        newFileName.append("/L");
        newFileName.append(QString::number(levelNumber->value()));
        newFileName.append(".xml");
        qDebug() << newFileName;

        QFile fileWrite(newFileName);
        if(!fileWrite.open(QIODevice::WriteOnly | QIODevice::Text)) { qDebug() << "ERROR"; }

        QDomDocument doc;
        QDomElement level = doc.createElement("LEVEL");

//        QList<QList<QPoint> > ennemi;
        int maxBlocksHeight, maxBlocksWidth;

        QFile fHeader(headerName);
        if(fHeader.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream t(&fHeader);
            t.setCodec(QTextCodec::codecForName("UTF-8"));
            QString line[1000];
            int line_count=0;

            while(!t.atEnd())
            {
                line_count++;
                line[line_count]=t.readLine();
                if(line[line_count].contains("[header]"))
                {
                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList valueWidth = line[line_count].split("=");
                    QDomElement size = doc.createElement("SIZE");
                    size.setAttribute("width",valueWidth.at(1).toInt());
                    maxBlocksWidth = valueWidth.at(1).toInt();

                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList valueHeight = line[line_count].split("=");
                    size.setAttribute("height",valueHeight.at(1).toInt());
                    level.appendChild(size);
                    maxBlocksHeight = valueHeight.at(1).toInt();

                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList valueViewX = line[line_count].split("=");
                    QDomElement position = doc.createElement("POSITION");
                    position.setAttribute("x",valueViewX.at(1).toInt());

                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList valueViewY = line[line_count].split("=");
                    position.setAttribute("y",valueViewY.at(1).toInt());
                    level.appendChild(position);

                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList valueStartX = line[line_count].split("=");
                    QDomElement start = doc.createElement("START");
                    start.setAttribute("x",valueStartX.at(1).toInt());

                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList valueStartY = line[line_count].split("=");
                    start.setAttribute("y",valueStartY.at(1).toInt());
                    level.appendChild(start);

                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList unlockEndX = line[line_count].split("=");
                    QDomElement end = doc.createElement("END");
                    end.setAttribute("x",unlockEndX.at(1).toInt());

                    line_count++;
                    line[line_count] = t.readLine();
                    QStringList unlockEndY = line[line_count].split("=");
                    end.setAttribute("y",unlockEndY.at(1).toInt());
                    level.appendChild(end);
                }
            }
        }
        fHeader.close();

        QDomNode noeud = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
        doc.insertBefore(noeud,doc.firstChild());

        QDomElement data = doc.createElement("DATA");
        data.appendChild(level);

        QDomElement lvl_elements = doc.createElement("LEVELITEM");

        QFile fLevel(tiledName);
//        int k = 0;

        if(fLevel.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream t(&fLevel);
            t.setCodec("UTF-8");
            QString line[1000];
            int line_count=0;

            int matX, matY;
            QDomElement ligne;
            QDomElement colonne;
            QDomElement element;

            while(!t.atEnd())
            {
                line_count++;
                line[line_count]=t.readLine();

//                if(line[line_count].contains("[ennemi]"))
//                {
//                    line_count++;
//                    line[line_count] = t.readLine();
//                    QStringList listEnnemi = line[line_count].split("//");

//                    for(int j = 0; j < listEnnemi.size(); j++)
//                    {
//                        QStringList listPoint = listEnnemi.at(j).split(",");
//                        QList<QPoint> listeDePoints;
//                        for(int i = 0; i < listPoint.size(); i++)
//                        {
//                            QStringList point = listPoint.at(i).split("-");
//                            listeDePoints.append(QPoint(point.at(0).toInt(),point.at(1).toInt()));
//                        }
//                        ennemi.append(listeDePoints);
//                    }
//                }
                if(line[line_count].contains("type=Walls_Blocks"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();
                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","WALL");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=Solid_Blocks"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();
                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","WALL");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=Movable_Blocks"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","MOVABLE");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
//                if(line[line_count].contains("type=Items"))
//                {
//                    line_count ++;
//                    line[line_count]=t.readLine();
//                    line_count ++;
//                    line[line_count]=t.readLine();

//                    for (matY = 0; matY < maxBlocksHeight; matY++)
//                    {
//                        QStringList values = line[line_count].split(",");

//                        for (matX = 0; matX < maxBlocksWidth; matX++)
//                        {
//                            if(values.at(matX).toInt() != 0)
//                            {
//                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
//                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
//                                element = findElement(doc, ligne,"ITEM","type","ITEM");
//                                ligne.appendChild(element);
//                                colonne.appendChild(ligne);
//                                lvl_elements.appendChild(colonne);
//                            }
//                        }
//                        line_count++;
//                        line[line_count]=t.readLine();
//                    }
//                }
                if(line[line_count].contains("type=Bonus"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"ITEM","type","BONUS");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=Enemies"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));

                                QString type;
                                switch(values.at(matX).toInt())
                                {
                                case 1: type = "FOX";
                                case 2: type = "WOLF";
                                default:break;
                                }

                                element = findElement(doc, ligne,"ENEMY","type",type);

//                                for (int i = 0; i < ennemi.at(k).size(); ++i) {
//                                    QDomElement deplacement = doc.createElement("MOVE");
//                                    deplacement.setAttribute("x",ennemi.at(k).at(i).x());
//                                    deplacement.setAttribute("y",ennemi.at(k).at(i).y());
//                                    deplacement.setAttribute("i",i+1);
//                                    element.appendChild(deplacement);
//                                }

                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);

//                                k++;
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=Scene_End"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"END","nextLevel",values.at(matX));
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
//                if(line[line_count].contains("type=Doors"))
//                {
//                    line_count ++;
//                    line[line_count]=t.readLine();
//                    line_count ++;
//                    line[line_count]=t.readLine();

//                    for (matY = 0; matY < maxBlocksHeight; matY++)
//                    {
//                        QStringList values = line[line_count].split(",");

//                        for (matX = 0; matX < maxBlocksWidth; matX++)
//                        {
//                            if(values.at(matX).toInt() != 0)
//                            {
//                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
//                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));

//                                if(values.at(matX).toInt() > 20 && values.at(matX).toInt() < 30)
//                                {
//                                    element = findElement(doc, ligne,"DOOR","item","Poisson");
//                                    element.setAttribute("nbItem",values.at(matX).toInt()%20);
//                                }
//                                else
//                                {
//                                    element = findElement(doc, ligne,"DOOR","","");
//                                }

//                                ligne.appendChild(element);
//                                colonne.appendChild(ligne);
//                                lvl_elements.appendChild(colonne);
//                            }
//                        }
//                        line_count++;
//                        line[line_count]=t.readLine();
//                    }
//                }
                if(line[line_count].contains("type=Water_Blocks"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();
                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","WATER");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=NoMoves_Blocks"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","WALL");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=Snow_Surface"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","SNOW");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=Ice_Surface"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","ICE");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
//                if(line[line_count].contains("type=Item_Shoes"))
//                {
//                    line_count ++;
//                    line[line_count]=t.readLine();
//                    line_count ++;
//                    line[line_count]=t.readLine();

//                    for (matY = 0; matY < maxBlocksHeight; matY++)
//                    {
//                        QStringList values = line[line_count].split(",");

//                        for (matX = 0; matX < maxBlocksWidth; matX++)
//                        {
//                            if(values.at(matX).toInt() != 0)
//                            {
//                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
//                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
//                                element = findElement(doc, ligne,"ITEM","type","SHOES");
//                                ligne.appendChild(element);
//                                colonne.appendChild(ligne);
//                                lvl_elements.appendChild(colonne);
//                            }
//                        }
//                        line_count++;
//                        line[line_count]=t.readLine();
//                    }
//                }
//                if(line[line_count].contains("type=Dialogs"))
//                {
//                    line_count ++;
//                    line[line_count]=t.readLine();
//                    line_count ++;
//                    line[line_count]=t.readLine();

//                    for (matY = 0; matY < maxBlocksHeight; matY++)
//                    {
//                        QStringList values = line[line_count].split(",");

//                        for (matX = 0; matX < maxBlocksWidth; matX++)
//                        {
//                            if(values.at(matX).toInt() != 0)
//                            {
//                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
//                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
//                                element = findElement(doc, ligne,"DIALOG","position",values.at(matX));
//                                //element.setAttribute("text",dialogList.at(values.at(matX).toInt()-1));
//                                ligne.appendChild(element);
//                                colonne.appendChild(ligne);
//                                lvl_elements.appendChild(colonne);
//                            }
//                        }
//                        line_count++;
//                        line[line_count]=t.readLine();
//                    }
//                }
                if(line[line_count].contains("type=Fire_Blocks"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","FIRE");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
                if(line[line_count].contains("type=Stone_Blocks"))
                {
                    line_count ++;
                    line[line_count]=t.readLine();
                    line_count ++;
                    line[line_count]=t.readLine();

                    for (matY = 0; matY < maxBlocksHeight; matY++)
                    {
                        QStringList values = line[line_count].split(",");

                        for (matX = 0; matX < maxBlocksWidth; matX++)
                        {
                            if(values.at(matX).toInt() != 0)
                            {
                                colonne = findElement(doc, lvl_elements,"COLONNE","position",QString::number(matX));
                                ligne = findElement(doc, colonne,"LIGNE","position",QString::number(matY));
                                element = findElement(doc, ligne,"BLOC","type","STONE");
                                ligne.appendChild(element);
                                colonne.appendChild(ligne);
                                lvl_elements.appendChild(colonne);
                            }
                        }
                        line_count++;
                        line[line_count]=t.readLine();
                    }
                }
            }
            fLevel.close();
        }
        else
        {
            qDebug() << "Fichier non ouvert";
        }

        if(!XMLName.isEmpty())
        {
            readXML(doc, lvl_elements);
        }

        data.appendChild(lvl_elements);
        doc.appendChild(data);

        QTextStream out(&fileWrite);
        out.setCodec(QTextCodec::codecForName("UTF-8"));
        out << doc.toString();

        QMessageBox msgBox;
        msgBox.setText("Fichier créé");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Les documents ont étés incorrectement sélectionnés.");
        msgBox.exec();
    }
}

void Convertisseur::readXML(QDomDocument doc, QDomElement lvlElement)
{
    QString errorMsg;
    int errorLine, errorColumn;
    QDomDocument* docFusion = new QDomDocument(XMLName);
    QFile file(XMLName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!docFusion->setContent(&file, &errorMsg, &errorLine, &errorColumn))
    {
        file.close();
        qDebug() << "ERROR";
        qDebug() << "Parsing error, line " << errorLine
                << " column " << errorColumn
                << ": " << qPrintable(errorMsg) << endl;
        return;
    }
    file.close();

    QDomElement elementLevel = docFusion->firstChildElement();
    for(QDomElement colonne = elementLevel.firstChildElement(); !colonne.isNull(); colonne = colonne.nextSiblingElement())
    {
        QDomElement colonneN = findElement(doc, lvlElement,"COLONNE","position",colonne.attribute("position"));
        for(QDomElement ligne = colonne.firstChildElement(); !ligne.isNull(); ligne = ligne.nextSiblingElement())
        {
            QDomElement ligneN = findElement(doc, colonneN,"LIGNE","position",ligne.attribute("position"));
            for(QDomElement item = ligne.firstChildElement(); !item.isNull(); item = item.nextSiblingElement())
            {
                ligneN.appendChild(item);
            }
            colonneN.appendChild(ligneN);
        }
        lvlElement.appendChild(colonneN);
    }
}
