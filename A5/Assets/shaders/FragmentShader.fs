#version 330

in vec2 textCoord;
in vec3 reflectedVector;
uniform bool reflected;

uniform sampler2D samUV;   //<-0
uniform sampler2D shadowMap; //<-1
uniform samplerCube envirMap;  //<-2

uniform sampler2D rTexture; // <-3
uniform sampler2D gTexture; // <-4
uniform sampler2D bTexture; //<-5
uniform sampler2D blendMap; //<-6
uniform bool blended;



struct LightSource {
    vec3 position;
    vec3 rgbIntensity;
};

in VsOutFsIn {
    vec3 position_ES; // Eye-space position
    vec3 normal_ES;   // Eye-space normal
    LightSource light;
    flat int umbra;
    vec4 lightSpace_ES;
} fs_in;


out vec4 fragColour;

struct Material {
    vec3 kd;
    vec3 ks;
    float shininess;
};
uniform Material material;

// Ambient light intensity for each RGB component.
uniform vec3 ambientIntensity;
in vec3 camPos;

//reference: https://learnopengl.com/#!Advanced-Lighting/Shadows/Shadow-Mapping

float ShadowCalculation(vec4 posLightSpace){
    vec3 projCoords = posLightSpace.xyz / posLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if(projCoords.x < 0.0) projCoords.x = 0.0;
    if(projCoords.y < 0.0) projCoords.y = 0.0;
    if(projCoords.x > 1.0) projCoords.x = 1.0;
    if(projCoords.y > 1.0) projCoords.y = 1.0;
    
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    
    vec3 lightDir = normalize(fs_in.light.position - fs_in.position_ES);
    float bias = max(0.05 * (1.0 - dot(normalize(fs_in.normal_ES), lightDir)), 0.005);
    
    float shadow = 0.0;
    
    vec2 texSize = 1.0/textureSize(shadowMap, 0);
    
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(i, j) + texSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    if (projCoords.z > 1.0) shadow = 0;
     
    
    //float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
    
    return shadow;
}


vec3 phongModel(vec3 fragPosition, vec3 fragNormal) {
    LightSource light = fs_in.light;
    
    // Direction from fragment to light source.
    vec3 l = normalize(light.position - fragPosition);
    
    // Direction from fragment to viewer (origin - fragPosition).
    vec3 v = normalize(-fragPosition.xyz);
    
    float n_dot_l = max(dot(fragNormal, l), 0.0);
    
    // for blending
    vec4 blendMapColor = texture(blendMap, textCoord);
    float backgroundTextureAmount =  1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
    vec2 tiledCoords = textCoord * 40.0;
    vec4 backgroundTextureColor = texture(samUV, tiledCoords) * backgroundTextureAmount;
    vec4 rTextureColour = texture(rTexture, tiledCoords) * blendMapColor.r;
    vec4 gTextureColour = texture(gTexture, tiledCoords) * blendMapColor.g;
    vec4 bTextureColour = texture(bTexture,tiledCoords) * blendMapColor.b;
    vec4 totalColour = backgroundTextureColor + rTextureColour + gTextureColour + bTextureColour;
    
    vec3 diffuse;
    if(blended){
       diffuse = totalColour.rgb * n_dot_l;
        
    } else {
      diffuse = texture(samUV, textCoord).rgb * n_dot_l;
    }
    
    
    
    
    
      // diffuse = material.kd * n_dot_l;
    
    vec3 specular = vec3(0.0);
    
    if (n_dot_l > 0.0) {
        // Halfway vector.
        vec3 h = normalize(v + l);
        float n_dot_h = max(dot(fragNormal, h), 0.0);
        
        specular = material.ks * pow(n_dot_h, material.shininess);
       
    }
    
    return ambientIntensity + light.rgbIntensity * (diffuse + specular);
}

vec4 Shader( vec3 fragPosition, vec3 fragNormal){
    
    
   
    vec3 color;
    
    if(blended){
        
        vec4 blendMapColor = texture(blendMap, textCoord);
        float backgroundTextureAmount =  1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
        vec2 tiledCoords = textCoord * 12.0;
        vec4 backgroundTextureColor = texture(samUV, tiledCoords) * backgroundTextureAmount;
        vec4 rTextureColour = texture(rTexture, tiledCoords) * blendMapColor.r;
        vec4 gTextureColour = texture(gTexture, tiledCoords) * blendMapColor.g;
        vec4 bTextureColour = texture(bTexture,tiledCoords) * blendMapColor.b;
        vec4 totalColour = backgroundTextureColor + rTextureColour + gTextureColour + bTextureColour;
        color = totalColour.rgb;
    } else {
        color = texture(samUV, textCoord).rgb;
    }
    
    vec3 normal = normalize(fragNormal);
    
    
    
    
    LightSource light = fs_in.light;
    //ambient
    vec3 ambient = 0.7 * color;
    //diffuse
    vec3 lightDir = normalize(light.position - fragPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * light.rgbIntensity;
    //specular
    vec3 viewDir = normalize(camPos -fragPosition.xyz);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular;
    specular = spec * light.rgbIntensity;
    
    float shadow;
    if (fs_in.umbra == 1) shadow = ShadowCalculation(fs_in.lightSpace_ES);
    else shadow = 0;
    
    
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    return vec4(lighting , 1.0);
    
}


void main() {
    vec4 reflectedColor = texture(envirMap, reflectedVector);
    
        fragColour = vec4(phongModel(fs_in.position_ES, fs_in.normal_ES), 1.0);
        fragColour = Shader(fs_in.position_ES, fs_in.normal_ES);
        if(reflected){  //<-- water
            vec4 blendMapColor = texture(blendMap, textCoord);
            
            fragColour = mix(fragColour, reflectedColor, 0.9);
            fragColour.a = blendMapColor.g * 0.5;
        }
    
       
    
}
