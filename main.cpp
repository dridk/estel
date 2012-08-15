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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime ().toTime_t ());

    LifeEditor * editor = new LifeEditor;

    editor->show();



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
