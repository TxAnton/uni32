#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Maksimova, Larin 8383");
    sideslayout = new QHBoxLayout;
    vertlayout  = new QVBoxLayout;

    buttonslayout = new QHBoxLayout;
    central_widget = new QWidget;

    cGL = new CustomGL();

    sc_x_slider = new QSlider(Qt::Horizontal, this);
    buttonslayout->addWidget(this->sc_x_slider);
    connect(sc_x_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetNSegments(int)));

    vertlayout->addWidget(cGL);
    vertlayout->addLayout(buttonslayout);
    sideslayout->addLayout(vertlayout);


    central_widget->setLayout(sideslayout);
    setCentralWidget(central_widget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

