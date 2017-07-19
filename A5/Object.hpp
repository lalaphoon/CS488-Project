//
//  Object.hpp
//  
//
//  Created by Mengyi LUO on 2017-07-13.
//
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/GlErrorCheck.hpp"

#include "SceneNode.hpp"

 static   float RUN_SPEED = 20;
 static  float TURN_SPEED = 160;
 static  float JUMP_POWER = 20;
 static  float GRAVITY = -10;

class Object{
    
public:
    Object();
    Object( glm::vec3 pos);
    Object(std::string name, glm::vec3 pos);
    Object(std::string name, glm::vec3 pos, float si);
    
    void bindSceneNode(SceneNode * node);
    
    void move();
    void jump();
    
    void updatePosition(glm::vec3 pos);
    void updateCurrentSpeed(float speed);
    void updateCurrentTurnSpeed(float speed);
    
    void updateVisibility (bool v);
    
    glm::vec3 getObjectPosition();
    glm::vec3 getObjectDPosition();
    
    float getObjectRolY();
    float getObjectRolX();
    float getObjectRolZ();
    
    float getObjectSize();
    
    bool isVisible();
    
    std::string getObjectName();
    
    void transNode();
    void transNode(glm::vec3 v);
    void rotateNode();
    void rotateNode(float speed);
    
    //=============== Like Camera
    
    
    
    
    
    
    
    
    
private:
    
    bool visible = true; // by default every object should show up at the first time
    
    glm::vec3 position = glm::vec3(0.0);
    glm::vec3 d_position = glm::vec3(0.0);
    
    float size = 0.0f;
    
    
    float RolY= 0.0f;
    float RolX = 0.0f;
    float RolZ = 0.0f;
    
    
    
    float currentSpeed = 0.0;
    float currentTurnSpeed = 0.0;
    float upwardSpeed = 0.0;
    bool isInAir = false;
    
    std::string m_name;
    SceneNode * node;
    
};