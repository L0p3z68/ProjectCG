#include <glad/glad.h> // Include GLAD for OpenGL functions

class Texture2D {
public:
    GLuint ID; // Texture ID
    GLuint Width, Height; // Texture dimensions
    GLuint Internal_Format, Image_Format; // Format of texture
    GLuint Wrap_S, Wrap_T, Filter_Min, Filter_Max; // Texture parameters

    // Constructor
    Texture2D();

    // Generates texture from image data
    void Generate(GLuint width, GLuint height, unsigned char* data);

    // Binds the texture for use
    void Bind() const;
};