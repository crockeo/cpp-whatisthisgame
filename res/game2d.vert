#version 150

uniform vec2 in_size;

in vec3 in_vertexCoord;
in vec2 in_texCoord;

out vec2 pass_texCoord;

void  main() {
    vec3 temp = in_vertexCoord;

    temp.x /= in_size.x / 2;
    temp.x -= 1;

    temp.y /= in_size.y / 2;
    temp.y -= 1;

    pass_texCoord = in_texCoord;
    gl_Position = vec4(temp, 1);
}
