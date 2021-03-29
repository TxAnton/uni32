uniform sampler2D qt_Texture0;
//varying highp vec4 qt_TexCoord0;
//uniform vec4 ourColor;
varying vec4 vColor;

void main(void)
{
//    gl_FragColor = ourColor;
//    gl_FragColor = vec4(0.4, 0.1, 0.0, 1.0);
//      gl_FragColor=texture2D(qt_Texture0, qt_TexCoord0.st);
    gl_FragColor = vColor;
}
