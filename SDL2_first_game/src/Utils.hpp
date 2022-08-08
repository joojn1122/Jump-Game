#pragma once // pragma once -> this file will be loaded only once (include guards)

#include <SDL.h> // or "SDL.h"

// namespace -> useless, just for better orientation
namespace utils {

	// inline means method declaration in this header file
	inline float hireTimeInSeconds()
	{
		float t = SDL_GetTicks64();
		t *= 0.001f;

		return t;
	}
}
