// proyecto: Grupal/Tapete
// archivo:  ActorPersonaje.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class JuegoMesaBase;

    enum class ModoAccionPersonaje
    {
        Nulo,
        Desplazamiento,
        Habilidad
    };

    class ActorPersonaje : public unir2d::ActorBase
    {
    public:
        /*!
         * \brief Constructor.
         * \param juego Contexto del juego.
         * \param lado_tablero Lado del tablero (Izquierda/Derecha).
         * \param indice_en_equipo Índice del personaje en su equipo.
         * \param nombre Nombre del personaje.
         */
        explicit ActorPersonaje(
            JuegoMesaBase *juego,
            LadoTablero lado_tablero,
            int indice_en_equipo,
            const wstring &nombre);

        /*!
         * \brief Destructor.
         */
        ~ActorPersonaje();

        /*! \brief Obtiene el contexto de juego.
         *  \return Puntero al contexto de juego.
         */
        JuegoMesaBase *juego();

        /*! \brief Obtiene el lado del tablero.
         *  \return LadoTablero del personaje.
         */
        LadoTablero ladoTablero() const;

        /*! \brief Obtiene el índice en el equipo.
         *  \return Índice en el equipo.
         */
        int indiceEnEquipo() const;

        /*! \brief Obtiene el nombre del personaje.
         *  \return Nombre del personaje.
         */
        const wstring &nombre() const;

        /*! \brief Obtiene la ruta al retrato.
         *  \return Ruta del archivo de retrato.
         */
        const string &archivoRetrato() const;

        /*!
         * \brief Asigna la ruta al retrato.
         * \param valor Ruta del archivo de imagen.
         */
        void ponArchivoRetrato(const string &valor);

        /*! \brief Obtiene la ruta a la ficha.
         *  \return Ruta del archivo de ficha.
         */
        const string &archivoFicha() const;

        /*!
         * \brief Asigna la ruta de la ficha.
         * \param valor Ruta del archivo de imagen.
         */
        void ponArchivoFicha(const string &valor);

        /*!
         * \brief Comprueba si el tipo de ataque está registrado.
         * \param tipo_ataque Tipo de ataque.
         * \return true si está registrado, false en caso contrario.
         */
        bool apareceAtaque(TipoAtaque *tipo_ataque) const;

        /*!
         * \brief Obtiene el valor de ataque base.
         * \param tipo_ataque Tipo de ataque.
         * \return Valor de ataque base.
         */
        int valorAtaque(TipoAtaque *tipo_ataque) const;

        /*!
         * \brief Registra un tipo de ataque con valor base.
         * \param tipo_ataque Tipo de ataque.
         * \param valor_base Valor inicial.
         */
        void agregaAtaque(TipoAtaque *tipo_ataque, int valor_base);

        /*!
         * \brief Cambia el valor de ataque.
         * \param tipo_ataque Tipo de ataque.
         * \param valor_cambio Incremento o decremento.
         */
        void cambiaAtaque(TipoAtaque *tipo_ataque, int valor_cambio);

        /*!
         * \brief Restaura el ataque a su valor inicial.
         * \param tipo_ataque Tipo de ataque.
         */
        void restauraAtaque(TipoAtaque *tipo_ataque);

        /*!
         * \brief Comprueba si el tipo de defensa está registrado.
         * \param tipo_ataque Tipo de defensa.
         * \return true si está registrado, false en caso contrario.
         */
        bool apareceDefensa(TipoDefensa *tipo_ataque) const;

        /*!
         * \brief Obtiene el valor de defensa base.
         * \param tipo_ataque Tipo de defensa.
         * \return Valor de defensa base.
         */
        int valorDefensa(TipoDefensa *tipo_ataque) const;

        /*!
         * \brief Registra un tipo de defensa con valor base.
         * \param tipo_defensa Tipo de defensa.
         * \param valor_base Valor inicial.
         */
        void agregaDefensa(TipoDefensa *tipo_defensa, int valor_base);

        /*!
         * \brief Cambia el valor de defensa.
         * \param tipo_defensa Tipo de defensa.
         * \param valor_cambio Incremento o decremento.
         */
        void cambiaDefensa(TipoDefensa *tipo_defensa, int valor_cambio);

        /*!
         * \brief Restaura defensa a su valor inicial.
         * \param tipo_defensa Tipo de defensa.
         */
        void restauraDefensa(TipoDefensa *tipo_defensa);

        /*!
         * \brief Comprueba si el tipo de reducción de daño está registrado.
         * \param tipo_dano Tipo de daño.
         * \return true si está registrado, false en caso contrario.
         */
        bool apareceReduceDano(TipoDano *tipo_dano) const;

        /*!
         * \brief Obtiene el valor de reducción de daño.
         * \param tipo_dano Tipo de daño.
         * \return Valor de reducción de daño.
         */
        int valorReduceDano(TipoDano *tipo_dano) const;

        /*!
         * \brief Registra reducción de daño.
         * \param tipo_dano Tipo de daño.
         * \param valor Valor de reducción.
         */
        void agregaReduceDano(TipoDano *tipo_dano, int valor);

        /*!
         * \brief Obtiene la lista de habilidades.
         * \return Referencia constante al vector de habilidades.
         */
        static constexpr int maximoHabilidades = 10;
        const std::vector<Habilidad *> &habilidades() const;

        /*!
         * \brief Añade una habilidad al personaje.
         * \param elemento Puntero a la habilidad.
         */
        void agregaHabilidad(Habilidad *elemento);

        /*!
         * \brief Obtiene el índice interno.
         * \return Índice interno.
         */
        int indice();

        /*!
         * \brief Asigna el índice interno.
         * \param valor Nuevo índice.
         */
        void ponIndice(int valor);

        /*!
         * \brief Accede a la presencia gráfica del personaje.
         * \return Referencia a la presencia gráfica.
         */
        PresenciaPersonaje &presencia();

        /*!
         * \brief Obtiene la posición de la ficha.
         * \return Coordenada de la ficha.
         */
        Coord sitioFicha() const;

        /*!
         * \brief Asigna la posición de la ficha.
         * \param valor Nueva coordenada.
         */
        void ponSitioFicha(Coord valor);

        /*!
         * \brief Obtiene la vitalidad actual.
         * \return Vitalidad actual.
         */
        static constexpr int maximaVitalidad = 100;
        int vitalidad() const;

        /*!
         * \brief Asigna la vitalidad.
         * \param valor Nueva vitalidad.
         */
        void ponVitalidad(int valor);

        /*!
         * \brief Obtiene los puntos de acción.
         * \return Puntos de acción.
         */
        static constexpr int maximoPuntosAccion = 20;
        int puntosAccion() const;

        /*!
         * \brief Asigna puntos de acción.
         * \param valor Nuevo valor.
         */
        void ponPuntosAccion(int valor);

        /*!
         * \brief Obtiene iniciativa del personaje.
         * \return Iniciativa.
         */
        int iniciativa() const;

        /*!
         * \brief Asigna iniciativa.
         * \param valor Nuevo valor.
         */
        void ponIniciativa(int valor);

        /*!
         * \brief Obtiene estado de utilizable.
         * \return Estado de utilizable.
         */
        int utilizable() const;

        /*!
         * \brief Asigna estado de utilizable.
         * \param valor Nuevo valor.
         */
        void ponUtilizable(int valor);

        /*!
         * \brief Obtiene puntos de acción restantes en turno.
         * \return Puntos de acción restantes.
         */
        int puntosAccionEnJuego() const;

        /*!
         * \brief Asigna puntos de acción restantes.
         * \param valor Nuevo valor.
         */
        void ponPuntosAccionEnJuego(int valor);

        /*!
         * \brief Obtiene ruta del archivo SFX de personaje.
         * \return Ruta del archivo SFX.
         */
        const string &archivoPersonajeSFX();

        /*!
         * \brief Obtiene volumen del SFX de personaje.
         * \return Volumen.
         */
        int volumenPersonajeSFX();

        /*!
         * \brief Asigna SFX de personaje y volumen.
         * \param archivo_establece Ruta del archivo SFX.
         * \param volumen Volumen.
         */
        void asignaPersonajeSFX(const string &archivo_establece, int volumen);

        /*!
         * \brief Emite SFX de personaje.
         */
        void emitePersonajeSFX();

        /*!
         * \brief Obtiene ruta del SFX de selección.
         * \return Ruta del archivo SFX.
         */
        const string &archivoSeleccionSFX();

        /*!
         * \brief Obtiene volumen del SFX de selección.
         * \return Volumen.
         */
        int volumenSeleccionSFX();

        /*!
         * \brief Asigna SFX de selección y volumen.
         * \param archivo_establece Ruta del archivo SFX.
         * \param volumen Volumen.
         */
        void asignaSeleccionSFX(const string &archivo_establece, int volumen);

        /*!
         * \brief Emite SFX de selección.
         */
        void emiteSeleccionSFX();

        /*!
         * \brief Obtiene ruta del SFX de desplazamiento.
         * \return Ruta del archivo SFX.
         */
        const string &archivoDesplazamientoSFX();

        /*!
         * \brief Obtiene volumen de desplazamiento.
         * \return Volumen.
         */
        int volumenDesplazamientoSFX();

        /*!
         * \brief Asigna SFX de desplazamiento y volumen.
         * \param archivo_establece Ruta del archivo SFX.
         * \param volumen Volumen.
         */
        void asignaDesplazamientoSFX(const string &archivo_establece, int volumen);

        /*!
         * \brief Emite SFX de desplazamiento.
         */
        void emiteDesplazamientoSFX();

    protected:
        /*!
         * \brief Inicializa el actor.
         */
        void inicia() override;

        /*!
         * \brief Finaliza el actor.
         */
        void termina() override;

        /*!
         * \brief Actualiza el actor cada fotograma.
         * \param tiempo_seg Tiempo en segundos.
         */
        void actualiza(double tiempo_seg) override;

    private:
        string archivo_personaje_sfx{};
        int volumen_personaje_sfx{};

        string archivo_seleccion_sfx{};
        int volumen_seleccion_sfx{};

        string archivo_desplazamiento_sfx{};
        int volumen_desplazamiento_sfx{};

        JuegoMesaBase *juego_{};

        LadoTablero lado_tablero{};
        int indice_en_equipo{};
        wstring nombre_;

        string archivo_retrato{};
        string archivo_ficha{};

        struct Multivalor
        {
            int inicial;
            int cambio;
        };
        std::map<TipoAtaque *, Multivalor> valores_tipo_ataque{};
        std::map<TipoDefensa *, Multivalor> valores_tipo_defensa{};
        std::map<TipoDano *, int> valores_tipo_reduce_dano{};

        std::vector<Habilidad *> lista_habilidades{};

        int indice_;

        Coord sitio_ficha{};

        int puntos_accion{};
        int vitalidad_{};
        int iniciativa_{};
        int utilizable_{};
        int ataque_{};
        int defensa_{};
        int reduccion_dano{};

        int puntos_accion_en_juego{};

        PresenciaPersonaje presencia_personaje{this};

        bool esta_sobre_ficha{false};

        /*!
         * \brief Refresca la representación de la ficha.
         */
        void refrescaFicha();

        /*!
         * \brief Gestiona la pulsación sobre el personaje.
         */
        void controlPersonajePulsacion();

        /*!
         * \brief Gestiona el hover sobre la ficha.
         */
        void controlSobreFicha();

        /*!
         * \brief Gestiona la pulsación sobre la ficha.
         */
        void controlFichaPulsacion();

        /*!
         * \brief Comprueba una condición y lanza excepción si es falsa.
         * \param expresion Expresión a evaluar.
         * \param mensaje Mensaje de error.
         */
        static void aserta(bool expresion, const string &mensaje);

        friend class CalculoCaminos;
        friend class PresenciaPersonaje;
    };

}