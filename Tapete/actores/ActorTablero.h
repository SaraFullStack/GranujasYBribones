// proyecto: Grupal/Tapete
// archivo:  ActorTablero.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class JuegoMesaBase;

    class ActorTablero : public unir2d::ActorBase
    {
    public:
        static constexpr int columnasGraficoMuros = RejillaTablero::columnas * 3 - 2;
        using GraficoMuros = std::array<const char[columnasGraficoMuros + 1], RejillaTablero::filas>;

        /// <summary>
        /// Constructor: inicializa el actor de tablero.
        /// </summary>
        explicit ActorTablero(JuegoMesaBase *juego);

        /// <summary>
        /// Destructor: libera los recursos gráficos y lógicos.
        /// </summary>
        ~ActorTablero();

        /// <summary>
        /// Obtiene la ruta del archivo de baldosas.
        /// </summary>
        const string &archivoBaldosas();

        /// <summary>
        /// Asigna el archivo de baldosas para el fondo.
        /// </summary>
        void ponArchivoBaldosas(const string &archivo);

        /// <summary>
        /// Obtiene el nombre del equipo en un lado del tablero.
        /// </summary>
        const wstring &nombreEquipo(LadoTablero lado_tablero);

        /// <summary>
        /// Obtiene la ruta del escudo para un equipo.
        /// </summary>
        const string &ArchivoEscudo(LadoTablero lado_tablero);

        /// <summary>
        /// Configura nombre y escudo para un equipo.
        /// </summary>
        void equipa(LadoTablero lado_tablero, const wstring &nombre, const string &archivo_escudo);

        /// <summary>
        /// Devuelve las coordenadas de los muros.
        /// </summary>
        const std::vector<Coord> &sitiosMuros() const;

        /// <summary>
        /// Sitúa los muros según un gráfico dado.
        /// </summary>
        void situaMuros(const GraficoMuros &grafico_muros);

        /// <summary>
        /// Valida las dimensiones del gráfico de muros.
        /// </summary>
        void validaGraficoMuros();

        /// <summary>
        /// Accede a la rejilla del tablero.
        /// </summary>
        RejillaTablero &rejilla();

        /// <summary>
        /// Obtiene la presencia de un actor según el lado.
        /// </summary>
        PresenciaActuante &presencia(LadoTablero lado);

        /// <summary>
        /// Obtiene el indicador de información.
        /// </summary>
        CuadroIndica &indicador();

        /// <summary>
        /// Obtiene la vista de camino de celdas.
        /// </summary>
        VistaCaminoCeldas &vistaCamino();

        /// <summary>
        /// Obtiene el listado de ayuda.
        /// </summary>
        ListadoAyuda &listadoAyuda();

        /// <summary>
        /// Muestra mensaje en el monitor de texto.
        /// </summary>
        template <typename S>
        void escribeMonitor(
            const std::vector<S> &mensaje,
            const std::vector<S> &indica);

        /// <summary>
        /// Muestra un display numérico de dos dígitos.
        /// </summary>
        void muestraDisplay(int digito_1, int digito_2);

        /// <summary>
        /// Borra el contenido del display.
        /// </summary>
        void borraDisplay();

        /// <summary>
        /// Indica un mensaje junto a un personaje.
        /// </summary>
        void indicaPersonaje(LadoTablero lado, const wstring &cadena);

        /// <summary>
        /// Indica un mensaje junto a una habilidad.
        /// </summary>
        void indicaHabilidad(LadoTablero lado, int indice_habilidad, const wstring &cadena);

        /// <summary>
        /// Limpia todas las indicaciones.
        /// </summary>
        void desindica();

        /// <summary>
        /// Obtiene la ruta del sonido de acción.
        /// </summary>
        const string &archivoSonidoEstablece();

        /// <summary>
        /// Obtiene el volumen del sonido de acción.
        /// </summary>
        int volumenSonidoEstablece();

        /// <summary>
        /// Asigna sonido de acción y su volumen.
        /// </summary>
        void asignaSonidoEstablece(const string &archivo_establece, int volumen);

        /// <summary>
        /// Obtiene la ruta del sonido de fracaso.
        /// </summary>
        const string &archivoSonidoFracaso();

        /// <summary>
        /// Obtiene el volumen del sonido de fracaso.
        /// </summary>
        int volumenSonidoFracaso();

        /// <summary>
        /// Asigna sonido de fracaso.
        /// </summary>
        void asignaSonidoFracaso(const string &archivo, int volumen);

        /// <summary>
        /// Obtiene la ruta del sonido de éxito.
        /// </summary>
        const string &archivoSonidoExito();

        /// <summary>
        /// Obtiene el volumen del sonido de éxito.
        /// </summary>
        int volumenSonidoExito();

        /// <summary>
        /// Asigna sonido de éxito.
        /// </summary>
        void asignaSonidoExito(const string &archivo, int volumen);

        /// <summary>
        /// Obtiene la ruta del sonido de desplazamiento.
        /// </summary>
        const string &archivoSonidoDesplaza();

        /// <summary>
        /// Obtiene el volumen del sonido de desplazamiento.
        /// </summary>
        int volumenSonidoDesplaza();

        /// <summary>
        /// Asigna sonido de desplazamiento.
        /// </summary>
        void asignaSonidoDesplaza(const string &archivo_desplaza, int volumen);

        /// <summary>
        /// Emite el sonido de acción.
        /// </summary>
        void emiteSonidoEstablece();

        /// <summary>
        /// Emite el sonido de desplazamiento.
        /// </summary>
        void emiteSonidoDesplaza();

        /// <summary>
        /// Emite el sonido de fracaso.
        /// </summary>
        void emiteSonidoFracaso();

        /// <summary>
        /// Emite el sonido de éxito.
        /// </summary>
        void emiteSonidoExito();

        /// <summary>
        /// Emite el sonido de una habilidad.
        /// </summary>
        void emiteSonidoHabilidad(Habilidad *habilidad);

    protected:
        /// <summary>
        /// Inicializa el actor de tablero.
        /// </summary>
        void inicia() override;

        /// <summary>
        /// Termina el actor de tablero.
        /// </summary>
        void termina() override;

        /// <summary>
        /// Actualiza la lógica del tablero cada fotograma.
        /// </summary>
        void actualiza(double tiempo_seg) override;

    private:
        JuegoMesaBase *juego{};

        string archivo_baldosas;

        wstring nombre_equipo_izqrd{};
        string archivo_escudo_izqrd{};
        wstring nombre_equipo_derch{};
        string archivo_escudo_derch{};

        const GraficoMuros *grafico_muros;
        std::vector<Coord> sitios_muros{};

        PresenciaTablero presencia_tablero{this};
        RejillaTablero rejilla_tablero{this};
        PresenciaHabilidades presencia_habilidades{this};
        PresenciaActuante presencia_actuante_izqrd{this, LadoTablero::Izquierda};
        PresenciaActuante presencia_actuante_derch{this, LadoTablero::Derecha};
        CuadroIndica cuadro_indica{this};
        VistaCaminoCeldas vista_camino_celdas{this};
        ListadoAyuda listado_ayuda{this};

        string archivo_sonido_establece{};
        int volumen_sonido_establece{};
        string archivo_sonido_desplaza{};
        int volumen_sonido_desplaza{};
        string archivo_sonido_fracaso{};
        int volumen_sonido_fracaso{};
        string archivo_sonido_exito{};
        int volumen_sonido_exito{};

        struct SobreRetrato
        {
            bool esta{false};
            LadoTablero lado{};
        };
        SobreRetrato sobre_retrato{};
        struct SobreHabilidad
        {
            bool esta{false};
            LadoTablero lado{};
            int indice{};
        };
        SobreHabilidad sobre_habilidad{};
        struct SobreCelda
        {
            bool esta{false};
            Coord celda{};
        };
        SobreCelda sobre_celda{};

        /// <summary>
        /// Calcula los lugares de los muros en la rejilla.
        /// </summary>
        void calculaSitiosMuros();

        /// <summary>
        /// Gestiona el hover sobre retratos.
        /// </summary>
        void controlSobreRetrato();

        /// <summary>
        /// Gestiona el hover sobre habilidades.
        /// </summary>
        void controlSobreHabilidad();

        /// <summary>
        /// Gestiona la pulsación en retratos.
        /// </summary>
        void controlRetratoPulsacion();

        /// <summary>
        /// Gestiona la pulsación en habilidades.
        /// </summary>
        void controlHabilidadPulsacion();

        /// <summary>
        /// Gestiona el hover sobre celdas.
        /// </summary>
        void controlSobreCelda();

        /// <summary>
        /// Gestiona la pulsación en celdas.
        /// </summary>
        void controlCeldaPulsacion();

        /// <summary>
        /// Gestiona la pulsación en ayuda.
        /// </summary>
        void controlAyudaPulsacion();

        /// <summary>
        /// Verifica condiciones y lanza excepción si fallan.
        /// </summary>
        static void aserta(bool expresion, const string &mensaje);

        friend class PresenciaTablero;
        friend class RejillaTablero;
        friend class PresenciaHabilidades;
        friend class PresenciaActuante;
        friend class ListadoAyuda;
    };

    template <typename S>
    void ActorTablero::escribeMonitor(
        const std::vector<S> &mensaje,
        const std::vector<S> &indica)
    {
        aserta(mensaje.size() + indica.size() <= PresenciaTablero::lineas_texto_monitor,
               "excesivo número de línea a escribir");

        for (int indc = 0; indc < PresenciaTablero::lineas_texto_monitor; ++indc)
        {
            presencia_tablero.texto_monitor[indc]->ponCadena("");
        }
        for (int indc = 0; indc < mensaje.size(); ++indc)
        {
            presencia_tablero.texto_monitor[indc]->ponCadena(mensaje[indc]);
            presencia_tablero.texto_monitor[indc]->ponColor(PresenciaTablero::rojo_oxido);
        }
        int indc_text = PresenciaTablero::lineas_texto_monitor - static_cast<int>(indica.size());
        for (int indc = 0; indc < indica.size(); ++indc)
        {
            presencia_tablero.texto_monitor[indc_text]->ponCadena(indica[indc]);
            presencia_tablero.texto_monitor[indc_text]->ponColor(Color::Amarillo);
            indc_text++;
        }
    }

}