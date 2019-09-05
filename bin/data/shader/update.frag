#version 410
#pragma include "utils/ShaderHelpers.glslinc"
#pragma include "utils/SimplexNoiseDerivatives4D.glslinc"
#pragma include "utils/Noise.glslinc"

uniform sampler2D   u_Position;
uniform sampler2D   u_Properties;
uniform sampler2D  u_InitialPos;

uniform float   u_Time;
uniform vec2    u_Res;
uniform float   u_Delta;

uniform float     u_min_Age;
uniform float     u_max_Age;
uniform float     u_noiseScale;
uniform float     u_noiseTime;
uniform float     u_noisePersist;


in vec2 fragUV;

layout(location = 0) out vec4 out_Position;
layout(location = 1) out vec4 out_Properties;

void    main()
{
    vec4 positionBuffer = texture(u_Position,fragUV);
    vec4 propertiesBuffer =  texture(u_Properties,fragUV);
    vec4 initial = texture(u_InitialPos,fragUV);

    vec3    position = positionBuffer.xyz;
    float   age = propertiesBuffer.x;
    float   ageMood =  propertiesBuffer.y;
    float     ageLimit = mix(u_min_Age,u_max_Age,ageMood);

    age+=u_Delta;
    if(age >= ageLimit){
        age=0.0;
        ageMood = rand(position.xy+vec2(u_Time,0.0));
        position.xyz = initial.xyz;
    }
   
    float noiseTime = u_Time*u_noiseTime;
    vec3 noise = curlNoise(position.xyz*u_noiseScale, noiseTime, 1, u_noisePersist);

    position.xyz+=noise*u_Delta;

    out_Position = vec4(position.xyz,1.0);
    out_Properties = vec4(age,ageMood,0.0,1.0);

}