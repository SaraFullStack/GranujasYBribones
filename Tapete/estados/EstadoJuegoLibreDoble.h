// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoLibreDoble.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class EstadoJuegoLibreDoble : public EstadoJuegoComun
    {
    public:
        /*!
         * \brief Código de estado que marca el inicio de una ronda.
         */
        static constexpr int inicioRonda = finalPartida + 1;

        /*!
         * \brief Código que marca el inicio de un turno cuando no se ha elegido personaje.
         */
        static constexpr int inicioTurnoNoElegido = finalPartida + 2;

        /*!
         * \brief Código que marca el inicio de la confirmación de turno.
         */
        static constexpr int inicioTurnoConfirmacion = finalPartida + 3;

        /*!
         * \brief Código que indica que se han agotado los puntos de acción.
         */
        static constexpr int agotadosPuntosAccion = finalPartida + 4;

        /*!
         * \brief Constructor que inicializa el estado con un código específico.
         * \param codigo Código de estado.
         */
        EstadoJuegoLibreDoble(int codigo);

        /*!
         * \brief Realiza la transición de este estado al estado destino en modalidad libre doble.
         * \param destino Estado destino para la transición.
         */
        void transita(const EstadoJuegoLibreDoble &destino);

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
        const std::string nombre() const override;
    };

}
