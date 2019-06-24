#include "pch.h"
#include "Window.h"

// Error codes
#define W_GLFW_FAILED_TO_INITIALISE -100
#define W_WINDOW_FAILED_TO_OPEN -101
#define W_COULD_NOT_INITIALISE_GLEW -102

int Window::s_windowWidth = WINDOW_WIDTH;
int Window::s_windowHeight = WINDOW_HEIGHT;

Window::Window()
{
	Initialise();
}

Window::~Window()
{
	// Clean up
	// Delete objects
	delete m_leftCube;
}

int Window::Initialise()
{	
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	// Try to initialise
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return W_GLFW_FAILED_TO_INITIALISE;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "JBEngine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. \n");
		glfwTerminate();
		return W_WINDOW_FAILED_TO_OPEN;
	}

	// Initialize GLEW
	glfwMakeContextCurrent(window); 
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return W_COULD_NOT_INITIALISE_GLEW;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// light blue background
	glClearColor(0.6f, 0.85f, 0.92f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Create Camera
	m_myCamera = new Camera();

	// Create and compile our GLSL program from the shaders
	//m_leftCube = new Object();
	m_rightCube = new Object();


	// Model matrix : an identity matrix (model will be at the origin)
	//m_leftCube->SetModelMatrix(glm::mat4(1.0f));
	m_rightCube->SetModelMatrix(glm::mat4(1.0f));

	// Our ModelViewProjection : multiplication of our 3 matrices
	//MVP = Projection * View * Cube->GetModelMatrix(); // Remember, matrix multiplication is the other way around

 	return 1;
}

void Window::Update()
{
	
	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_leftCube->Draw(m_myCamera);
	m_rightCube->Draw(m_myCamera);

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

}

GLFWwindow* Window::GetWindowComponent()
{
	return window;
}

int Window::CheckWindowClose()
{
	// returns false if ESC not pressed or window isn't attempting to 
	//  close.
	return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window);
}
