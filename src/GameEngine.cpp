#include <game_engine/GameEngine.h>

int main(int argc, char **argv)
{
	for (int i=1; i<argc; i++) {
		std::cout << i << ' ' << argv[i] << std::endl;
	}

	return GUI().start();
}
