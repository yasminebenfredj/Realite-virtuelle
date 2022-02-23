varying highp vec4 outColor;
varying highp vec2 outTexCoord;
uniform sampler2D texture3;

void main(void)
{
    vec4 col0 = texture2D(texture3, outTexCoord.st);
    gl_FragColor = col0*outColor ;

    gl_FragColor.a = outColor.a;
}
