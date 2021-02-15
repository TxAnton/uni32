#ifndef CUSTOMGL_H
#define CUSTOMGL_H
//#include <typeinfo>
#include <vector>
#include <tuple>

#include <QObject>
#include <QWidget>

#include <QtOpenGL>

class CustomGL : public QGLWidget
{
  Q_OBJECT

typedef std::tuple<float, float, float>  clr_t;

private:
    int w=1,h=1;
    std::vector<std::pair<float,float> > pts;
    std::vector<clr_t> colors;

    int geomType = GL_POINTS;
public slots:
    void slSetGeometryType(int typ = GL_POINTS);


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
