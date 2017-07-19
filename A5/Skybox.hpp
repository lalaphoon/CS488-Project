#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/GlErrorCheck.hpp"
#include <vector>
//reference: https://github.com/nelk/cs488/blob/master/handin/A5/proposal/proposal.pdf
//reference2: https://learnopengl.com/#!Advanced-OpenGL/Cubemaps




class Skybox{
public:
    Skybox();
  Skybox(const char* front,const char* back, const char* top, const char* bottom,const char* left,const char* right);
  void setUp();
  void draw(ShaderProgram& s);
  GLuint getTexture();
  GLuint tex;
private:
  
    
  void loadSide(GLenum side,const char*file);
  
    std::vector<const char*> faces;
  GLuint vbo;
  GLuint blockIbo;
};