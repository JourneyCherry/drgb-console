#pragma once
#include <iostream>
#include <string>
#include <stdarg.h>

class display
{
	public:
		enum colors
		{
			black = 0,
			red,
			green,
			yellow,
			blue,
			purple,
			cyan,
			white
		};
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
		void set_color(colors, colors);
	private:
		void move(const int&, const int&);
		void set_color(int, int);
		void clear_color();
};