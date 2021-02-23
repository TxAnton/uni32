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

    central_widget = new QWidget;

    cGL = new CustomGL();
    cGL->slSetGeometryType(GL_POINTS);
//    graphicsView = new GraphGraphicView();
//    listViewAL = new ListViewActionLogger();
/*
//    butAdd = new QPushButton("Add");
//    butRem = new QPushButton("Rem");
//    butNew = new QPushButton("New");
//    butSkip = new QPushButton("Clear");

//    spinBox = new QSpinBox();
//    spinBox->setFixedSize(85,26);
    */
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
    /*
#define GL_POINTS				0x0000
#define GL_LINES				0x0001
#define GL_LINE_LOOP				0x0002
#define GL_LINE_STRIP				0x0003
#define GL_TRIANGLES				0x0004
#define GL_TRIANGLE_STRIP			0x0005
#define GL_TRIANGLE_FAN				0x0006
#define GL_QUADS				0x0007
#define GL_QUAD_STRIP				0x0008
#define GL_POLYGON				0x0009
    */
//    geo_type->addItem("Polygon");

    buttonslayout->addWidget(geo_type);

    connect(geo_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetGeometryType(int)));
//    buttonslayout->addWidget(butNew);
//    buttonslayout->addWidget(butAdd);
//    buttonslayout->addWidget(butRem);
//    buttonslayout->addWidget(spinBox);
//    buttonslayout->addWidget(butSkip);

    //ALPHA
    alpha_type = new QComboBox();

    alpha_type->addItem("GL_NEVER");
    alpha_type->addItem("GL_LESS");
    alpha_type->addItem("GL_EQUAL");
    alpha_type->addItem("GL_LEQUAL");
    alpha_type->addItem("GL_GREATER");
    alpha_type->addItem("GL_NOTEQUAL");
    alpha_type->addItem("GL_GEQUAL");
    alpha_type->addItem("GL_ALWAYS");

    alpha_slider = new QSlider(Qt::Horizontal, this);

    controlslayout  = new QVBoxLayout;
    controlslayout->addWidget(this->alpha_type);
    controlslayout->addWidget(this->alpha_slider);





    connect(alpha_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetAlphaType(int)));

    connect(alpha_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetAlphaVal(int)));


    /*
        #define GL_NEVER				0x0200
        #define GL_LESS					0x0201
        #define GL_EQUAL				0x0202
        #define GL_LEQUAL				0x0203
        #define GL_GREATER				0x0204
        #define GL_NOTEQUAL				0x0205
        #define GL_GEQUAL				0x0206
        #define GL_ALWAYS				0x0207
    */
    //SCISSORS
    sc_x_slider = new QSlider(Qt::Horizontal, this);
    sc_y_slider = new QSlider(Qt::Horizontal, this);

    controlslayout->addWidget(this->sc_x_slider);
    controlslayout->addWidget(this->sc_y_slider);

    connect(sc_x_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetScX(int)));
    connect(sc_y_slider,SIGNAL(valueChanged(int)),cGL,SLOT(slSetScY(int)));

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



    /*
#define GL_ZERO					0
#define GL_ONE					1
#define GL_SRC_COLOR				0x0300
#define GL_ONE_MINUS_SRC_COLOR			0x0301
#define GL_SRC_ALPHA				0x0302
#define GL_ONE_MINUS_SRC_ALPHA			0x0303
#define GL_DST_ALPHA				0x0304
#define GL_ONE_MINUS_DST_ALPHA			0x0305
#define GL_DST_COLOR				0x0306
#define GL_ONE_MINUS_DST_COLOR			0x0307
#define GL_SRC_ALPHA_SATURATE			0x0308
    */

    vertlayout->addWidget(cGL);
    vertlayout->addLayout(buttonslayout);
//    vertlayout->addLayout(controlslayout);
    sideslayout->addLayout(vertlayout);
    sideslayout->addLayout(controlslayout);

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
