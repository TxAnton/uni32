attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_MultiTexCoord0;
uniform highp mat4 qt_ModelViewProjectionMatrix;
//varying highp vec4 qt_TexCoord0;
//attribute vec3 coord2d;
//attribute vec4 color;

//attribute vec3


varying vec4 vColor;

void main(void)
{
    vec4 _vec =  qt_Vertex;
//    gl_Position = _vec;//vec4(sin(_vec.x),_vec.y,sin(_vec.z),1.0f);
    gl_Position = qt_ModelViewProjectionMatrix * (vec4(sin(qt_Vertex.x),qt_Vertex.y,sin(qt_Vertex.z),1.0f));

//    qt_TexCoord0 = qt_MultiTexCoord0;

//    gl_Position =  vec4(coord2d.x, coord2d.y, coord2d.z, 1.0);
    vColor = vec4(sin(_vec.x*2*3.14f)+.5,_vec.y+.5,sin(_vec.z*3.14f)+.5,1.0f);;
//    vColor = vec4
}
