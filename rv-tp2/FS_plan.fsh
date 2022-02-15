varying highp vec4 outColor;

void main(void)
{
    gl_FragColor = outColor * (1.0 - gl_FragCoord.z);
    gl_FragColor.a = outColor.a;
}
