#pragma once
#include <string>

//dimensions in 2D that are whole numbers
struct Dim2Di
{
	int x, y;
};

//dimensions in 2D that are floating point numbers
struct Dim2Df
{
	float x, y;
};


/*
Send text to the debug output window
Second parameter can be ignored
*/
void DebugPrint(const std::string& mssg1, const std::string& mssg2 = "");

