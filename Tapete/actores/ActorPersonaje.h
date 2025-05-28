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
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="juego">Contexto del juego.</param>
        /// <param name="lado_tablero">Lado del tablero (Izquierda/Derecha).</param>
        /// <param name="indice_en_equipo">Índice del personaje en su equipo.</param>
        /// <param name="nombre">Nombre del personaje.</param>
        explicit ActorPersonaje(
            JuegoMesaBase *juego,
            LadoTablero lado_tablero,
            int indice_en_equipo,
            const wstring &nombre);

        /// <summary>
        /// Destructor.
        /// </summary>
        ~ActorPersonaje();

        /// <summary>Obtiene el contexto de juego.</summary>
        JuegoMesaBase *juego();

        /// <summary>Obtiene el lado del tablero.</summary>
        LadoTablero ladoTablero() const;

        /// <summary>Obtiene el índice en el equipo.</summary>
        int indiceEnEquipo() const;

        /// <summary>Obtiene el nombre del personaje.</summary>
        const wstring &nombre() const;

        /// <summary>Obtiene la ruta al retrato.</summary>
        const string &archivoRetrato() const;
        /// <summary>Asigna la ruta al retrato.</summary>
        /// <param name="valor">Ruta del archivo de imagen.</param>
        void ponArchivoRetrato(const string &valor);

        /// <summary>Obtiene la ruta a la ficha.</summary>
        const string &archivoFicha() const;
        /// <summary>Asigna la ruta de la ficha.</summary>
        /// <param name="valor">Ruta del archivo de imagen.</param>
        void ponArchivoFicha(const string &valor);

        /// <summary>Comprueba si el tipo de ataque está registrado.</summary>
        /// <param name="tipo_ataque">Tipo de ataque.</param>
        bool apareceAtaque(TipoAtaque *tipo_ataque) const;
        /// <summary>Obtiene el valor de ataque base.</summary>
        /// <param name="tipo_ataque">Tipo de ataque.</param>
        int valorAtaque(TipoAtaque *tipo_ataque) const;
        /// <summary>Registra un tipo de ataque con valor base.</summary>
        /// <param name="tipo_ataque">Tipo de ataque.</param>
        /// <param name="valor_base">Valor inicial.</param>
        void agregaAtaque(TipoAtaque *tipo_ataque, int valor_base);
        /// <summary>Cambia el valor de ataque.</summary>
        /// <param name="tipo_ataque">Tipo de ataque.</param>
        /// <param name="valor_cambio">Incremento o decremento.</param>
        void cambiaAtaque(TipoAtaque *tipo_ataque, int valor_cambio);
        /// <summary>Restaura el ataque a su valor inicial.</summary>
        /// <param name="tipo_ataque">Tipo de ataque.</param>
        void restauraAtaque(TipoAtaque *tipo_ataque);

        /// <summary>Comprueba si el tipo de defensa está registrado.</summary>
        bool apareceDefensa(TipoDefensa *tipo_ataque) const;
        /// <summary>Obtiene el valor de defensa base.</summary>
        int valorDefensa(TipoDefensa *tipo_ataque) const;
        /// <summary>Registra un tipo de defensa con valor base.</summary>
        void agregaDefensa(TipoDefensa *tipo_defensa, int valor_base);
        /// <summary>Cambia el valor de defensa.</summary>
        void cambiaDefensa(TipoDefensa *tipo_defensa, int valor_cambio);
        /// <summary>Restaura defensa a su valor inicial.</summary>
        void restauraDefensa(TipoDefensa *tipo_defensa);

        /// <summary>Comprueba si el tipo de reducción de daño está registrado.</summary>
        bool apareceReduceDano(TipoDano *tipo_dano) const;
        /// <summary>Obtiene el valor de reducción de daño.</summary>
        int valorReduceDano(TipoDano *tipo_dano) const;
        /// <summary>Registra reducción de daño.</summary>
        void agregaReduceDano(TipoDano *tipo_dano, int valor);

        /// <summary>Obtiene la lista de habilidades.</summary>
        static constexpr int maximoHabilidades = 10;
        const std::vector<Habilidad *> &habilidades() const;
        /// <summary>Añade una habilidad al personaje.</summary>
        void agregaHabilidad(Habilidad *elemento);

        /// <summary>Obtiene el índice interno.</summary>
        int indice();
        /// <summary>Asigna el índice interno.</summary>
        void ponIndice(int valor);

        /// <summary>Accede a la presencia gráfica del personaje.</summary>
        PresenciaPersonaje &presencia();

        /// <summary>Obtiene la posición de la ficha.</summary>
        Coord sitioFicha() const;
        /// <summary>Asigna la posición de la ficha.</summary>
        void ponSitioFicha(Coord valor);

        /// <summary>Obtiene la vitalidad actual.</summary>
        static constexpr int maximaVitalidad = 100;
        int vitalidad() const;
        /// <summary>Asigna la vitalidad.</summary>
        void ponVitalidad(int valor);

        /// <summary>Obtiene los puntos de acción.</summary>
        static constexpr int maximoPuntosAccion = 20;
        int puntosAccion() const;
        /// <summary>Asigna puntos de acción.</summary>
        void ponPuntosAccion(int valor);

        /// <summary>Obtiene iniciativa del personaje.</summary>
        int iniciativa() const;
        /// <summary>Asigna iniciativa.</summary>
        void ponIniciativa(int valor);

        /// <summary>Obtiene estado de utilizable.</summary>
        int utilizable() const;
        /// <summary>Asigna estado de utilizable.</summary>
        void ponUtilizable(int valor);

        /// <summary>Obtiene puntos de acción restantes en turno.</summary>
        int puntosAccionEnJuego() const;
        /// <summary>Asigna puntos de acción restantes.</summary>
        void ponPuntosAccionEnJuego(int valor);

        /// <summary>Obtiene ruta del archivo SFX de personaje.</summary>
        const string &archivoPersonajeSFX();
        /// <summary>Obtiene volumen del SFX de personaje.</summary>
        int volumenPersonajeSFX();
        /// <summary>Asigna SFX de personaje y volumen.</summary>
        void asignaPersonajeSFX(const string &archivo_establece, int volumen);
        /// <summary>Emite SFX de personaje.</summary>
        void emitePersonajeSFX();

        /// <summary>Obtiene ruta del SFX de selección.</summary>
        const string &archivoSeleccionSFX();
        /// <summary>Obtiene volumen del SFX de selección.</summary>
        int volumenSeleccionSFX();
        /// <summary>Asigna SFX de selección y volumen.</summary>
        void asignaSeleccionSFX(const string &archivo_establece, int volumen);
        /// <summary>Emite SFX de selección.</summary>
        void emiteSeleccionSFX();

        /// <summary>Obtiene ruta del SFX de desplazamiento.</summary>
        const string &archivoDesplazamientoSFX();
        /// <summary>Obtiene volumen de desplazamiento.</summary>
        int volumenDesplazamientoSFX();
        /// <summary>Asigna SFX de desplazamiento y volumen.</summary>
        void asignaDesplazamientoSFX(const string &archivo_establece, int volumen);
        /// <summary>Emite SFX de desplazamiento.</summary>
        void emiteDesplazamientoSFX();

    protected:
        /// <summary>Inicializa el actor.</summary>
        void inicia() override;

        /// <summary>Finaliza el actor.</summary>
        void termina() override;

        /// <summary>Actualiza el actor cada fotograma.</summary>
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

        /// <summary>Refresca la representación de la ficha.</summary>
        void refrescaFicha();
        /// <summary>Gestiona la pulsación sobre el personaje.</summary>
        void controlPersonajePulsacion();
        /// <summary>Gestiona el hover sobre la ficha.</summary>
        void controlSobreFicha();
        /// <summary>Gestiona la pulsación sobre la ficha.</summary>
        void controlFichaPulsacion();

        /// <summary>
        /// Comprueba una condición y lanza excepción si es falsa.
        /// </summary>
        /// <param name="expresion">Expresión a evaluar.</param>
        /// <param name="mensaje">Mensaje de error.</param>
        static void aserta(bool expresion, const string &mensaje);

        friend class CalculoCaminos;
        friend class PresenciaPersonaje;
    };

}
