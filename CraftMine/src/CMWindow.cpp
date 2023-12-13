#include "../include/CMWindow.h"


glm::mat4 projection;


void rebuildProjectionMatrix(int width, int height)
{
    projection = glm::perspective(
        glm::radians(params::graphical::VIEW_ANGLE),
        (float)width / (float)height,
        params::graphical::NEAR_PLANE,
        params::graphical::FAR_PLANE
    );
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    rebuildProjectionMatrix(width, height);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F12 && action == GLFW_RELEASE)
    {
        std::cout << "Key held down\n";
    }
}



CMWindow::CMWindow(std::string title, int width, int height) : title{ title }, fullscreen{ false }
{
    init(width, height);
}


CMWindow::CMWindow(std::string title, bool isFullscreen) : title{ title }, fullscreen{ isFullscreen }
{
    init(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}


CMWindow::~CMWindow()
{
    delete objectShader, obj;
    glfwTerminate();
}


void CMWindow::init(int width, int height)
{
    std::string* returnMesssage = initWindow(width, height);

    if (returnMesssage != nullptr)
    {
        throw std::runtime_error(*returnMesssage);
    }

    objectShader = new Shader("./res/shaders/vertex_test.glsl", "./res/shaders/fragment_test.glsl");
    
    std::vector<glm::vec2> translations(100);
    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    obj = new InstancedMesh(translations);
}


std::string* CMWindow::initWindow(int width, int height)
{
    if (!glfwInit())
    {
        return new std::string("Initialization of GLFW failed\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    updateMonitorInfo();

    if (fullscreen)
        window = glfwCreateWindow(monitor.width, monitor.height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    //glfwSetWindowPos(window, 2625, 200);

    if (window == NULL)
    {
        return new std::string("GLFW window creation failed\n");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return new std::string("Failed to initialize GLAD\n");
    }

    glViewport(0, 0, getWidth(), getHeight());

    glfwSetKeyCallback(window, key_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void CMWindow::updateMonitorInfo()
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    monitor.width = mode->width;
    monitor.height = mode->height;
    monitor.redBits = mode->redBits;
    monitor.greenBits = mode->greenBits;
    monitor.blueBits = mode->blueBits;
    monitor.refreshRate = mode->refreshRate;
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

    obj->draw(*objectShader);

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void CMWindow::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        params::graphical::VIEW_ANGLE += 0.01f;
    
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        params::graphical::VIEW_ANGLE -= 0.01f;

    if (glfwGetKey(window, GLFW_KEY_F12) == GLFW_PRESS)
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

    fullscreen = !fullscreen;
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
