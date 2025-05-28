// proyecto: Grupal/Tapete
// archivo   SucesosJuegoLibreDoble.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class ModoJuegoLibreDoble;
    class JuegoMesa;


    /* 
     * \class SucesosJuegoLibreDoble
     * \brief Gestiona los eventos y sucesos específicos para el modo de juego libre doble.
     *
     * Hereda de SucesosJuegoComun y redefine eventos clave como inicio, selección de personaje, actuante,
     * habilidad, y pulsaciones de espacio y escape, permitiendo implementar la lógica particular de interacción
     * y control para partidas en modalidad libre doble.
     */
    class SucesosJuegoLibreDoble : public SucesosJuegoComun {
    public:
        /*!
         * \brief Constructor que inicializa el sistema de sucesos para el modo libre doble.
         * \param juego Puntero al contexto del juego.
         * \param proceso Puntero al modo de juego libre doble.
         */
        explicit SucesosJuegoLibreDoble(JuegoMesaBase *juego, ModoJuegoLibreDoble *proceso);

    private:
        /*!
         * \brief Devuelve el puntero al modo de juego libre doble.
         * \return Puntero a ModoJuegoLibreDoble.
         */
        ModoJuegoLibreDoble *modo();

        /*!
         * \brief Evento llamado al iniciar el sistema de sucesos.
         */
        void iniciado() override;

        /*!
         * \brief Evento cuando se selecciona un personaje.
         * \param personaje Puntero al personaje seleccionado.
         */
        void personajeSeleccionado(ActorPersonaje *personaje) override;

        /*!
         * \brief Evento cuando se selecciona un actuante.
         * \param lado Lado del tablero.
         */
        void actuanteSeleccionado(LadoTablero lado) override;

        /*!
         * \brief Evento cuando se selecciona una habilidad.
         * \param lado Lado del tablero.
         * \param indice_habilidad Índice de la habilidad seleccionada.
         */
        void habilidadSeleccionada(LadoTablero lado, int indice_habilidad) override;

        /*!
         * \brief Evento cuando se pulsa la barra espaciadora.
         */
        void pulsadoEspacio() override;

        /*!
         * \brief Evento cuando se pulsa la tecla Escape.
         */
        void pulsadoEscape() override;
    };


}

