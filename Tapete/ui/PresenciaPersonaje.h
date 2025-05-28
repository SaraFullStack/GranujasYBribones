// proyecto: Grupal/Tapete
// archivo:  PresenciaPersonaje.h
// versión:  2.1  (Abril-2025)


#pragma once

namespace tapete {

    class ActorPersonaje; ///< Declaración anticipada de la clase ActorPersonaje

    /**
     * @class PresenciaPersonaje
     * @brief Gestiona la visualización del retrato lateral, ficha circular y barra de vida del personaje.
     */
    class PresenciaPersonaje {
    public:

        /**
         * @brief Obtiene la imagen del retrato lateral.
         * @return Puntero a la imagen de retrato.
         */
        unir2d::Imagen * imagenRetrato () const;

        /**
         * @brief Obtiene la imagen de la ficha circular del personaje.
         * @return Puntero a la imagen de la ficha.
         */
        unir2d::Imagen * imagenFicha   () const;

        /**
         * @brief Muestra una etiqueta junto a la ficha del personaje.
         * @param cadena Cadena de texto wide que se mostrará.
         */
        void indicaFicha (const wstring & cadena);

        /**
         * @brief Aplica un efecto de oscurecimiento al retrato para indicar inactividad.
         */
        void oscureceRetrato ();

        /**
         * @brief Restaura el brillo original del retrato.
         */
        void aclaraRetrato ();

        /**
         * @brief Actualiza la barra de vida para reflejar la vida actual del personaje.
         */
        void refrescaBarraVida ();

    private:

        static constexpr int    radioFicha = 15;                ///< Radio del círculo que representa la ficha
        static constexpr Vector deslizaFicha {radioFicha, radioFicha}; ///< Desplazamiento para centrar la ficha en su región
        static constexpr int    cuentaBarrasVida = 21;         ///< Número de pasos discretos en la barra de vida

        ActorPersonaje * actor_personaje; ///< Personaje asociado a esta presencia

        Region panel_lateral {};          ///< Región lateral donde se dibuja el retrato y la ficha

        unir2d::Textura * textura_retrato {}; ///< Textura base para el retrato lateral

        inline static unir2d::Textura * textura_titulos {}; ///< Textura para los títulos de grupo
        unir2d::Imagen *                imagen_titulo {};   ///< Imagen que contiene el título de grupo

        unir2d::Rectangulo *            fondo_retrato {};    ///< Rectángulo de fondo tras el retrato
        unir2d::Imagen *                imagen_retrato_lateral {}; ///< Imagen del retrato lateral
        inline static unir2d::Textura * textura_marco_retrato {};   ///< Textura del marco que rodea el retrato
        unir2d::Imagen *                imagen_marco_retrato {};   ///< Imagen del marco de retrato

        unir2d::Textura *               textura_ficha {};    ///< Textura para la ficha circular
        unir2d::Imagen *                imagen_ficha {};     ///< Imagen de la ficha circular

        inline static unir2d::Textura * textura_barras_vida {}; ///< Textura para la barra de vida
        unir2d::Imagen *                imagen_barra_vida {}; ///< Imagen que muestra la barra de vida actual

        unir2d::Imagen *                imagen_retrato_actuante {}; ///< Retrato del personaje en HUD de activa

        /**
         * @brief Constructor privado, asigna el actor.
         * @param actor_personaje Puntero al personaje.
         */
        explicit PresenciaPersonaje (ActorPersonaje * actor_personaje);

        /**
         * @brief Destructor libera recursos asociados.
         */
        ~PresenciaPersonaje ();

        /**
         * @brief Carga texturas e inicializa elementos gráficos.
         */
        void prepara ();

        /**
         * @brief Libera texturas, imágenes y recursos auxiliares.
         */
        void libera ();

        /**
         * @brief Prepara la región y contenido del panel lateral según lado e índice de grupo.
         * @param lado_tablero Lado del tablero (bando).
         * @param indice_grupo Índice del grupo de personajes para el título.
         */
        void preparaPanel (LadoTablero lado_tablero, int indice_grupo);

        /**
         * @brief Ajusta el título mostrando la lista de personajes y el actual.
         * @param lista_personajes Vector con punteros a todos los personajes.
         * @param personaje_actual Puntero al personaje actualmente seleccionado.
         */
        void preparaTitulo (
                const std::vector <ActorPersonaje *> & lista_personajes, 
                ActorPersonaje *                       personaje_actual );

        /**
         * @brief Carga y posiciona el retrato lateral dentro del panel.
         */
        void preparaRetratoLateral ();

        /**
         * @brief Configura la barra de vida inicial.
         */
        void preparaBarraVida ();

        /**
         * @brief Devuelve el índice en la textura de vida para la vida actual.
         * @return Índice entero.
         */
        int  indiceBarraVida ();

        /**
         * @brief Prepara el retrato utilizado en el HUD de personaje activo.
         */
        void preparaRetratoActuante ();

        //void preparaHabilidadesActuante (ActorPersonaje * actor_personaje);

        /**
         * @brief Prepara la imagen circular de la ficha del personaje.
         */
        void preparaFicha ();

        /**
         * @brief Aserta una condición de programación y lanza error si falla.
         * @param expresion Condición esperada verdaderamente.
         * @param mensaje Mensaje de error en caso de fallo.
         */
        static void aserta (bool expresion, const string & mensaje);

        /**
         * @brief Sonido al mostrar personaje.
         */
        unir2d::Sonido *                sonido_personaje      {};
        /**
         * @brief Sonido al seleccionar personaje.
         */
        unir2d::Sonido *                sonido_seleccion      {};
        /**
         * @brief Sonido al desplazar personaje.
         */
        unir2d::Sonido *                sonido_desplazamiento {};
        inline static unir2d::Textura * textura_retrato_muerto{}; ///< Textura para retrato cuando personaje muerto
        unir2d::Imagen *                imagen_retrato_muerto {}; ///< Imagen de retrato en estado muerto

        /**
         * @brief Carga efectos de sonido (SFX).
         */
        void preparaSFX (); // cargamos los sonidos en cada puntero
        /**
         * @brief Libera los efectos de sonido cargados.
         */
        void liberaSFXs();  // para liberar los SFXs en el metodo libera()

        friend class ActorPersonaje; ///< ActorPersonaje puede crear y destruir instancias

    };

}
