#version 330 core
in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = mix(texture(texture1, texCoords), texture(texture2, texCoords), 0.3);
}
