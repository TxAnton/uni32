#ifndef CUSTOMGL_H
#define CUSTOMGL_H
//#include <typeinfo>

#include <cmath>
#include <cassert>
#include <vector>
#include <tuple>

#include <QObject>
#include <QWidget>

#include <QtOpenGL>
#include <QDebug>

#include "interpolator.h"

typedef std::pair<double,double> CPoint;

class CustomGL : public QGLWidget
{
  Q_OBJECT

typedef std::tuple<float, float, float>  clr_t;

private:
    int steps = 60;
    Interpolator* interp;
    int w=1,h=1;
    std::vector<std::pair<double,double> > pts;
    std::vector<clr_t> colors;

    int geomType = GL_POINTS;
    int alphaType = GL_NEVER;
    float alphaVal = 0;
    float xSc = 0;
    float ySc = 0;

    int sfactorType = GL_SRC_COLOR;
    int dfactorType = GL_SRC_COLOR;

    // Interaction

//    std::vector<CPoint> pts;
    int cur_dot;                                    //индекс в векторе перемещаемой точки

    int count_dots;
    int d_size = 15;                                     //координаты и размер точки
    int l_size = 10;                                     //координаты и размер точки

    int mouse_x, mouse_y;                           //координаты мыши
    bool dot_move = false;                          //сдвигаем точку?

    std::pair<double,double> _coordScreenToGl(int x, int y);
    std::pair<int,int> _coordGlToScreen(double x, double y);
#define _ABS(_X)        ( (_X)<0?-(_X):(_X) )
#define _GL_TO_SC_X(_X) ( (int)  (_ABS((_X)) / 2.0f * w) )
#define _GL_TO_SC_Y(_Y) ( (int)  (_ABS((_Y)) / 2.0f * h) )
#define _SC_TO_GL_X(_X) ( (double)     (_ABS((_X)) / ((double)w) * 2.0f) )
#define _SC_TO_GL_Y(_Y) ( (double)     (_ABS((_Y)) / ((double)h) * 2.0f) )

public slots:
    void slSetGeometryType(int typ = GL_POINTS);
    void slSetAlphaType(int typ = GL_NEVER);
    void slSetAlphaVal(int value = 0);
    void slSetScX(int value = 0);
    void slSetScY(int value = 0);

    void slSetSfactorType(int typ = GL_SRC_COLOR);
    void slSetDfactorType(int typ = GL_SRC_COLOR);


public:
    bool checkPressOnDot(double x, double y);

    void mousePressEvent(QMouseEvent *event) override;      //зажали клавишу мыши
    void mouseReleaseEvent(QMouseEvent *event) override;    //отпустили клавишу мыши
    void mouseMoveEvent(QMouseEvent *event) override;       //перемещение с зажатой клавишей мыши

    CustomGL();
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void scene();

    void drawGeometry(int typ);
//    void drawPoint();
//    void drawLines();
//    void drawLineStrip();
//    void drawLineLoop();
//    void drawTriangles();
//    void drawTriangleStrip();
//    void drawTriangleFan();
//    void drawQuads();
//    void drawQuadStrip();
//    void drawPolygon();

};

#endif // CUSTOMGL_H
