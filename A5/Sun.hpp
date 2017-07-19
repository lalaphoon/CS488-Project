//
//  Sun.hpp
//  
//
//  Created by Mengyi LUO on 2017-07-15.
//
//

#pragma once

#include "cs488-framework/GlErrorCheck.hpp"
#include "cs488-framework/MathUtils.hpp"
#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/MeshConsolidator.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include "Texture.hpp"

class Sun {
    
    
 public:
    Sun(){}
    Sun(Texture t, float s){
        this->texture = t;
        this->scale = s;
    }
    void setScale(float s){
        this->scale = s;
    }
    void setDirection(float x, float y, float z){
        this->lightDirection = glm::normalize(glm::vec3(x,y,z));
    }
    Texture getTexture(){
        return this->texture;
    }
    glm::vec3 getLightDirection(){
        return this->lightDirection;
    }
    float getScale(){
        return scale;
    }
    
    glm::vec3 getWorldPosition(glm::vec3 camPos){
        glm::vec3 sunPos = glm::vec3(lightDirection);
        sunPos = glm::vec3(-sunPos.x, -sunPos.y, -sunPos.z);
        sunPos *= SUN_DIS;
        return camPos + sunPos;
    }
    glm::vec3 getPosition(){
        return this->position;
    }
    
    void setPosition(glm::vec3 pos){
        this->position = pos;
    }
private:
    float SUN_DIS = 40.0f;
    Texture texture;
    glm::vec3 lightDirection = glm::vec3(0, -1, 0);
    float scale;
    glm::vec3 position;

};