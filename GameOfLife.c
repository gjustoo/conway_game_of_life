#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
    printf("Hello conway's Game Of Life\n");

    int grid_cell_size = 10;
    int grid_width = 100;
    int grid_height = 100;

    int window_width = (grid_width * grid_cell_size) + 1;
    int window_height = (grid_height * grid_cell_size) + 1;

    // Dark theme.
    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
    SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White

    // Cell definition
    // SDL_Rect grid_cursor = {
    //     .x = (grid_width - 1) / 2 * grid_cell_size,
    //     .y = (grid_height - 1) / 2 * grid_cell_size,
    //     .w = grid_cell_size,
    //     .h = grid_cell_size,
    // };

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

    int n_cells = 20;

    struct SDL_Rect cells[n_cells];

    for (int i = 0; i < n_cells; i++)
    {
        int rand_x = rand() % (window_width) + 1;
        int rand_y = rand() % (window_height) + 1;
        SDL_Rect grid_cursor = {
            .x = rand_x,
            .y = rand_y,
            .w = grid_cell_size,
            .h = grid_cell_size,
        };

        cells[i] = grid_cursor;
    }

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

        // Generate random cells

        SDL_SetRenderDrawColor(renderer, grid_cursor_color.r,
                               grid_cursor_color.g, grid_cursor_color.b,
                               grid_cursor_color.a);

        for (int i = 0; i < n_cells; i++)
        {
            SDL_RenderFillRect(renderer, &cells[i]);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\n BYE BYE !\n");
    return 0;
}