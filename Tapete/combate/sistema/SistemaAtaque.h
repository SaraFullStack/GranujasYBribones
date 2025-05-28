// proyecto: Grupal/Tapete
// archivo   SistemaAtaque.h
// versión:  2.1  (Abril-2025)
#pragma once

namespace tapete
{

    class SistemaAtaque
    {
    public:
        /*!
         * \brief Constructor que inicializa el sistema de ataque con una instancia de JuegoMesaBase.
         * \param juego Puntero al contexto del juego.
         */
        explicit SistemaAtaque(JuegoMesaBase *juego);

        /*!
         * \brief Destructor de la clase SistemaAtaque.
         */
        ~SistemaAtaque();

        /*!
         * \brief Obtiene la lista de grados de efectividad registrados.
         * \return Vector de punteros a GradoEfectividad.
         */
        const std::vector<GradoEfectividad *> &efectividades() const;

        /*!
         * \brief Agrega un nuevo grado de efectividad al sistema.
         * \param elemento Puntero al grado de efectividad.
         */
        void agregaEfectividad(GradoEfectividad *elemento);

        /*!
         * \brief Obtiene el personaje atacante actual.
         * \return Puntero al atacante.
         */
        ActorPersonaje *atacante() const;

        /*!
         * \brief Obtiene la habilidad utilizada en el ataque.
         * \return Puntero a la habilidad.
         */
        Habilidad *habilidad() const;

        /*!
         * \struct AtaqueOponente
         * \brief Almacena información detallada de un ataque a un oponente.
         */
        struct AtaqueOponente
        {
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

        /*!
         * \brief Obtiene la lista de ataques calculados para los oponentes.
         * \return Vector de AtaqueOponente.
         */
        const std::vector<AtaqueOponente> &ataquesOponente() const;

        /*!
         * \struct CuracionOponente
         * \brief Almacena información detallada de curaciones a un oponente.
         */
        struct CuracionOponente
        {
            ActorPersonaje *oponente;
            int valor_curacion;
            int vitalidad_origen;
            int vitalidad_final;
        };

        /*!
         * \brief Obtiene la lista de curaciones calculadas para los oponentes.
         * \return Vector de CuracionOponente.
         */
        const std::vector<CuracionOponente> &curacionesOponente() const;

        /*!
         * \struct CambioEfecto
         * \brief Almacena cambios de efectividad para ataque y defensa.
         */
        struct CambioEfecto
        {
            TipoAtaque *tipo_ataque;
            int valor_cambio_ataque;
            int valor_origen_ataque;
            int valor_final_ataque;
            TipoDefensa *tipo_defensa;
            int valor_cambio_defensa;
            int valor_origen_defensa;
            int valor_final_defensa;
        };

        /*!
         * \brief Obtiene la lista de cambios de efecto calculados.
         * \return Vector de CambioEfecto.
         */
        const std::vector<CambioEfecto> &cambiosEfecto() const;

        /*!
         * \brief Calcula ataques, curaciones y efectos para múltiples oponentes.
         * \param atacante Puntero al personaje atacante.
         * \param habilidad Puntero a la habilidad utilizada.
         */
        void calcula(
            ActorPersonaje *atacante,
            Habilidad *habilidad);

        /*!
         * \brief Calcula un único ataque especificando un oponente y un valor aleatorio.
         * \param atacante Puntero al personaje atacante.
         * \param habilidad Puntero a la habilidad utilizada.
         * \param oponente Puntero al oponente.
         * \param aleatorio_100 Valor aleatorio entre 0 y 100.
         */
        void calcula(
            ActorPersonaje *atacante,
            Habilidad *habilidad,
            ActorPersonaje *oponente,
            int aleatorio_100);

        /*!
         * \brief Calcula ataques para una lista de oponentes y un valor aleatorio.
         * \param atacante Puntero al personaje atacante.
         * \param habilidad Puntero a la habilidad utilizada.
         * \param lista_oponentes Vector de punteros a oponentes.
         * \param aleatorio_100 Valor aleatorio entre 0 y 100.
         */
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

        /*!
         * \brief Reinicia los contenedores internos antes de un nuevo cálculo.
         */
        void reinicia();

        /*!
         * \brief Calcula los detalles de un ataque para un oponente dado.
         * \param oponente Puntero al oponente.
         * \param aleatorio_100 Valor aleatorio entre 0 y 100.
         */
        void calculaAtaque(ActorPersonaje *oponente, int aleatorio_100);

        /*!
         * \brief Calcula los detalles de una curación para un oponente dado.
         * \param oponente Puntero al oponente.
         */
        void calculaCuracion(ActorPersonaje *oponente);
    };
}