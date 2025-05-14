// proyecto: Grupal/Juego      
// arhivo:   juego1.h
// versión:  2.1  (Abril-2025)


#pragma once


#include <UNIR-2D.h>
//using string = std::string;
//using Vector = unir2d::Vector;
//using Coord  = unir2d::Coord;
//using Region = unir2d::Region;
//using Color  = unir2d::Color;


#include <tapete.h>
using namespace tapete;


#include "eventos/SucesosJuegoPares.h"
#include "estados/EstadoJuegoPares.h"
#include "modos/ModoJuegoPares.h"

#include "eventos/SucesosJuegoEquipo.h"
#include "estados/EstadoJuegoEquipo.h"
#include "modos/ModoJuegoEquipo.h"

#include "eventos/SucesosJuegoLibreDoble.h"
#include "estados/EstadoJuegoLibreDoble.h"
#include "modos/ModoJuegoLibreDoble.h"

#include "core/JuegoMesa.h"
