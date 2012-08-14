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
#include "lifetypewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime ().toTime_t ());

    Life * life = new Life(0,0);

    life->addGene(Gene("g1"));
    life->addGene(Gene("g2"));
    life->loadScript("/home/sacha/devel/estel/life.js");

    LifeEngine engine(100,100);
    engine.addLife(life);




//    engine.addLife(l->muted());
//    engine.addLife(l->muted());
//    engine.run(20000);



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
