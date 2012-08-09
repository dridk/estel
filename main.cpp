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
#include "lifeengineview.h"
#include "shapewidget.h"
#include "lifedialog.h"
#include "scriptlife.h"
#include "lifetypewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime ().toTime_t ());


    Life * life = new Life(0,0);

    life->addGene( Gene("test"));
    life->addGene( Gene("taux"));
    life->addGene( Gene("g1"));
    life->addGene( Gene("g2"));
    life->addGene( Gene("g3"));
    life->addGene( Gene("g4"));


    life->gene("test").setValue(2);
  life->gene("taux").setValue(16);

 qDebug()<< life->genom().identity();




//    engine.run(5);



    //    engine.load("experimentA-14.json");

    //    LifeEngineView * view = new LifeEngineView(&engine);


    //    view->show();


    //  LifeDialog * dialog = new LifeDialog(life);

    //  dialog->exec();


    //  life->genom().debug();

    //ShapeWidget * w = new ShapeWidget;

    //w->show();

    
    return a.exec();
}
