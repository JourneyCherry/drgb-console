#include "display.hpp"

display::display(const size_t &w, const size_t &h) : width(w), height(h)
{
    system("clear");
	flush();
}

display::~display()
{
	//clear();
	flush();
}

void display::draw(const int &x, const int &y, const char* format, ...)
{
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
	clear_color();
	move(0, height);
}

void display::clear()
{
	clear_color();
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

void display::draw_border()
{
	for(int i = 0;i<width;i++)
	{
		for(int j = 0;j<height;j++)
		{
			move(i, j);
			int bits = 0;
			if(i == 0)			bits |= 0b1000;	//left
			if(i == width-1)	bits |= 0b0100;	//right
			if(j == 0)			bits |= 0b0010;	//top
			if(j == height-1)	bits |= 0b0001;	//bottom
			switch(bits)
			{
				case 0b1010:	printf("┌");	break;
				case 0b1001:	printf("└");	break;
				case 0b0110:	printf("┐");	break;
				case 0b0101:	printf("┘");	break;
				case 0b1000:
				case 0b0100:
					printf("│");
					break;
				case 0b0010:
				case 0b0001:
					printf("─");
					break;
			}
		}	
	}
	move(0, height+1);
}

void display::move(const int &x, const int &y)
{
	printf("\033[%d;%dH", y+1, x+1);
}

void display::set_color(colors word, colors bg)
{
	set_color((int)word, (int)bg);
}

void display::set_color(int word, int bg)
{
	printf("\033[0;3%dm\033[0;4%dm", word, bg);
}

void display::clear_color()
{
	printf("\033[0m");
}