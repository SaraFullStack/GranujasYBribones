// proyecto: Grupal/Tapete
// archivo:  tapete.h
// versión:  2.1  (Abril-2025)


#pragma once


#include <UNIR-2D.h>
using Vector = unir2d::Vector;
using Coord  = unir2d::Coord;
using Region = unir2d::Region;
using Color  = unir2d::Color;


#include <sstream>

#include "core/LadoTablero.h"
#include "combate/tipos/TipoEstadistica.h"
#include "combate/habilidades/Habilidad.h"
#include "ui/CuadroIndica.h"

#include "utils/Excepciones.h"

#include "ui/PresenciaPersonaje.h"
#include "grid/CalculoCaminos.h"
#include "actores/ActorPersonaje.h"

#include "ui/PresenciaTablero.h"
#include "grid/RejillaTablero.h"
#include "ui/PresenciaHabilidades.h"
#include "ui/PresenciaActuante.h"
#include "ui/VistaCaminoCeldas.h"
#include "ui/PresenciaFicha.h"
#include "ui/ListadoAyuda.h"
#include "actores/ActorTablero.h"
#include "actores/ActorObjetoRecolectable.h"

#include "actores/ActorMusica.h"

#include "combate/sistema/GradoEfectividad.h"
#include "combate/sistema/SistemaAtaque.h"
#include "ui/EscritorAyuda.h"
#include "modos/ModoJuegoBase.h"

#include "eventos/SucesosJuegoComun.h"
#include "estados/EstadoJuegoComun.h"
#include "modos/ModoJuegoComun.h"

#include "eventos/SucesosJuegoPares.h"
#include "estados/EstadoJuegoPares.h"
#include "modos/ModoJuegoPares.h"

#include "eventos/SucesosJuegoEquipo.h"
#include "estados/EstadoJuegoEquipo.h"
#include "modos/ModoJuegoEquipo.h"

#include "eventos/SucesosJuegoLibreDoble.h"
#include "estados/EstadoJuegoLibreDoble.h"
#include "modos/ModoJuegoLibreDoble.h"

#include "validacion/ValidacionJuego.h"
#include "core/JuegoMesaBase.h"
#include "ui/IntroJuegoImagen.h"
