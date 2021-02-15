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

//    butAdd = new QPushButton("Add");
//    butRem = new QPushButton("Rem");
//    butNew = new QPushButton("New");
//    butSkip = new QPushButton("Clear");

//    spinBox = new QSpinBox();
//    spinBox->setFixedSize(85,26);

    geo_type = new QComboBox();

    geo_type->addItem("GL_POINTS");
    geo_type->addItem("GL_LINES");
    geo_type->addItem("GL_LINE_STRIP");
    geo_type->addItem("GL_LINE_LOOP");
    geo_type->addItem("GL_TRIANGLES");
    geo_type->addItem("GL_TRIANGLE_STRIP");
    geo_type->addItem("GL_TRIANGLE_FAN");
    geo_type->addItem("GL_QUADS");
    geo_type->addItem("GL_QUAD_STRIP");
    geo_type->addItem("GL_POLYGON");
//    geo_type->addItem("Polygon");

    buttonslayout->addWidget(geo_type);
//    buttonslayout->addWidget(butNew);
//    buttonslayout->addWidget(butAdd);
//    buttonslayout->addWidget(butRem);
//    buttonslayout->addWidget(spinBox);
//    buttonslayout->addWidget(butSkip);

//    sideslayout->addWidget(cGL);
    vertlayout->addWidget(cGL);
    vertlayout->addLayout(buttonslayout);
    sideslayout->addLayout(vertlayout);

    central_widget->setLayout(sideslayout);
    setCentralWidget(central_widget);


//    ui->btnDraw->click();
    connect(geo_type,SIGNAL(currentIndexChanged(int)),cGL,SLOT(slSetGeometryType(int)));
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
