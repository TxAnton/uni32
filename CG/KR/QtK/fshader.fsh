//#version 130

uniform sampler2D qt_Texture0;
uniform highp vec4 qt_lightsource;
//varying highp vec4 qt_TexCoord0;
//uniform vec4 ourColor;

//varying vec4 vColor;


varying vec3 vColor;
varying vec2 TexCoord;
varying float offset;
varying vec3 normal;
varying vec3 position;
varying vec3 lightsource;

//in float foffset;
//in vec3 color;
//in vec2 TexCoord;

void main()
{

    float freq_mul = 100.0f;
    float ampl_div = 10.0f;
//    float val = dot(normalize(lightsource.xyz-position),normal) - length(lightsource.xyz-position)*.01;
    float dist = length(lightsource.xyz-position);
    float val = 2-dist*offset*10;
    gl_FragColor = vec4(vColor.xyz,1.0f) + vec4(val,val,val,1)* dot(normalize(lightsource.xyz-position),normal);
//    gl_FragColor = vec4(normal.xyz*5,1.0f);
//    gl_FragColor = vec4(vec3(val,val,val),1.0f)+vec4(vColor.xyz,1.0f)*.1;

//    gl_position.xyz
//    gl_FragColor = texture(qt_Texture0, TexCoord);
//    gl_FragColor = texture(qt_Texture0, vec2(TexCoord.x+sin(TexCoord.x+offset*freq_mul)/ampl_div/3, TexCoord.y+sin(TexCoord.x+offset*freq_mul*2.2f)/ampl_div));   //Gendalf
//    gl_FragColor = vec4(1,1,1,2)-texture(qt_Texture0, vec2(TexCoord.x+sin(TexCoord.y+offset*freq_mul/2)/ampl_div*3 ,
//                                             TexCoord.y+sin(TexCoord.x+offset*freq_mul)/ampl_div*4) +.5f);        //Drunk
}
