#define SDL_COMPILE_TIME_ASSERT(name, x)               \
    typedef int SDL_compile_time_assert_##name[(x) * 2 - 1]
SDL_COMPILE_TIME_ASSERT(SDL_Event, sizeof(SDL_Event) == sizeof(((SDL_Event *)NULL)->padding));
