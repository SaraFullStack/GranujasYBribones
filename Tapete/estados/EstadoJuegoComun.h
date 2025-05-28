// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoComun.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class EstadoJuegoComun
    {
    public:
        /// <summary>Código del estado inicial del juego.</summary>
        static constexpr int inicial = 0;
        /// <summary>Código del estado terminal del juego.</summary>
        static constexpr int terminal = 1;

        /// <summary>Código para el inicio de una nueva jugada.</summary>
        static constexpr int inicioJugada = 2;

        /// <summary>Código para la preparación del desplazamiento de fichas.</summary>
        static constexpr int preparacionDesplazamiento = 3;
        /// <summary>Código para la marcación del camino de ficha.</summary>
        static constexpr int marcacionCaminoFicha = 4;

        /// <summary>Código cuando la habilidad simple es inválida.</summary>
        static constexpr int habilidadSimpleInvalida = 5;
        /// <summary>Código para confirmar una habilidad simple.</summary>
        static constexpr int habilidadSimpleConfirmacion = 6;
        /// <summary>Código para mostrar el resultado de la habilidad simple.</summary>
        static constexpr int habilidadSimpleResultado = 7;

        /// <summary>Código para preparar la habilidad de oponente.</summary>
        static constexpr int preparacionHabilidadOponente = 8;
        /// <summary>Código cuando la habilidad de oponente es inválida.</summary>
        static constexpr int oponenteHabilidadInvalido = 9;
        /// <summary>Código para confirmar la habilidad de oponente.</summary>
        static constexpr int oponenteHabilidadConfirmacion = 10;
        /// <summary>Código cuando la habilidad de oponente está calculando.</summary>
        static constexpr int oponenteHabilidadCalculando = 11;
        /// <summary>Código para mostrar el resultado de la habilidad de oponente.</summary>
        static constexpr int oponenteHabilidadResultado = 12;

        /// <summary>Código para preparar una habilidad de área.</summary>
        static constexpr int preparacionHabilidadArea = 13;
        /// <summary>Código cuando la habilidad de área es inválida.</summary>
        static constexpr int areaHabilidadInvalida = 14;
        /// <summary>Código para confirmar una habilidad de área.</summary>
        static constexpr int areaHabilidadConfirmacion = 15;
        /// <summary>Código cuando la habilidad de área está calculando.</summary>
        static constexpr int areaHabilidadCalculando = 16;
        /// <summary>Código para mostrar el resultado de la habilidad de área.</summary>
        static constexpr int areaHabilidadResultado = 17;

        /// <summary>Código para el modo de ayuda en pantalla.</summary>
        static constexpr int mostrandoAyuda = 18;

        /// <summary>Código para el estado de final de partida.</summary>
        static constexpr int finalPartida = 19;

        /// <summary>Constructor por defecto: inicializa el estado con <c>inicial</c>.</summary>
        explicit EstadoJuegoComun();
        /// <summary>Constructor desde un código específico.</summary>
        EstadoJuegoComun(int codigo);

        /// <summary>Conversion a entero para obtener el código de estado.</summary>
        operator int() const;

        /// <summary>Realiza la transición al estado destino.</summary>
        void transita(const EstadoJuegoComun &destino);

        /// <summary>Conserva el estado especificado sin transición.</summary>
        void conserva(const EstadoJuegoComun &estado);

        /// <summary>Devuelve el nombre textual del estado.</summary>
        virtual const std::string nombre() const;

    protected:
        /// <summary>Activar o desactivar trazado de transiciones.</summary>
        inline static bool traza_transitos = true;

        /// <summary>Establece el código interno del estado.</summary>
        void ponCodigo(int valor);

        /// <summary>Valida la transición al estado destino; lanza si inválida.</summary>
        virtual void valida(const EstadoJuegoComun &destino);
        /// <summary>Asserción para la condición de transición.</summary>
        void aserta(const EstadoJuegoComun &destino, bool condicion) const;

    private:
        /// <summary>Código interno que representa el estado actual.</summary>
        int codigo;

        // Se deshabilitan constructores y operadores de copia/movimiento
        EstadoJuegoComun(const EstadoJuegoComun &) = delete;
        EstadoJuegoComun(EstadoJuegoComun &&) = delete;
        EstadoJuegoComun &operator=(const EstadoJuegoComun &) = delete;
        EstadoJuegoComun &operator=(EstadoJuegoComun &&) = delete;
    };

}