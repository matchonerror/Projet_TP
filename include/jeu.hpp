#ifndef JEU_HPP
#define JEU_HPP

#include <list>

typedef enum {VIDE, MUR, POMME, CADEAU} Case;
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

    // Ajoute la mur
    void ajoutMur();
    void suppressionMur();

    // Ajout la pomme
    Position getPomme();
    void ajoutPomme();


    //Ajout la cadeau
    Position getCadeau();
    void ajoutCadeau();

    // Retourne  la temp pour la cadeaiu

    int getcadTimer() const;

    //Retourn la score
    int getScore()  const;
};

#endif

