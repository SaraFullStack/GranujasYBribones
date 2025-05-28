// proyecto: Grupal/Tapete
// archivo   CalculoCaminos.cpp
// versión:  2.1  (Abril-2025)

#include "tapete.h"

namespace tapete
{

    bool CalculoCaminos::celdaEnTablero(Coord celda)
    {

        if (celda.fila() % 2 == 0)
        {
            if (celda.fila() < 2)
            {
                return false;
            }
            if (celda.fila() > RejillaTablero::filas - 1)
            {
                return false;
            }
        }
        else
        {
            if (celda.fila() < 1)
            {
                return false;
            }
            if (celda.fila() > RejillaTablero::filas)
            {
                return false;
            }
        }

        if (celda.coln() <= 0)
        {
            return false;
        }
        if (celda.coln() > RejillaTablero::columnas)
        {
            return false;
        }

        return true;
    }

    bool CalculoCaminos::celdaEnMuro(JuegoMesaBase *juego, Coord celda)
    {
        for (const Coord &coord : juego->tablero()->sitiosMuros())
        {
            if (coord == celda)
            {
                return true;
            }
        }
        return false;
    }

    bool CalculoCaminos::celdaOcupada(JuegoMesaBase *juego, Coord celda)
    {
        for (const ActorPersonaje *persj : juego->personajes())
        {
            if (persj->sitioFicha() == celda)
            {
                return true;
            }
        }
        for (const Coord &coord : juego->tablero()->sitiosMuros())
        {
            if (coord == celda)
            {
                return true;
            }
        }
        for (const Coord &coord : juego->modo()->etapasCamino())
        {
            if (coord == celda)
            {
                return true;
            }
        }
        return false;
    }

    bool CalculoCaminos::etapaValidaCamino(JuegoMesaBase *juego, Coord celda_destino_etapa)
    {
        aserta(juego->modo()->etapasCamino().size() >= 1, "camino no iniciado");
        Coord celda_origen_etapa = juego->modo()->etapasCamino().back();
        aserta(celda_origen_etapa != celda_destino_etapa, "etapa del camino nula");

        int direccion_exacta;
        int direccion_cuadrante;
        calculoDireccion(
            celda_origen_etapa, celda_destino_etapa,
            direccion_exacta, direccion_cuadrante);
        if (direccion_exacta != 0)
        {
            return etapaValidaCaminoExacto(
                juego,
                celda_origen_etapa, celda_destino_etapa,
                direccion_exacta);
        }
        return etapaValidaCaminoCuadrante(
            juego,
            celda_origen_etapa, celda_destino_etapa,
            direccion_cuadrante);
    }

    bool CalculoCaminos::segmentoValido(
        JuegoMesaBase *juego, Coord celda_origen, Coord celda_destino)
    {
        aserta(celda_origen != celda_destino, "segmento de camino nulo");

        int direccion_exacta;
        int direccion_cuadrante;
        calculoDireccion(
            celda_origen, celda_destino,
            direccion_exacta, direccion_cuadrante);
        if (direccion_exacta != 0)
        {
            return etapaValidaCaminoExacto(
                juego,
                celda_origen, celda_destino,
                direccion_exacta);
        }
        return etapaValidaCaminoCuadrante(
            juego,
            celda_origen, celda_destino,
            direccion_cuadrante);
    }

    void CalculoCaminos::calculoDireccion(
        Coord celda_origen_etapa, Coord celda_destino_etapa,
        int &direccion_exacta, int &direccion_cuadrante)
    {
        direccion_exacta = 0;
        direccion_cuadrante = 0;
        int filas = celda_destino_etapa.fila() - celda_origen_etapa.fila();
        int colns = celda_destino_etapa.coln() - celda_origen_etapa.coln();
        if (filas == 0)
        {
            if (colns > 0)
            {
                direccion_cuadrante = 2;
            }
            else
            {
                direccion_cuadrante = 5;
            }
        }
        else if (colns == 0)
        {
            if (filas > 0)
            {
                direccion_exacta = 4;
            }
            else
            {
                direccion_exacta = 1;
            }
        }
        else if (filas > 0 && colns > 0)
        {
            if (filas == colns)
            {
                direccion_exacta = 3;
            }
            else if (filas < colns)
            {
                direccion_cuadrante = 2;
            }
            else
            {
                direccion_cuadrante = 3;
            }
        }
        else if (filas > 0 && colns < 0)
        {
            if (filas == -colns)
            {
                direccion_exacta = 5;
            }
            else if (filas < -colns)
            {
                direccion_cuadrante = 5;
            }
            else
            {
                direccion_cuadrante = 4;
            }
        }
        else if (filas < 0 && colns > 0)
        {
            if (-filas == colns)
            {
                direccion_exacta = 2;
            }
            else if (-filas < colns)
            {
                direccion_cuadrante = 2;
            }
            else
            {
                direccion_cuadrante = 1;
            }
        }
        else if (filas < 0 && colns < 0)
        {
            if (-filas == -colns)
            {
                direccion_exacta = 6;
            }
            else if (-filas < -colns)
            {
                direccion_cuadrante = 5;
            }
            else
            {
                direccion_cuadrante = 6;
            }
        }
    }

    bool CalculoCaminos::etapaValidaCaminoExacto(
        JuegoMesaBase *juego,
        Coord celda_origen_etapa, Coord celda_destino_etapa,
        int direccion_exacta)
    {
        Coord celda_sale = celda_origen_etapa;
        while (true)
        {
            Coord celda_llega;
            celdaProximaCaminoExacto(celda_sale, direccion_exacta, celda_llega);
            if (celda_llega == celda_destino_etapa)
            {
                return true;
            }
            if (!celdaEnTablero(celda_llega))
            {
                return false;
            }
            if (celdaOcupada(juego, celda_llega))
            {
                return false;
            }
            celda_sale = celda_llega;
        }
    }

    void CalculoCaminos::celdaProximaCaminoExacto(
        Coord celda_sale, int direccion_exacta,
        Coord &celda_llega)
    {
        switch (direccion_exacta)
        {
        case 1:
            celda_llega = Coord{celda_sale.fila() - 2, celda_sale.coln()};
            break;
        case 2:
            celda_llega = Coord{celda_sale.fila() - 1, celda_sale.coln() + 1};
            break;
        case 3:
            celda_llega = Coord{celda_sale.fila() + 1, celda_sale.coln() + 1};
            break;
        case 4:
            celda_llega = Coord{celda_sale.fila() + 2, celda_sale.coln()};
            break;
        case 5:
            celda_llega = Coord{celda_sale.fila() + 1, celda_sale.coln() - 1};
            break;
        case 6:
            celda_llega = Coord{celda_sale.fila() - 1, celda_sale.coln() - 1};
            break;
        }
    }

    bool CalculoCaminos::etapaValidaCaminoCuadrante(
        JuegoMesaBase *juego,
        Coord celda_origen_etapa, Coord celda_destino_etapa,
        int direccion_cuadrante)
    {
        Vector vector_origen = RejillaTablero::centroHexagono(celda_origen_etapa);
        Vector vector_destino = RejillaTablero::centroHexagono(celda_destino_etapa);
        EcuacionRecta recta_etapa;
        calculaRecta(vector_destino - vector_origen, vector_origen, recta_etapa);

        Coord celda_sale = celda_origen_etapa;
        while (true)
        {
            Coord celda_llega;
            celdaProximaCaminoCuadrante(celda_sale, direccion_cuadrante, recta_etapa, celda_llega);
            if (celda_llega == celda_destino_etapa)
            {
                return true;
            }
            if (!celdaEnTablero(celda_llega))
            {
                return false;
            }
            if (celdaOcupada(juego, celda_llega))
            {
                return false;
            }
            celda_sale = celda_llega;
        }
        return true;
    }

    void CalculoCaminos::celdaProximaCaminoCuadrante(
        Coord celda_sale, int direccion_cuadrante,
        const EcuacionRecta &recta_etapa, Coord &celda_llega)
    {
        std::array<Coord, 2> celda_proxm{};

        switch (direccion_cuadrante)
        {
        case 1:
            celda_proxm[0] = Coord{celda_sale.fila() - 2, celda_sale.coln()};
            celda_proxm[1] = Coord{celda_sale.fila() - 1, celda_sale.coln() + 1};
            break;
        case 2:
            celda_proxm[0] = Coord{celda_sale.fila() - 1, celda_sale.coln() + 1};
            celda_proxm[1] = Coord{celda_sale.fila() + 1, celda_sale.coln() + 1};
            break;
        case 3:
            celda_proxm[0] = Coord{celda_sale.fila() + 1, celda_sale.coln() + 1};
            celda_proxm[1] = Coord{celda_sale.fila() + 2, celda_sale.coln()};
            break;
        case 4:
            celda_proxm[0] = Coord{celda_sale.fila() + 2, celda_sale.coln()};
            celda_proxm[1] = Coord{celda_sale.fila() + 1, celda_sale.coln() - 1};
            break;

        case 5:
            celda_proxm[0] = Coord{celda_sale.fila() + 1, celda_sale.coln() - 1};
            celda_proxm[1] = Coord{celda_sale.fila() - 1, celda_sale.coln() - 1};
            break;
        case 6:
            celda_proxm[0] = Coord{celda_sale.fila() - 1, celda_sale.coln() - 1};
            celda_proxm[1] = Coord{celda_sale.fila() - 2, celda_sale.coln()};
            break;
        }

        for (int indc = 0; indc < celda_proxm.size(); ++indc)
        {
            if (!celdaEnTablero(celda_proxm[indc]))
            {
                celda_proxm[indc] = Coord{0, 0};
            }
        }

        if (celda_proxm[0] == Coord{0, 0})
        {
            celda_llega = celda_proxm[1];
            return;
        }
        if (celda_proxm[1] == Coord{0, 0})
        {
            celda_llega = celda_proxm[0];
            return;
        }

        std::array<float, 2> distn_proxm{};
        for (int indc = 0; indc < celda_proxm.size(); ++indc)
        {
            Vector punto = RejillaTablero::centroHexagono(celda_proxm[indc]);
            distn_proxm[indc] = distancia(recta_etapa, punto);
        }

        if (distn_proxm[0] < distn_proxm[1])
        {
            celda_llega = celda_proxm[0];
        }
        else
        {
            celda_llega = celda_proxm[1];
        }
    }

    void CalculoCaminos::calculaRecta(
        Vector vector_director, Vector punto_recta,
        CalculoCaminos::EcuacionRecta &recta)
    {

        recta.a = vector_director.y();
        recta.b = -vector_director.x();
        recta.c = -recta.a * punto_recta.x() - recta.b * punto_recta.y();

        recta.d = std::sqrtf(recta.a * recta.a + recta.b * recta.b);
    }

    float CalculoCaminos::distancia(const EcuacionRecta &recta, Vector punto)
    {

        return std::fabsf(recta.a * punto.x() + recta.b * punto.y() + recta.c) / recta.d;
    }

    void CalculoCaminos::areaCeldas(
        JuegoMesaBase *juego,
        Coord celda_central,
        int radio_area,
        AreaCentradaCeldas &area_celdas)
    {

        area_celdas.resize(radio_area + 1u);
        area_celdas[0].push_back(celda_central);
        for (int indc_radio = 1; indc_radio <= radio_area; ++indc_radio)
        {
            agregaLadoArea(juego, celda_central, indc_radio, Coord{-2, 0}, Coord{1, 1}, area_celdas);
            agregaLadoArea(juego, celda_central, indc_radio, Coord{-1, 1}, Coord{2, 0}, area_celdas);
            agregaLadoArea(juego, celda_central, indc_radio, Coord{1, 1}, Coord{1, -1}, area_celdas);
            agregaLadoArea(juego, celda_central, indc_radio, Coord{2, 0}, Coord{-1, -1}, area_celdas);
            agregaLadoArea(juego, celda_central, indc_radio, Coord{1, -1}, Coord{-2, 0}, area_celdas);
            agregaLadoArea(juego, celda_central, indc_radio, Coord{-1, -1}, Coord{-1, 1}, area_celdas);
        }
    }

    void CalculoCaminos::agregaLadoArea(
        JuegoMesaBase *juego,
        Coord celda_central,
        int indice_radio,
        Coord origen_lado,
        Coord director_lado,
        AreaCentradaCeldas &area_celdas)
    {
        Coord celda = celda_central + indice_radio * origen_lado;
        if (celdaEnTablero(celda) && !celdaEnMuro(juego, celda))
        {
            area_celdas[indice_radio].push_back(celda);
        }
        for (int indc = 2; indc <= indice_radio; ++indc)
        {
            celda += director_lado;
            if (celdaEnTablero(celda) && !celdaEnMuro(juego, celda))
            {
                area_celdas[indice_radio].push_back(celda);
            }
        }
    }

    void CalculoCaminos::aserta(bool expresion, const string &mensaje)
    {
        if (expresion)
        {
            return;
        }
        throw std::logic_error(mensaje);
    }

}
