#include "../include/CMWindow.h"


int CMWindow::instanceCount = 0;

bool CMWindow::fullscreen = false;

glm::mat4 CMWindow::projection = glm::mat4(1.0f);

GLFWwindow* CMWindow::window = nullptr;

GLFWvidmode CMWindow::monitor = {};

std::shared_ptr<Player> CMWindow::player = std::make_shared<Player>(params::world::DEFAULT_PLAYER_LOCATION);

std::unique_ptr<ChunkCluster> CMWindow::cluster = nullptr;

std::unique_ptr<Compass> CMWindow::compass = nullptr;



CMWindow::CMWindow(std::string title, int width, int height, int x, int y) : title{ title }
{
    fullscreen = false;
    init(width, height, x, y);
}


CMWindow::CMWindow(std::string title, bool isFullscreen) : title{ title }
{
    fullscreen = isFullscreen;
    init(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}


CMWindow::~CMWindow()
{
    glfwTerminate();
    instanceCount -= 1;
}


void CMWindow::rebuildProjectionMatrix(int width, int height)
{
    projection = glm::perspective(
        glm::radians(params::graphical::VIEW_ANGLE),
        (float)width / (float)height,
        params::graphical::NEAR_PLANE,
        params::graphical::FAR_PLANE
    );
}


void CMWindow::resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    rebuildProjectionMatrix(width, height);
}


void CMWindow::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    player->getCam().proccessMouse((int)xpos, (int)ypos);
}


void CMWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
        toggleFullscreenMode();
}


void CMWindow::toggleFullscreenMode()
{
    if (fullscreen)
    {
        glfwSetWindowMonitor(window, NULL, 100, 100, DEFAULT_WIDTH, DEFAULT_HEIGHT, monitor.refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(
            window,
            glfwGetPrimaryMonitor(), 
            0, 0, 
            monitor.width, monitor.height, 
            monitor.refreshRate
        );
    }
    rebuildProjectionMatrix(getWidth(), getHeight());
    fullscreen = !fullscreen;
}


void CMWindow::init(int width, int height, int x, int y)
{
    if (0 < instanceCount)
        throw std::runtime_error("CMWindow class can only have one instance at a time");

    instanceCount += 1;

    std::srand(std::time(nullptr));

    initWindow(width, height, x, y);
    rebuildProjectionMatrix(getWidth(), getHeight());

    objectShader = std::make_unique<Shader>(
        params::graphical::CHUNK_VERTEX_SHADER_PATH, 
        params::graphical::CHUNK_FRAGMENT_SHADER_PATH
    );
    compassShader = std::make_unique<Shader>(
        params::graphical::COMPASS_VERTEX_SHADER_PATH,
        params::graphical::COMPASS_FRAGMENT_SHADER_PATH
    );

    cluster = std::make_unique<ChunkCluster>(player);
    compass = std::make_unique<Compass>();
}


void CMWindow::initWindow(int width, int height, int x, int y)
{
    if (!glfwInit())
        throw std::runtime_error("Initialization of GLFW failed\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, params::developement::OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, params::developement::OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    monitor = *glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (fullscreen)
        window = glfwCreateWindow(monitor.width, monitor.height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL)
        throw std::runtime_error("GLFW window creation failed\n");

    if (!fullscreen)
        glfwSetWindowPos(window, x, y);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD\n");

    glViewport(0, 0, getWidth(), getHeight());

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    glEnable(GL_DEPTH_TEST);

    if (params::developement::ENABLE_FACE_CULLING)
        glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void CMWindow::start()
{
    std::chrono::steady_clock::time_point begin, end;

    while (!glfwWindowShouldClose(window))
    {
        begin = std::chrono::steady_clock::now();

        run();

        end = std::chrono::steady_clock::now();
        previousFrameDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        frameRateUpdateLimit += previousFrameDuration;
        updateFramerate();
    }
}


void CMWindow::updateFramerate()
{
    if (frameRateUpdateLimit < SECOND) 
        return;

    int frameRate = SECOND / (float)previousFrameDuration;
    std::string newTitle = title + ", FPS : " + std::to_string(frameRate) + ", " + std::to_string((float)previousFrameDuration / 1000) + " ms";
    
    glfwSetWindowTitle(window, newTitle.c_str());
    frameRateUpdateLimit = 0;
}


void CMWindow::run()
{
    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = player->getCam().getViewMatrix();
    cluster->draw(*objectShader, projection, view);

    if (params::developement::DEBUG_MODE)
        compass->draw(*compassShader, projection, player->getCam());

    //glm::vec3 pos = player->getCam().position;
    //std::cout << "x : " << (int)pos.x << ", y : " << (int)pos.y << ", z : " << (int)pos.z << "\n";

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void CMWindow::processInput()
{
    float camSpeed = params::controls::CAM_SPEED * previousFrameDuration;

    if (glfwGetKey(window, params::bindings::SPRINT) == GLFW_PRESS)
        camSpeed *= 2;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, params::bindings::MOVE_FORWARD) == GLFW_PRESS)
        player->getCam().moveForward(camSpeed);

    if (glfwGetKey(window, params::bindings::MOVE_LEFT) == GLFW_PRESS)
        player->getCam().moveSideWays(-camSpeed);

    if (glfwGetKey(window, params::bindings::MOVE_BACKWARD) == GLFW_PRESS)
        player->getCam().moveForward(-camSpeed);

    if (glfwGetKey(window, params::bindings::MOVE_RIGHT) == GLFW_PRESS)
        player->getCam().moveSideWays(camSpeed);

    if (glfwGetKey(window, params::bindings::JUMP) == GLFW_PRESS)
        player->getCam().moveUpward(camSpeed);

    if (glfwGetKey(window, params::bindings::CROUCH) == GLFW_PRESS)
        player->getCam().moveUpward(-camSpeed);

    /* DEV BINDING */

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && params::developement::DEBUG_MODE)
    {
        std::cout << "\nPlayer position ("
            <<   "x : " << (int)player->getCam().getPosition().x
            << ", y : " << (int)player->getCam().getPosition().y
            << ", z : " << (int)player->getCam().getPosition().z
            << ")";

        std::cout << "\nPlayer chunk position ("
            <<   "x : " << (int)player->getChunkPos().x
            << ", y : " << (int)player->getChunkPos().y
            << ")";

        /*const Chunk& c = (*cluster)[ChunkCluster::getKey(
            (int)player->getChunkPos().x,
            (int)player->getChunkPos().y
        )];
        std::cout << "\nChunk faces status ("
            <<   "NORTH : " << c.getFacesStatus()[constants::NORTH]
            << ", SOUTH : " << c.getFacesStatus()[constants::SOUTH]
            <<  ", EAST : " << c.getFacesStatus()[constants::EAST]
            <<  ", WEST : " << c.getFacesStatus()[constants::WEST]
            << ")";*/
    }
}


int CMWindow::getWidth()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}


int CMWindow::getHeight() 
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}
