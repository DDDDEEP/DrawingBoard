#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <stack>
#include "global.h"

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = nullptr);

    int penWidth() const { return thePen.width(); }
    void setPenWidth(int width) { thePen.setWidth(width); }

    QColor penColor() const { return thePen.color(); }
    void setPenColor(const QColor& color) { thePen.setColor(color); }

    void setBrushMode(bool toFillMode)
    {
        filling = toFillMode;
        theBrush.setColor(toFillMode ? thePen.color() : Qt::transparent);
    }

    Qt::PenStyle penStyle() const { return thePen.style(); }
    void setPenStyle(const Qt::PenStyle& style){ thePen.setStyle(style); }

    PaintType paintType() const { return thePaintType; }
    void setPaintType(const PaintType& type) { thePaintType = type; }

    void fillColor(const QPoint &point); // 油漆桶功能
    void saveImage();                    // 保存绘制图像
    void openImage();                    // 打开已有的图像
    void Undo();                         // 撤回上一步绘制操作
    void Redo();

protected:
    void paint(QImage&);                  // 手动调用的绘制函数
    void paintEvent(QPaintEvent*);        // 重绘事件
    void mousePressEvent(QMouseEvent*);   // 鼠标按下事件
    void mouseMoveEvent(QMouseEvent*);    // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent*); // 鼠标释放事件


private:
    const int halfEraserSize = 8;

    QImage theImage;             // 绘图对象
    QImage tempImage;            // 临时绘图区，用于需要临时显示绘制效果的操作，如特殊图形的绘制
    QRgb backgroundColor;        // 画布背景色
    QPoint startPoint, endPoint; // 鼠标操作的前后两个点

    QPen thePen;            // 画笔
    QBrush theBrush;        // 画刷
    PaintType thePaintType; // 绘制类型

    qreal theScale; // 缩放比例
    qreal theShear; // 拉伸量
    int theAngle;   // 旋转角度，顺时针为正

    bool modified; // 文件是否被修改
    bool drawing;  // 是否正在绘制
    bool filling;  // 是否为填充模式
    bool pressing; // 鼠标是否按下去

    std::stack<QImage> history_undo;
    std::stack<QImage> history_redo;


signals:
    void statusEvent(const QString&);

public slots:
};

#endif // BOARDWIDGET_H
