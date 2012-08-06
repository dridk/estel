#include <QtGui/QApplication>
#include <QDebug>
#include <QDateTime>

#include "gene.h"
#include "genom.h"
#include "life.h"
#include <cmath>
#include "lifeengine.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "shapewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime ().toTime_t ());

    ShapeWidget * widget = new ShapeWidget;
    widget->show();
    //    LifeEngine engine(100,100);
    //    Life * b = new Life;




    //    engine.addLife(b);
    //    engine.setFileName("simulationTest.json");

    //    qDebug()<<engine.count();
    //    engine.run(20);
    //    qDebug()<<engine.count();



    
    return a.exec();
}
