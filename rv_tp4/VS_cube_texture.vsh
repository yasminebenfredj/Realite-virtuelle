attribute highp vec3 rv_Position;
attribute highp vec3 rv_Color;
attribute highp vec3 rv_TexCoord ;

uniform   highp mat4 u_ModelViewProjectionMatrix;
uniform   highp float u_Opacity;
uniform   highp vec4 u_Color;

varying   highp vec4 outColor;
varying  highp  vec2 outTexCoord ;

void main(void)
{
    gl_Position = u_ModelViewProjectionMatrix * vec4(rv_Position, 1.0);
    outColor = vec4(rv_Color * u_Color.rgb, u_Opacity);
    outTexCoord = rv_TexCoord.st;
}
