attribute vec2 vertex;
attribute vec4 color;

varying vec4 colorOut;

void main()
{
    colorOut=color;
    gl_Position=vec4(vertex[0] / 400.0 - 1.0, 1.0 - vertex[1] / 300.0, 0.0,1.0);
}
