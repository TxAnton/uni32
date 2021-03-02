#include "customgl.h"

void CustomGL::slSetGeometryType(int typ)
{
    this->geomType = typ + GL_POINTS;

    paintGL();
}

void CustomGL::slSetAlphaType(int typ)
{
    alphaType = typ+GL_NEVER;
    qDebug()<<"AlphaTYpe set to "<<typ<<endl;
    paintGL();
}

void CustomGL::slSetAlphaVal(int value)
{

    this->alphaVal = (float)((float)value+1)/100.0f;
//    qDebug()<<"AlphaVal set to "<<value<<endl;
    paintGL();
}

void CustomGL::slSetScX(int value)
{
//    qDebug()<<"Sc x set to "<<value<<endl;
    xSc = (value+1)/100.0f;
    paintGL();
}

void CustomGL::slSetScY(int value)
{
//    qDebug()<<"Sc y set to "<<value<<endl;
    ySc = (value+1)/100.0f;
    paintGL();
}

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

void CustomGL::slSetSfactorType(int typ)
{
    qDebug()<<"sfactorType set to "<<typ<<endl;
    if(typ<=10){
        sfactorType = typ + GL_SRC_COLOR;
    } else{
        sfactorType = typ - 11;
    }
    paintGL();
}

void CustomGL::slSetDfactorType(int typ)
{
    qDebug()<<"dfactorType set to "<<typ<<endl;
    if(typ<=10){
        sfactorType = typ + GL_SRC_COLOR;
    } else{
        sfactorType = typ - 11;
    }
    paintGL();
}

CustomGL::CustomGL()
{




    pts.push_back({-.9,-.9});
    pts.push_back({-.6,-.3});
    pts.push_back({-.3,.3});
    pts.push_back({0.0,.9});
    pts.push_back({.3,.3});
    pts.push_back({.6,-.3});

//    pts.push_back({0.0,.9}); //T
//    pts.push_back({-.6,-.5});//BL
//    pts.push_back({.6,.5});  //TR
//    pts.push_back({-.6,.5}); //TL
//    pts.push_back({.6,-.5}); //BR
//    pts.push_back({0.0,.9}); //T

//    pts.push_back({0.0,.9}); //T

//    pts.push_back({0.0,-.9});//B

    interp = new Interpolator(pts);

//    for(double i = -.9; i < .6; i+=.1){
//        qDebug() <<i<<" "<< this->interp->f(i);
//    }


    colors.push_back(std::make_tuple(0.0,1.0,0.0)); //T
    colors.push_back(std::make_tuple(1.0,0.0,0.0)); //BL
    colors.push_back(std::make_tuple(0.0,1.0,1.0)); //TR
    colors.push_back(std::make_tuple(1.0,1.0,0.0)); //TL
    colors.push_back(std::make_tuple(0.0,0.0,1.0)); //BR
    colors.push_back(std::make_tuple(0.0,1.0,0.0)); //T

//    colors.push_back(std::make_tuple(1.0,0.0,0.0)); //BL

//    colors.push_back(std::make_tuple(1.0,0.0,1.0)); //B

//    pts.push_back({0.0,.9}); //T
//    pts.push_back({-.6,.5}); //TL
//    pts.push_back({-.6,-.5});//BL

//    pts.push_back({0.0,-.9});//B
//    pts.push_back({.6,-.5}); //BR
//    pts.push_back({.6,.5});  //TR

//    colors.push_back(std::make_tuple(0.0,1.0,0.0)); //T
//    colors.push_back(std::make_tuple(1.0,1.0,0.0)); //TL
//    colors.push_back(std::make_tuple(1.0,0.0,0.0)); //BL

//    colors.push_back(std::make_tuple(1.0,0.0,1.0)); //B
//    colors.push_back(std::make_tuple(0.0,0.0,1.0)); //BR
//    colors.push_back(std::make_tuple(0.0,1.0,1.0)); //TR
}

void CustomGL::initializeGL()
{
    this->qglClearColor(QColor(100,100,100,100));
//    this->qglClearColor(QColor(000,000,000,100));
//    this->qglClearColor(QColor(255,255,255,100));
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
    /*
    int i = geomType;

    switch (geomType) {
    case 0:
        i = GL_POINTS;
        break;
    case 1:
        i = GL_LINES;
        break;
    case 2:
        i = GL_LINE_LOOP;
        break;
    case 3:
        i = GL_LINE_STRIP;
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
*/

//    glEnable(GL_BLEND);
//    glBlendFunc(sfactorType, dfactorType);

//    glEnable(GL_SCISSOR_TEST);
//    glScissor(w*xSc,h*ySc,w*(1-xSc),h*(1-ySc));

//    glEnable(GL_ALPHA_TEST);
//    glAlphaFunc(alphaType, alphaVal);

    drawGeometry(geomType);

//    glDisable(GL_ALPHA_TEST);

//    glDisable(GL_SCISSOR_TEST);

//    glDisable(GL_BLEND);
    return;
}

void CustomGL::drawGeometry(int typ)
{
    glPointSize(12.0f);
    glLineWidth(12.0f);

    double mrg = .01;//(this->interp->MaxX() - this->interp->MinX()) / (double)this->steps;

//    double _x = this->interp->MinX();
    double _y;// = this->interp->f(_x);
//    glVertex2f(_x,_y);
    qDebug()<<"MinMax " <<this->interp->MinX()<<" "<<this->interp->MaxX();
    glBegin(GL_LINE_STRIP);
//    glVertex2f(pts.front().first,pts.front().second);
//    glVertex2f(pts.back().first,pts.back().second);
    qDebug()<<mrg;
    for(auto i = this->interp->MinX(); i <this->interp->MaxX(); i+=mrg/2){
//        _x+=mrg;
        _y == this->interp->f(i);
        glVertex2f(i,this->interp->f(i));
        qDebug() <<i<<" "<< _y;
    }
    glEnd();


//    glPointSize(12.0f);
//    glLineWidth(12.0f);
//    glBegin(typ);
//    for(int i = 0; i < pts.size();i++){
//        glColor4f(std::get<0>(colors[i]), std::get<1>(colors[i]), std::get<2>(colors[i]),(float)((float)(i+1)/((float)pts.size()+2)));
//        glVertex2f(pts[i].first,pts[i].second);
////        glColor4
//    }
//    glEnd();
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
