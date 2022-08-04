#version 330 core
out vec4 FragColor;



void main() {
    /*vec2 u_resolution=vec2(1200,900);
    vec2 ndc_xy = -1.0 + 2.0 * gl_FragCoord.xy/u_resolution.xy;
    
    
    if((ndc_xy.x*ndc_xy.x)+(ndc_xy.y*ndc_xy.y)<=(radius*radius))
    {
        FragColor=vec4(0.78, 0.07, 0.22, 1);
    }
    else{
        FragColor=vec4(0.0782, 0.0782, 0.0782, 1);
    }*/
    FragColor=vec4(0.06, 0.84, 0.77, 1);
}