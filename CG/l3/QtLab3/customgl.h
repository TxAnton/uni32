#ifndef CUSTOMGL_H
#define CUSTOMGL_H
//#include <typeinfo>
#include <vector>
#include <tuple>

#include <QObject>
#include <QWidget>

#include <QtOpenGL>
#include <QDebug>

#include "interpolator.h"

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

public slots:
    void slSetGeometryType(int typ = GL_POINTS);
    void slSetAlphaType(int typ = GL_NEVER);
    void slSetAlphaVal(int value = 0);
    void slSetScX(int value = 0);
    void slSetScY(int value = 0);

    void slSetSfactorType(int typ = GL_SRC_COLOR);
    void slSetDfactorType(int typ = GL_SRC_COLOR);


public:
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
