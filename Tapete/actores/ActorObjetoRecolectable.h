#pragma once

#include "tapete.h"
#include "../ui/PresenciaFicha.h"

namespace tapete {

    class ActorObjetoRecolectable : public unir2d::ActorBase {
    public:
        enum class TipoEfectoObjeto {
            Dano,
            Curacion
        };

        ActorObjetoRecolectable(JuegoMesaBase* juego, Coord posicion, const std::string& archivo);
        ~ActorObjetoRecolectable();

        void inicia() override;
        void actualiza(double tiempo_seg) override;
        void termina() override;

        void ponEfecto(TipoEfectoObjeto tipo_, int valor_);
        TipoEfectoObjeto tipoEfecto() const;
        int valorEfecto() const;

        bool estaRecogido() const;
        Coord sitioFicha() const;

    private:
        JuegoMesaBase* juego{};
        Coord pos{};
        std::string archivo_ficha;
        bool recogido{ false };

        TipoEfectoObjeto tipo{ TipoEfectoObjeto::Dano };
        int valor{ 20 };

        PresenciaFicha ficha{ this };
    };

}
