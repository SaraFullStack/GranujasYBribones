// proyecto: Grupal/Tapete
// archivo   ModoJuegoComun.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


/* 
 * \class ModoJuegoComun
 * \brief Implementa la lógica común para los modos de juego estándar, derivando de ModoJuegoBase.
 *
 * Gestiona el estado actual y previo del juego, la interacción con el tablero y los personajes,
 * la evaluación y ejecución de habilidades, el control de ayudas, y la validación de atributos y estados.
 * Incluye utilidades para depuración y control de flujo en las distintas fases de la partida.
 */
class ModoJuegoComun : public ModoJuegoBase {
public:
    /*!
     * \brief Destructor virtual.
     */
    ~ModoJuegoComun() override;

    /*!
     * \brief Devuelve una referencia al estado actual del juego.
     */
    EstadoJuegoComun &estado();

    /*!
     * \brief Devuelve una referencia al estado previo del juego.
     */
    EstadoJuegoComun &estadoPrevio();

    /*!
     * \brief Salta al estado final del juego.
     */
    void saltaFinalJuego();

    /*!
     * \brief Anuncia el actuante de un lado.
     * \param lado Lado del tablero.
     */
    void anunciaActuante(LadoTablero lado);

    /*!
     * \brief Quita el anuncio del actuante de un lado.
     * \param lado Lado del tablero.
     */
    void desanunciaActuante(LadoTablero lado);

    /*!
     * \brief Anuncia una habilidad de un lado.
     * \param lado Lado del tablero.
     * \param indice Índice de la habilidad.
     */
    void anunciaHabilidad(LadoTablero lado, int indice);

    /*!
     * \brief Quita el anuncio de una habilidad de un lado.
     * \param lado Lado del tablero.
     * \param indice Índice de la habilidad.
     */
    void desanunciaHabilidad(LadoTablero lado, int indice);

    /*!
     * \brief Anuncia una ficha (personaje).
     * \param personaje Puntero al personaje.
     */
    void anunciaFicha(ActorPersonaje *personaje);

    /*!
     * \brief Quita el anuncio de una ficha (personaje).
     * \param personaje Puntero al personaje.
     */
    void desanunciaFicha(ActorPersonaje *personaje);

    /*!
     * \brief Entra en la acción de desplazamiento.
     */
    void entraAccionDesplazam();

    /*!
     * \brief Entra en la marcación del camino.
     */
    void entraMarcacionCamino();

    /*!
     * \brief Marca una ficha en el camino.
     * \param personaje Puntero al personaje.
     */
    void marcaFichaCamino(ActorPersonaje *personaje);

    /*!
     * \brief Desmarca una ficha en el camino.
     * \param personaje Puntero al personaje.
     */
    void desmarcaFichaCamino(ActorPersonaje *personaje);

    /*!
     * \brief Marca una celda del camino.
     * \param celda Coordenada de la celda.
     */
    void marcaCeldaCamino(Coord celda);

    /*!
     * \brief Desmarca una celda del camino.
     * \param celda Coordenada de la celda.
     */
    void desmarcaCeldaCamino(Coord celda);

    /*!
     * \brief Fija una celda del camino.
     * \param celda Coordenada de la celda.
     */
    void fijaCeldaCamino(Coord celda);

    /*!
     * \brief Revierte la acción de desplazamiento.
     */
    void revierteAccionDesplazam();

    /*!
     * \brief Entra en la acción de habilidad.
     * \param indice_habilidad Índice de la habilidad.
     */
    void entraAccionHabilidad(int indice_habilidad);

    /*!
     * \brief Evalúa una habilidad simple.
     * \param indice_habilidad Índice de la habilidad.
     */
    void evaluaHabilidadSimple(int indice_habilidad);

    /*!
     * \brief Ejecuta una habilidad simple.
     */
    void efectuaHabilidadSimple();

    /*!
     * \brief Revierte una habilidad simple.
     */
    void revierteHabilidadSimple();

    /*!
     * \brief Evalúa una habilidad de oponente por índice.
     * \param indice_habilidad Índice de la habilidad.
     */
    void evaluaHabilidadOponente(int indice_habilidad);

    /*!
     * \brief Evalúa una habilidad de oponente sobre un personaje.
     * \param personaje Puntero al personaje.
     */
    void evaluaHabilidadOponente(ActorPersonaje *personaje);

    /*!
     * \brief Ejecuta una habilidad de oponente.
     */
    void efectuaHabilidadOponente();

    /*!
     * \brief Calcula una habilidad de oponente (asincrónica).
     * \param tiempo Referencia al tiempo de cálculo.
     */
    void calculaHabilidadOponente(unir2d::Tiempo &tiempo);

    /*!
     * \brief Revierte una habilidad de oponente.
     */
    void revierteHabilidadOponente();

    /*!
     * \brief Evalúa una habilidad de área por índice.
     * \param indice_habilidad Índice de la habilidad.
     */
    void evaluaHabilidadArea(int indice_habilidad);

    /*!
     * \brief Evalúa una habilidad de área sobre una celda.
     * \param celda Coordenada de la celda.
     */
    void evaluaHabilidadArea(Coord celda);

    /*!
     * \brief Ejecuta una habilidad de área.
     */
    void efectuaHabilidadArea();

    /*!
     * \brief Calcula una habilidad de área (asincrónica).
     * \param tiempo Referencia al tiempo de cálculo.
     */
    void calculaHabilidadArea(unir2d::Tiempo &tiempo);

    /*!
     * \brief Revierte una habilidad de área.
     */
    void revierteHabilidadArea();

    /*!
     * \brief Muestra la ayuda general.
     */
    void muestraAyuda();

    /*!
     * \brief Muestra la ayuda de un personaje.
     * \param personaje Puntero al personaje.
     */
    void muestraAyuda(ActorPersonaje *personaje);

    /*!
     * \brief Muestra la ayuda del actuante.
     */
    void muestraAyudaActuante();

    /*!
     * \brief Sube en la ayuda.
     */
    void subeAyuda();

    /*!
     * \brief Baja en la ayuda.
     */
    void bajaAyuda();

    /*!
     * \brief Oculta la ayuda.
     */
    void ocultaAyuda();

protected:
    /*!
     * \brief Constructor protegido. Inicializa el modo de juego común con el juego y los estados.
     * \param juego Puntero al juego.
     * \param estado Referencia al estado actual.
     * \param estado_previo Referencia al estado previo.
     */
    explicit ModoJuegoComun(JuegoMesaBase *juego, EstadoJuegoComun &estado, EstadoJuegoComun &estado_previo);

    /*!
     * \brief Escribe el estado actual (para depuración).
     */
    virtual void escribeEstado();

    // --- Métodos y utilidades para depuración ---

    /*!
     * \enum SimboloValida
     * \brief Símbolos para la validación de atributos y estados.
     */
    enum SimboloValida {
        NO, SI,
        NINGUNO, UNO, AMBOS,
        NULO, ASIGNADO,
        CERO, VARIOS,
        DESPLAZAM, HABILIDAD,
        SIMPLE, OPONENTE, AREA,
        VACIO, NO_VACIO,
        ignora
    };

    /*!
     * \brief Devuelve el nombre del módulo para depuración.
     */
    virtual const string nombreModulo();

    /*!
     * \brief Valida que el estado actual coincida con los estados dados.
     * \param estados Lista de estados válidos.
     */
    void validaEstado(const std::initializer_list<int> &estados);

    /*!
     * \brief Valida que la condición y el estado coincidan con los estados dados.
     * \param coincide Condición booleana.
     * \param estados Lista de estados válidos.
     */
    void validaEstado(bool coincide, const std::initializer_list<int> &estados);

    /*!
     * \brief Valida los atributos del modo de juego (debe ser implementado por derivadas).
     */
    virtual void validaAtributos() = 0;

    /*!
     * \brief Valida los atributos y estados del modo de juego.
     */
    virtual void valida(
        SimboloValida simbolo_equipo_inicial,
        SimboloValida simbolo_equipo_actual,
        SimboloValida simbolo_elegidos,
        SimboloValida simbolo_atacante_,
        SimboloValida simbolo_agotado,
        SimboloValida simbolo_vivo,
        SimboloValida simbolo_modo_accion,
        SimboloValida simbolo_etapas_camino,
        SimboloValida simbolo_habilidad,
        SimboloValida simbolo_tipo_accion,
        SimboloValida simbolo_oponente_,
        SimboloValida simbolo_area_celdas);

    /*!
     * \brief Informa del proceso actual (para depuración).
     * \param metodo Nombre del método.
     */
    void informaProceso(const string &metodo);

    /*!
     * \brief Aserta una condición sobre un atributo.
     * \param condicion Condición a comprobar.
     * \param atributo Nombre del atributo.
     * \param simbolo Símbolo de validación.
     */
    static void aserta(bool condicion, const string &atributo, SimboloValida simbolo);

    /*!
     * \brief Lanza una excepción con información del método y la excepción capturada.
     * \param metodo Nombre del método.
     * \param excepcion Excepción capturada.
     */
    void excepciona(const string &metodo, const std::exception &excepcion);

private:
    EstadoJuegoComun &estado_;
    EstadoJuegoComun &estado_previo_;
    static constexpr double segundos_calculo = 1.0;
};


}



