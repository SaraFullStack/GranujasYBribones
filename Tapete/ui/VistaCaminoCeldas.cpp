// proyecto: Grupal/Tapete
// archivo   VistaCaminoCeldas.cpp
// versión:  2.1  (Abril-2025)

#include "tapete.h"

namespace tapete
{

    VistaCaminoCeldas::VistaCaminoCeldas(ActorTablero *actor_tablero)
    {
        this->actor_tablero = actor_tablero;
    }

    VistaCaminoCeldas::~VistaCaminoCeldas()
    {
        this->actor_tablero = nullptr;
    }

    void VistaCaminoCeldas::prepara()
    {
        if (textura_mdiana == nullptr)
        {
            textura_mdiana = new unir2d::Textura{};
            textura_mdiana->carga(JuegoMesaBase::carpetaActivos() + "microdiana.png");
        }
        trazos = new unir2d::Trazos{};
        trazos->ponIndiceZ(1);
        actor_tablero->agregaDibujo(trazos);

        celda_inicio_marcada = false;
    }

    void VistaCaminoCeldas::libera()
    {
        assert(imagenes_mdiana.size() == 0);
        assert(imagenes_mdiana_fijadas == 0);
        assert(imagen_mdiana_cache == nullptr);
        assert(!celda_inicio_marcada);

        delete trazos;
        trazos = nullptr;
        if (textura_mdiana != nullptr && textura_mdiana->cuentaUsos() == 0)
        {
            delete textura_mdiana;
            textura_mdiana = nullptr;
        }
    }

    void VistaCaminoCeldas::marcaCeldaInicio(Coord celda)
    {
        assert(!celda_inicio_marcada);
        assert(imagenes_mdiana.size() == 0);
        assert(imagenes_mdiana_fijadas == 0);

        agregaMicrodiana(celda, true, true);

        assert(imagenes_mdiana.size() == 1);
        assert(imagenes_mdiana_fijadas == 0);

        celda_inicio_marcada = true;
        camino_arrancado = false;
    }

    void VistaCaminoCeldas::desmarcaCeldaInicio()
    {

        assert(imagenes_mdiana.size() <= 1);
        assert(imagenes_mdiana_fijadas <= 1);

        if (imagenes_mdiana.size() == 0)
        {

            return;
        }
        if (imagenes_mdiana_fijadas == 1)
        {

            return;
        }

        assert(celda_inicio_marcada);
        assert(!camino_arrancado);
        assert(imagenes_mdiana.size() == 1);
        assert(imagenes_mdiana_fijadas == 0);

        extraeMicrodiana();

        assert(imagenes_mdiana.size() == 0);
        assert(imagenes_mdiana_fijadas == 0);

        celda_inicio_marcada = false;
    }

    bool VistaCaminoCeldas::celdaInicioMarcada()
    {
        return celda_inicio_marcada;
    }

    void VistaCaminoCeldas::arrancaCamino()
    {
        assert(celda_inicio_marcada);
        assert(!camino_arrancado);
        assert(imagenes_mdiana.size() == 1);
        assert(imagenes_mdiana_fijadas == 0);

        imagenes_mdiana_fijadas = 1;
        imagenes_mdiana[0]->seleccionaEstampa(1, 2); // cambia a color blanco

        celda_inicio_marcada = false;
        camino_arrancado = true;
        celda_etapa_marcada = false;
        celda_etapa_fijada = false;
    }

    void VistaCaminoCeldas::marcaCeldaEtapa(Coord celda, bool etapa_valida, Coord origen_trazo)
    {
        assert(camino_arrancado);
        assert(!celda_etapa_marcada);
        assert(imagenes_mdiana.size() >= 1);
        assert(imagenes_mdiana_fijadas == imagenes_mdiana.size());

        if (imagen_mdiana_cache == nullptr)
        {
            agregaMicrodiana(celda, true, etapa_valida);
        }
        else
        {
            descacheaMicrodiana(celda, true, etapa_valida);
        }
        agregaTrazado(celda, true, etapa_valida, origen_trazo);

        assert(imagenes_mdiana.size() >= 2);
        assert(imagenes_mdiana_fijadas == imagenes_mdiana.size() - 1);

        celda_etapa_marcada = true;
        celda_etapa_fijada = false;
    }

    void VistaCaminoCeldas::desmarcaCeldaEtapa()
    {
        if (imagenes_mdiana_fijadas == imagenes_mdiana.size())
        {

            assert(imagenes_mdiana.size() >= 1);
            return;
        }

        assert(camino_arrancado);
        assert(celda_etapa_marcada);
        assert(!celda_etapa_fijada);
        assert(imagenes_mdiana.size() >= 2);
        assert(imagenes_mdiana_fijadas >= imagenes_mdiana.size() - 1);

        cacheaMicrodiana();
        for (int indc = 0; indc < grosorTrazado; ++indc)
        {
            trazos->extreUltimaLinea();
        }

        assert(imagenes_mdiana.size() >= 1);
        assert(imagenes_mdiana_fijadas >= imagenes_mdiana.size());

        celda_etapa_marcada = false;
    }

    void VistaCaminoCeldas::fijaCeldaEtapa()
    {
        assert(camino_arrancado);
        assert(celda_etapa_marcada);
        assert(!celda_etapa_fijada);
        assert(imagenes_mdiana.size() >= 2);
        assert(imagenes_mdiana_fijadas == imagenes_mdiana.size() - 1);

        imagenes_mdiana_fijadas++;
        imagenes_mdiana.back()->seleccionaEstampa(1, 2);
        for (int indc = 1; indc <= grosorTrazado; ++indc)
        {
            trazos->ponColorLinea(static_cast<int>(trazos->lineas().size()) - indc, Color::Blanco);
        }

        assert(imagenes_mdiana.size() >= 2);
        assert(imagenes_mdiana_fijadas == imagenes_mdiana.size());

        celda_etapa_marcada = false;
        celda_etapa_fijada = true;
    }

    void VistaCaminoCeldas::vaciaCamino()
    {
        trazos->borraLineas();

        if (imagen_mdiana_cache != nullptr)
        {
            actor_tablero->extraeDibujo(imagen_mdiana_cache);
            delete imagen_mdiana_cache;
            imagen_mdiana_cache = nullptr;
        }

        imagenes_mdiana_fijadas = 0;
        for (unir2d::Imagen *imagn : imagenes_mdiana)
        {
            actor_tablero->extraeDibujo(imagn);
            delete imagn;
        }
        imagenes_mdiana.clear();

        celda_inicio_marcada = false;
    }

    void VistaCaminoCeldas::agregaMicrodiana(Coord celda, bool provisional, bool valida)
    {
        unir2d::Imagen *imagn = new unir2d::Imagen{};
        imagn->asigna(textura_mdiana);
        imagn->defineEstampas(1, 4);
        if (!valida)
        {
            imagn->seleccionaEstampa(1, 3);
        }
        else if (provisional)
        {
            imagn->seleccionaEstampa(1, 1);
        }
        else
        {
            imagn->seleccionaEstampa(1, 2);
        }
        Vector poscn = posicionMicrodiana(celda);
        imagn->ponPosicion(poscn);
        imagn->ponIndiceZ(1);
        imagenes_mdiana.push_back(imagn);
        actor_tablero->agregaDibujo(imagn);
    }

    void VistaCaminoCeldas::extraeMicrodiana()
    {
        unir2d::Imagen *imagn = imagenes_mdiana.back();
        imagenes_mdiana.pop_back();
        actor_tablero->extraeDibujo(imagn);
        delete imagn;
    }

    void VistaCaminoCeldas::agregaTrazado(Coord celda, bool provisional, bool valida, Coord origen)
    {
        Vector poscn_orign = RejillaTablero::centroHexagono(origen) +
                             PresenciaTablero::regionRejilla.posicion();
        Vector poscn_destn = RejillaTablero::centroHexagono(celda) +
                             PresenciaTablero::regionRejilla.posicion();
        static_assert(grosorTrazado == 5);
        std::array<Vector, grosorTrazado> tabla_orign{
            Vector{poscn_orign.x() + 1, poscn_orign.y()},
            Vector{poscn_orign.x() + 1, poscn_orign.y() - 1},
            Vector{poscn_orign.x(), poscn_orign.y()},
            Vector{poscn_orign.x() + 1, poscn_orign.y() + 1},
            Vector{poscn_orign.x() + 2, poscn_orign.y()}};
        std::array<Vector, grosorTrazado> tabla_destn{
            Vector{poscn_destn.x() + 1, poscn_destn.y()},
            Vector{poscn_destn.x() + 1, poscn_destn.y() - 1},
            Vector{poscn_destn.x(), poscn_destn.y()},
            Vector{poscn_destn.x() + 1, poscn_destn.y() + 1},
            Vector{poscn_destn.x() + 2, poscn_destn.y()}};
        Color color = Color::Negro;
        if (!valida)
        {
            color = Color::Rojo;
        }
        for (int indc = 0; indc < tabla_orign.size(); ++indc)
        {
            unir2d::TrazoLinea trazo{tabla_orign[indc], tabla_destn[indc], color};
            trazos->agrega(trazo);
        }
    }

    void VistaCaminoCeldas::cacheaMicrodiana()
    {
        imagen_mdiana_cache = imagenes_mdiana.back();
        imagenes_mdiana.pop_back();
        imagen_mdiana_cache->ponVisible(false);
    }

    void VistaCaminoCeldas::descacheaMicrodiana(Coord celda, bool provisional, bool valida)
    {
        if (!valida)
        {
            imagen_mdiana_cache->seleccionaEstampa(1, 3);
        }
        else if (provisional)
        {
            imagen_mdiana_cache->seleccionaEstampa(1, 1);
        }
        else
        {
            imagen_mdiana_cache->seleccionaEstampa(1, 2);
        }
        Vector poscn = posicionMicrodiana(celda);
        imagen_mdiana_cache->ponPosicion(poscn);
        imagenes_mdiana.push_back(imagen_mdiana_cache);
        imagen_mdiana_cache->ponVisible(true);
        imagen_mdiana_cache = nullptr;
    }

    Vector VistaCaminoCeldas::posicionMicrodiana(Coord coord)
    {
        Vector poscn = RejillaTablero::centroHexagono(coord);
        poscn += PresenciaTablero::regionRejilla.posicion();
        poscn -= Vector{10, 10};
        return poscn;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // métodos para depurar
    ////////////////////////////////////////////////////////////////////////////////////////////////


    //bool VistaCaminoCeldas::fichaMarcada () {
    //    return celda_inicio_marcada;
    //}


    //bool VistaCaminoCeldas::caminoArrancado () {
    //    return camino_arrancado;
    //}


    //bool VistaCaminoCeldas::celdaMarcada () {
    //    return celda_etapa_marcada;
    //}


    //bool VistaCaminoCeldas::celdaAgregada () {
    //    return celda_agregada;
    //}


    //int VistaCaminoCeldas::dianasVisibles () {
    //    return static_cast <int> (imagenes_mdiana.size ());
    //}


    //int VistaCaminoCeldas::dianasFijadas () {
    //    return imagenes_mdiana_fijadas;
    //}


}