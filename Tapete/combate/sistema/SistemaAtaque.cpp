// proyecto: Grupal/Tapete
// archivo   SistemaAtaque.cpp
// versión:  2.1  (Abril-2025)

#include "tapete.h"

namespace tapete
{

    SistemaAtaque::SistemaAtaque(JuegoMesaBase *juego)
    {
        this->juego = juego;
    }

    SistemaAtaque::~SistemaAtaque()
    {
        juego = nullptr;
        atacante_ = nullptr;
        habilidad_ = nullptr;
    }

    const std::vector<GradoEfectividad *> &SistemaAtaque::efectividades() const
    {
        return grados_efectividad;
    }

    void SistemaAtaque::agregaEfectividad(GradoEfectividad *elemento)
    {
        grados_efectividad.push_back(elemento);
    }

    ActorPersonaje *SistemaAtaque::atacante() const
    {
        return atacante_;
    }

    Habilidad *SistemaAtaque::habilidad() const
    {
        return habilidad_;
    }

    const std::vector<SistemaAtaque::AtaqueOponente> &SistemaAtaque::ataquesOponente() const
    {
        return ataques_oponente;
    }

    const std::vector<SistemaAtaque::CuracionOponente> &SistemaAtaque::curacionesOponente() const
    {
        return curaciones_oponente;
    }

    const std::vector<SistemaAtaque::CambioEfecto> &SistemaAtaque::cambiosEfecto() const
    {
        return cambios_efecto;
    }

    void SistemaAtaque::calcula(
        ActorPersonaje *atacante,
        Habilidad *habilidad)
    {
        assert(habilidad->tipoEnfoque() == EnfoqueHabilidad::si_mismo);
        assert(habilidad->tipoAcceso() == AccesoHabilidad::ninguno);
        assert(habilidad->antagonista() == Antagonista::si_mismo);

        reinicia();
        this->atacante_ = atacante;
        this->habilidad_ = habilidad;

        if (habilidad_->efectosAtaque().size() == 0 &&
            habilidad_->efectosDefensa().size() == 0)
        {
            throw std::logic_error{
                "Sistema de ataque mal configurado: habilidad auto-aplicada sin efectos definidos"};
        }

        for (const std::pair<TipoAtaque *, int> &pareja : habilidad_->efectosAtaque())
        {
            CambioEfecto registro{};

            registro.tipo_ataque = pareja.first;          // get<0> (pareja);
            registro.valor_cambio_ataque = pareja.second; // get<1> (pareja);
            registro.tipo_defensa = nullptr;

            if (!atacante_->apareceAtaque(registro.tipo_ataque))
            {
                throw std::logic_error{
                    "Sistema de ataque mal configurado, aplicando efecto en ataque: tipo de ataque no admitido por el atacante"};
            }
            registro.valor_origen_ataque = atacante_->valorAtaque(registro.tipo_ataque);
            atacante_->cambiaAtaque(registro.tipo_ataque, registro.valor_cambio_ataque);

            registro.valor_final_ataque = atacante_->valorAtaque(registro.tipo_ataque);

            cambios_efecto.push_back(registro);
        }
        for (const std::pair<TipoDefensa *, int> &pareja : habilidad_->efectosDefensa())
        {
            CambioEfecto registro{};

            registro.tipo_ataque = nullptr;
            registro.tipo_defensa = pareja.first;          // get<0> (pareja);
            registro.valor_cambio_defensa = pareja.second; // get<1> (pareja);

            if (!atacante_->apareceDefensa(registro.tipo_defensa))
            {
                throw std::logic_error{
                    "Sistema de ataque mal configurado, aplicando efecto en defensa: tipo de defensa no admitido por el atacante"};
            }
            registro.valor_origen_defensa = atacante_->valorDefensa(registro.tipo_defensa);
            atacante_->cambiaDefensa(registro.tipo_defensa, registro.valor_cambio_defensa);

            registro.valor_final_defensa = atacante_->valorDefensa(registro.tipo_defensa);

            cambios_efecto.push_back(registro);
        }
    }

    void SistemaAtaque::calcula(
        ActorPersonaje *atacante,
        Habilidad *habilidad,
        ActorPersonaje *oponente,
        int aleatorio_100)
    {
        assert(habilidad->tipoEnfoque() == EnfoqueHabilidad::personaje);
        assert(habilidad->tipoAcceso() == AccesoHabilidad::directo ||
               habilidad->tipoAcceso() == AccesoHabilidad::indirecto);
        assert(habilidad->antagonista() == Antagonista::oponente ||
               habilidad->antagonista() == Antagonista::aliado);

        reinicia();
        this->atacante_ = atacante;
        this->habilidad_ = habilidad;

        if (habilidad_->antagonista() == Antagonista::oponente)
        {
            calculaAtaque(oponente, aleatorio_100);
        }
        else
        {
            calculaCuracion(oponente);
        }
    }

    void SistemaAtaque::calcula(
        ActorPersonaje *atacante,
        Habilidad *habilidad,
        std::vector<ActorPersonaje *> lista_oponentes,
        int aleatorio_100)
    {
        assert(habilidad->tipoEnfoque() == EnfoqueHabilidad::area);
        assert(habilidad->tipoAcceso() == AccesoHabilidad::directo ||
               habilidad->tipoAcceso() == AccesoHabilidad::indirecto);
        assert(habilidad->antagonista() == Antagonista::oponente ||
               habilidad->antagonista() == Antagonista::aliado);

        reinicia();
        this->atacante_ = atacante;
        this->habilidad_ = habilidad;

        ataques_oponente.clear();
        curaciones_oponente.clear();
        cambios_efecto.clear();

        for (ActorPersonaje *oponente : lista_oponentes)
        {
            if (habilidad_->antagonista() == Antagonista::oponente)
            {
                calculaAtaque(oponente, aleatorio_100);
            }
            else
            {
                calculaCuracion(oponente);
            }
        }
    }

    void SistemaAtaque::reinicia()
    {
        atacante_ = nullptr;
        habilidad_ = nullptr;
        ataques_oponente.clear();
        curaciones_oponente.clear();
        cambios_efecto.clear();
    }

    void SistemaAtaque::calculaAtaque(ActorPersonaje *oponente, int aleatorio_100)
    {
        assert(habilidad_->antagonista() == Antagonista::oponente);

        AtaqueOponente registro{};
        registro.oponente = oponente;

        registro.tipo_ataque = habilidad_->tipoAtaque();

        if (registro.tipo_ataque == nullptr)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: tipo de ataque no establecido en la habilidad"};
        }

        if (!atacante_->apareceAtaque(registro.tipo_ataque))
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: tipo de ataque no admitido por el atacante"};
        }
        registro.valor_ataque = atacante_->valorAtaque(registro.tipo_ataque);

        if (registro.valor_ataque <= 0 || ActorPersonaje::maximaVitalidad < registro.valor_ataque)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: valor de ataque inválido"};
        }

        registro.tipo_defensa = habilidad_->tipoDefensa();

        if (registro.tipo_defensa == nullptr)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: tipo de defensa no establecido en la habilidad"};
        }

        if (!oponente->apareceDefensa(registro.tipo_defensa))
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: tipo de ataque no admitido por el oponente"};
        }
        registro.valor_defensa = oponente->valorDefensa(registro.tipo_defensa);

        if (registro.valor_defensa <= 0 || ActorPersonaje::maximaVitalidad < registro.valor_defensa)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: valor de defensa inválido"};
        }

        registro.ventaja = registro.valor_ataque - registro.valor_defensa;
        registro.aleatorio_100 = aleatorio_100;
        registro.valor_final_ataque = registro.ventaja + registro.aleatorio_100;

        if (grados_efectividad.size() == 0)
        {
            throw std::logic_error{"Sistema de ataque mal configurado: grados de efectividad no configurados"};
        }

        for (GradoEfectividad *efectividad : grados_efectividad)
        {
            if (registro.valor_final_ataque <= efectividad->valorSuperiorAtaque())
            {
                registro.efectividad = efectividad;
                registro.porciento_dano = efectividad->porcentajeDano();
                break;
            }
        }

        registro.tipo_dano = habilidad_->tipoDano();

        if (registro.tipo_dano == nullptr)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: tipo de daño no establecido en la habilidad"};
        }
        registro.valor_dano = habilidad_->valorDano();

        if (registro.valor_dano <= 0 || ActorPersonaje::maximaVitalidad < registro.valor_dano)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: valor de daño inválido"};
        }
        registro.valor_ajustado_dano = (int)(registro.valor_dano * (((float)registro.porciento_dano) / 100.0f));

        if (!oponente->apareceReduceDano(registro.tipo_dano))
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: reducción de daño no establecido en el oponente"};
        }
        registro.valor_reduce_dano = oponente->valorReduceDano(registro.tipo_dano);

        if (registro.valor_dano < 0 || ActorPersonaje::maximaVitalidad < registro.valor_dano)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando ataque: valor de reducción de daño inválido"};
        }
        registro.valor_final_dano = registro.valor_ajustado_dano - registro.valor_reduce_dano;

        registro.vitalidad_origen = oponente->vitalidad();
        registro.vitalidad_final = oponente->vitalidad();
        if (registro.vitalidad_final > 0)
        {
            registro.vitalidad_final -= registro.valor_final_dano;
            if (registro.vitalidad_final < 0)
            {
                registro.vitalidad_final = 0;
            }
            if (registro.vitalidad_final > ActorPersonaje::maximaVitalidad)
            {
                registro.vitalidad_final = ActorPersonaje::maximaVitalidad;
            }
            oponente->ponVitalidad(registro.vitalidad_final);
        }

        ataques_oponente.push_back(registro);
    }

    void SistemaAtaque::calculaCuracion(ActorPersonaje *oponente)
    {

        assert(habilidad_->antagonista() == Antagonista::aliado);

        CuracionOponente registro{};
        registro.oponente = oponente;

        if (habilidad_->valorCuracion() == 0)
        {
            throw std::logic_error{"Sistema de ataque mal configurado, aplicando curación: curación no establecida en la habilidad"};
        }
        registro.valor_curacion = habilidad_->valorCuracion();

        registro.vitalidad_origen = oponente->vitalidad();
        registro.vitalidad_final = oponente->vitalidad();
        if (registro.vitalidad_final > 0)
        {
            registro.vitalidad_final += registro.valor_curacion;
            if (registro.vitalidad_final < 0)
            {
                registro.vitalidad_final = 0;
            }
            if (registro.vitalidad_final > ActorPersonaje::maximaVitalidad)
            {
                registro.vitalidad_final = ActorPersonaje::maximaVitalidad;
            }
            oponente->ponVitalidad(registro.vitalidad_final);
        }

        curaciones_oponente.push_back(registro);
    }

}