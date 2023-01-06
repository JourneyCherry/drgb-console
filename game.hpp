#pragma once
#include <array>
#include <algorithm>
#include <map>

class game
{
	public:
		static constexpr int MAX_PLAYER = 2;
		static constexpr int MAX_HEALTH = 1;
		static constexpr int MAX_ENERGY = 2;

		enum action_type : int
		{
			meditate	 = 1 << 0,	//0000 0001
			guard		 = 1 << 1,	//0000 0010
			punch		 = 1 << 2,	//0000 0100
			evade		 = 1 << 3,	//0000 1000
			fire		 = 1 << 4,	//0001 0000
			count		 = 5
		};

	public:
		std::array<action_type, MAX_PLAYER> actions;
		std::array<int, MAX_PLAYER> healths;
		std::array<int, MAX_PLAYER> energies;
		std::map<action_type, int> required_energy;

	public:
		game();
		~game() = default;
		bool input(int, int);	//Player, Action
		bool process();
		int getwinner();
	private:
		inline int opponent(const int&);
};