#pragma once
#include <iostream>
#include <string>
#include <stdarg.h>

class display
{
	private:
		size_t width;
		size_t height;

    public:
        display(const size_t&, const size_t&);
        ~display();
        void draw(const int&, const int&, const char*, ...);
		void flush();
        void clear();
		void draw_border(const char&);
	private:
		void move(const int&, const int&);
};