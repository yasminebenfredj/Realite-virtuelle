varying highp vec3 outTexCoord;
uniform samplerCube texture4;

void main(void)
{
    vec4 col = textureCube(texture4, outTexCoord);
    gl_FragColor = col ;
}
