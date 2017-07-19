#include "Skybox.hpp"
#include "stb_image.hpp"
#include <iostream>



Skybox::Skybox(){
}


Skybox::Skybox(const char* front,const char* back, const char* top, const char* bottom,const char* left,const char* right){
    //right
    //left
    //top
    //bottom
    //back
    //front
    
    faces.push_back(right);
    faces.push_back(left);
    faces.push_back(top);
    faces.push_back(bottom);
    faces.push_back(back);
    faces.push_back(front);
}



// Draw the skybox using the skybox shader
void Skybox::draw(ShaderProgram& s){

/*
  GLint posAttrib = s.getAttribLocation( "position" );

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP,tex);
  GLint cube = s.getUniformLocation("cubeMap");
  glUniform1i(cube,0);

  glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

  glDrawArrays (GL_TRIANGLES, 0, 36);

  glBindBuffer(GL_ARRAY_BUFFER,0);
    */
    
    //glDepthMask(GL_FALSE);
    


}
void Skybox::setUp(){
    
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP,tex);
    
    int width,height,nrChannels;
    for (unsigned int i =0; i < faces.size(); i++){
        unsigned char* data = stbi_load(faces[i], &width, &height, &nrChannels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
        
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
     
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
  
    
 /*
    // load each image and copy into a side of the cube-map texture
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1,&tex);
  glBindTexture(GL_TEXTURE_CUBE_MAP,tex);


  loadSide ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
  loadSide ( GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
  loadSide (GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
  loadSide ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
  loadSide ( GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
  loadSide (GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
    
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  float points[] = {
  -10.0f,  10.0f, -10.0f,
  -10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,

  -10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,

   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,

  -10.0f, -10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,

  -10.0f,  10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f, -10.0f,

  -10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f,  10.0f
};

  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points, GL_STATIC_DRAW);
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  CHECK_GL_ERRORS;
  
  
  */
    
    
    
}


GLuint Skybox::getTexture(){
  return tex;
}

// Load a side of the cube texture
void Skybox::loadSide(GLenum side,const char*file){
  int w,h, numComponents;
  unsigned char* image = stbi_load(file,&w,&h,&numComponents,4);
  if(image==NULL){
    std::cerr << "Error loading " << file << std::endl;
    return;
  }
  glTexImage2D(side, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

 stbi_image_free(image);
}
