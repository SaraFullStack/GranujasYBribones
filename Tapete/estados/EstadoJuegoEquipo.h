// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoEquipo.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class EstadoJuegoEquipo : public EstadoJuegoComun
    {
    public:
        /*!
         * \brief Código de estado que marca el inicio de una ronda.
         */
        static constexpr int inicioRonda = finalPartida + 1;

        /*!
         * \brief Código de estado que marca el inicio de un turno.
         */
        static constexpr int inicioTurno = finalPartida + 2;

        /*!
         * \brief Constructor que inicializa el estado con un código específico.
         * \param codigo Código de estado.
         */
        EstadoJuegoEquipo(int codigo);

        /*!
         * \brief Realiza la transición de este estado al estado destino.
         * \param destino Estado de equipo al cual transitar.
         */
        void transita(const EstadoJuegoEquipo &destino);

    private:
        /*!
         * \brief Valida que la transición al estado destino sea permitida.
         * \param destino Estado común destino a validar.
         */
        void valida(const EstadoJuegoComun &destino) override;

        /*!
         * \brief Obtiene el nombre textual del estado para logging.
         * \return Nombre del estado.
         */
        const string nombre() const override;
    };

}
