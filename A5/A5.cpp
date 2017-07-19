#include "A5.hpp"
#include "scene_lua.hpp"
using namespace std;

#include "cs488-framework/GlErrorCheck.hpp"
#include "cs488-framework/MathUtils.hpp"
#include "GeometryNode.hpp"
#include "JointNode.hpp"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>

#include "stb_image.hpp"


using namespace glm;
using namespace std;

static bool show_gui = true;

bool reflection;
bool blended;
bool blendMap_option;
bool normaled;
bool shadow_option;

bool end_game_option;

int life = 3;

const size_t CIRCLE_PTS = 48;
float turtle_init_speed = 0.0;

Texture earth_tex, plane_tex, egg_tex, bubble_tex, sun_tex, water_tex;
Texture blendMap_tex, grassFlower_tex, path_tex, mud_tex;
Texture house_tex, houseBlend_tex;
Texture shell2D_tex, egg2D_tex;
Texture gamestart_tex, youwin_tex, youlose_tex;
Texture turtle_tex;
Texture tree_tex;
Texture earth_normal_tex;

Texture tex2;
Texture tex3;
Texture tex4;
Texture tex5;
Texture tex6;
Texture tex7;
Texture tex8;
Texture rainbow_tex;


FlareTexture flare2;
FlareTexture flare3;
FlareTexture flare4;
FlareTexture flare5;
FlareTexture flare6;
FlareTexture flare7;
FlareTexture flare8;

//particles
static GLfloat * particle_position_size;
int LastUsedParticle = 0;


const unsigned int SHADOW_WIDTH = 5024, SHADOW_HEIGHT = 5024;

static const GLfloat skyboxVertices[] = {
    -10.0f,  10.0f, -10.0f,
    -10.0f, -10.0f, -10.0f,
    10.0f, -10.0f, -10.0f,
    10.0f, -10.0f, -10.0f,
    10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f,
    
    -10.0f, -10.0f,  10.0f,
    -10.0f, -10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f, -10.0f,
    -10.0f,  10.0f,  10.0f,
    -10.0f, -10.0f,  10.0f,
    
    10.0f, -10.0f, -10.0f,
    10.0f, -10.0f,  10.0f,
    10.0f,  10.0f,  10.0f,
    10.0f,  10.0f,  10.0f,
    10.0f,  10.0f, -10.0f,
    10.0f, -10.0f, -10.0f,
    
    -10.0f, -10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,
    10.0f,  10.0f,  10.0f,
    10.0f,  10.0f,  10.0f,
    10.0f, -10.0f,  10.0f,
    -10.0f, -10.0f,  10.0f,
    
    -10.0f,  10.0f, -10.0f,
    10.0f,  10.0f, -10.0f,
    10.0f,  10.0f,  10.0f,
    10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f,  10.0f,
    -10.0f,  10.0f, -10.0f,
    
    -10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f,  10.0f,
    10.0f, -10.0f, -10.0f,
    10.0f, -10.0f, -10.0f,
    -10.0f, -10.0f,  10.0f,
    10.0f, -10.0f,  10.0f
};

vec3 particle_vertex_buffer_data[] = {
    vec3( -0.5f, -0.5f, 0.0f),
    vec3( 0.5f, -0.5f, 0.0f),
    vec3( -0.5f, 0.5f, 0.0f),
    vec3( 0.5f, 0.5f, 0.0f)
};


vec2 flare_vertex_buffer_data[] = {
    vec2( -0.5f, -0.5f),
    vec2( -0.5f, 0.5f),
    vec2( 0.5f, -0.5f),
    vec2( 0.5f, 0.5f)
};


vec2 gui_vertex_buffer_data[] = {
    vec2(-1.0, 1.0),
    vec2(-1.0, -1.0),
    vec2(1.0, 1.0),
    vec2(1.0, -1.0)
};

//----------------------------------------------------------------------------------------
// Constructor
A3::A3(const std::string & luaSceneFile)
: m_luaSceneFile(luaSceneFile),
m_positionAttribLocation(0),
m_normalAttribLocation(0),
m_vao_meshData(0),
m_vbo_vertexPositions(0),
m_vbo_vertexNormals(0),
m_vao_arcCircle(0),
m_vbo_arcCircle(0),
m_vao_skybox(0),
m_vao_flare(0),
m_vbo_flarePosition(0),
m_vao_gui(0),
m_vbo_gui(0)

{
    reset();
    
    texture = Texture();
    earth_tex = Texture();
    plane_tex = Texture();
    egg_tex = Texture();
    bubble_tex =  Texture();
    water_tex = Texture();
    shell2D_tex = Texture();
    egg2D_tex = Texture();
    turtle_tex = Texture();
    
    earth_normal_tex = Texture();
    
    blendMap_tex =  Texture();
    grassFlower_tex =  Texture();
    path_tex =  Texture();
    mud_tex = Texture();
    tree_tex = Texture();
    
    gamestart_tex = Texture();
    youwin_tex = Texture();
    youlose_tex = Texture();
    
    //house
    house_tex = Texture();
    houseBlend_tex = Texture();
    
    
    // flares texture
    sun_tex = Texture();
    tex8 = Texture();
    tex2 = Texture();
    tex3 = Texture();
    tex4 = Texture();
    tex5 = Texture();
    tex6 = Texture();
    tex7 = Texture();
    rainbow_tex = Texture();
  
   
    const char* front = "Assets/skybox/sky_ft.png";
    const char* back = "Assets/skybox/sky_bk.png";
    const char* up = "Assets/skybox/sky_up.png";
    const char* down = "Assets/skybox/sky_dn.png";
    const char* left = "Assets/skybox/sky_rt.png";
    const char* right = "Assets/skybox/sky_lf.png";
    
    skybox = Skybox(front, back, up, down, left, right);
    
    
    player =  Object("player", player_pos, 0.7);
    egg = Object("egg", glm::vec3(0.0, -0.8, 15.0), 0.5);
    egg1 = Object("egg1", glm::vec3(-9.0, -0.8, 18.0), 0.5);
    egg2 = Object("egg2", glm::vec3(7.0, -0.8, 21.0), 0.5);
    
    turtle = Object("turtle", glm::vec3(5.0, -0.8, 5.0), 1.0 ); //<---size might be not right
    turtle1 = Object("turtle1", glm::vec3(5.0, -0.8, 0.0), 1.0 );
    turtle2 = Object("turtle2", glm::vec3(-5.0, -0.8, 5.0), 1.0 );
    
    particle_position_size = new GLfloat[MaxParticles * 4];
    turtle_init_speed = 0.0;
    
    
}

//----------------------------------------------------------------------------------------
// Destructor
A3::~A3()
{
   // delete skybox;
}

















//===================for A3==============================================
void A3::reset(){

    option_circle = false;
    option_zBuffer = true;
    option_backfaceCulling = false;
    option_frontfaceCulling = false;
    current_mode = mode_position;
    leftKey = false;
    middleKey = false;
    rightKey =  false;
    
    TRANSPOSITION = glm::mat4();
    ORIENTATION = glm::mat4();
    TMP = glm::mat4();
    last_one = -1;
    for(int i =0; i < selected.size();i++){
        selected[i]= false;
    }
}
void A3::resetPosition(){
    m_rootNode->set_transform(glm::inverse(TRANSPOSITION) * m_rootNode->get_transform());
    TRANSPOSITION = glm::mat4();
}
void A3::resetOrientation(){
    m_rootNode->set_transform( m_rootNode->get_transform() * glm::inverse(ORIENTATION));
    ORIENTATION = glm::mat4();
}
void A3::resetJoints(){
    for (int i = 0; i <= last_one; i++) {
        for (int j = 0; j < theProcess[i].ids.size(); j++) {
            SceneNode *node = getNode(m_rootNode, theProcess[i].ids[j]);
            if (node->m_nodeType == NodeType::JointNode) {
                node->set_transform(node->get_transform() * inverse(theProcess[i].T));
            }
        }
    }
    
    theProcess.clear();
    last_one = -1;
}

void A3::add_a_process(std::vector<unsigned int> ids, glm::mat4 T){
    process_cmd pro = {ids, T};
    theProcess.resize(last_one+1);
    theProcess.push_back(pro);
    last_one++;
}

void A3::undo(){
    if (theProcess.empty() || last_one < 0) return;
    for (unsigned int i = 0; i < theProcess[last_one].ids.size(); i++) {
        SceneNode *node = getNode(m_rootNode, theProcess[last_one].ids[i]);
        if (!node) return;
        node->set_transform(node->get_transform() * inverse(theProcess[last_one].T));
    }
    last_one--;
}
void A3::redo() {
    if (theProcess.empty() || last_one+1 == theProcess.size()) return;
    last_one++;
    for (unsigned int i = 0; i < theProcess[last_one].ids.size(); i++) {
        SceneNode *node = getNode(m_rootNode, theProcess[last_one].ids[i]);
        if (!node) return;
        node->set_transform(node->get_transform() * theProcess[last_one].T);
    }
}
//================================For A3 above============================================

































//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void A3::init()
{
    // Set the background colour.
    glClearColor(0.0, 0.75, 1.0, 1.0);
    
    createShaderProgram();
    
    glGenVertexArrays(1, &m_vao_arcCircle);
    glGenVertexArrays(1, &m_vao_meshData);
    glGenVertexArrays(1, &m_vao_skybox);
    glGenVertexArrays(1, &m_vao_flare);
    glGenVertexArrays(1, &m_vao_sun);
    glGenVertexArrays(1, &m_vao_gui);
    
    enableVertexShaderInputSlots();
    
    processLuaSceneFile(m_luaSceneFile);
    
    // Load and decode all .obj files at once here.  You may add additional .obj files to
    // this list in order to support rendering additional mesh types.  All vertex
    // positions, and normals will be extracted and stored within the MeshConsolidator
    // class.
    unique_ptr<MeshConsolidator> meshConsolidator (new MeshConsolidator{
        //getAssetFilePath("cube.obj"),
        //getAssetFilePath("sphere.obj"),
        //getAssetFilePath("suzanne.obj"),
        "Assets/models/water.obj",
        "Assets/models/sphere.obj",
        "Assets/models/maze.obj",
        "Assets/models/egg.obj",
        "Assets/turtle/turtle2.obj",
        "Assets/tree/tree.obj",
        "Assets/house/house.obj"
        
        //getAssetFilePath("cow.obj")
    });
    
    
    // Acquire the BatchInfoMap from the MeshConsolidator.
    meshConsolidator->getBatchInfoMap(m_batchInfoMap);
    
    // Take all vertex data within the MeshConsolidator and upload it to VBOs on the GPU.
    uploadVertexDataToVbos(*meshConsolidator);
    
    mapVboDataToVertexShaderInputLocations();
    
    initPerspectiveMatrix();
    
    initViewMatrix();
    
    initLightSources();
    
    readInModel(m_rootNode);
    
    reflection = false;
    blended = false;
    normaled = false;
    blendMap_option = true; //<--- initially I want to see this
    shadow_option = false; //<---- initilaly I don't want to see this
    
    
    end_game_option =  false;
    
    // Exiting the current scope calls delete automatically on meshConsolidator freeing
    // all vertex data resources.  This is fine since we already copied this data to
    // VBOs on the GPU.  We have no use for storing vertex data on the CPU side beyond
    // this point.
    
    shadowFrame();
    
    
    bgm = irrklang::createIrrKlangDevice();
    bgm->play2D("Assets/sound/heal.mp3", true);
    
    texture.setUp("Assets/texture/grass.png");
    plane_tex.setUp("Assets/terrian/grass.png");
    earth_tex.setUp("Assets/texture/earth.bmp");
    egg_tex.setUp("Assets/texture/egg.jpg");
    bubble_tex.setUp("Assets/texture/bubble.png");
    water_tex.setUp("Assets/texture/water.jpg");
    sun_tex.setUp("Assets/lensFlare/sun.png", true);
    shell2D_tex.setUp("Assets/gui/tor.png");
    egg2D_tex.setUp("Assets/gui/nest.png");
    turtle_tex.setUp("Assets/turtle/turtle.png");
    tree_tex.setUp("Assets/tree/tree.png");
    earth_normal_tex.setUp("Assets/texture/earthNormal.jpg");
    
    skybox.setUp();
    
    //Blending map setup for the plane
    blendMap_tex.setUp("Assets/terrian/blendMap2.png");  //<-3
    grassFlower_tex.setUp("Assets/terrian/grassFlowers.png");    //<-4
    path_tex.setUp("Assets/terrian/path.png");     //<-5
    mud_tex.setUp("Assets/terrian/mud.jpg");      //<-6
    
    //house texture setup
    house_tex.setUp("Assets/house/houseDiffuse.png");
    houseBlend_tex.setUp("Assets/house/houseExtra.png");
    
    youlose_tex.setUp("Assets/gui/YouLose.png");
    youwin_tex.setUp("Assets/gui/YouWin.png");
    gamestart_tex.setUp("Assets/gui/GameStart.png");
    
    
    
    
    
    
    
    //sun
    sun = Sun(sun_tex, 50.0);
    sun.setDirection(0, -0.2f, 1);
    
    //Lens flare
    tex8.setUp("Assets/lensFlare/tex8.png", true);
    tex2.setUp("Assets/lensFlare/tex2.png", true);
    tex3.setUp("Assets/lensFlare/tex3.png", true);
    tex4.setUp("Assets/lensFlare/tex4.png", true);
    tex5.setUp("Assets/lensFlare/tex5.png", true);
    tex6.setUp("Assets/lensFlare/tex6.png", true);
    tex7.setUp("Assets/lensFlare/tex7.png", true);
    

    
    
    flare8 = FlareTexture(tex8, 0.6f);
    flare2 = FlareTexture(tex2, 0.1f);
    flare3 = FlareTexture(tex3, 0.06f);
    flare4 = FlareTexture(tex4, 0.5f);
    flare5 = FlareTexture(tex5, 0.07f);
    flare6 = FlareTexture(tex6, 0.5f);
    flare7 = FlareTexture(tex7, 0.2f);
  
    
    //flare8.setScreenPos(glm::vec2(0.5, 0.5f));  // <=== Bill Board
    List_of_flares.push_back(FlareTexture(tex6, 0.5f));
    List_of_flares.push_back(FlareTexture(tex4, 0.23f));
    List_of_flares.push_back(FlareTexture(tex2, 0.1f));
    List_of_flares.push_back(FlareTexture(tex7, 0.05f));
    List_of_flares.push_back(FlareTexture(tex3, 0.06f));
    List_of_flares.push_back(FlareTexture(tex5, 0.07f));
    List_of_flares.push_back(FlareTexture(tex7, 0.2f));
    List_of_flares.push_back(FlareTexture(tex3, 0.07f));
    List_of_flares.push_back(FlareTexture(tex5, 0.3f));
    List_of_flares.push_back(FlareTexture(tex4, 0.4f));
    List_of_flares.push_back(FlareTexture(tex8, 0.6f));
    
    
    //Bind scene node with objects
    player.bindSceneNode(getNode(m_rootNode,player.getObjectName()));
    
    egg.bindSceneNode(getNode(m_rootNode, egg.getObjectName()));
    egg1.bindSceneNode(getNode(m_rootNode, egg1.getObjectName()));
    egg2.bindSceneNode(getNode(m_rootNode, egg2.getObjectName()));
    
    //TURTLE
    turtle.bindSceneNode(getNode(m_rootNode, turtle.getObjectName()));
    turtle1.bindSceneNode(getNode(m_rootNode, turtle1.getObjectName()));
    turtle2.bindSceneNode(getNode(m_rootNode, turtle2.getObjectName()));
    
    turtleBucket.push_back(turtle);
    turtleBucket.push_back(turtle1);
    turtleBucket.push_back(turtle2);
    
    eggBasket.push_back(egg);
    eggBasket.push_back(egg1);
    eggBasket.push_back(egg2);
    
    
    guiBucket.push_back(Gui(shell2D_tex, vec2(-0.5, -0.8), vec2(0.08, 0.1), true));
    guiBucket.push_back(Gui(egg2D_tex, vec2(0.5, -0.8), vec2(0.08, 0.1), true));
    guiBucket.push_back(Gui(gamestart_tex, vec2(0.0,0.0), vec2(1.0,1.0), true));  //<-- 2
    guiBucket.push_back(Gui(youlose_tex, vec2(0.0, 0.0), vec2(1.0, 1.0), false)); //<-3
    guiBucket.push_back(Gui(youwin_tex, vec2(0.0, 0.0), vec2(1.0, 1.0), false)); //<- 4
    
    
}











void A3::readInModel( SceneNode* root){
    
    if(root == NULL){
        return;
    }
    
    for (SceneNode * node : root->children) {
        
        if (node->m_nodeType == NodeType::GeometryNode){
           
        
        
        const GeometryNode * geometryNode = static_cast<const GeometryNode *>(node);
        
        glm::mat4 T = geometryNode->trans;
        xforms.push_back(T);
        cols.push_back(geometryNode->material.kd);
        selected.push_back(false);
        shapes.push_back(geometryNode->meshId);
        //id.push_back(geometryNode->m_nodeId);
        nodeId_to_id[geometryNode->m_nodeId] = selected.size()-1;
        id_to_nodeId[selected.size()-1] = geometryNode->m_nodeId;
        }
        readInModel(node);
        
        
    }
  
}

void A3::markAllNodes(SceneNode* node){
    if (node == NULL){
        return ;
    }
    for (SceneNode* nodes : node->children){
        int id = nodeId_to_id[nodes->m_nodeId];
        selected[id] = !selected[id];
        markAllNodes(nodes);
    }
}
void A3::selectNode( SceneNode * root , unsigned int id){
    for (SceneNode * node : root->children) {
        if(node->m_nodeId == id ) {
            
            int id = nodeId_to_id[node->m_nodeId];
            selected[id] = !selected[id];
            markAllNodes(node);
            return;
        }
        
        if(node->children.size() > 0)
            selectNode(node, id);
    }
}
SceneNode * A3::getNode(SceneNode* node, unsigned int id){
    if(node->m_nodeId == id) {
        return node;
    }
    for (SceneNode* child: node->children){
        SceneNode * current = getNode(child, id);
        if (current){
            return current;
        }
    }
    return NULL;
}
SceneNode * A3::getNode(SceneNode* node, std::string name){
    if(node->m_name == name) {
        return node;
    }
    for (SceneNode* child: node->children){
        SceneNode * current = getNode(child, name);
        if (current){
            return current;
        }
    }
    return NULL;
}
SceneNode * A3::findParentNode(SceneNode* node, unsigned int id){
    for (SceneNode * child : node->children){
        if (child->m_nodeId== id){
            return node;
        }
        SceneNode * parent = findParentNode(child, id);
        if(parent){
            return parent;
        }
    }
    return NULL;

}

//----------------------------------------------------------------------------------------
void A3::processLuaSceneFile(const std::string & filename) {
    // This version of the code treats the Lua file as an Asset,
    // so that you'd launch the program with just the filename
    // of a puppet in the Assets/ directory.
     std::string assetFilePath = getAssetFilePath(filename.c_str());
    // m_rootNode = std::shared_ptr<SceneNode>(import_lua(assetFilePath));
    
    // This version of the code treats the main program argument
    // as a straightforward pathname.
   // m_rootNode = std::shared_ptr<SceneNode>(import_lua(filename));
    m_rootNode = (SceneNode*) (import_lua(assetFilePath));
    if (!m_rootNode) {
        std::cerr << "Could not open " << filename << std::endl;
    }
}

























//===========dsaf===============
//
//
//           init
//
//
//==============================


//----------------------------------------------------------------------------------------
void A3::createShaderProgram()
{
    m_shader.generateProgramObject();
    m_shader.attachVertexShader( getAssetFilePath("/shaders/VertexShader.vs").c_str() );
    m_shader.attachFragmentShader( getAssetFilePath("/shaders/FragmentShader.fs").c_str() );
    m_shader.link();
    
    m_shader_arcCircle.generateProgramObject();
    m_shader_arcCircle.attachVertexShader( getAssetFilePath("/shaders/arc_VertexShader.vs").c_str() );
    m_shader_arcCircle.attachFragmentShader( getAssetFilePath("/shaders/arc_FragmentShader.fs").c_str() );
    m_shader_arcCircle.link();
    
    m_skybox_shader.generateProgramObject();
    m_skybox_shader.attachVertexShader( getAssetFilePath("/skybox/SkyboxVert.vs").c_str() );
    m_skybox_shader.attachFragmentShader( getAssetFilePath("/skybox/SkyboxFrag.fs").c_str() );
    m_skybox_shader.link();
    
    m_sun_shader.generateProgramObject();
    m_sun_shader.attachVertexShader( getAssetFilePath("/shaders/sunVertex.vs").c_str() );
    m_sun_shader.attachFragmentShader( getAssetFilePath("/shaders/sunFragment.fs").c_str() );
    m_sun_shader.link();
    
    m_flare_shader.generateProgramObject();
    m_flare_shader.attachVertexShader( getAssetFilePath("/shaders/flareVertex.vs").c_str() );
    m_flare_shader.attachFragmentShader( getAssetFilePath("/shaders/flareFragment.fs").c_str() );
    m_flare_shader.link();
    
    m_shadow_shader.generateProgramObject();
    m_shadow_shader.attachVertexShader( getAssetFilePath("/shaders/shadowVS.vs").c_str() );
    m_shadow_shader.attachFragmentShader( getAssetFilePath("/shaders/shadowFS.fs").c_str() );
    m_shadow_shader.link();
    
    m_particle_shader.generateProgramObject();
    m_particle_shader.attachVertexShader(getAssetFilePath("/shaders/ParticleVertexShader.vs").c_str());
    m_particle_shader.attachFragmentShader( getAssetFilePath("/shaders/ParticleFragmentShader.fs").c_str() );
    m_particle_shader.link();
    
    m_gui_shader.generateProgramObject();
    m_gui_shader.attachVertexShader(getAssetFilePath("/shaders/guiVertexShader.vs").c_str());
    m_gui_shader.attachFragmentShader(getAssetFilePath("/shaders/guiFragmentShader.fs").c_str());
    m_gui_shader.link();
}

//----------------------------------------------------------------------------------------
void A3::enableVertexShaderInputSlots()
{
    //-- Enable input slots for m_vao_meshData:
    {
        glBindVertexArray(m_vao_meshData);
        
        // Enable the vertex shader attribute location for "position" when rendering.
        m_positionAttribLocation = m_shader.getAttribLocation("position");
        glEnableVertexAttribArray(m_positionAttribLocation);
        
        // Enable the vertex shader attribute location for "normal" when rendering.
        m_normalAttribLocation = m_shader.getAttribLocation("normal");
        glEnableVertexAttribArray(m_normalAttribLocation);
        
        
        m_uvAttribLocation = m_shader.getAttribLocation("atextCoord");
        glEnableVertexAttribArray(m_uvAttribLocation);
        
        m_tangentAttribLocation = m_shader.getAttribLocation("tangent");
        glEnableVertexAttribArray(m_tangentAttribLocation);
        
        m_bitangentAttribLocation = m_shader.getAttribLocation("bitangent");
        glEnableVertexAttribArray( m_bitangentAttribLocation);
        
        glBindVertexArray(0);
        
        CHECK_GL_ERRORS;
    }
    
    
    {
        glBindVertexArray(m_vao_meshData);
        GLuint m_shadow_position = m_shadow_shader.getAttribLocation("position");
        glEnableVertexAttribArray(m_shadow_position);
       // cout << "getting shadow_position"<< m_shadow_position <<endl;
        glBindVertexArray(0);
    }
    
    
    //lens flare
    {
        glBindVertexArray(m_vao_flare);
        GLuint m_flare_position = m_flare_shader.getAttribLocation("in_position");
        glEnableVertexAttribArray(m_flare_position);
        glBindVertexArray(0);
        //CHECK_GL_ERRORS;
        CHECK_GL_ERRORS;
    
    }
    
    //sun
    {
        glBindVertexArray(m_vao_sun);
        GLuint m_sun_position = m_sun_shader.getAttribLocation("in_position");
        glEnableVertexAttribArray(m_sun_position);
        glBindVertexArray(0);
        //CHECK_GL_ERRORS;
        CHECK_GL_ERRORS;
    
    }
    
    //skybox
    {
        glBindVertexArray(m_vao_skybox);
        GLuint m_skybox_position = m_skybox_shader.getAttribLocation("position");
        glEnableVertexAttribArray(m_skybox_position);
       // cout << "getting sky posiiton "<< m_skybox_position <<endl;
        glBindVertexArray(0);
        //CHECK_GL_ERRORS;
        CHECK_GL_ERRORS;
        
    
    }
    //gui
    {
        glBindVertexArray(m_vao_gui);
        GLuint m_gui_position = m_gui_shader.getAttribLocation("position");
        glEnableVertexAttribArray(m_gui_position);
        glBindVertexArray(0);
        CHECK_GL_ERRORS;
    }
    
    //particles
    {
        glGenVertexArrays(1, &m_vao_particle);
        glBindVertexArray(m_vao_particle);
        //all vertices
        GLint particleVertAttribLocation = m_particle_shader.getAttribLocation( "vert" );
        glEnableVertexAttribArray(particleVertAttribLocation);
        
        // positions of particles, center
        GLint positionAttribLocation = m_particle_shader.getAttribLocation( "position" );
        glEnableVertexAttribArray(positionAttribLocation);
        
        // the color of the particles
        //  positionAttribLocation = particle_shader.getAttribLocation( "color" );
        // glEnableVertexAttribArray(positionAttribLocation);
        
        particleUVLocation = m_particle_shader.getAttribLocation("atextCoord");
        glEnableVertexAttribArray(particleUVLocation);
        
        // Restore defaults
        glBindVertexArray(0);
        
        //CHECK_GL_ERRORS;
        CHECK_GL_ERRORS;
    
    }
    
    
    
    
    
    
    
    //-- Enable input slots for m_vao_arcCircle:
    {
        glBindVertexArray(m_vao_arcCircle);
        
        // Enable the vertex shader attribute location for "position" when rendering.
        m_arc_positionAttribLocation = m_shader_arcCircle.getAttribLocation("position");
        glEnableVertexAttribArray(m_arc_positionAttribLocation);
        
        CHECK_GL_ERRORS;
    }
    
    // Restore defaults
    glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------
void A3::uploadVertexDataToVbos (
                                 const MeshConsolidator & meshConsolidator
                                 ) {
    //1  Generate VBO to store all vertex position data
    {
        glGenBuffers(1, &m_vbo_vertexPositions);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexPositions);
        glBufferData(GL_ARRAY_BUFFER, meshConsolidator.getNumVertexPositionBytes(),
                     meshConsolidator.getVertexPositionDataPtr(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
    
    
    // 2 Generate VBO to store all vertex normal data
    
        glGenBuffers(1, &m_vbo_vertexNormals);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexNormals);
        glBufferData(GL_ARRAY_BUFFER, meshConsolidator.getNumVertexNormalBytes(),
                     meshConsolidator.getVertexNormalDataPtr(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
    
        
    //3
    
        glGenBuffers(1, &m_vbo_vertexTextCoords);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexTextCoords);
        glBufferData(GL_ARRAY_BUFFER, meshConsolidator.getNumVertexUVBytes(),
                     meshConsolidator.getVertexUVDataPtr(),GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
        
        
    // 4
        glGenBuffers(1, &m_vbo_vertexTangents);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexTangents);
        glBufferData(GL_ARRAY_BUFFER, meshConsolidator.getNumVertexTangentsBytes(),
                     meshConsolidator.getVertexTangentsPtr(),GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
        
    //5
        glGenBuffers(1, &m_vbo_vertexBitangents);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexBitangents);
        glBufferData(GL_ARRAY_BUFFER, meshConsolidator.getNumVertexBitangentsBytes(),
                     meshConsolidator.getVertexBitangentsPtr(),GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
        
    }
    
    
    
    
    
    
    // Generate VBO to store the trackball circle.
    {
        glGenBuffers( 1, &m_vbo_arcCircle );
        glBindBuffer( GL_ARRAY_BUFFER, m_vbo_arcCircle );
        
        float *pts = new float[ 2 * CIRCLE_PTS ];
        for( size_t idx = 0; idx < CIRCLE_PTS; ++idx ) {
            float ang = 2.0 * M_PI * float(idx) / CIRCLE_PTS;
            pts[2*idx] = cos( ang );
            pts[2*idx+1] = sin( ang );
        }
        
        glBufferData(GL_ARRAY_BUFFER, 2*CIRCLE_PTS*sizeof(float), pts, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
    }
    //GUI
    {
        glGenBuffers(1, &m_vbo_gui);
        glBindBuffer(GL_ARRAY_BUFFER,m_vbo_gui);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gui_vertex_buffer_data), gui_vertex_buffer_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
        
    }
    
    
    //lensflare
    {
        glGenBuffers(1, &m_vbo_flarePosition);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_flarePosition);
        glBufferData(GL_ARRAY_BUFFER, sizeof(flare_vertex_buffer_data), flare_vertex_buffer_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
    
    }
    
    
    //sun - similar to lens flare
    {
        glGenBuffers(1, &m_vbo_sunPosition);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_sunPosition);
        glBufferData(GL_ARRAY_BUFFER, sizeof(flare_vertex_buffer_data), flare_vertex_buffer_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
    }
   
    
    //skybox
    {
    
        glGenBuffers(1, &m_vbo_skyboxPosition);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_skyboxPosition);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CHECK_GL_ERRORS;
    
    }
    
    vec2 quadsuv[] = {
       vec2( 0.0f,1.0f),
       vec2( 1.0f,1.0f),
       vec2( 0.0f,0.0f),
       vec2(1.0f,0.0f)
    };
    
    //particle
    {
    
        glGenBuffers(3, m_vbo_particle);
        
        // The VBO containing the 4 vertices of the particles.
        // Thanks to instancing, they will be shared by all particles.
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particle_vertex_buffer_data), particle_vertex_buffer_data,
                     GL_STATIC_DRAW);
        
        // The VBO containing the positions and sizes of the particles
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[1]);
        glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL,
                     GL_STREAM_DRAW);
        
        
        // The VBO containing the colors of the particles
         glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[2]);
         glBufferData(GL_ARRAY_BUFFER, sizeof(quadsuv),quadsuv,
                     GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        CHECK_GL_ERRORS;
    
    
    
    
    }
    
    
    
}

//----------------------------------------------------------------------------------------
void A3::mapVboDataToVertexShaderInputLocations()
{
    {
    // Bind VAO in order to record the data mapping.
    glBindVertexArray(m_vao_meshData);
    
    // Tell GL how to map data from the vertex buffer "m_vbo_vertexPositions" into the
    // "position" vertex attribute location for any bound vertex shader program.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexPositions);
    glVertexAttribPointer(m_positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    
    
    GLuint m_shadow_position = m_shadow_shader.getAttribLocation("position");
    glVertexAttribPointer( m_shadow_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    // Tell GL how to map data from the vertex buffer "m_vbo_vertexNormals" into the
    // "normal" vertex attribute location for any bound vertex shader program.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexNormals);
    glVertexAttribPointer(m_normalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
   
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexTextCoords);
    glVertexAttribPointer(m_uvAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexTangents);
    glVertexAttribPointer(m_tangentAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexBitangents);
    glVertexAttribPointer(m_bitangentAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    
    //-- Unbind target, and restore default values:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    CHECK_GL_ERRORS;
    
    }
    
    
    
    
    
    {
    
    // Bind VAO in order to record the data mapping.
    glBindVertexArray(m_vao_arcCircle);
    
    // Tell GL how to map data from the vertex buffer "m_vbo_arcCircle" into the
    // "position" vertex attribute location for any bound vertex shader program.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_arcCircle);
    glVertexAttribPointer(m_arc_positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    //-- Unbind target, and restore default values:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    CHECK_GL_ERRORS;
    
    }
    
    
    {
    
    glBindVertexArray(m_vao_skybox);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_skyboxPosition);
    GLuint m_skybox_position = m_skybox_shader.getAttribLocation("position");
    glVertexAttribPointer(m_skybox_position, 3, GL_FLOAT, GL_FALSE, 0 , nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    CHECK_GL_ERRORS;
    
    }
    
    {
   
    glBindVertexArray(m_vao_gui);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_gui);
    GLuint m_gui_position = m_gui_shader.getAttribLocation("position");
    glVertexAttribPointer(m_gui_position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    CHECK_GL_ERRORS;
    }
    
    {
    
    
    glBindVertexArray(m_vao_flare);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_flarePosition);
    GLuint m_flare_position = m_flare_shader.getAttribLocation("in_position");
    glVertexAttribPointer(m_flare_position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    CHECK_GL_ERRORS;
    }
    
    
    {
    
    glBindVertexArray(m_vao_sun);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_sunPosition);
    GLuint m_sun_position = m_sun_shader.getAttribLocation("in_position");
    glVertexAttribPointer(m_sun_position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    CHECK_GL_ERRORS;
    }
    
    
    
}













//----------------------------------------------------------------------------------------
void A3::initPerspectiveMatrix()
{
    float aspect = ((float)m_windowWidth) / m_windowHeight;
    m_perpsective = glm::perspective(degreesToRadians(60.0f), aspect, 0.1f, 100.0f);
}


//----------------------------------------------------------------------------------------
void A3::initViewMatrix() {
    //SceneNode * player = getNode(m_rootNode, "player");
   // glm::vec3 m = player_pos;
    
   // m_view = glm::lookAt(camera_pos, player_pos,
    //                     vec3(0.0f, 1.0f, 0.0f));
    camera.updatePlayerPos(player_pos);
    camera.updatePlayerRolY(player_rolY);
    camera.move();
    m_view = camera.generateViewMatrix();
    
    
    
}

//----------------------------------------------------------------------------------------
void A3::initLightSources() {
    // World-space position
    m_light.position = vec3(0.0f, 30.0f, 25.0f);
    m_light.rgbIntensity = vec3(1.0f); // White light
    m_light.lightView = glm::lookAt(vec3(0.0f, 30.0f, 25.0f), vec3(0.0f, 0.0f, -6.0f), vec3(0.0f, 1.0f, 0.0f));
    GLfloat near_plane =-25.0f, far_plane = 50.5f;
    m_light.projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
  
}

//----------------------------------------------------------------------------------------
void A3::uploadCommonSceneUniforms() {
    m_shader.enable();
    {
        //-- Set Perpsective matrix uniform for the scene:
        GLint location = m_shader.getUniformLocation("Perspective");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_perpsective));
        CHECK_GL_ERRORS;
        
        location = m_shader.getUniformLocation("reflected");
        glUniform1i(location, reflection ? 1: 0);
        
        
        location = m_shader.getUniformLocation("umbra");
        glUniform1i(location,shadow_option);
        CHECK_GL_ERRORS;
        
        // may has a problem here
        location = m_shader.getUniformLocation("blended");
        glUniform1i(location, blended ? 1: 0);
        
        location = m_shader.getUniformLocation("normaled");
        glUniform1i(location, normaled ? 1 : 0);
        
        
       
       
        CHECK_GL_ERRORS;
        
        //-- Set LightSource uniform for the scene:
        {
          
                location = m_shader.getUniformLocation("light.position");
                glUniform3fv(location, 1, value_ptr(m_light.position));
                location = m_shader.getUniformLocation("light.rgbIntensity");
                glUniform3fv(location, 1, value_ptr(m_light.rgbIntensity));
                CHECK_GL_ERRORS;
           
        }
        
        //-- Set background light ambient intensity
        {
           
                location = m_shader.getUniformLocation("ambientIntensity");
                vec3 ambientIntensity(0.05f);
                glUniform3fv(location, 1, value_ptr(ambientIntensity));
                CHECK_GL_ERRORS;
            
        }
    }
    m_shader.disable();
    
   
    
   
}
//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void A3::appLogic()
{
    // Place per frame, application logic here ...
    
    uploadCommonSceneUniforms();
}






























//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void A3::guiLogic()
{
    if( !show_gui ) {
        return;
    }
    
    static bool firstRun(true);
    if (firstRun) {
        ImGui::SetNextWindowPos(ImVec2(50, 50));
        firstRun = false;
    }
    
    static bool showDebugWindow(true);
    ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize);
    float opacity(0.5f);
    windowFlags |= ImGuiWindowFlags_MenuBar;
    
    ImGui::Begin("Properties", &showDebugWindow, ImVec2(100,100), opacity,
                 windowFlags);
    
    
    
    
    
    // Add more gui elements here here ...
    /*
 if(ImGui::BeginMenuBar()){
       if(ImGui::BeginMenu("Application",true)){
         if (ImGui::MenuItem("Reset Position", "I", false, true)){
            resetPosition();
         }
         if (ImGui::MenuItem("Reset Orientation", "O", false, true)){
            resetOrientation();
         }
         if (ImGui::MenuItem("Reset Joints", "N", false, true)) {
            resetJoints();
         }
         if (ImGui::MenuItem("Reset All", "A", false, true)){
             resetPosition();
             resetOrientation();
             resetJoints();
             //reset();
             TRANSPOSITION = glm::mat4();
             ORIENTATION = glm::mat4();
             TMP = glm::mat4();
             last_one = -1;
             for(int i =0; i < selected.size();i++){
                 selected[i]= false;
             }
         }
         if( ImGui::MenuItem( "Quit App", "Q", false, true) ) {
            glfwSetWindowShouldClose(m_window, GL_TRUE);
         }
         ImGui::EndMenu();
       }
    
      if(ImGui::BeginMenu("Edit", true)){
          if (ImGui::Button("Undo [U]")){
              undo();
          }
          if (ImGui::Button("Redo [R]")){
              redo();
          }
        
          ImGui::EndMenu();
      }
    
        if(ImGui::BeginMenu("Options", true)){
            ImGui::Checkbox("Circle [C]", &option_circle );
            ImGui::Checkbox("Z-buffer [Z]", &option_zBuffer);
            ImGui::Checkbox("Backface Culling [B]", &option_backfaceCulling);
            ImGui::Checkbox("Frontface Culling [F]", &option_frontfaceCulling);
            ImGui::EndMenu();
        }
     
    
        ImGui::EndMenuBar();
    }*/
    
    ImGui::Checkbox("Blend map for plane", &blendMap_option);
    ImGui::Checkbox("Shadow", &shadow_option);
    
    //ImGui::RadioButton("Position/Orientation [P]", &current_mode, mode_position);
    // ImGui::RadioButton("Joints [J]", &current_mode, mode_joints);
    
    if (ImGui::Button("Quit Application")){
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }
    
    
    ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );
    
    ImGui::End();
}

//----------------------------------------------------------------------------------------
// Update mesh specific shader uniforms:
void updateShaderUniforms(
                          const ShaderProgram & shader,
                          const GeometryNode & node,
                          const glm::mat4 & viewMatrix
                          ) {
    
    shader.enable();
    {
        //-- Set ModelView matrix:
        GLint location = shader.getUniformLocation("ModelView");
        mat4 modelView = viewMatrix * node.trans;
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
        CHECK_GL_ERRORS;
        
        
        //-- Set NormMatrix:
        location = shader.getUniformLocation("NormalMatrix");
        mat3 normalMatrix = glm::transpose(glm::inverse(mat3(modelView)));
        glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(normalMatrix));
        CHECK_GL_ERRORS;
      
            
            //-- Set Material values:
            location = shader.getUniformLocation("material.kd");
            vec3 kd = node.material.kd;
            glUniform3fv(location, 1, value_ptr(kd));
            CHECK_GL_ERRORS;
            location = shader.getUniformLocation("material.ks");
            vec3 ks = node.material.ks;
            glUniform3fv(location, 1, value_ptr(ks));
            CHECK_GL_ERRORS;
            location = shader.getUniformLocation("material.shininess");
            glUniform1f(location, node.material.shininess);
            CHECK_GL_ERRORS;
        
        
    }
    shader.disable();
    
}

// Update mesh specific shader uniforms:
void A3::updateShaderUniforms( const glm::mat4& MV, unsigned int idx, const glm::vec3& col, GeometryNode * node )
{
    
    mat4 lightMatrix = m_light.projection * m_light.lightView;
    
    m_shader.enable();
    {
    
    //-- Set ModelView matrix:
    GLint location = m_shader.getUniformLocation("ModelView");
    mat4 modelView = MV * node->trans;
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
    CHECK_GL_ERRORS;
    
    location = m_shader.getUniformLocation("View");
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_view));
    
     CHECK_GL_ERRORS;
    
    
    GLint uniformLocation_diffuse = m_shader.getUniformLocation("samUV");
    glUniform1i(uniformLocation_diffuse, 0);
        CHECK_GL_ERRORS;
    
    location = m_shader.getUniformLocation("shadowMap");
    glUniform1i(location, 1);
    CHECK_GL_ERRORS;
        
    location = m_shader.getUniformLocation("envirMap");
    glUniform1i(location,2);
    CHECK_GL_ERRORS;
        
    //blending map
    location = m_shader.getUniformLocation("rTexture");
    glUniform1i(location,3);
    CHECK_GL_ERRORS;
        
    location = m_shader.getUniformLocation("gTexture");
    glUniform1i(location,4);
    CHECK_GL_ERRORS;
        
    location = m_shader.getUniformLocation("bTexture");
    glUniform1i(location,5);
    CHECK_GL_ERRORS;
    
    location = m_shader.getUniformLocation("blendMap");
    glUniform1i(location,6);
    CHECK_GL_ERRORS;
        
    location = m_shader.getUniformLocation("normalMap");
    glUniform1i(location,7);
    CHECK_GL_ERRORS;
        
    
    //mat4 lightMatrix = m_light.projection * m_light.lightView;
    location = m_shader.getUniformLocation("lightSpace");
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(lightMatrix));
    CHECK_GL_ERRORS;
      
        
    location = m_shader.getUniformLocation("cameraPosition");
    glUniform3fv(location, 1, value_ptr(camera.getPosition()));
    CHECK_GL_ERRORS;
        
    
    
    
    
  
        //-- Set NormMatrix:
        location = m_shader.getUniformLocation("NormalMatrix");
        mat3 normalMatrix = glm::transpose(glm::inverse(mat3(modelView)));
        glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(normalMatrix));
        CHECK_GL_ERRORS;
        
        //-- Set Material values:
        location = m_shader.getUniformLocation("material.kd");
        glUniform3fv(location, 1, value_ptr(col));
        CHECK_GL_ERRORS;
        
        location = m_shader.getUniformLocation("material.ks");
        vec3 ks = node->material.ks;
        glUniform3fv(location, 1, value_ptr(ks));
        CHECK_GL_ERRORS;
        location = m_shader.getUniformLocation("material.shininess");
        glUniform1f(location, node->material.shininess);
        CHECK_GL_ERRORS;
        
     
      
    }

    m_shader.disable();
    
    CHECK_GL_ERRORS;
    
   /*
    m_shadow_shader.enable();
    {
        GLint location = m_shadow_shader.getUniformLocation("model");
        mat4 modelView = MV * node->trans;
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
       
        
        location = m_shadow_shader.getUniformLocation("lightSpaceMatrix");
         glUniformMatrix4fv(location,1,GL_FALSE,value_ptr(lightMatrix));
        
    }
    m_shadow_shader.disable();
    */
    
    
    
    m_flare_shader.enable();
    {
        GLint uniformLocation_diffuse = m_flare_shader.getUniformLocation("flareTexture");
        glUniform1i(uniformLocation_diffuse, 0);
        
    }
    m_flare_shader.disable();
    
    
    
    m_sun_shader.enable();
    {
        GLint uniformLocation_diffuse = m_sun_shader.getUniformLocation("sunTexture");
        glUniform1i(uniformLocation_diffuse, 0);
        
    }
    m_sun_shader.disable();
    
    
    
    
    m_skybox_shader.enable();
    {
        mat4 MVP = m_perpsective * m_view;
        GLint location = m_skybox_shader.getUniformLocation("MVP");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(MVP));
        
        GLint cube = m_skybox_shader.getUniformLocation("cubeMap");
        glUniform1i(cube,1);
        CHECK_GL_ERRORS;
        
    }
    m_skybox_shader.disable();
    
}




























//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void A3::draw() {
    glViewport(0,0,m_windowWidth*2,m_windowHeight*2);
   
    
   
    
    
    /*
     if(option_zBuffer){
     glEnable( GL_DEPTH_TEST );
     } else {
     glDisable(GL_DEPTH_TEST);
     }
     
     if (option_backfaceCulling || option_frontfaceCulling) {
     glEnable(GL_CULL_FACE);
     if(option_frontfaceCulling && option_backfaceCulling) {
     glCullFace(GL_FRONT_AND_BACK);
     } else if (option_frontfaceCulling) {
     glCullFace(GL_FRONT);
     } else if  (option_backfaceCulling){
     glCullFace(GL_BACK);
     }
     } else {
     glDisable(GL_CULL_FACE);
     }
     */
   //================================== Player movement and Camera Movement ========================
    
    if(A_button_pressed){
        
        player.updateCurrentTurnSpeed(1.6);
      
    }
    else if(D_button_pressed){
    
        player.updateCurrentTurnSpeed(-1.6);
     
    } else {
        player.updateCurrentTurnSpeed(0.0);
    }
    
    
    
    if (W_button_pressed){
       
        player.updateCurrentSpeed(0.2);
       
    } else if (S_button_pressed){
   
         player.updateCurrentSpeed(-0.2);
        
    } else {
         
         player.updateCurrentSpeed(0.0);
    }
    
    player.move(); // updating the player position
    glm::vec3 pos = player.getObjectPosition();
    
    //glm::vec3 dPos = player.getObjectDPosition();
    //movePlayer(dPos);
   
    
    camera.updatePlayerPos(pos);
    camera.updatePlayerRolY(player.getObjectRolY()); // updating the camera angle and camera position
    camera.move();
    
    
    m_view = camera.generateViewMatrix();
    //m_light.lightView *= glm::translate(mat4(), player.getObjectDPosition());
    
    //================================== End of Camera and Player Movement ============================
    
    //Collision detection
    
    for (int i = 0; i < eggBasket.size(); i++){
        bool touched = collision(player, eggBasket[i]);
        if (touched){
           
            eggBasket[i].updateVisibility(false);
            
            bgm->play2D("Assets/sound/egg.mp3");
            life++;
            //cout<< "touched" <<endl;
            if(life == 10){
                end_game_option = true;
                turtle_init_speed = 0.0f;
                callEnding (end_game_option);
                guiBucket[3].setVisible(false);//<--- may not useful
                guiBucket[4].setVisible(true);
            }
            
        } else {
          
        }
     
    }
    
    
    
    for(int i = 0; i < eggBasket.size(); i++){
        if(!eggBasket[i].isVisible()){
            vec3 oldPosition = eggBasket[i].getObjectPosition();
            float x = rand()%15 -7.5;
            float y = 0.0;
            float z = rand()%15 -7.5;
            eggBasket[i].updatePosition(glm::vec3(x, y, z));
            eggBasket[i].transNode(vec3(x,y,z));
            eggBasket[i].updateVisibility(true);
        }
    }
    
    
    for(int i = 0; i < turtleBucket.size(); i++){
        bool touched = collision(player, turtleBucket[i]);
        if (touched){
            turtleBucket[i].updateVisibility(false);
            bgm->play2D("Assets/sound/baby.mp3");
            life--;
            if(life == 0){
                end_game_option = true;
                turtle_init_speed = 0.0f;
                callEnding (end_game_option);
                guiBucket[3].setVisible(true);
                guiBucket[4].setVisible(false);
            }
           
        } else {
          
        }
        vec3 disPos = player.getObjectPosition() - turtleBucket[i].getObjectPosition();
        turtleBucket[i].updatePosition(vec3(disPos.x * turtle_init_speed, 0, disPos.z * turtle_init_speed));
        float degree = atan(disPos.z/ disPos.x);
        turtleBucket[i].updateCurrentTurnSpeed(degree);
        turtleBucket[i].transNode(vec3(disPos.x * turtle_init_speed, 0, disPos.z * turtle_init_speed));
        
        //turtleBucket[i].updateCurrentSpeed(-0.01);
       // turtleBucket[i].updateCurrentTurnSpeed(1.6);
        turtleBucket[i].move();
    }
    
    for(int i = 0; i < turtleBucket.size(); i++){
        if(!turtleBucket[i].isVisible()){
            vec3 oldPosition = turtleBucket[i].getObjectPosition();
            float x = rand()%15 -7.5;
            float y = 0.0;
            float z = rand()%15 -7.5;
            turtleBucket[i].updatePosition(glm::vec3(x, y, z));
            turtleBucket[i].transNode(vec3(x,y,z));
            turtleBucket[i].updateVisibility(true);
        }
    }
    
    
    
    
   
    
    
    
    
    
    
    //==========================   Draw Objects =================================
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_DEPTH_TEST );
    //glViewport(0,0,m_windowWidth,m_windowHeight);
    
    
    
    //glViewport(0,0,m_windowWidth,m_windowHeight);
    glViewport(0,0,SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER,FramebufferName);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    int flag = 0;//render with shadow shadr
    
    renderSceneGraph(m_rootNode, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
   glClear(GL_STENCIL_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
   
    //render normally
     glViewport(0,0,m_windowWidth*2,m_windowHeight*2);
    renderSceneGraph(m_rootNode, 1);
    
    
    //cout <<"m_windowWidth:" << m_windowWidth * 2 << endl;
    //cout << "m_windowHeight:" << m_windowHeight * 2 << endl;
    
    //=============================== End of Draw Objects ========================================
    
    
    
    //==================================  Draw Sky Box =======================================
    
    //skybox
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    
    glBindVertexArray(m_vao_skybox);
    m_skybox_shader.enable();
    
    mat4 view = m_view;
    view = glm::mat4(glm::mat3(m_view));
    mat4 MVP = m_perpsective * view;
    GLint location = m_skybox_shader.getUniformLocation("MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(MVP));
    
    GLint cube = m_skybox_shader.getUniformLocation("cubeMap");
    glUniform1i(cube,0);
    CHECK_GL_ERRORS;
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTexture());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    
    glBindVertexArray(0);
    
    
    m_skybox_shader.disable();
    
    glDepthMask(GL_TRUE);
    
    glDepthFunc(GL_LESS);
    
    //======================================= Draw Sky box ======================================
    
    
    
    
    
    
    
    //==============================  Particles - transparency ==========================
    glDisable(GL_CULL_FACE);
  
    
    if ( W_button_pressed || S_button_pressed ){
        bubble_tex.Bind(0);
        SceneNode* play = getNode(m_rootNode, player.getObjectName());
        glm::mat4 m = play->get_transform();
        m*= glm::rotate(mat4(), (float)glm::radians(-player.getObjectRolY()), glm::vec3(0.0, 1.0, 0.0));
        drawParticles(m);  //<< ---- can be called by difference of model matrix m
    
    }
    
    
    
    
    
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
  
 
    
    
    //============================ sun ================================================
    sunRender();
    
    
    
    //============================ Lens Flare ==========================================
   // calcFlarePositions(vec2(1, 0), vec2(0, 1));
   // renderFlare(List_of_flares, 0.5f);
    
    // Sun posiiton is imperfect here:
    
    vec3 sunpos = sun.getPosition() * vec3(1.0, 0.5, -1.0);
    /*
    //vec3 sunpos = vec3(0.8, 10.8 , 90.0);
    cout << "what I get on sunpos : x" << sun.getPosition().x<<endl;
    cout << "what I get on sunpos : y" << sun.getPosition().y<<endl;
    cout << "what I get on sunpos : z" << sun.getPosition().z<<endl;
    */
    
    renderSun(sunpos);
    
    
    
    
    
    //======================================================================================
    
    glDisable( GL_DEPTH_TEST );
    
    
    renderGui();
    
    
    
    
    
    
    
    
    if (option_circle) {
        renderArcCircle();
    }
    
    
    
    
   
    
}

//----------------------------------------------------------------------------------------
void A3::renderSceneGraphHelper(SceneNode *node, glm::mat4 M, int flag){
    if(node == NULL){
        return;
    }
    glm::mat4 E = node->get_transform();
    node->set_transform(M * E);
    if (node->children.size() > 0){
        for(SceneNode * child : node->children){
            renderSceneGraphHelper(child, node->get_transform(), flag);
        }
    }
    if (node->m_nodeType == NodeType::GeometryNode){
        unsigned int nodeid = node->m_nodeId;
        int idx = nodeId_to_id[nodeid];
        //const glm::mat4& T = xforms[idx];
        glm::vec3 col = cols[idx];
        if( selected[idx] ) {
            col = glm::vec3( 1.0, 1.0, 0.0 );
        }
        GeometryNode* gnode = static_cast<GeometryNode *>(node);
        
        
        reflection = false; //<-- only true on water
        blended = false; //<== this is only used for map
        normaled = false; //<=== this is only used for player normal mapping
        
        
        
        if (flag == 1){
            
            
        
        if (gnode->m_name == "lake"){
            reflection = true;
            uploadCommonSceneUniforms(); // used to update the reflected
            
            
            water_tex.Bind(0);
            
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthTexture);
            
            
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTexture());
            
            
            
            
            updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
            
          
            
            BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
            
            
            
            m_shader.enable();
            glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
            m_shader.disable();
            
            
        } else if (gnode->m_name == "plane"){
            if(blendMap_option){
            
                blended = true;
                path_tex.Bind(5);
                mud_tex.Bind(3);
                grassFlower_tex.Bind(4);
                blendMap_tex.Bind(6);
            }
            uploadCommonSceneUniforms();
           
            plane_tex.Bind(0); //< change to mud
            
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthTexture);
            
            
          //  glActiveTexture(GL_TEXTURE2);
           // glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTexture());
           
            //path_tex.Bind(5);
            //mud_tex.Bind(3);
            //grassFlower_tex.Bind(4);
            //blendMap_tex.Bind(6);
            
            
            updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
            BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
            
           
            
            m_shader.enable();
            glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
            m_shader.disable();
          
        
        }
        else if (gnode->m_name.find( "turtle") != std::string::npos){
            uploadCommonSceneUniforms();
            
            Object tempTurtle;
            for (int i = 0; i < turtleBucket.size(); i++){
                if (gnode->m_name == turtleBucket[i].getObjectName()){
                    tempTurtle = turtleBucket[i];
                    break;
                }
            }
            if (tempTurtle.isVisible()){
                turtle_tex.Bind(0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, depthTexture);
                
                // glActiveTexture(GL_TEXTURE2);
                // glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTexture());
                
                
                
                updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
                BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
                
                m_shader.enable();
                glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
                m_shader.disable();
                
            }
            
          
            
        } else if (gnode->m_name.find("tree") != std::string::npos){
            uploadCommonSceneUniforms();
            tree_tex.Bind(0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthTexture);
            updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
            BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
            
            m_shader.enable();
            glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
            m_shader.disable();
            
            
        }
        
        
        else if (gnode->m_name == "player"){
            normaled = true;
            
            uploadCommonSceneUniforms();
            
            earth_tex.Bind(0);
            
            
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthTexture);
            
            earth_normal_tex.Bind(7);
            
           // glActiveTexture(GL_TEXTURE2);
           // glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTexture());
            
            
            
            updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
            BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
            
            m_shader.enable();
            glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
            m_shader.disable();
            
        } else if (gnode->m_name == "house1"){
            
            uploadCommonSceneUniforms();
            
            house_tex.Bind(0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthTexture);
            
            
            updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
            BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
            
            m_shader.enable();
            glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
            m_shader.disable();
            
            
        } else if (gnode->m_name.find( "egg") != std::string::npos){
             
            uploadCommonSceneUniforms();
            Object tempEgg;
            for (int i = 0; i < eggBasket.size(); i++){
                if (gnode->m_name == eggBasket[i].getObjectName()){
                    tempEgg = eggBasket[i];
                    break;
                }
            }
                if(tempEgg.isVisible()){
            
            
                    egg_tex.Bind(0);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, depthTexture);
                    
                  //  glActiveTexture(GL_TEXTURE2);
                  //  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTexture());
            
                    updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
                    BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
            
                    m_shader.enable();
                    glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
                  m_shader.disable();
                }
            
        }
        
        
        else {
            
            
               uploadCommonSceneUniforms();
           
            
                glBindTexture(GL_TEXTURE_2D, 0);
            
            
                updateShaderUniforms( mat4() , (unsigned int)idx, col,  gnode );
                BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
        
                m_shader.enable();
            
                glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
               m_shader.disable();
          
            
            
           
            
            }
            
            
            
            
            
        } else  {
           //  glBindTexture(GL_TEXTURE_2D, 0);
           // cout <<"start printing the name" <<endl;
           // cout << node->m_name <<endl;
            
            m_shadow_shader.enable();
            
            {
                mat4 lightMatrix = m_light.projection * m_light.lightView;
                mat4 modelView = node->get_transform();
                
                GLint location = m_shadow_shader.getUniformLocation("model");
                // modelView = mat4();
                glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
                
                
                location = m_shadow_shader.getUniformLocation("lightSpaceMatrix");
                glUniformMatrix4fv(location,1,GL_FALSE,value_ptr(lightMatrix));
                
               // cout << "right here"<<endl;
                
            }
            m_shadow_shader.disable();
            
            
            //updateShaderUniforms( m_view , (unsigned int)idx, col,  gnode );
            BatchInfo batchInfo = m_batchInfoMap[ shapes[idx]];
            
            //m_shader.enable();
            m_shadow_shader.enable();
            glDrawArrays( GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices );
            //  m_shader.disable();
            m_shadow_shader.enable();
        
        }

        
    }
    node->set_transform(E);
    
}
void A3::renderSceneGraph( SceneNode * root, int flag) {
  
    glBindVertexArray( m_vao_meshData );
    
    
    renderSceneGraphHelper(m_rootNode, glm::mat4(), flag);
                           
    glBindVertexArray( 0 );
  
    CHECK_GL_ERRORS;
    
    
}

//----------------------------------------------------------------------------------------
// Draw the trackball circle.
void A3::renderArcCircle() {
    glBindVertexArray(m_vao_arcCircle);
    
    m_shader_arcCircle.enable();
    GLint m_location = m_shader_arcCircle.getUniformLocation( "M" );
    float aspect = float(m_framebufferWidth)/float(m_framebufferHeight);
    glm::mat4 M;
    if( aspect > 1.0 ) {
        M = glm::scale( glm::mat4(), glm::vec3( 0.5/aspect, 0.5, 1.0 ) );
    } else {
        M = glm::scale( glm::mat4(), glm::vec3( 0.5, 0.5*aspect, 1.0 ) );
    }
    glUniformMatrix4fv( m_location, 1, GL_FALSE, value_ptr( M ) );
    glDrawArrays( GL_LINE_LOOP, 0, CIRCLE_PTS );
    m_shader_arcCircle.disable();
    
    glBindVertexArray(0);
    CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void A3::cleanup()
{
    glDeleteBuffers(3, m_vbo_particle);
    glDeleteVertexArrays(1, &m_vao_particle);
    
    delete[] particle_position_size;
    bgm->drop();
}






























//    Human Operation Controls






//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles cursor entering the window area events.
 */
bool A3::cursorEnterWindowEvent (
                                 int entered
                                 ) {
    bool eventHandled(false);
    
    // Fill in with event handling code...
    
    return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse cursor movement events.
 */
bool A3::mouseMoveEvent (
                         double xPos,
                         double yPos
                         ) {
    bool eventHandled(true);
    vec2 m_mouse_GL_coordinate = vec2 (
                                       (2.0f * xPos) / m_windowWidth - 1.0f,
                                       1.0f - ( (2.0f * yPos) / m_windowHeight)
                                       );
    currentxpos = m_mouse_GL_coordinate.x;
    currentypos = m_mouse_GL_coordinate.y;
    
    if (!ImGui::IsMouseHoveringAnyWindow()){
        if(leftKey || middleKey || rightKey){
            cur_mx = xPos;
            cur_my = yPos;
            //Do some calculations with cur and last
            glm::mat4 T;
            glm::vec3 axis;
            int width, height;
            
            glfwGetWindowSize(m_window, &width, &height);
            float diameter = m_framebufferWidth/2 < m_framebufferHeight/2 ? m_framebufferWidth / 2 : m_framebufferHeight /2;
            
            float distance_x = (cur_mx - last_mx )/100;
            float distance_y = (cur_my - last_my )/1000;
            if (current_mode == mode_position){
               
                
                if (leftKey){
                    
                   
                    camera.calculateAngleAroundPlayer(distance_x * 20);
                    
                }
                
                if (middleKey){
                    
                    
                }
                
                if (rightKey){
                   
                    
                    camera.calculatePitch(distance_y * 20.0f);
                    
                }
            
            }
            
            //developer mode
            
            if (current_mode == mode_joints){
                double theta = -(cur_my-last_my) * PI / 180;
                double dx = (cur_mx-last_mx) * PI / 180;
                if (leftKey){
                    
                }
                if (middleKey){
                   
                }
                if (rightKey){
                    
                }
            
            }
            
            last_mx = xPos;
            last_my = yPos;
            eventHandled = true;
        } else {
            last_mx = xPos;
            last_my = yPos;
            eventHandled = true;
        }
    }
    
    // Fill in with event handling code...
    
    return eventHandled;
}


//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse button events.
 */
bool A3::mouseButtonInputEvent (
                                int button,
                                int actions,
                                int mods
                                ) {
    bool eventHandled(false);
    
    
    if (!ImGui::IsMouseHoveringAnyWindow()) {
        if (actions == GLFW_PRESS) {
            if (button == GLFW_MOUSE_BUTTON_RIGHT){
                rightKey = true;
            }
            if (button == GLFW_MOUSE_BUTTON_MIDDLE){
                middleKey = true;
            }
            
            
            
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                leftKey = true;
                
            }
        }
        
        if (actions == GLFW_RELEASE){
            vector<unsigned int> node_ids;
            if (button == GLFW_MOUSE_BUTTON_RIGHT){
                rightKey = false;
                
                
            }
            if (button == GLFW_MOUSE_BUTTON_MIDDLE){
                middleKey = false;
                
                
            }
            if (button == GLFW_MOUSE_BUTTON_LEFT){
                leftKey = false;
            }
        }
        
        
        
    }
    
    eventHandled = true;
    return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse scroll wheel events.
 */
bool A3::mouseScrollEvent (
                           double xOffSet,
                           double yOffSet
                           ) {
    bool eventHandled(true);
 
    
    camera.calculateZoom(yOffSet);
    // m_view = camera.generateViewMatrix();
    
    return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles window resize events.
 */
bool A3::windowResizeEvent (
                            int width,
                            int height
                            ) {
    bool eventHandled(true);
    m_windowWidth = width;
    m_windowHeight = height;
    //cout << m_windowWidth << endl;
    //cout << m_windowHeight << endl;
    initPerspectiveMatrix();
    return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles key input events.
 */
bool A3::keyInputEvent (
                        int key,
                        int action,
                        int mods
                        ) {
    bool eventHandled(true);
  
    
    if( action == GLFW_PRESS ) {
        if( key == GLFW_KEY_M ) {
            show_gui = !show_gui;
            eventHandled = true;
        }
      
       
        if (key == GLFW_KEY_A)
        {
      
            A_button_pressed = true;
            
        }
        if (key == GLFW_KEY_D){
            D_button_pressed = true;
            
        }
        if (key == GLFW_KEY_W){
            W_button_pressed = true;
        }
        if (key == GLFW_KEY_S){
            S_button_pressed = true ;
        }
        
        if (key == GLFW_KEY_SPACE){
       
            player.jump();
            bgm->play2D("Assets/sound/jump.mp3");
        }
        
        if (key == GLFW_KEY_Q){
            glfwSetWindowShouldClose(m_window, GL_TRUE);
        }
        if(key == GLFW_KEY_ENTER){
            turtle_init_speed = 0.01f;
            bgm->drop();
            bgm = irrklang::createIrrKlangDevice();
            bgm->play2D("Assets/sound/playing.mp3", true);
            guiBucket[2].setVisible(false);
            guiBucket[3].setVisible(false);
            guiBucket[4].setVisible(false);
            life = 3;
            for(int i = 0; i < eggBasket.size(); i++){
                eggBasket[i].updateVisibility(true);
            }
            for(int i = 0; i < turtleBucket.size(); i++){
                turtleBucket[i].updateVisibility(true);
            }
        }
       
       
        
    } else if (action == GLFW_RELEASE){
       
        
        if(key == GLFW_KEY_A){
            A_button_pressed = false;
            distance_left_x = 0.0f;
        }
        if(key == GLFW_KEY_D){
            D_button_pressed = false;
            distance_right_x = 0.0f;
        }
        if (key == GLFW_KEY_W){
            W_button_pressed = false;
            distance_forward_z = 0.0f;
        }
        if (key == GLFW_KEY_S){
            S_button_pressed = false ;
            distance_backward_z = 0.0f;
        }
        
        
       
    }
    
    return eventHandled;
}



















//============== Lens Flare ======================
//reference: https://www.youtube.com/watch?v=OiMRdkhvwqg&index=57&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP
//
//
//
//
//
//============== Lens Flare =======================

glm::vec2 A3::convertToScreenSpace(glm::vec3 worldPos, glm::mat4 viewMatrix, glm::mat4 perspectiveMatrix){
    glm::vec4 coords = glm::vec4(worldPos.x, worldPos.y, worldPos.z, 1.0f);
    coords = viewMatrix * coords;
    coords = perspectiveMatrix * coords;
   // cout << "coords .x" << coords.x <<endl;
    //cout << "coords .y" << coords.y <<endl;
    //cout << "coords .z" << coords.z <<endl;
   // cout << "coords .w" << coords.w <<endl;
    if (coords.w <= 0){
        return vec2(-999.0f);
    }
    float x = (coords.x / coords.w + 1.0f) / 2.0f;
    float y = 1.0f - ((coords.y / coords.w + 1.0f) / 2.0f);
    return glm::vec2(x,y);
}
void A3::calcFlarePositions(glm::vec2 sunToCenter, glm::vec2 sunCoords){
    for (int i = 0; i < List_of_flares.size(); i++){
        glm::vec2 direction = glm::vec2(sunToCenter);
        float spacing = 0.4f;
        direction = direction * ((i) * spacing);
        glm::vec2 flarePos = sunCoords + direction;
      //  cout << "flare pos x" << flarePos.x <<endl;
       //  cout << "flare pos y" << flarePos.y <<endl;
        List_of_flares[i].setScreenPos(flarePos);
        //List_of_flares[i].setScreenPos(vec2(0.5f, 0.5f));
    }
}

void A3::renderSun(glm::vec3 sunPos){
    vec2 sunCoords = convertToScreenSpace(sunPos, m_view, m_perpsective);
   
    if(sunCoords == vec2(-999.0f)){
         //cout << "I'm stoping" <<endl;
        return;
    }
    vec2 CENTER_SCREEN = vec2(0.5f,0.5f);
    vec2 sunToCenter = CENTER_SCREEN - sunCoords;
    float brightness = 1 - (glm::length(sunToCenter)/ 0.5f );
   // cout << "brightness : " << brightness <<endl;
    if (brightness > 0){
        calcFlarePositions(sunToCenter, sunCoords);
        renderFlare(List_of_flares, brightness);
    }

}


void A3::renderFlare(std::vector<FlareTexture>flares, float brightness){
    
    glDisable( GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    m_flare_shader.enable();
    {
        glBindVertexArray(m_vao_flare);
        
        GLint location = m_flare_shader.getUniformLocation("brightness");
        glUniform1f(location, brightness);
        
        for (int i = 0; i < flares.size(); i++){
            Texture tmpFlare = flares[i].getTexture();
            tmpFlare.Bind(0);
            float xScale = flares[i].getScale();
            float yScale = xScale * (m_windowWidth / m_windowHeight);
            glm::vec2 centerPos = flares[i].getScreenPos();
            
            glm::vec4 answer = glm::vec4(centerPos.x,centerPos.y , xScale , yScale);
            
            location = m_flare_shader.getUniformLocation("transform");
            glUniform4fv(location,1, value_ptr(answer));
            
            glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
        }
    
    
    }
    m_flare_shader.disable();
    
    //Ending
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
}



//================== sun ===============================
//
//
//
//
//
//
//=================== sun ===============================

void A3::sunRender(){
    glDisable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    
    m_sun_shader.enable();
    {
        glBindVertexArray(m_vao_sun);
        sun.getTexture().Bind(0);
       
        glm::mat4 modelMatrix = glm::mat4();
        glm::vec3 sunPos = sun.getWorldPosition(camera.getPosition()) + glm::vec3(0.0, 35.0, -30.0);
        
        //sunPos = vec3(0.0, 0.0, -16.0);
       // sunPos = vec3(8.0, 3.0, -5.0);
       // cout << "sun pos x" << sunPos.x <<endl;
       // cout << "sun pos y" << sunPos.y <<endl;
       // cout << "sun pos z" << sunPos.z <<endl;
        //============= extra ================
        sun.setPosition(sunPos);
        //============== extra ===============
        
        modelMatrix *= glm::translate(mat4(), sunPos);
        glm::mat4 modelViewMat = applyViewMartrix(modelMatrix, m_view);
        glm::vec3 sunScale = glm::vec3(sun.getScale(),sun.getScale(),sun.getScale());
        modelViewMat *= glm::scale (mat4(), sunScale);
        
        //mat4 mvpMat = m_perpsective * modelViewMat;
        mat4 mvpMat = m_perpsective * m_view * modelViewMat;
        
        GLint location = m_sun_shader.getUniformLocation("mvpMatrix");
        
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(mvpMat));
        glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
    
    }
    m_sun_shader.disable();
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glDisable(GL_BLEND);
    
    
}
glm::mat4 A3::applyViewMartrix(glm::mat4 modelMatrix, glm::mat4 viewMatrix){
    modelMatrix[0][0] = viewMatrix[0][0];
    modelMatrix[0][1] = viewMatrix[1][0];
    modelMatrix[0][2] = viewMatrix[2][0];
    modelMatrix[1][0] = viewMatrix[0][1];
    modelMatrix[1][1] = viewMatrix[1][1];
    modelMatrix[1][2] = viewMatrix[2][1];
    modelMatrix[2][0] = viewMatrix[0][2];
    modelMatrix[2][1] = viewMatrix[1][2];
    modelMatrix[2][2] = viewMatrix[2][2];
    return viewMatrix * modelMatrix ;
}

















// ============= Particles ==========
//
//
//
//
//
//
// ============== Particle=============

void A3::makeParticles(int num){
    //Genew particle
    float spread = 5.0f;
    for (int i=0;i< num;i++) {
        int index = FindUnusedParticle();
        
        
        if (index != -1) {
            pContainer[index].life = 0.5f;
            pContainer[index].size = (rand() % 10 + 1)/ 20.5f;
            //starting location
            pContainer[index].pos = vec3(0.0 , 0.0, -1.0);
            
            vec3 dir = vec3(0.0f,0.0f,5.0f);
            
            // randir from -1 to 1
            glm::vec3 spread_dir = glm::vec3(
                                             (rand()%200 - 100.0f)/100.0f,
                                             (rand()%200 - 100.0f)/100.0f,
                                             (rand()%200 - 100.0f)/100.0f
                                             );
            
            pContainer[index].speed = dir + spread_dir*spread;
        }//index2
    }//for loop
}

int A3::FindUnusedParticle(){
    for(int i=LastUsedParticle; i<MaxParticles; i++){
        if (pContainer[i].life <= 0.0f){
            LastUsedParticle = i;
            return i;
        }
    }
    
    for(int i=0; i<LastUsedParticle; i++){
        if (pContainer[i].life <= 0.0f){
            LastUsedParticle = i;
            return i;
        }
    }
    LastUsedParticle = 0;
    return 0; // All particles are taken, override the first one
}

int A3::countAliveParticles(){
    // Simulate all particles
    int ParticlesCount = 0;
    
    for(int i=0; i<MaxParticles; i++){
        float delta = 0.005f;
        Particle& p = pContainer[i]; // shortcut
        
        if(p.life > 0.0f){
            
            // Decrease life
            p.life -= delta;
            if (p.life > 0.0f){
                
                // Simulate simple physics : gravity only, no collisions
                p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
                p.pos += p.speed * (float)delta;
                
                //p.cameradistance = glm::length( p.pos - CameraPosition );
                
                //ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;
                
                // Fill the GPU buffer
                
                particle_position_size[4*ParticlesCount+0] = p.pos.x;
                particle_position_size[4*ParticlesCount+1] = p.pos.y;
                particle_position_size[4*ParticlesCount+2] = p.pos.z;
                
                particle_position_size[4*ParticlesCount+3] = p.size;
                
                //  g_particule_color_data[4*ParticlesCount+0] = p.r;
                //  g_particule_color_data[4*ParticlesCount+1] = p.g;
                //  g_particule_color_data[4*ParticlesCount+2] = p.b;
                // g_particule_color_data[4*ParticlesCount+3] = p.a;
                
            }else{
                // Particles that just died will be put at the end of the buffer in SortParticles();
                //  p.cameradistance = -1.0f;
                p.pos = vec3(-999.0f,-999.0f,-999.0f);
            }
            
            ParticlesCount++;
            
        }
    }
    return ParticlesCount;
}

void A3::drawParticles(glm::mat4 model){
    makeParticles(1);
    
    int particlesCount = countAliveParticles();
    
    // glBindVertexArray(m_vao_particle);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[1]);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat),NULL, GL_STREAM_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * 4 * sizeof(GLfloat), particle_position_size);
    
    
    
    
    m_particle_shader.enable();
    {
        
        glBindVertexArray(m_vao_particle);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[0]);
        GLuint positionAttribLocation = m_particle_shader.getAttribLocation( "vert" );
        glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        
        // 2nd attribute buffer : positions of particles' centers
        // size : x + y + z + size => 4
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[1]);
        GLuint transformLocation = m_particle_shader.getAttribLocation( "position" );
        glVertexAttribPointer(transformLocation,4, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[2]);
        glVertexAttribPointer(particleUVLocation,2, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        
        // glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[2]);
        // GLuint colorLocation = m_shader.getAttribLocation( "color" );
        // glVertexAttribPointer(colorLocation,4, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        
        glVertexAttribDivisor(positionAttribLocation, 0);
        glVertexAttribDivisor(transformLocation, 1);
        CHECK_GL_ERRORS;
        
        
        // glVertexAttribDivisor(colorLocation, 1);
        
        GLint uniformLocation_diffuse = m_particle_shader.getUniformLocation("diffuse");
        glUniform1i(uniformLocation_diffuse, 0);
        CHECK_GL_ERRORS;
        
        //up load the P and V
        //glm::mat4 view = glm::lookAt(vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = m_view;
        //view *= glm::translate(mat4(),glm::vec3(0.0, -1.0 , 2.5));
        GLint location = m_particle_shader.getUniformLocation("view");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(view));
        CHECK_GL_ERRORS;
        
        location = m_particle_shader.getUniformLocation("perspective");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_perpsective));
        CHECK_GL_ERRORS;
        
        
        //SceneNode* play = getNode(m_rootNode, "egg");
        //glm::mat4 m = play->get_transform();
        location = m_particle_shader.getUniformLocation("model");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(model));
        CHECK_GL_ERRORS;
        
        
        
        
        
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesCount);
        
        
        
        
        //-- Unbind target, and restore default values:
        //   glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    m_particle_shader.disable();
    
    
    CHECK_GL_ERRORS;
}




















//============== gui =====================================
//
//
//
//
//
//============== gui =====================================
void A3::renderGui(){
    m_gui_shader.enable();
    {
        glBindVertexArray(m_vao_gui);
        
        
        
        mat4 mvpMat = mat4();
        
  
        
        float lifebar_width = 0.4;
        float lifebar_height = 0.05;
        float lifeW = ((float)life/10) * lifebar_width;
        float move = -lifebar_width + lifeW;
        
        
        // life bar
        mvpMat *= glm::translate(mat4(), vec3(move, -0.8, 0.0));
        mvpMat *=  glm::scale(mat4(), vec3( lifeW, lifebar_height, 0.0));
        
       GLint location = m_gui_shader.getUniformLocation("transformationMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(mvpMat));
        
        location = m_gui_shader.getUniformLocation("life");
        glUniform1i(location, 1);
        
        location = m_gui_shader.getUniformLocation("lifeValue");
        glUniform1f(location, life/10.0);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
        
        
        
        
        
        
        
        
        // Then gui units
        location = m_gui_shader.getUniformLocation("life");
        glUniform1i(location, 0);
        for (int i = 0; i < guiBucket.size(); i++){
            if(guiBucket[i].getVisibility()){
            Texture t = guiBucket[i].getTexture();
            t.Bind(0);
            
            mat4 mvpMat = mat4();
            mvpMat *= glm::translate(mat4(), vec3(guiBucket[i].getPosition(), 0.0));
            mvpMat *=  glm::scale(mat4(), vec3(guiBucket[i].getScale(), 0.0));
            
             location = m_gui_shader.getUniformLocation("transformationMatrix");
            
            glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(mvpMat));
            glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
            }
            
        }
        glBindTexture(GL_TEXTURE_2D, 0);
       
        
        glBindVertexArray(0);
        
        
    }
    m_gui_shader.disable();
}






































void A3::drawParticles(ParticleContainer pc, glm::mat4 model){
    pc.makeParticles(10);
    
    int particlesCount = pc.countAliveParticles(particle_position_size);
    
    // glBindVertexArray(m_vao_particle);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[1]);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat),NULL, GL_STREAM_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * 4 * sizeof(GLfloat), particle_position_size);
    
    
    
    
    m_particle_shader.enable();
    {
        
        glBindVertexArray(m_vao_particle);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[0]);
        GLuint positionAttribLocation = m_particle_shader.getAttribLocation( "vert" );
        glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        
        // 2nd attribute buffer : positions of particles' centers
        // size : x + y + z + size => 4
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[1]);
        GLuint transformLocation = m_particle_shader.getAttribLocation( "position" );
        glVertexAttribPointer(transformLocation,4, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        
         glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle[2]);
         glVertexAttribPointer(particleUVLocation,2, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        
    
        
        
        
        glVertexAttribDivisor(positionAttribLocation, 0);
        glVertexAttribDivisor(transformLocation, 1);
        CHECK_GL_ERRORS;
        
        
        // glVertexAttribDivisor(colorLocation, 1);
        
     
        
        //up load the P and V
        glm::mat4 view = m_view;
        
        GLint location = m_particle_shader.getUniformLocation("view");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(view));
        CHECK_GL_ERRORS;
        
        location = m_particle_shader.getUniformLocation("perspective");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_perpsective));
        CHECK_GL_ERRORS;
        
       
        location = m_particle_shader.getUniformLocation("model");
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(model));
        CHECK_GL_ERRORS;
        
        GLint uniformLocation_diffuse = m_particle_shader.getUniformLocation("diffuse");
        glUniform1i(uniformLocation_diffuse, 0);
        CHECK_GL_ERRORS;
        
        
        
        
        
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesCount);
        
        
        
        
        //-- Unbind target, and restore default values:
        //   glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    m_particle_shader.disable();
    
    
    CHECK_GL_ERRORS;

}

















void A3::callEnding(bool & button){
    if (button){
        bgm->drop();
         bgm = irrklang::createIrrKlangDevice();
         bgm->play2D("Assets/sound/ending.mp3", true);
        button = false;
    }
    
    
}




//https://learnopengl.com/#!Advanced-Lighting/Shadows/Shadow-Mapping
void A3::shadowFrame(){
  //  GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    
    // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
    //GLuint depthTexture;
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, SHADOW_WIDTH,SHADOW_HEIGHT, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    // glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, m_windowWidth, m_windowHeight, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, depthTexture, 0);
    
    glDrawBuffer(GL_NONE); // No color buffer is drawn to.
    glReadBuffer(GL_NONE);
    
    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "WARNING: TROUBLE --- Framebuffer is not complete." << endl;
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void A3::movePlayer(glm::vec3 howmany){
    glm::mat4 p = glm::translate(mat4(), howmany);
    SceneNode* player = getNode(m_rootNode, "player");
    player->set_transform(p *  player->get_transform());
}
void A3::rotatePlayer (float howmany, glm::vec3 axis){
    glm::mat4 p = glm::rotate(mat4(), howmany, axis);
    SceneNode* player = getNode(m_rootNode, "player");
    player->set_transform( player->get_transform() * p);
   
}

bool A3::collision(Object obj1, Object obj2){
    if(obj1.isVisible() && obj2.isVisible()){
        float A = obj1.getObjectPosition().x - obj2.getObjectPosition().x;
        float B = obj1.getObjectPosition().z - obj2.getObjectPosition().z;
        float D = obj1.getObjectPosition().y - obj2.getObjectPosition().y;
        float C = sqrt(A*A + B*B);
        float E = sqrt(B*B + D*D);
        if (C < obj1.getObjectSize() + obj2.getObjectSize() && E < obj1.getObjectSize() + obj2.getObjectSize()){
            return true;
        }
        else return false;
        
        
    }
    return false;
}



