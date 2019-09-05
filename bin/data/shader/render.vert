#version 410

uniform sampler2D   u_Position;
uniform sampler2D   u_Properties;
uniform vec2 u_Res;
uniform vec3 u_Scale;

uniform float     u_min_Age;
uniform float     u_max_Age;
uniform float     u_Born_Scale;
uniform float     u_Dead_Scale;

layout (location = 3) in vec2 uv;

uniform mat4 modelViewProjectionMatrix;

in vec3 position;
out vec2 fragUV;

out float fragLifeNormal;

void    main()
{
    fragUV = uv;
    
    vec4 positionBuffer = texture(u_Position,fragUV);
    vec4 propertiesBuffer =  texture(u_Properties,fragUV);
    vec3 position = positionBuffer.xyz;
    float     age = propertiesBuffer.x;
    float     ageMood =  propertiesBuffer.y;
    float     ageLimit = mix(u_min_Age,u_max_Age,ageMood);

    float lifeNormal = clamp(age/ageLimit,0.0,1.0);
    fragLifeNormal = lifeNormal;

    position.xyz*=u_Scale;
    position.x-=u_Scale.x*.5;
    position.y-=u_Scale.y*.5;

    gl_PointSize = mix(u_Born_Scale,u_Dead_Scale,lifeNormal);
    gl_Position = modelViewProjectionMatrix*vec4(position.xyz,1.0);

}