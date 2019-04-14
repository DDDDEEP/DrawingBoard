#include <string>
#include <sstream>
#include <QPainter>
#include <QMouseEvent>
#include "global.h"
#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent),
    theImage(QImage(600, 300, QImage::Format_RGB32)),
    backgroundColor(qRgb(255,255,255)),
    thePen(Qt::black, 1, Qt::SolidLine),
    theBrush(Qt::transparent),
    thePaintType(PaintType::NONE),
    theScale(1),
    theShear(0),
    theAngle(0),
    modified(false),
    drawing(false),
    filling(false)
{
    theImage.fill(backgroundColor);
    this->setFixedSize(600, 300);
    setMouseTracking(true);
}

void BoardWidget::paint(QImage& qImage)
{
    QPainter painter(&qImage);
    painter.setPen(thePen);
    painter.setBrush(theBrush);
    int startX = static_cast<int>(startPoint.x() / theScale),
        startY = static_cast<int>(startPoint.y() / theScale),
        width = static_cast<int>((endPoint.x() - startX) / theScale),
        height = static_cast<int>((endPoint.y() - startY) / theScale); // 用于绘制特殊图形

    switch(thePaintType)
    {
    case PaintType::NONE:
        break;
    case PaintType::PENCIL:
        painter.drawLine(startPoint / theScale, endPoint / theScale);  // 由起始坐标和终止坐标绘制直线
        startPoint = endPoint; // 终点变成下次操作的起点
        break;
    case PaintType::ERASER:
    {
        QRect eraser = QRect(
                QPoint(startPoint.x() - halfEraserSize, startPoint.y() - halfEraserSize),
                QPoint(startPoint.x() + halfEraserSize, startPoint.y() + halfEraserSize)
            ); // 橡皮擦大小
        painter.eraseRect(eraser);
        startPoint = endPoint;
        break;
    }
    case PaintType::LINE:
        painter.drawLine(startPoint / theScale, endPoint / theScale);
        break;
    case PaintType::RECT:
        painter.drawRect(startX, startY, width, height);
        break;
    case PaintType::SQUARE:
        painter.drawRect(startX, startY, width, (height > 0) ? abs(width) : -abs(width));
        break;
    case PaintType::ELLIPSE:
        painter.drawEllipse(startX, startY, width, height);
        break;
    case PaintType::CIRCLE:
        painter.drawEllipse(startX, startY, width, (height > 0) ? abs(width) : -abs(width));
        break;
    }
    update(); // 更新界面，以此触发重绘事件
}

void BoardWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.scale(theScale, theScale);
    if (drawing) {
        // 如果正在绘制特殊图形，则显示临时绘图区上的内容
        painter.drawImage(0, 0, tempImage);
    } else {
        if (theShear != 0.0) {
            // 进行伸缩
            QImage shearImage = theImage;
            QPainter sharePainter(&shearImage);
            sharePainter.shear(theShear, theShear);
            sharePainter.drawImage(0, 0, theImage);
            theImage = shearImage;
            theShear = 0;
        }
        if (theAngle != 0) {
            // 进行旋转
            QImage rotateImage = theImage; // 旋转用的临时 Image
            QPainter rotatePainter(&rotateImage); // 旋转用的临时 Painter
            QPointF center(rotateImage.width() / 2.0, rotateImage.height() / 2.0);
            rotatePainter.translate(center);
            rotatePainter.rotate(theAngle);
            rotatePainter.translate(-center);
            rotatePainter.drawImage(0, 0, theImage); // 将原图片写入变换用的 Painter
            theImage = rotateImage;  // 复制变换后的图片
            theAngle = 0; // 完成旋转后将角度值重新设为 0
        }
        painter.drawImage(0, 0, theImage);
    }
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        drawing = true;
    }
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        endPoint = event->pos();
        if (thePaintType == NONE || thePaintType == PENCIL
                || thePaintType == ERASER)  {
            // 随着鼠标移动实际绘制的操作
            drawing = false;
            paint(theImage);
        } else {
            // 随着鼠标移动临时绘制的操作
            tempImage = theImage;
            paint(tempImage);
        }
    }
    std::ostringstream message;
    message << "(" << event->pos().x() << ", " << event->pos().y() << ")";
    statusEvent(QString::fromStdString(message.str()));
}

void BoardWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        drawing = false;
        paint(theImage);
    }
}
