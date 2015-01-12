#version 150

uniform vec2 size;

in vec2 position;
in vec3 color;
in vec2 texCoord;

out vec3 Color;
out vec2 TexCoord;

void main()
{
    vec2 temp = position;

    temp.x /= (size.x / 2);
    temp.x -= 1;

    temp.y /= (size.y / 2);
    temp.y -= 1;

    Color = color;
    TexCoord = texCoord;
    gl_Position = vec4(temp, 0, 1); // vec4(position, 0.0, 1.0);
}
