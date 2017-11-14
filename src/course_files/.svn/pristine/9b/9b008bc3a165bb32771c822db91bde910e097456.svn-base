varying vec4 colorOut;
varying vec3 vertexOut;

void main()
{
	// if(length(vertexOut)<3.0)
	// {
	// 	// gl_FragColor.a=0.0;
	// 	discard;
	// }

    float pi=3.1415927;
    vec4 rainbow=vec4(sin(vertexOut.x),sin(pi/2.0+vertexOut.y),sin(pi+vertexOut.z),1.0);
    gl_FragColor=colorOut+rainbow;

}
