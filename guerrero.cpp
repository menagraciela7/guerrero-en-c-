#include <iostream>
#include <string>
#include <memory>

// ============================================
// ARMA
// ============================================
class Arma {
private:
    std::string nombre;
    int danio;

public:
    Arma(const std::string& nombre, int danio) : nombre(nombre), danio(danio) {}

    void atacar() const {
        std::cout << "⚔️ Ataque con " << nombre << ": " << danio << " puntos de danio\n";
    }

    int getDanio() const { return danio; }
    std::string getNombre() const { return nombre; }
};

// ============================================
// HABILIDAD
// ============================================
class Habilidad {
private:
    std::string nombre;
    int poder;

public:
    Habilidad(const std::string& nombre, int poder) : nombre(nombre), poder(poder) {}

    void usar() const {
        std::cout << "✨ Se utiliza " << nombre << ": " << poder << " puntos de poder\n";
    }

    std::string getNombre() const { return nombre; }
};

// ============================================
// PERSONAJE
// ============================================
class Personaje {
private:
    std::string nombre;
    int vida;
    std::shared_ptr<Arma> arma;             // Composición mediante punteros inteligentes
    std::shared_ptr<Habilidad> habilidad;

public:
    Personaje(const std::string& nombre, int vida, std::shared_ptr<Arma> arma, std::shared_ptr<Habilidad> habilidad)
        : nombre(nombre), vida(vida), arma(arma), habilidad(habilidad) {}

    void atacar() const {
        std::cout << nombre << " ataca:\n";
        arma->atacar(); // Se usa "->" para acceder a los métodos del puntero
    }

    void usarHabilidad() const {
        std::cout << nombre << " utiliza una habilidad:\n";
        habilidad->usar();
    }

    void cambiarArma(std::shared_ptr<Arma> nuevaArma) {
        arma = nuevaArma;
        std::cout << nombre << " ahora utiliza " << nuevaArma->getNombre() << "\n";
    }

    void recibirDanio(int danio) {
        vida -= danio;
        std::cout << nombre << " recibio " << danio << " puntos de danio.\n";
        std::cout << "Vida restante: " << vida << "\n";
    }
};

// ============================================
// EJECUCIÓN PRINCIPAL
// ============================================
int main() {
    // Creamos armas usando std::make_shared
    auto espada = std::make_shared<Arma>("Espada de fuego", 30);
    auto arco = std::make_shared<Arma>("Arco magico", 20);

    // Creamos habilidades
    auto curacion = std::make_shared<Habilidad>("Curacion", 25);
    auto escudo = std::make_shared<Habilidad>("Escudo magico", 15);

    // ============================================
    // COMPOSICIÓN & JUEGO (Guerrero)
    // ============================================
    Personaje guerrero("Guerrero", 100, espada, curacion);

    guerrero.atacar();
    guerrero.usarHabilidad();
    guerrero.recibirDanio(20);

    // CAMBIAMOS EL ARMA
    guerrero.cambiarArma(arco);
    guerrero.atacar();

    // ============================================
    // CREAMOS OTRO PERSONAJE (Arquero)
    // ============================================
    Personaje arquero("Arquero", 80, arco, escudo);
    arquero.atacar();
    arquero.usarHabilidad();

    return 0;
}
