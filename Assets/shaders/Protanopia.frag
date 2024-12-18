uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixtel = vec4(pixel.r * 0.56667 + pixel.g * 0.43333 + pixel.b * 0.0,
                       pixel.r * 0.55833 + pixel.g * 0.44167 + pixel.b * 0.0,
                       pixel.r * 0.0 + pixel.g * 0.24167 + pixel.b * 0.75833,
                       1.0);
    gl_FragColor = pixtel * pixel;
}