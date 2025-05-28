// PresenciaFicha.cpp

#include "tapete.h"
#include "PresenciaFicha.h"
#include <stdexcept>

namespace tapete
{

    PresenciaFicha::PresenciaFicha(unir2d::ActorBase *actor)
        : actor_base(actor)
    {
    }

    PresenciaFicha::~PresenciaFicha()
    {
        if (actor_base && imagen_ficha)
            actor_base->extraeDibujo(imagen_ficha);

        delete imagen_ficha;
        delete textura_ficha;

        imagen_ficha = nullptr;
        textura_ficha = nullptr;
    }

    void PresenciaFicha::ponArchivoFicha(const std::string &archivo)
    {
        textura_ficha = new unir2d::Textura();
        textura_ficha->carga(archivo);
        imagen_ficha = new unir2d::Imagen();
        imagen_ficha->asigna(textura_ficha);
        actor_base->agregaDibujo(imagen_ficha); // registro en el motor :contentReference[oaicite:6]{index=6}:contentReference[oaicite:7]{index=7}
    }

    void PresenciaFicha::ponCentro(const Vector &centro)
    {
        if (imagen_ficha)
            imagen_ficha->ponPosicion(centro);
    }

    void PresenciaFicha::muestra()
    {
        if (imagen_ficha)
            imagen_ficha->ponVisible(true);
    }

    void PresenciaFicha::oculta()
    {
        if (imagen_ficha)
            imagen_ficha->ponVisible(false);
    }

    void PresenciaFicha::posicionaEnCelda(Coord celda, const Vector &offset)
    {
        Vector poscn = RejillaTablero::centroHexagono(celda);
        poscn += PresenciaTablero::regionRejilla.posicion();
        poscn -= offset; // Centrado, por ejemplo {16,16} para imagen de 32x32
        if (imagen_ficha)
        {
            imagen_ficha->ponPosicion(poscn);
        }
    }

}
