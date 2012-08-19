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
#include "animmainwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QDateTime::currentDateTime ().toTime_t ());


    //    LifeEditor * editor = new LifeEditor;
    //    editor->show();


    // Show splash screen
    QSplashScreen splash(QPixmap(":/splash.png"));
    splash.show();


    // Create main windows
    SimMainWindow * m  = new SimMainWindow;
    m->show();



//    AnimMainWindow * w  =new AnimMainWindow;

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


    // Hide splash screen
    // ikit: commenté car sinon on ne le voit pas :)
    //splash.finish(m);
    
    return a.exec();
}
