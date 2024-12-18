uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixtel = vec4(gl_Color.r * pixel.r * 0.95 + gl_Color.g * pixel.g * 0.05 + gl_Color.b * pixel.b * 0.0,
                       gl_Color.r * pixel.r * 0.0 + gl_Color.g * pixel.g * 0.43333 + gl_Color.b * pixel.b * 0.56667,
                       gl_Color.r * pixel.r * 0.0 + gl_Color.g * pixel.g * 0.475 + gl_Color.b * pixel.b * 0.525,
                       gl_Color.a);
    gl_FragColor = pixtel * pixel;
}