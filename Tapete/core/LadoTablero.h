// proyecto: Grupal/Tapete
// archivo:  LadoTablero.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    /// <summary>Define los lados posibles del tablero.</summary>
    enum class LadoTablero
    {
        /// <summary>Representa el lado izquierdo.</summary>
        Izquierda,
        /// <summary>Representa el lado derecho.</summary>
        Derecha,
        /// <summary>Valor nulo o indefinido.</summary>
        nulo
    };

    /// <summary>Devuelve el lado opuesto dado uno válido.</summary>
    /// <param name="lado">Lado actual del tablero (no debe ser nulo).</param>
    /// <returns>El lado contrario (Izquierda ↔ Derecha).</returns>
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
