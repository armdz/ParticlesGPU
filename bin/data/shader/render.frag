#version 410

in vec2 fragUV;
out vec4    outColor;

in float fragLifeNormal;



void    main()
{
    vec3 N = vec3(0.0);
    N.xy = gl_PointCoord.xy*vec2(2.0, -2.0) + vec2(-1.0, 1.0);
    float r2 = dot(N.xy, N.xy);
    if (r2 > 1.0) discard; 
    N.z = sqrt(1.0-r2);
    outColor = vec4(vec3(0.0),1.0-fragLifeNormal);
}