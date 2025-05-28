// proyecto: Grupal/Tapete
// archivo   ModoJuegoEquipo.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class JuegoMesa;

    /* 
     * \class ModoJuegoEquipo
     * \brief Implementa la lógica del modo de juego por equipos, derivando de ModoJuegoComun.
     *
     * Gestiona el estado específico de equipo, la entrada en partida y jugada, el movimiento de fichas,
     * la asunción de habilidades y la búsqueda de jugadas válidas. Permite la validación y depuración
     * de atributos y estados propios de la modalidad por equipos.
     */
    class ModoJuegoEquipo : public ModoJuegoComun {
    public:
        /*!
         * \brief Constructor que inicializa el modo de juego por equipos con el juego asociado.
         * \param juego Puntero al juego.
         */
        explicit ModoJuegoEquipo(JuegoMesaBase *juego);

        /*!
         * \brief Devuelve una referencia al estado de equipo actual.
         * \return Referencia a EstadoJuegoEquipo.
         */
        EstadoJuegoEquipo &estado();

        /*!
         * \brief Inicia la partida en modo equipos.
         */
        void entraPartida();

        /*!
         * \brief Inicia la jugada en modo equipos.
         */
        void entraInicioJugada();

        /*!
         * \brief Realiza el movimiento de ficha.
         */
        void mueveFicha();

        /*!
         * \brief Asume la habilidad seleccionada.
         */
        void asumeHabilidad();

    private:
        EstadoJuegoEquipo estado_;
        EstadoJuegoEquipo estado_previo_;

        /*!
         * \brief Busca una jugada válida.
         * \param encontrada Referencia booleana que indica si se encontró jugada.
         */
        void buscaJugada(bool &encontrada);

        /*!
         * \brief Asume el estado de la jugada, turno, ronda o final de partida.
         * \param inicio_jugada Indica si es inicio de jugada.
         * \param inicio_turno Indica si es inicio de turno.
         * \param inicio_ronda Indica si es inicio de ronda.
         * \param final_partida Indica si es final de partida.
         */
        void asume(
            bool &inicio_jugada,
            bool &inicio_turno,
            bool &inicio_ronda,
            bool &final_partida);

        /*!
         * \brief Escribe el estado actual (para depuración).
         */
        void escribeEstado() override;

        /*!
         * \brief Devuelve el nombre del módulo para depuración.
         * \return Nombre del módulo.
         */
        const string nombreModulo() override;

        /*!
         * \brief Valida los atributos del modo de juego por equipos.
         */
        void validaAtributos() override;

    };


}

