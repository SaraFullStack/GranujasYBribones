// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoPares.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    /// <summary>Gestiona los estados de juego en modalidad de pares, extendiendo EstadoJuegoComun.</summary>
    class EstadoJuegoPares : public EstadoJuegoComun
    {
    public:
        /// <summary>Código de estado que marca el inicio de una ronda.</summary>
        static constexpr int inicioRonda = finalPartida + 1;

        /// <summary>Código que marca el inicio de turno cuando ningún jugador ha sido elegido.</summary>
        static constexpr int inicioTurnoNoElegidos = finalPartida + 2;
        /// <summary>Código que marca el inicio de turno cuando un jugador ha sido elegido.</summary>
        static constexpr int inicioTurnoElegidoUno = finalPartida + 3;
        /// <summary>Código que marca el inicio de confirmación de turno.</summary>
        static constexpr int inicioTurnoConfirmacion = finalPartida + 4;

        /// <summary>Código que indica que se han agotado los puntos de acción.</summary>
        static constexpr int agotadosPuntosAccion = finalPartida + 5;
        /// <summary>Código que marca el final del turno.</summary>
        static constexpr int finalTurno = finalPartida + 6;

        /// <summary>Constructor que inicializa el estado con un código específico.</summary>
        EstadoJuegoPares(int codigo);

        /// <summary>Realiza la transición de este estado al estado destino en modalidad de pares.</summary>
        /// <param name="destino">Estado destino para la transición.</param>
        void transita(const EstadoJuegoPares &destino);

    private:
        /// <summary>Valida que la transición al estado destino sea permitida.</summary>
        /// <param name="destino">Estado común destino a validar.</param>
        void valida(const EstadoJuegoComun &destino) override;

        /// <summary>Obtiene el nombre textual del estado para logging.</summary>
        /// <returns>Nombre del estado.</returns>
        const string nombre() const override;
    };

}
