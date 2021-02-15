#include "customgl.h"

void CustomGL::slSetGeometryType(int typ)
{
    this->geomType = typ;

    paintGL();
}

CustomGL::CustomGL()
{
    pts.push_back({0.0,.9});
    pts.push_back({-.6,.5});
    pts.push_back({-.6,-.5});

    pts.push_back({0.0,-.9});
    pts.push_back({.6,-.5});
    pts.push_back({.6,.5});

    colors.push_back(std::make_tuple(0.0,1.0,0.0)); //T
    colors.push_back(std::make_tuple(1.0,1.0,0.0)); //TL
    colors.push_back(std::make_tuple(1.0,0.0,0.0)); //BL

    colors.push_back(std::make_tuple(1.0,0.0,1.0)); //B
    colors.push_back(std::make_tuple(0.0,0.0,1.0)); //BR
    colors.push_back(std::make_tuple(0.0,1.0,1.0)); //TR
}

void CustomGL::initializeGL()
{
    this->qglClearColor(Qt::white);
}

void CustomGL::resizeGL(int nWidth, int nHeight)
{
    if(nHeight==0)nHeight=1;
    w=nWidth;h=nHeight;
    glViewport(0,0,nWidth,nHeight);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glMatrixMode(GL_MODELVIEW);
}

void CustomGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
    scene();
    swapBuffers();

}

void CustomGL::scene()
{
    int i = 0;
    switch (geomType) {
    case 0:
        i = GL_POINTS;
        break;
    case 1:
        i = GL_LINES;
        break;
    case 2:
        i = GL_LINE_STRIP;
        break;
    case 3:
        i = GL_LINE_LOOP;
        break;
    case 4:
        i = GL_TRIANGLES;
        break;
    case 5:
        i = GL_TRIANGLE_STRIP;
        break;
    case 6:
        i = GL_TRIANGLE_FAN;
        break;
    case 7:
        i = GL_QUADS;
        break;
    case 8:
        i = GL_QUAD_STRIP;
        break;
    case 9:
        i = GL_POLYGON;
        break;
    default:
        i=GL_POINT;
        break;
    }
    drawGeometry(i);
    return;
}

void CustomGL::drawGeometry(int typ)
{
    glPointSize(12.0f);
    glLineWidth(12.0f);
    glBegin(typ);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

/*
void CustomGL::drawPoint()
{
    glPointSize(12.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawLines()
{
    glLineWidth(12.0f);
    glBegin(GL_LINES);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawLineStrip()
{
    glLineWidth(12.0f);
    glColor3f(0.0f, 0.1f, 0.9f);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawLineLoop()
{
    glLineWidth(12.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawTriangles()
{
    glLineWidth(12.0f);
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawTriangleStrip()
{
    glLineWidth(12.0f);
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawTriangleFan()
{
    glLineWidth(12.0f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawQuads()
{
    glLineWidth(12.0f);
    glBegin(GL_QUADS);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawQuadStrip()
{
    glLineWidth(12.0f);
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

void CustomGL::drawPolygon()
{
    glLineWidth(12.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < pts.size();i++){
        glColor3f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]));
        glVertex2f(pts[i].first,pts[i].second);
    }
    glEnd();
}

*/
