﻿// proyecto: Grupal/Tapete
// archivo   ModoJuegoEquipo.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class JuegoMesa;


    class ModoJuegoEquipo : public ModoJuegoComun {
    public:

        explicit ModoJuegoEquipo (JuegoMesaBase * juego);

        // EstadoJuegoComun es polimórfica
        EstadoJuegoEquipo & estado ();

        void entraPartida ();

        void entraInicioJugada ();

        void mueveFicha ();
        void asumeHabilidad ();

    private:

        EstadoJuegoEquipo estado_;
        EstadoJuegoEquipo estado_previo_;


        void buscaJugada (bool & encontrada);
        void asume (
                bool & inicio_jugada, 
                bool & inicio_turno, 
                bool & inicio_ronda, 
                bool & final_partida);

        void escribeEstado () override;

        const string nombreModulo () override;
        void validaAtributos () override;
//        void excepciona (const string & metodo, const std::exception & excepcion);

    };


}

