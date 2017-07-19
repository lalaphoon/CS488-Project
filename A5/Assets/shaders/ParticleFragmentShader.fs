#version 330

uniform sampler2D diffuse;
//uniform vec3 colour;

out vec4 fragColor;
in vec2 textCoord;

void main() {
    
    //fragColor = vec4(0.0, 0.98, 0.82, 0.5f);
    vec4 textColor = texture(diffuse, textCoord);
    if (textColor.a < 0.2) {
        discard;
    }
    fragColor = textColor;
   
}
