#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h> //pour gérer le random
#include <SDL/SDL_mixer.h> //pour gérer le son
#include "main.h"


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

int DistanceObjectFromPerso(int movement,long posX)
{
    return ((heightWindows+movement)-posX);
}

void image(SDL_Surface *ecran,long posX, long posY, char name[linelength])
{
    SDL_Surface *image = NULL;
    SDL_Rect position;
    position.x=posX;
    position.y=posY;
    image = SDL_LoadBMP(name);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 255, 255));//on rend transparent le blanc
    SDL_BlitSurface(image, NULL, ecran, &position);
    SDL_FreeSurface(image);
}

void sautperso(SDL_Surface *ecran,long posXbackground,long posX, long *posY,long posiY,int *movement2,int *movement)
{
    SDL_Event event;
    SDL_WaitEvent(&event);
    Image ground;
    int DstObjet = DistanceObjectFromPerso(*movement2,posX);
    ground.x = *movement2;
    ground.y = 400;
    char buf[256];
    int tmp = *posY;
    Speed s;

    //moveground(ecran,posXbackground,movement2,s.zero,posX,posiY);

    for (int i=1;i<=6;i++)
    {//modif pos perso pour img 2,3,4
        char buf[256];
        sprintf(buf,"Pictures/jump%d.bmp",i);

        switch(i)
        {
            case 2:
                *posY-=40;
            break;
            case 3:
                *posY -=30;
            break;
            case 4:
                *posY -= 40;
                if(( DstObjet < 100 )&&( DstObjet > 65 )) //si posCaisse - posPerso <50
                    tmp = tmp - 50; //monte sur caisse
                if( DstObjet<-65 && DstObjet>55 ) //si depasse caisse alors perso tombe
                    tmp = tmp + 50; //descend de caisse
            break;
            default:
                *posY = tmp;
        }

        movesky(ecran,posXbackground,movement,movement2,s.zero,posX,0);
        moveground(ecran,posXbackground,movement2,s.zero,posX,posiY);
        image(ecran,posX,*posY,buf);
        SDL_Flip(ecran);
        SDL_Delay(50);
    }

}

void movesky(SDL_Surface *ecran,long posXbackground,int *movement,int *movement2,int speed,int posX,int posY)
{
    Image sky;
    int DstObjet = DistanceObjectFromPerso(*movement2,posX);

    if(DstObjet !=70 || posY <250)
        *movement = (*movement -speed)%(-2*heightWindows); //ciel se déplace en arrière
    sky.x = *movement;
    sky.y = 0;
    image(ecran,sky.x,sky.y,"Pictures/ciel.bmp");
    image(ecran,((2*heightWindows)+sky.x),sky.y,"Pictures/ciel.bmp");
}

void moveground(SDL_Surface *ecran,long posXbackground,int *movement,int speed, int posX,int posY)
{
    Image ground;
    int DstObjet = DistanceObjectFromPerso(*movement,posX);
    if(DstObjet !=70 || posY <250) //si il est a moins de 90px de la boite ou qu'il saute
    {
        *movement = (*movement -speed)%(-2*heightWindows); //Fait deplacer le ciel en arrière
    }
    ground.x = *movement;
    ground.y = 400;
    image(ecran,ground.x,ground.y,"Pictures/sol.bmp");
    image(ecran,((2*heightWindows)+ground.x),ground.y,"Pictures/sol.bmp");
    //image(ecran,(heightWindows+ground.x),360,"box.bmp"); //faire générateur de boite
    generateObject(ecran,(heightWindows+ground.x),widthWindows-ground.y);

}

void generateObject(SDL_Surface *ecran,long posX,int widthGround)
{
    //Simuler une chance/nbmaxPixel de générer une forme
    Image tree;
    tree.x = 140;
    tree.y = 230;

    //int chanceOf = rand()%100;

    image(ecran,posX+100,widthWindows-tree.y-widthGround,"Pictures/tree.bmp");

    image(ecran,posX,350,"Pictures/box.bmp");
}

void moveperso(SDL_Surface *ecran,long posX, long *posY,int *step,int *movement)
{
    if(heightWindows+*movement-posX==-40) //si depasse caisse alors perso tombe
        *posY=*posY+50; //50 : hauteur de la caisse
    switch(*step)
    {
        case 1:
            image(ecran,posX,*posY,"Pictures/persoStep1.bmp");
            *step = (*step %4) +1;
            break;
        case 2:
            image(ecran,posX,*posY,"Pictures/persoStep2.bmp");
            *step = (*step %4)+1;
            break;
        case 3:
            image(ecran,posX,*posY,"Pictures/persoStep3.bmp");
            *step = (*step %4)+1;
            break;
        case 4:
            image(ecran,posX,*posY,"Pictures/persoStep4.bmp");
            *step = (*step %4)+1;
            break;
    }
}

void walkPersonage(SDL_Surface *ecran,long posX, long posY, long posXbackground)
{

    SDL_Event event;
    int continuer = 1;
    int step = 1;
    int saut = 1;
    int movement = posXbackground;
    int movement2 = posXbackground;
    Speed speed;
    SDL_EnableKeyRepeat(10, 100);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT: // Flèche droite

                        movesky(ecran,posXbackground,&movement,&movement2,speed.veryLow,posX,posY);
                        moveground(ecran,posXbackground,&movement2,speed.medium,posX,posY); //10 = vitesse deplacement
                        moveperso(ecran,posX,&posY,&step,&movement2);
                    break;

                    case SDLK_SPACE: //saut du personnage

                        movesky(ecran,posXbackground,&movement,&movement2,speed.low,posX,posY);
                        moveground(ecran,posXbackground,&movement2,speed.veryHigh,posX,posY);
                        //affiche decort ciel + arbre + caisse + ... affiche toute l'image
                        sautperso(ecran,posXbackground,posX,&posY,posY,&movement2,&movement);
                    break;


                }
            break;
        }
        SDL_Flip(ecran);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    SDL_Surface *ecran = NULL, *texte = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Rect position;
    Mix_Music *musique;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); //demerage de la SDL
    SDL_WM_SetCaption("SDL_Mixer", NULL);

    
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
      printf("%s", Mix_GetError());
    }

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }


    ecran = SDL_SetVideoMode(heightWindows, widthWindows, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("IO Game", NULL); //titre fenetre

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 100, 100)); //couleur de fenetre gris


    long const x = (heightWindows/2-50);
    long const y = (widthWindows/2-218);
    musique = Mix_LoadMUS("Songs/ioSong.mp3");
    image(ecran,0,400,"Pictures/sol.bmp");
    image(ecran,0,0,"Pictures/ciel.bmp");
    image(ecran,(640/2-50),(480-218),"Pictures/persoArret.bmp");
	Mix_PlayMusic(musique, -1); //jouer infiniment la musique
    walkPersonage(ecran,(640/2-50),(480-218),0);
    SDL_Flip(ecran); /* Mise à jour de l'écran avec sa nouvelle couleur */
    pause(); //mise en pause du programme
    Mix_FreeMusic(musique);
    Mix_CloseAudio(); //Fermeture de l'API
    SDL_Quit(); //Arret de la sdl

    return EXIT_SUCCESS;

}

