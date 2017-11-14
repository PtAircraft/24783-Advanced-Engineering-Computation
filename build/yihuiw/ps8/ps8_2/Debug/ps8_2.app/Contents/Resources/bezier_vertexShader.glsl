attribute float s, t;
uniform vec3 ctp[16];
uniform mat4 projection,modelView;

varying vec3 vtxOut;

vec3 curveCal(const vec3 c[4], float s1)
{
    vec3 a[3];
    a[0] = c[0]*(1.0-s1)+c[1]*s1;
    a[1] = c[1]*(1.0-s1)+c[2]*s1;
    a[2] = c[2]*(1.0-s1)+c[3]*s1;
    vec3 b[2];
    b[0] = a[0]*(1.0-s1)+a[1]*s1;
    b[1] = a[1]*(1.0-s1)+a[2]*s1;
    return b[0]*(1.0-s1)+b[1]*s1;
}

void main ()
{
    vec3 c1[4];
    vec3 c2[4];
    vec3 c3[4];
    vec3 c4[4];

    c1[0] = ctp[0];
    c1[1] = ctp[1];
    c1[2] = ctp[2];
    c1[3] = ctp[3];
    
    c2[0] = ctp[4];
    c2[1] = ctp[5];
    c2[2] = ctp[6];
    c2[3] = ctp[7];
    
    c3[0] = ctp[8];
    c3[1] = ctp[9];
    c3[2] = ctp[10];
    c3[3] = ctp[11];
    
    c4[0] = ctp[12];
    c4[1] = ctp[13];
    c4[2] = ctp[14];
    c4[3] = ctp[15];
    
    vec3 a[4];
    a[0] = curveCal(c1,s);
    a[1] = curveCal(c2,s);
    a[2] = curveCal(c3,s);
    a[3] = curveCal(c4,s);

    vtxOut = curveCal(a,t);
    gl_Position=projection*modelView*vec4(vtxOut,1.0);
}
