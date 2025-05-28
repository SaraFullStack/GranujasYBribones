// proyecto: Grupal/Tapete
// archivo:  GradoEfectividad.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete {

    class GradoEfectividad {
    public:
        // Constructor: inicializa el grado de efectividad con su nombre
        GradoEfectividad(const std::wstring &nombre);

        // estableceRango: define el rango de ataque y el porcentaje de daño asociado
        void estableceRango(int valor_ataque_inf, int valor_ataque_sup, int porciento_dano);

        // nombre: devuelve el nombre del grado de efectividad
        const std::wstring &nombre() const;

        // valorInferiorAtaque: obtiene el valor mínimo del rango de ataque
        int valorInferiorAtaque() const;
        // valorSuperiorAtaque: obtiene el valor máximo del rango de ataque
        int valorSuperiorAtaque() const;
        // porcentajeDano: obtiene el porcentaje de daño de este grado
        int porcentajeDano() const;

    private:
        // nombre interno del grado de efectividad
        std::wstring nombre_{};

        // valores del rango de ataque
        int valor_ataque_inf{};
        int valor_ataque_sup{};
        // porcentaje de daño aplicado para este rango
        int porciento_dano{};
    };

}
