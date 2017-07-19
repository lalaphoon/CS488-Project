//
//  Texture.hpp
//  CS488-Projects
//
//  Created by Mengyi LUO on 2017-06-27.
//  Copyright © 2017 none. All rights reserved.
//
#pragma once


#include <stdio.h>
#include <iostream>
#include "lodepng.hpp"

//#include <glew/include/GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <cassert>

using namespace std;

class Texture
{
public:
    Texture();
   // void setUp(const std::string & fileName);
    void setUp(const std::string & fileName, bool flare = false);
    void Bind(unsigned int unit, bool flare = false); //determine which texture you use
    virtual ~Texture();
GLuint m_texture; // handle for texture
private:
    
    //Texture(const Texture& other);
    
};