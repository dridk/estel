#include "shapewidget.h"
#include "ui_shapewidget.h"

ShapeWidget::ShapeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeWidget)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene;
    mShape = new MetaPolygonItem;
    mScene->addItem(mShape);
    ui->graphicsView->setScene(mScene);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            this,SLOT(set()));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),
            this,SLOT(set()));
}

ShapeWidget::~ShapeWidget()
{
    delete ui;
}

void ShapeWidget::set()
{

    mShape->setShape(ui->horizontalSlider->value(),
                     ui->horizontalSlider_2->value());

}
