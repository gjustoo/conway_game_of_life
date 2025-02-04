#include "gol.h"

int main()
{
    printf("Hello conway's Game Of Life\n");

    // Creamos la matriz de celulas o casillas
    struct cell cell_matrix[grid_height][grid_width];

    // Inicializar una celula por casilla:
    printf("B1\n");

    for (int y = 0; y < grid_height; y++)
    {
        for (int x = 0; x < grid_width; x++)
        {

            cell_matrix[x][y] = (struct cell){
                .grid_cursor = (struct SDL_Rect){
                    .x = x * grid_cell_size,
                    .y = y * grid_cell_size,
                    .w = grid_cell_size,
                    .h = grid_cell_size,
                },
                .alive = rand() % 10};
        }
    }

    // Dark theme.
    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
    SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create a window
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Create window and rederer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Conway's Game Of Life");

    SDL_bool quit = SDL_FALSE;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;

    // Event Loop
    while (!quit)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g, grid_line_color.b, grid_line_color.a);

        for (int x = 0; x < window_width; x += grid_cell_size)
        {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }

        for (int y = 0; y < window_height; y += grid_cell_size)
        {

            SDL_RenderDrawLine(renderer, window_width, y, 0, y);
        }

        // Pintamos las celulas

        SDL_SetRenderDrawColor(renderer, grid_cursor_color.r,
                               grid_cursor_color.g, grid_cursor_color.b,
                               grid_cursor_color.a);

        for (int y = 0; y < grid_width; y++)
        {
            for (int x = 0; x < grid_height; x++)
            {

                if (cell_matrix[x][y].alive)
                {
                    SDL_RenderFillRect(renderer, &cell_matrix[x][y].grid_cursor);
                }
            }
        }
        SDL_RenderPresent(renderer);
        check_generation(cell_matrix);
        update_alive_states(cell_matrix);
        // sleep(2);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\n BYE BYE !\n");
    return 0;
}

void check_generation(cell matrix[grid_height][grid_width])
{

    int total_deaths = 0;
    int total_revives = 0;
    int total_keep_alive = 0;
    for (int y = 0; y < grid_width; y++)
    {
        for (int x = 0; x < grid_height; x++)
        {

            // Check underpopulation
            int alive_neighbours = 0;

            // [][][]
            // []  []
            // [][][]

            for (int xx = -1; xx <= 1; xx++)
            {
                for (int yy = -1; yy <= 1; yy++)
                {
                    // Skip (0,0), which is the cell itself
                    if (xx == 0 && yy == 0)
                        continue;

                    int nx = x + xx;
                    int ny = y + yy;

                    // Check that nx, ny are within 0..grid_width-1, 0..grid_height-1
                    if (nx >= 0 && nx < grid_width && ny >= 0 && ny < grid_height)
                    {
                        if (matrix[nx][ny].alive != 0)
                        {
                            alive_neighbours++;
                        }
                    }
                }
            }

            if (alive_neighbours < 2 && matrix[x][y].alive != 0)
            {

                matrix[x][y].next_alive = 0;
                // printf("I SHOULD DIE!");
                total_deaths++;
            }
            else if (alive_neighbours > 3 && matrix[x][y].alive != 0)
            {
                matrix[x][y].next_alive = 0;
                // printf("I SHOULD DIE!");
                total_deaths++;
            }
            else if (alive_neighbours = 3 && matrix[x][y].alive == 0)
            {
                matrix[x][y].next_alive = 1;
                total_revives++;
            }
            else if (alive_neighbours >= 2 && alive_neighbours <= 3 && matrix[x][y].alive != 0)
            {
                matrix[x][y].next_alive = 1;
                total_keep_alive++;
            }
        }
    }

    printf("%d cells should DIE \n", total_deaths);
    printf("%d cells should STAY ALIVE \n", total_keep_alive);
    printf("%d cells should REVIVE \n", total_revives);
}

void update_alive_states(cell matrix[grid_height][grid_width])
{

    for (int y = 0; y < grid_width; y++)
    {
        for (int x = 0; x < grid_height; x++)
        {
            matrix[x][y].alive = matrix[x][y].next_alive;
        }
    }
}