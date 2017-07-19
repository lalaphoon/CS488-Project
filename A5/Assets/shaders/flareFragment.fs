#version 330

in vec2 pass_textureCoords;

out vec4 out_colour;

uniform sampler2D flareTexture;
uniform float brightness;

void main(void){

    out_colour = texture(flareTexture, pass_textureCoords) + vec4(0.5, 0.5, 0.5, 0.0);
    out_colour.a *= brightness;
    //out_colour.a -= 0.2;


}