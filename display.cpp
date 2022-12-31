#include "display.hpp"

display::display(const size_t &w, const size_t &h) : width(w), height(h)
{
    system("clear");
	flush();
}

display::~display()
{
	//clear();
	//flush();
}

void display::draw(const int &x, const int &y, const char* format, ...)
{
	//TODO : (x, y)에 c 그리기.
	va_list args;
	va_start(args, format);
	move(x, y);
	vprintf(format, args);
	va_end(args);
	move(0, height);
}

void display::flush()
{
	fflush(stdout);
}

void display::clear()
{
	move(0, 0);
	for(int i = 0;i<height;i++)
	{
		for(int j = 0;j<width;j++)
		{
			printf(" ");
		}
		printf("\n");
	}
}

void display::draw_border(const char &ch)
{
	for(int i = 0;i<width;i++)
	{
		for(int j = 0;j<height;j++)
		{
			if(i == 0 || i == width-1 || j == 0 || j == height-1)
			{
				move(i, j);
				printf("%c", ch);
			}
		}
	}
	move(0, height);
}

void display::move(const int &x, const int &y)
{
	printf("\033[%d;%dH", y+1, x+1);
}