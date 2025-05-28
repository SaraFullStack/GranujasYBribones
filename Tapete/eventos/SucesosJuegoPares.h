// proyecto: Grupal/Tapete
// archivo   SucesosJuegoPares.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class ModoJuegoPares;
    class JuegoMesa;


    class SucesosJuegoPares : public SucesosJuegoComun {
    public:

        explicit SucesosJuegoPares (JuegoMesaBase * juego,ModoJuegoPares * proceso);

    private:

        ModoJuegoPares * modo ();          


        void iniciado  () override;

        void personajeSeleccionado (ActorPersonaje * personaje) override;

        void pulsadoEspacio () override;
        void pulsadoEscape  () override;

    };


}
