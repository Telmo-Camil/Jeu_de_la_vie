
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../headers/StrategieRegles.hpp"

class Cellule
{
public:
    bool vivante;

    Cellule() : vivante(false) {}
    explicit Cellule(bool v) : vivante(v) {}
};

class Grille
{
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<Cellule>> cellules;
    StrategieRegles *regles;

public:
    Grille(int l, int h)
        : largeur(l), hauteur(h),
          cellules(h, std::vector<Cellule>(l, Cellule(false))),
          regles(nullptr) {}

    ~Grille() {}

    bool chargerDepuisFichier(const std::string &chemin)
    {
        std::ifstream fichier(chemin);
        if (!fichier.is_open())
        {
            return false;
        }

        std::string ligne;
        int y = 0;

        while (std::getline(fichier, ligne) && y < hauteur)
        {
            for (int x = 0; x < largeur && x < ligne.length(); x++)
            {
                cellules[y][x].vivante = (ligne[x] == '1' || ligne[x] == 'O' || ligne[x] == '*');
            }
            y++;
        }

        fichier.close();
        return true;
    }

    int obtenirVoisinsVivants(int x, int y) const
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
                    if (cellules[ny][nx].vivante)
                        count++;
                }
            }
        }
        return count;
    }

    void mettreAJour()
    {
        if (regles == nullptr)
        {
            return;
        }

        std::vector<std::vector<Cellule>> nouvelleGrille = cellules;

        for (int y = 0; y < hauteur; y++)
        {
            for (int x = 0; x < largeur; x++)
            {
                int voisins = obtenirVoisinsVivants(x, y);
                bool estVivante = cellules[y][x].vivante;

                if (estVivante)
                {
                    nouvelleGrille[y][x].vivante =
                        regles->celluleVivanteDoitResterVivante(voisins);
                }
                else
                {
                    nouvelleGrille[y][x].vivante =
                        regles->nouvelleCelluleDoitNaitre(voisins);
                }
            }
        }

        cellules = nouvelleGrille;
    }

    void afficherConsole() const
    {
        for (int y = 0; y < hauteur; y++)
        {
            for (int x = 0; x < largeur; x++)
            {
                std::cout << (cellules[y][x].vivante ? "■ " : "· ");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void sauvegarderDansFichier(std::ostream &sortie) const
    {
        for (int y = 0; y < hauteur; y++)
        {
            for (int x = 0; x < largeur; x++)
            {
                sortie << (cellules[y][x].vivante ? '1' : '0');
            }
            sortie << std::endl;
        }
    }

    void setRegles(StrategieRegles *r)
    {
        regles = r;
    }

    StrategieRegles *getRegles() const
    {
        return regles;
    }

    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }

    bool getCellule(int x, int y) const
    {
        if (x >= 0 && x < largeur && y >= 0 && y < hauteur)
        {
            return cellules[y][x].vivante;
        }
        return false;
    }

    void setCellule(int x, int y, bool etat)
    {
        if (x >= 0 && x < largeur && y >= 0 && y < hauteur)
        {
            cellules[y][x].vivante = etat;
        }
    }
};
