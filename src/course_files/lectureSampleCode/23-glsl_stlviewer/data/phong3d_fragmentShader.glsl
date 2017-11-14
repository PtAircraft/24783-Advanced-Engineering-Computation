varying vec4 colorOut;
varying vec3 normalOut;
varying vec3 viewDirOut;

uniform vec3 lightDir;
uniform float ambient;
uniform float specularIntensity;
uniform float specularExponent;

void main()
{
    vec3 lit=normalize(lightDir);
	vec3 nom=normalize(normalOut);
	vec3 viewDir=normalize(viewDirOut);

    float diffuse=max(0.0,dot(nom,lit));

    vec3 midDir=normalize(viewDir+lit);
    float specular=specularIntensity*pow(max(0.0,dot(midDir,nom)),specularExponent);

    gl_FragColor=vec4(colorOut.rgb*(ambient+diffuse),colorOut.a)
            +vec4(specular,specular,specular,0.0);
}
