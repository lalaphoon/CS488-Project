#version 330

// Model-Space coordinates
in vec3 position;
in vec3 normal;
in vec2 atextCoord;
in vec3 tangent;
in vec3 bitangent;

struct LightSource {
    vec3 position;
    vec3 rgbIntensity;
};

uniform LightSource light;

uniform mat4 ModelView;
uniform mat4 View;
uniform mat4 Perspective;

// Remember, this is transpose(inverse(ModelView)).  Normals should be
// transformed using this matrix instead of the ModelView matrix.
uniform mat3 NormalMatrix;


uniform int umbra;
uniform mat4 lightSpace;
uniform vec3 cameraPosition;

out VsOutFsIn {
	vec3 position_ES; // Eye-space position
	vec3 normal_ES;   // Eye-space normal
    
    vec3 tangent_ES;
    vec3 bitangent_ES;
    
	LightSource light;
    vec4 lightSpace_ES; // FragPosLightSpace
    flat int umbra;
} vs_out;
out vec2 textCoord;

//reflection
out vec3 reflectedVector;

out vec3 camPos;
out mat3 TBN;


void main() {
	vec4 pos4 = vec4(position, 1.0);
    vec4 worldPosition = ModelView * pos4;
    vec3 viewVector = normalize(worldPosition.xyz - cameraPosition);

	//-- Convert position and normal to Eye-Space:
	vs_out.position_ES = vec3(  ModelView * pos4);
	vs_out.normal_ES = normalize(NormalMatrix * normal);
    
    vs_out.tangent_ES = normalize(NormalMatrix * tangent);
    vs_out.bitangent_ES = normalize(NormalMatrix * bitangent);

	vs_out.light = light;
    
    vs_out.umbra = umbra;
    //vs_out.lightSpace_ES = lightSpace * ModelView * pos4;   ////<-------------------- Model View -> Model
    //vs_out.lightSpace_ES = lightSpace * vec4(vs_out.position_ES, 1.0);
    vs_out.lightSpace_ES = lightSpace * vec4(vec3(ModelView * pos4), 1.0);
   
    

	gl_Position = Perspective * View * ModelView * vec4(position, 1.0);
    textCoord = atextCoord;
    reflectedVector = reflect(viewVector, normalize(normal));
    camPos = cameraPosition;
    TBN =  transpose(mat3(
                          vs_out.tangent_ES,
                          vs_out.bitangent_ES,
                          vs_out.normal_ES
                          ));
    
   
}
