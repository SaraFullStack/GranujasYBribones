// proyecto: Grupal/Tapete
// archivo:  EscritorAyuda.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    class ModoJuegoBase;


    /* 
     * \class EscritorAyuda
     * \brief Proporciona utilidades para mostrar y gestionar la ayuda contextual en el juego.
     *
     * Incluye métodos estáticos para escribir la ayuda general, de personaje, de cálculo, de habilidades,
     * ataques, curaciones y efectos, así como para borrar la ayuda y formatear párrafos para su visualización.
     * Facilita la presentación de información contextual y detallada al usuario durante la partida.
     */
    class EscritorAyuda {
    public:
        /*!
         * \brief Escribe la ayuda general del juego.
         * \param juego Referencia al juego.
         */
        static void escribeGeneral(JuegoMesaBase &juego);

        /*!
         * \brief Escribe la ayuda específica de un personaje.
         * \param juego Referencia al juego.
         * \param personaje Puntero al personaje.
         */
        static void escribePersonaje(JuegoMesaBase &juego, ActorPersonaje *personaje);

        /*!
         * \brief Escribe la ayuda de cálculo.
         * \param juego Referencia al juego.
         */
        static void escribeCalculo(JuegoMesaBase &juego);

        /*!
         * \brief Borra la ayuda mostrada.
         * \param juego Referencia al juego.
         */
        static void borra(JuegoMesaBase &juego);

        /*!
         * \brief Escribe la ayuda de una habilidad.
         * \param listado Referencia al listado de ayuda.
         * \param habilidad Puntero a la habilidad.
         */
        static void escribeHabilidad(
            ListadoAyuda &listado,
            Habilidad *habilidad);

        /*!
         * \brief Escribe la ayuda de un ataque.
         * \param listado Referencia al listado de ayuda.
         * \param sistema Referencia al sistema de ataque.
         * \param registro Referencia al registro de ataque de oponente.
         */
        static void escribeAtaque(
            ListadoAyuda &listado,
            const SistemaAtaque &sistema,
            const SistemaAtaque::AtaqueOponente &registro);

        /*!
         * \brief Escribe la ayuda de una curación.
         * \param listado Referencia al listado de ayuda.
         * \param sistema Referencia al sistema de ataque.
         * \param registro Referencia al registro de curación de oponente.
         */
        static void escribeCuracion(
            ListadoAyuda &listado,
            const SistemaAtaque &sistema,
            const SistemaAtaque::CuracionOponente &registro);

        /*!
         * \brief Escribe la ayuda de un efecto.
         * \param listado Referencia al listado de ayuda.
         * \param sistema Referencia al sistema de ataque.
         * \param registro Referencia al registro de cambio de efecto.
         */
        static void escribeEfecto(
            ListadoAyuda &listado,
            const SistemaAtaque &sistema,
            const SistemaAtaque::CambioEfecto &registro);

        /*!
         * \brief Divide un párrafo en líneas de una anchura máxima.
         * \param anchura Anchura máxima de cada línea.
         * \param parrafo Párrafo a dividir.
         * \return Vector de líneas resultantes.
         */
        static std::vector<wstring> parrafea(int anchura, const wstring &parrafo);
    };


}