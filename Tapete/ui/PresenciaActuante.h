// proyecto: Grupal/Tapete
// archivo:  PresenciaActuante.h
// versión:  2.1  (Abril-2025)


#pragma once

namespace tapete
{

    /**
     * @brief Gestiona la visualización del personaje activo y sus indicadores en la HUD.
     *
     * Muestra u oculta el retrato, barras de vida, puntos de acción y habilidades,
     * así como marcas y luces indicadoras.
     */
    class PresenciaActuante
    {
    public:
        /**
         * @brief Muestra el panel del personaje activo.
         * @param personaje Puntero al personaje a mostrar.
         */
        void muestra(ActorPersonaje *personaje);

        /**
         * @brief Oculta el panel del personaje activamente mostrado.
         */
        void oculta();

        /**
         * @brief Comprueba si el panel está visible.
         * @return true si está visible, false en caso contrario.
         */
        bool visible();

        /**
         * @brief Obtiene el personaje actualmente mostrado.
         * @return Puntero al personaje mostrado.
         */
        ActorPersonaje *personaje();

        /**
         * @brief Marca visualmente el retrato del personaje.
         */
        void marcaRetrato();

        /**
         * @brief Marca la habilidad seleccionada.
         * @param indice Índice de la habilidad a marcar.
         */
        void marcaHabilidad(int indice);

        /**
         * @brief Quita marcas de retrato y habilidades.
         */
        void desmarcaRetratoHabilidad();

        /**
         * @brief Ilumina los puntos de acción.
         * @param actuales Puntos de acción actuales.
         * @param en_juego Puntos de acción totales en turno.
         */
        void iluminaPuntosAccion(int actuales, int en_juego);

        /**
         * @brief Refresca la barra de vida según el estado actual.
         */
        void refrescaBarraVida();

    private:
        static constexpr int cuentaPuntosAccion = ActorPersonaje::maximoPuntosAccion; ///< Número máximo de puntos de acción
        static constexpr int cuentaHabilidades = ActorPersonaje::maximoHabilidades;   ///< Número máximo de habilidades
        static constexpr int cuentaBarrasVida = 21;                                   ///< Pasos en la barra de vida

        ActorTablero *actor_tablero; ///< Puntero al actor de tablero para coordinaciones
        LadoTablero lado_tablero;    ///< Lado (bando) del tablero de este actuante

        Region panel_abajo;                                      ///< Región inferior de HUD
        Region panel_retrato;                                    ///< Región del retrato del personaje
        std::array<Region, cuentaHabilidades> paneles_habilidad; ///< Regiones de paneles de habilidades

        inline static unir2d::Textura *textura_marco_personaje{}; ///< Textura marco de retrato
        unir2d::Imagen *imagen_marco_personaje{};                 ///< Imagen del marco de retrato

        inline static unir2d::Textura *textura_marco_habilidad{};                 ///< Textura de marco de habilidad
        std::array<unir2d::Imagen *, cuentaHabilidades> imagen_marco_habilidad{}; ///< Imágenes de marcos de habilidades

        inline static unir2d::Textura *textura_luces_punto_accion{};                  ///< Textura de luces de PA
        std::array<unir2d::Imagen *, cuentaPuntosAccion> imagen_luces_punto_accion{}; ///< Luz por cada PA

        inline static unir2d::Textura *textura_barras_vida{}; ///< Textura de barra de vida
        unir2d::Imagen *imagen_barra_vida{};                  ///< Imagen actual de barra de vida

        inline static unir2d::Textura *textura_marca{};                           ///< Textura para marcar retrato y habilidades
        unir2d::Imagen *imagen_marca_retrato{};                                   ///< Imagen de marca sobre retrato
        std::array<unir2d::Imagen *, cuentaHabilidades> imagen_marca_habilidad{}; ///< Imágenes de marcas de habilidades

        bool visible_{};                      ///< Estado de visibilidad actual
        ActorPersonaje *personaje_mostrado{}; ///< Personaje que se está mostrando

        /**
         * @brief Constructor privado para inicializar con actor y bando.
         * @param actor_tablero Puntero al actor del tablero asociado.
         * @param lado_tablero  Lado del tablero del actuante.
         */
        explicit PresenciaActuante(ActorTablero *actor_tablero, LadoTablero lado_tablero);

        /**
         * @brief Destructor libera todos los recursos asociados.
         */
        ~PresenciaActuante();

        /**
         * @brief Prepara recursos gráficos e inicializa estados.
         */
        void prepara();

        /**
         * @brief Libera recursos gráficos e imágenes.
         */
        void libera();

        /**
         * @brief Configura las regiones de paneles.
         */
        void preparaPaneles();

        /**
         * @brief Carga y posiciona el retrato del personaje.
         */
        void preparaPersonaje();

        /**
         * @brief Prepara las imágenes de habilidades.
         */
        void preparaHabilidades();

        /**
         * @brief Genera las luces para puntos de acción.
         */
        void preparaPuntosAccion();

        /**
         * @brief Configura la barra de vida con sus divisiones.
         */
        void preparaBarraVida();

        /**
         * @brief Inicializa las imágenes de marca para retrato y habilidades.
         */
        void preparaMarcas();

        /**
         * @brief Calcula el índice de la barra de vida según vida restante.
         * @return Índice de la imagen en la textura de vida.
         */
        int indiceBarraVida();

        /**
         * @brief Aserta una condición lanzando std::logic_error en fallo.
         * @param expresion Condición que debe ser verdadera.
         * @param mensaje  Mensaje de error si la aserción falla.
         */
        static void aserta(bool expresion, const std::string &mensaje);

        friend class ActorTablero; ///< ActorTablero puede crear y destruir instancias
    };

} // namespace tapete
