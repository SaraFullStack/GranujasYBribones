// proyecto: Grupal/Tapete
// archivo   ModoJuegoLibreDoble.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class JuegoMesa;

    /*
     * \class ModoJuegoLibreDoble
     * \brief Implementa la lógica del modo de juego libre doble, derivando de ModoJuegoComun.
     *
     * Gestiona el estado específico de la modalidad libre doble, la entrada en partida, la elección y movimiento de personajes,
     * la asunción de habilidades y el control de personajes agotados. Permite la validación y depuración de atributos y estados
     * propios de la modalidad libre doble.
     */
    class ModoJuegoLibreDoble : public ModoJuegoComun
    {
    public:
        /*!
         * \brief Constructor que inicializa el modo de juego libre doble con el juego asociado.
         * \param juego Puntero al juego.
         */
        explicit ModoJuegoLibreDoble(JuegoMesaBase *juego);

        /*!
         * \brief Devuelve una referencia al estado actual de libre doble.
         * \return Referencia a EstadoJuegoLibreDoble.
         */
        EstadoJuegoLibreDoble &estado();

        /*!
         * \brief Inicia la partida en modo libre doble.
         */
        void entraPartida();

        /*!
         * \brief Inicia el turno de elección de personaje.
         */
        void entraTurnoEleccion();

        /*!
         * \brief Elige un personaje para el turno.
         * \param personaje Puntero al personaje elegido.
         */
        void eligePersonaje(ActorPersonaje *personaje);

        /*!
         * \brief Revierte el inicio de turno.
         */
        void revierteInicioTurno();

        /*!
         * \brief Inicia la jugada en modo libre doble.
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

    private:
        EstadoJuegoLibreDoble estado_;
        EstadoJuegoLibreDoble estado_previo_;

        /*!
         * \brief Asume el estado de la jugada, turno, ronda o final de partida.
         * \param inicio_jugada Indica si es inicio de jugada.
         * \param ataca_agotado Indica si el personaje está agotado.
         * \param inicio_turno Indica si es inicio de turno.
         * \param inicio_ronda Indica si es inicio de ronda.
         * \param final_partida Indica si es final de partida.
         */
        void asume(
            bool &inicio_jugada,
            bool &ataca_agotado,
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
         * \brief Valida los atributos del modo de juego libre doble.
         */
        void validaAtributos() override;
    };
}
