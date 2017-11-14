attribute vec3 vertex;
attribute vec4 color;

uniform mat4 projection,modelView;

varying vec4 colorOut;
varying vec3 vertexOut;

void main()
{
    colorOut=color;
	vertexOut=vertex;
    gl_Position=projection*modelView*vec4(vertex,1.0);
}
