uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixtel = vec4(pixel.r * 0.625 + pixel.g * 0.375 + pixel.b * 0.0,
                       pixel.r * 0.7 + pixel.g * 0.3 + pixel.b * 0.0,
                       pixel.r * 0.0 + pixel.g * 0.3 + pixel.b * 0.7,
                       1.0);
    gl_FragColor = pixtel * pixel;
}