#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/GlErrorCheck.hpp"

#include "SceneNode.hpp"
//reference: https://www.youtube.com/watch?v=PoxDDZmctnU&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=19




class Camera{
    public:
        Camera();
        Camera(SceneNode * player);
        glm::vec3 getPosition();
        float getPitch();
        float getYaw();
        float getRoll();
        void move();
  
        void updatePlayerPos(glm::vec3 pos);
        void updatePlayerRolY(float rolY);

        void calculateZoom(float zoomlevel); // middle key
        void calculatePitch(float pitchChange); // right mouse
        void calculateAngleAroundPlayer(float angleChange); // left mouse
        float calculateHorizontalDistance();
        float calculateVerticalDistance();
        void calculateCameraPosition(float horizonDistance, float verticalDistance);
    
        glm::mat4 generateViewMatrix();
  
    private:
        glm::vec3 position = glm::vec3(0.0);
        float pitch = 20.0f;
        float yaw = 0.0;
        float roll;


        float distanceFromPlayer = 13.0f;
        float angleAroundPlayer = 0.0f;


        SceneNode* player;
        glm::vec3 player_pos;
        float playerRolY;
  
};