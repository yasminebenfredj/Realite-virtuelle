attribute highp vec3 rv_Position;
uniform   highp mat4 u_ModelViewProjectionMatrix;
varying   highp vec4 outColor;
uniform  highp vec3  u_color ;
uniform   highp float u_Opacity;

void main(void)
{
    gl_Position = u_ModelViewProjectionMatrix * vec4(rv_Position, 1.0);
    outColor = vec4(u_color.rgb, u_Opacity);
}
