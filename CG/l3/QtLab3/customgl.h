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
    Interpolator* interp;
    int steps = 60;
    int w=1,h=1;
    std::vector<std::pair<double,double> > pts;
    int nSegments = 0;

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
    void slSetNSegments(int value = 0);

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

    void drawGeometry();
};

#endif // CUSTOMGL_H
