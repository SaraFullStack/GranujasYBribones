// ActorObjetoRecolectable.cpp
#include "tapete.h"
#include "ActorObjetoRecolectable.h"

namespace tapete
{

    ActorObjetoRecolectable::ActorObjetoRecolectable(
        JuegoMesaBase *juego,
        Coord posicion,
        const std::string &archivo) : juego{juego}, pos{posicion}, archivo_ficha{archivo}
    {
    }

    ActorObjetoRecolectable::~ActorObjetoRecolectable()
    {
        juego = nullptr;
    }

    void ActorObjetoRecolectable::inicia()
    {

        ponPosicion(Vector{0, 0});

        Vector centro = juego->tablero()->rejilla().centroHexagono(pos);

        centro += PresenciaTablero::regionRejilla.posicion();

        ficha.ponArchivoFicha(archivo_ficha);

        ficha.posicionaEnCelda(pos);
        ficha.muestra(); // la hace visible
    }

    void ActorObjetoRecolectable::actualiza(double)
    {
        if (recogido)
            return;
        Vector c = juego->tablero()->rejilla().centroHexagono(pos) + PresenciaTablero::regionRejilla.posicion();
        ficha.posicionaEnCelda(pos);
    }

    void ActorObjetoRecolectable::termina()
    {
        ficha.oculta();
    }

    void ActorObjetoRecolectable::ponEfecto(TipoEfectoObjeto tipo_, int valor_)
    {
        tipo = tipo_;
        valor = valor_;
    }

    ActorObjetoRecolectable::TipoEfectoObjeto ActorObjetoRecolectable::tipoEfecto() const
    {
        return tipo;
    }

    int ActorObjetoRecolectable::valorEfecto() const
    {
        return valor;
    }

    bool ActorObjetoRecolectable::estaRecogido() const
    {
        return recogido;
    }

    Coord ActorObjetoRecolectable::sitioFicha() const
    {
        return pos;
    }

}