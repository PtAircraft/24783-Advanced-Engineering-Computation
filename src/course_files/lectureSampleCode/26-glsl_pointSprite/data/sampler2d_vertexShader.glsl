attribute vec3 vertex;
attribute vec2 texCoord;
varying vec2 texCoordOut;
void main()
{
	texCoordOut=texCoord;
    gl_Position=vec4(vertex,1.0);
}
