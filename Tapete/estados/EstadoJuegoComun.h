// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoComun.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{
    class EstadoJuegoComun
    {
    public:
        /*!
         * \brief Código del estado inicial del juego.
         */
        static constexpr int inicial = 0;
        /*!
         * \brief Código del estado terminal del juego.
         */
        static constexpr int terminal = 1;
        /*!
         * \brief Código para el inicio de una nueva jugada.
         */
        static constexpr int inicioJugada = 2;
        /*!
         * \brief Código para la preparación del desplazamiento de fichas.
         */
        static constexpr int preparacionDesplazamiento = 3;
        /*!
         * \brief Código para la marcación del camino de ficha.
         */
        static constexpr int marcacionCaminoFicha = 4;
        /*!
         * \brief Código cuando la habilidad simple es inválida.
         */
        static constexpr int habilidadSimpleInvalida = 5;
        /*!
         * \brief Código para confirmar una habilidad simple.
         */
        static constexpr int habilidadSimpleConfirmacion = 6;
        /*!
         * \brief Código para mostrar el resultado de la habilidad simple.
         */
        static constexpr int habilidadSimpleResultado = 7;
        /*!
         * \brief Código para preparar la habilidad de oponente.
         */
        static constexpr int preparacionHabilidadOponente = 8;
        /*!
         * \brief Código cuando la habilidad de oponente es inválida.
         */
        static constexpr int oponenteHabilidadInvalido = 9;
        /*!
         * \brief Código para confirmar la habilidad de oponente.
         */
        static constexpr int oponenteHabilidadConfirmacion = 10;
        /*!
         * \brief Código cuando la habilidad de oponente está calculando.
         */
        static constexpr int oponenteHabilidadCalculando = 11;
        /*!
         * \brief Código para mostrar el resultado de la habilidad de oponente.
         */
        static constexpr int oponenteHabilidadResultado = 12;
        /*!
         * \brief Código para preparar una habilidad de área.
         */
        static constexpr int preparacionHabilidadArea = 13;
        /*!
         * \brief Código cuando la habilidad de área es inválida.
         */
        static constexpr int areaHabilidadInvalida = 14;
        /*!
         * \brief Código para confirmar una habilidad de área.
         */
        static constexpr int areaHabilidadConfirmacion = 15;
        /*!
         * \brief Código cuando la habilidad de área está calculando.
         */
        static constexpr int areaHabilidadCalculando = 16;
        /*!
         * \brief Código para mostrar el resultado de la habilidad de área.
         */
        static constexpr int areaHabilidadResultado = 17;
        /*!
         * \brief Código para el modo de ayuda en pantalla.
         */
        static constexpr int mostrandoAyuda = 18;
        /*!
         * \brief Código para el estado de final de partida.
         */
        static constexpr int finalPartida = 19;

        /*!
         * \brief Constructor por defecto: inicializa el estado con inicial.
         */
        explicit EstadoJuegoComun();
        /*!
         * \brief Constructor desde un código específico.
         * \param codigo Código de estado.
         */
        EstadoJuegoComun(int codigo);

        /*!
         * \brief Conversión a entero para obtener el código de estado.
         * \return Código de estado.
         */
        operator int() const;

        /*!
         * \brief Realiza la transición al estado destino.
         * \param destino Estado destino.
         */
        void transita(const EstadoJuegoComun &destino);

        /*!
         * \brief Conserva el estado especificado sin transición.
         * \param estado Estado a conservar.
         */
        void conserva(const EstadoJuegoComun &estado);

        /*!
         * \brief Devuelve el nombre textual del estado.
         * \return Nombre del estado.
         */
        virtual const std::string nombre() const;

    protected:
        /*!
         * \brief Activar o desactivar trazado de transiciones.
         */
        inline static bool traza_transitos = true;

        /*!
         * \brief Establece el código interno del estado.
         * \param valor Nuevo código.
         */
        void ponCodigo(int valor);

        /*!
         * \brief Valida la transición al estado destino; lanza si inválida.
         * \param destino Estado destino.
         */
        virtual void valida(const EstadoJuegoComun &destino);

        /*!
         * \brief Asserción para la condición de transición.
         * \param destino Estado destino.
         * \param condicion Condición a validar.
         */
        void aserta(const EstadoJuegoComun &destino, bool condicion) const;

    private:
        /*!
         * \brief Código interno que representa el estado actual.
         */
        int codigo;

        // Se deshabilitan constructores y operadores de copia/movimiento
        EstadoJuegoComun(const EstadoJuegoComun &) = delete;
        EstadoJuegoComun(EstadoJuegoComun &&) = delete;
        EstadoJuegoComun &operator=(const EstadoJuegoComun &) = delete;
        EstadoJuegoComun &operator=(EstadoJuegoComun &&) = delete;
    };
    
}