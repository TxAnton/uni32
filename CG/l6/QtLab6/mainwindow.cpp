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

    buttonslayout = new QVBoxLayout;
    central_widget = new QWidget;

    cGL = new CustomGL();


    //--------
    //create sliders
    auto wf_check = new QCheckBox(this);
    auto fr_check = new QCheckBox(this);

    auto n_seg_slider = new QSlider(Qt::Horizontal, this);
    auto ss_slider = new QSlider(Qt::Horizontal, this);

    auto eu_x_slider = new QSlider(Qt::Horizontal, this);
    auto eu_y_slider = new QSlider(Qt::Horizontal, this);
    auto eu_z_slider = new QSlider(Qt::Horizontal, this);

    auto tr_x_slider = new QSlider(Qt::Horizontal, this);
    auto tr_y_slider = new QSlider(Qt::Horizontal, this);
    auto tr_z_slider = new QSlider(Qt::Horizontal, this);

    auto sc_x_slider = new QSlider(Qt::Horizontal, this);
    auto sc_y_slider = new QSlider(Qt::Horizontal, this);
    auto sc_z_slider = new QSlider(Qt::Horizontal, this);



    //--------
    //add sliders
    buttonslayout->addWidget(n_seg_slider);
    buttonslayout->addWidget(ss_slider);
//    buttonslayout->addWidget(new QSplitter(Qt::Horizontal));
    buttonslayout->addWidget(eu_x_slider);
    buttonslayout->addWidget(eu_y_slider);
    buttonslayout->addWidget(eu_z_slider);
    buttonslayout->addWidget(wf_check);
    buttonslayout->addWidget(tr_x_slider);
    buttonslayout->addWidget(tr_y_slider);
    buttonslayout->addWidget(tr_z_slider);
    buttonslayout->addWidget(fr_check);
    buttonslayout->addWidget(sc_x_slider);
    buttonslayout->addWidget(sc_y_slider);
    buttonslayout->addWidget(sc_z_slider);
    //--------
    //connect sliders
    connect(wf_check,SIGNAL(clicked(bool)),cGL,SLOT(slSetWireframe(bool)));
    connect(fr_check,SIGNAL(clicked(bool)),cGL,SLOT(slSetFrustum(bool)));

    connect(n_seg_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetNSegments(int)));

    connect(ss_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetSS(int)));



    connect(eu_x_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetEulerX(int)));
    connect(eu_y_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetEulerY(int)));
    connect(eu_z_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetEulerZ(int)));

    connect(tr_x_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetTrX(int)));
    connect(tr_y_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetTrY(int)));
    connect(tr_z_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetTrZ(int)));

    connect(sc_x_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetScX(int)));
    connect(sc_y_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetScY(int)));
    connect(sc_z_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetScZ(int)));



    //--------

    timer = new QTimer(this);
//    connect(timer, SIGNAL(QTimer::timeout(QPrivateSignal)), cGL, SLOT(slTimerUpdate(QPrivateSignal)));
    connect(timer, &QTimer::timeout, cGL, &CustomGL::slTimerUpdate);
//    timer->start(20);

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

