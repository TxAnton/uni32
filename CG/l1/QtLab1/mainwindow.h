#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

    QPixmap stdPixmap;
    QListView *lstVw;
//    ListViewActionLogger* listViewAL;
    QPushButton* butNew;
    QPushButton* butAdd;
    QPushButton* butRem;
    QPushButton* butSkip;

    QSpinBox* spinBox;

    QComboBox* geo_type;

private slots:
  void handleButton();

};

#endif // MAINWINDOW_H
