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



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime ().toTime_t ());



      Life * life = new Life(5,5);

      life->addGene(Gene("taux"));
      life->addGene(Gene("color"));
      life->addGene(Gene("radius"));



      life->gene("taux").setMutationProbability(0.9);
      life->gene("taux").setVariance(1);




      LifeEngine engine(100,100);

      engine.addLife(life);

     engine.run(10);







    
    return a.exec();
}
