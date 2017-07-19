#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/MeshConsolidator.hpp"

#include <math.h>

#include "SceneNode.hpp"
#include "trackball.hpp"

#include <glm/glm.hpp>
#include <memory>
#include "GeometryNode.hpp"
#include <vector>
#include <string>


#include "Texture.hpp"
#include "Skybox.hpp"
#include "Camera.hpp"
#include "Object.hpp"
#include "Particle.hpp"
#include "LensFlare.hpp"
#include "Sun.hpp"
#include "Shadow.hpp"
#include "Gui.hpp"

//for sound
#include <irrklang/irrKlang.h>

//Study based on:
//reference: https://github.com/mismayil/cs488/tree/master/A3

struct LightSource {
    glm::vec3 position;
    glm::vec3 rgbIntensity;
    
    glm::mat4 projection;
    glm::mat4 lightView;
};

struct process_cmd{

    std::vector<unsigned int> ids;
    glm::mat4 T;
    
};


class A3 : public CS488Window {
public:
    A3(const std::string & luaSceneFile);
    virtual ~A3();
    
protected:
    virtual void init() override;
    virtual void appLogic() override;
    virtual void guiLogic() override;
    virtual void draw() override;
    virtual void cleanup() override;
    
    //-- Virtual callback methods
    virtual bool cursorEnterWindowEvent(int entered) override;
    virtual bool mouseMoveEvent(double xPos, double yPos) override;
    virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
    virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
    virtual bool windowResizeEvent(int width, int height) override;
    virtual bool keyInputEvent(int key, int action, int mods) override;
   
    
    
    
    
    
    //-- One time initialization methods:
    void processLuaSceneFile(const std::string & filename);
    void createShaderProgram();
    void enableVertexShaderInputSlots();
    void uploadVertexDataToVbos(const MeshConsolidator & meshConsolidator);
    void mapVboDataToVertexShaderInputLocations();
    
    void initViewMatrix();
    void initLightSources();
    void initPerspectiveMatrix();
    
    void uploadCommonSceneUniforms();
    void updateShaderUniforms( const glm::mat4& MV, unsigned int idx, const glm::vec3& col, GeometryNode * node );
    
    void renderSceneGraph( SceneNode *node, int flag);
    void renderArcCircle();
    
    glm::mat4 m_perpsective;
    glm::mat4 m_view;
    
    LightSource m_light;
    
    //-- GL resources for mesh geometry data:
    GLuint m_vao_meshData;
    GLuint m_vbo_vertexPositions;
    GLuint m_vbo_vertexNormals;
    GLuint m_vbo_vertexTextCoords;    // <-----------------------
    GLuint m_vbo_vertexTangents;
    GLuint m_vbo_vertexBitangents;
    
    GLint m_positionAttribLocation;
    GLint m_normalAttribLocation;
    GLint m_uvAttribLocation;
    GLint m_tangentAttribLocation;
    GLint m_bitangentAttribLocation;
    
    
    
    
    ShaderProgram m_shader;
    
    //-- GL resources for trackball circle geometry:
    GLuint m_vbo_arcCircle;
    GLuint m_vao_arcCircle;
    GLint m_arc_positionAttribLocation;
    ShaderProgram m_shader_arcCircle;
    
    // BatchInfoMap is an associative container that maps a unique MeshId to a BatchInfo
    // object. Each BatchInfo object contains an index offset and the number of indices
    // required to render the mesh with identifier MeshId.
    BatchInfoMap m_batchInfoMap;
    
    std::string m_luaSceneFile;
    
    //std::shared_ptr<SceneNode> m_rootNode;
    SceneNode * m_rootNode;
    
    //============================================Mengyi add this==============================
    
    int NODEID_OF_HEAD_JOINT = 4;
    
    //adding something for mouse
    bool leftKey;
    bool middleKey;
    bool rightKey;
    
    double currentxpos;
    double currentypos;
    double cur_mx;
    double cur_my;
    double last_mx;
    double last_my;
    double distance;
    
    glm::mat4 TRANSPOSITION;
    glm::mat4 ORIENTATION;
    void resetPosition();
    void resetOrientation();
    void resetJoints();
    
    glm::mat4 TMP;
   // void changeJoint(SceneNode *, double dx, double dy, bool option);
    
    
    bool option_circle;
    bool option_zBuffer;
    bool option_backfaceCulling;
    bool option_frontfaceCulling;
    
    int current_mode;
    int mode_position = 1;
    int mode_joints = 2;
    
    //bool do_picking;
    std::vector<glm::mat4> xforms;
    std::vector<std::string> shapes;
    std::vector<glm::vec3> cols;
    std::vector<bool> selected;
    std::vector<unsigned int>picked_nodes;
    std::unordered_map<unsigned int, int>nodeId_to_id;
    std::unordered_map<int, unsigned int>id_to_nodeId;
    
    void reset(); // used to initialize everything
    //read in model
    void readInModel( SceneNode * root);
    //void markAllsubnodes(unsigned int id);
    void selectNode( SceneNode * root, unsigned int id);
    SceneNode * getNode(SceneNode * root, unsigned int id);
    SceneNode * findParentNode (SceneNode * root, unsigned int id);
    void markAllNodes(SceneNode* node);
    void renderSceneGraphHelper( SceneNode *node, glm::mat4 M, int flag);
    
    
    std::vector<process_cmd> theProcess;
    
    int last_one = -1;
    
    void add_a_process(std::vector<unsigned int> ids, glm::mat4 T);
    
    void undo();
    void redo();
    
    //========================================  A5 ================================
    //Texture sample
    Texture texture;
    
    //Skybox
    Skybox skybox;
    ShaderProgram m_skybox_shader;
    GLuint m_vao_skybox;
    GLuint m_vbo_skyboxPosition;
    
    //Sun
    Sun sun;
    ShaderProgram m_sun_shader;
    GLuint m_vao_sun;
    GLuint m_vbo_sunPosition;
    void sunRender();
    glm::mat4 applyViewMartrix(glm::mat4 modelMatrix, glm::mat4 viewMatrix);
    
    
    
    //lensflare
    ShaderProgram m_flare_shader;
    GLuint m_vao_flare;
    GLuint m_vbo_flarePosition;
    void renderFlare(std::vector<FlareTexture>flares, float brightness);
    void renderSun(glm::vec3 sunPos);
    glm::vec2 convertToScreenSpace(glm::vec3 worldPos, glm::mat4 viewMatrix, glm::mat4 perspectiveMatrix);
    void calcFlarePositions(glm::vec2 sunToCenter, glm::vec2 sunCoords);
    std::vector<FlareTexture> List_of_flares;
    
    //Shadow
    ShaderProgram m_shadow_shader;
    void shadowFrame();
    GLuint FramebufferName;
    GLuint depthTexture;
    
    //Camera
    Camera camera;
    
    //Player
    Object player;
    
    //Egg
    Object egg;
    Object egg1;
    Object egg2;
    std::vector<Object> eggBasket;
    
    //turtle
    Object turtle;
    Object turtle1;
    Object turtle2;
    std::vector<Object> turtleBucket;
    
    //Sound
    irrklang::ISoundEngine * bgm;
    void callEnding(bool & button);
    
    
    //Gui
    ShaderProgram m_gui_shader;
    GLuint m_vao_gui;
    GLuint m_vbo_gui;
    std::vector<Gui> guiBucket;
    void renderGui();
    
    
    
    //Particle
    ShaderProgram m_particle_shader;
    GLuint m_vao_particle;
    GLuint m_vbo_particle[3];
    Particle pContainer[MaxParticles];
    GLint particleUVLocation;
    void drawParticles(glm::mat4 model);
    void makeParticles(int num);
    int FindUnusedParticle();
    int countAliveParticles();
    
    //Particle Container
    ParticleContainer pc;
    void drawParticles(ParticleContainer pc, glm::mat4 model);  //<---didn't work well
    
    
    //Ball Player Controls
    SceneNode * getNode(SceneNode* root, std::string name);
    bool A_button_pressed = false;
    bool D_button_pressed = false;
    bool W_button_pressed = false;
    bool S_button_pressed = false;
    
    float distance_left_x = 0.0f;
    float distance_right_x = 0.0f;
    float distance_forward_z = 0.0f;
    float distance_backward_z = 0.0f;
    glm::vec3 player_pos = glm::vec3(0.0, 0.0, -5.0);
    float player_rolY = 0.0f;
    
    
    //glm::vec3 camera_pos = glm::vec3(0.0, 0.0, 0.0);
    //glm::vec3 camera_up = glm::vec3(0.0, 1.0, 0.0);
   
    void movePlayer(glm::vec3 howmany);
    void rotatePlayer (float howmany, glm::vec3 axis);
    
    bool collision(Object obj1, Object obj2);
    
    
    
};
