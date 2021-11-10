#version 330 core

struct Material {
  // vec3 ambient; // Same with diffuse
  sampler2D diffuse; // Set diffuse map from texture color
  sampler2D specular; // Set specular map from texture color
  float shininess;
};
struct PhongModel {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
struct AttnConst {
  float constant;
  float linear;
  float quadratic;
};
struct DirLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
struct PointLight {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
struct SpotLight {
  vec3 position;
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float flashCosPhi;
  float flashCosGamma;
};

out vec4 FRAGCOLOR;

in vec3 NORMAL;
in vec3 FRAGPOS;
in vec2 TEXCOORD;

uniform vec3 CAMPOS;
uniform Material MATERIAL;
uniform AttnConst ATTNCONST;
uniform DirLight DIRLIGHT;
#define NPOINTLIGHTS 1 // TODO: HOW TO REMOVE THIS
uniform PointLight POINTLIGHTS[NPOINTLIGHTS];
uniform SpotLight SPOTLIGHT;

PhongModel UpdatePhongModel(PhongModel phongModel, vec3 unitNormal,
                            vec3 viewDir, vec3 lightDir);
vec3 CalcDirLight(DirLight dirLight, vec3 unitNormal, vec3 viewDir);
vec3 CalcPointLight(PointLight pointLight, vec3 unitNormal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight spotLight, vec3 unitNormal, vec3 viewDir);

void main() {
  vec3 unitNormal = normalize(NORMAL);
  vec3 viewDir = normalize(CAMPOS - FRAGPOS);

  vec3 shadedRGB;
  shadedRGB += CalcDirLight(DIRLIGHT, unitNormal, viewDir);
  for (int idx = 0; idx < NPOINTLIGHTS; idx++)
    shadedRGB += CalcPointLight(POINTLIGHTS[idx], unitNormal, viewDir);
  shadedRGB += CalcSpotLight(SPOTLIGHT, unitNormal, viewDir);

  FRAGCOLOR = vec4(shadedRGB, 1.0);
}

PhongModel UpdatePhongModel(PhongModel phongModel, vec3 unitNormal,
                            vec3 viewDir, vec3 lightDir) {
  // Ambient lighting
  float ambientStrength = 1.0;

  // Diffuse lighting
  float diffuseStrength = max(dot(unitNormal, lightDir), 0.0);

  // Specular lighting
  vec3 reflectDir = reflect(-lightDir, unitNormal);
  float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0),
                               MATERIAL.shininess);

  // Light mapping with texture
  // ambientMap == diffuseMap
  vec3 diffuseMap = vec3(texture(MATERIAL.diffuse, TEXCOORD));
  vec3 specularMap = vec3(texture(MATERIAL.specular, TEXCOORD));

  // Phong modeling
  vec3 ambient = diffuseMap * phongModel.ambient * ambientStrength;
  vec3 diffuse = diffuseMap * phongModel.diffuse * diffuseStrength;
  vec3 specular = specularMap * phongModel.specular * specularStrength;
  PhongModel updatedPhongModel = PhongModel(ambient, diffuse, specular);

  return updatedPhongModel;
}

vec3 CalcDirLight(DirLight dirLight, vec3 unitNormal, vec3 viewDir) {
  // Phong modeling
  vec3 lightDir = normalize(-dirLight.direction);
  PhongModel phongModel = PhongModel(dirLight.ambient, dirLight.diffuse,
                                     dirLight.specular);
  PhongModel updatedPhongModel = UpdatePhongModel(phongModel, unitNormal,
                                                  viewDir, lightDir);
  vec3 shadedRGB = updatedPhongModel.ambient + updatedPhongModel.diffuse +
                   updatedPhongModel.specular;
  return shadedRGB;
}

vec3 CalcPointLight(PointLight pointLight, vec3 unitNormal, vec3 viewDir) {
  // Phong modeling
  vec3 lightDir = normalize(pointLight.position - FRAGPOS);
  PhongModel phongModel = PhongModel(pointLight.ambient, pointLight.diffuse,
                                     pointLight.specular);
  PhongModel updatedPhongModel = UpdatePhongModel(phongModel, unitNormal,
                                                  viewDir, lightDir);

  // Light attenuation
  float lightDist = length(pointLight.position - FRAGPOS);
  float attenuation = 1.0 / (ATTNCONST.constant + ATTNCONST.linear *
                             lightDist + ATTNCONST.quadratic * pow(lightDist,
                                                                    2));

  vec3 shadedRGB = (updatedPhongModel.ambient + updatedPhongModel.diffuse +
                    updatedPhongModel.specular) * attenuation;
  return shadedRGB;
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 unitNormal, vec3 viewDir) {
  // Phong modeling
  vec3 lightDir = normalize(spotLight.position - FRAGPOS);
  PhongModel phongModel = PhongModel(spotLight.ambient, spotLight.diffuse,
                                     spotLight.specular);
  PhongModel updatedPhongModel = UpdatePhongModel(phongModel, unitNormal,
                                                  viewDir, lightDir);

  // Light attenuation
  float lightDist = length(spotLight.position - FRAGPOS);
  float attenuation = 1.0 / (ATTNCONST.constant + ATTNCONST.linear *
                             lightDist + ATTNCONST.quadratic * pow(lightDist,
                                                                   2));

  // Light smoothing
  float flashCosTheta = dot(lightDir, normalize(-spotLight.direction));
  float flashIntensity = clamp((flashCosTheta - spotLight.flashCosGamma) /
                               (spotLight.flashCosPhi -
                                spotLight.flashCosGamma), 0.0, 1.0);

  vec3 shadedRGB = (updatedPhongModel.ambient + (updatedPhongModel.diffuse +
                    updatedPhongModel.specular) * flashIntensity) *
                    attenuation;
  return shadedRGB;
}
