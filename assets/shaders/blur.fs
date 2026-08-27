#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

// simple box blur - raise blurSize for a stronger effect
const float blurSize = 1.0 / 300.0;

void main()
{
    vec4 sum = vec4(0.0);

    sum += texture(texture0, vec2(fragTexCoord.x - 4.0*blurSize, fragTexCoord.y)) * 0.05;
    sum += texture(texture0, vec2(fragTexCoord.x - 3.0*blurSize, fragTexCoord.y)) * 0.09;
    sum += texture(texture0, vec2(fragTexCoord.x - 2.0*blurSize, fragTexCoord.y)) * 0.12;
    sum += texture(texture0, vec2(fragTexCoord.x - 1.0*blurSize, fragTexCoord.y)) * 0.15;
    sum += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y))               * 0.16;
    sum += texture(texture0, vec2(fragTexCoord.x + 1.0*blurSize, fragTexCoord.y)) * 0.15;
    sum += texture(texture0, vec2(fragTexCoord.x + 2.0*blurSize, fragTexCoord.y)) * 0.12;
    sum += texture(texture0, vec2(fragTexCoord.x + 3.0*blurSize, fragTexCoord.y)) * 0.09;
    sum += texture(texture0, vec2(fragTexCoord.x + 4.0*blurSize, fragTexCoord.y)) * 0.05;

    // vertical blur, sampled from the original texture again (kept simple)
    vec4 sumV = vec4(0.0);
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y - 4.0*blurSize)) * 0.05;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y - 3.0*blurSize)) * 0.09;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y - 2.0*blurSize)) * 0.12;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y - 1.0*blurSize)) * 0.15;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y))               * 0.16;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y + 1.0*blurSize)) * 0.15;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y + 2.0*blurSize)) * 0.12;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y + 3.0*blurSize)) * 0.09;
    sumV += texture(texture0, vec2(fragTexCoord.x, fragTexCoord.y + 4.0*blurSize)) * 0.05;

    finalColor = mix(sum, sumV, 0.5) * colDiffuse * fragColor;
}
