#include <iostream>
#include <cassert>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
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
    applesEaten = 0;
    currentMap = 1;
    dirSnake = DROITE;
    loadMap(currentMap, dirSnake);
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
            applesEaten++;
            if (applesEaten == 5)
            {
                createPortal();
            }
            snake.push_front(posTest);
            terrain[posTest.y*largeur+posTest.x]=VIDE;
            ajoutPomme();
            score+=10;
        } else if (terrain[posTest.y*largeur+posTest.x]==PORTAL)
        {
            nextLevel();
        } else {
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
            } else if (terrain[posTest.y*largeur+posTest.x]==CADEAU) {
                snake.push_front(posTest);
                snake.push_front(posTest);
                terrain[posTest.y*largeur+posTest.x] = VIDE;

                score += 20;

                cadTimer=0;
                pTimer=30;
                // ajout le cadeau et quand le serphent mangage le cadeau sa score va +20 et aussi sa longeur +2 unitée,et dermarrer la pause=30*0.15=4.5s

            } else{
                //Game over
                QMessageBox msgBox;
                msgBox.setWindowTitle("Information");
                msgBox.setText("Game Over. Do you want to continue?");
                msgBox.setIcon(QMessageBox::Question);
                QPushButton *yes_button = msgBox.addButton("Yes", QMessageBox::YesRole);
                QPushButton *no_button = msgBox.addButton("No", QMessageBox::NoRole);

                msgBox.exec();

                QPushButton *clickedButton = qobject_cast<QPushButton *>(msgBox.clickedButton());

                if (clickedButton == yes_button) {
                    init();
                } else {
                    exit(0);
                }
            }
        }
    }
    Position poscad=getCadeau();
    if (poscad.x!=-1 && poscad.y!=-1)
    {
        // si la cadeau apparait sur la terrain
        if (cadTimer>0) {
            cadTimer--;
            if (cadTimer==0) {
                for (int y=0;y<hauteur;y++) {
                    for (int x=0; x<largeur;x++) {
                        if (terrain[y*largeur +x] == CADEAU) {
                            terrain[y*largeur +x] = VIDE;
                        }
                    }
                }
            }
        }

        pTimer=50; // atteindre 50*0.15=7.5s
    }
    else if (pTimer>0){
        pTimer--;
        if (pTimer<=0) {
            ajoutCadeau();
            cadTimer=30;// le cadeau va appraret en 30*0.15=4.5s

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
    else
        return false;
}

void Jeu::setDirection(Direction dir)
{
    dirSnake = dir;
}
Direction Jeu::getDirection()
{
    return dirSnake;
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

Position Jeu::getCadeau(){
    Position posCad;

    posCad.x=-1;// position d'initilisation du cadeau
    posCad.y=-1;
    for (int y=0; y<hauteur; y++)
        for (int x=0; x<largeur; x++)
            if (terrain[y*largeur+x]==CADEAU)
            {
                posCad.x = x;
                posCad.y = y;
            }
    return posCad;
}


void Jeu::ajoutCadeau() {
    Position posCad;
    //Trouve un Cadeau
    do {
        posCad.x=rand() %largeur;
        posCad.y=rand() %hauteur;
    }while (!posValide(posCad));
    terrain[posCad.y*largeur+posCad.x]=CADEAU;
}

int Jeu::getcadTimer() const {
    return static_cast<int>(cadTimer);//temps en seconds  mais  * temps per evelue()=0.15s
}

int Jeu::getScore() const
{
    return score;
}

Position Jeu::getPortal()
{
    Position posPortal;
    posPortal.x = -1;
    posPortal.y = -1;

    for (int y=0; y<hauteur; y++)
        for (int x=0; x<largeur; x++)
            if (terrain[y*largeur+x]==PORTAL)
            {
                posPortal.x = x;
                posPortal.y = y;
            }
    return posPortal;
}

void Jeu::loadMap(int mapNumber, Direction direction)
{
    int x, y;
    const char *terrain_defaut;
    //set direction
    dirSnake = direction;
    switch (mapNumber)
    {
        case 1:
            terrain_defaut =
                "####..##############"
                "#........##........#"
                "#.#####..##...####.#"
                "#........##........#"
                "#..................#"
                "#..................#"
                "...................."
                "...................."
                "...................."
                "...................."
                "#..................#"
                "#..................#"
                "#.....#......#.....#"
                "#.....#......#.....#"
                "####..##############";
            break;
        case 2:
            terrain_defaut =
                "...................."
                "...##..........##..."
                "....##........##...."
                ".....##......##....."
                "......##....##......"
                ".......##..##......."
                "........####........"
                "...................."
                "........####........"
                ".......##..##......."
                "......##....##......"
                ".....##......##....."
                "....##........##...."
                "...##..........##..."
                "....................";
            break;
        case 3:
            terrain_defaut =
                "...................."
                "...####......####..."
                "...####......####..."
                "...####......####..."
                "...................."
                "...................."
                "...................."
                "...................."
                "...................."
                "...................."
                "...................."
                "...####......####..."
                "...####......####..."
                "...####......####..."
                "....................";
            break;
        default:
            return;
    }

    largeur = 20;
    hauteur = 15;

    if (terrain != nullptr)
        delete[] terrain;

    terrain = new Case[largeur * hauteur];

    for (y = 0; y < hauteur; ++y)
        for (x = 0; x < largeur; ++x)
            if (terrain_defaut[y * largeur + x] == '#')
                terrain[y * largeur + x] = MUR;
            else
                terrain[y * largeur + x] = VIDE;

    int longueurSerpent = 5;
    snake.clear();
    ajoutPomme();
    Position posTete;
    posTete.x = 15;
    posTete.y = 8;
    for (int i = 0; i < longueurSerpent; i++)
    {
        snake.push_back(posTete);
        posTete.x--;
    }
}

void Jeu::createPortal()
{
    Position posPortal;
    bool found = false;
    int attempts = 0;

    while (!found && attempts < 100) { // Giới hạn số lần thử
        posPortal.x = rand() % largeur;
        posPortal.y = rand() % hauteur;
        if (posValide(posPortal)) {
            found = true;
        }
        attempts++;
    }

    if (found) {
        terrain[posPortal.y * largeur + posPortal.x] = PORTAL;
        qDebug() << "Portal created at (" << posPortal.x << "," << posPortal.y << ")";
    } else {
        qDebug() << "Failed to create portal!";
    }
}


void Jeu::nextLevel()
{
    currentMap++;
    loadMap(currentMap, DROITE);
    applesEaten = 0;
}
