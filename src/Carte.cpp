
/**
 * @file carte.cpp
 * @authors KORTAM Nirmine, SEYE Fatou,
 *          MILO SOULARD, LIAM SMALL
 * @date 28/11/2024
 * @brief Programme pour la  carte.
 * @details ouverture de fichier contenant les parcelles ,
 * affichage des parcelles
 *sauvegarde de la carte dans un fichier
 */


#include "Carte.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

/**  Constructeur par défaut*/
Carte::Carte() : surfaceTotale(0.0f) {}

/** Constructeur qui charge les parcelles depuis un fichier*/
Carte::Carte(const std::string& filename) : surfaceTotale(0.0f) {
    lireDepuisFichier(filename);
}

/**  Méthode pour ajouter une parcelle à la carte */
void Carte::ajouterParcelle(Parcelle* parcelle) {
    parcelles.push_back(parcelle);
    surfaceTotale += parcelle->getSurface();
}

/**  Calcul de la surface totale de la carte */
float Carte::calculerSurfaceTotale() const {
    return surfaceTotale;
}

void Carte::lireDepuisFichier(const std::string& filename) {
    std::ifstream fichier(filename);
    if (!fichier.is_open()) {
        throw std::runtime_error("Erreur lors de l'ouverture du fichier: " + filename);
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::istringstream iss(ligne);
        std::string typeParcelle, proprietaire;
        int numero;
        iss >> typeParcelle >> numero >> proprietaire;

        /**  Lecture des points formant la parcelle */
        std::getline(fichier, ligne);  /** Lire la ligne des points */

        std::vector<Point2D<int>> points;
        if (!ligne.empty()) {
            std::istringstream pointsStream(ligne);

            char ignoreChar;
            int x, y;
            while (pointsStream >> ignoreChar >> x >> ignoreChar >> y >> ignoreChar) {  
                // ignoreChar lit et ignore les crochets '[' et ';'
                points.emplace_back(x, y);
            }
        }

        if (points.empty()) {
            continue;
        }

        Polygone<int> forme(points); /** Créer la forme du polygone */

        /** Déterminer le type de la parcelle et la créer */
        Parcelle* parcelle = nullptr;
        if (typeParcelle == "ZA") {
            std::string typeCulture;
            fichier >> typeCulture;
            parcelle = new ZA(numero, proprietaire, forme, typeCulture);
        } else if (typeParcelle == "ZAU") {
            int pConstructible;
            fichier >> pConstructible;
            parcelle = new ZAU(numero, proprietaire, forme, pConstructible);
        } else if (typeParcelle == "ZU") {
            int pConstructible;
            float surfaceConstruite;
            fichier >> pConstructible >> surfaceConstruite;
            parcelle = new ZoneUrbaine(numero, proprietaire, forme, pConstructible, surfaceConstruite);
        } else if (typeParcelle == "ZN") {
            parcelle = new ZN(numero, proprietaire, forme);
        }

        if (parcelle) {
            ajouterParcelle(parcelle);
        }
    }

    fichier.close();
}


void Carte::sauvegarderDansFichier(const std::string& filename) const {
    std::ofstream fichier(filename);
    if (!fichier) {
        throw std::runtime_error("Erreur lors de l'ouverture du fichier pour la sauvegarde");
    }

    for (const auto& parcelle : parcelles) {
        fichier << "Parcelle n°" << parcelle->getNumero() << " :\n";
        fichier << "Type : " << parcelle->getType() << "\n";
        fichier << "Polygone : " << parcelle->getForme() << "\n";
        fichier << "Propriétaire : " << parcelle->getProprietaire() << "\n";
        fichier << "Surface : " << parcelle->getSurface() << "\n";

        // Vérification du type de parcelle pour ajouter les attributs spécifiques
        if (auto* zu = dynamic_cast<ZoneUrbaine*>(parcelle)) {
            fichier << "Surface construite : " << zu->getSurfaceConstruite() << "\n";
            fichier << "Surface à construire restante : " << zu->surfaceConstructible() << "\n";
        } 
        else if (auto* zau = dynamic_cast<ZAU*>(parcelle)) {
            fichier << "% constructible : " << zau->surfaceConstructible() * 100 << " %\n";
        } 
        else if (auto* za = dynamic_cast<ZA*>(parcelle)) {
            fichier << "Type culture : " << za->get_type_culture() << "\n";
        }

        fichier << "\n"; // Séparation entre les parcelles pour plus de lisibilité
    }

    fichier.close();
}

/** Afficher la carte avec toutes ses parcelles */
void Carte::afficherCarte() const {
    for (const auto& parcelle : parcelles) {
        std::cout << *parcelle << std::endl;
    }
}

/**  Destructeur pour libérer la mémoire allouée pour les objets Parcelle */
Carte::~Carte() {
    for (auto parcelle : parcelles) {
        delete parcelle;
    }
}
