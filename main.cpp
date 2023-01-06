#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <string>
#include "display.hpp"
#include "input.hpp"
#include "game.hpp"

int main(int argc, char *argv[])
{
	const int dis_width = 50;
	const int dis_height = 10;
	input in;
	display dis(dis_width, dis_height);
	game gm;

	bool isRunning = true;
	bool hide_input = false;

	const double display_time = 0.08;
	const double game_time = 2.0;

	double display_timer = 0.0;
	double game_timer = game_time;

	std::chrono::duration<double> dt;
	std::chrono::time_point start = std::chrono::system_clock::now();
	std::chrono::time_point end = start;

	using colors = display::colors;

	while(isRunning)
	{
		while(in._kbhit())
		{
			int key = in._getch();
			switch(key)
			{
				//left player
				case 'a':	gm.input(0, 0);	break;	//meditate
				case 's':	gm.input(0, 1);	break;	//guard
				case 'd':	gm.input(0, 3);	break;	//evade
				case 'w':	gm.input(0, 2);	break;	//punch
				case 'e':	gm.input(0, 4);	break;	//fire

				//right player
				case 'l':	gm.input(1, 0);	break;	//meditate
				case ';':	gm.input(1, 1);	break;	//guard
				case '\'':	gm.input(1, 3);	break;	//evade
				case 'p':	gm.input(1, 2);	break;	//punch
				case '[':	gm.input(1, 4);	break;	//fire

				//system
				case 'h':	hide_input = !hide_input;	break;
				case 27:	isRunning = false;	break;	//esc
			}
		}

		end = std::chrono::system_clock::now();
		dt = end - start;
		start = end;
		double delta_time = dt.count();

		display_timer -= delta_time;
		game_timer -= delta_time;

		if(game_timer <= 0.0)
		{
			game_timer += game_time;
			if(gm.process())
				isRunning = false;
		}

		if(display_timer <= 0.0)
		{
			display_timer += display_time;

			//BorderLine Display
			{
				dis.set_color(colors::black, colors::black);
				dis.draw_border();
			}

			//Time Display
			{
				static const int col = 1;
				int remain_time = std::floor(game_timer*2);
				dis.draw(col, 1, "Remain Time : %d", remain_time);
				int line = (int)(std::floor((game_timer / game_time) * (dis_width-2)));
				for(int i = 1;i<dis_width - 1;i++)
				{
					if(i - 1 < line)
						dis.set_color(colors::cyan, colors::blue);
					else
						dis.set_color(colors::cyan, colors::red);
					dis.draw(i, col+1, "#");
				}
			}

			//Health Display
			{
				static const int col = 3;
				int left = gm.healths[0];
				int right = gm.healths[1];
				for(int i = 0;i<gm.MAX_HEALTH;i++)
				{
					if(left-- > 0)	dis.set_color(colors::white, colors::red);
					else			dis.set_color(colors::white, colors::black);
					dis.draw(i + 2, col, "O");

					if(right-- > 0)	dis.set_color(colors::white, colors::red);
					else			dis.set_color(colors::white, colors::black);
					dis.draw(dis_width - (i+2) - 1, col, "O");
				}
			}

			//Energy Display
			{
				static const int col = 4;
				int left = gm.energies[0];
				int right = gm.energies[1];
				for(int i = 0;i<gm.MAX_ENERGY;i++)
				{
					if(left-- > 0)	dis.set_color(colors::green, colors::blue);
					else			dis.set_color(colors::green, colors::black);
					dis.draw(i + 2, col, "O");

					if(right-- > 0)	dis.set_color(colors::green, colors::blue);
					else			dis.set_color(colors::green, colors::black);
					dis.draw(dis_width - (i+2) - 1, col, "O");
				}
			}

			//Action Display
			{
				static const int col = 6;
				static std::array<int, 2> row = {2, dis_width - 2};
				static const std::string ui = "Action";
				dis.set_color(colors::black, colors::black);
				for(int i = 0;i<gm.MAX_PLAYER;i++)
				{
					std::string str;
					switch(gm.actions[i])
					{
						case game::action_type::meditate:	str = "Medit";	break;
						case game::action_type::guard:		str = "Guard";	break;
						case game::action_type::punch:		str = "Punch";	break;
						case game::action_type::evade:		str = "Evade";	break;
						case game::action_type::fire:		str = "Shoot";	break;
					}
					if(hide_input)							str = "?????";
					dis.draw(row[i] - ui.length()*i, col, "%s", ui.c_str());
					dis.draw(row[i] - str.length()*i, col + 1, "%s", str.c_str());
				}
			}

			dis.flush();
		}
	}

	int result = gm.getwinner();
	std::string r_str;
	if(result < 0)
	{
		r_str = "Draw!";
		dis.set_color(colors::cyan, colors::green);
	}
	else
	{
		r_str = "Player " + std::to_string(result) + " Wins!";
		dis.set_color(colors::white, colors::blue);
	}

	dis.draw((dis_width - r_str.length())/2, dis_height - 2, "%s", r_str.c_str());
	dis.flush();

    return 0;
}