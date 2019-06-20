/*
Title: Line and Circle 2D intersection
File Name: Main.cpp
Copyright © 2015
Revision Author: Srinivasan Thiagarajan
Original authors: Brockton Roth
Modified by: Parth Contractor
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Description:
This is an example to detect the intersection of a line and circle in 2D. 
You can control the two end-points of the line segment which a small part of the line, and move them using "w,a,s,d" and "i,j,k,l" respectively.
The line turns blue when an intersection is detected, and turns red when there is no intersection. 
It checks for the point closest to the circle's center, which also lies on the line,
and checks if that point lies inside the circle. If so, collision is detected else not.
*/

#include "GLIncludes.h"
#include "GameObject.h"
#include "GLRender.h"
#include "Line.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Variables for FPS and Physics Timestep calculations.
int frame = 0;
double time = 0;
double timebase = 0;
double accumulator = 0.0;
int fps = 0;
double FPSTime = 0.0;
double physicsStep = 0.012; // This is the number of milliseconds we intend for the physics to update.

// Reference to the window object being created by GLFW.
GLFWwindow* window;

// Regular check if the line-segment intersects with the circle.
bool TestIntersection()
{
	//Now we find the point on the line (extended line segment) which is closest to the circle. We take the projection of the line joining the end 
	// Then we determine if that point lies outside or inside the circle.
	// if the point satisfies all these conditions then the line and the circle are colliding.

	//see if any of the end points of the line are inside the circle
	float dis = glm::distance(glm::vec2(0.0f, 0.0f), line.point1);
	if (dis < radius)
		return true;

	dis = glm::distance(glm::vec2(0.0f, 0.0f), line.point2);
	if (dis < radius)
		return true;

	glm::vec2 d = line.point2 - line.point1;								
	glm::vec2 lc = glm::vec2(0.0f, 0.0f) - line.point1;
	glm::vec2 projectionVector = glm::normalize(d);
	projectionVector  *= glm::dot(lc, projectionVector);

 	glm::vec2 nearestPoint = line.point1 + projectionVector;

	dis = glm::distance(glm::vec2(0.0f, 0.0f), nearestPoint);
	
	if (line.getIsLine())
	{
		return ((dis < radius));										// is the point inside the circle ?
	}

	return ((dis < radius)											// is the point inside the circle ?
		&& (glm::length(projectionVector) <= glm::length(d))		// does the point lie on the line segment in one direction?
		&& (glm::dot(projectionVector, d) >= 0));					// does the point lie on the line segment in the other direction?
}

// This runs once every physics timestep.
void update(float dt)
{
	//test if they are intersection. If so, change the color of the line segment.
	if (TestIntersection())
	{
		//Blue color
		line.lineColor.x = 0.0f;
		line.lineColor.y = 0.0f;
		line.lineColor.z = 1.0f;
	}
	else
	{	
		//red color
		line.lineColor.x = 1.0f;
		line.lineColor.y = 0.0f;
		line.lineColor.z = 0.0f;
	}
}



int main(int argc, char **argv)
{
	// Initializes the GLFW library
	glfwInit();

	// Creates a window given (width, height, title, monitorPtr, windowPtr).
	// Don't worry about the last two, as they have to do with controlling which monitor to display on and having a reference to other windows. Leaving them as nullptr is fine.
	window = glfwCreateWindow(800, 800, "Line and Circle 2D collision", nullptr, nullptr);

	// Makes the OpenGL context current for the created window.
	glfwMakeContextCurrent(window);
	
	// Sets the number of screen updates to wait before swapping the buffers.
	// Setting this to zero will disable VSync, which allows us to actually get a read on our FPS. Otherwise we'd be consistently getting 60FPS or lower, 
	// since it would match our FPS to the screen refresh rate.
	// Set to 1 to enable VSync.
	glfwSwapInterval(0);

	// Initializes most things needed before the main loop
	init();

	// Sends the funtion as a funtion pointer along with the window to which it should be applied to.
	glfwSetKeyCallback(window, key_callback);

	// Enter the main loop.
	while (!glfwWindowShouldClose(window))
	{
		update(0.25f);

		// Call the render function.
		renderScene();

		// Swaps the back buffer to the front buffer
		// Remember, you're rendering to the back buffer, then once rendering is complete, you're moving the back buffer to the front so it can be displayed.
		glfwSwapBuffers(window);

		// Add one to our frame counter, since we've successfully 
		frame++;

		// Checks to see if any events are pending and then processes them.
		glfwPollEvents();
	}

	cleanup();

	return 0;
}