#include <iostream>
#include "display.hpp"

int main(int argc, char *argv[])
{
	display dis(5, 5);
	dis.draw_border('-');
	//dis.draw(0, 0, "I'am Zero");
	//dis.draw(1, 1, "hello");
	//dis.draw(2, 2, "%d", 3);

	dis.flush();



    return 0;
}