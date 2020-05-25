#version 120
uniform sampler2D texture;
uniform float time;

void main() {
    vec2 coord = gl_TexCoord[0].xy;
    vec4 pixel_color = texture2D(texture, coord);
    float alpha = 0.5 + 0.5 * cos(5 * time);

    gl_FragColor = vec4 (pixel_color.xyz,min(alpha,pixel_color.w));
}