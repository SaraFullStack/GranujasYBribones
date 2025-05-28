// proyecto: Grupal/Tapete
// archivo:  VistaCaminoCeldas.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    /*!
     * \class VistaCaminoCeldas
     * \brief Gestiona la visualización del camino de celdas en el tablero durante el desplazamiento de fichas.
     *
     * Permite marcar y desmarcar la celda de inicio, etapas del camino y gestionar la visualización de microdianas y trazos.
     * Facilita la depuración y el control visual del recorrido de las fichas, mostrando el avance y las etapas del camino
     * de manera interactiva y visualmente clara para el usuario.
     */
    class VistaCaminoCeldas {
    public:
        /*!
         * \brief Marca la celda de inicio del camino.
         * \param celda Coordenada de la celda de inicio.
         */
        void marcaCeldaInicio(Coord celda);

        /*!
         * \brief Desmarca la celda de inicio del camino.
         */
        void desmarcaCeldaInicio();

        /*!
         * \brief Indica si la celda de inicio está marcada.
         * \return true si está marcada, false en caso contrario.
         */
        bool celdaInicioMarcada();

        /*!
         * \brief Arranca el camino fijando la celda de inicio.
         */
        void arrancaCamino();

        /*!
         * \brief Marca una celda como etapa del camino.
         * \param celda Coordenada de la celda.
         * \param etapa_valida Indica si la etapa es válida.
         * \param origen_trazo Coordenada de origen del trazo.
         */
        void marcaCeldaEtapa(Coord celda, bool etapa_valida, Coord origen_trazo);

        /*!
         * \brief Desmarca la celda de etapa del camino.
         */
        void desmarcaCeldaEtapa();

        /*!
         * \brief Fija la celda de etapa del camino.
         */
        void fijaCeldaEtapa();

        /*!
         * \brief Vacía el camino, eliminando todas las marcas y trazos.
         */
        void vaciaCamino();

        // Métodos para depuración (no borrar)
        // int dianasVisibles();
        // int dianasFijadas();

    private:
        /*!
         * \brief Grosor del trazado del camino.
         */
        static constexpr int grosorTrazado = 5;

        /*!
         * \brief Puntero al actor del tablero asociado.
         */
        ActorTablero *actor_tablero{};

        /*!
         * \brief Textura de la microdiana utilizada para marcar celdas.
         */
        inline static unir2d::Textura *textura_mdiana{};

        /*!
         * \brief Imágenes de microdianas actualmente mostradas.
         */
        std::vector<unir2d::Imagen *> imagenes_mdiana{};

        /*!
         * \brief Número de microdianas fijadas.
         */
        int imagenes_mdiana_fijadas{};

        /*!
         * \brief Microdiana en caché para reutilización.
         */
        unir2d::Imagen *imagen_mdiana_cache{};

        /*!
         * \brief Trazos gráficos del camino.
         */
        unir2d::Trazos *trazos{};

        // Variables de control y depuración

        /*!
         * \brief Indica si la celda de inicio está marcada.
         */
        bool celda_inicio_marcada{}; // se ha marcado la celda de inicio del camino, aún no se ha fijado 

        /*!
         * \brief Indica si el camino ha arrancado (celda de inicio fijada).
         */
        bool camino_arrancado{};     // se ha fijado la celda de inicio en el camino

        /*!
         * \brief Indica si una celda de etapa está marcada.
         */
        bool celda_etapa_marcada{};  // se ha marcado una celda en el camino, distinta a la de inicio, aún no se ha fijado 

        /*!
         * \brief Indica si una celda de etapa está fijada.
         */
        bool celda_etapa_fijada{};   // se ha fijado una celda en el camino, además de la celda de inicio, no es muy útil

        /*!
         * \brief Constructor explícito, solo accesible por clases amigas.
         * \param actor_tablero Puntero al actor del tablero asociado.
         */
        explicit VistaCaminoCeldas(ActorTablero *actor_tablero);

        /*!
         * \brief Destructor.
         */
        ~VistaCaminoCeldas();

        /*!
         * \brief Prepara los recursos gráficos del camino.
         */
        void prepara();

        /*!
         * \brief Libera los recursos gráficos del camino.
         */
        void libera();

        /*!
         * \brief Agrega una microdiana a la celda indicada.
         * \param celda Coordenada de la celda.
         * \param provisional Indica si es provisional.
         * \param valida Indica si la etapa es válida.
         */
        void agregaMicrodiana(Coord celda, bool provisional, bool valida);

        /*!
         * \brief Extrae la microdiana actual.
         */
        void extraeMicrodiana();

        /*!
         * \brief Agrega un trazo al camino.
         * \param celda Coordenada de la celda.
         * \param provisional Indica si es provisional.
         * \param valida Indica si la etapa es válida.
         * \param origen Coordenada de origen del trazo.
         */
        void agregaTrazado(Coord celda, bool provisional, bool valida, Coord origen);

        /*!
         * \brief Almacena en caché la microdiana actual.
         */
        void cacheaMicrodiana();

        /*!
         * \brief Elimina la microdiana de la caché.
         * \param celda Coordenada de la celda.
         * \param provisional Indica si es provisional.
         * \param valida Indica si la etapa es válida.
         */
        void descacheaMicrodiana(Coord celda, bool provisional, bool valida);

        /*!
         * \brief Calcula la posición de la microdiana en la celda indicada.
         * \param coord Coordenada de la celda.
         * \return Vector con la posición de la microdiana.
         */
        Vector posicionMicrodiana(Coord coord);


        friend class ActorTablero;

    };


}



