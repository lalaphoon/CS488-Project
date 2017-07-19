#version 330

in vec3 vert;
in vec4 position;


in vec2 atextCoord;

//uniform mat4 transform;
//out vec2 textCoord;
uniform mat4 view;
uniform mat4 model;
uniform mat4 perspective;

out vec2 textCoord;

void main() {
    float size = position.w;
    vec3 pos = position.xyz;
    
    vec3 cr = vec3(view[0][0],view[1][0],view[2][0]);
    vec3  cu = vec3(view[0][1],view[1][1],view[2][1]);
    vec3 finalPos = pos  + cr * vert.x * size + cu * vert.y * size;
   
    
	//gl_Position = transform * vec4(position, 1.0);
    //gl_Position = vec4(position.x/position.z, position.y/position.z,1.0,1.0) * vec4(vert,1.0);
   // textCoord = atextCoord;
    gl_Position = perspective * view * model * vec4(finalPos,1.0);
    textCoord = atextCoord;
}