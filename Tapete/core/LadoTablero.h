// proyecto: Grupal/Tapete
// archivo:  LadoTablero.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{
    enum class LadoTablero
    {
        /* \brief Representa el lado izquierdo. */
        Izquierda,
        /* \brief Representa el lado derecho. */
        Derecha,
        /* \brief Valor nulo o indefinido. */
        nulo
    };

    /*
     * \brief Devuelve el lado opuesto dado uno válido.
     * \param lado Lado actual del tablero (no debe ser nulo).
     * \return El lado contrario (Izquierda ↔ Derecha).
     */
    inline LadoTablero opuesto(LadoTablero lado)
    {
        assert(lado != LadoTablero::nulo);
        if (lado == LadoTablero::Izquierda)
        {
            return LadoTablero::Derecha;
        }
        else
        {
            return LadoTablero::Izquierda;
        }
    }
}
