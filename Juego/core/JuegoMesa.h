/**
 * @file JuegoMesa.h
 * @brief Proyecto grupal de juego de mesa.
 * @version 2.1 (Abril-2025)
 */
#pragma once

namespace juego
{

    /**
     * @class JuegoMesa
     * @brief Orquesta toda la configuración y puesta en marcha de la partida.
     *
     * Implementa el patrón Template Method definido en JuegoMesaBase para
     * configurar tablero, personajes, habilidades, estadísticas, sistema de ataque
     * y lógica de recolección de tesoros.
     */
    class JuegoMesa : public JuegoMesaBase
    {
    public:
        /**
         * @brief Constructor.
         *
         * Inicializa el modo de juego (Pares) y el sistema de sucesos correspondientes.
         */
        JuegoMesa();

        /**
         * @brief Evento post-movimiento de un personaje.
         *
         * Comprueba si el @p personaje ha recogido un tesoro tras moverse.
         * @param personaje Puntero al ActorPersonaje que acaba de moverse.
         */
        void despuesDeMover(ActorPersonaje *personaje) override;

    private:
        //---------------------------------------------------------------------
        /**
         * @name Sección IV-2: Personajes
         * Declaración de punteros a los seis personajes del juego.
         * Edward, Balthazar, Buenavida: bando izquierdo.
         * Victoria, Luciana, Dorian: bando derecho.
         */
        //@{
        ActorPersonaje *Edward{};       /**< Puntero a Edward. */
        ActorPersonaje *Balthazar{};    /**< Puntero a Balthazar. */
        ActorPersonaje *Buenavida{};    /**< Puntero a Buenavida. */
        ActorPersonaje *Victoria{};     /**< Puntero a Victoria. */
        ActorPersonaje *Luciana{};      /**< Puntero a Luciana. */
        ActorPersonaje *Dorian{};       /**< Puntero a Dorian. */
        //@}

        /**
         * @brief Número de tesoros a colocar en el tablero.
         */
        static constexpr int NUM_TESOROS = 10;

        /**
         * @brief Coordenadas fijas de los tesoros en el tablero.
         */
        Coord posiciones[NUM_TESOROS] = {
            Coord{3, 13},
            Coord{3, 33},
            Coord{5, 43},
            Coord{10, 30},
            Coord{25, 15},
            Coord{26, 24},
            Coord{25, 33},
            Coord{40, 24},
            Coord{45, 15},
            Coord{45, 33}};

        /**
         * @brief Array de punteros a los objetos recolectables (tesoros).
         */
        ActorObjetoRecolectable *tesoros[NUM_TESOROS] = {nullptr};

        //---------------------------------------------------------------------
        /**
         * @name Sección V-1: Habilidades
         * Declaración de punteros a las instancias de Habilidad.
         */
        //@{
        Habilidad *canionazo{};           /**< Habilidad Cañonazo. */
        Habilidad *embestida{};           /**< Habilidad Embestida. */
        Habilidad *abordaje{};            /**< Habilidad Abordaje. */
        Habilidad *reparacionBarco{};     /**< Habilidad Reparación de barco. */
        Habilidad *sangradoMortal{};      /**< Habilidad Sangrado mortal. */
        Habilidad *oleadaMetralla{};      /**< Habilidad Oleada de metralla. */
        Habilidad *golpeDevastador{};     /**< Habilidad Golpes devastadores. */
        Habilidad *punoCorsario{};        /**< Habilidad Puño del Corsario. */
        Habilidad *tornado{};              /**< Habilidad Efecto tornado. */
        Habilidad *golpeAncla{};           /**< Habilidad Golpe de ancla. */
        //@}

        //---------------------------------------------------------------------
        /**
         * @name Sección VI-1: Tipos de estadísticas
         * Punteros a los tipos de ataque, defensa y daño.
         */
        //@{
        TipoAtaque *ataqueCuerpoACuerpo{}; /**< Tipo: ataque cuerpo a cuerpo. */
        TipoAtaque *ataqueADistancia{};    /**< Tipo: ataque a distancia. */
        TipoDefensa *defensaCuerpoACuerpo{};/**< Tipo: defensa cuerpo a cuerpo. */
        TipoDefensa *defensaADistancia{};   /**< Tipo: defensa a distancia. */
        TipoDano *danoFisico{};             /**< Tipo: daño físico. */
        GradoEfectividad *fallo{};          /**< Grado de efectividad: fallo. */
        GradoEfectividad *roce{};           /**< Grado de efectividad: roce. */
        GradoEfectividad *impacto{};        /**< Grado de efectividad: impacto. */
        GradoEfectividad *critico{};        /**< Grado de efectividad: crítico. */
        //@}

    private:
        /**
         * @brief Rutas base de recursos: activos, retratos, habilidades y sonidos.
         */
        static string carpeta_activos_juego;
        static string carpeta_retratos_juego;
        static string carpeta_habilides_juego;
        static string carpeta_sonidos_juego;

        //---------------------------------------------------------------------
        /**
         * @name Métodos de configuración (Template Method)
         */
        //@{
        /**
         * @brief Obtiene el título de la ventana del juego.
         * @return Título como std::wstring.
         */
        const std::wstring tituloVentana() const override;

        /**
         * @brief Configura el tablero: fondo, equipo y muros aleatorios.
         */
        void preparaTablero() override;

        /**
         * @brief Instancia y configura los personajes del juego.
         */
        void preparaPersonajes() override;

        /**
         * @brief Instancia y registra las habilidades disponibles.
         */
        void preparaHabilidades() override;

        /**
         * @brief Crea y añade los tipos de ataque, defensa y daño.
         */
        void preparaTiposEstadisticas() override;

        /**
         * @brief Vincula habilidades a los personajes.
         */
        void agregaHabilidadesPersonajes() override;

        /**
         * @brief Define estadísticas (coste, alcance, daño) de cada habilidad.
         */
        void agregaEstadisticasHabilidades() override;

        /**
         * @brief Asigna estadísticas base a cada personaje.
         */
        void agregaEstadisticasPersonajes() override;

        /**
         * @brief Configura el sistema de ataque (rangos de efectividad).
         */
        void preparaSistemaAtaque() override;

        /**
         * @brief Ajusta posiciones, puntos de acción, sonidos, música y créditos.
         */
        void configuraJuego() override;

        /**
         * @brief Verifica si un personaje recolecta un tesoro tras moverse.
         * @param personaje Puntero al ActorPersonaje en movimiento.
         */
        void verificaRecoleccion(ActorPersonaje *personaje);

        /**
         * @brief Limpia recursos y resetea punteros al terminar la partida.
         */
        void termina() override;
        //@}
    };

} // namespace juego
