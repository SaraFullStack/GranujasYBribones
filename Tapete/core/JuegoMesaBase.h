// JuegoMesaBase.h
#pragma once

#include "tapete.h"
#include "../ui/IntroJuegoImagen.h"
#include <vector>

namespace tapete {

    enum class EstadoIntro {
        Logo,      // img_intro0_
        Imagen0,   // img_intro1_
        Imagen1,   // img_intro2_
        Imagen2,   // img_intro3_
        Imagen3,   // img_intro4_
        Imagen4,   // img_intro5_
        Imagen5,   // img_intro6_
        Imagen6,   // img_intro7_
        Imagen7,   // img_intro8_
        Imagen8,   // última: tesoro.png
        Fin
    };

    class JuegoMesaBase : public unir2d::JuegoBase {
    public:
        static const std::string& carpetaActivos();

        ActorTablero* tablero();
        const std::vector<ActorPersonaje*>& personajes() const;
        const std::vector<ActorPersonaje*>& personajes(LadoTablero lado) const;
        const std::vector<Habilidad*>& habilidades() const;
        const std::vector<TipoAtaque*>& ataques() const;
        const std::vector<TipoDefensa*>& defensas() const;
        const std::vector<TipoDano*>& danos() const;
        ActorMusica* musica();
        const std::vector<std::wstring>& nombresAlumnos() const;
        const std::wstring& cursoAcademico() const;
        SucesosJuegoComun* sucesos();
        ModoJuegoBase* modo();
        SistemaAtaque& sistemaAtaque();
        unir2d::Tiempo& tiempoCalculo();

        void agregaObjeto(ActorObjetoRecolectable* obj);
        virtual void despuesDeMover(ActorPersonaje* personaje) {}

    protected:
        ~JuegoMesaBase();
        void inicia() override;
        void termina() override;
        void preactualiza(double tiempo_seg) override;
        void posactualiza(double tiempo_seg) override;

        // — Hooks que implementará cada juego concreto —
        virtual void preparaTablero() = 0;
        virtual void preparaPersonajes() = 0;
        virtual void preparaHabilidades() = 0;
        virtual void preparaTiposEstadisticas() = 0;
        virtual void agregaHabilidadesPersonajes() = 0;
        virtual void agregaEstadisticasPersonajes() = 0;
        virtual void agregaEstadisticasHabilidades() = 0;
        virtual void preparaSistemaAtaque() = 0;
        virtual void configuraJuego() = 0;

        // Métodos internos de configuración
        void agregaTablero(ActorTablero* valor);
        void agregaPersonaje(ActorPersonaje* elemento);
        void agregaHabilidad(Habilidad* elemento);
        void agregaAtaque(TipoAtaque* elemento);
        void agregaDefensa(TipoDefensa* elemento);
        void agregaDano(TipoDano* elemento);
        void agregaEfectividad(GradoEfectividad* elemento);
        void agregaMusica(ActorMusica* valor);
        void configura(SucesosJuegoComun* sucesos, ModoJuegoBase* modo);
        void agregaNombreAlumno(const std::wstring& nombre);
        void indicaCursoAcademico(const std::wstring& curso);

    private:
        // carpeta de assets
        static std::string carpeta_activos_comun;

        // — Intro controlada por espacio —
        std::vector<IntroJuegoImagen*> imgs_;  // img_intro0_ … img_intro8_
        IntroJuegoImagen* img_actual_intro_{ nullptr };
        int                             currentIntroIdx_{ 0 };
        bool                            espacio_pulsado_intro_{ false };
        unir2d::Sonido* musica_intro_{ nullptr };

        EstadoIntro                     estado_intro_{ EstadoIntro::Logo };

        // — Estado del juego tras intro —
        ActorTablero* tablero_{ nullptr };
        std::vector<ActorPersonaje*>           personajes_;
        std::vector<ActorPersonaje*>           personajes_izqrd_, personajes_derch_;
        std::vector<Habilidad*>                habilidades_;
        std::vector<TipoAtaque*>               ataques_;
        std::vector<TipoDefensa*>              defensas_;
        std::vector<TipoDano*>                 danos_;
        ActorMusica* musica_{ nullptr };
        std::vector<ActorObjetoRecolectable*>  objetos_;
        std::vector<std::wstring>              nombres_;
        std::wstring                           curso_;

        // — Validación y eventos —
        ValidacionJuego     valida_{ this };
        SucesosJuegoComun* sucesos_{ nullptr };
        ModoJuegoBase* modo_{ nullptr };
        SistemaAtaque       ataque_{ this };
        unir2d::Tiempo      tiempo_calculo{};

        // helpers
        void regionVentana(Vector& pos, Vector& tam) const override;
        void controlTeclado();
        void controlTiempo();
    };

} // namespace tapete
