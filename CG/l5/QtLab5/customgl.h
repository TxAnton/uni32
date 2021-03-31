#ifndef CUSTOMGL_H
#define CUSTOMGL_H
//#include <typeinfo>



#include <cmath>
#include <cassert>
#include <vector>
#include <tuple>
#include <ctime>
#include<fstream>

#include <QObject>
#include <QWidget>


#include <QtOpenGL>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QDebug>

#include <GL/glu.h>


//#include "interpolator.h"
//#include "l_system.h"



typedef std::pair<double,double> CPoint;

class CustomGL : public QGLWidget
{
  Q_OBJECT

typedef std::tuple<float, float, float>  clr_t;

private:

    unsigned int texture_n;
    int texwidth, texheight, texnrChannels;
    unsigned char *texdata;
    GLfloat texoffset;

    QGLShaderProgram* shaderProgram;

    double cameraX = 0,cameraY = 0,cameraZ = 0;

    QMatrix4x4 pmvMatrix;

    double alpha = 0;
    double theta = 0;

    int w=1,h=1;

    int nSegments = 0;

    int d_size = 15;                                     //координаты и размер точки
    float l_size = 10;                                     //координаты и размер точки

    double pressX=0, pressY=0;
    double cameraDistance = .1;
//    int mouse_x, mouse_y;                           //координаты мыши

    std::pair<double,double> _coordScreenToGl(int x, int y);
    std::pair<int,int> _coordGlToScreen(double x, double y);
#define _ABS(_X)        ( (_X)<0?-(_X):(_X) )
#define _GL_TO_SC_X(_X) ( (int)  (_ABS((_X)) / 2.0f * w) )
#define _GL_TO_SC_Y(_Y) ( (int)  (_ABS((_Y)) / 2.0f * h) )
#define _SC_TO_GL_X(_X) ( (double)     (_ABS((_X)) / ((double)w) * 2.0f) )
#define _SC_TO_GL_Y(_Y) ( (double)     (_ABS((_Y)) / ((double)h) * 2.0f) )

public slots:
    void slSetNSegments(int value = 0);
    void slTimerUpdate();

public:

    void mousePressEvent(QMouseEvent *event) override;      //зажали клавишу мыши
    void mouseReleaseEvent(QMouseEvent *event) override;    //отпустили клавишу мыши
    void mouseMoveEvent(QMouseEvent *event) override;       //перемещение с зажатой клавишей мыши
    void wheelEvent(QWheelEvent *event);
    CustomGL();
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void scene();

    void drawSquare();
    void drawGeometry();

    void initShaders();

    std::string readFile(std::string filename);
};

#endif // CUSTOMGL_H
