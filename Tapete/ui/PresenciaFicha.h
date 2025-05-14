// PresenciaFicha.h
#pragma once

#include <Textura.h>
#include <Imagen.h>
#include <ActorBase.h>
#include <Vector.h>

namespace tapete {

    class PresenciaFicha {
    public:
        explicit PresenciaFicha(unir2d::ActorBase* actor);
        ~PresenciaFicha();

        void ponArchivoFicha(const std::string& archivo);
        void ponCentro(const Vector& centro);
        void muestra();
        void oculta();
        void posicionaEnCelda(Coord celda, const Vector& offset = Vector{ 16, 16 });

    private:
        unir2d::ActorBase* actor_base{};
        unir2d::Textura* textura_ficha{};
        unir2d::Imagen* imagen_ficha{};
    };

}
