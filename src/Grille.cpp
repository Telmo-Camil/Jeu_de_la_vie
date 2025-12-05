#include "Grille.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../headers/StrategieRegles.hpp"



Grille::Grille(int l, int h)
    : largeur(l), hauteur(h), regles(nullptr)
{
    cellules.resize(hauteur, std::vector<Cellule*>(largeur));

    for (int y = 0; y < hauteur; y++)
        for (int x = 0; x < largeur; x++)
        {
            cellules[y][x] = new Cellule();
            cellules[y][x]->setEtat(new EtatMort());
        }
}

Grille::~Grille()
{
    for (int y = 0; y < hauteur; y++)
        for (int x = 0; x < largeur; x++)
            delete cellules[y][x];
}

bool Grille::chargerDepuisFichier(const std::string &chemin)
{
    std::ifstream fichier(chemin);
    if (!fichier.is_open())
        return false;

    int h, l;
    fichier >> h >> l;

    if (h != hauteur || l != largeur)
        return false;

    for (int y = 0; y < hauteur; y++)
    {
        for (int x = 0; x < largeur; x++)
        {
            int val;
            fichier >> val;

            if (val == 1)
                cellules[y][x]->setEtat(new EtatVivant());
            else
                cellules[y][x]->setEtat(new EtatMort());
        }
    }

    return true;
}

int Grille::obtenirVoisinsVivants(int x, int y) const
{
    int count = 0;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur)
            {
                if (cellules[ny][nx]->estVivante())
                    count++;
            }
        }
    }

    return count;
}

void Grille::mettreAJour()
{
    if (!regles)
        return;

    std::vector<std::vector<Cellule*>> nouvelleGrille(hauteur, std::vector<Cellule*>(largeur, nullptr));

    for (int y = 0; y < hauteur; y++)
    {
        for (int x = 0; x < largeur; x++)
        {
            int voisins = obtenirVoisinsVivants(x, y);
            Cellule* ancienne = cellules[y][x];

            bool vivante = ancienne->estVivante();

            bool nouvelleVie =
                vivante ? regles->celluleVivanteDoitResterVivante(voisins)
                        : regles->nouvelleCelluleDoitNaitre(voisins);

            nouvelleGrille[y][x] = new Cellule();
            nouvelleGrille[y][x]->setEtat(nouvelleVie ? 
                (EtatCellule*) new EtatVivant() : 
                (EtatCellule*) new EtatMort());
        }
    }

    // libérer ancienne grille
    for (int y = 0; y < hauteur; y++)
        for (int x = 0; x < largeur; x++)
            delete cellules[y][x];

    cellules = nouvelleGrille;
}

void Grille::afficherConsole() const
{
    for (int y = 0; y < hauteur; y++)
    {
        for (int x = 0; x < largeur; x++)
        {
            std::cout << (cellules[y][x]->estVivante() ? "■ " : "· ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grille::sauvegarderDansFichier(std::ostream &sortie) const
{
    sortie << hauteur << " " << largeur << "\n";

    for (int y = 0; y < hauteur; y++)
    {
        for (int x = 0; x < largeur; x++)
        {
            sortie << (cellules[y][x]->estVivante() ? '1' : '0') << " ";
        }
        sortie << "\n";
    }
}

void Grille::setRegles(StrategieRegles *r)
{
    regles = r;
}

StrategieRegles *Grille::getRegles() const
{
    return regles;
}

int Grille::getLargeur() const { return largeur; }
int Grille::getHauteur() const { return hauteur; }

bool Grille::getCellule(int x, int y) const
{
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur)
        return cellules[y][x]->estVivante();
    return false;
}

void Grille::setCellule(int x, int y, bool etat)
{
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur)
    {
        cellules[y][x]->setEtat(etat ? 
            (EtatCellule*) new EtatVivant() : 
            (EtatCellule*) new EtatMort());
    }
}
