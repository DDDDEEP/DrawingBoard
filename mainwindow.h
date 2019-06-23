#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QLabel>
#include <QSpinBox>
#include <QMainWindow>
#include "global.h"

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

    void createMainToolBar();                 // ui编辑器下只能向主工具栏添加action，其它组件主要动态添加
    void resetActionTool();                   // 重置当前所选的工具按钮
    void setPermanentMessage(const QString&); // 设置状态栏的永久信息

    QLabel* labelPermanent; // 状态栏右下角永久信息
    QLabel* labelText;      // 字体大小标签
    QSpinBox* spinBoxColor; // 字体大小改变框


private slots:
    void on_actPencil_triggered(bool);
    void on_actEraser_triggered(bool);
    void on_actLine_triggered(bool);
    void on_actEllipse_triggered(bool);
    void on_actCircle_triggered(bool);
    void on_actRect_triggered(bool);
    void on_actSquare_triggered(bool);
    void on_actColor_triggered(bool);
    void on_actFill_triggered(bool);
    void on_actSaveFile_triggered(bool);
    void on_actOpenFile_triggered(bool);
    void on_actUndo_triggered(bool);
    void on_actRedo_triggered(bool);
    void on_actNewFile_triggered(bool checked);
    void custom_spinBoxColor_valueChanged(int);

    void setStatusBarText(const QString&); // 子组件改变状态栏的接口



    void on_actionactInvert_triggered(bool checked);
    void on_actionactGray_triggered(bool checked);
    void on_actionactMosaic_triggered(bool checked);
};

#endif // MAINWINDOW_H
