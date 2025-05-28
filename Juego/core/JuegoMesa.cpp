// proyecto: Grupal/Juego
// archivo   JuegoMesa.cpp
// versión:  2.1  (Abril-2025)
#include "juego.h"
#include <array>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <tuple>
#include <utility>
#include <queue>

namespace juego
{

    string JuegoMesa::carpeta_activos_juego{"./Assets/activos/"};
    string JuegoMesa::carpeta_retratos_juego{"./Assets/retratos/"};
    string JuegoMesa::carpeta_habilides_juego{"./Assets/habilidades/"};
    string JuegoMesa::carpeta_sonidos_juego{"./Assets/sonidos/"};

    const std::wstring JuegoMesa::tituloVentana() const
    {
        return L"UNIR-2D :: Granujas y Bribones";
    }

    using GraficoMuros = char *[51];

    JuegoMesa::JuegoMesa()
    {
        ModoJuegoPares *modo = new ModoJuegoPares{this};
        SucesosJuegoPares *sucesos = new SucesosJuegoPares{this, modo};
        JuegoMesaBase::configura(sucesos, modo);
        std::srand(std::time(nullptr));
    }

    /// <summary>
    /// Genera de forma aleatoria la disposición de muros en el tablero.
    /// </summary>
    /// <returns>Referencia a un GraficoMuros con la nueva distribución.</returns>
    ActorTablero::GraficoMuros &generaMurosAleatorios()
    {
        static char buf[51][146];
        constexpr int ROWS = 51;
        constexpr int COLS = 145;
        constexpr int TOKENS = 25;
        constexpr int HALF = TOKENS / 2;
        constexpr int STEP = 6;
        constexpr int BLOCK_H = 4;
        constexpr int OFFSET[BLOCK_H] = {0, 3, 0, 3};

        static const std::vector<std::pair<int, int>> coordenadas_protegidas = {
            {35, 5}, {37, 5}, {39, 5}, {35, 45}, {37, 45}, {39, 45}, {3, 13}, {3, 33}, {5, 43}, {10, 30}, {25, 15}, {26, 24}, {25, 33}, {40, 24}, {45, 15}, {45, 33}};
        constexpr int FORBIDDEN_MARGIN = 1;

        auto isForbidden = [&](int row, int token)
        {
            for (auto &p : coordenadas_protegidas)
            {
                if (std::abs(p.first - row) <= FORBIDDEN_MARGIN && std::abs(p.second - token) <= FORBIDDEN_MARGIN)
                    return true;
            }
            return false;
        };

        auto isValidToken = [&](int r, int c)
        {
            if (c < 0 || c >= COLS || c % 3 != 0)
                return false;
            int fila1 = r + 1;
            int tok = (c / 3) + 1;
            return (fila1 % 2) == (tok % 2);
        };

        auto toTokenCoord = [&](int r, int c)
        {
            return std::pair<int, int>{r + 1, (c / 3) + 1};
        };

        for (int r = 0; r < ROWS; ++r)
        {
            for (int c = 0; c < COLS; ++c)
            {
                buf[r][c] = (c % 3 == 0 && isValidToken(r, c)) ? '-' : ' ';
            }
            buf[r][COLS] = '\0';
        }

        using Cell = std::pair<int, int>;
        static const std::vector<Cell> shapes[] = {
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
            {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}},
            {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}},
            {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
            {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}},
            {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 3}, {2, 0}, {2, 3}}};
        constexpr int NUM_SHAPES = sizeof(shapes) / sizeof(shapes[0]);

        std::mt19937 gen{std::random_device{}()};
        std::uniform_int_distribution<> islandCount(1, 2);
        std::uniform_int_distribution<> shapeIdx(0, NUM_SHAPES - 1);

        for (int block = 0; block < ROWS / BLOCK_H; ++block)
        {
            int count = islandCount(gen);
            int baseRow = block * BLOCK_H;
            for (int i = 0; i < count; ++i)
            {
                auto const &shape = shapes[shapeIdx(gen)];
                int maxdc = 0;
                for (auto &d : shape)
                    maxdc = std::max(maxdc, d.second);
                int w = maxdc + 1;
                std::uniform_int_distribution<> colOff(0, HALF - w);
                int obc = colOff(gen);
                int obr = baseRow + (gen() % BLOCK_H);
                int mirror = TOKENS - w - obc;

                bool valid = true;
                for (auto &d : shape)
                {
                    int rr = obr + d.first;
                    int cc = obc + d.second;
                    int cc2 = mirror + d.second;
                    if (rr < 0 || rr >= ROWS || cc < 0 || cc >= HALF || cc2 < HALF || cc2 >= TOKENS)
                    {
                        valid = false;
                        break;
                    }
                    int c1 = OFFSET[rr % BLOCK_H] + cc * STEP;
                    int c2 = OFFSET[rr % BLOCK_H] + cc2 * STEP;
                    if (!isValidToken(rr, c1) || !isValidToken(rr, c2))
                    {
                        valid = false;
                        break;
                    }
                    auto [tr1, tk1] = toTokenCoord(rr, c1);
                    auto [tr2, tk2] = toTokenCoord(rr, c2);
                    if (isForbidden(tr1, tk1) || isForbidden(tr2, tk2))
                    {
                        valid = false;
                        break;
                    }
                }
                if (!valid)
                {
                    --i;
                    continue;
                }

                for (auto &d : shape)
                {
                    int rr = obr + d.first;
                    int cc = obc + d.second;
                    int cc2 = mirror + d.second;
                    int c1 = OFFSET[rr % BLOCK_H] + cc * STEP;
                    int c2 = OFFSET[rr % BLOCK_H] + cc2 * STEP;
                    auto [tr1, tk1] = toTokenCoord(rr, c1);
                    auto [tr2, tk2] = toTokenCoord(rr, c2);
                    if (!isForbidden(tr1, tk1))
                        buf[rr][c1] = 'O';
                    if (!isForbidden(tr2, tk2))
                        buf[rr][c2] = 'O';
                }
            }
        }

        return reinterpret_cast<ActorTablero::GraficoMuros &>(buf);
    }

    void JuegoMesa::preparaTablero()
    {
        agregaTablero(new ActorTablero(this));
        tablero()->ponArchivoBaldosas(carpeta_activos_juego + "estampas_fondo.png");
        tablero()->equipa(LadoTablero::Izquierda, L"Granujas", carpeta_activos_juego + "granujas.png");
        tablero()->equipa(LadoTablero::Derecha, L"Bribones", carpeta_activos_juego + "bribones.png");
        tablero()->situaMuros(generaMurosAleatorios());
    }

    void JuegoMesa::preparaPersonajes()
    {
        Edward = new ActorPersonaje{this, LadoTablero::Izquierda, 0, L"Edward"};
        Balthazar = new ActorPersonaje{this, LadoTablero::Izquierda, 1, L"Balthazar"};
        Buenavida = new ActorPersonaje{this, LadoTablero::Izquierda, 2, L"Buenavida"};
        Victoria = new ActorPersonaje{this, LadoTablero::Derecha, 0, L"Victoria"};
        Luciana = new ActorPersonaje{this, LadoTablero::Derecha, 1, L"Luciana"};
        Dorian = new ActorPersonaje{this, LadoTablero::Derecha, 2, L"Dorian"};
        Edward->ponArchivoRetrato(carpeta_retratos_juego + "edward.png");
        Dorian->ponArchivoRetrato(carpeta_retratos_juego + "dorian.png");
        Balthazar->ponArchivoRetrato(carpeta_retratos_juego + "balthazar.png");
        Buenavida->ponArchivoRetrato(carpeta_retratos_juego + "buenavida.png");
        Luciana->ponArchivoRetrato(carpeta_retratos_juego + "luciana.png");
        Victoria->ponArchivoRetrato(carpeta_retratos_juego + "victoria.png");
        Edward->ponArchivoFicha(carpeta_retratos_juego + "carry.png");
        Dorian->ponArchivoFicha(carpeta_retratos_juego + "tanke2.png");
        Balthazar->ponArchivoFicha(carpeta_retratos_juego + "support.png");
        Buenavida->ponArchivoFicha(carpeta_retratos_juego + "tanke.png");
        Luciana->ponArchivoFicha(carpeta_retratos_juego + "support2.png");
        Victoria->ponArchivoFicha(carpeta_retratos_juego + "carry2.png");
        Edward->ponIniciativa(20);
        Dorian->ponIniciativa(19);
        Balthazar->ponIniciativa(17);
        Buenavida->ponIniciativa(20);
        Luciana->ponIniciativa(19);
        Victoria->ponIniciativa(17);

        Edward->asignaPersonajeSFX(carpeta_sonidos_juego + "SonidosPirata/EdwardRojo/Edward1.ogg", 100);
        Dorian->asignaPersonajeSFX(carpeta_sonidos_juego + "SonidosPirata/Dorian/Dorian1.ogg", 100);
        Balthazar->asignaPersonajeSFX(carpeta_sonidos_juego + "SonidosPirata/Balthazar/Balthazar1.ogg", 100);
        Buenavida->asignaPersonajeSFX(carpeta_sonidos_juego + "SonidosPirata/LucianaOeste/Luciana5.ogg", 100);
        Luciana->asignaPersonajeSFX(carpeta_sonidos_juego + "SonidosPirata/LucianaVientos/Lucianavientos2.ogg", 100);
        Victoria->asignaPersonajeSFX(carpeta_sonidos_juego + "SonidosPirata/Victoria/Victoria1.ogg", 100);

        Edward->asignaSeleccionSFX(carpeta_sonidos_juego + "SonidosPirata/EdwardRojo/Edwardpresentacion.ogg", 100);
        Dorian->asignaSeleccionSFX(carpeta_sonidos_juego + "SonidosPirata/Dorian/Dorianpresentacion.ogg", 100);
        Balthazar->asignaSeleccionSFX(carpeta_sonidos_juego + "SonidosPirata/Balthazar/Balthazarpresentacion.ogg", 100);
        Buenavida->asignaSeleccionSFX(carpeta_sonidos_juego + "SonidosPirata/LucianaVientos/Lucianavientospresentacion.ogg", 100);
        Luciana->asignaSeleccionSFX(carpeta_sonidos_juego + "SonidosPirata/LucianaOeste/Lucianapresentacion.ogg", 100);
        Victoria->asignaSeleccionSFX(carpeta_sonidos_juego + "SonidosPirata/Victoria/Victoriapresentacion.ogg", 100);

        Edward->asignaDesplazamientoSFX(carpeta_sonidos_juego + "SonidosPirata/EdwardRojo/Edward2.ogg", 100);
        Dorian->asignaDesplazamientoSFX(carpeta_sonidos_juego + "SonidosPirata/Dorian/Dorian2.ogg", 100);
        Balthazar->asignaDesplazamientoSFX(carpeta_sonidos_juego + "SonidosPirata/Balthazar/Balthazar2.ogg", 100);
        Buenavida->asignaDesplazamientoSFX(carpeta_sonidos_juego + "SonidosPirata/LucianaOeste/Luciana2.ogg", 100);
        Luciana->asignaDesplazamientoSFX(carpeta_sonidos_juego + "SonidosPirata/LucianaVientos/Lucianavientos3.ogg", 100);
        Victoria->asignaDesplazamientoSFX(carpeta_sonidos_juego + "SonidosPirata/Victoria/Victoria2.ogg", 100);

        agregaPersonaje(Edward);
        agregaPersonaje(Balthazar);
        agregaPersonaje(Buenavida);
        agregaPersonaje(Victoria);
        agregaPersonaje(Luciana);
        agregaPersonaje(Dorian);
    }

    void JuegoMesa::preparaHabilidades()
    {

        canionazo = new Habilidad{
            L"Cañonazo",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::directo,
            Antagonista::oponente};
        canionazo->ponDescripcion(
            L"Disparo de cañón de largo alcance que causa gran daño.");
        canionazo->ponArchivosImagenes(
            carpeta_habilides_juego + "canionazo.png",
            carpeta_habilides_juego + "fondo_5.png");
        canionazo->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/Canonazo.wav");

        embestida = new Habilidad{
            L"Embestida",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::directo,
            Antagonista::oponente};
        embestida->ponDescripcion(
            L"Ataque cuerpo a cuerpo que empuja al enemigo.");
        embestida->ponArchivosImagenes(
            carpeta_habilides_juego + "embestida.png",
            carpeta_habilides_juego + "fondo_5.png");
        embestida->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/Embestida.wav");

        abordaje = new Habilidad{
            L"Abordaje",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::directo,
            Antagonista::oponente};
        abordaje->ponDescripcion(
            L"Permite invadir el barco enemigo y realizar un ataque especial.");
        abordaje->ponArchivosImagenes(
            carpeta_habilides_juego + "abordaje.png",
            carpeta_habilides_juego + "fondo_5.png");
        abordaje->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/Abordaje.wav");

        reparacionBarco = new Habilidad{
            L"Reparación de barco",
            EnfoqueHabilidad::si_mismo,
            AccesoHabilidad::ninguno,
            Antagonista::si_mismo};
        reparacionBarco->ponDescripcion(
            L"Repara pequeños daños en el casco, recuperando 5 puntos de vitalidad.");
        reparacionBarco->ponArchivosImagenes(
            carpeta_habilides_juego + "reparar.png",
            carpeta_habilides_juego + "fondo_5.png");
        reparacionBarco->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/Reparacion.wav");

        sangradoMortal = new Habilidad{
            L"Sangrado mortal",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::indirecto,
            Antagonista::oponente};
        sangradoMortal->ponDescripcion(
            L"Edward corta a su enemigo causando daño a un enemigo.");
        sangradoMortal->ponArchivosImagenes(
            carpeta_habilides_juego + "cuchillo.png",
            carpeta_habilides_juego + "fondo_5.png");
        sangradoMortal->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/EdwardSangrado.wav");

        oleadaMetralla = new Habilidad{
            L"Oleada de metralla",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::indirecto,
            Antagonista::oponente};
        oleadaMetralla->ponDescripcion(
            L"Balthazar dispara una salva de metralla que daña a todos los enemigos cercanos.");
        oleadaMetralla->ponArchivosImagenes(
            carpeta_habilides_juego + "pistola.png",
            carpeta_habilides_juego + "fondo_5.png");
        oleadaMetralla->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/BalthazarMetralla.wav");

        golpeDevastador = new Habilidad{
            L"Golpes devastadores",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::indirecto,
            Antagonista::oponente};
        golpeDevastador->ponDescripcion(
            L"Buenavida golpea fuertemente empujando y dañando al enemigo.");
        golpeDevastador->ponArchivosImagenes(
            carpeta_habilides_juego + "boxeo.png",
            carpeta_habilides_juego + "fondo_5.png");
        golpeDevastador->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/BuenavidaGolpeEspolon.wav");

        punoCorsario = new Habilidad{
            L"Puño del Corsario",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::indirecto,
            Antagonista::oponente};
        punoCorsario->ponDescripcion(
            L"Victoria asesta un puño empapado en ron, embistiendo al enemigo como un navío.");
        punoCorsario->ponArchivosImagenes(
            carpeta_habilides_juego + "ponche.png",
            carpeta_habilides_juego + "fondo_5.png");
        punoCorsario->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/VictoriaPuno.wav");

        tornado = new Habilidad{
            L"Efecto tornado",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::indirecto,
            Antagonista::oponente};
        tornado->ponDescripcion(
            L"Luciana genera un tronado provocando daño al objetivo.");
        tornado->ponArchivosImagenes(
            carpeta_habilides_juego + "tornado.png",
            carpeta_habilides_juego + "fondo_5.png");
        tornado->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/LucianaTornado.wav");

        golpeAncla = new Habilidad{
            L"Golpe de ancla",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::indirecto,
            Antagonista::oponente};
        golpeAncla->ponDescripcion(
            L"Dorian usa su ancla como mazo y golpea a un enemigo cercano con gran fuerza.");
        golpeAncla->ponArchivosImagenes(
            carpeta_habilides_juego + "ancla.png",
            carpeta_habilides_juego + "fondo_5.png");
        golpeAncla->ponArchivoSonido(
            carpeta_sonidos_juego + "SonidosPirata/Habilidades/DorianAncla.wav");
            
        
        agregaHabilidad(canionazo);
        agregaHabilidad(embestida);
        agregaHabilidad(abordaje);
        agregaHabilidad(reparacionBarco);
        agregaHabilidad(sangradoMortal);
        agregaHabilidad(oleadaMetralla);
        agregaHabilidad(golpeDevastador);
        agregaHabilidad(punoCorsario);
        agregaHabilidad(tornado);
        agregaHabilidad(golpeAncla);
    }

    void JuegoMesa::preparaTiposEstadisticas()
    {
        ataqueCuerpoACuerpo = new TipoAtaque{L"Ataque cuerpo a cuerpo"};
        ataqueADistancia = new TipoAtaque{L"Ataque a distancia"};
        defensaCuerpoACuerpo = new TipoDefensa{L"Defensa cuerpo a cuerpo"};
        defensaADistancia = new TipoDefensa{L"Defensa a distancia"};
        danoFisico = new TipoDano{L"Daño físico"};
        agregaAtaque(ataqueCuerpoACuerpo);
        agregaAtaque(ataqueADistancia);
        agregaDefensa(defensaCuerpoACuerpo);
        agregaDefensa(defensaADistancia);
        agregaDano(danoFisico);
    }

    void JuegoMesa::agregaHabilidadesPersonajes()
    {
        for (auto *personaje : personajes())
        {
            personaje->agregaHabilidad(canionazo);
            personaje->agregaHabilidad(embestida);
            personaje->agregaHabilidad(abordaje);
            personaje->agregaHabilidad(reparacionBarco);
        }

        Edward->agregaHabilidad(sangradoMortal);
        Balthazar->agregaHabilidad(oleadaMetralla);
        Buenavida->agregaHabilidad(golpeDevastador);
        Victoria->agregaHabilidad(punoCorsario);
        Luciana->agregaHabilidad(tornado);
        Dorian->agregaHabilidad(golpeAncla);
    }

    void JuegoMesa::agregaEstadisticasHabilidades()
    {
        canionazo->ponCoste(8);
        canionazo->ponAlcance(12);
        canionazo->asignaAtaque(ataqueADistancia);
        canionazo->asignaDefensa(defensaADistancia);
        canionazo->asignaDano(danoFisico, 40);

        embestida->ponCoste(8);
        embestida->ponAlcance(1);
        embestida->asignaAtaque(ataqueCuerpoACuerpo);
        embestida->asignaDefensa(defensaCuerpoACuerpo);
        embestida->asignaDano(danoFisico, 25);

        abordaje->ponCoste(8);
        abordaje->ponAlcance(1);
        abordaje->asignaAtaque(ataqueCuerpoACuerpo);
        abordaje->asignaDefensa(defensaCuerpoACuerpo);
        abordaje->asignaDano(danoFisico, 50);

        reparacionBarco->ponCoste(3);
        reparacionBarco->agregaEfectoDefensa(defensaCuerpoACuerpo, 5);

        sangradoMortal->ponCoste(1);
        sangradoMortal->ponAlcance(5);
        sangradoMortal->asignaAtaque(ataqueADistancia);
        sangradoMortal->asignaDefensa(defensaADistancia);
        sangradoMortal->asignaDano(danoFisico, 29);

        oleadaMetralla->ponCoste(1);
        oleadaMetralla->ponAlcance(5);
        oleadaMetralla->asignaAtaque(ataqueCuerpoACuerpo);
        oleadaMetralla->asignaDefensa(defensaCuerpoACuerpo);
        oleadaMetralla->asignaDano(danoFisico, 38);
        golpeDevastador->ponCoste(1);
        golpeDevastador->ponAlcance(5);
        golpeDevastador->asignaAtaque(ataqueCuerpoACuerpo);
        golpeDevastador->asignaDefensa(defensaCuerpoACuerpo);
        golpeDevastador->asignaDano(danoFisico, 26);

        punoCorsario->ponCoste(1);
        punoCorsario->ponAlcance(45);
        punoCorsario->asignaAtaque(ataqueCuerpoACuerpo);
        punoCorsario->asignaDefensa(defensaCuerpoACuerpo);
        punoCorsario->asignaDano(danoFisico, 32);
        tornado->ponCoste(1);
        tornado->ponAlcance(5);
        tornado->asignaAtaque(ataqueCuerpoACuerpo);
        tornado->asignaDefensa(defensaCuerpoACuerpo);
        tornado->asignaDano(danoFisico, 34);
        golpeAncla->ponCoste(1);
        golpeAncla->ponAlcance(5);
        golpeAncla->asignaAtaque(ataqueCuerpoACuerpo);
        golpeAncla->asignaDefensa(defensaCuerpoACuerpo);
        golpeAncla->asignaDano(danoFisico, 27);
    }

    void JuegoMesa::agregaEstadisticasPersonajes()
    {
        Edward->agregaAtaque(ataqueCuerpoACuerpo, 40);
        Edward->agregaAtaque(ataqueADistancia, 75);
        Edward->agregaDefensa(defensaCuerpoACuerpo, 45);
        Edward->agregaDefensa(defensaADistancia, 60);
        Edward->agregaReduceDano(danoFisico, 5);

        Victoria->agregaAtaque(ataqueCuerpoACuerpo, 45);
        Victoria->agregaAtaque(ataqueADistancia, 70);
        Victoria->agregaDefensa(defensaCuerpoACuerpo, 50);
        Victoria->agregaDefensa(defensaADistancia, 60);
        Victoria->agregaReduceDano(danoFisico, 5);

        Balthazar->agregaAtaque(ataqueCuerpoACuerpo, 50);
        Balthazar->agregaAtaque(ataqueADistancia, 50);
        Balthazar->agregaDefensa(defensaCuerpoACuerpo, 55);
        Balthazar->agregaDefensa(defensaADistancia, 55);
        Balthazar->agregaReduceDano(danoFisico, 12);

        Luciana->agregaAtaque(ataqueCuerpoACuerpo, 45);
        Luciana->agregaAtaque(ataqueADistancia, 50);
        Luciana->agregaDefensa(defensaCuerpoACuerpo, 55);
        Luciana->agregaDefensa(defensaADistancia, 60);
        Luciana->agregaReduceDano(danoFisico, 12);

        Buenavida->agregaAtaque(ataqueCuerpoACuerpo, 80);
        Buenavida->agregaAtaque(ataqueADistancia, 30);
        Buenavida->agregaDefensa(defensaCuerpoACuerpo, 75);
        Buenavida->agregaDefensa(defensaADistancia, 60);
        Buenavida->agregaReduceDano(danoFisico, 20);

        Dorian->agregaAtaque(ataqueCuerpoACuerpo, 75);
        Dorian->agregaAtaque(ataqueADistancia, 35);
        Dorian->agregaDefensa(defensaCuerpoACuerpo, 70);
        Dorian->agregaDefensa(defensaADistancia, 60);
        Dorian->agregaReduceDano(danoFisico, 20);
    }

    void JuegoMesa::preparaSistemaAtaque()
    {
        GradoEfectividad *fallo = new GradoEfectividad{L"Fallo"};
        GradoEfectividad *roce = new GradoEfectividad{L"Roce"};
        GradoEfectividad *impacto = new GradoEfectividad{L"Impacto"};
        GradoEfectividad *critico = new GradoEfectividad{L"Impacto crítico"};
        fallo->estableceRango(INT_MIN, 9, 0);
        roce->estableceRango(10, 49, 50);
        impacto->estableceRango(50, 89, 100);
        critico->estableceRango(90, INT_MAX, 150);
        agregaEfectividad(fallo);
        agregaEfectividad(roce);
        agregaEfectividad(impacto);
        agregaEfectividad(critico);
    }

    void JuegoMesa::configuraJuego()
    {
        agregaMusica(new ActorMusica{this});
        modo()->configuraDesplaza(RejillaTablero::distanciaCeldas);
        Edward->ponSitioFicha(Coord{35, 5});
        Balthazar->ponSitioFicha(Coord{37, 5});
        Buenavida->ponSitioFicha(Coord{39, 5});

        Victoria->ponSitioFicha(Coord{35, 45});
        Luciana->ponSitioFicha(Coord{37, 45});
        Dorian->ponSitioFicha(Coord{39, 45});

        Buenavida->ponPuntosAccion(8);

        Dorian->ponPuntosAccion(8);

        Balthazar->ponPuntosAccion(12);

        Luciana->ponPuntosAccion(12);

        Edward->ponPuntosAccion(14);

        Victoria->ponPuntosAccion(14);

        tablero()->asignaSonidoEstablece(carpeta_sonidos_juego + "Metal Click.wav", 100);
        tablero()->asignaSonidoDesplaza(carpeta_sonidos_juego + "SnowWalk.ogg", 100);
        tablero()->asignaSonidoFracaso(carpeta_sonidos_juego + "bad.ogg", 100);
        tablero()->asignaSonidoExito(carpeta_sonidos_juego + "yar.ogg", 100);
        musica()->asignaMusica(carpeta_sonidos_juego + "Track_1.ogg", 100);
        
        agregaNombreAlumno(L"Sara Cubero García-Conde");
        agregaNombreAlumno(L"Juan Carlos Jibaja");
        agregaNombreAlumno(L"Nahuel Alejandro Espeche");
        agregaNombreAlumno(L"Carlos Díez Navarro");
        agregaNombreAlumno(L"Oriol Zabala Martínez");
        indicaCursoAcademico(L"2024 - 2025");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> tipoDist(0, 1);
        for (int i = 0; i < 10; ++i)
        {
            tesoros[i] = new ActorObjetoRecolectable(
                this,
                posiciones[i],
                carpeta_activos_juego + "suerte.png");

            bool esCuracion = tipoDist(gen);

            if (esCuracion)
            {
                tesoros[i]->ponEfecto(tapete::ActorObjetoRecolectable::TipoEfectoObjeto::Curacion, 20);
            }
            else
            {
                tesoros[i]->ponEfecto(tapete::ActorObjetoRecolectable::TipoEfectoObjeto::Dano, 20);
            }

            agregaObjeto(tesoros[i]);
        }
    }

    void JuegoMesa::despuesDeMover(ActorPersonaje *personaje)
    {
        verificaRecoleccion(personaje);
    }

    void JuegoMesa::verificaRecoleccion(ActorPersonaje *personaje)
    {
        if (!personaje)
            return;
        Coord pos = personaje->sitioFicha();

        for (int i = 0; i < NUM_TESOROS; ++i)
        {
            auto *obj = tesoros[i];
            if (obj && !obj->estaRecogido() && obj->sitioFicha() == pos)
            {

                using Efecto = tapete::ActorObjetoRecolectable::TipoEfectoObjeto;

                switch (obj->tipoEfecto())
                {
                case Efecto::Dano:
                {
                    int dmg = obj->valorEfecto();
                    personaje->ponVitalidad(personaje->vitalidad() - dmg);
                    personaje->presencia().refrescaBarraVida();
                    tablero()->emiteSonidoFracaso();
                    break;
                }
                case Efecto::Curacion:
                {
                    int heal = obj->valorEfecto();
                    personaje->ponVitalidad(std::min(personaje->vitalidad() + heal, 100));
                    personaje->presencia().refrescaBarraVida();
                    tablero()->emiteSonidoExito();
                    break;
                }
                }

                tablero()->indicador().desindica();

                obj->termina();
                tesoros[i] = nullptr;

                break;
            }
        }
    }

    void JuegoMesa::termina()
    {
        JuegoMesaBase::termina();
        for (auto *&t : tesoros)
        {
            if (t)
            {
                t->termina();
                delete t;
                t = nullptr;
            }
        }

        canionazo = nullptr;
        embestida = nullptr;
        abordaje = nullptr;
        reparacionBarco = nullptr;
        sangradoMortal = nullptr;
        oleadaMetralla = nullptr;
        golpeDevastador = nullptr;
        punoCorsario = nullptr;
        tornado = nullptr;
        golpeAncla = nullptr;

        ataqueCuerpoACuerpo = nullptr;
        ataqueADistancia = nullptr;
        defensaCuerpoACuerpo = nullptr;
        defensaADistancia = nullptr;
        danoFisico = nullptr;

        Buenavida = nullptr;
        Luciana = nullptr;
        Victoria = nullptr;
        Edward = nullptr;
        Dorian = nullptr;
        Balthazar = nullptr;
    }

}