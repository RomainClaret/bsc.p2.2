#include <QApplication>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QList>
#include <QPoint>

QDomElement findElement(QDomDocument doc, QDomElement parent, QString element, QString attribute, QString value)
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString levelName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"), "/", QObject::tr("Text files (*.cpp *.txt)"));
    QString newFileName = "0.xml";

    QFile fileWrite(newFileName);
    if(!fileWrite.open(QIODevice::WriteOnly | QIODevice::Text)) { qDebug() << "ERROR"; }

    QDomDocument doc(newFileName);
    QDomElement level = doc.createElement("LEVEL");

    QList<QList<QPoint> > ennemi;
    int maxBlocksHeight, maxBlocksWidth;

    QFile fHeader(levelName);
    if(fHeader.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&fHeader);
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
    doc.appendChild(level);

    QStringList dialogList;
    levelName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"), "/", QObject::tr("Text files (*.cpp *.txt)"));
    QFile fTextes(levelName);

    if(fTextes.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&fTextes);
        t.setCodec("UTF-8");
        QString line[1000];
        int line_count=0;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();
            dialogList.append(line[line_count]);
        }
    }
    fTextes.close();

    QDomElement lvl_elements = doc.createElement("LEVEL_ELEMENT");

    levelName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"), "/", QObject::tr("Text files (*.cpp *.txt)"));
    QFile fLevel(levelName);

    int k = 0;

    if(fLevel.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&fLevel);
        t.setCodec("UTF-8");
        QString line[1000];
        QString s;
        int line_count=0;

        int matX, matY;
        QDomElement ligne;
        QDomElement colonne;
        QDomElement element;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();

            if(line[line_count].contains("[ennemi]"))
            {
                line_count++;
                line[line_count] = t.readLine();
                QStringList listEnnemi = line[line_count].split("//");

                for(int j = 0; j < listEnnemi.size(); j++)
                {
                    QStringList listPoint = listEnnemi.at(j).split(",");
                    QList<QPoint> listeDePoints;
                    for(int i = 0; i < listPoint.size(); i++)
                    {
                        QStringList point = listPoint.at(i).split("-");
                        listeDePoints.append(QPoint(point.at(0).toInt(),point.at(1).toInt()));
                    }
                    ennemi.append(listeDePoints);
                }
            }

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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"BLOC","type","WALL");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"BLOC","type","WALL");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"BLOC","type","MOVABLE");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
                        }
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }



            if(line[line_count].contains("type=Items"))
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"ITEM","type","ITEM");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
                        }
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"ITEM","type","BONUS");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));

                            QString type;
                            switch(values.at(matX).toInt())
                            {
                            case 1: type = "RENARD";
                            case 2: type = "LOUP";
                            default:break;
                            }

                            element = findElement(doc, colonne,"ENNEMI","type",type);

                            for (int i = 0; i < ennemi.at(k).size(); ++i) {
                                QDomElement deplacement = doc.createElement("MOVE");
                                deplacement.setAttribute("x",ennemi.at(k).at(i).x());
                                deplacement.setAttribute("y",ennemi.at(k).at(i).y());
                                deplacement.setAttribute("i",i+1);
                                element.appendChild(deplacement);
                            }

                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);

                            k++;
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"END","nextLevel",values.at(matX));
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
                        }
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Doors"))
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));

                            if(values.at(matX).toInt() > 20 && values.at(matX).toInt() < 30)
                            {
                                element = findElement(doc, colonne,"DOOR","item","Poisson");
                                element.setAttribute("nbItem",values.at(matX).toInt()%20);
                            }

                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
                        }
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"BLOC","type","WATER");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"BLOC","type","WALL");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"BLOC","type","SNOW");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"BLOC","type","ICE");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
                        }
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Item_Shoes"))
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"ITEM","type","shoes");
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
                        }
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Dialogs"))
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
                            ligne = findElement(doc, lvl_elements,"LIGNE","position",QString::number(matX));
                            colonne = findElement(doc, ligne,"COLONNE","position",QString::number(matY));
                            element = findElement(doc, colonne,"DIALOG","position",values.at(matX));
                            element.setAttribute("text",dialogList.at(values.at(matX).toInt()-1));
                            colonne.appendChild(element);
                            ligne.appendChild(colonne);
                            lvl_elements.appendChild(ligne);
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

    doc.appendChild(lvl_elements);
    QTextStream out(&fileWrite);
    out << doc.toString();

    return 0;
}
