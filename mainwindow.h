#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>

// 绘制类型
enum PaintType
{
    NONE,
    PENCIL,
    LINE,
    ELLIPSE,
    CIRCLE,
    RECT,
    SQUARE,
    ERASER
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    
    void resetActionTool(); // 重置当前所选的工具按钮

private slots:
    void on_actPencil_triggered(bool);
    void on_actEraser_triggered(bool);
    void on_actLine_triggered(bool);
    void on_actEllipse_triggered(bool);
    void on_actCircle_triggered(bool);
    void on_actRect_triggered(bool);
    void on_actSquare_triggered(bool);

};

#endif // MAINWINDOW_H
