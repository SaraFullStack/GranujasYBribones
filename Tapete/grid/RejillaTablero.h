// proyecto: Grupal/Tapete
// archivo:  RejillaTablero.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    /* 
     * \class RejillaTablero
     * \brief Gestiona la rejilla hexagonal del tablero y el marcado de celdas.
     *
     * Proporciona utilidades para calcular posiciones y vértices de hexágonos, localizar celdas a partir de coordenadas,
     * y marcar/desmarcar celdas con distintos colores y grosores. Permite la gestión visual y lógica de la rejilla
     * sobre la que se desarrolla el juego.
     */
    class RejillaTablero {
    public:
        /*!
         * \brief Lado de cada hexágono en píxeles.
         */
        static constexpr int   ladoHexagono  = 20;
        /*!
         * \brief Seno de 60 grados (aproximado y exacto).
         */
        static constexpr float seno60        = 0.85f;
        static constexpr float seno60_exacto = 0.866f;
        /*!
         * \brief Distancia entre centros de celdas.
         */
        static constexpr float distanciaCeldas = ladoHexagono * seno60 * 2;
        /*!
         * \brief Número de filas de la rejilla.
         */
        static constexpr int filas    = 51;
        /*!
         * \brief Número de columnas de la rejilla.
         */
        static constexpr int columnas = 49;


        /*!
         * \brief Calcula el centro de un hexágono dado su coordenada.
         * \param centro Coordenada central.
         * \return Vector con la posición del centro.
         */
        static Vector centroHexagono(Coord centro);

        /*!
         * \brief Calcula el vértice de un hexágono dado su centro y el "minuto" (0-5).
         * \param centro Coordenada central.
         * \param minuto Índice del vértice (0-5).
         * \return Vector con la posición del vértice.
         */
        static Vector verticeHexagono(Coord centro, int minuto);

        /*!
         * \brief Localiza la celda más cercana a un punto dado.
         * \param punto Punto de referencia.
         * \param localizada Coordenada de la celda localizada (salida).
         */
        void localizaCelda(Vector punto, Coord &localizada);

        /*!
         * \brief Marca una celda con un color.
         * \param posicion Coordenada de la celda.
         * \param color Color de marcado.
         */
        void marcaCelda(Coord posicion, Color color);

        /*!
         * \brief Marca una celda con un color y grosor.
         * \param posicion Coordenada de la celda.
         * \param color Color de marcado.
         * \param grueso Si el marcado es grueso.
         */
        void marcaCelda(Coord posicion, Color color, bool grueso);

        /*!
         * \brief Desmarca una celda.
         * \param posicion Coordenada de la celda.
         */
        void desmarcaCelda(Coord posicion);

        /*!
         * \brief Desmarca todas las celdas.
         */
        void desmarcaCeldas();

    private:
        /*!
         * \brief Número de puntos para dibujar un hexágono.
         */
        static constexpr int puntosHexagono = 7;

        /*!
         * \brief Puntero al actor del tablero asociado.
         */
        ActorTablero *actor_tablero;

        /*!
         * \brief Trazos gráficos de la rejilla.
         */
        unir2d::Trazos *trazos_rejilla{};

        /*!
         * \struct MarcajeCelda
         * \brief Estructura para almacenar información de marcado de celdas.
         */
        struct MarcajeCelda {
            Coord posicion;
            Color color;
            bool  grueso;
        };
        /*!
         * \brief Vector de celdas marcadas.
         */
        std::vector<MarcajeCelda> marcaje_celdas{};

        /*!
         * \brief Trazos gráficos para el marcado.
         */
        unir2d::Trazos *trazos_marcaje{};
        /*!
         * \brief Indica si los trazos de marcado han cambiado.
         */
        bool cambio_trazos_marcaje{};


        /*!
         * \brief Constructor explícito, solo accesible por clases amigas.
         * \param actor_tablero Puntero al actor del tablero.
         */
        explicit RejillaTablero(ActorTablero *actor_tablero);

        /*!
         * \brief Destructor.
         */
        ~RejillaTablero();

        /*!
         * \brief Prepara la rejilla para su uso.
         */
        void prepara();

        /*!
         * \brief Libera los recursos de la rejilla.
         */
        void libera();

        /*!
         * \brief Busca una celda marcada en el vector de marcaje.
         * \param posicion Coordenada de la celda.
         * \return Iterador al elemento encontrado o marcaje_celdas.end().
         */
        std::vector<MarcajeCelda>::iterator buscaMarcaCelda(Coord posicion);

        /*!
         * \brief Refresca el marcado de celdas en pantalla.
         */
        void refrescaMarcaje();

        /*!
         * \brief Traza un hexágono en pantalla según el marcaje.
         * \param marcaje Información de marcado de la celda.
         */
        void trazaHexagono(const MarcajeCelda &marcaje);


        friend class ActorTablero;
        friend class PresenciaTablero;

    };


}

