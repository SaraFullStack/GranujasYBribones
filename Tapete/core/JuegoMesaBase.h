// JuegoMesaBase.h
#pragma once

#include "tapete.h"
#include "../ui/IntroJuegoImagen.h"
#include <vector>

namespace tapete
{

    enum class EstadoIntro
    {
        Logo,    ///< img_intro0_
        Imagen0, ///< img_intro1_
        Imagen1, ///< img_intro2_
        Imagen2, ///< img_intro3_
        Imagen3, ///< img_intro4_
        Imagen4, ///< img_intro5_
        Imagen5, ///< img_intro6_
        Imagen6, ///< img_intro7_
        Imagen7, ///< img_intro8_
        Imagen8, ///< última: tesoro.png
        Fin
    };

    class JuegoMesaBase : public unir2d::JuegoBase
    {
    public:
        /*!
         * \brief Obtiene la ruta de la carpeta de activos compartidos.
         * \return Ruta de la carpeta de activos.
         */
        static const std::string &carpetaActivos();

        /*!
         * \brief Devuelve el tablero del juego.
         * \return Puntero al tablero.
         */
        ActorTablero *tablero();

        /*!
         * \brief Devuelve la lista de personajes.
         * \return Vector de punteros a personajes.
         */
        const std::vector<ActorPersonaje *> &personajes() const;

        /*!
         * \brief Devuelve los personajes de un lado específico del tablero.
         * \param lado Lado del tablero.
         * \return Vector de punteros a personajes.
         */
        const std::vector<ActorPersonaje *> &personajes(LadoTablero lado) const;

        /*!
         * \brief Devuelve la lista de habilidades disponibles.
         * \return Vector de punteros a habilidades.
         */
        const std::vector<Habilidad *> &habilidades() const;

        /*!
         * \brief Devuelve los tipos de ataque registrados.
         * \return Vector de punteros a tipos de ataque.
         */
        const std::vector<TipoAtaque *> &ataques() const;

        /*!
         * \brief Devuelve los tipos de defensa registrados.
         * \return Vector de punteros a tipos de defensa.
         */
        const std::vector<TipoDefensa *> &defensas() const;

        /*!
         * \brief Devuelve los tipos de daño registrados.
         * \return Vector de punteros a tipos de daño.
         */
        const std::vector<TipoDano *> &danos() const;

        /*!
         * \brief Accede al gestor de música.
         * \return Puntero al actor de música.
         */
        ActorMusica *musica();

        /*!
         * \brief Devuelve los nombres de los alumnos.
         * \return Vector de nombres.
         */
        const std::vector<std::wstring> &nombresAlumnos() const;

        /*!
         * \brief Devuelve el curso académico actual.
         * \return Cadena con el curso académico.
         */
        const std::wstring &cursoAcademico() const;

        /*!
         * \brief Accede al sistema de sucesos del juego.
         * \return Puntero al sistema de sucesos.
         */
        SucesosJuegoComun *sucesos();

        /*!
         * \brief Accede al modo de juego activo.
         * \return Puntero al modo de juego.
         */
        ModoJuegoBase *modo();

        /*!
         * \brief Accede al sistema de ataque.
         * \return Referencia al sistema de ataque.
         */
        SistemaAtaque &sistemaAtaque();

        /*!
         * \brief Accede al tiempo de cálculo interno.
         * \return Referencia al objeto de tiempo.
         */
        unir2d::Tiempo &tiempoCalculo();

        /*!
         * \brief Agrega un objeto recolectable al juego.
         * \param obj Puntero al objeto recolectable.
         */
        void agregaObjeto(ActorObjetoRecolectable *obj);

        /*!
         * \brief Evento virtual que se ejecuta después de mover un personaje.
         * \param personaje Puntero al personaje que se ha movido.
         */
        virtual void despuesDeMover(ActorPersonaje *personaje) {}

    protected:
        /*!
         * \brief Destructor protegido.
         */
        ~JuegoMesaBase();

        /*!
         * \brief Inicializa el juego.
         */
        void inicia() override;

        /*!
         * \brief Finaliza el juego.
         */
        void termina() override;

        /*!
         * \brief Lógica antes de la actualización por frame.
         * \param tiempo_seg Tiempo en segundos.
         */
        void preactualiza(double tiempo_seg) override;

        /*!
         * \brief Lógica después de la actualización por frame.
         * \param tiempo_seg Tiempo en segundos.
         */
        void posactualiza(double tiempo_seg) override;

        /*!
         * \brief Configura el tablero; debe implementarse en derivadas.
         */
        virtual void preparaTablero() = 0;

        /*!
         * \brief Configura los personajes; debe implementarse en derivadas.
         */
        virtual void preparaPersonajes() = 0;

        /*!
         * \brief Configura las habilidades; debe implementarse en derivadas.
         */
        virtual void preparaHabilidades() = 0;

        /*!
         * \brief Configura los tipos de estadística; debe implementarse en derivadas.
         */
        virtual void preparaTiposEstadisticas() = 0;

        /*!
         * \brief Asigna habilidades a personajes; debe implementarse en derivadas.
         */
        virtual void agregaHabilidadesPersonajes() = 0;

        /*!
         * \brief Asigna estadísticas a personajes; debe implementarse en derivadas.
         */
        virtual void agregaEstadisticasPersonajes() = 0;

        /*!
         * \brief Asigna estadísticas a habilidades; debe implementarse en derivadas.
         */
        virtual void agregaEstadisticasHabilidades() = 0;

        /*!
         * \brief Configura el sistema de ataque; debe implementarse en derivadas.
         */
        virtual void preparaSistemaAtaque() = 0;

        /*!
         * \brief Configuraciones adicionales del juego; debe implementarse en derivadas.
         */
        virtual void configuraJuego() = 0;

        /*!
         * \brief Agrega el tablero a la gestión interna.
         * \param valor Puntero al tablero.
         */
        void agregaTablero(ActorTablero *valor);

        /*!
         * \brief Agrega un personaje a la gestión interna.
         * \param elemento Puntero al personaje.
         */
        void agregaPersonaje(ActorPersonaje *elemento);

        /*!
         * \brief Agrega una habilidad a la gestión interna.
         * \param elemento Puntero a la habilidad.
         */
        void agregaHabilidad(Habilidad *elemento);

        /*!
         * \brief Agrega un tipo de ataque a la gestión interna.
         * \param elemento Puntero al tipo de ataque.
         */
        void agregaAtaque(TipoAtaque *elemento);

        /*!
         * \brief Agrega un tipo de defensa a la gestión interna.
         * \param elemento Puntero al tipo de defensa.
         */
        void agregaDefensa(TipoDefensa *elemento);

        /*!
         * \brief Agrega un tipo de daño a la gestión interna.
         * \param elemento Puntero al tipo de daño.
         */
        void agregaDano(TipoDano *elemento);

        /*!
         * \brief Agrega un grado de efectividad al sistema de ataque.
         * \param elemento Puntero al grado de efectividad.
         */
        void agregaEfectividad(GradoEfectividad *elemento);

        /*!
         * \brief Agrega música al juego.
         * \param valor Puntero al actor de música.
         */
        void agregaMusica(ActorMusica *valor);

        /*!
         * \brief Configura sucesos y modo de juego.
         * \param sucesos Puntero al sistema de sucesos.
         * \param modo Puntero al modo de juego.
         */
        void configura(SucesosJuegoComun *sucesos, ModoJuegoBase *modo);

        /*!
         * \brief Agrega el nombre de un alumno.
         * \param nombre Nombre del alumno.
         */
        void agregaNombreAlumno(const std::wstring &nombre);

        /*!
         * \brief Establece el curso académico.
         * \param curso Cadena con el curso académico.
         */
        void indicaCursoAcademico(const std::wstring &curso);

    private:
        static std::string carpeta_activos_comun;

        std::vector<IntroJuegoImagen *> imgs_;        ///< img_intro0_ … img_intro8_
        IntroJuegoImagen *img_actual_intro_{nullptr}; ///< imagen actual de la intro
        int currentIntroIdx_{0};                      ///< índice de la intro
        bool espacio_pulsado_intro_{false};           ///< estado de tecla espacio
        unir2d::Sonido *musica_intro_{nullptr};       ///< música de la intro

        EstadoIntro estado_intro_{EstadoIntro::Logo}; ///< estado actual de la intro

        ActorTablero *tablero_{nullptr};
        std::vector<ActorPersonaje *> personajes_;
        std::vector<ActorPersonaje *> personajes_izqrd_, personajes_derch_;
        std::vector<Habilidad *> habilidades_;
        std::vector<TipoAtaque *> ataques_;
        std::vector<TipoDefensa *> defensas_;
        std::vector<TipoDano *> danos_;
        ActorMusica *musica_{nullptr};
        std::vector<ActorObjetoRecolectable *> objetos_;
        std::vector<std::wstring> nombres_;
        std::wstring curso_;

        ValidacionJuego valida_{this};
        SucesosJuegoComun *sucesos_{nullptr};
        ModoJuegoBase *modo_{nullptr};
        SistemaAtaque ataque_{this};     ///< sistema de ataque del juego
        unir2d::Tiempo tiempo_calculo{}; ///< tiempo interno para cálculos

        /*!
         * \brief Ajusta la región de la ventana según la posición y tamaño.
         * \param pos Posición.
         * \param tam Tamaño.
         */
        void regionVentana(Vector &pos, Vector &tam) const override;

        /*!
         * \brief Procesa la entrada de teclado.
         */
        void controlTeclado();

        /*!
         * \brief Procesa eventos de tiempo.
         */
        void controlTiempo();
    };

} // namespace tapete
