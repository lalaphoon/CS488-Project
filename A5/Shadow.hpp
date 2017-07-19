//
//  Shadow.hpp
//  
//
//  Created by Mengyi LUO on 2017-07-17.
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
#include "Camera.hpp"
#include <vector>
const float NEAR_PLANE = -20.0f;
const float FOV = 35.0f;

class ShadowBox{
    
public:
    ShadowBox(){
        
    }
    ShadowBox(glm::mat4 lightViewMatrix, Camera camera){
        this->lightViewMatrix = lightViewMatrix;
        this->camera = camera;
        calculateWidthsAndHeights();
    }
    ~ShadowBox(){
    }
    
    void update(){
        glm::mat4 rotation = calculateCameraRotationMatrix();
        glm::vec3 result = glm::vec3(rotation * FORWARD);
        glm::vec3 forwardVector = result;
        glm::vec3 toFar = forwardVector;
        toFar *=  SHADOW_DISTANCE;
        glm::vec3 toNear = forwardVector;
        toNear *= NEAR_PLANE;  //<-- Near Plane value
        glm::vec3 centerNear = toNear + camera.getPosition();
        glm::vec3 centerFar = toFar + camera.getPosition();
        
        std::vector<glm::vec4> points = calculateFrustumVertices(rotation, forwardVector, centerNear, centerFar);
        bool first = true;
        for (int i = 0; i < points.size(); i++){
            if(first){
                minX = points[i].x;
                maxX = points[i].x;
                minY = points[i].y;
                maxY = points[i].y;
                minZ = points[i].z;
                maxZ = points[i].z;
                first = false;
                continue;
            }
            if(points[i].x > maxX){
                maxX = points[i].x;
            } else if  (points[i].x < minX){
                minX = points[i].x;
            }
            
            if (points[i].y > maxY){
                maxY = points[i].y;
            } else if (points[i].y < minY){
                minY = points[i].y;
            }
            
            if (points[i].z > maxZ){
                maxZ = points[i].z;
            } else if (points[i].z < minZ){
                minZ = points[i].z;
            }
        }
        
        maxZ += OFFSET;
    
    }
    
    glm::vec3 getCenter(){
        float x = (minX + maxX) / 2.0f;
        float y = (minY + maxY) / 2.0f;
        float z = (minZ + maxZ) / 2.0f;
        
        glm::vec4 cen = glm::vec4(x, y, z, 1.0);
        glm::mat4 invertedLight = glm::inverse(lightViewMatrix);
        glm::vec4 result = invertedLight * cen;
        return glm::vec3(result.x, result.y, result.z);
    }
    float getWidth(){
        return maxX - minX;
    }
    
    float getHeight(){
        return maxY - minY;
    }
    
    float getLength(){
        return maxZ - minZ;
    }
    
    std::vector<glm::vec4> calculateFrustumVertices(glm::mat4 rotation, glm::vec3 forwardVector, glm::vec3 centerNear, glm::vec3 centerFar){
        
        glm::vec3 upVector = glm::vec3(rotation * UP);
        glm::vec3 rightVector = glm::cross(forwardVector , upVector);
        glm::vec3 downVector = glm::vec3(-upVector.x, -upVector.y, -upVector.z);
        glm::vec3 leftVector = glm::vec3(-rightVector.x, -rightVector.y, -rightVector.z);
        glm::vec3 farTop = centerFar + glm::vec3(upVector.x * farHeight,
                                                 upVector.y * farHeight, upVector.z * farHeight);
        glm::vec3 farBottom = centerFar + glm::vec3(downVector.x * farHeight,
                                                    downVector.y * farHeight, downVector.z * farHeight);
        glm::vec3 nearTop = centerNear + glm::vec3(upVector.x * nearHeight,
                                                   upVector.y * nearHeight, upVector.z * nearHeight);
        glm::vec3 nearBottom = centerNear + glm::vec3(downVector.x * nearHeight,
                                                      downVector.y * nearHeight, downVector.z * nearHeight);
        std::vector<glm::vec4> points;
         points.push_back (calculateLightSpaceFrustumCorner(farTop, rightVector, farWidth));
         points.push_back (calculateLightSpaceFrustumCorner(farTop, leftVector, farWidth));
         points.push_back (calculateLightSpaceFrustumCorner(farBottom, rightVector, farWidth));
         points.push_back (calculateLightSpaceFrustumCorner(farBottom, leftVector, farWidth));
         points.push_back (calculateLightSpaceFrustumCorner(nearTop, rightVector, nearWidth));
         points.push_back (calculateLightSpaceFrustumCorner(nearTop, leftVector, nearWidth));
         points.push_back (calculateLightSpaceFrustumCorner(nearBottom, rightVector, nearWidth));
         points.push_back (calculateLightSpaceFrustumCorner(nearBottom, leftVector, nearWidth));
        return points;
        
    }
    glm::vec4 calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width){
        glm::vec3 point = startPoint + glm::vec3(direction.x * width, direction.y * width, direction.z * width);
        
        glm::vec4 point4f = glm::vec4(point.x, point.y, point.z, 1.0f);
        point4f = lightViewMatrix * point4f;
        return point4f;
    }
    glm::mat4 calculateCameraRotationMatrix(){
        glm::mat4 rotation = glm::mat4();
        rotation *= glm::rotate(glm::mat4(), (float)glm::radians(-camera.getYaw()), glm::vec3(0.0, 1.0, 0.0));
        rotation *= glm::rotate(glm::mat4(), (float)glm::radians(-camera.getPitch()), glm::vec3(1.0, 0.0, 0.0));
        return rotation;
    }
    void calculateWidthsAndHeights(){
        farWidth = (float) (SHADOW_DISTANCE * tan(glm::radians(FOV)));   //<-------Fov
        nearWidth =(float) NEAR_PLANE * tan(FOV);
        farHeight = farWidth / getAspectRatio();
        nearHeight = nearWidth / getAspectRatio();
        
    }
    
    // <---------------Width/height
    float getAspectRatio(){
        return (float)2048 / (float)2048;
    }
    
private:
    float OFFSET =10.0f;
    glm::vec4 UP = glm::vec4(0.0, 1.0, 0.0, 0.0);
    glm::vec4 FORWARD = glm::vec4(0.0, 0.0, -1.0, 0.0);
    float SHADOW_DISTANCE = 100;
    
    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
    glm::mat4 lightViewMatrix;
    Camera camera;
    float farHeight, farWidth, nearHeight, nearWidth;
    
    
};
