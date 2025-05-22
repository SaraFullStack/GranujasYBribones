// JuegoMesaBase.cpp
#include "tapete.h"
#include "JuegoMesaBase.h"

namespace tapete {

    // carpeta de imágenes
    std::string JuegoMesaBase::carpeta_activos_comun{ "../Tapete/Assets/images/" };

    const std::string& JuegoMesaBase::carpetaActivos() {
        return carpeta_activos_comun;
    }

    JuegoMesaBase::~JuegoMesaBase() {
        validaVacio();
        delete modo_;    modo_ = nullptr;
        delete sucesos_; sucesos_ = nullptr;
    }

    ActorTablero* JuegoMesaBase::tablero() { return tablero_; }
    const std::vector<ActorPersonaje*>& JuegoMesaBase::personajes() const { return personajes_; }
    const std::vector<ActorPersonaje*>& JuegoMesaBase::personajes(LadoTablero lado) const {
        return (lado == LadoTablero::Izquierda) ? personajes_izqrd_ : personajes_derch_;
    }
    const std::vector<Habilidad*>& JuegoMesaBase::habilidades() const { return habilidades_; }
    const std::vector<TipoAtaque*>& JuegoMesaBase::ataques() const { return ataques_; }
    const std::vector<TipoDefensa*>& JuegoMesaBase::defensas() const { return defensas_; }
    const std::vector<TipoDano*>& JuegoMesaBase::danos() const { return danos_; }
    ActorMusica* JuegoMesaBase::musica() { return musica_; }
    const std::vector<std::wstring>& JuegoMesaBase::nombresAlumnos() const { return nombres_; }
    const std::wstring& JuegoMesaBase::cursoAcademico() const { return curso_; }
    SucesosJuegoComun* JuegoMesaBase::sucesos() { return sucesos_; }
    ModoJuegoBase* JuegoMesaBase::modo() { return modo_; }
    SistemaAtaque& JuegoMesaBase::sistemaAtaque() { return ataque_; }
    unir2d::Tiempo& JuegoMesaBase::tiempoCalculo() { return tiempo_calculo; }

    void JuegoMesaBase::agregaObjeto(ActorObjetoRecolectable* obj) {
        if (obj) objetos_.push_back(obj);
    }

    void JuegoMesaBase::regionVentana(Vector& pos, Vector& tam) const {
        pos = Vector{ 4,4 };
        tam = PresenciaTablero::tamanoTablero;
    }

    void JuegoMesaBase::inicia() {
        // Validaciones + hooks
        valida_.Construccion();           preparaTablero();          valida_.Tablero();
        preparaPersonajes();              valida_.Personajes();
        preparaHabilidades();             valida_.Habilidades();
        preparaTiposEstadisticas();       valida_.TiposEstadisticas();
        agregaHabilidadesPersonajes();    valida_.HabilidadesPersonajes();
        agregaEstadisticasPersonajes();   valida_.EstadisticasPersonajes();
        agregaEstadisticasHabilidades();  valida_.EstadisticasHabilidades();
        preparaSistemaAtaque();           valida_.SistemaAtaque();
        configuraJuego();                 valida_.ConfiguraJuego();

        // Carga todas las imágenes en el vector
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "estudio.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "portada.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "mover.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "trampa.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "arreglo.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "canonazo.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "embestida.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "abordaje.png"));
        imgs_.push_back(new IntroJuegoImagen(carpeta_activos_comun + "tesoro.png"));

        // empezamos por la primera
        currentIntroIdx_ = 0;
        img_actual_intro_ = imgs_[0];
        agregaActor(img_actual_intro_);

        // opción: suena la música de intro
        musica_intro_ = new unir2d::Sonido{};
        musica_intro_->abre("../Tapete/Assets/sonidos/intro.ogg");
        musica_intro_->suena();

        estado_intro_ = EstadoIntro::Logo;
        espacio_pulsado_intro_ = false;
    }

    void JuegoMesaBase::posactualiza(double) {
        if (estado_intro_ != EstadoIntro::Fin) {
            // detectamos edge de tecla espacio
            bool pulsado = unir2d::Teclado::pulsando(unir2d::Tecla::espacio);
            if (pulsado && !espacio_pulsado_intro_) {
                // quitamos la imagen actual
                extraeActor(img_actual_intro_);
                currentIntroIdx_++;

                if (currentIntroIdx_ < (int)imgs_.size()) {
                    // mostramos la siguiente
                    img_actual_intro_ = imgs_[currentIntroIdx_];
                    agregaActor(img_actual_intro_);
                    estado_intro_ = static_cast<EstadoIntro>(currentIntroIdx_);
                }
                else {
                    // ya no quedan: fin de intro
                    estado_intro_ = EstadoIntro::Fin;
                }
            }
            espacio_pulsado_intro_ = pulsado;

            if (estado_intro_ == EstadoIntro::Fin) {
                // limpiamos imágenes y música de intro
                musica_intro_->para();
                delete musica_intro_; musica_intro_ = nullptr;
                for (auto* img : imgs_) delete img;
                imgs_.clear();

                // arrancamos el juego
                agregaActor(tablero_);
                for (auto* p : personajes_)  agregaActor(p);
                agregaActor(musica_);
                for (auto* o : objetos_)     agregaActor(o);
                sucesos_->iniciado();
            }
            return;
        }

        // después de la intro: lógica normal
        controlTeclado();
        controlTiempo();
    }

    void JuegoMesaBase::termina() {
        sucesos_->terminado();
        sucesos_ = nullptr;
        for (auto* a : ataques_)   delete a; ataques_.clear();
        for (auto* d : defensas_)  delete d; defensas_.clear();
        for (auto* d : danos_)      delete d; danos_.clear();
        extraeActores();
        for (auto* h : habilidades_) delete h;  habilidades_.clear();
        delete musica_; musica_ = nullptr;
        for (auto* p : personajes_)  delete p;  personajes_.clear();
        personajes_izqrd_.clear();
        personajes_derch_.clear();
        delete tablero_; tablero_ = nullptr;
    }

    void JuegoMesaBase::preactualiza(double) {
        // no-op
    }

    void JuegoMesaBase::controlTeclado() {
        if (unir2d::Teclado::pulsando(unir2d::Tecla::espacio)) sucesos_->pulsadoEspacio();
        else if (unir2d::Teclado::pulsando(unir2d::Tecla::escape)) sucesos_->pulsadoEscape();
        else if (unir2d::Teclado::pulsando(unir2d::Tecla::arriba))  sucesos_->pulsadoArriba();
        else if (unir2d::Teclado::pulsando(unir2d::Tecla::abajo))  sucesos_->pulsadoAbajo();
    }

    void JuegoMesaBase::controlTiempo() {
        if (tiempo_calculo.iniciado())
            sucesos_->alarmaCalculo(tiempo_calculo);
    }

    // — Métodos de configuración interna —
    void JuegoMesaBase::agregaTablero(ActorTablero* v) { tablero_ = v; }
    void JuegoMesaBase::agregaPersonaje(ActorPersonaje* e) {
        if (!e) return;
        e->ponIndice((int)personajes_.size());
        personajes_.push_back(e);
        if (e->ladoTablero() == LadoTablero::Izquierda) personajes_izqrd_.push_back(e);
        else                                          personajes_derch_.push_back(e);
    }
    void JuegoMesaBase::agregaHabilidad(Habilidad* e) {
        if (!e) return;
        e->ponIndice((int)habilidades_.size());
        habilidades_.push_back(e);
    }
    void JuegoMesaBase::agregaAtaque(TipoAtaque* e) {
        if (!e) return;
        e->ponIndice((int)ataques_.size());
        ataques_.push_back(e);
    }
    void JuegoMesaBase::agregaDefensa(TipoDefensa* e) {
        if (!e) return;
        e->ponIndice((int)defensas_.size());
        defensas_.push_back(e);
    }
    void JuegoMesaBase::agregaDano(TipoDano* e) {
        if (!e) return;
        e->ponIndice((int)danos_.size());
        danos_.push_back(e);
    }
    void JuegoMesaBase::agregaEfectividad(GradoEfectividad* e) { ataque_.agregaEfectividad(e); }
    void JuegoMesaBase::agregaMusica(ActorMusica* m) { musica_ = m; }
    void JuegoMesaBase::configura(SucesosJuegoComun* s, ModoJuegoBase* m) { sucesos_ = s; modo_ = m; }
    void JuegoMesaBase::agregaNombreAlumno(const std::wstring& n) { nombres_.push_back(n); }
    void JuegoMesaBase::indicaCursoAcademico(const std::wstring& c) { curso_ = c; }

} // namespace tapete
