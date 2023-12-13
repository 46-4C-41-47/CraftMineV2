#include "../include/CMWindow.h"


int CMWindow::instanceCount = 0;

bool CMWindow::fullscreen = false;

glm::mat4 CMWindow::projection = glm::mat4(1.0f);

GLFWwindow* CMWindow::window = nullptr;

GLFWvidmode CMWindow::monitor = {};

Camera* CMWindow::cam = new Camera();


CMWindow::CMWindow(std::string title, int width, int height) : title{ title }
{
    fullscreen = false;
    init(width, height);
}


CMWindow::CMWindow(std::string title, bool isFullscreen) : title{ title }
{
    fullscreen = isFullscreen;
    init(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}


CMWindow::~CMWindow()
{
    delete objectShader, obj;
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
    cam->proccessMouse(xpos, ypos);
}


void CMWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F12 && action == GLFW_RELEASE)
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


void CMWindow::init(int width, int height)
{
    if (0 < instanceCount)
        throw std::runtime_error("CMWindow class can have only one instance at a time");

    instanceCount += 1;

    initWindow(width, height);

    rebuildProjectionMatrix(getWidth(), getHeight());

    objectShader = new Shader("./res/shaders/vertex_test.glsl", "./res/shaders/fragment_test.glsl");
    
    std::vector<glm::vec3> translations = { 
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(3.0f, 1.0f, 0.7f),
        glm::vec3(0.5f, 0.0f, -7.6f)
    };

    obj = new InstancedMesh(translations);
}


void CMWindow::initWindow(int width, int height)
{
    if (!glfwInit())
        throw std::runtime_error("Initialization of GLFW failed\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    monitor = *glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (fullscreen)
        window = glfwCreateWindow(monitor.width, monitor.height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    glfwSetWindowPos(window, 100, 100);
    //glfwSetWindowPos(window, 2625, 200);

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void CMWindow::start(int frameRate)
{
    if (frameRate == -1)
    {
        std::chrono::high_resolution_clock::time_point start, end;
        double delta = 0, frameInterval = 1000000.0f / frameRate;

        while (!glfwWindowShouldClose(window))
        {
            start = std::chrono::high_resolution_clock::now();
            
            run();

            end = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::this_thread::sleep_for(
                std::chrono::microseconds((int)std::max(frameInterval - delta, 0.0))
            );
        }
    }
    else
    {
        while (!glfwWindowShouldClose(window))
        {
            run();
        }
    }
}


void CMWindow::run()
{
    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = cam->getViewMatrix();
    obj->draw(*objectShader, projection, view);

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void CMWindow::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    double camSpeed;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camSpeed = params::controls::CAM_SPEED * 2.0 * 0.00005;
    else
        camSpeed = params::controls::CAM_SPEED * 0.00005;


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->moveForward(camSpeed);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->moveSideWays(-camSpeed);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->moveForward(-camSpeed);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->moveSideWays(camSpeed);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam->moveUpward(camSpeed);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam->moveUpward(-camSpeed);
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
