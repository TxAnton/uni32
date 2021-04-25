#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QSplitter>
#include <QCheckBox>

#include "customgl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CustomGL* cGL;
    QPushButton *m_button;

    QHBoxLayout *sideslayout;
    QVBoxLayout *vertlayout;

    QVBoxLayout *buttonslayout;

    QWidget *central_widget;

//    QSlider* n_seg_slider;

    QTimer *timer;

};

#endif // MAINWINDOW_H
