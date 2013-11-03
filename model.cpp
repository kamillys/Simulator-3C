#include "model.h"
using namespace glm;

//#define SIMULATOR_USE_PATTERN
#define NOMRALS_WITH_GSHADER

std::string GLSL_Perlin =
        "vec4 mod289(vec4 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }"
        "vec4 permute(vec4 x) { return mod289(((x*34.0)+1.0)*x); }"
        "vec4 taylorInvSqrt(vec4 r) { return 1.79284291400159 - 0.85373472095314 * r; }"
        "vec2 fade(vec2 t) { return t*t*t*(t*(t*6.0-15.0)+10.0); }"

        /**
           CNoise
         **/
        "float cnoise(vec2 P)"
        "{"
        "vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);"
        "vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);"
        "Pi = mod289(Pi);"
        "vec4 ix = Pi.xzxz; vec4 iy = Pi.yyww;"
        "vec4 fx = Pf.xzxz; vec4 fy = Pf.yyww;"
        "vec4 i = permute(permute(ix) + iy);"
        "vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;"
        "vec4 gy = abs(gx) - 0.5 ; vec4 tx = floor(gx + 0.5);"
        "gx = gx - tx;"
        "vec2 g00 = vec2(gx.x,gy.x); vec2 g10 = vec2(gx.y,gy.y); vec2 g01 = vec2(gx.z,gy.z); vec2 g11 = vec2(gx.w,gy.w);"
        "vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));"
        "g00 *= norm.x; g01 *= norm.y; g10 *= norm.z; g11 *= norm.w;"
        "float n00 = dot(g00, vec2(fx.x, fy.x)); float n10 = dot(g10, vec2(fx.y, fy.y));"
        "float n01 = dot(g01, vec2(fx.z, fy.z)); float n11 = dot(g11, vec2(fx.w, fy.w));"
        "vec2 fade_xy = fade(Pf.xy);"
        "vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);"
        "float n_xy = mix(n_x.x, n_x.y, fade_xy.y); return 2.3 * n_xy;"
        "}"
        /**
           FBM
         **/

        "float fbm(vec2 P, int octaves, float lacunarity, float gain)"
        "{"
        "float sum = 0.0;"
        "float amp = 1.0;"
        "vec2 pp = P;"
        "int i;"
        "for(i = 0; i < octaves; i+=1)"
        "{"
        "amp *= gain;"
        "sum += amp * cnoise(pp);"
        "pp *= lacunarity;"
        "}"
        "return sum;"
        "}"
        /**
           Pattern
         **/
        "float pattern(in vec2 p) {"
        "float l = 2.5;"
        "float g = 0.4;"
        "int oc = 10;"
        "vec2 q = vec2( fbm( p + vec2(0.0,0.0),oc,l,g),fbm( p + vec2(5.2,1.3),oc,l,g));"
        "vec2 r = vec2( fbm( p + 4.0*q + vec2(1.7,9.2),oc,l,g ), fbm( p + 4.0*q + vec2(8.3,2.8) ,oc,l,g));"
        "return fbm( p + 4.0*r ,oc,l,g);"
        "}"
        "";

ModelMaterial::ModelMaterial(){
    shader = new VBGL::ShaderProgram;
    shader->addShader("#version 130\n"
                      "in vec3 in_vertices;""\n"
                      "out int vVP;"
                      "in int in_vertexProblems;\n"
                      "in float in_heightValues;\n"
                      "out vec3 pos;"
                      "uniform mat4 UMV;"
                      "uniform mat4 UMVP;"
                      "uniform mat4 UNormalMatrix;"
                      "void main(){""\n"
                      "pos = in_vertices;"
                      "pos.z += in_heightValues;"
                      "vVP = in_vertexProblems;"
                      "gl_Position = UMVP * vec4(pos, 1.0);"
                      "}""\n", VBGL::ShaderProgram::VertexShader);

    shader->addShader((std::string() +
                "#version 150\n"

                "layout(triangles) in;""\n"
                "layout(triangle_strip, max_vertices = 3) out;""\n"
                "in vec3 pos[];"
                "in int vVP[];"
                "out vec4 color;"
                "out vec3 gpos;"

                "void main(void) {""\n"
                "vec3 e0 = (pos[1]-pos[0]);"
                "vec3 e1 = (pos[2]-pos[1]);"
                "vec3 e2 = (pos[0]-pos[2]);"
                "vec4 normals = vec4(normalize(cross(e0, -e2)), 0);""\n"
                "int gVP=vVP[0]|vVP[1]|vVP[2];"
                "const vec4 lightDir = vec4(0,0,-1,0);"
                "float dt = dot(-lightDir.xyz, normals.xyz);"
                "float p = 0.3+0.7*dt*dt*dt*dt*dt*dt;"
                "p = clamp(p,0,1);"
                "color.a = 1;"
                //#EFC190
                "if (gVP == 0)"
                "{"
                "color.rgb = p*vec3(0.93,0.75,0.56);"
                "}"
                "else\n"
                "color.rgb = vec3(1,0,0);"

                "gpos=pos[0];gl_Position = gl_in[0].gl_Position; EmitVertex();""\n"
                "gpos=pos[1];gl_Position = gl_in[1].gl_Position; EmitVertex();""\n"
                "gpos=pos[2];gl_Position = gl_in[2].gl_Position; EmitVertex();""\n"
                "EndPrimitive();""\n"
                "}"
                       ).c_str(),VBGL::ShaderProgram::GeometryShader);

    shader->addShader((std::string() + "#version 130\n"
                       "in vec3 gpos;"
                       "in vec4 color;""\n"
                       "out vec4 fcolor;"
                       +GLSL_Perlin+
                       "void main(){""\n"
                       "fcolor = color;"
                   #ifdef SIMULATOR_USE_PATTERN
                       "float pat = pattern(0.001 * gpos.xy);"
                       "fcolor.xyz *= 0.5 + 0.5 * pat;"
                   #endif
                       ""
                       "}""\n").c_str(), VBGL::ShaderProgram::FragmentShader);
    shader->build();
}


glm::ivec2 Model::getSize() const
{
    return size;
}

Model::Model()
{
}

void Model::resize(glm::ivec2 s, glm::vec3 O, glm::vec3 S)
{
    int w = s.x, h = s.y;
    size = s;
    const float W = S.x;
    const float H = S.y;
    const float D = S.z;
    VBGL::Geometry* geometry = mesh->geometry();
    geometry->verticesClear();
    geometry->indicesClear();
    geometry->vertexProblemsClear();
    geometry->heightValuesClear();

    for (int i=0;i<w;++i) for (int j=0;j<h;++j)
    {
        glm::vec3 v = O+vec3(W*i/(w-1),H*j/(h-1), 0);
        //v.z = 0.1*(v.x * v.y + v.y * v.y);
        geometry->verticesAppend(v);
        geometry->vertexProblemsAppend(0);
        geometry->heightValuesAppend(D);
    }

    for (int i=0;i<w-1;++i) for (int j=0;j<h-1;++j)
    {
        geometry->indicesAppend(i*h+j); geometry->indicesAppend((i+1)*h+j); geometry->indicesAppend((i+1)*h+j+1);
        geometry->indicesAppend(i*h+j); geometry->indicesAppend((i+1)*h+j+1); geometry->indicesAppend(i*h+j+1);
    }
//    size_t vc = geometry->verticesCount();
//    for(int i=0;i<vc;++i)
//    {
//        vec3 v = geometry->vertices(i);
//        float d = distance(vec2(v), vec2(W,H)*0.5f);
//        if (d<W/2)
//            v.z = sqrt(W*W/4.0-d*d);
//        if (distance(vec2(v), vec2(W,0)*0.5f)<W/8)
//            geometry->vertexProblemsSet(i,1);
//        geometry->verticesSet(i, v);
    //    }
}



void Model::reset()
{
    VTF::RefPointer<VBGL::Geometry> geometry = new VBGL::Geometry;
    VTF::RefPointer<VBGL::Material> material = new ModelMaterial;
    mesh = new VBGL::Mesh(geometry, material);
    resize(glm::ivec2(128,128), glm::vec3(-50,-75,0),glm::vec3(100,150,50));
}

//void Model::randomMove()
//{
//    VBGL::Geometry* geometry = mesh->geometry();
//    size_t vc = geometry->verticesCount();
//    for (unsigned i=0;i<vc;++i)
//    {
//        vec3 v = geometry->vertices(i);
//        //v.z = randF();
//        //geometry->verticesSet(i, v);
//    }
//}

void Model::draw(VBGL::Camera *cam)
{
    mesh->draw(cam);
}
