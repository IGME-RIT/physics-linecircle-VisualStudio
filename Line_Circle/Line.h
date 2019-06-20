/*
Title: Line and Circle 2D intersection
File Name: Line.h
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

#ifndef _LINE_H
#define _LINE_H

#include "GLIncludes.h"

class Line
{
public:
	glm::vec2 point1;
	glm::vec2 point2;
	glm::vec3 lineColor;

	Line();
	void drawLine();
	void extendLineToInfinity();
	void setIsLine(bool _isLine);
	bool getIsLine()
	{
		return isLine;
	}

private:
	bool isLine = true;
};

#endif // !_LINE_H