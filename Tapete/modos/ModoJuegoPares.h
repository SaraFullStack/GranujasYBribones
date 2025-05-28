// proyecto: Grupal/Tapete
// archivo   ModoJuegoPares.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class JuegoMesa;


    /* 
     * \class ModoJuegoPares
     * \brief Implementa la lógica del modo de juego por pares, derivando de ModoJuegoComun.
     *
     * Gestiona el estado específico de la modalidad por pares, la entrada en partida, la elección y movimiento de personajes,
     * la asunción de habilidades, el control de personajes agotados y la reinicialización de turnos. Permite la validación
     * y depuración de atributos y estados propios de la modalidad por pares.
     */
    class ModoJuegoPares : public ModoJuegoComun {
    public:
        /*!
         * \brief Constructor que inicializa el modo de juego por pares con el juego asociado.
         * \param juego Puntero al juego.
         */
        explicit ModoJuegoPares(JuegoMesaBase *juego);

        /*!
         * \brief Devuelve una referencia al estado actual de pares.
         * \return Referencia a EstadoJuegoPares.
         */
        EstadoJuegoPares &estado();

        /*!
         * \brief Inicia la partida en modo pares.
         */
        void entraPartida();

        /*!
         * \brief Inicia el turno de elección de personajes.
         */
        void entraTurnoEleccion();

        /*!
         * \brief Elige el primer personaje para el turno.
         * \param personaje Puntero al personaje elegido.
         */
        void eligePrimerPersonaje(ActorPersonaje *personaje);

        /*!
         * \brief Elige el segundo personaje para el turno.
         * \param personaje Puntero al personaje elegido.
         */
        void eligeSegundoPersonaje(ActorPersonaje *personaje);

        /*!
         * \brief Revierte el inicio de turno.
         */
        void revierteInicioTurno();

        /*!
         * \brief Inicia la jugada en modo pares.
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

        /*!
         * \brief Ignora el personaje agotado y continúa el flujo.
         */
        void ignoraPersonajeAgotado();

        /*!
         * \brief Reinicia el turno actual.
         */
        void reiniciaTurno();

    private:
        EstadoJuegoPares estado_;
        EstadoJuegoPares estado_previo_;

        /*!
         * \brief Asume el estado de la jugada, agotamiento o final de turno.
         * \param inicio_jugada Indica si es inicio de jugada.
         * \param ataca_agotado Indica si el personaje está agotado.
         * \param final_turno Indica si es final de turno.
         */
        void asume(
                bool &inicio_jugada,
                bool &ataca_agotado,
                bool &final_turno);

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
         * \brief Valida los atributos del modo de juego por pares.
         */
        void validaAtributos() override;

    };


}





