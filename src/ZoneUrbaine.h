
/**
 * @file ZoneUrbaine.h
 * @authors KORTAM Nirmine, SEYE Fatou,
 *          MILO SOULARD, LIAM SMALL
 * @date 28/11/2024
 * @brief Création de la classe ZoneUrbaine avec ses fonctions.
 */
 #ifndef ZONEURBAINE_H
#define ZONEURBAINE_H

#include "ZoneConstructible.h"

class ZoneUrbaine : public ZoneConstructible {
private:
    float surfaceRestante;  /**  Surface encore constructible */

public:
    ZoneUrbaine();  /** Constructeur par défaut */
    ZoneUrbaine(int num, std::string prop, Polygone<int> forme, float surfaceConstruite);
    ZoneUrbaine(int num, std::string prop, Polygone<int> forme, float surfaceConstruite, float surfaceRestante);

    /** Redéfinition de la méthode pour calculer la surface constructible restante */
    float surfaceConstructible() override;

    /** Getter et Setter */
    float getSurfaceRestante() const;
    void setSurfaceRestante(float surface);
    virtual float getSurfaceConstruite() const;

    /** Surcharge opérateur >> pour afficher  */
    friend std::ostream& operator<<(std::ostream& os, const ZoneUrbaine& zu) {
        os << "Numero: " << zu.getNumero() << "\n"
           << "Type: " << zu.getType() << "\n"
           << "" << zu.getForme() << "\n"
           << "Proprietaire: " << zu.getProprietaire() << "\n"
           << "Surface: " << zu.getSurface() << "\n"
           << "Surface construite: " << zu.getSurfaceConstruite() << "\n"
           << "Surface constructible restante: " << zu.getSurfaceRestante() << "\n";
        return os;
    }
};

#endif // ZONEURBAINE_H