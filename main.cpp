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
#include "lifeeditor.h"
#include "jsedit.h"
#include "simmainwindow.h"
#include "actionlistview.h"
#include "lifefileview.h"
#include "lifesview.h"
#include "genecolorwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime ().toTime_t ());

    SimMainWindow * w = new SimMainWindow;
    w->show();

//    Gene g = 14;
//    GeneDialog * d = new GeneDialog;
//    d->setGene(g);
//    d->show();

//    Gene gene;
//    gene.setRootColor("red");

//    GeneColorWidget * w = new GeneColorWidget(gene);
//    w->show();



            //        LifeEngine * engine =new LifeEngine(100,100);
            //        engine->load("/home/sacha/simtest.estel");



            //       LifesView * v = new LifesView(engine);
            //        v->show();


            //    view->show();





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
