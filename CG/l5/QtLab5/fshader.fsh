//#version 130

uniform sampler2D qt_Texture0;
//varying highp vec4 qt_TexCoord0;
//uniform vec4 ourColor;

//varying vec4 vColor;

varying vec3 vColor;
varying vec2 TexCoord;
varying float offset;

//in float foffset;
//in vec3 color;
//in vec2 TexCoord;

void main()
{
    float freq_mul = 100.0f;
    float ampl_div = 10.0f;
//    FragColor = texture(qt_Texture0, TexCoord);
//    gl_FragColor = texture(qt_Texture0, vec2(TexCoord.x+sin(TexCoord.x+offset*freq_mul)/ampl_div/3, TexCoord.y+sin(TexCoord.x+offset*freq_mul*2.2f)/ampl_div));   //Gendalf
    gl_FragColor = vec4(1,1,1,2)-texture(qt_Texture0, vec2(TexCoord.x+sin(TexCoord.y+offset*freq_mul/2)/ampl_div*3 ,
                                             TexCoord.y+sin(TexCoord.x+offset*freq_mul)/ampl_div*4) +.5f);        //Drunk
}
