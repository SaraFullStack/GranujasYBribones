// proyecto: Grupal/Tapete
// archivo   PresenciaTablero.cpp
// versión:  2.1  (Abril-2025)#include "tapete.h"
#include "tapete.h"

namespace tapete
{

    PresenciaTablero::PresenciaTablero(ActorTablero *actor_tablero)
    {
        this->actor_tablero = actor_tablero;
    }

    PresenciaTablero::~PresenciaTablero()
    {
        this->actor_tablero = nullptr;
    }

    void PresenciaTablero::prepara()
    {
        preparaBaldosas();
        preparaMuros();
        preparaPaneles();
        preparaMonitor();
        preparaDisplay();
        preparaAyuda();
        preparaSonidos();
    }

    void PresenciaTablero::reprepara()
    {
        actor_tablero->agregaDibujo(malla_muros);

        actor_tablero->agregaDibujo(imagen_panel_vertcl_izqrd);
        actor_tablero->agregaDibujo(imagen_panel_vertcl_derch);
        actor_tablero->agregaDibujo(imagen_panel_abajo_izqrd);
        actor_tablero->agregaDibujo(imagen_panel_abajo_derch);
        actor_tablero->agregaDibujo(imagen_bandera_izqrd);
        actor_tablero->agregaDibujo(imagen_escudo_izqrd);
        actor_tablero->agregaDibujo(imagen_bandera_derch);
        actor_tablero->agregaDibujo(imagen_escudo_derch);

        actor_tablero->agregaDibujo(imagen_fondo_monitor);
        for (int indc = 0; indc < lineas_texto_monitor; ++indc)
        {
            actor_tablero->agregaDibujo(texto_monitor[indc]);
        }
    }

    void PresenciaTablero::libera()
    {
        liberaPaneles();
        liberaMuros();
        liberaBaldosas();
        liberaMonitor();
        liberaDisplay();
        liberaAyuda();
        liberaSonidos();
    }

    void PresenciaTablero::preparaBaldosas()
    {
        textura_fondo = new unir2d::Textura{};
        baldosas_fondo = new unir2d::Baldosas{};
        constexpr int filas_estamp = 4;
        constexpr int colns_estamp = 4;
        textura_fondo->carga(actor_tablero->archivoBaldosas());

        baldosas_fondo->asigna(this->textura_fondo);
        baldosas_fondo->defineEstampas(filas_estamp, colns_estamp);
        baldosas_fondo->ponPosicion(Vector{0, 0});
        constexpr int filas_superf = 32;
        constexpr int colns_superf = 56;
        baldosas_fondo->defineSuperficie(filas_superf, colns_superf);
        std::vector<uint32_t> mapeo{};
        mapeo.resize(static_cast<int>(filas_superf * colns_superf));
        std::random_device semilla{};
        std::mt19937 generador{semilla()};
        std::uniform_int_distribution<unsigned int> distrb_filas{0, filas_estamp - 1};
        std::uniform_int_distribution<unsigned int> distrb_colns{0, colns_estamp - 1};
        for (int f_s = 0; f_s < filas_superf; ++f_s)
        {
            for (int c_s = 0; c_s < colns_superf; ++c_s)
            {
                int f_e = (int)distrb_filas(generador);
                int c_e = (int)distrb_colns(generador);
                mapeo[f_s * colns_superf + c_s] = f_e * colns_estamp + c_e;
            }
        }
        baldosas_fondo->mapea(mapeo);
        actor_tablero->agregaDibujo(baldosas_fondo);
    }

    void PresenciaTablero::liberaBaldosas()
    {
        delete baldosas_fondo;
        delete textura_fondo;

        baldosas_fondo = nullptr;
        textura_fondo = nullptr;
    }

    void PresenciaTablero::preparaMuros()
    {
        textura_muros = new unir2d::Textura{};
        textura_muros->carga(JuegoMesaBase::carpetaActivos() + "muro_piedra.png");
        malla_muros = new unir2d::Malla{};
        malla_muros->asigna(textura_muros);
        malla_muros->ponPosicion(PresenciaTablero::regionRejilla.posicion());

        IndicesEstampas indcs_estmp;
        calculaEstampasMuros(actor_tablero->sitios_muros, indcs_estmp);

        PuntosHexagonos puntos_textr{};
        punteaTexturaMuros(puntos_textr);
        PuntosHexagonos puntos_rejll{};
        punteaRejillaMuros(actor_tablero->sitios_muros, puntos_rejll);
        estableceMallaMuros(puntos_rejll, indcs_estmp, puntos_textr);
    }

    void PresenciaTablero::liberaMuros()
    {
        delete malla_muros;
        delete textura_muros;

        malla_muros = nullptr;
        textura_muros = nullptr;
    }

    void PresenciaTablero::calculaEstampasMuros(
        const std::vector<Coord> &posiciones_rejilla,
        IndicesEstampas &indices_estampas)
    {
        constexpr int colns_rejilla = RejillaTablero::columnas + 1; // 50
        constexpr int filas_rejilla = RejillaTablero::filas + 1;    // 52

        std::array<std::array<bool, colns_rejilla>, filas_rejilla> tabla_rejilla{false};
        for (const Coord &coord : posiciones_rejilla)
        {
            tabla_rejilla[coord.fila()][coord.coln()] = true;
        }
        for (const Coord &coord : posiciones_rejilla)
        {
            bool las_12 = false;
            bool las__2 = false;
            bool las__4 = false;
            bool las__6 = false;
            bool las__8 = false;
            bool las_10 = false;
            if (coord.fila() - 2 >= 1)
            {
                las_12 = tabla_rejilla[coord.fila() - 2][coord.coln()];
            }
            if (coord.fila() - 1 >= 1 &&
                coord.coln() + 1 <= RejillaTablero::columnas)
            {
                las__2 = tabla_rejilla[coord.fila() - 1][coord.coln() + 1];
            }
            if (coord.fila() + 1 <= RejillaTablero::filas &&
                coord.coln() + 1 <= RejillaTablero::columnas)
            {
                las__4 = tabla_rejilla[coord.fila() + 1][coord.coln() + 1];
            }
            if (coord.fila() + 2 <= RejillaTablero::filas)
            {
                las__6 = tabla_rejilla[coord.fila() + 2][coord.coln()];
            }
            if (coord.fila() + 1 <= RejillaTablero::filas &&
                coord.coln() - 1 >= 1)
            {
                las__8 = tabla_rejilla[coord.fila() + 1][coord.coln() - 1];
            }
            if (coord.fila() - 1 >= 1 &&
                coord.coln() - 1 >= 1)
            {
                las_10 = tabla_rejilla[coord.fila() - 1][coord.coln() - 1];
            }
            std::array<int, 6> entrd{};
            entrd[0] = estampaMuros(las_10, las_12, las__2);
            entrd[1] = estampaMuros(las_12, las__2, las__4);
            entrd[2] = estampaMuros(las__2, las__4, las__6);
            entrd[3] = estampaMuros(las__4, las__6, las__8);
            entrd[4] = estampaMuros(las__6, las__8, las_10);
            entrd[5] = estampaMuros(las__8, las_10, las_12);
            indices_estampas.push_back(entrd);
        }
    }

    int PresenciaTablero::estampaMuros(bool previo, bool adjunto, bool postrer)
    {
        if (adjunto)
        {
            return 4;
        }
        if (previo && postrer)
        {
            return 3;
        }
        if (!previo && postrer)
        {
            return 2;
        }
        if (previo && !postrer)
        {
            return 1;
        }
        if (!previo && !postrer)
        {
            return 0;
        }
        return -1;
    }

    void PresenciaTablero::punteaTexturaMuros(PuntosHexagonos &puntos_textura)
    {

        puntos_textura.resize(estampasTexturaMuros);
        for (int indc_celda = 0; indc_celda < estampasTexturaMuros; ++indc_celda)
        {
            puntos_textura[indc_celda][0] = {
                Vector{20.0f, 17.0f},
                Vector{10.0f, 0.0f},
                Vector{30.0f, 0.0f}};
            puntos_textura[indc_celda][1] = {
                Vector{20.0f, 17.0f},
                Vector{30.0f, 0.0f},
                Vector{40.0f, 17.0f}};
            puntos_textura[indc_celda][2] = {
                Vector{20.0f, 17.0f},
                Vector{40.0f, 17.0f},
                Vector{30.0f, 34.0f}};
            puntos_textura[indc_celda][3] = {
                Vector{20.0f, 17.0f},
                Vector{30.0f, 34.0f},
                Vector{10.0f, 34.0f}};
            puntos_textura[indc_celda][4] = {
                Vector{20.0f, 17.0f},
                Vector{10.0f, 34.0f},
                Vector{0.0f, 17.0f}};
            puntos_textura[indc_celda][5] = {
                Vector{20.0f, 17.0f},
                Vector{0.0f, 17.0f},
                Vector{10.0f, 0.0f}};
            for (int indc_trngl = 0; indc_trngl < 6; ++indc_trngl)
            {
                for (int indc_vertc = 0; indc_vertc < 3; ++indc_vertc)
                {
                    puntos_textura[indc_celda][indc_trngl][indc_vertc] +=
                        ((float)indc_celda) * Vector{42.0f, 0.0f};
                }
            }
        }
    }

    void PresenciaTablero::punteaRejillaMuros(
        const std::vector<Coord> &posiciones_rejilla,
        PuntosHexagonos &puntos_rejilla)
    {

        puntos_rejilla.resize(posiciones_rejilla.size());
        std::vector<Vector> punto_hexgn{RejillaTablero::puntosHexagono};
        for (int indc_celda = 0; indc_celda < posiciones_rejilla.size(); ++indc_celda)
        {
            for (int indc_hexgn = 0; indc_hexgn < RejillaTablero::puntosHexagono; ++indc_hexgn)
            {
                Vector punto;
                if (indc_hexgn == 0)
                {
                    punto = RejillaTablero::centroHexagono(posiciones_rejilla[indc_celda]);
                }
                else
                {
                    punto = RejillaTablero::verticeHexagono(posiciones_rejilla[indc_celda], indc_hexgn);
                }
                punto_hexgn[indc_hexgn] = Vector{punto.x(), punto.y()};
            }

            puntos_rejilla[indc_celda][0] = {
                punto_hexgn[0],
                punto_hexgn[1],
                punto_hexgn[2]};
            puntos_rejilla[indc_celda][1] = {
                punto_hexgn[0],
                punto_hexgn[2],
                punto_hexgn[3]};
            puntos_rejilla[indc_celda][2] = {
                punto_hexgn[0],
                punto_hexgn[3],
                punto_hexgn[4]};
            puntos_rejilla[indc_celda][3] = {
                punto_hexgn[0],
                punto_hexgn[4],
                punto_hexgn[5]};
            puntos_rejilla[indc_celda][4] = {
                punto_hexgn[0],
                punto_hexgn[5],
                punto_hexgn[6]};
            puntos_rejilla[indc_celda][5] = {
                punto_hexgn[0],
                punto_hexgn[6],
                punto_hexgn[1]};
        }
    }

    void PresenciaTablero::estableceMallaMuros(
        const PuntosHexagonos &puntos_rejilla,
        const IndicesEstampas &indices_estampas,
        const PuntosHexagonos &puntos_textura)
    {
        this->malla_muros->define((int)puntos_rejilla.size() * 6);
        for (int indc_celda = 0; indc_celda < puntos_rejilla.size(); ++indc_celda)
        {
            for (int indc_trngl = 0; indc_trngl < 6; ++indc_trngl)
            {
                unir2d::TrianguloMalla trngl_malla{};
                for (int indc_vertc = 0; indc_vertc < 3; ++indc_vertc)
                {
                    trngl_malla.ponPunto(indc_vertc, puntos_rejilla[indc_celda][indc_trngl][indc_vertc]);
                    int indc_estmp = indices_estampas[indc_celda][indc_trngl];
                    trngl_malla.ponTexel(indc_vertc, puntos_textura[indc_estmp][indc_trngl][indc_vertc]);
                }
                this->malla_muros->asigna(indc_celda * 6 + indc_trngl, trngl_malla);
            }
        }
    }

    void PresenciaTablero::preparaPaneles()
    {

        textura_panel_vertcl = new unir2d::Textura{};
        textura_panel_vertcl->carga(JuegoMesaBase::carpetaActivos() + "panel_lateral.png");

        imagen_panel_vertcl_izqrd = new unir2d::Imagen{};
        imagen_panel_vertcl_izqrd->asigna(textura_panel_vertcl);
        imagen_panel_vertcl_izqrd->ponPosicion(regionPanelVertclIzqrd.posicion());

        imagen_panel_vertcl_derch = new unir2d::Imagen{};
        imagen_panel_vertcl_derch->asigna(textura_panel_vertcl);
        imagen_panel_vertcl_derch->ponPosicion(regionPanelVertclDerch.posicion());

        textura_panel_abajo = new unir2d::Textura{};
        textura_panel_abajo->carga(JuegoMesaBase::carpetaActivos() + "panel_abajo.png");

        imagen_panel_abajo_izqrd = new unir2d::Imagen{};
        imagen_panel_abajo_izqrd->asigna(textura_panel_abajo);
        imagen_panel_abajo_izqrd->ponPosicion(regionPanelAbajoIzqrd.posicion());

        imagen_panel_abajo_derch = new unir2d::Imagen{};
        imagen_panel_abajo_derch->asigna(textura_panel_abajo);
        imagen_panel_abajo_derch->ponPosicion(regionPanelAbajoDerch.posicion());

        float altura_bloque_izq = 3 * 135.0f;
        float y_bloque_izq = regionPanelVertclIzqrd.posicion().y() +
                             (tamanoPanelVertcl.y() - altura_bloque_izq) / 2.0f + 60.0f;

        float y_bandera_izq = y_bloque_izq - 90.0f;

        textura_bandera_izqrd = new unir2d::Textura();
        textura_bandera_izqrd->carga(JuegoMesaBase::carpetaActivos() + "bandera_izquierda.png");

        imagen_bandera_izqrd = new unir2d::Imagen();
        imagen_bandera_izqrd->asigna(textura_bandera_izqrd);
        imagen_bandera_izqrd->ponPosicion(Vector{
            regionPanelVertclIzqrd.posicion().x() + 10,
            y_bandera_izq});

        textura_escudo_izqrd = new unir2d::Textura();
        textura_escudo_izqrd->carga(actor_tablero->archivo_escudo_izqrd);

        imagen_escudo_izqrd = new unir2d::Imagen();
        imagen_escudo_izqrd->asigna(textura_escudo_izqrd);
        imagen_escudo_izqrd->ponPosicion(imagen_bandera_izqrd->posicion() + Vector{25.0f, 5.0f});

        float altura_bloque_derch = 3 * 135.0f;
        float y_bloque_derch = regionPanelVertclDerch.posicion().y() +
                               (tamanoPanelVertcl.y() - altura_bloque_derch) / 2.0f + 60.0f;

        float y_bandera_derch = y_bloque_derch - 90.0f;

        textura_bandera_derch = new unir2d::Textura();
        textura_bandera_derch->carga(JuegoMesaBase::carpetaActivos() + "bandera_derecha.png");

        imagen_bandera_derch = new unir2d::Imagen();
        imagen_bandera_derch->asigna(textura_bandera_derch);
        imagen_bandera_derch->ponPosicion(Vector{
            regionPanelVertclDerch.posicion().x() + 10,
            y_bandera_derch});

        textura_escudo_derch = new unir2d::Textura();
        textura_escudo_derch->carga(actor_tablero->archivo_escudo_derch);

        imagen_escudo_derch = new unir2d::Imagen();
        imagen_escudo_derch->asigna(textura_escudo_derch);

        imagen_escudo_derch->ponPosicion(imagen_bandera_derch->posicion() + Vector{25.0f, 5.0f});
    }

    void PresenciaTablero::liberaPaneles()
    {
        delete imagen_escudo_derch;
        imagen_escudo_derch = nullptr;
        delete textura_escudo_derch;
        textura_escudo_derch = nullptr;
        delete imagen_escudo_izqrd;
        imagen_escudo_izqrd = nullptr;
        delete textura_escudo_izqrd;
        textura_escudo_izqrd = nullptr;
        delete imagen_bandera_derch;
        imagen_bandera_derch = nullptr;
        delete textura_bandera_derch;
        textura_bandera_derch = nullptr;
        delete imagen_bandera_izqrd;
        imagen_bandera_izqrd = nullptr;
        delete textura_bandera_izqrd;
        textura_bandera_izqrd = nullptr;
        delete imagen_panel_abajo_izqrd;
        imagen_panel_abajo_izqrd = nullptr;
        delete imagen_panel_abajo_derch;
        imagen_panel_abajo_derch = nullptr;
        delete textura_panel_abajo;
        textura_panel_abajo = nullptr;
        delete imagen_panel_vertcl_derch;
        imagen_panel_vertcl_derch = nullptr;
        delete imagen_panel_vertcl_izqrd;
        imagen_panel_vertcl_izqrd = nullptr;
        delete textura_panel_vertcl;
        textura_panel_vertcl = nullptr;
    }

    void PresenciaTablero::preparaMonitor()
    {

        Vector pos_fondo = regionMonitor.posicion() + Vector{0, 0};

        textura_fondo_monitor = new unir2d::Textura{};
        textura_fondo_monitor->carga(JuegoMesaBase::carpetaActivos() + "monitor_fondo.png");

        imagen_fondo_monitor = new unir2d::Imagen{};
        imagen_fondo_monitor->asigna(textura_fondo_monitor);
        imagen_fondo_monitor->ponPosicion(pos_fondo);

        Vector pos_texto = pos_fondo + Vector{5, 12}; // ← ajusta según lo centrado que lo quieras
        for (int indc = 0; indc < lineas_texto_monitor; ++indc)
        {
            texto_monitor[indc] = new unir2d::Texto("Kingthings Petrock");
            texto_monitor[indc]->ponTamano(20);                // ligeramente más grande
            texto_monitor[indc]->ponColor(Color{0, 255, 180}); // verde esmeralda pirata brillante
            texto_monitor[indc]->ponCadena("Hola gente.");
            texto_monitor[indc]->ponPosicion(pos_texto);
            pos_texto += Vector{0, 18}; // más separación vertical
        }
    }

    void PresenciaTablero::liberaMonitor()
    {
        for (int indc = 0; indc < lineas_texto_monitor; ++indc)
        {
            delete texto_monitor[indc];
            texto_monitor[indc] = nullptr;
        }
        delete imagen_fondo_monitor;
        imagen_fondo_monitor = nullptr;
        delete textura_fondo_monitor;
        textura_fondo_monitor = nullptr;
    }

    void PresenciaTablero::preparaDisplay()
    {
        textura_marco_display = new unir2d::Textura{};
        textura_marco_display->carga(JuegoMesaBase::carpetaActivos() + "marco_display.png");

        imagen_marco_display = new unir2d::Imagen{};
        imagen_marco_display->asigna(textura_marco_display);
        imagen_marco_display->ponPosicion(PresenciaTablero::regionDisplay.posicion() + Vector{6, 34});
        imagen_marco_display->ponVisible(true);
        actor_tablero->agregaDibujo(imagen_marco_display);

        textura_digitos_display = new unir2d::Textura{};
        textura_digitos_display->carga(JuegoMesaBase::carpetaActivos() + "digitos_display.png");

        Vector poscn = imagen_marco_display->posicion() + Vector{6, 2};
        for (int indc = 0; indc < cuentaDigitosDisplay; ++indc)
        {
            imagenes_digitos_display[indc] = new unir2d::Imagen{};
            imagenes_digitos_display[indc]->asigna(textura_digitos_display);
            imagenes_digitos_display[indc]->ponPosicion(poscn);
            imagenes_digitos_display[indc]->defineEstampas(1, 11);
            imagenes_digitos_display[indc]->seleccionaEstampa(1, 11);
            imagenes_digitos_display[indc]->ponVisible(true);
            actor_tablero->agregaDibujo(imagenes_digitos_display[indc]);
            poscn += Vector{34, 0};
        }
    }

    void PresenciaTablero::liberaDisplay()
    {
        for (int indc = 0; indc < cuentaDigitosDisplay; ++indc)
        {
            delete imagenes_digitos_display[indc];
            imagenes_digitos_display[indc] = nullptr;
        }
        delete textura_digitos_display;
        textura_digitos_display = nullptr;
        delete imagen_marco_display;
        imagen_marco_display = nullptr;
        delete textura_marco_display;
        textura_marco_display = nullptr;
    }

    void PresenciaTablero::preparaAyuda()
    {
        textura_boton_ayuda = new unir2d::Textura{};
        textura_boton_ayuda->carga(JuegoMesaBase::carpetaActivos() + "boton_ayuda.png");

        imagen_boton_ayuda = new unir2d::Imagen{};
        imagen_boton_ayuda->asigna(textura_boton_ayuda);
        imagen_boton_ayuda->ponPosicion(posicion_ayuda);
        imagen_boton_ayuda->ponVisible(true);
        actor_tablero->agregaDibujo(imagen_boton_ayuda);

        imagen_interroga = new unir2d::Imagen{};
        imagen_interroga->ponPosicion(posicion_ayuda);
        imagen_interroga->ponVisible(true);
        actor_tablero->agregaDibujo(imagen_interroga);
    }

    void PresenciaTablero::liberaAyuda()
    {
        delete imagen_interroga;
        imagen_interroga = nullptr;
        delete textura_interroga;
        textura_interroga = nullptr;
        delete imagen_boton_ayuda;
        imagen_boton_ayuda = nullptr;
        delete textura_boton_ayuda;
        textura_boton_ayuda = nullptr;
    }

    void PresenciaTablero::preparaSonidos()
    {
        sonido_establece = new unir2d::Sonido{};
        sonido_establece->carga(actor_tablero->archivo_sonido_establece);
        sonido_establece->ponVolumen(actor_tablero->volumen_sonido_establece);
        sonido_desplaza = new unir2d::Sonido{};
        sonido_desplaza->carga(actor_tablero->archivo_sonido_desplaza);
        sonido_desplaza->ponVolumen(actor_tablero->volumen_sonido_desplaza);
        sonido_exito = new unir2d::Sonido{};
        sonido_exito->carga(actor_tablero->archivo_sonido_exito);
        sonido_exito->ponVolumen(actor_tablero->volumen_sonido_exito);
        sonido_fracaso = new unir2d::Sonido{};
        sonido_fracaso->carga(actor_tablero->archivo_sonido_fracaso);
        sonido_fracaso->ponVolumen(actor_tablero->volumen_sonido_fracaso);
    }

    void PresenciaTablero::liberaSonidos()
    {
        delete sonido_establece;
        sonido_establece = nullptr;
        delete sonido_desplaza;
        sonido_desplaza = nullptr;
        delete sonido_exito;
        sonido_exito = nullptr;
        delete sonido_fracaso;
        sonido_fracaso = nullptr;
    }

}