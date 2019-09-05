#version 410


uniform mat4    modelViewProjectionMatrix;

in vec2 texcoord;
in vec3 position;
out vec2 fragUV;

void    main()
{
    fragUV = texcoord;
    gl_Position = modelViewProjectionMatrix*vec4(position,1.0);
}