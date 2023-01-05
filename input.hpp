#pragma once
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

class input
{
	private:
		struct termios initial_settings, new_settings;
		int peek_character;
	public:
		input();
		~input();
		int _kbhit();
		int _getch();
};