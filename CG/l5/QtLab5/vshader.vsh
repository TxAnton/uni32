attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_Color;
attribute highp vec2 qt_TexC;
attribute highp vec2 qt_offset;

attribute highp vec4 qt_MultiTexCoord0;

//out vec2 TexCoord;
//out vec3 color;

//varying vec3 сolor;
//varying vec2 TexCoord;

uniform highp mat4 qt_ModelViewProjectionMatrix;
uniform highp float uoffset;
//varying highp vec4 qt_TexCoord0;
//attribute vec3 coord2d;
//attribute vec4 color;

//attribute vec3

varying vec3 vColor;
varying vec2 TexCoord;
varying float offset;

//varying vec4 vColor;

void main(void)
{
    vec4 _vec =  qt_Vertex;
//    gl_Position = _vec;//vec4(sin(_vec.x),_vec.y,sin(_vec.z),1.0f);
//    gl_Position = qt_ModelViewProjectionMatrix * (vec4(sin(qt_Vertex.x),qt_Vertex.y,sin(qt_Vertex.z),1.0f));
    gl_Position = qt_ModelViewProjectionMatrix * (qt_Vertex);

    TexCoord = qt_TexC.xy;
    vColor = qt_Color.rgb;
    offset = uoffset;
//    qt_TexCoord0 = qt_MultiTexCoord0;

//    vColor = vec4(sin(_vec.x*2*3.14f)+.5,_vec.y+.5,sin(_vec.z*3.14f)+.5,1.0f);;
//    vColor = vec4
}
