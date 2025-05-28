// proyecto: Grupal/Tapete
// archivo   SistemaAtaque.h
// versión:  2.1  (Abril-2025)
#pragma once

namespace tapete {

    class SistemaAtaque {
    public:
        /// <summary>Constructor que inicializa el sistema de ataque con una instancia de JuegoMesaBase.</summary>
        explicit SistemaAtaque(JuegoMesaBase *juego);
        /// <summary>Destructor de la clase SistemaAtaque.</summary>
        ~SistemaAtaque();

        /// <summary>Obtiene la lista de grados de efectividad registrados.</summary>
        const std::vector<GradoEfectividad *> &efectividades() const;
        /// <summary>Agrega un nuevo grado de efectividad al sistema.</summary>
        void agregaEfectividad(GradoEfectividad *elemento);

        /// <summary>Obtiene el personaje atacante actual.</summary>
        ActorPersonaje *atacante() const;
        /// <summary>Obtiene la habilidad utilizada en el ataque.</summary>
        Habilidad *habilidad() const;

        /// <summary>Estructura que almacena información detallada de un ataque a un oponente.</summary>
        struct AtaqueOponente {
            ActorPersonaje *oponente;
            TipoAtaque *tipo_ataque;
            int valor_ataque;
            TipoDefensa *tipo_defensa;
            int valor_defensa;
            int ventaja;
            int aleatorio_100;
            int valor_final_ataque;
            GradoEfectividad *efectividad;
            int porciento_dano;
            TipoDano *tipo_dano;
            int valor_dano;
            int valor_ajustado_dano;
            int valor_reduce_dano;
            int valor_final_dano;
            int vitalidad_origen;
            int vitalidad_final;
        };
        /// <summary>Obtiene la lista de ataques calculados para los oponentes.</summary>
        const std::vector<AtaqueOponente> &ataquesOponente() const;

        /// <summary>Estructura que almacena información detallada de curaciones a un oponente.</summary>
        struct CuracionOponente {
            ActorPersonaje *oponente;
            int valor_curacion;
            int vitalidad_origen;
            int vitalidad_final;
        };
        /// <summary>Obtiene la lista de curaciones calculadas para los oponentes.</summary>
        const std::vector<CuracionOponente> &curacionesOponente() const;

        /// <summary>Estructura que almacena cambios de efectividad para ataque y defensa.</summary>
        struct CambioEfecto {
            TipoAtaque *tipo_ataque;
            int valor_cambio_ataque;
            int valor_origen_ataque;
            int valor_final_ataque;
            TipoDefensa *tipo_defensa;
            int valor_cambio_defensa;
            int valor_origen_defensa;
            int valor_final_defensa;
        };
        /// <summary>Obtiene la lista de cambios de efecto calculados.</summary>
        const std::vector<CambioEfecto> &cambiosEfecto() const;

        /// <summary>Calcula ataques, curaciones y efectos para múltiples oponentes.</summary>
        void calcula(
            ActorPersonaje *atacante,
            Habilidad *habilidad);

        /// <summary>Calcula un único ataque especificando un oponente y un valor aleatorio.</summary>
        void calcula(
            ActorPersonaje *atacante,
            Habilidad *habilidad,
            ActorPersonaje *oponente,
            int aleatorio_100);

        /// <summary>Calcula ataques para una lista de oponentes y un valor aleatorio.</summary>
        void calcula(
            ActorPersonaje *atacante,
            Habilidad *habilidad,
            std::vector<ActorPersonaje *> lista_oponentes,
            int aleatorio_100);

    private:
        JuegoMesaBase *juego{};
        std::vector<GradoEfectividad *> grados_efectividad{};

        ActorPersonaje *atacante_{};
        Habilidad *habilidad_{};

        std::vector<AtaqueOponente> ataques_oponente{};
        std::vector<CuracionOponente> curaciones_oponente{};
        std::vector<CambioEfecto> cambios_efecto{};

        /// <summary>Reinicia los contenedores internos antes de un nuevo cálculo.</summary>
        void reinicia();

        /// <summary>Calcula los detalles de un ataque para un oponente dado.</summary>
        void calculaAtaque(ActorPersonaje *oponente, int aleatorio_100);
        /// <summary>Calcula los detalles de una curación para un oponente dado.</summary>
        void calculaCuracion(ActorPersonaje *oponente);

    };

}