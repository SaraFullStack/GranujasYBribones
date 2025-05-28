// proyecto: Grupal/Tapete
// archivo:  CuadroIndica.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class ActorTablero;


    /* 
     * \class CuadroIndica
     * \brief Gestiona el cuadro de indicación visual sobre el tablero.
     *
     * Permite mostrar y ocultar mensajes o indicaciones en una posición concreta del tablero,
     * gestionando los recursos gráficos asociados (rectángulo, trazos y texto) y su ciclo de vida.
     * Utilizado para resaltar información contextual al usuario durante la partida.
     */
    class CuadroIndica {
    public:
        /*!
         * \brief Prepara los recursos gráficos del cuadro de indicación.
         */
        void prepara();

        /*!
         * \brief Libera los recursos gráficos del cuadro de indicación.
         */
        void libera();

        /*!
         * \brief Muestra el cuadro de indicación en una posición con un texto dado.
         * \param poscn Posición en coordenadas del tablero.
         * \param cadena Texto a mostrar.
         */
        void indica(Vector poscn, const wstring &cadena);

        /*!
         * \brief Oculta el cuadro de indicación.
         */
        void desindica();

    private:
        /*!
         * \brief Color por defecto del cuadro de indicación.
         */
        static constexpr Color colorIndica {239, 228, 176, 255};

        /*!
         * \brief Puntero al actor del tablero asociado.
         */
        ActorTablero *actor_tablero;

        /*!
         * \brief Puntero al rectángulo gráfico del cuadro de indicación.
         */
        unir2d::Rectangulo *rectangl_indica{};

        /*!
         * \brief Puntero a los trazos gráficos del cuadro de indicación.
         */
        unir2d::Trazos *trazos_indica{};

        /*!
         * \brief Puntero al texto gráfico del cuadro de indicación.
         */
        unir2d::Texto *texto_indica{};

        /*!
         * \brief Constructor explícito, solo accesible por clases amigas.
         * \param actor_tablero Puntero al actor del tablero.
         */
        explicit CuadroIndica(ActorTablero *actor_tablero);

        /*!
         * \brief Destructor.
         */
        ~CuadroIndica();


        friend class ActorTablero;

    };


}


