#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <Model.hpp>

#include <Transform.hpp>

#include <MathUtil.hpp>

/******************************************************************************/
int main()
{
  // Initialize GLFW.
  if(!glfwInit())
  {
    std::cout << "Failed to initialize GLFW!" << std::endl;
    return -1;
  }

  // Set the desired OpenGL version to 3.3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Use the core profile only; this removes backwards-compatible features
  // that are no longer needed for the engine.
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE);

  // Enable forward compatibility; this removes all deprecated features
  // in the desired version of OpenGL (3.3).
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GLFW_TRUE);

  // Enable double buffering.
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

  // Create a new window.
  auto window = glfwCreateWindow(1280, 720, "cubes", nullptr, nullptr);
  if(window == nullptr)
  {
    std::cout << "Failed to create window!" << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD.
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return -1;
  }

  glViewport(0, 0, 1280, 720);
  glEnable(GL_DEPTH_TEST);

  // Load the shader.
  Kuma3D::Shader shader;
  shader.LoadFromFiles("resources/shaders/Model.vert",
                       "resources/shaders/Model.frag");

  // Load the model.
  Kuma3D::Model model;
  model.LoadFromFile("resources/model/Spitfire.obj");

  // Set shader uniforms.
  Kuma3D::Transform modelTransform;
  modelTransform.SetPosition(Kuma3D::Vec3(0, 0, -10));
  shader.Activate();
  shader.SetMat4("modelMatrix", modelTransform.GetMatrix());
  shader.SetMat4("viewMatrix", Kuma3D::View(Kuma3D::Vec3(0, 0, 1),
                                            Kuma3D::Vec3(1, 0, 0),
                                            Kuma3D::Vec3(0, 0, 0)));
  shader.SetMat4("projectionMatrix", Kuma3D::Perspective(45, 1280, 720, 0.1, 100));

  // Run until instructed to close.
  while(!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model.Draw(shader);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
