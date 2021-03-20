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
    nSegments = value;
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
    l = new L_system();
    l->reset("0");
    l->addRule('1',"21");
    l->addRule('0',"1[+0]1[-0]+0");

    l->iterate(8);

    qDebug()<<l->getState().c_str();

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
//    glViewport(0,0,800,800);
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
    glPointSize((float)d_size);
    glPushMatrix();
    glTranslated(.2,-1,0);
    glScaled(.7/std::pow(1.65,nSegments)*10,.9 /std::pow(1.65,nSegments)*10,1);
    drawIter(nSegments);
    glPopMatrix();
    return;
}

void CustomGL::drawIter(int n)
{

    if(n==0){
        cnt++;
//        glColor3d(cnt%3==0,cnt%3==1,cnt%3==2);
//        glLineWidth((float)dw*10000);
//        glBegin(GL_LINES);
//            glVertex2d(0,-dl/2);
//            glVertex2d(0,dl/2);
//        glEnd();

//        glColor3d(0,0,0);

        glBegin(GL_LINE_STRIP);
        glVertex2d(dw/2,dl/2);
        glVertex2d(-dw/2,dl/2);
        glVertex2d(-dw/2,-dl/2);
        glVertex2d(dw/2,-dl/2);
        glVertex2d(dw/2,dl/2);
        glEnd();
        return;
    }else{
        drawIter(n-1);

//        glColor3d(n%3==0,n%3==1,n%3==2);
        glPushMatrix();

        // Left branch

        glRotated(30-(n),0,0,1);
        glTranslated(dw/2,dl*.6 + std::pow(1.8-(0.005*nSegments),n-1)/10 ,0);
        glScaled(1,.7,1);
        drawIter(n-1);

        glPopMatrix();
        glPushMatrix();

        // Right branch

        glRotated(-40+(n),0,0,1);
        glTranslated(-dw/2,dl*.35 + std::pow(1.7-(0.005*nSegments),n-1)/10 ,0);




        glScaled(.7,.5,1);
        drawIter(n-1);
        glPopMatrix();
    }
}



void CustomGL::drawGeometry()
{

    glColor3f(.2,.2,.99);


    glPushMatrix();
    glTranslated(0,-1,0);
    glScaled(.0003,.0005,.004);
    std::vector<float> lvec;
    glPointSize((float)d_size);
//    glLineWidth((float)l_size);
    lvec.push_back((float)l_size);
    for(char c:l->getState()){
        switch (c) {
        case '+':
            glRotated(-angl,0,0,1);
            break;
        case '-':
            glRotated(angl,0,0,1);
            break;
        case '2':
        case '1':
            glBegin(GL_LINES);
            glVertex2d(0,0);
            glVertex2d(0,dl);
            glEnd();
            glTranslated(0,dl,0);
            break;
        case '0':
            // Здесь могла быть ваша реклама
            break;
        case '[':
            glPushMatrix();
            lvec.push_back((float)l_size);
            l_size *=.7;
            glLineWidth((float)l_size);
            break;
        case ']':
            l_size = lvec.back() ;
            glLineWidth((float)l_size);
            lvec.pop_back();
            glPopMatrix();

            break;
        default:
            break;
        }
    }

    glPopMatrix();
//    glScaled(10.0/4.0,10.
}
