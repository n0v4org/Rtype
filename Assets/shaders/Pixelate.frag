uniform sampler2D texture;
uniform float pixel_threshold;

void main()
{
    float factor = 1.0 / (pixel_threshold + 0.0001);
    vec2 pos = floor(gl_TexCoord[0].xy * factor + 0.01) / factor;
    gl_FragColor = texture2D(texture, pos) * gl_Color;
}