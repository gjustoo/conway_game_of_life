#include <stdio.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#define grid_cell_size 10
#define grid_width 100
#define grid_height 100

#define window_width (grid_width * grid_cell_size) + 1
#define window_height (grid_height * grid_cell_size) + 1

struct cell
{
    SDL_Rect grid_cursor; // cell_grid properties
    int alive;            // !0 if alive
    int next_alive;       // next generation alive state
};
typedef struct cell cell;

void check_generation(cell matrix[grid_height][grid_width]);

void update_alive_states(cell matrix[grid_height][grid_width]);
