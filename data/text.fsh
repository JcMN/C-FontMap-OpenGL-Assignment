uniform sampler2D texture1;
uniform vec4 textColor;
uniform bool tt;


in vec2 v_uv1;

out vec4 PixelColor;

void main(){
    vec4 sampled = texture(texture1, v_uv1);
    
    if (tt == false && length(sampled.rgb - vec3(0.0, 0.0, 0.0)) < 0.15){
        discard;
    }

    if (tt){
        PixelColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        PixelColor = vec4(textColor.r, textColor.g, textColor.b, 1.0);
    }
    
    
}