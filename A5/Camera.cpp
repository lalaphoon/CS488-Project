#include "Camera.hpp"
#include <stdio.h>
#include <iostream>


 Camera::Camera(){

 }

 Camera::Camera(SceneNode * player){

 	this->player = player;
 }

glm::vec3 Camera::getPosition(){
  	return position;
}

float Camera::getPitch(){
  	return pitch;
}

float Camera::getYaw(){
  	return yaw;
  
}

float Camera::getRoll(){
  	return roll;
  
}

void Camera::move(){
   //TODO:
    float horizontalDistance = calculateHorizontalDistance();
    float verticalDistance = calculateVerticalDistance();
    calculateCameraPosition(horizontalDistance, verticalDistance);
    this->yaw = 180 - (playerRolY  + angleAroundPlayer);
  
}

void Camera::updatePlayerPos(glm::vec3 pos){
    player_pos.x = pos.x;
    player_pos.y = pos.y;
    player_pos.z = pos.z;
}

void Camera::updatePlayerRolY(float rolY){
    playerRolY = rolY;
}

// mouse scroll
void Camera::calculateZoom(float zoomlevel){
  //	distanceFromPlayer -= zoomlevel;
    
    distanceFromPlayer -= zoomlevel;
   

  
}

// right mouse
void Camera::calculatePitch(float pitchChange){
  		pitch -= pitchChange;
  
}

// left mouse
void Camera::calculateAngleAroundPlayer(float angleChange){

      angleAroundPlayer -= angleChange;
}

float Camera::calculateHorizontalDistance(){
      return (float)(distanceFromPlayer * cos(glm::radians(pitch)));
  
}

float Camera::calculateVerticalDistance(){
    return (float)(distanceFromPlayer * sin(glm::radians(pitch)));
}

void Camera::calculateCameraPosition(float horizonDistance, float verticalDistance){
    float theta = playerRolY + angleAroundPlayer;
    float offsetX = (float)(horizonDistance * sin(glm::radians(theta)));
    float offsetZ = (float)(horizonDistance * cos(glm::radians(theta)));
    position.x = player_pos.x - offsetX;
    position.z = player_pos.z - offsetZ;
    position.y = player_pos.y + verticalDistance;
}

glm::mat4 Camera::generateViewMatrix(){
    glm::mat4 viewMatrix = glm::mat4(1.0);
    viewMatrix *= glm::rotate(glm::mat4(), (float)glm::radians(this->getPitch()), glm::vec3(1.0, 0.0, 0.0));
    viewMatrix *= glm::rotate(glm::mat4(), (float)glm::radians(this->getYaw()),glm::vec3(0.0, 1.0, 0.0));
    glm::vec3 negativeCameraPos = glm::vec3(-position.x, -position.y, -position.z);
    viewMatrix *= glm::translate(glm::mat4(), negativeCameraPos);
    return viewMatrix;
    
}





