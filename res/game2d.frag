#version 150

uniform sampler2D in_tex;

in vec2 pass_texCoord;

out vec4 out_color;

void main() {
    out_color = texture(in_tex, pass_texCoord);
}
