//
//  Gui.hpp
//  
//
//  Created by Mengyi LUO on 2017-07-18.
//
//
#pragma once

#include "Texture.hpp"
#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/MeshConsolidator.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Gui{
public:
    Gui(){}
    ~Gui(){}
    
    Gui(Texture texture, glm::vec2 pos, glm::vec2 s){
        this->texture = texture;
        this->position = pos;
        this->scale = s;
        this->visibility = true;
    
    }
    Gui(Texture texture, glm::vec2 pos, glm::vec2 s, bool v){
        this->texture = texture;
        this->position = pos;
        this->scale = s;
        this->visibility = v;
        
    }
    Texture getTexture(){
        return this->texture;
    }
    glm::vec2 getPosition(){
        return this->position;
    }
    glm::vec2 getScale(){
        return this->scale;
    }
    void setVisible(bool v){
        this->visibility = v;
    }
    bool getVisibility(){
        return visibility;
    }
private:
    Texture texture;
    glm::vec2 position;
    glm::vec2 scale;
    bool visibility;
};