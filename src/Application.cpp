#include <Protegon.h>

#include "scenes/Scenes.h"

int main(int c, char** v) {

	ptgn::Engine::Start<Level1>("level1", "Squirhell", { 800, 600 }, 60);

	return 0;
}