// ActorObjetoRecolectable.cpp
#include "tapete.h"
#include "ActorObjetoRecolectable.h"

namespace tapete {

    ActorObjetoRecolectable::ActorObjetoRecolectable(
        JuegoMesaBase* juego,
        Coord posicion,
        const std::string& archivo
    ) : juego{ juego }, pos{ posicion }, archivo_ficha{ archivo } {
    }

    ActorObjetoRecolectable::~ActorObjetoRecolectable() {
        juego = nullptr;
    }

    void ActorObjetoRecolectable::inicia() {
        // 1) Fija el sistema de coordenadas local, igual que en Personaje
        ponPosicion(Vector{ 0, 0 });

        // 2) Calcula el centro en rejilla�
        Vector centro = juego->tablero()->rejilla().centroHexagono(pos);

        // 3) �y despl�zalo dentro de la regi�n central del tablero
        centro += PresenciaTablero::regionRejilla.posicion();

        // 4) Carga y registra la ficha
        ficha.ponArchivoFicha(archivo_ficha);  // carga textura + registra dibujo
        //ficha.ponCentro(centro);               // posiciona la imagen
        ficha.posicionaEnCelda(pos);
        ficha.muestra();                       // la hace visible
    }

    void ActorObjetoRecolectable::actualiza(double /*tiempo_seg*/) {
    if (recogido) return;
            Vector c = juego->tablero()->rejilla().centroHexagono(pos)
                + PresenciaTablero::regionRejilla.posicion();
            ficha.posicionaEnCelda(pos);//ficha.ponCentro(c);
            }

    void ActorObjetoRecolectable::termina() {
        ficha.oculta();
    }

    void ActorObjetoRecolectable::ponEfecto(TipoEfectoObjeto tipo_, int valor_) {
        tipo = tipo_;
        valor = valor_;
    }

    ActorObjetoRecolectable::TipoEfectoObjeto ActorObjetoRecolectable::tipoEfecto() const {
        return tipo;
    }

    int ActorObjetoRecolectable::valorEfecto() const {
        return valor;
    }

    bool ActorObjetoRecolectable::estaRecogido() const {
        return recogido;
    }

    Coord ActorObjetoRecolectable::sitioFicha() const {
        return pos;
    }

}