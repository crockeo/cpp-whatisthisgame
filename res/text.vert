#version 330

uniform vec2 in_size;

in vec4 in_coords;

out vec2 pass_textureCoords;

void main() {
    vec2 temp = in_coords.xy;

    temp.x /= in_size.x / 2;
    temp.x -= 1;

    temp.y /= in_size.y / 2;
    temp.y -= 1;

    pass_textureCoords = in_coords.zw;
    gl_Position = vec4(temp, 0, 1);
}
