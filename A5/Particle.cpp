//
//  Particle.cpp
//  CS488-Projects
//
//  Created by Mengyi LUO on 2017-06-30.
//  Copyright © 2017 none. All rights reserved.
//

//reference2: http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/particles-instancing/
//reference: https://learnopengl.com/#!In-Practice/2D-Game/Particles

#include "Particle.hpp"
ParticleContainer::ParticleContainer(){}
ParticleContainer::~ParticleContainer(){}

void ParticleContainer::makeParticles(int num){
    //Genew particle
    float spread = 5.0f;
    for (int i=0;i< num;i++) {
        int index = FindUnusedParticle();
        
        
        if (index != -1) {
            pContainer[index].life = 1.0f;
            pContainer[index].size = (rand() % 10 + 1)/ 30.5f;
            //starting location
            pContainer[index].pos = glm::vec3(0.1,2.1,-3.5f);
            
            glm::vec3 dir = glm::vec3(0.0f,0.0f,-10.0f);
            
            // randir from -1 to 1
            glm::vec3 spread_dir = glm::vec3(
                                             (rand()%200 - 100.0f)/100.0f,
                                             (rand()%200 - 100.0f)/100.0f,
                                             (rand()%200 - 100.0f)/100.0f
                                             );
            
            pContainer[index].speed = dir + spread_dir*spread;
        }//index2
    }//for loop
}



int ParticleContainer::FindUnusedParticle(){
    for(int i=LastUsedParticle; i<MaxParticles; i++){
        if (pContainer[i].life <= 0.0f){
            LastUsedParticle = i;
            return i;
        }
    }
    
    for(int i=0; i<LastUsedParticle; i++){
        if (pContainer[i].life <= 0.0f){
            LastUsedParticle = i;
            return i;
        }
    }
    //LastUsedParticle = 0;
    return 0; // All particles are taken, override the first one
}


int ParticleContainer::countAliveParticles(GLfloat* g_particule_position_size_data){
    // Simulate all particles
    int ParticlesCount = 0;
    float delta = 0.1;
    for(int i=0; i<MaxParticles; i++){
        
        Particle& p = pContainer[i]; // shortcut
        
        if(p.life > 0.0f){
            
            // Decrease life
            p.life -= delta;
            if (p.life > 0.0f){
                
                // Simulate simple physics : gravity only, no collisions
                p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
                p.pos += p.speed * (float)delta;
               
                //p.cameradistance = glm::length( p.pos - CameraPosition );
                
                //ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;
                
                // Fill the GPU buffer
                g_particule_position_size_data[4*ParticlesCount+0] = p.pos.x;
                g_particule_position_size_data[4*ParticlesCount+1] = p.pos.y;
                g_particule_position_size_data[4*ParticlesCount+2] = p.pos.z;
                
                g_particule_position_size_data[4*ParticlesCount+3] = p.size;
                
              //  g_particule_color_data[4*ParticlesCount+0] = p.r;
              //  g_particule_color_data[4*ParticlesCount+1] = p.g;
              //  g_particule_color_data[4*ParticlesCount+2] = p.b;
               // g_particule_color_data[4*ParticlesCount+3] = p.a;
                
            }else{
                // Particles that just died will be put at the end of the buffer in SortParticles();
              //  p.cameradistance = -1.0f;
            }
            
            ParticlesCount++;
            
        }
    }
    return ParticlesCount;
}

