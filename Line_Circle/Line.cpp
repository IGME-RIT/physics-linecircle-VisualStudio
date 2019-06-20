/*
Title: Line and Circle 2D intersection
File Name: Line.cpp
Copyright © 2015
Revision Author: Srinivasan Thiagarajan
Original authors: Brockton Roth
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

#ifndef _LINE_CPP
#define _LINE_CPP
#include "Line.h"

Line::Line()
{
	point1 = glm::vec2(1.0f, 1.0f);
	point2 = glm::vec2(1.0f, 1.0f);
	lineColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Line::drawLine()
{
	// code to draw the line between two points.This is using a deprecated method. This should be done in the shaders. But for simple physics implementations and debugging,
	// this is enough. 
	glUseProgram(0);
	glLineWidth(2.5f);
	glColor3f(lineColor.x, lineColor.y, lineColor.z);
	glBegin(GL_LINES);
	glVertex3f(point1.x, point1.y, 0.0f);
	glVertex3f(point2.x, point2.y, 0.0f);

	if (isLine)
	{
		extendLineToInfinity();
	}
	
	glEnd();
}

void Line::extendLineToInfinity()
{
	// This part draws the green line which represents the entire line which extends to infinity
	float m;													// Slope of the line	(y = mx +c)
	m = (point2.y - point1.y) / (point2.x - point1.x);		// m = (y2-y1)/(x2-x1)
	float c = point1.y - (m * point1.x);				// constant		// c = y - mx
	glColor3f(0.0f, 1.0f, 0.0f);								// Change the color to Green 
	glVertex3f(10.0f, (m*10.0f) + c, 0.0f);					// vertex x value = 10
	glVertex3f(-10.0f, (m*(-10.0f)) + c, 0.0f);					// vertex x value = -10
}

void Line::setIsLine(bool _isLine)
{
	isLine = _isLine;
}

#endif // !_LINE_CPP
