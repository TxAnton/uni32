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

void CustomGL::slSetNSegments(int value)
{
    nSegments = value+1;
    steps = nSegments;
    paintGL();
}

// Public

bool CustomGL::checkPressOnDot(double x, double y)
{
    int index = -1;
    for(CPoint dot : pts) {
        index++;
        if(         (x >= (dot.first  - _SC_TO_GL_X(d_size/2)))
                &&  (y >= (dot.second - _SC_TO_GL_Y(d_size/2)))
                &&  (x <= (dot.first  + _SC_TO_GL_X(d_size/2)))
                &&  (y <= (dot.second + _SC_TO_GL_Y(d_size/2))) )
        {

            cur_dot = index;                                    //если нашла такую точку, запоминаем ее индекс в векторе
            return true;
        }
    }
    return false;                                               //иначе игнорируем
}



void CustomGL::mousePressEvent(QMouseEvent *event)
{
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
    }
}

void CustomGL::mouseMoveEvent(QMouseEvent *event)
{
    auto glPoint = _coordScreenToGl(event->x(),event->y());
    double x = glPoint.first;
    double y = glPoint.second;

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

    interp = new Interpolator(pts);
}

void CustomGL::initializeGL()
{
    this->qglClearColor(QColor(100,100,100,100));
}

void CustomGL::resizeGL(int nWidth, int nHeight)
{
    if(nHeight==0)nHeight=1;
    w=nWidth;h=nHeight;
    glViewport(0,0,nWidth,nHeight);
}

void CustomGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene();
    swapBuffers();

}

void CustomGL::scene()
{
    drawGeometry();

    return;
}

void CustomGL::drawGeometry()
{
    glPointSize((float)d_size);
    glLineWidth((float)l_size);

    glColor3f(.2,.2,.99);
    double mrg = (this->interp->MaxX() - this->interp->MinX()) / (double)this->steps;
    mrg = _ABS(mrg);

    double _y;// = this->interp->f(_x);

    glBegin(GL_LINE_STRIP);

    for(auto i = this->interp->MinX(); i <=this->interp->MaxX()+(mrg/2); i+=mrg){
        _y = this->interp->f(i);
        glVertex2f(i,_y);
    }
    glEnd();

    glColor3f(.99,.2,.2);
    glBegin(GL_POINTS);
    for(CPoint dot : pts) {
        glVertex2f(dot.first, dot.second);
    }
    glEnd();
}
