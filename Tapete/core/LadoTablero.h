// proyecto: Grupal/Tapete
// archivo:  LadoTablero.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    enum class LadoTablero {
        Izquierda,
        Derecha,
        nulo
    };


    inline LadoTablero opuesto (LadoTablero lado) {
        assert (lado != LadoTablero::nulo);
        if (lado == LadoTablero::Izquierda) {
            return LadoTablero::Derecha;
        } else {
            return LadoTablero::Izquierda;
        }
    }

}


