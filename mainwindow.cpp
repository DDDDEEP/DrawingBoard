#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->actPencil, SIGNAL(triggered(bool)), this, SLOT(on_actPencil_triggered(bool)));
//    connect(ui->actLine, SIGNAL(triggered(bool)), this, SLOT(on_actLine_triggered(bool)));
//    connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(handleToolBar(QAction*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetActionTool()
{
    switch(ui->board->getPaintType())
    {
    case PaintType::NONE:
        break;
    case PaintType::PENCIL:
        ui->actPencil->setChecked(false);
        break;
    case PaintType::LINE:
        ui->actLine->setChecked(false);
        break;
    case PaintType::ELLIPSE:
        ui->actEllipse->setChecked(false);
        break;
    case PaintType::CIRCLE:
        ui->actCircle->setChecked(false);
        break;
    case PaintType::RECT:
        ui->actRect->setChecked(false);
        break;
    case PaintType::SQUARE:
        ui->actSquare->setChecked(false);
        break;
    case PaintType::ERASER:
        ui->actEraser->setChecked(false);
        break;
    default:
        break;
    }
}

void MainWindow::on_actPencil_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->board->setPaintType(PaintType::PENCIL);
    } else {
        ui->board->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actEraser_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->board->setPaintType(PaintType::ERASER);
    } else {
        ui->board->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actLine_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->board->setPaintType(PaintType::LINE);
    } else {
        ui->board->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actEllipse_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->board->setPaintType(PaintType::ELLIPSE);
    } else {
        ui->board->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actCircle_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->board->setPaintType(PaintType::CIRCLE);
    } else {
        ui->board->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actRect_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->board->setPaintType(PaintType::RECT);
    } else {
        ui->board->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actSquare_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->board->setPaintType(PaintType::SQUARE);
    } else {
        ui->board->setPaintType(PaintType::NONE);
    }
}
