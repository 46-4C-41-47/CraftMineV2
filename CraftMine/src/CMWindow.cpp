#include "../include/CMWindow.h"


int windowWidth, windowHeight;
glm::mat4 projection;


void rebuildProjectionMatrix()
{
    projection = glm::perspective(
        glm::radians(params::graphical::VIEW_ANGLE),
        (float)windowWidth / (float)windowHeight,
        params::graphical::NEAR_PLANE,
        params::graphical::FAR_PLANE
    );
}


void windowResizeCallback(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, windowWidth, windowHeight);

    rebuildProjectionMatrix();
}



CMWindow::CMWindow(std::string title, int width, int height) : title{ title }, fullscreen{ false }
{
    windowWidth = width;
    windowHeight = height;

	std::string* returnMesssage = initWindow();

    if (returnMesssage != nullptr)
    {
        throw std::runtime_error(*returnMesssage);
    }
}


CMWindow::CMWindow(std::string title, bool isFullscreen) : title{ title }, fullscreen{ isFullscreen }
{
    windowWidth = DEFAULT_WIDTH;
    windowHeight = DEFAULT_HEIGHT;

    std::string* returnMesssage = initWindow();

    if (returnMesssage != nullptr)
    {
        throw std::runtime_error(*returnMesssage);
    }
}


CMWindow::~CMWindow()
{
    glfwTerminate();
}


std::string* CMWindow::initWindow()
{
    if (!glfwInit())
    {
        return new std::string("Initialization of GLFW failed\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (fullscreen)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        windowWidth = mode->width;
        windowHeight = mode->height;
        window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    }
    else
    {
        window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
    }
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

    glViewport(0, 0, windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    //glfwSetCursorPosCallback(window, mouse_callback);

    glEnable(GL_DEPTH_TEST);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
}


int CMWindow::getWidth() { return windowWidth; }


int CMWindow::getHeight() { return windowHeight; }
