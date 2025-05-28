// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoLibreDoble.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    /// <summary>Gestiona los estados de juego en modalidad libre doble, extendiendo EstadoJuegoComun.</summary>
    class EstadoJuegoLibreDoble : public EstadoJuegoComun
    {
    public:
        /// <summary>Código de estado que marca el inicio de una ronda.</summary>
        static constexpr int inicioRonda = finalPartida + 1;

        /// <summary>Código que marca el inicio de un turno cuando no se ha elegido personaje.</summary>
        static constexpr int inicioTurnoNoElegido = finalPartida + 2;
        /// <summary>Código que marca el inicio de la confirmación de turno.</summary>
        static constexpr int inicioTurnoConfirmacion = finalPartida + 3;

        /// <summary>Código que indica que se han agotado los puntos de acción.</summary>
        static constexpr int agotadosPuntosAccion = finalPartida + 4;

        /// <summary>Constructor que inicializa el estado con un código específico.</summary>
        EstadoJuegoLibreDoble(int codigo);

        /// <summary>Realiza la transición de este estado al estado destino en modalidad libre doble.</summary>
        /// <param name="destino">Estado destino para la transición.</param>
        void transita(const EstadoJuegoLibreDoble &destino);

    private:
        /// <summary>Valida que la transición al estado destino sea permitida.</summary>
        /// <param name="destino">Estado común destino a validar.</param>
        void valida(const EstadoJuegoComun &destino) override;

        /// <summary>Obtiene el nombre textual del estado para logging.</summary>
        /// <returns>Nombre del estado.</returns>
        const std::string nombre() const override;
    };

}
