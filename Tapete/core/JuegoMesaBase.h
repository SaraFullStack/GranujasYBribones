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
        /// <summary>Obtiene la ruta de la carpeta de activos compartidos.</summary>
        static const std::string &carpetaActivos();

        /// <summary>Devuelve el tablero del juego.</summary>
        ActorTablero *tablero();
        /// <summary>Devuelve la lista de personajes.</summary>
        const std::vector<ActorPersonaje *> &personajes() const;
        /// <summary>Devuelve los personajes de un lado específico del tablero.</summary>
        const std::vector<ActorPersonaje *> &personajes(LadoTablero lado) const;
        /// <summary>Devuelve la lista de habilidades disponibles.</summary>
        const std::vector<Habilidad *> &habilidades() const;
        /// <summary>Devuelve los tipos de ataque registrados.</summary>
        const std::vector<TipoAtaque *> &ataques() const;
        /// <summary>Devuelve los tipos de defensa registrados.</summary>
        const std::vector<TipoDefensa *> &defensas() const;
        /// <summary>Devuelve los tipos de daño registrados.</summary>
        const std::vector<TipoDano *> &danos() const;
        /// <summary>Accede al gestor de música.</summary>
        ActorMusica *musica();
        /// <summary>Devuelve los nombres de los alumnos.</summary>
        const std::vector<std::wstring> &nombresAlumnos() const;
        /// <summary>Devuelve el curso académico actual.</summary>
        const std::wstring &cursoAcademico() const;
        /// <summary>Accede al sistema de sucesos del juego.</summary>
        SucesosJuegoComun *sucesos();
        /// <summary>Accede al modo de juego activo.</summary>
        ModoJuegoBase *modo();
        /// <summary>Accede al sistema de ataque.</summary>
        SistemaAtaque &sistemaAtaque();
        /// <summary>Accede al tiempo de cálculo interno.</summary>
        unir2d::Tiempo &tiempoCalculo();

        /// <summary>Agrega un objeto recolectable al juego.</summary>
        void agregaObjeto(ActorObjetoRecolectable *obj);
        /// <summary>Evento virtual que se ejecuta después de mover un personaje.</summary>
        virtual void despuesDeMover(ActorPersonaje *personaje) {}

    protected:
        /// <summary>Destructor protegido.</summary>
        ~JuegoMesaBase();
        /// <summary>Inicializa el juego.</summary>
        void inicia() override;
        /// <summary>Finaliza el juego.</summary>
        void termina() override;
        /// <summary>Lógica antes de la actualización por frame.</summary>
        void preactualiza(double tiempo_seg) override;
        /// <summary>Lógica después de la actualización por frame.</summary>
        void posactualiza(double tiempo_seg) override;

        /// <summary>Configura el tablero; debe implementarse en derivadas.</summary>
        virtual void preparaTablero() = 0;
        /// <summary>Configura los personajes; debe implementarse en derivadas.</summary>
        virtual void preparaPersonajes() = 0;
        /// <summary>Configura las habilidades; debe implementarse en derivadas.</summary>
        virtual void preparaHabilidades() = 0;
        /// <summary>Configura los tipos de estadística; debe implementarse en derivadas.</summary>
        virtual void preparaTiposEstadisticas() = 0;
        /// <summary>Asigna habilidades a personajes; debe implementarse en derivadas.</summary>
        virtual void agregaHabilidadesPersonajes() = 0;
        /// <summary>Asigna estadísticas a personajes; debe implementarse en derivadas.</summary>
        virtual void agregaEstadisticasPersonajes() = 0;
        /// <summary>Asigna estadísticas a habilidades; debe implementarse en derivadas.</summary>
        virtual void agregaEstadisticasHabilidades() = 0;
        /// <summary>Configura el sistema de ataque; debe implementarse en derivadas.</summary>
        virtual void preparaSistemaAtaque() = 0;
        /// <summary>Configuraciones adicionales del juego; debe implementarse en derivadas.</summary>
        virtual void configuraJuego() = 0;

        /// <summary>Agrega el tablero a la gestión interna.</summary>
        void agregaTablero(ActorTablero *valor);
        /// <summary>Agrega un personaje a la gestión interna.</summary>
        void agregaPersonaje(ActorPersonaje *elemento);
        /// <summary>Agrega una habilidad a la gestión interna.</summary>
        void agregaHabilidad(Habilidad *elemento);
        /// <summary>Agrega un tipo de ataque a la gestión interna.</summary>
        void agregaAtaque(TipoAtaque *elemento);
        /// <summary>Agrega un tipo de defensa a la gestión interna.</summary>
        void agregaDefensa(TipoDefensa *elemento);
        /// <summary>Agrega un tipo de daño a la gestión interna.</summary>
        void agregaDano(TipoDano *elemento);
        /// <summary>Agrega un grado de efectividad al sistema de ataque.</summary>
        void agregaEfectividad(GradoEfectividad *elemento);
        /// <summary>Agrega música al juego.</summary>
        void agregaMusica(ActorMusica *valor);
        /// <summary>Configura sucesos y modo de juego.</summary>
        void configura(SucesosJuegoComun *sucesos, ModoJuegoBase *modo);
        /// <summary>Agrega el nombre de un alumno.</summary>
        void agregaNombreAlumno(const std::wstring &nombre);
        /// <summary>Establece el curso académico.</summary>
        void indicaCursoAcademico(const std::wstring &curso);

    private:
        static std::string carpeta_activos_comun;

        std::vector<IntroJuegoImagen *> imgs_;               ///< img_intro0_ … img_intro8_
        IntroJuegoImagen *img_actual_intro_{nullptr};        ///< imagen actual de la intro
        int currentIntroIdx_{0};                             ///< índice de la intro
        bool espacio_pulsado_intro_{false};                  ///< estado de tecla espacio
        unir2d::Sonido *musica_intro_{nullptr};              ///< música de la intro

        EstadoIntro estado_intro_{EstadoIntro::Logo};        ///< estado actual de la intro

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
        SistemaAtaque ataque_{this};                        ///< sistema de ataque del juego
        unir2d::Tiempo tiempo_calculo{};                     ///< tiempo interno para cálculos

        /// <summary>Ajusta la región de la ventana según la posición y tamaño.</summary>
        void regionVentana(Vector &pos, Vector &tam) const override;
        /// <summary>Procesa la entrada de teclado.</summary>
        void controlTeclado();
        /// <summary>Procesa eventos de tiempo.</summary>
        void controlTiempo();
    };

} // namespace tapete
