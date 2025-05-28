// proyecto: Grupal/Tapete
// archivo   SucesosJuegoEquipo.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class ModoJuegoEquipo;
    class JuegoMesa;


    class SucesosJuegoEquipo : public SucesosJuegoComun {
    public:

        explicit SucesosJuegoEquipo (JuegoMesaBase * juego, ModoJuegoEquipo * proceso);

    private:

        ModoJuegoEquipo * modo ();          


        void iniciado  () override;

        void pulsadoEspacio () override;
        void pulsadoEscape  () override;

    };


}

