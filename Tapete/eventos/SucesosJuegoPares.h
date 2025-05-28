// proyecto: Grupal/Tapete
// archivo   SucesosJuegoPares.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class ModoJuegoPares;
    class JuegoMesa;


    /* 
     * \class SucesosJuegoPares
     * \brief Gestiona los eventos y sucesos específicos para el modo de juego por pares.
     *
     * Hereda de SucesosJuegoComun y redefine eventos clave como inicio, selección de personaje,
     * y pulsaciones de espacio y escape, permitiendo implementar la lógica particular de interacción
     * y control para partidas en modalidad de pares.
     */
    class SucesosJuegoPares : public SucesosJuegoComun {
    public:
        /*!
         * \brief Constructor que inicializa el sistema de sucesos para el modo de pares.
         * \param juego Puntero al contexto del juego.
         * \param proceso Puntero al modo de juego por pares.
         */
        explicit SucesosJuegoPares(JuegoMesaBase *juego, ModoJuegoPares *proceso);

    private:
        /*!
         * \brief Devuelve el puntero al modo de juego por pares.
         * \return Puntero a ModoJuegoPares.
         */
        ModoJuegoPares *modo();

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
         * \brief Evento cuando se pulsa la barra espaciadora.
         */
        void pulsadoEspacio() override;

        /*!
         * \brief Evento cuando se pulsa la tecla Escape.
         */
        void pulsadoEscape() override;
    };


}
