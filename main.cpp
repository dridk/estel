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



    ScriptLife * l = new ScriptLife;
    l->addGene(Gene("g1",50,0,100,2,0.5));
    l->addGene(Gene("g2",50,0,100,2,0.5));
    l->setScript("lifescript.js");



    LifeEngine engine(100,100);
    engine.addLife(l);
    engine.addLife(l2);

//    engine.addLife(l->muted());
//    engine.addLife(l->muted());
    engine.run(10);



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
