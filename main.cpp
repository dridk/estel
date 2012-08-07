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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime ().toTime_t ());


    Life * life = new Life(0,0);
    Gene g1("g1");
    Gene g2("g2");

    g1.setMutationProbability(0.5);
    g2.setMutationProbability(0.2);
    g1.setVariance(5);
    g2.setVariance(20);

    life->addGene(g1);
    life->addGene(g2);



  LifeEngine engine(100,100);

//    engine.addLife(life);
//    engine.run(1000);



    engine.load("experimentA-10.json");

    LifeEngineView * view = new LifeEngineView(&engine);


    view->show();



    
    return a.exec();
}
