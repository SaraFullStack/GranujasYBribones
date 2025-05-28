// proyecto: Grupal/Tapete
// archivo:  ModoJuegoBase.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    /* 
     * \class ModoJuegoBase
     * \brief Clase base para la gestión de la lógica de los distintos modos de juego.
     *
     * Proporciona la interfaz y utilidades para la gestión de rondas, turnos, jugadas, equipos, personajes,
     * acciones, caminos, habilidades, áreas y eventos de ayuda. Permite la configuración y control del flujo
     * principal de la partida, así como la depuración mediante informes de proceso.
     * Debe ser derivada para implementar la lógica específica de cada modo de juego.
     */
    class ModoJuegoBase {
    public:
        /*!
         * \brief Destructor virtual necesario para la herencia.
         */
        virtual ~ModoJuegoBase ();

        /*!
         * \brief Devuelve el puntero al juego asociado.
         * \return Puntero a JuegoMesaBase.
         */
        JuegoMesaBase * juego ();

        /*!
         * \brief Devuelve los puntos de acción necesarios para desplazarse.
         * \return Puntos de acción.
         */
        float puntosAccionDeDesplaza () const;

        /*!
         * \brief Configura los puntos de acción necesarios para desplazarse.
         * \param puntos_accion_desplaza Valor a configurar.
         */
        void configuraDesplaza (float puntos_accion_desplaza);

        /*!
         * \brief Devuelve el número de ronda actual.
         */
        int ronda  () const;

        /*!
         * \brief Devuelve el número de turno actual.
         */
        int turno  () const;

        /*!
         * \brief Devuelve el número de jugada actual.
         */
        int jugada () const;

        /*!
         * \brief Devuelve el lado del equipo inicial.
         */
        LadoTablero ladoEquipoInicial () const;

        /*!
         * \brief Devuelve el lado del equipo actual.
         */
        LadoTablero ladoEquipoActual  () const;

        /*!
         * \brief Devuelve la lista de factores de los equipos.
         */
        const std::vector <ActorPersonaje * > & factoresEquipos () const;

        /*!
         * \brief Devuelve el índice del factor de equipos.
         */
        int indiceFactorEquipos () const;

        /*!
         * \brief Devuelve el personaje elegido de un lado.
         * \param lado Lado del tablero.
         */
        ActorPersonaje * personajeElegido (LadoTablero lado) const;

        /*!
         * \brief Devuelve el atacante actual.
         */
        ActorPersonaje * atacante () const;

        /*!
         * \brief Devuelve el modo de acción del personaje.
         */
        ModoAccionPersonaje  modoAccion () const;

        /*!
         * \brief Devuelve las etapas del camino actual.
         */
        const std::vector <Coord> & etapasCamino () const;

        /*!
         * \brief Devuelve la habilidad de acción actual.
         */
        Habilidad * habilidadAccion () const;

        /*!
         * \brief Devuelve el oponente actual.
         */
        ActorPersonaje * oponente () const;

        /*!
         * \brief Devuelve el área de celdas actual.
         */
        const AreaCentradaCeldas & areaCeldas () const;

        /*!
         * \brief Devuelve el texto del informe de depuración.
         */
        const string textoInforme () const;

    protected:

        /*!
         * \brief Constructor protegido. Inicializa el modo de juego con el juego asociado.
         * \param juego Puntero al juego.
         */
        ModoJuegoBase (JuegoMesaBase * juego);

        /*!
         * \brief Comprueba si ambos equipos tienen el mismo número de personajes.
         * \return true si es igual, false en caso contrario.
         */
        bool cuentaPersonajesIgual ();

        /*!
         * \brief Inicia las rondas del juego.
         */
        void iniciaRondas ();

        /*!
         * \brief Avanza a la siguiente jugada.
         */
        void avanzaJugada ();

        /*!
         * \brief Avanza al siguiente turno.
         */
        void avanzaTurno  ();

        /*!
         * \brief Avanza a la siguiente ronda.
         */
        void avanzaRonda  ();

        /*!
         * \brief Atenúa la música del juego.
         */
        void atenuaMusica ();

        /*!
         * \brief Elige el equipo con la iniciativa.
         * \return Lado del equipo con iniciativa.
         */
        LadoTablero eligeEquipoIniciativa ();

        /*!
         * \brief Asigna el equipo inicial.
         * \param equipo Lado del equipo.
         */
        void asignaEquipoInicial (LadoTablero equipo);

        /*!
         * \brief Asigna el equipo actual.
         * \param equipo Lado del equipo.
         */
        void asignaEquipoActual  (LadoTablero equipo);

        /*!
         * \brief Establece los factores de los equipos.
         */
        void estableceFactoresEquipos ();

        /*!
         * \brief Indexa el factor de equipos.
         * \param valor Índice.
         */
        void indexaFactorEquipos (int valor);

        /*!
         * \brief Establece el personaje elegido.
         * \param personaje Puntero al personaje.
         */
        void establecePersonajeElegido (ActorPersonaje * personaje);

        /*!
         * \brief Anula la elección de personajes.
         */
        void anulaEleccionPersonajes ();

        /*!
         * \brief Elige el atacante con iniciativa.
         * \return Lado del atacante.
         */
        LadoTablero eligeAtacanteIniciativa ();

        /*!
         * \brief Establece el atacante.
         * \param lado_tablero Lado del tablero.
         */
        void estableceAtacante (LadoTablero lado_tablero);

        /*!
         * \brief Suprime el atacante actual.
         */
        void suprimeAtacante ();

        /*!
         * \brief Reinicia el atacante.
         */
        void reiniciaAtacante ();

        /*!
         * \brief Establece el modo de acción de desplazamiento.
         */
        void estableceModoAccionDesplazam ();

        /*!
         * \brief Establece el modo de acción de habilidad.
         * \param indice_habilidad Índice de la habilidad.
         */
        void estableceModoAccionHabilidad (int indice_habilidad);

        /*!
         * \brief Anula el modo de acción.
         */
        void anulaModoAccion ();

        /*!
         * \brief Marca la celda de inicio.
         */
        void marcaCeldaInicio ();

        /*!
         * \brief Desmarca la celda de inicio.
         */
        void desmarcaCeldaInicio ();

        /*!
         * \brief Inicia el camino de movimiento.
         */
        void iniciaCamino ();

        /*!
         * \brief Valida una etapa del camino.
         * \param proxima_celda Próxima celda.
         * \param etapa_valida Resultado de la validación.
         * \param puntos_en_juego Puntos en juego.
         */
        void validaEtapaCamino   (Coord proxima_celda, bool & etapa_valida, int & puntos_en_juego);

        /*!
         * \brief Marca una celda del camino.
         * \param proxima_celda Próxima celda.
         * \param etapa_valida Si la etapa es válida.
         */
        void marcaCeldaCamino    (Coord proxima_celda, bool etapa_valida);

        /*!
         * \brief Desmarca una celda del camino.
         * \param proxima_celda Próxima celda.
         */
        void desmarcaCeldaCamino (Coord proxima_celda);

        /*!
         * \brief Agrega una etapa al camino.
         * \param proxima_celda Próxima celda.
         * \param puntos_en_juego Puntos en juego.
         */
        void agregaEtapaCamino   (Coord proxima_celda, int puntos_en_juego);

        /*!
         * \brief Mueve la ficha a lo largo del camino.
         */
        void mueveFichaCamino ();

        /*!
         * \brief Anula el camino actual.
         */
        void anulaCamino ();

        /*!
         * \brief Genera un valor aleatorio entre 0 y 100.
         */
        void alea100 ();

        /*!
         * \brief Muestra el valor aleatorio generado.
         */
        void muestraAleatorio100 ();

        /*!
         * \brief Oculta el valor aleatorio mostrado.
         */
        void ocultaAleatorio100 ();

        /*!
         * \brief Muestra la ayuda general.
         */
        void muestraAyudaGeneral ();

        /*!
         * \brief Muestra la ayuda específica de un personaje.
         * \param personaje Puntero al personaje.
         */
        void muestraAyudaPersonaje (ActorPersonaje * personaje);

        /*!
         * \brief Muestra la ayuda de cálculo.
         */
        void muestraAyudaCalculo ();

        /*!
         * \brief Navega hacia arriba en la ayuda.
         */
        void sigueAyudaArriba ();

        /*!
         * \brief Navega hacia abajo en la ayuda.
         */
        void sigueAyudaAbajo ();

        /*!
         * \brief Oculta la ayuda.
         */
        void ocultaAyuda ();

        /*!
         * \brief Valida el uso de una habilidad simple.
         * \param uso_valido Resultado de la validación.
         * \param puntos_en_juego Puntos en juego.
         */
        void validaHabilidadSimple  (bool & uso_valido, int & puntos_en_juego);

        /*!
         * \brief Muestra la información de una habilidad simple.
         * \param uso_valido Si el uso es válido.
         * \param puntos_en_juego Puntos en juego.
         */
        void muestraHabilidadSimple (bool uso_valido, int puntos_en_juego);

        /*!
         * \brief Oculta la información de la habilidad simple.
         */
        void ocultaHabilidadSimple ();

        /*!
         * \brief Aplica la habilidad simple.
         */
        void aplicaHabilidadSimple ();

        /*!
         * \brief Establece el oponente.
         * \param personaje Puntero al personaje oponente.
         */
        void estableceOponente (ActorPersonaje * personaje);

        /*!
         * \brief Suprime el oponente actual.
         */
        void suprimeOponente ();

        /*!
         * \brief Valida el ataque al oponente.
         * \param acceso_valido Resultado de la validación.
         * \param puntos_en_juego Puntos en juego.
         */
        void validaAtaqueOponente  (bool & acceso_valido, int & puntos_en_juego);

        /*!
         * \brief Muestra la información del ataque al oponente.
         * \param acceso_valido Si el acceso es válido.
         * \param puntos_en_juego Puntos en juego.
         */
        void muestraAtaqueOponente (bool acceso_valido, int puntos_en_juego);

        /*!
         * \brief Oculta la información del ataque al oponente.
         */
        void ocultaAtaqueOponente ();

        /*!
         * \brief Realiza el ataque al oponente.
         */
        void atacaOponente ();

        /*!
         * \brief Establece el área de la habilidad.
         * \param celda Celda central del área.
         */
        void estableceAreaHabilidad (Coord celda);

        /*!
         * \brief Anula el área de la habilidad.
         */
        void anulaAreaHabilidad ();

        /*!
         * \brief Valida el ataque de área.
         * \param acceso_valido Resultado de la validación.
         * \param puntos_en_juego Puntos en juego.
         */
        void validaAtaqueArea  (bool & acceso_valido, int & puntos_en_juego);

        /*!
         * \brief Muestra la información del ataque de área.
         * \param acceso_valido Si el acceso es válido.
         * \param puntos_en_juego Puntos en juego.
         */
        void muestraAtaqueArea (bool acceso_valido, int puntos_en_juego);

        /*!
         * \brief Oculta la información del ataque de área.
         */
        void ocultaAtaqueArea ();

        /*!
         * \brief Realiza el ataque de área.
         */
        void atacaArea ();

        /*!
         * \brief Inicia el temporizador de cálculo.
         */
        void iniciaTiempoCalculo ();

        /*!
         * \brief Termina el temporizador de cálculo.
         */
        void terminaTiempoCalculo ();

        /*!
         * \brief Muestra la indicación del actuante.
         * \param lado Lado del tablero.
         */
        void muestraIndicaActuante  (LadoTablero lado);

        /*!
         * \brief Muestra la indicación de la habilidad.
         * \param lado Lado del tablero.
         * \param indice_habilidad Índice de la habilidad.
         */
        void muestraIndicaHabilidad (LadoTablero lado, int indice_habilidad);

        /*!
         * \brief Muestra la indicación de la ficha.
         * \param personaje Puntero al personaje.
         */
        void muestraIndicaFicha     (ActorPersonaje * personaje);    

        /*!
         * \brief Oculta todas las indicaciones.
         */
        void ocultaIndicaciones     ();

        /*!
         * \brief Indica si hay rondas disponibles.
         * \return true si hay rondas, false en caso contrario.
         */
        bool rondasDisponibles ();

        /*!
         * \brief Indica si ambos equipos tienen turnos disponibles.
         * \return true si ambos tienen turnos, false en caso contrario.
         */
        bool turnosDisponiblesAmbos ();

        /*!
         * \brief Anula completamente el estado del modo de juego.
         */
        void anulaTotalmente ();

        /*!
         * \brief Almacena un informe de depuración.
         * \param estado Estado del juego.
         * \param modulo Nombre del módulo.
         * \param metodo Nombre del método.
         */
        void almacenaInforme ( 
                const EstadoJuegoComun & estado,
                const string &           modulo, 
                const string &           metodo );

    private:


        class InformesProceso {
        public:

            void agregaInforme (
                    const EstadoJuegoComun & estado, 
                    const ModoJuegoBase * proceso, 
                    const string &           modulo, 
                    const string &           metodo  );

            const string textoInforme () const;

        private:

            struct Informe {

                std::chrono::system_clock::time_point tiempo;

                string estado;

                int ronda_;
                int turno_;
                int jugada_;

                string modulo;
                string metodo;

            };


            std::array <Informe *, 20> lista_informes {}; 


            void prepara  (Informe * & informe);
            void rota ();

        };


    private:

        inline static bool trazar_avance = true;

        JuegoMesaBase * juego_;

        float puntos_accion_de_desplaza {};

        int ronda_  {};
        int turno_  {};
        int jugada_ {};

        LadoTablero lado_equipo_inicial {};
        LadoTablero lado_equipo_actual {};

        std::vector <ActorPersonaje * > factores_equipos {};
        int                             indice_factor_equipos {};

        ActorPersonaje * personaje_elegido_izqrd {};
        ActorPersonaje * personaje_elegido_derch {};

        ActorPersonaje * atacante_ {};

        ModoAccionPersonaje  modo_accion {};
        std::vector <Coord>  etapas_camino {};
        Habilidad *          habilidad_accion {};        
        ActorPersonaje *     oponente_ {};
        AreaCentradaCeldas   area_celdas {};

        int valor_aleatorio_100 {};

        InformesProceso informes_proceso {};

        inline static Color color_elegido  = Color::Blanco;
        inline static Color color_atacante = Color::Amarillo;
        inline static Color color_objetivo = Color::Marron;


        static int azarosa (unsigned int contador);

        int   puntosEnJuegoCamino   (Coord proxima_celda) const;
        float distanciaCeldas (Coord celda_origen, Coord celda_destino) const;

        void marcaCeldasArea ();
        void desmarcaCeldasArea ();
        void personajesAreaCeldas (std::vector <ActorPersonaje *> & lista_oponentes) const;

        void iniciaPersonajes ();
        void restauraPersonajes ();

        void refrescaBarrasVida ();
        void refrescaPuntosAccion ();

        void asertaHabilidadSimple   (const string & metodo);
        void asertaHabilidadOponente (const string & metodo, ActorPersonaje * oponentable);
        void asertaHabilidadArea     (const string & metodo, bool con_area);
        void aserta (bool condicion, const string & metodo, const string & explicacion) const;


        friend class InformesProceso;

    };


}


