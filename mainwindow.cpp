﻿#include <string>
#include <sstream>
#include <QDebug>
#include <QLabel>
#include <QSpinBox>
#include <QColorDialog>
#include "boardwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    labelPermanent(nullptr),
    labelText(nullptr),
    spinBoxColor(nullptr)
{
    ui->setupUi(this);
    this->createMainToolBar(); // 动态创建部分工具栏内容
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true); // 开启鼠标追踪

    // 更新状态栏窗口大小信息
    std::ostringstream message;
    message << ui->boardWidget->width() << " x " << ui->boardWidget->height();
    setPermanentMessage(QString::fromStdString(message.str()));

    connect(spinBoxColor, SIGNAL(valueChanged(int)), this, SLOT(custom_spinBoxColor_valueChanged(int)));
    connect(ui->boardWidget, SIGNAL(statusEvent(QString)), this, SLOT(setStatusBarText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete labelPermanent;
    delete labelText;
    delete spinBoxColor;
}

void MainWindow::createMainToolBar()
{
    labelText = new QLabel;
    labelText->setText(QStringLiteral("线条大小:"));
    labelText->setIndent(10);
    ui->mainToolBar->addWidget(labelText);

    spinBoxColor = new QSpinBox;
    spinBoxColor->setRange(1, 10);
    spinBoxColor->setFixedWidth(50);
    ui->mainToolBar->addWidget(spinBoxColor);
}

void MainWindow::resetActionTool()
{

    switch(ui->boardWidget->paintType())
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
        this->setCursor(Qt::ArrowCursor);
        break;
    case PaintType::FILL:
        ui->actFill->setChecked(false);
        break;
    }
}

void MainWindow::setPermanentMessage(const QString &s)
{
    if (labelPermanent == nullptr) {
        labelPermanent = new QLabel;
        ui->statusBar->addPermanentWidget(labelPermanent);
    }
    labelPermanent->setText(s);
}

void MainWindow::on_actPencil_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::PENCIL);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actEraser_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::ERASER);
        QPixmap pixmap(":/img/img/cursor_erase.png");
        pixmap = pixmap.scaled(BoardWidget::halfEraserSize * 2, BoardWidget::halfEraserSize * 2);

        QCursor cursor = QCursor(pixmap, BoardWidget::halfEraserSize, BoardWidget::halfEraserSize);
        this->setCursor(cursor);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actLine_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::LINE);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actEllipse_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::ELLIPSE);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actCircle_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::CIRCLE);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actRect_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::RECT);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actSquare_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::SQUARE);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::on_actColor_triggered(bool)
{
    QColorDialog color;
    ui->boardWidget->setPenColor(color.getRgba());
}

void MainWindow::on_actFill_triggered(bool checked)
{
    if (checked) {
        resetActionTool();
        ui->boardWidget->setPaintType(PaintType::FILL);
    } else {
        ui->boardWidget->setPaintType(PaintType::NONE);
    }
}

void MainWindow::custom_spinBoxColor_valueChanged(int value)
{
    ui->boardWidget->setPenWidth(value);
}

void MainWindow::setStatusBarText(const QString& s)
{
    statusBar()->showMessage(s);
}

void MainWindow::on_actSaveFile_triggered(bool)
{
    ui->boardWidget->saveImage();
}

void MainWindow::on_actOpenFile_triggered(bool)
{
    ui->boardWidget->openImage();
}

void MainWindow::on_actUndo_triggered(bool)
{
    ui->boardWidget->Undo();
}

void MainWindow::on_actRedo_triggered(bool)
{
    ui->boardWidget->Redo();
}


void MainWindow::on_actNewFile_triggered(bool)
{

    ui->boardWidget->newFile();
}



void MainWindow::on_actionactInvert_triggered(bool)
{
    ui->boardWidget->invert();
}

void MainWindow::on_actionactGray_triggered(bool)
{
    ui->boardWidget->gray();
}

void MainWindow::on_actionactMosaic_triggered(bool)
{
    ui->boardWidget->mosaic();
}
