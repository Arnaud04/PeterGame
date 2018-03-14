#define linelength 20
#define heightWindows 640
#define widthWindows 480

typedef struct Image Image;

struct Image
{
    int x;
    int y;
};

typedef struct Speed Speed;
struct Speed
{
    int zero = 0;
    int veryLow = 1;
    int low = 2;
    int medium = 10;
    int high = 40;
    int veryHigh = 50;
};

void pause();
void rectangle(SDL_Surface *ecran,long posX, long posY, int largeur, int hauteur, int rouge,int vert, int bleu);
void image(SDL_Surface *ecran,long posX, long posY, char name[linelength]);
void walkPersonage(SDL_Surface *ecran,long posX, long posY, long posXbackground);
void sautperso(SDL_Surface *ecran,long posXbackground,long posX, long *posY,long posiY,int *movement2,int *movement);
void movesky(SDL_Surface *ecran,long posXbackground,int *movement,int *movement2,int speed,int posX,int posY);
void moveground(SDL_Surface *ecran,long posXbackground,int *movement,int speed, int posX,int posY);
void generateObject(SDL_Surface *ecran,long posX,int widthGround);
int DistanceObjectFromPerso(int *movement,long posX);
