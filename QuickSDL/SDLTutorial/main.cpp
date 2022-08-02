#include "GameManager.h"

#if defined(_WIN64)
int wmain(int argc, char* argv[]) {
#else
int main(int argc, char* argv[]) {
#endif
	QuickSDL::GameManager* game = QuickSDL::GameManager::Instance();

	game->Run();

	QuickSDL::GameManager::Release();
	game = NULL;

	return 0;
}