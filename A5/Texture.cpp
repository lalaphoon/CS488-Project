//
//  Texture.cpp
//  CS488-Projects
//
//  Created by Mengyi LUO on 2017-06-27.
//  Copyright © 2017 none. All rights reserved.
//

#include "Texture.hpp"
#include "stb_image.hpp"
#include <array>
Texture::Texture(){
    
}
/*
void Texture::setUp(const std::string& fileName){
    
    int width, height, numComponents;
    //float* imageData = stbi_loadf(fileName.c_str(), &width, &height, &numComponents, 4);
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
    if(imageData == NULL){
        cerr << "Texture loading failed for "<<fileName<< endl;
    }
    
    
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    
    stbi_image_free(imageData);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}*/

void Texture::setUp(const std::string& fileName, bool flare){
    
    if (flare == false){
        
    int width, height, numComponents;
    
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
    if(imageData == NULL){
        cerr << "Texture loading failed for ... "<<fileName<< endl;
    }
    
    
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    
    stbi_image_free(imageData);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    } else {
        int width, height, numComponents;
        
        unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
        if(imageData == NULL){
            cerr << "Texture loading failed for ... "<<fileName<< endl;
        }
        
        
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        
        
        stbi_image_free(imageData);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
    
    }
}
Texture::~Texture(){
    if (m_texture!=0) {
         //glDeleteTextures(1, &m_texture);
    }
}

void Texture::Bind(unsigned int unit, bool flare){
    if (flare == false){
        assert(unit >= 0 && unit <= 31);
        glActiveTexture(GL_TEXTURE0 + unit);
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    } else  {
        assert(unit >= 0 && unit <= 31);
        glActiveTexture(GL_TEXTURE0 + unit);
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_1D, m_texture);
    }
}