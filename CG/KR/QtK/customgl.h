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


//#include <SDL.h>
#include <GLES3/gl3.h>

//#define GL_GLEXT_PROTOTYPES 1
//#include <SDL2/SDL_opengl.h>
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
    GLfloat sub_time;

    QGLShaderProgram*  shaderProgram;

    double cameraX = 0,cameraY = 0,cameraZ = 0;

    QMatrix4x4 pmvMatrix;

    bool doAnimate = true;


    double alpha = 0;
    double theta = 0;

    int w=1,h=1;


    QVector3D eulerRotation;
    QVector3D scale;
    QVector3D translation;
    int nSegments = 0;
    bool isFrustum = false;
    bool isWireframe = false;
    int ss = 1;

    int d_size = 15;                                     //координаты и размер точки
    float l_size = 10;                                     //координаты и размер точки

    double pressX=0, pressY=0;
    double cameraDistance = .1;

#define AS_ARRAY(_V, _T) ( (_T*)(&((_V)[0])) )
#define BUFFER_OFFSET(i) ( (char *)NULL + (i) )
//    GLuint vao = 0;
//    GLuint vbo = 0;
//    GLuint positonID, colorID;
//    GLuint indexBufferID;

    std::vector<std::tuple<GLfloat,GLfloat,GLfloat> > _vertexes;
    std::vector<std::tuple<GLfloat,GLfloat,GLfloat> > vertexes;
    std::vector<std::tuple<GLfloat,GLfloat,GLfloat> > _colors;
    std::vector<std::tuple<GLfloat,GLfloat,GLfloat> > prime_colors;
    std::vector<std::tuple<GLfloat,GLfloat,GLfloat> > colors;
    std::vector<std::tuple<GLfloat,GLfloat,GLfloat> > normals;
    std::list<std::tuple<GLuint ,GLuint ,GLuint>> faces;

    QVector3D light_source;
    float light_intensity = 1;

//    int mouse_x, mouse_y;                           //координаты мыши

    std::pair<double,double> _coordScreenToGl(int x, int y);
    std::pair<int,int> _coordGlToScreen(double x, double y);
#define _SQR(_X)        ( (_X)*(_X) )
#define _ABS(_X)        ( (_X)<0?(-(_X)):(_X) )
#define _MIN(_X,_Y)     ( (_X)<(_Y)?(_X):(_Y) )
#define _MAX(_X,_Y)     ( (_X)>(_Y)?(_X):(_Y) )
#define _D_CLAMP(_X,_D) ( _MAX((_X),(_D)) )
#define _U_CLAMP(_X,_U) ( _MIN((_X),(_U)) )
#define _CLAMP(_X,_D,_U) ( _U_CLAMP((_D_CLAMP((_X),(_D))),(_U)) )
#define _GL_TO_SC_X(_X) ( (int)  (_ABS((_X)) / 2.0f * w) )
#define _GL_TO_SC_Y(_Y) ( (int)  (_ABS((_Y)) / 2.0f * h) )
#define _SC_TO_GL_X(_X) ( (double)     (_ABS((_X)) / ((double)w) * 2.0f) )
#define _SC_TO_GL_Y(_Y) ( (double)     (_ABS((_Y)) / ((double)h) * 2.0f) )

public slots:
    void slSetNSegments(int value = 0);

    void slSetWireframe(bool value = false);
    void slSetFrustum(bool value = false);

    void slSetSS(int value = 0);

    void slSetEulerX(int value=0);
    void slSetEulerY(int value=0);
    void slSetEulerZ(int value=0);

    void slSetTrX(int value = 0);
    void slSetTrY(int value = 0);
    void slSetTrZ(int value = 0);

    void slSetScX(int value = 50);
    void slSetScY(int value = 50);
    void slSetScZ(int value = 50);




    void slTimerUpdate();
    void slControllerUpdate();

public:

    void mousePressEvent(QMouseEvent *event) override;      //зажали клавишу мыши
    void mouseReleaseEvent(QMouseEvent *event) override;    //отпустили клавишу мыши
    void mouseMoveEvent(QMouseEvent *event) override;       //перемещение с зажатой клавишей мыши
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event);
    CustomGL();
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void scene();

    void drawSquare();
    void drawGeometry();
    void drawIco();
    void drawAxis();
    void updateLighting();
    void getIco(int n = 0);
    
    void getRect(float p = 0);


    void initShaders();


    std::string readFile(std::string filename);
};

#endif // CUSTOMGL_H
