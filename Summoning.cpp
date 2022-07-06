#include <iostream>
#include <SDL2/SDL.h>

#include <math.h>

const int HEIGHT = 400, WIDTH = 400;

#define N 8
#define SIZE (N - 1) * (N - 1)

SDL_Window *main_window = NULL;
SDL_Renderer *rendering_tool = NULL;
SDL_Rect array[SIZE];
SDL_Surface *main_surface = NULL;

bool initilaizing();

bool rendering(float array[]);

bool close();

void calculate(float matrix[][SIZE], float results[], float unkonwns[]);

void regulating(int size, float matrix[][SIZE]);

void printing_matrix(float matrix[][SIZE]);

void printing_matrix_format(float array[], int size);

int main(int argc, char *argv[])
{

    float matrix[SIZE][SIZE] = {0};
    float intila_state[SIZE] = {};
    intila_state[SIZE/2]=100;


    // giving an initial guess for the Gauss-Siedel method
    float guesses[SIZE] = {};
    for (int i = 0; i < SIZE; i++)
    {
        guesses[i] = 3;
    }

    // forms the desierd matrix which is diagonaly dominant
    regulating(SIZE, matrix);

    // we are calculating the matrix by suing Gausse-Siedel method
    for (int i = 0; i < 300; i++)
    {
        // printing_matrix_format(guesses,SIZE);
        std::cout << std::endl;
        calculate(matrix, intila_state, guesses);
    }
    std::cout << "This is the array with guesses which has to be our final resut\n";
    printing_matrix_format(guesses, SIZE);

    bool quit = false;

    if (!initilaizing())
    {
        std::cout << "Something went worng during initialization" << std::endl;
        system("echo Somtheign tragyc happend");
    }

    if (!rendering(guesses))
    {
        std::cout << "SOmething went wrong during the image rendering" << std::endl;
    }

    SDL_Event e;
    // initializing the base heat of our system
    // we are entering the rendering loop fo our porgram
     while(!quit){
         while (SDL_PollEvent(&e))
         {
             if(e.key.type==SDL_QUIT){
                 quit=true;
             }
         }

    rendering(guesses);
    
    }

    close();

    return 0;
}

bool initilaizing()
{

    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "An error ocured during the initial initialization of sdl ::" << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {

        main_window = SDL_CreateWindow("Tesing grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

        if (main_window == NULL)
        {
            std::cout << "An error occured during the initialization of the window ::" << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            rendering_tool = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
            if (rendering_tool == NULL)
            {
                std::cout << "An error ocured during the initiliaziation of the rederer:: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(rendering_tool, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return success;
}

bool rendering(float array2[])
{
    bool success = true;

    // WE WILL DO EVERYHTING HERE, BUT FIRST LET US TEST IT, SHALL WE!
    int color = 0;

    int square_metter = WIDTH / (N-1);
    for (int i = 0; i < (N-1); i++)
    {

        for (int j = 0; j < (N-1); j++)
        {

          
                array[i * (N-1) + j] = {j * square_metter, i * square_metter, square_metter, square_metter};
                SDL_SetRenderDrawColor(rendering_tool, array2[i * (N-1) + j]*2+50 , array2[i * (N-1) + j]*2+50 , array2[i * (N-1) + j]*2 +50, 0);
                SDL_RenderFillRect(rendering_tool, &array[i * (N-1) + j]);
    
        }
    }
    SDL_RenderPresent(rendering_tool);
    
    return success;
}

bool close()
{
    bool succes;

    SDL_DestroyRenderer(rendering_tool);
    SDL_DestroyWindow(main_window);
    rendering_tool = NULL;
    main_window = NULL;

    SDL_Quit();
}

void calculate(float matrix[][SIZE], float results[], float unkonwns[])
{
    float temp = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                temp += matrix[i][j] * unkonwns[j];
                
            }
        }

        unkonwns[i] = (results[i] - temp) / matrix[i][i];
        temp = 0;
    }
}

void regulating(int size, float matrix[][SIZE])
{

    // the first  rows of the matrix
    matrix[0][0] = 4;
    matrix[0][1] = -1;
    matrix[0][3] = -1;

    matrix[1][0] = -1;
    matrix[1][1] = 4;
    matrix[1][2] = -1;
    matrix[1][4] = -1;

    matrix[2][1] = -1;
    matrix[2][2] = 4;
    matrix[2][5] = -1;

    // the last 3 rows of the matrix

    matrix[size - 3][size - 3] = 4;
    matrix[size - 3][size - 6] = -1;
    matrix[size - 3][size - 2] = -1;

    matrix[size - 2][size - 5] = -1;
    matrix[size - 2][size - 2] = 4;
    matrix[size - 2][size - 3] = -1;
    matrix[size - 2][size - 1] = -1;

    matrix[size - 1][size - 4] = -1;
    matrix[size - 1][size - 1] = 4;
    matrix[size - 1][size - 2] = -1;

    int number = 0;
    for (int i = 3; i < size - 3; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 4;

                if (number == 0)
                {
                    matrix[i][j - 3] = -1;
                    matrix[i][j + 1] = -1;
                    matrix[i][j + 3] = -1;
                    number++;
                }
                else if (number == 1)
                {
                    matrix[i][j - 1] = -1;
                    matrix[i][j - 3] = -1;
                    matrix[i][j + 1] = -1;
                    matrix[i][j + 3] = -1;
                    number++;
                }
                else
                {
                    matrix[i][j - 1] = -1;
                    matrix[i][j + 3] = -1;
                    matrix[i][j - 3] = -1;
                    number++;
                }
                number = number % 3;
            }
        }
    }
}

void printing_matrix(float matrix[][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << " " << matrix[i][j];
        }
        std::cout << "\n";
    }
}

void printing_matrix_format(float array[], int size)
{
    int dimension = sqrt(size);
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            std::cout << " " << array[i * dimension + j];
        }
        std::cout << "\n";
    }
}