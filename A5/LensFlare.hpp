//
//  LensFlare.hpp
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

class FlareTexture {
public:
    Texture texture;
    float scale;
    glm::vec2 screenPos;
    FlareTexture(){
    }
    FlareTexture(Texture t, float s){
        this->texture = t;
        this->scale = s;
        
    }
    
    void setScreenPos(glm::vec2 newPos){
        this->screenPos = newPos;
    }
    
    Texture getTexture() {
        return texture;
    }
    
    float getScale(){
        return scale;
    }
    
    glm::vec2 getScreenPos(){
        return screenPos;
    }
    
};
