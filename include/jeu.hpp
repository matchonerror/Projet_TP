#ifndef JEU_HPP
#define JEU_HPP

#include <list>

typedef enum {VIDE, MUR, POMME, PORTAL, CADEAU} Case;
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction;

class Position
{
public:
    int x, y;
    Position();
    Position(int,int);
    bool operator==(const Position &) const;
    bool operator!=(const Position &) const;
};

class Jeu
{
protected:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    std::list<Position> snake;
    Direction dirSnake;

    //gestion portal
    int applesEaten;
    int currentMap;

    //cadeau et score
    int score;
    int cadTimer;
    int pTimer;

public:
    Jeu();
    Jeu(const Jeu &);
    ~Jeu();

    Jeu &operator=(const Jeu &);

    bool init();
    void evolue();

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Retourne la case � une position donn�e
    Case getCase(const Position &) const;

    // Retourne la liste des �l�ments du serpent en lecture seule
    const std::list<Position> &getSnake() const;

    // Indique si la case � une position donn�e existe et est libre
    bool posValide(const Position &) const;

    // Modifie la direction
    void setDirection(Direction);
    //get direction
    Direction getDirection();

    void ajoutMur();
    void suppressionMur();

    Position getPomme();
    void ajoutPomme();

    //Ajout la cadeau
    Position getCadeau();
    void ajoutCadeau();

    // Retourne  la temp pour la cadeau
    int getcadTimer() const;

    //Retourn la score
    int getScore()  const;

    //gestion portal entre les niveaux
    void loadMap(int, Direction);
    void createPortal();
    Position getPortal();
    void nextLevel();
};

#endif
