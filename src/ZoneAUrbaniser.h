/**
 * @file ZoneAUrbaniser.h
 * @authors KORTAM Nirmine, SEYE Fatou,
 *          MILO SOULARD, LIAM SMALL
 * @date 28/11/2024
 * @brief Création de la classe ZoneAUrbaniser avec ses attributs et fonctions.
 */

#ifndef ZAU_H
#define ZAU_H

#include <iostream>
#include "parcelle.h"
#include "ZoneConstructible.h"

using namespace std;
class ZAU : public ZoneConstructible {
private:
    float surface_constructible;

public:

    /** Constructeur */
    ZAU(int num, std::string prop, Polygone<int> forme, float surface) ;

    /** Getter pour la surface xconstructible */
    float getSurfaceConstructible() const;

    /** Setter pour la surface constructible */
    void setSurfaceConstructible(float surface);

    /** Méthode pour obtenir la surface constructible */
    float surfaceConstructible();

    /** Surcharge de l'opérateur << pour affichage */
    friend ostream& operator<<(std::ostream& os, const ZAU& zau) {
    os << "Numero: " << zau.getNumero() << "\n"
       << "Type: " << zau.getType() << "\n"
       << "" << zau.getForme() << "\n"
       << "Proprietaire: " << zau.getProprietaire() << "\n"
       << "Surface: " << zau.getSurface() << "\n"
       << "Constructible: " << zau.getSurfaceConstructible() * 100 << " %\n";
       
    return os;
    }
};

#endif 