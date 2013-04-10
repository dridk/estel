#include <QtGui/QApplication>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <cmath>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "gene.h"
#include "genom.h"
#include "life.h"
#include "jsedit.h"
#include "lifeengineview.h"
#include "lifesview.h"
#include "genomview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setOrganizationDomain("labsquare.org");
    QCoreApplication::setApplicationName("ESTEL");
    QCoreApplication::setApplicationVersion("alpha 0.1");


    qsrand(QDateTime::currentDateTime ().toTime_t ());


    LifeEngine * engine = new LifeEngine;
    engine->addLife(new Life());
    engine->addLife(new Life(4,3));
    engine->addLife(new Life(14,3));



//    GenomView * gv = new GenomView(new Life);
//    gv->show();

    Life * life = new Life;
    life->addGene(Gene("sexe"));
    life->addGene(Gene("taille"));


    GeneDialog * g = new GeneDialog;
    g->show();



    //    // Show splash screen
    //    QSplashScreen splash(QPixmap(":/splash.png"));
    //    splash.setAttribute(Qt::WA_DeleteOnClose);
    //    splash.show();

    //    SimMainWindow * w = new SimMainWindow;
    //    w->show();

    //    w->show();
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
