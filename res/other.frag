#version 150

uniform sampler2D tex;

in vec3 Color;
in vec2 TexCoord;

out vec4 outColor;

void main()
{
    outColor = texture(tex, TexCoord) * vec4(Color, 1);
}
