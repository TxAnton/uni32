#include "customgl.h"


std::pair<double, double> CustomGL::_coordScreenToGl(int x, int y)
{
    // Turn upside down
    y = h - y + 1;

    // Turn into double
    double _xf = x;
    double _yf = y;

    // Origin to center
    _xf -= ((double)w)/2;
    _yf -= ((double)h)/2;

    // Scale to relative (-1..1)
    _xf /= ((double)w)/2;
    _yf /= ((double)h)/2;

    // Clamp
    if(_xf > 1.0)_xf = 1.0;
    if(_xf < -1.0)_xf = -1.0;
    if(_yf > 1.0)_yf = 1.0;
    if(_yf < -1.0)_yf = -1.0;

    return {_xf,_yf};
}

std::pair<int, int> CustomGL::_coordGlToScreen(double x, double y)
{
    // Scale to absolute (-w/2, w/2)
    x *= ((double)w)/2;
    y *= ((double)h)/2;

    // Origin to top left
    x += ((double)w)/2;
    y += ((double)h)/2;

    //Turn into integer
    int _xd = x;
    int _yd = y;

    // Turn upside down
    _yd = h - _yd + 1;

    // Clamp
    if(_xd > w)_xd = w;
    if(_xd < 0)_xd = 0;
    if(_yd > h)_yd = h;
    if(_yd < 0)_yd = 0;

    return {_xd,_yd};
}

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

// Public

bool CustomGL::checkPressOnDot(double x, double y)
{
    int index = -1;
    for(CPoint dot : pts) {
        index++;
        //qDebug() << x << " " << dot.x() - (d_size/2) << " " << y << " " << dot.y() + (d_size/2);
        if(     (x >= (dot.first  - _SC_TO_GL_X(d_size/2)))
            &&  (y >= (dot.second - _SC_TO_GL_Y(d_size/2)))
            &&  (x <= (dot.first  + _SC_TO_GL_X(d_size/2)))
            &&  (y <= (dot.second + _SC_TO_GL_Y(d_size/2))) )
        {

            cur_dot = index;                                    //если нашла такую точку, запоминаем ее индекс в векторе
            return true;
        }else{
            qDebug()<<"x: "<<x<<" dotX: "<<dot.first<<" dist: " <<_ABS(x-dot.first);
        }
    }
    qDebug()<<"Miss! "<<_SC_TO_GL_X(d_size/2);
    return false;                                               //иначе игнорируем
}



void CustomGL::mousePressEvent(QMouseEvent *event)
{

    qDebug() << "\nmousePress: " << event->x() << " " << event->y();
    std::pair<double, double> mp = _coordScreenToGl(event->x(), event->y());
    qDebug() << "mousePress: " << mp.first << " " << mp.second;
//    std::pair<int, int> md = _coordGlToScreen(mp.first, mp.second);
//    qDebug() << "mousePress: " << md.first << " " << md.second;

    //    qDebug() << "mousePress: " << event->x() << " " << event->y();

    auto glPoint = _coordScreenToGl(event->x(),event->y());
    double x = glPoint.first;
    double y = glPoint.second;

    mouse_x = x;                                            //текущая позиция клика мыши
    mouse_y = y;
    if(checkPressOnDot(x, y)) {                                 //проверяем, что нажали по точке
        dot_move = true;

    }
}

void CustomGL::mouseReleaseEvent(QMouseEvent *event)
{
    auto glPoint = _coordScreenToGl(event->x(),event->y());
    double x = glPoint.first;
    double y = glPoint.second;

    if(dot_move) {
        dot_move = false; //для след раза
        pts[cur_dot].first =x;//(pts[cur_dot].first  + (x - mouse_x)); //вектор перемещения
        pts[cur_dot].second=y;//(pts[cur_dot].second + (y - mouse_y));
        interp->setPoints(pts);
//        update();
        paintGL();
//        paintGL();
    }
}

void CustomGL::mouseMoveEvent(QMouseEvent *event)
{
    auto glPoint = _coordScreenToGl(event->x(),event->y());
    double x = glPoint.first;
    double y = glPoint.second;

    assert(!std::isinf(x));
    assert(!std::isinf(y));
    mouse_x = x;                                            //текущая позиция клика мыши
    mouse_y = y;

    if(dot_move) {

        pts[cur_dot].first =x;//(pts[cur_dot].first  + (x - mouse_x));  //вектор перемещения
        pts[cur_dot].second=y;//(pts[cur_dot].second + (y - mouse_y));
        interp->setPoints(pts);
//        update();
        paintGL();


    }
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
    glPointSize((float)d_size);
    glLineWidth((float)l_size);

    glColor3f(.2,.2,.99);
    double mrg = (this->interp->MaxX() - this->interp->MinX()) / (double)this->steps;
    mrg = _ABS(mrg);

    //    double _x = this->interp->MinX();
    double _y;// = this->interp->f(_x);
    //    glVertex2f(_x,_y);
//    qDebug()<<"MinMax " <<this->interp->MinX()<<" "<<this->interp->MaxX();
    glBegin(GL_LINE_STRIP);
    //    glVertex2f(pts.front().first,pts.front().second);
    //    glVertex2f(pts.back().first,pts.back().second);
//    qDebug()<<mrg;
    for(auto i = this->interp->MinX(); i <=this->interp->MaxX(); i+=mrg){
        //        _x+=mrg;
        _y = this->interp->f(i);
        glVertex2f(i,_y);
//        qDebug() <<i<<" "<< _y;
    }
    glEnd();

    glColor3f(.99,.2,.2);
    glBegin(GL_POINTS);
    for(CPoint dot : pts) {
        glVertex2f(dot.first, dot.second);
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
