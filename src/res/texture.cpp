#include "texture.hpp"

//////////////
// Includes //
#include <iostream>
#include <cstdlib>
#include <png.h>

//////////
// Code //

// Loading a png texture from the disk. I stole it from stackoverflow. Too lazy
GLuint png_texture_load(const char* file_name, int* width, int* height) {
    png_byte header[8];

    FILE* fp = fopen(file_name, "rb");
    if (fp == 0) {
        perror(file_name);
        return 0;
    }

    // read the header
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        std::cerr << "Error: " << file_name << " is not a png!" << std::endl;
        fclose(fp);
        return 0;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        std::cerr << "Error: png_create_read_struct returned 0." << std::endl;
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        std::cerr << "Error: png_create_info_struct returned 0." << std::endl;
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        std::cerr << "Error: png_create_info_struct returned 0." << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return 0;
    }

    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "Random libpng error!" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);

    if (width)
        *width = temp_width;
    if (height)
        *height = temp_height;

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes - 1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte* image_data;
    image_data = (png_byte*)malloc(rowbytes * temp_height * sizeof(png_byte));
    memset(image_data, 0, rowbytes * temp_height * sizeof(png_byte));
    if (image_data == NULL) {
        std::cerr << "Error: Could not allocate memory for PNG image data." << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep* row_pointers = (png_bytep*)malloc(temp_height * sizeof(png_bytep));
    if (row_pointers == NULL) {
        std::cerr << "Error: Could not allocate memory for PNG row pointers." << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(fp);
        return 0;
    }

    // set the individual row_pointers to point at the correct offsets of image_data
    int i;
    for (i = 0; i < temp_height; i++) {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // Generate the OpenGL texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp_width, temp_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , temp_width, temp_height, 0, GL_RGB , GL_UNSIGNED_BYTE, image_data);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(fp);
    return texture;
}

// The new copy constructor for this thingy.
Texture::Texture(const Texture& t) {
    this->id = t.id;
    this->original = false;
}

// Loading a texture from a location on the disk.
Texture::Texture(std::string path) {
    this->id = png_texture_load(path.c_str(), &this->width, &this->height);
    this->original = true;
}

// Deleting this texture.
Texture::~Texture() {
    if (this->original)
        glDeleteTextures(1, &this->id);
}

// Accessing the texture id.
GLuint Texture::getID() const { return this->id; }

// Getting the texture coordinates.
std::vector<GLfloat> Texture::getTextureCoords() const{
    std::vector<GLfloat> tc {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    return tc;
}

// Checking if the texture is good.
bool Texture::good() const { return this->getID() != 0; }

// Getting the texture width and height respectively.
int Texture::getWidth()  const { return this->width; }
int Texture::getHeight() const { return this->height; }
