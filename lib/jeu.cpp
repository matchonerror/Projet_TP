#include <iostream>
#include <cassert>
#include "jeu.hpp"

using namespace std;

Position::Position()
{
}

Position::Position(int a, int b)
{
    x=a;
    y=b;
}

bool Position::operator==(const Position &pos) const
{
    return (x==pos.x && y==pos.y);
}

bool Position::operator!=(const Position &pos) const
{
    return (x!=pos.x || y!=pos.y);
}

Jeu::Jeu()
{
    terrain = nullptr;
    largeur = 0; hauteur = 0;
    dirSnake = DROITE;
}

Jeu::Jeu(const Jeu &jeu):snake(jeu.snake)
{
    largeur = jeu.largeur;
    hauteur = jeu.hauteur;
    dirSnake = jeu.dirSnake;

    if (jeu.terrain!=nullptr)
    {
        terrain = new Case[largeur*hauteur];
        for (int c=0; c<largeur*hauteur; c++)
            terrain[c] = jeu.terrain[c];
    }
    else
        terrain = nullptr;
}

Jeu::~Jeu()
{
    if (terrain!=nullptr)
        delete[] terrain;
}

Jeu &Jeu::operator=(const Jeu &jeu)
{
    if (terrain!=nullptr)
        delete[] terrain;

    largeur = jeu.largeur;
    hauteur = jeu.hauteur;
    dirSnake = jeu.dirSnake;
    snake = jeu.snake;

    if (jeu.terrain!=nullptr)
    {
        terrain = new Case[largeur*hauteur];
        for (int c=0; c<largeur*hauteur; c++)
            terrain[c] = jeu.terrain[c];
    }
    else
        terrain = nullptr;
    return *this;
}

bool Jeu::init()
{
    int x, y;
    // list<Position>::iterator itSnake;

    const char terrain_defaut[15][21] = {
            "####..##############",
            "#........##........#",
            "#.#####..##...####.#",
            "#........##........#",
            "#..................#",
            "#..................#",
            "....................",
            "....................",
            "....................",
            "....................",
            "#..................#",
            "#..................#",
            "#.....#......#.....#",
            "#.....#......#.....#",
            "####..##############"
    };

    largeur = 20;
    hauteur = 15;

    terrain = new Case[largeur*hauteur];

    for(y=0;y<hauteur;++y)
        for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else
                terrain[y*largeur+x] = VIDE;

    int longueurSerpent = 5;
    snake.clear();
    //ajoutPomme
    ajoutPomme();
    Position posTete;
    posTete.x = 15;
    posTete.y = 8;
    for (int i=0; i<longueurSerpent; i++)
    {
        snake.push_back(posTete);
        posTete.x--;
    }

    return true;
}

void Jeu::evolue()
{
    Position posTest;
    list<Position>::iterator itSnake;

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    posTest.x = snake.front().x + depX[dirSnake];
    posTest.y = snake.front().y + depY[dirSnake];

    if (posValide(posTest))
    {
        snake.pop_back();
        snake.push_front(posTest);
    } else{
        if (terrain[posTest.y*largeur+posTest.x]==POMME){
            snake.push_front(posTest);
            terrain[posTest.y*largeur+posTest.x]=VIDE;
            ajoutPomme();
        } else{
            if (posTest.x==largeur || posTest.x==-1 || posTest.y==hauteur || posTest.y==-1){
                if (posTest.x==largeur){
                    posTest.x = 0;
                } else if (posTest.x==-1){
                    posTest.x = largeur-1;
                } else if (posTest.y==hauteur){
                    posTest.y = 0;
                } else if (posTest.y==-1){
                    posTest.y = hauteur-1;
                }
                snake.pop_back();
                snake.push_front(posTest);
            } else{
                //exit game
                cout << "Game Over" << endl;
                exit(0);
            }
        }
    }
}

int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

Case Jeu::getCase(const Position &pos) const
{
    assert(pos.x>=0 && pos.x<largeur && pos.y>=0 && pos.y<hauteur);
    return terrain[pos.y*largeur+pos.x];
}

const list<Position> &Jeu::getSnake() const
{
    return snake;
}

bool Jeu::posValide(const Position &pos) const
{
    if (pos.x>=0 && pos.x<largeur && pos.y>=0 && pos.y<hauteur
        && terrain[pos.y*largeur+pos.x]==VIDE)
    {
        list<Position>::const_iterator itSnake;
        itSnake = snake.begin();
        while (itSnake!=snake.end() && *itSnake!=pos)
            itSnake++;
        return (itSnake==snake.end());
    }
    else if (pos.x==largeur || pos.x==-1 || pos.y==hauteur || pos.y==-1)
    {

    }
    else
        return false;
}

void Jeu::setDirection(Direction dir)
{
    dirSnake = dir;
}

void Jeu::ajoutMur()
{
    Position posMur;

    // Trouve une case libre
    do {
        posMur.x = rand()%largeur;
        posMur.y = rand()%hauteur;
    } while (!posValide(posMur));
    terrain[posMur.y*largeur+posMur.x]=MUR;
}

void Jeu::suppressionMur()
{
    Position posMur;

    // Trouve un mur
    do {
        posMur.x = rand()%largeur;
        posMur.y = rand()%hauteur;
    } while (terrain[posMur.y*largeur+posMur.x]!=MUR);
    terrain[posMur.y*largeur+posMur.x]=VIDE;
}

Position Jeu::getPomme()
{
    Position posPomme;
    posPomme.x = -1;
    posPomme.y = -1;

    for (int y=0; y<hauteur; y++)
        for (int x=0; x<largeur; x++)
            if (terrain[y*largeur+x]==POMME)
            {
                posPomme.x = x;
                posPomme.y = y;
            }
    return posPomme;
}

void Jeu::ajoutPomme()
{
    Position posPomme;

    // Trouve une case libre
    do {
        posPomme.x = rand()%largeur;
        posPomme.y = rand()%hauteur;
    } while (!posValide(posPomme));
    terrain[posPomme.y*largeur+posPomme.x]=POMME;
}