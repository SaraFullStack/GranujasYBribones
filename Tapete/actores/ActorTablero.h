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
        /*!
         * \brief Número de columnas del gráfico de muros.
         */
        static constexpr int columnasGraficoMuros = RejillaTablero::columnas * 3 - 2;

        /*!
         * \brief Tipo para el gráfico de muros.
         */
        using GraficoMuros = std::array<const char[columnasGraficoMuros + 1], RejillaTablero::filas>;

        /*!
         * \brief Constructor: inicializa el actor de tablero.
         * \param juego Contexto del juego.
         */
        explicit ActorTablero(JuegoMesaBase *juego);

        /*!
         * \brief Destructor: libera los recursos gráficos y lógicos.
         */
        ~ActorTablero();

        /*!
         * \brief Obtiene la ruta del archivo de baldosas.
         * \return Ruta del archivo.
         */
        const string &archivoBaldosas();

        /*!
         * \brief Asigna el archivo de baldosas para el fondo.
         * \param archivo Ruta del archivo.
         */
        void ponArchivoBaldosas(const string &archivo);

        /*!
         * \brief Obtiene el nombre del equipo en un lado del tablero.
         * \param lado_tablero Lado del tablero.
         * \return Nombre del equipo.
         */
        const wstring &nombreEquipo(LadoTablero lado_tablero);

        /*!
         * \brief Obtiene la ruta del escudo para un equipo.
         * \param lado_tablero Lado del tablero.
         * \return Ruta del archivo de escudo.
         */
        const string &ArchivoEscudo(LadoTablero lado_tablero);

        /*!
         * \brief Configura nombre y escudo para un equipo.
         * \param lado_tablero Lado del tablero.
         * \param nombre Nombre del equipo.
         * \param archivo_escudo Ruta del archivo de escudo.
         */
        void equipa(LadoTablero lado_tablero, const wstring &nombre, const string &archivo_escudo);

        /*!
         * \brief Devuelve las coordenadas de los muros.
         * \return Vector de coordenadas.
         */
        const std::vector<Coord> &sitiosMuros() const;

        /*!
         * \brief Sitúa los muros según un gráfico dado.
         * \param grafico_muros Gráfico de muros.
         */
        void situaMuros(const GraficoMuros &grafico_muros);

        /*!
         * \brief Valida las dimensiones del gráfico de muros.
         */
        void validaGraficoMuros();

        /*!
         * \brief Accede a la rejilla del tablero.
         * \return Referencia a la rejilla.
         */
        RejillaTablero &rejilla();

        /*!
         * \brief Obtiene la presencia de un actor según el lado.
         * \param lado Lado del tablero.
         * \return Referencia a la presencia.
         */
        PresenciaActuante &presencia(LadoTablero lado);

        /*!
         * \brief Obtiene el indicador de información.
         * \return Referencia al cuadro indicador.
         */
        CuadroIndica &indicador();

        /*!
         * \brief Obtiene la vista de camino de celdas.
         * \return Referencia a la vista.
         */
        VistaCaminoCeldas &vistaCamino();

        /*!
         * \brief Obtiene el listado de ayuda.
         * \return Referencia al listado.
         */
        ListadoAyuda &listadoAyuda();

        /*!
         * \brief Muestra mensaje en el monitor de texto.
         * \param mensaje Vector de líneas de mensaje.
         * \param indica Vector de líneas de indicación.
         */
        template <typename S>
        void escribeMonitor(
            const std::vector<S> &mensaje,
            const std::vector<S> &indica);

        /*!
         * \brief Muestra un display numérico de dos dígitos.
         * \param digito_1 Primer dígito.
         * \param digito_2 Segundo dígito.
         */
        void muestraDisplay(int digito_1, int digito_2);

        /*!
         * \brief Borra el contenido del display.
         */
        void borraDisplay();

        /*!
         * \brief Indica un mensaje junto a un personaje.
         * \param lado Lado del tablero.
         * \param cadena Mensaje a mostrar.
         */
        void indicaPersonaje(LadoTablero lado, const wstring &cadena);

        /*!
         * \brief Indica un mensaje junto a una habilidad.
         * \param lado Lado del tablero.
         * \param indice_habilidad Índice de la habilidad.
         * \param cadena Mensaje a mostrar.
         */
        void indicaHabilidad(LadoTablero lado, int indice_habilidad, const wstring &cadena);

        /*!
         * \brief Limpia todas las indicaciones.
         */
        void desindica();

        /*!
         * \brief Obtiene la ruta del sonido de acción.
         * \return Ruta del archivo.
         */
        const string &archivoSonidoEstablece();

        /*!
         * \brief Obtiene el volumen del sonido de acción.
         * \return Volumen.
         */
        int volumenSonidoEstablece();

        /*!
         * \brief Asigna sonido de acción y su volumen.
         * \param archivo_establece Ruta del archivo.
         * \param volumen Volumen.
         */
        void asignaSonidoEstablece(const string &archivo_establece, int volumen);

        /*!
         * \brief Obtiene la ruta del sonido de fracaso.
         * \return Ruta del archivo.
         */
        const string &archivoSonidoFracaso();

        /*!
         * \brief Obtiene el volumen del sonido de fracaso.
         * \return Volumen.
         */
        int volumenSonidoFracaso();

        /*!
         * \brief Asigna sonido de fracaso.
         * \param archivo Ruta del archivo.
         * \param volumen Volumen.
         */
        void asignaSonidoFracaso(const string &archivo, int volumen);

        /*!
         * \brief Obtiene la ruta del sonido de éxito.
         * \return Ruta del archivo.
         */
        const string &archivoSonidoExito();

        /*!
         * \brief Obtiene el volumen del sonido de éxito.
         * \return Volumen.
         */
        int volumenSonidoExito();

        /*!
         * \brief Asigna sonido de éxito.
         * \param archivo Ruta del archivo.
         * \param volumen Volumen.
         */
        void asignaSonidoExito(const string &archivo, int volumen);

        /*!
         * \brief Obtiene la ruta del sonido de desplazamiento.
         * \return Ruta del archivo.
         */
        const string &archivoSonidoDesplaza();

        /*!
         * \brief Obtiene el volumen del sonido de desplazamiento.
         * \return Volumen.
         */
        int volumenSonidoDesplaza();

        /*!
         * \brief Asigna sonido de desplazamiento.
         * \param archivo_desplaza Ruta del archivo.
         * \param volumen Volumen.
         */
        void asignaSonidoDesplaza(const string &archivo_desplaza, int volumen);

        /*!
         * \brief Emite el sonido de acción.
         */
        void emiteSonidoEstablece();

        /*!
         * \brief Emite el sonido de desplazamiento.
         */
        void emiteSonidoDesplaza();

        /*!
         * \brief Emite el sonido de fracaso.
         */
        void emiteSonidoFracaso();

        /*!
         * \brief Emite el sonido de éxito.
         */
        void emiteSonidoExito();

        /*!
         * \brief Emite el sonido de una habilidad.
         * \param habilidad Puntero a la habilidad.
         */
        void emiteSonidoHabilidad(Habilidad *habilidad);

    protected:
        /*!
         * \brief Inicializa el actor de tablero.
         */
        void inicia() override;

        /*!
         * \brief Termina el actor de tablero.
         */
        void termina() override;

        /*!
         * \brief Actualiza la lógica del tablero cada fotograma.
         * \param tiempo_seg Tiempo en segundos.
         */
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

        /*!
         * \brief Calcula los lugares de los muros en la rejilla.
         */
        void calculaSitiosMuros();

        /*!
         * \brief Gestiona el hover sobre retratos.
         */
        void controlSobreRetrato();

        /*!
         * \brief Gestiona el hover sobre habilidades.
         */
        void controlSobreHabilidad();

        /*!
         * \brief Gestiona la pulsación en retratos.
         */
        void controlRetratoPulsacion();

        /*!
         * \brief Gestiona la pulsación en habilidades.
         */
        void controlHabilidadPulsacion();

        /*!
         * \brief Gestiona el hover sobre celdas.
         */
        void controlSobreCelda();

        /*!
         * \brief Gestiona la pulsación en celdas.
         */
        void controlCeldaPulsacion();

        /*!
         * \brief Gestiona la pulsación en ayuda.
         */
        void controlAyudaPulsacion();

        /*!
         * \brief Verifica condiciones y lanza excepción si fallan.
         * \param expresion Expresión a evaluar.
         * \param mensaje Mensaje de error.
         */
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