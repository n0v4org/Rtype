uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixtel = vec4(pixel.r * 0.95 + pixel.g * 0.05 + pixel.b * 0.0,
                       pixel.r * 0.0 + pixel.g * 0.43333 + pixel.b * 0.56667,
                       pixel.r * 0.0 + pixel.g * 0.475 + pixel.b * 0.525,
                       1.0);
    gl_FragColor = pixtel * pixel;
}