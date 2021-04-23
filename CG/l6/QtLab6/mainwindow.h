#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>


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

    QHBoxLayout *buttonslayout;

    QWidget *central_widget;

    QSlider* sc_x_slider;

    QTimer *timer;

};

#endif // MAINWINDOW_H
