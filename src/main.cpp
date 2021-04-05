#include <engine/Include.h>

#include "core/Game.h"

int main(int argc, char* argv[]) {
	
	engine::Engine::Start<Game>("Squirhell", 512, 400, 60);

	return 0;

}