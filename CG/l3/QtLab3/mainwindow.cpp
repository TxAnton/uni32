#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Larin 8383");
    sideslayout = new QHBoxLayout;
    vertlayout  = new QVBoxLayout;

    buttonslayout = new QHBoxLayout;
    controlslayout  = new QVBoxLayout;
    central_widget = new QWidget;

    cGL = new CustomGL();
    cGL->slSetGeometryType(GL_POINTS);

    //GEO
    geo_type = new QComboBox();

    geo_type->addItem("GL_POINTS");
    geo_type->addItem("GL_LINES");
    geo_type->addItem("GL_LINE_LOOP");
    geo_type->addItem("GL_LINE_STRIP");
    geo_type->addItem("GL_TRIANGLES");
    geo_type->addItem("GL_TRIANGLE_STRIP");
    geo_type->addItem("GL_TRIANGLE_FAN");
    geo_type->addItem("GL_QUADS");
    geo_type->addItem("GL_QUAD_STRIP");
    geo_type->addItem("GL_POLYGON");

    buttonslayout->addWidget(geo_type);

    connect(geo_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetGeometryType(int)));


//    buttonslayout->addWidget(butNew);
//    buttonslayout->addWidget(butAdd);
//    buttonslayout->addWidget(butRem);
//    buttonslayout->addWidget(spinBox);
//    buttonslayout->addWidget(butSkip);
/*
    //ALPHA
    alpha_type = new QComboBox();

    geo_type->addItem("GL_POINTS");
    geo_type->addItem("GL_LINES");
    geo_type->addItem("GL_LINE_LOOP");
    geo_type->addItem("GL_LINE_STRIP");
    geo_type->addItem("GL_TRIANGLES");
    geo_type->addItem("GL_TRIANGLE_STRIP");
    geo_type->addItem("GL_TRIANGLE_FAN");
    geo_type->addItem("GL_QUADS");
    geo_type->addItem("GL_QUAD_STRIP");
    geo_type->addItem("GL_POLYGON");

    buttonslayout->addWidget(geo_type);

    connect(geo_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetGeometryType(int)));
*/
 /*
    alpha_type->addItem("GL_NEVER");
    alpha_type->addItem("GL_LESS");
    alpha_type->addItem("GL_EQUAL");
    alpha_type->addItem("GL_LEQUAL");
    alpha_type->addItem("GL_GREATER");
    alpha_type->addItem("GL_NOTEQUAL");
    alpha_type->addItem("GL_GEQUAL");
    alpha_type->addItem("GL_ALWAYS");

    alpha_slider = new QSlider(Qt::Horizontal, this);


    controlslayout->addWidget(this->alpha_type);
    controlslayout->addWidget(this->alpha_slider);

    connect(alpha_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetAlphaType(int)));
    connect(alpha_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetAlphaVal(int)));
*/
/*
    //SCISSORS
    sc_x_slider = new QSlider(Qt::Horizontal, this);
    sc_y_slider = new QSlider(Qt::Horizontal, this);

    controlslayout->addWidget(this->sc_x_slider);
    controlslayout->addWidget(this->sc_y_slider);

    connect(sc_x_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetScX(int)));
    connect(sc_y_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetScY(int)));
*/
/*
    //BLEND

    sfactor_type = new QComboBox();
    dfactor_type = new QComboBox();

    GL_SRC_ALPHA;
    sfactor_type->addItem("GL_SRC_COLOR");
    sfactor_type->addItem("GL_ONE_MINUS_SRC_COLOR");
    sfactor_type->addItem("GL_SRC_ALPHA");
    sfactor_type->addItem("GL_ONE_MINUS_SRC_ALPHA");
    sfactor_type->addItem("GL_DST_ALPHA");
    sfactor_type->addItem("GL_ONE_MINUS_DST_ALPHA");
    sfactor_type->addItem("GL_DST_ALPHA");
    sfactor_type->addItem("GL_ONE_MINUS_DST_ALPHA");
    sfactor_type->addItem("GL_DST_COLOR");
    sfactor_type->addItem("GL_ONE_MINUS_DST_COLOR");
    sfactor_type->addItem("GL_SRC_ALPHA_SATURATE");
    sfactor_type->addItem("GL_ZERO");
    sfactor_type->addItem("GL_ONE");

    dfactor_type->addItem("GL_SRC_COLOR");
    dfactor_type->addItem("GL_ONE_MINUS_SRC_COLOR");
    dfactor_type->addItem("GL_SRC_ALPHA");
    dfactor_type->addItem("GL_ONE_MINUS_SRC_ALPHA");
    dfactor_type->addItem("GL_DST_ALPHA");
    dfactor_type->addItem("GL_ONE_MINUS_DST_ALPHA");
    dfactor_type->addItem("GL_DST_ALPHA");
    dfactor_type->addItem("GL_ONE_MINUS_DST_ALPHA");
    dfactor_type->addItem("GL_DST_COLOR");
    dfactor_type->addItem("GL_ONE_MINUS_DST_COLOR");
    dfactor_type->addItem("GL_SRC_ALPHA_SATURATE");
    dfactor_type->addItem("GL_ZERO");
    dfactor_type->addItem("GL_ONE");

    controlslayout->addWidget(this->sfactor_type);
    controlslayout->addWidget(this->dfactor_type);

    connect(sfactor_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetSfactorType(int)));
    connect(dfactor_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetDfactorType(int)));
*/

    vertlayout->addWidget(cGL);
    vertlayout->addLayout(buttonslayout);
//    vertlayout->addLayout(controlslayout);
    sideslayout->addLayout(vertlayout);
//    sideslayout->addLayout(controlslayout);

    central_widget->setLayout(sideslayout);
    setCentralWidget(central_widget);


//    ui->btnDraw->click();

//    connect(this->geo_type, &QComboBox::currentIndexChanged(int), cGL, &CustomGL::slSetGeometryType(int));
//    connect(ui->btnDraw, &QPushButton::released, this, &MainWindow::handleButton);



//    m_button = new QPushButton("My Button", this);
//    // set size and location of the button
//    m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

//    // Connect button signal to appropriate slot
//    connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);

//    cGL = new CustomGL();
//    QGLWidget;
//    QOpenGLWidget;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    cGL->show();
    m_button->setText("Example");
    // resize button
    m_button->resize(100,100);
}
