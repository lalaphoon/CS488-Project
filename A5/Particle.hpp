//
//  Particle.hpp
//  CS488-Projects
//
//  Created by Mengyi LUO on 2017-06-30.
//  Copyright © 2017 none. All rights reserved.
//

#pragma once
#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include <glm/glm.hpp>

#include <stdio.h>
const int MaxParticles = 100;


struct Particle {

    
    glm::vec3 pos, speed;
    //unsigned char r,g,b,a; // Color
    float size;
    //angle, weight;
    float life; // Remaining life of the particle. if < 0 : dead and unused.
    Particle():life(-1),size(0.5){}
    
};

class ParticleContainer {
    
public:
    ParticleContainer();
    ParticleContainer(int count): amount(count){
       // pContainer =  Particle [amount];
    }
    ~ParticleContainer();
    
    int FindUnusedParticle();
    int countAliveParticles(GLfloat* g);
    void makeParticles(int num);
private:
    int amount;
    int LastUsedParticle = 0;
    Particle pContainer[MaxParticles];
    
    
    
};

