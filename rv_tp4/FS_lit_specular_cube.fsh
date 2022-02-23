varying   highp vec2 outTexCoord;
varying   highp vec3 outPos;
varying   highp vec3 outNormal;
varying   highp vec4 outColor;

uniform samplerCube skybox;
uniform highp vec3 eye_position;


void main(void)
{
    //calcul de la composante diffuse
    vec3 norm = normalize(outNormal);

    //calcul de la composante spéculaire
    vec3 viewdir = normalize(outPos - eye_position);
    vec3 reflectdir = reflect(viewdir, norm);

    //couleur finale
    gl_FragColor = textureCube(skybox, reflectdir);
    gl_FragColor.a = outColor.a;
}
