#include "Simulator.h"

void Simulator::setUp()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simple Cloth Simulation", NULL, NULL);
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST); // for 3D 

    m_resource_manager = new ResourceManager();
    m_resource_manager->loadShader("Basic", "../shader/vertex_shader.vs", "../shader/fragment_shader.fs");
    m_resource_manager->loadShader("Cloth", "../shader/cloth.vs", "../shader/cloth.fs");

    m_sphere = new Sphere();
    m_cam = new Camera(glm::vec3(0.0f, 0.5f, 5.0f));
    m_cloth = new Cloth(50, 50, 0.1f, -2.0f, -2.0f, -2.0f);

    glm::mat4 projection = glm::perspective(glm::radians(m_cam->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = m_cam->GetViewMatrix();
    m_resource_manager->getShader("Basic").use().setMat4("projection", projection);
    m_resource_manager->getShader("Basic").use().setMat4("model", model);
    m_resource_manager->getShader("Basic").use().setMat4("view", view);
    m_resource_manager->getShader("Basic").use().setVec3("viewPos", m_cam->Position);

    m_resource_manager->getShader("Cloth").use().setMat4("projection", projection);
    m_resource_manager->getShader("Cloth").use().setMat4("model", model);
    m_resource_manager->getShader("Cloth").use().setMat4("view", view);
    m_resource_manager->getShader("Cloth").use().setVec3("viewPos", m_cam->Position);

}

void Simulator::run()
{
    Shader basic_shader = m_resource_manager->getShader("Basic");
    Shader cloth_shader = m_resource_manager->getShader("Cloth");

    float last_time = 0.0f;
    float curr_time = 0.0f;
    float delta_time;

    while (!glfwWindowShouldClose(m_window))
    {
        curr_time = static_cast<float>(glfwGetTime());
        delta_time = curr_time - last_time;
        last_time = curr_time;

        processInput(m_window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 100.0f);


        m_sphere->draw(basic_shader);

        m_cloth->update(delta_time);
        m_cloth->draw(cloth_shader);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
        
    }
}

void Simulator::exit()
{
    glfwDestroyWindow(m_window);

    delete m_cam;
    delete m_sphere;
    delete m_cloth;
    delete m_resource_manager;
}

void Simulator::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}