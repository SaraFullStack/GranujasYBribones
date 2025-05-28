// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoEquipo.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    /// <summary>Gestiona los estados de juego específicos por equipo, extendiendo EstadoJuegoComun.</summary>
    class EstadoJuegoEquipo : public EstadoJuegoComun
    {
    public:
        /// <summary>Código de estado que marca el inicio de una ronda.</summary>
        static constexpr int inicioRonda = finalPartida + 1;

        /// <summary>Código de estado que marca el inicio de un turno.</summary>
        static constexpr int inicioTurno = finalPartida + 2;

        /// <summary>Constructor que inicializa el estado con un código específico.</summary>
        EstadoJuegoEquipo(int codigo);

        /// <summary>Realiza la transición de este estado al estado destino.</summary>
        /// <param name="destino">Estado de equipo al cual transitar.</param>
        void transita(const EstadoJuegoEquipo &destino);

    private:
        /// <summary>Valida que la transición al estado destino sea permitida.</summary>
        /// <param name="destino">Estado común destino a validar.</param>
        void valida(const EstadoJuegoComun &destino) override;

        /// <summary>Obtiene el nombre textual del estado para logging.</summary>
        /// <returns>Nombre del estado.</returns>
        const string nombre() const override;
    };

}
