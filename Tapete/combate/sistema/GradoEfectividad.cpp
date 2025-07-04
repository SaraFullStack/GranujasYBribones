﻿// proyecto: Grupal/Tapete
// arhivo:   JuegoMesa.cpp
// versión:  2.1  (Abril-2025)

#include "tapete.h"

namespace tapete
{

    GradoEfectividad::GradoEfectividad(const wstring &nombre)
    {
        this->nombre_ = nombre;
    }

    void GradoEfectividad::estableceRango(
        int valor_ataque_inf, int valor_ataque_sup, int porciento_dano)
    {
        this->valor_ataque_inf = valor_ataque_inf;
        this->valor_ataque_sup = valor_ataque_sup;
        this->porciento_dano = porciento_dano;
    }

    const wstring &GradoEfectividad::nombre() const
    {
        return nombre_;
    }

    int GradoEfectividad::valorInferiorAtaque() const
    {
        return valor_ataque_inf;
    }

    int GradoEfectividad::valorSuperiorAtaque() const
    {
        return valor_ataque_sup;
    }

    int GradoEfectividad::porcentajeDano() const
    {
        return porciento_dano;
    }

}