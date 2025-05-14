// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoLibreDoble.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class EstadoJuegoLibreDoble : public EstadoJuegoComun {
    public:

        static constexpr int inicioRonda             = finalPartida + 1;

        static constexpr int inicioTurnoNoElegido    = finalPartida + 2;
        static constexpr int inicioTurnoConfirmacion = finalPartida + 3;

        static constexpr int agotadosPuntosAccion    = finalPartida + 4;
        

        EstadoJuegoLibreDoble (int codigo);

        void transita (const EstadoJuegoLibreDoble & destino);

    private:

        void valida (const EstadoJuegoComun & destino) override;

        const string nombre () const override;

    };


}
