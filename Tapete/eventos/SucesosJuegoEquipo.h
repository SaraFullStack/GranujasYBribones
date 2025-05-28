// proyecto: Grupal/Tapete
// archivo   SucesosJuegoEquipo.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class ModoJuegoEquipo;
    class JuegoMesa;


    /* 
     * \class SucesosJuegoEquipo
     * \brief Gestiona los eventos y sucesos específicos para el modo de juego por equipos.
     *
     * Hereda de SucesosJuegoComun y redefine los eventos clave como inicio, pulsación de espacio y escape,
     * permitiendo implementar la lógica particular de interacción y control para partidas por equipos.
     */
    class SucesosJuegoEquipo : public SucesosJuegoComun {
    public:
        /*!
         * \brief Constructor que inicializa el sistema de sucesos para el modo de equipos.
         * \param juego Puntero al contexto del juego.
         * \param proceso Puntero al modo de juego por equipos.
         */
        explicit SucesosJuegoEquipo(JuegoMesaBase *juego, ModoJuegoEquipo *proceso);

    private:
        /*!
         * \brief Devuelve el puntero al modo de juego por equipos.
         * \return Puntero a ModoJuegoEquipo.
         */
        ModoJuegoEquipo *modo();

        /*!
         * \brief Evento llamado al iniciar el sistema de sucesos.
         */
        void iniciado() override;

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

