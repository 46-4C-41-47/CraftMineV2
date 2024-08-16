#include "../include/CMWindow.h"


int CMWindow::instanceCount = 0;

bool CMWindow::fullscreen = false;

glm::mat4 CMWindow::projection = glm::mat4(1.0f);

GLFWwindow* CMWindow::window = nullptr;

GLFWvidmode CMWindow::monitor = {};

Player* CMWindow::player = new Player(glm::vec3(0.5f, 0.5f, -1.0f));

ChunkRenderer* CMWindow::renderer = nullptr;

ChunkCluster* CMWindow::cluster = nullptr;


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
    delete objectShader;
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

    initWindow(width, height, x, y);
    rebuildProjectionMatrix(getWidth(), getHeight());

    objectShader = new Shader(params::graphical::CHUNK_VERTEX_SHADER_PATH, params::graphical::CHUNK_FRAGMENT_SHADER_PATH);

    cluster = new ChunkCluster();
    renderer = ChunkRenderer::getInstance();
}


void CMWindow::initWindow(int width, int height, int x, int y)
{
    if (!glfwInit())
        throw std::runtime_error("Initialization of GLFW failed\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    monitor = *glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (fullscreen)
        window = glfwCreateWindow(monitor.width, monitor.height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!fullscreen)
        glfwSetWindowPos(window, x, y);

    if (window == NULL)
        throw std::runtime_error("GLFW window creation failed\n");

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD\n");

    glViewport(0, 0, getWidth(), getHeight());

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    glEnable(GL_DEPTH_TEST);
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
    renderer->draw(*objectShader, projection, view, *cluster);

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void CMWindow::processInput()
{
    float camSpeed = params::controls::CAM_SPEED * previousFrameDuration;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camSpeed *= 2;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player->getCam().moveForward(camSpeed);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player->getCam().moveSideWays(-camSpeed);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player->getCam().moveForward(-camSpeed);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player->getCam().moveSideWays(camSpeed);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player->getCam().moveUpward(camSpeed);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        player->getCam().moveUpward(-camSpeed);
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
