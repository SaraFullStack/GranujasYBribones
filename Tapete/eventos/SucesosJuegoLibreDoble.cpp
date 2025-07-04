﻿// proyecto: Grupal/Tapete
// archivo   SucesosJuegoLibreDoble.cpp
// versión:  2.1  (Abril-2025)

#include "tapete.h"

namespace tapete {

    SucesosJuegoLibreDoble::SucesosJuegoLibreDoble (JuegoMesaBase * juego, ModoJuegoLibreDoble * modo) :
        SucesosJuegoComun (juego, modo) { 
    }

    ModoJuegoLibreDoble * SucesosJuegoLibreDoble::modo () {
        return static_cast <ModoJuegoLibreDoble *> (SucesosJuegoComun::modo ());
    }

    void SucesosJuegoLibreDoble::iniciado () {
        if (modo ()->estado () == EstadoJuegoComun::inicial) {
            modo ()->entraPartida ();
        }
    }

    void SucesosJuegoLibreDoble::personajeSeleccionado (ActorPersonaje * personaje) {
        switch (modo ()->estado ()) {
        case EstadoJuegoLibreDoble::inicioTurnoNoElegido:
            modo ()->eligePersonaje (personaje);
            break;
        default:
            SucesosJuegoComun::personajeSeleccionado (personaje);
            break;
        }
    }

    void SucesosJuegoLibreDoble::actuanteSeleccionado (LadoTablero lado) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () == EstadoJuegoLibreDoble::inicioTurnoConfirmacion) {

            if (modo ()->ladoEquipoActual () != lado) {
                return;
            }
            modo ()->entraInicioJugada ();
            modo ()->entraAccionDesplazam ();
            return;

        }
        SucesosJuegoComun::actuanteSeleccionado (lado);
    }

    void SucesosJuegoLibreDoble::habilidadSeleccionada (LadoTablero lado, int indice_habilidad) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () == EstadoJuegoLibreDoble::inicioTurnoConfirmacion) {

            if (modo ()->ladoEquipoActual () != lado) {
                return;
            }
            if (indice_habilidad >= modo ()->personajeElegido (lado)->habilidades ().size ()) {
                return;
            }
            modo ()->entraInicioJugada ();
            modo ()->entraAccionHabilidad (indice_habilidad);
            return;

        }
        SucesosJuegoComun::habilidadSeleccionada (lado, indice_habilidad);
    }

    void SucesosJuegoLibreDoble::pulsadoEspacio () {
        switch (modo ()->estado ()) {
        case EstadoJuegoLibreDoble::inicioRonda:
            modo ()->entraTurnoEleccion ();
            break;
        case EstadoJuegoLibreDoble::inicioTurnoConfirmacion:
            modo ()->entraInicioJugada ();
            break;
        case EstadoJuegoLibreDoble::agotadosPuntosAccion:
            modo ()->ignoraPersonajeAgotado ();
            break;
        case EstadoJuegoLibreDoble::marcacionCaminoFicha:
            modo ()->mueveFicha ();
            break;  
        case EstadoJuegoLibreDoble::habilidadSimpleResultado:
        case EstadoJuegoLibreDoble::oponenteHabilidadResultado:
        case EstadoJuegoLibreDoble::areaHabilidadResultado:
            modo ()->asumeHabilidad ();
            break;
        default:
            SucesosJuegoComun::pulsadoEspacio ();
            break;
        }        
        unir2d::Teclado::consume (unir2d::Tecla::espacio);
    }

    void SucesosJuegoLibreDoble::pulsadoEscape () {
        switch (modo ()->estado ()) {
        case EstadoJuegoLibreDoble::inicioTurnoConfirmacion:
            modo ()->revierteInicioTurno ();
            break;
        default:
            SucesosJuegoComun::pulsadoEscape ();
            break;
        }
        unir2d::Teclado::consume (unir2d::Tecla::escape);
    }

}
