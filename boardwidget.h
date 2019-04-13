#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QDebug>

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = nullptr);
    int getPaintType() { return paintType; }
    void setPaintType(int type) { this->paintType = type; }
private:
    int paintType;
signals:

public slots:
};

#endif // BOARDWIDGET_H
