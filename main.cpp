#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#include <string.h>
#include <stdlib>
#include <stdio>
#include <SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif
#define timer 25

void pause();

int main ( int argc, char** argv )
{
    int tempsPrecedent = 0, tempsActuel = 0;
    SDL_Event event;
    int continuer = 1;
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *joueur = NULL; // Le pointeur qui va stocker la surface de l'écran

    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;

    SDL_Rect positionjoueur;
    positionjoueur.x = 250;
    positionjoueur.y = 400;


    typedef struct SDL_Rect
    {
        Sint32 x, y;
        Uint32 w, h;
    } SDL_Rect;

    Sint32 y = -7400;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    };
    ecran = SDL_SetVideoMode(560, 700, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    SDL_WM_SetCaption("Flying shark!", NULL);
    /* Chargement d'une image Bitmap dans une surface */
    imageDeFond = IMG_Load("img/map2.png");
    joueur = IMG_Load("img/avion.png");

    while (continuer)
    {
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            //positionFond.y++; /* On bouge Zozor */
            y++;

            if(y==0)
            {
                continuer=0;
            }
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }
        /* On blitte par-dessus l'écran */
        positionFond.y = y;
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_BlitSurface(joueur, NULL, ecran, &positionjoueur);

        SDL_Flip(ecran);

        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT:
                joueur = IMG_Load("img/avion.png");
                break;
            case SDLK_RIGHT:
                joueur = IMG_Load("img/avion.png");
                break;
            case SDLK_UP:
                joueur = IMG_Load("img/avion.png");
                break;
            case SDLK_DOWN:
                joueur = IMG_Load("img/avion.png");
                break;
            default:
                joueur = IMG_Load("img/avion.png");
                break;

            }break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_LEFT:
                positionjoueur.x = positionjoueur.x -5;
                joueur = IMG_Load("img/jl.gif");
                break;
            case SDLK_RIGHT:
                positionjoueur.x = positionjoueur.x +5;
                joueur = IMG_Load("img/jr.gif");
                break;
            case SDLK_UP:
                positionjoueur.y = positionjoueur.y -5;
                joueur = IMG_Load("img/avion.png");
                break;
            case SDLK_DOWN:
                positionjoueur.y = positionjoueur.y +5;
                joueur = IMG_Load("img/avion.png");
                break;
            default:
                joueur = IMG_Load("img/avion.png");
                break;

            }
            break;
        }
    }

    SDL_FreeSurface(imageDeFond); /* On libère la surface */
    SDL_FreeSurface(joueur);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
        }
    }
}
