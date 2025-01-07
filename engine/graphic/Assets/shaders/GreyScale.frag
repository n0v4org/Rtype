uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixtel = vec4(255,
                       255,
                       255,
                       pixel.r * 0.299 + pixel.g * 0.587 + pixel.b * 0.114);
    gl_FragColor = pixtel * pixel;
}