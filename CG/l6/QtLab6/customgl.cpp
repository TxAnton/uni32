#include "customgl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    texoffset = (nSegments/100.0f)-.5f;
    //    steps = nSegments;
    paintGL();
}

void CustomGL::slTimerUpdate()
{
    texoffset+=0.01f+(0.001f*(nSegments-50));
    updateGL();
    //    paintGL();

}



void CustomGL::mousePressEvent(QMouseEvent *event)
{
    //    auto glPoint = _coordScreenToGl(event->x(),event->y());
    //    double x = glPoint.first;
    //    double y = glPoint.second;
    pressX = event->x();
    pressY = event->y();

}

void CustomGL::mouseReleaseEvent(QMouseEvent *event)
{
    auto glPoint = _coordScreenToGl(event->x(),event->y());
    double x = glPoint.first;
    double y = glPoint.second;

}

void CustomGL::mouseMoveEvent(QMouseEvent *event)
{
    //    auto glPoint = _coordScreenToGl(event->x(),event->y());
    //    double x = glPoint.first;
    //    double y = glPoint.second;
    float __step = 0.05;
    if (pressY - event->y() > 0) {if (alpha + 0.01 < M_PI / 2) { alpha += __step; } }
    else if (pressY - event->y() < 0) { if ( -M_PI / 2 < alpha - 0.01) { alpha -= __step; }  }
    if (pressX - event->x() > 0) { theta += __step; }
    else if (pressX - event->x() < 0) { theta -= __step; }

    int x = cameraDistance * cos(alpha) * sin(theta);
    int y = cameraDistance * sin(alpha);
    int z = cameraDistance * cos(alpha) * cos(theta);

    pressX = event->x();
    pressY = event->y();
    updateGL();

}

void CustomGL::wheelEvent(QWheelEvent *event)
{
    int d = cameraDistance - (event->delta()) / 120;
    if (d > 1) {
        cameraDistance = d;
        updateGL();
    }
}

CustomGL::CustomGL()
{
    texoffset = 0.0f;
    shaderProgram = new QGLShaderProgram( this );

    cameraDistance = 10;
    cameraX = 0;
    cameraY = 0;
    cameraZ = cameraDistance;

    alpha = M_PI / 6;
    theta = M_PI / 6;

    light_source = QVector3D(+2,+2,+1);
    light_intensity = 1;

    glGenTextures(1, &texture_n);
    glBindTexture(GL_TEXTURE_2D, texture_n);

    // Устанавливаем параметры наложения и фильтрации текстур (для текущего связанного объекта текстуры)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    texdata = stbi_load("img.jpg", &texwidth, &texheight, &texnrChannels, 0);
    if (texdata)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);

        //        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {

        qDebug() << ("Failed to load texture");
    }
}

void CustomGL::initializeGL()
{
    this->qglClearColor(QColor(100,100,100,100));
    initShaders();
    getIco();
}

void CustomGL::resizeGL(int nWidth, int nHeight)
{

    if(nHeight==0)nHeight=1;
    w=nWidth;h=nHeight;
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CustomGL::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    scene();


    //    glVertex2d();
}

void CustomGL::scene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    drawGeometry();
    drawIco();

    pmvMatrix.setToIdentity();
    glLoadIdentity();

    swapBuffers();
    glFlush();

    //    glPointSize((float)d_size);
    //    glPushMatrix();
    //    glTranslated(.2,-1,0);
    //    glScaled(.7/std::pow(1.65,nSegments)*10,.9 /std::pow(1.65,nSegments)*10,1);
    //    drawIter(nSegments);
    //    glPopMatrix();
    return;
}


void CustomGL::drawSquare()
{
    glBegin(GL_POLYGON);
    glVertex3d(-.2,-.2,0);
    glVertex3d(+.2,-.2,0);
    glVertex3d(0.0,.5,-2.0);
    //    glVertex2d(-.2,-.2);
    //    glVertex2d(+.2,-.2);
    //    glVertex2d(0.0,.5);
    //    glVertex3d(-100,-100,-100);
    //    glVertex3d(-100,-100,100);
    //    glVertex3d(100,-100,-100);

    glEnd();
}


/*
void CustomGL::drawGeometry()
{


    float x = cameraDistance * cos(alpha) * sin(theta);
    float y = cameraDistance * sin(alpha);
    float z = cameraDistance * cos(alpha) * cos(theta);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_TEXTURE_WRAP_S
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    shaderProgram->bind();

    glBindTexture(GL_TEXTURE_2D, texture_n);

    // Устанавливаем параметры наложения и фильтрации текстур (для текущего связанного объекта текстуры)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // Бинд текстуры

    if (texdata)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);
    }
    else
    {
        qDebug() << ("Failed to load texture");
    }

    //Рисуем шейдером

    GLfloat vertexes[] = {
        // координаты
        0.5f,  0.5f, 0.0f, // верхняя правая
        0.5f, -0.5f, 0.0f, // нижняя правая
        -0.5f, -0.5f, 0.0f, // нижняя левая
        -0.5f,  0.5f, 0.0f, // верхняя левая
    };

    GLfloat colors[] = {
        // цвета            // текстурные координаты
        1.0f, 0.0f, 0.0f,   // верхняя правая
        0.0f, 1.0f, 0.0f,   // нижняя правая
        0.0f, 0.0f, 1.0f,   // нижняя левая
        1.0f, 1.0f, 0.0f,   // верхняя левая
    };

    GLfloat texCoords[] = {
        // текстурные координаты
        1.0f, 1.0f,   // верхняя правая
        1.0f, 0.0f,   // нижняя правая
        0.0f, 0.0f,   // нижняя левая
        0.0f, 1.0f,    // верхняя левая
    };

    GLfloat quad[] = {
        -0.5f,  -0.5f,  -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,   -0.5f,   -0.5f
    };
    GLfloat textCoord[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };

    pmvMatrix.setToIdentity();
    //Эти две строчки чтобы вращать картинку
    pmvMatrix.translate(0,0,cameraDistance/50.0f);
    pmvMatrix.rotate(QQuaternion::fromEulerAngles((alpha)/M_PI*180,(theta)/M_PI*180,90));
    pmvMatrix.scale(2);
    //    pmvMatrix.rotate(QQuaternion::fromEulerAngles(0,0,90));

    int matrixLoc = shaderProgram->uniformLocation("qt_ModelViewProjectionMatrix");
    int vertexLoc = shaderProgram->attributeLocation("qt_Vertex");
    int colorLoc = shaderProgram->attributeLocation("qt_Color");
    int textureLoc = shaderProgram->attributeLocation("qt_TexC");
    int offsetLoc = shaderProgram->uniformLocation("uoffset");

    shaderProgram->bind();
    shaderProgram->setUniformValue(matrixLoc,pmvMatrix);

    shaderProgram->setAttributeArray(vertexLoc,vertexes,3);
    shaderProgram->setAttributeArray(colorLoc,colors,3);
    shaderProgram->setAttributeArray(textureLoc,textCoord,2);

    shaderProgram->setUniformValue(offsetLoc,texoffset);

    shaderProgram->enableAttributeArray(vertexLoc);
    shaderProgram->enableAttributeArray(textureLoc);
    shaderProgram->enableAttributeArray(colorLoc);
    glDrawArrays(GL_QUADS,0,4);

    shaderProgram->disableAttributeArray(vertexLoc);
    shaderProgram->disableAttributeArray(textureLoc);
    shaderProgram->disableAttributeArray(colorLoc);

    shaderProgram->release();


}
*/
void CustomGL::drawIco()
{


    float x = cameraDistance * cos(alpha) * sin(theta);
    float y = cameraDistance * sin(alpha);
    float z = cameraDistance * cos(alpha) * cos(theta);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_TEXTURE_WRAP_S
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    shaderProgram->bind();

    glBindTexture(GL_TEXTURE_2D, texture_n);

    // Устанавливаем параметры наложения и фильтрации текстур (для текущего связанного объекта текстуры)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // Бинд текстуры

    if (texdata)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);
    }
    else
    {
        qDebug() << ("Failed to load texture");
    }

    pmvMatrix.setToIdentity();
    //Эти две строчки чтобы вращать картинку
    pmvMatrix.translate(0,0,cameraDistance/50.0f);
    pmvMatrix.rotate(QQuaternion::fromEulerAngles((alpha)/M_PI*180,(theta)/M_PI*180,0));
    pmvMatrix.scale(.2);
    //    pmvMatrix.rotate(QQuaternion::fromEulerAngles(0,0,90));

    int matrixLoc = shaderProgram->uniformLocation("qt_ModelViewProjectionMatrix");
    int vertexLoc = shaderProgram->attributeLocation("qt_Vertex");
    int colorLoc = shaderProgram->attributeLocation("qt_Color");
    int textureLoc = shaderProgram->attributeLocation("qt_TexC");
    int normalLoc = shaderProgram->attributeLocation("qt_normal");

    int offsetLoc = shaderProgram->uniformLocation("uoffset");
    int lightLoc = shaderProgram->uniformLocation("qt_lightsource");

    shaderProgram->bind();
    shaderProgram->setUniformValue(matrixLoc,pmvMatrix);

    shaderProgram->setAttributeArray(vertexLoc,AS_ARRAY(vertexes,GLfloat),3);
    shaderProgram->setAttributeArray(colorLoc,AS_ARRAY(colors,GLfloat),3);
    shaderProgram->setAttributeArray(normalLoc,AS_ARRAY(normals,GLfloat),3);

    //    shaderProgram->setAttributeArray(textureLoc,textCoord,2);
    shaderProgram->setUniformValue(lightLoc, QVector4D(light_source,light_intensity));
    shaderProgram->setUniformValue(offsetLoc,(nSegments/100.0f)-.5f);
//    qDebug()<< (nSegments/100.0f)-.5f;

    shaderProgram->enableAttributeArray(vertexLoc);
    shaderProgram->enableAttributeArray(textureLoc);
    shaderProgram->enableAttributeArray(colorLoc);
    shaderProgram->enableAttributeArray(normalLoc);
    glDrawArrays(GL_TRIANGLES,0,faces.size()*3);

    shaderProgram->disableAttributeArray(vertexLoc);
    shaderProgram->disableAttributeArray(textureLoc);
    shaderProgram->disableAttributeArray(colorLoc);
    shaderProgram->disableAttributeArray(normalLoc);

    shaderProgram->release();


}

void CustomGL::updateLighting()
{
    colors.clear();
    for(int i = 0; i<vertexes.size();i++){
        QVector3D p_color = QVector3D(std::get<0>(prime_colors[i]),std::get<1>(prime_colors[i]),std::get<2>(prime_colors[i]));
        QVector3D p_coord = QVector3D(std::get<0>(vertexes[i]),std::get<1>(vertexes[i]),std::get<2>(vertexes[i]));

    }
}

void CustomGL::getIco(int n)
{

    double t = (1.0 + std::sqrt(5.0)) / 2.0;
    //    GLfloat fl[3] = {-1,  t,  0};
    //    vertexes.push_back({-1,  t,  0});

    _vertexes.push_back({-1,  t,  0});
    _vertexes.push_back({ 1,  t,  0});
    _vertexes.push_back({-1, -t,  0});
    _vertexes.push_back({ 1, -t,  0});

    _vertexes.push_back({ 0, -1,  t});
    _vertexes.push_back({ 0,  1,  t});
    _vertexes.push_back({ 0, -1, -t});
    _vertexes.push_back({ 0,  1, -t});

    _vertexes.push_back({ t,  0, -1});
    _vertexes.push_back({ t,  0,  1});
    _vertexes.push_back({-t,  0, -1});
    _vertexes.push_back({-t,  0,  1});

    for(int i=0 ;i<_vertexes.size();i++){
        //        colors.push_back({.5f,.5f,.5f});
        _colors.push_back({(GLfloat)(i%3==0),(GLfloat)(i%3==1),(GLfloat)(i%3==2)});
    }
    //    faces.push_back({0, 11, 5});

    faces.push_back({0, 11, 5});
    faces.push_back({0, 5, 1});
    faces.push_back({0, 1, 7});
    faces.push_back({0, 7, 10});
    faces.push_back({0, 10, 11});

    // 5 adjacent faces
    faces.push_back({1, 5, 9});
    faces.push_back({5, 11, 4});
    faces.push_back({11, 10, 2});
    faces.push_back({10, 7, 6});
    faces.push_back({7, 1, 8});

    // 5 faces around point 3
    faces.push_back({3, 9, 4});
    faces.push_back({3, 4, 2});
    faces.push_back({3, 2, 6});
    faces.push_back({3, 6, 8});
    faces.push_back({3, 8, 9});

    // 5 adjacent faces
    faces.push_back({4, 9, 5});
    faces.push_back({2, 4, 11});
    faces.push_back({6, 2, 10});
    faces.push_back({8, 6, 7});
    faces.push_back({9, 8, 1});

    // Subdivide faces

    for(auto face: faces){
        //_vertexes[std::get<0>(face)
        auto _v0 = _vertexes[std::get<0>(face)];
        auto _v1 = _vertexes[std::get<1>(face)];
        auto _v2 = _vertexes[std::get<2>(face)];
        QVector3D v0 = QVector3D(
                std::get<0>(_v0),
                std::get<1>(_v0),
                std::get<2>(_v0)
                );
        QVector3D v1 = QVector3D(
                std::get<0>(_v1),
                std::get<1>(_v1),
                std::get<2>(_v1)
                );
        QVector3D v2 = QVector3D(
                std::get<0>(_v2),
                std::get<1>(_v2),
                std::get<2>(_v2)
                );

        auto u = v1-v0;
        auto v = v2-v0;
        auto n = QVector3D::crossProduct(v,u).normalized();
        //        if(QVector3D::dotProduct(QVector3D::crossProduct(u,v),v0)>0){
        qDebug()<<n.x();

        vertexes.push_back(_vertexes[std::get<0>(face)]);
        prime_colors.push_back(_colors[std::get<0>(face)]);
        normals.push_back({n.x(),n.y(),n.z()});

        vertexes.push_back(_vertexes[std::get<1>(face)]);
        prime_colors.push_back(_colors[std::get<1>(face)]);
        normals.push_back({n.x(),n.y(),n.z()});

        vertexes.push_back(_vertexes[std::get<2>(face)]);
        prime_colors.push_back(_colors[std::get<2>(face)]);
        normals.push_back({n.x(),n.y(),n.z()});
    }
    colors = prime_colors;


    //    for(std::tuple<GLfloat,GLfloat,GLfloat>& vertex: _vertexes){
    //        double n = std::sqrt(_SQR(std::get<0>(vertex)) + _SQR(std::get<1>(vertex)) +_SQR(std::get<2>(vertex)));
    ////        std::get<0>(vertex) /= n;
    ////        std::get<1>(vertex) /= n;
    ////        std::get<2>(vertex) /= n;

    //        std::swap(std::get<0>(vertex),std::get<2>(vertex));
    //    }
    //    for(std::tuple<GLuint,GLuint,GLuint>& face: faces){
    //        std::swap(std::get<0>(face),std::get<2>(face));
    //    }



}


void CustomGL::initShaders()
{
    /*
    //    // Compile vertex shader
    //       shaderProgram->addShaderFromSourceFile( QGLShader::Vertex, "./vshader.vsh" );

    //       // Compile fragment shader
    //       shaderProgram->addShaderFromSourceFile( QGLShader::Fragment, "./fshader.fsh" );


    // Bind vertex array object
    //    QOpenGLVertexArrayObject *vao = new QOpenGLVertexArrayObject( this );
    //    vao->bind();
*/
    // Bind shader pipeline for use
    shaderProgram->link();
    shaderProgram->bind();

    std::string _fsh = readFile("./fshader.fsh");
    std::string _vsh = readFile("./vshader.vsh");
    qDebug() << _fsh.c_str();
    qDebug() << _vsh.c_str();


    if (!shaderProgram->addShaderFromSourceCode(QGLShader::Fragment, _fsh.c_str()))
        close();

    // Compile vertex shader
    if (!shaderProgram->addShaderFromSourceCode(QGLShader::Vertex, _vsh.c_str()))
        close();
    /*
    //    if (!shaderProgram->addShaderFromSourceCode(QGLShader::Fragment, "void main(void)\n{gl_FragColor = vec4(0.4, 0.5, 0.0, 1.0);}"))
    //        close();

    //    // Compile vertex shader
    //    if (!shaderProgram->addShaderFromSourceCode(QGLShader::Vertex, "void main(void)\n{gl_Position = ftransform();}"))
    //        close();

    //       // Link shader pipeline
    //       if (!shaderProgram->link())
    //           close();

    //       // Bind shader pipeline for use
    //       if (!shaderProgram->bind())
    //           close();
*/
}

std::string CustomGL::readFile(std::string filename)
{
    std::ifstream t(filename);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    return str;
}

