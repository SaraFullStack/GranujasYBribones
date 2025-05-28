// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoComun.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class ModoJuegoComun;

    /* 
     * \class SucesosJuegoComun
     * \brief Clase base para la gestión de eventos y sucesos comunes durante la partida.
     *
     * Define la interfaz para la gestión de eventos relacionados con la interacción de los jugadores,
     * selección y pulsación de fichas, habilidades, celdas, ayuda y control de flujo del juego.
     * Debe ser derivada para implementar la lógica específica de cada modo de juego.
     */
    class SucesosJuegoComun
    {
    public:
        /*!
         * \brief Constructor que inicializa el sistema de sucesos con el juego y el modo.
         * \param juego Puntero al contexto del juego.
         * \param proceso Puntero al modo de juego.
         */
        explicit SucesosJuegoComun(JuegoMesaBase *juego, ModoJuegoComun *proceso);

        /*!
         * \brief Destructor virtual.
         */
        virtual ~SucesosJuegoComun();

        /*!
         * \brief Devuelve el puntero al contexto del juego.
         * \return Puntero a JuegoMesaBase.
         */
        JuegoMesaBase *juego();

        /*!
         * \brief Devuelve el puntero al modo de juego.
         * \return Puntero a ModoJuegoComun.
         */
        ModoJuegoComun *modo();

        /*!
         * \brief Evento llamado al iniciar el sistema de sucesos.
         */
        virtual void iniciado() = 0;

        /*!
         * \brief Evento llamado al finalizar el sistema de sucesos.
         */
        virtual void terminado();

        /*!
         * \brief Evento al entrar en el actuante de un lado del tablero.
         * \param lado Lado del tablero.
         */
        virtual void entrandoActuante(LadoTablero lado);

        /*!
         * \brief Evento al salir del actuante de un lado del tablero.
         * \param lado Lado del tablero.
         */
        virtual void saliendoActuante(LadoTablero lado);

        /*!
         * \brief Evento al entrar en una habilidad.
         * \param lado Lado del tablero.
         * \param indice Índice de la habilidad.
         */
        virtual void entrandoHabilidad(LadoTablero lado, int indice);

        /*!
         * \brief Evento al salir de una habilidad.
         * \param lado Lado del tablero.
         * \param indice Índice de la habilidad.
         */
        virtual void saliendoHabilidad(LadoTablero lado, int indice);

        /*!
         * \brief Evento al entrar en una ficha.
         * \param personaje Puntero al personaje.
         */
        virtual void entrandoFicha(ActorPersonaje *personaje);

        /*!
         * \brief Evento al salir de una ficha.
         * \param personaje Puntero al personaje.
         */
        virtual void saliendoFicha(ActorPersonaje *personaje);

        /*!
         * \brief Evento al entrar en una celda.
         * \param celda Coordenada de la celda.
         */
        virtual void entrandoCelda(Coord celda);

        /*!
         * \brief Evento al salir de una celda.
         * \param celda Coordenada de la celda.
         */
        virtual void saliendoCelda(Coord celda);

        /*!
         * \brief Evento cuando se selecciona un personaje.
         * \param personaje Puntero al personaje.
         */
        virtual void personajeSeleccionado(ActorPersonaje *personaje);

        /*!
         * \brief Evento cuando se selecciona un actuante.
         * \param lado Lado del tablero.
         */
        virtual void actuanteSeleccionado(LadoTablero lado);

        /*!
         * \brief Evento cuando se selecciona una habilidad.
         * \param lado Lado del tablero.
         * \param indice Índice de la habilidad.
         */
        virtual void habilidadSeleccionada(LadoTablero lado, int indice);

        /*!
         * \brief Evento cuando se selecciona una ficha.
         * \param personaje Puntero al personaje.
         */
        virtual void fichaSeleccionada(ActorPersonaje *personaje);

        /*!
         * \brief Evento cuando se pulsa una ficha.
         * \param personaje Puntero al personaje.
         */
        virtual void fichaPulsada(ActorPersonaje *personaje);

        /*!
         * \brief Evento cuando se selecciona una celda.
         * \param celda Coordenada de la celda.
         */
        virtual void celdaSeleccionada(Coord celda);

        /*!
         * \brief Evento cuando se pulsa una celda.
         * \param celda Coordenada de la celda.
         */
        virtual void celdaPulsada(Coord celda);

        /*!
         * \brief Evento cuando se selecciona la ayuda.
         */
        virtual void ayudaSeleccionada();

        /*!
         * \brief Evento cuando se pulsa la barra espaciadora.
         */
        virtual void pulsadoEspacio();

        /*!
         * \brief Evento cuando se pulsa la tecla Escape.
         */
        virtual void pulsadoEscape();

        /*!
         * \brief Evento cuando se pulsa la flecha arriba.
         */
        virtual void pulsadoArriba();

        /*!
         * \brief Evento cuando se pulsa la flecha abajo.
         */
        virtual void pulsadoAbajo();

        /*!
         * \brief Evento de alarma para cálculos temporizados.
         * \param tiempo Referencia al objeto de tiempo.
         */
        virtual void alarmaCalculo(unir2d::Tiempo &tiempo);

    private:
        JuegoMesaBase *juego_{};
        ModoJuegoComun *modo_{};
    };

}
