#include <iostream>
#include <thread>
#include <chrono>
#include "display.hpp"
#include "input.hpp"

int main(int argc, char *argv[])
{
	input in;
	display dis(15, 15);
	dis.draw_border('-');
	//dis.draw(0, 0, "I'am Zero");
	//dis.draw(1, 1, "hello");
	//dis.draw(2, 2, "%d", 3);

	dis.flush();

	std::this_thread::sleep_for(std::chrono::seconds(1));	//이 시간 內에 입력된 모든 키가 

	char ch;
	int i = 0;
	while(in._kbhit())
	{
		ch = in._getch();									//여기서 읽히게 된다.
		dis.draw(1, i+2, "%2d Input : %c", i+1, ch);
		i++;
	}
	dis.draw(1, 1, "Key Hit Count : %d", i);

	dis.flush();

    return 0;
}