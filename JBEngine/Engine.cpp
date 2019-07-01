#include "pch.h"
#include "Engine.h"

// Disable nSight unknown object warning

Engine::Engine()
{
	MyWindow = new Window();
}

Engine::~Engine()
{
}

void Engine::MainLoop()
{
	// Get deltatime
	double lastTime = glfwGetTime();
	int totalFrames = 0;
	do {
		// Get delta time by comparing current time and last time
		double currentTime = glfwGetTime();
		m_deltaTime = float(currentTime - lastTime);

		// Update Window
		MyWindow->Update(m_deltaTime);

		// record new last time
		lastTime = currentTime;

	} // Check if the ESC key was pressed or the window was closed
	while (MyWindow->CheckWindowClose() == 0);

}
