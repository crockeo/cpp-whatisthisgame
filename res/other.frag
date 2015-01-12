#version 150

uniform sampler2D tex;

in vec3 pass_color;
in vec2 pass_texCoord;

out vec4 out_color;

void main()
{
    out_color = texture(tex, pass_texCoord) * vec4(pass_color, 1);
}
