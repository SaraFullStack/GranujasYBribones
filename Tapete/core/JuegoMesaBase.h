#pragma once

#include "tapete.h"
#include "../ui/IntroJuegoImagen.h"

namespace tapete {

    enum class EstadoIntro {
        Logo,
        Imagen0,
        Imagen1,
        Imagen2,
        Imagen3,
        Imagen4,
        Imagen5,
        Imagen6,
        Imagen7,
        Imagen8,
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

        // Métodos de configuración interna
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

        // Hooks puros que debe implementar cada juego concreto
        virtual void preparaTablero() = 0;
        virtual void preparaPersonajes() = 0;
        virtual void preparaHabilidades() = 0;
        virtual void preparaTiposEstadisticas() = 0;
        virtual void agregaHabilidadesPersonajes() = 0;
        virtual void agregaEstadisticasPersonajes() = 0;
        virtual void agregaEstadisticasHabilidades() = 0;
        virtual void preparaSistemaAtaque() = 0;
        virtual void configuraJuego() = 0;

    private:
        // carpeta común de assets
        static std::string carpeta_activos_comun;

        // --- Secuencia de intro ---
        EstadoIntro       estado_intro_{ EstadoIntro::Logo };
        unir2d::Tiempo* cronometro_intro_{ nullptr };
        unir2d::Sonido* musica_intro_{ nullptr };

        IntroJuegoImagen* img_intro0_{ nullptr };
        IntroJuegoImagen* img_intro1_{ nullptr };
        IntroJuegoImagen* img_intro2_{ nullptr };
        IntroJuegoImagen* img_intro3_{ nullptr };
        IntroJuegoImagen* img_intro4_{ nullptr };
        IntroJuegoImagen* img_intro5_{ nullptr };
        IntroJuegoImagen* img_intro6_{ nullptr };
        IntroJuegoImagen* img_intro7_{ nullptr };
        IntroJuegoImagen* img_intro8_{ nullptr };

        const double      dur_total_intro_{ 29.0 };              // 29 segundos en total
        double            tiempo_por_img_{ dur_total_intro_ / 9.0 }; // ≈3.22 s por imagen
        int               currentIntroIdx_{ 0 };                 // 0..8 → imagenes, 9 = fin

        // --- Actores del juego ---
        ActorTablero* tablero_{ nullptr };
        std::vector<ActorPersonaje*>           personajes_{};
        std::vector<ActorPersonaje*>           personajes_izqrd{}, personajes_derch{};
        std::vector<Habilidad*>                habilidades_{};
        std::vector<TipoAtaque*>               ataques_{};
        std::vector<TipoDefensa*>              defensas_{};
        std::vector<TipoDano*>                 danos_{};
        ActorMusica* musica_{ nullptr };
        std::vector<ActorObjetoRecolectable*>  objetos_{};
        std::vector<std::wstring>              nombres_{};
        std::wstring                           curso_{};

        // Validación y sistema de eventos
        ValidacionJuego     valida_{ this };
        SucesosJuegoComun* sucesos_{ nullptr };
        ModoJuegoBase* modo_{ nullptr };
        SistemaAtaque       ataque_{ this };
        unir2d::Tiempo      tiempo_calculo{};

        // Helpers internos
        void regionVentana(Vector& pos, Vector& tam) const override;
        void controlTeclado();
        void controlTiempo();
    };

} // namespace tapete
