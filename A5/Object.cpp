//
//  Object.cpp
//  
//
//  Created by Mengyi LUO on 2017-07-13.
//
//

#include "Object.hpp"
#include <stdio.h>
#include <iostream>





Object::Object(){

}

Object::Object(glm::vec3 pos):position(pos){

}
Object::Object(std::string name, glm::vec3 pos):m_name(name), position(pos){
 
}
Object::Object(std::string name, glm::vec3 pos, float si): m_name(name), position(pos), size(si){

}

void Object::bindSceneNode(SceneNode * node){
    this->node = node;
}


void Object::move(){
    // change roty by currentTurn Speed
    RolY += currentTurnSpeed;
    //RolX += currentSpeed;
    
    upwardSpeed += GRAVITY * 0.001 ;
  
    float distance = currentSpeed;
    float dx = distance * sin(glm::radians(this->RolY));
    float dz = distance * cos(glm::radians(this->RolY));
    float dy = upwardSpeed;
    
    position.y += dy;
    if(position.y < 0.0){   //<=------ terrain height
       
        upwardSpeed = 0.0;
        isInAir = false;
        position.y = 0.0; //<---- teriain height
        dy = 0.0 - position.y;
    }
    
    
    
    this->d_position = glm::vec3(dx, dy, dz);
    updatePosition(glm::vec3(dx, dy, dz));

    
    
    //Animation for object

    rotateNode();
    transNode();
    
}
void Object::jump(){
  if (!isInAir){
        upwardSpeed = JUMP_POWER*0.01;
        isInAir = true;
    }
}


void Object::updateVisibility (bool v){
    this->visible = v;
}

bool Object::isVisible(){
    return this->visible;
}


void Object::updatePosition(glm::vec3 pos){
    this->position += pos;
}

void Object::updateCurrentSpeed(float speed){
    this->currentSpeed = speed;
}

void Object::updateCurrentTurnSpeed(float speed){
    this->currentTurnSpeed = speed;
}

glm::vec3 Object::getObjectPosition(){
    return this->position;
}

float Object::getObjectRolY(){
    return this->RolY;
}

float Object::getObjectRolX(){
    return this->RolX;
}

float Object::getObjectRolZ(){
    return this->RolZ;
}

glm::vec3 Object::getObjectDPosition(){
    return this->d_position;
}

std::string Object::getObjectName(){
    return this->m_name;
}

float Object::getObjectSize(){
    return this->size;
}

void Object::transNode(){
    glm::vec3 howmuch = glm::vec3(d_position.x, d_position.y ,d_position.z );
    glm::mat4 p = glm::translate(glm::mat4(), howmuch);
    node->set_transform( p * node->get_transform());
}
void Object::transNode(glm::vec3 v){
    glm::vec3 howmuch = glm::vec3(v.x, v.y ,v.z );
    glm::mat4 p = glm::translate(glm::mat4(), howmuch);
    node->set_transform( p * node->get_transform());
    
}
void Object::rotateNode(){
   
    
   /*
    if (currentSpeed != 0.0){
        
        glm::mat4 matrix = glm::mat4();
        matrix = glm::rotate( glm::mat4(), (float)glm::radians(currentSpeed * 31.4), glm::vec3(1.0, 0.0, 0.0));
        node->set_transform(  node->get_transform() * matrix);
        
    }
    */
     
   
    
    if (currentTurnSpeed != 0.0){
       glm::mat4 matrix = glm::mat4();
       matrix = glm::rotate( glm::mat4(), (float)glm::radians(currentTurnSpeed), glm::vec3(0.0, 1.0, 0.0));
       node->set_transform(  node->get_transform() * matrix);
    }
    
    
    
    
   // matrix *= glm::rotate( glm::mat4(), (float)glm::radians(currentSpeed * 20.0), glm::vec3(1.0, 0.0, 0.0));
  //  matrix *= glm::rotate( glm::mat4(), (float)glm::radians(currentTurnSpeed), glm::vec3(0.0, 1.0, 0.0));
   // matrix *= glm::rotate( glm::mat4(), (float)glm::radians(RolZ), glm::vec3(0.0, 0.0, 1.0));
  //  node->set_transform(  node->get_transform() * matrix);
    
}
void Object::rotateNode(float speed){
    if (currentTurnSpeed != 0.0){
        glm::mat4 matrix = glm::mat4();
        matrix = glm::rotate( glm::mat4(), (float)glm::radians(speed), glm::vec3(0.0, 1.0, 0.0));
        node->set_transform(  node->get_transform() * matrix);
    }

}






