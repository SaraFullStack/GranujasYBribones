// Archivo: JuegoMesaBase.cpp  (versión 2.1 Abril-2025)
#include "tapete.h"
#include "JuegoMesaBase.h"

namespace tapete
{
    string JuegoMesaBase::carpeta_activos_comun{"../Tapete/Assets/images/"};

    // <<< AÑADE ESTO >>>
    const std::string &JuegoMesaBase::carpetaActivos()
    {
        return carpeta_activos_comun;
    }

    JuegoMesaBase::~JuegoMesaBase()
    {
        validaVacio();
        delete modo_;
        modo_ = nullptr;
        delete sucesos_;
        sucesos_ = nullptr;
    }
    

    ActorTablero *JuegoMesaBase::tablero() { return tablero_; }
    const std::vector<ActorPersonaje *> &JuegoMesaBase::personajes() const { return personajes_; }
    const std::vector<ActorPersonaje *> &JuegoMesaBase::personajes(LadoTablero lado) const
    {
        return (lado == LadoTablero::Izquierda) ? personajes_izqrd : personajes_derch;
    }
    const std::vector<Habilidad *> &JuegoMesaBase::habilidades() const { return habilidades_; }
    const std::vector<TipoAtaque *> &JuegoMesaBase::ataques() const { return ataques_; }
    const std::vector<TipoDefensa *> &JuegoMesaBase::defensas() const { return defensas_; }
    const std::vector<TipoDano *> &JuegoMesaBase::danos() const { return danos_; }
    ActorMusica *JuegoMesaBase::musica() { return musica_; }
    const std::vector<std::wstring> &JuegoMesaBase::nombresAlumnos() const { return nombres_; }
    const std::wstring &JuegoMesaBase::cursoAcademico() const { return curso_; }
    SucesosJuegoComun *JuegoMesaBase::sucesos() { return sucesos_; }
    ModoJuegoBase *JuegoMesaBase::modo() { return modo_; }
    SistemaAtaque &JuegoMesaBase::sistemaAtaque() { return ataque_; }
    unir2d::Tiempo &JuegoMesaBase::tiempoCalculo() { return tiempo_calculo; }

    void JuegoMesaBase::agregaObjeto(ActorObjetoRecolectable *obj)
    {
        if (obj)
            objetos_.push_back(obj);
    }

    void JuegoMesaBase::regionVentana(Vector &pos, Vector &tam) const
    {
        pos = Vector{4, 4};
        tam = PresenciaTablero::tamanoTablero;
    }

    // Inicia intro y retiene el arranque del juego
   void JuegoMesaBase::inicia() {
    // … validaciones y hooks previos siguen iguales …
    valida_.Construccion(); preparaTablero(); valida_.Tablero();
    preparaPersonajes();    valida_.Personajes();
    preparaHabilidades();   valida_.Habilidades();
    preparaTiposEstadisticas(); valida_.TiposEstadisticas();
    agregaHabilidadesPersonajes(); valida_.HabilidadesPersonajes();
    agregaEstadisticasPersonajes(); valida_.EstadisticasPersonajes();
    agregaEstadisticasHabilidades(); valida_.EstadisticasHabilidades();
    preparaSistemaAtaque(); valida_.SistemaAtaque();
    configuraJuego();       valida_.ConfiguraJuego();

    // ——— Carga 9 imágenes de intro ———
    img_intro0_ = new IntroJuegoImagen(carpeta_activos_comun + "estudio.png");
    img_intro1_ = new IntroJuegoImagen(carpeta_activos_comun + "portada.png");
    img_intro2_ = new IntroJuegoImagen(carpeta_activos_comun + "mover.png");
    img_intro3_ = new IntroJuegoImagen(carpeta_activos_comun + "trampa.png");
    img_intro4_ = new IntroJuegoImagen(carpeta_activos_comun + "arreglo.png");
    img_intro5_ = new IntroJuegoImagen(carpeta_activos_comun + "canonazo.png");
    img_intro6_ = new IntroJuegoImagen(carpeta_activos_comun + "embestida.png");
    img_intro7_ = new IntroJuegoImagen(carpeta_activos_comun + "abordaje.png");
    img_intro8_ = new IntroJuegoImagen(carpeta_activos_comun + "tesoro.png");
    // mostramos la primera
    agregaActor(img_intro0_);

    musica_intro_ = new unir2d::Sonido{};
    musica_intro_->abre("../Tapete/Assets/sonidos/intro.ogg");
    musica_intro_->suena();

    cronometro_intro_ = new unir2d::Tiempo{};
    cronometro_intro_->inicia();
    estado_intro_     = EstadoIntro::Logo;
}

void JuegoMesaBase::posactualiza(double tiempo_seg) {
    if (estado_intro_ != EstadoIntro::Fin) {
        double t = cronometro_intro_->segundos();
        EstadoIntro nuevo = EstadoIntro::Fin;

        if      (t <  1 * tiempo_por_img_) nuevo = EstadoIntro::Logo;
        else if (t <  2 * tiempo_por_img_) nuevo = EstadoIntro::Imagen0;
        else if (t <  3 * tiempo_por_img_) nuevo = EstadoIntro::Imagen1;
        else if (t <  4 * tiempo_por_img_) nuevo = EstadoIntro::Imagen2;
        else if (t <  5 * tiempo_por_img_) nuevo = EstadoIntro::Imagen3;
        else if (t <  6 * tiempo_por_img_) nuevo = EstadoIntro::Imagen4;
        else if (t <  7 * tiempo_por_img_) nuevo = EstadoIntro::Imagen5;
        else if (t <  8 * tiempo_por_img_) nuevo = EstadoIntro::Imagen6;
        else if (t <  9 * tiempo_por_img_) nuevo = EstadoIntro::Imagen7;
        else if (t < 10 * tiempo_por_img_) nuevo = EstadoIntro::Imagen8;

        if (nuevo != estado_intro_) {
            // eliminar la anterior
            if (estado_intro_ == EstadoIntro::Logo)       extraeActor(img_intro0_);
            else if (estado_intro_ == EstadoIntro::Imagen0) extraeActor(img_intro1_);
            else if (estado_intro_ == EstadoIntro::Imagen1) extraeActor(img_intro2_);
            else if (estado_intro_ == EstadoIntro::Imagen2) extraeActor(img_intro3_);
            else if (estado_intro_ == EstadoIntro::Imagen3) extraeActor(img_intro4_);
            else if (estado_intro_ == EstadoIntro::Imagen4) extraeActor(img_intro5_);
            else if (estado_intro_ == EstadoIntro::Imagen5) extraeActor(img_intro6_);
            else if (estado_intro_ == EstadoIntro::Imagen6) extraeActor(img_intro7_);
            else if (estado_intro_ == EstadoIntro::Imagen7) extraeActor(img_intro8_);
            // (no hay img_intro9_, así que Imagen8 sólo se limpia en Fin)

            // añadir la nueva (si no es FIN)
            if      (nuevo == EstadoIntro::Logo)    agregaActor(img_intro0_);
            else if (nuevo == EstadoIntro::Imagen0) agregaActor(img_intro1_);
            else if (nuevo == EstadoIntro::Imagen1) agregaActor(img_intro2_);
            else if (nuevo == EstadoIntro::Imagen2) agregaActor(img_intro3_);
            else if (nuevo == EstadoIntro::Imagen3) agregaActor(img_intro4_);
            else if (nuevo == EstadoIntro::Imagen4) agregaActor(img_intro5_);
            else if (nuevo == EstadoIntro::Imagen5) agregaActor(img_intro6_);
            else if (nuevo == EstadoIntro::Imagen6) agregaActor(img_intro7_);
            else if (nuevo == EstadoIntro::Imagen7) agregaActor(img_intro8_);

            estado_intro_ = nuevo;
        }

        if (estado_intro_ == EstadoIntro::Fin) {
            // Fin de la intro: limpieza
            musica_intro_->para();
            delete musica_intro_;    musica_intro_ = nullptr;
            delete cronometro_intro_; cronometro_intro_ = nullptr;
            delete img_intro0_; img_intro0_ = nullptr;
            delete img_intro1_; img_intro1_ = nullptr;
            delete img_intro2_; img_intro2_ = nullptr;
            delete img_intro3_; img_intro3_ = nullptr;
            delete img_intro4_; img_intro4_ = nullptr;
            delete img_intro5_; img_intro5_ = nullptr;
            delete img_intro6_; img_intro6_ = nullptr;
            delete img_intro7_; img_intro7_ = nullptr;
            delete img_intro8_; img_intro8_ = nullptr;

            // arrancar el juego
            agregaActor(tablero_);
            for (auto* p : personajes_) agregaActor(p);
            agregaActor(musica_);
            for (auto* o : objetos_)    agregaActor(o);
            sucesos_->iniciado();
        }

        return;  // salir antes de la lógica normal
    }

    // — lógica de juego tras la intro —
    controlTeclado();
    controlTiempo();
}

    // termina()
    void JuegoMesaBase::termina()
    {
        sucesos_->terminado();
        sucesos_ = nullptr;
        for (auto *tipo : ataques_)
            delete tipo;
        ataques_.clear();
        for (auto *tipo : defensas_)
            delete tipo;
        defensas_.clear();
        for (auto *tipo : danos_)
            delete tipo;
        danos_.clear();
        extraeActores();
        for (auto *hab : habilidades_)
            delete hab;
        habilidades_.clear();
        delete musica_;
        musica_ = nullptr;
        for (auto *p : personajes_)
            delete p;
        personajes_.clear();
        personajes_izqrd.clear();
        personajes_derch.clear();
        delete tablero_;
        tablero_ = nullptr;
    }

    // preactualiza: nada especial
    void JuegoMesaBase::preactualiza(double tiempo_seg)
    {
        // vacio
    }

    // control de teclado y tiempo para juego post-intro
    void JuegoMesaBase::controlTeclado()
    {
        if (unir2d::Teclado::pulsando(unir2d::Tecla::espacio))
            sucesos_->pulsadoEspacio();
        else if (unir2d::Teclado::pulsando(unir2d::Tecla::escape))
            sucesos_->pulsadoEscape();
        else if (unir2d::Teclado::pulsando(unir2d::Tecla::arriba))
            sucesos_->pulsadoArriba();
        else if (unir2d::Teclado::pulsando(unir2d::Tecla::abajo))
            sucesos_->pulsadoAbajo();
    }

    void JuegoMesaBase::controlTiempo()
    {
        if (tiempo_calculo.iniciado())
            sucesos_->alarmaCalculo(tiempo_calculo);
    }

    // Métodos auxiliares declarados en header pero no definidos:
    void JuegoMesaBase::agregaTablero(ActorTablero *valor) { tablero_ = valor; }
    void JuegoMesaBase::agregaPersonaje(ActorPersonaje *elemento)
    {
        if (!elemento)
            return;
        elemento->ponIndice((int)personajes_.size());
        personajes_.push_back(elemento);
        if (elemento->ladoTablero() == LadoTablero::Izquierda)
            personajes_izqrd.push_back(elemento);
        else
            personajes_derch.push_back(elemento);
    }
    void JuegoMesaBase::agregaHabilidad(Habilidad *elemento)
    {
        if (!elemento)
            return;
        elemento->ponIndice((int)habilidades_.size());
        habilidades_.push_back(elemento);
    }
    void JuegoMesaBase::agregaAtaque(TipoAtaque *elemento)
    {
        if (!elemento)
            return;
        elemento->ponIndice((int)ataques_.size());
        ataques_.push_back(elemento);
    }
    void JuegoMesaBase::agregaDefensa(TipoDefensa *elemento)
    {
        if (!elemento)
            return;
        elemento->ponIndice((int)defensas_.size());
        defensas_.push_back(elemento);
    }
    void JuegoMesaBase::agregaDano(TipoDano *elemento)
    {
        if (!elemento)
            return;
        elemento->ponIndice((int)danos_.size());
        danos_.push_back(elemento);
    }
    void JuegoMesaBase::agregaEfectividad(GradoEfectividad *elemento) { ataque_.agregaEfectividad(elemento); }
    void JuegoMesaBase::agregaMusica(ActorMusica *valor) { musica_ = valor; }

    void JuegoMesaBase::configura(SucesosJuegoComun *sucesos, ModoJuegoBase *modo)
    {
        sucesos_ = sucesos;
        modo_ = modo;
    }
    void JuegoMesaBase::agregaNombreAlumno(const std::wstring &nombre) { nombres_.push_back(nombre); }
    void JuegoMesaBase::indicaCursoAcademico(const std::wstring &curso) { curso_ = curso; }

} // namespace tapete
