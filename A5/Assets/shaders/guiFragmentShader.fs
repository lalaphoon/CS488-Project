#version 140

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D guiTexture;

uniform bool life;
uniform float lifeValue;

void main(void){
   
    if(life){
        out_Color = vec4((1.0 - lifeValue),lifeValue,0.0,1.0);
    
    } else {
        vec4 textColor = texture(guiTexture,textureCoords);
        if (textColor.a < 0.2){
            discard;
        }
        out_Color = textColor;
        out_Color.a = 0.0;
    }

}