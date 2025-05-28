// proyecto: Grupal/Tapete
// archivo:  CalculoCaminos.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete {


    class JuegoMesaBase;


    // Es admisible que la celda central:
    //      esté fuera del tablero, 
    //      esté en los muros o 
    //      esté ocupada por una ficha
    // El resto de las celdas aparecen cuando:
    //      no estan fuera del tablero y 
    //      no están en los muros
    using AreaCentradaCeldas = std::vector <std::vector <Coord>>;


    /* 
     * \class CalculoCaminos
     * \brief Proporciona utilidades para el cálculo de caminos y áreas en la rejilla del tablero.
     *
     * Incluye métodos estáticos para comprobar si una celda está en el tablero, en un muro u ocupada,
     * validar etapas y segmentos de camino, calcular áreas centradas en una celda y gestionar la geometría
     * necesaria para el movimiento y alcance en el juego.
     */
    class CalculoCaminos {
    public:
        /*!
         * \brief Comprueba si una celda está dentro de los límites del tablero.
         * \param celda Coordenada de la celda.
         * \return true si está en el tablero, false en caso contrario.
         */
        static bool celdaEnTablero (Coord celda);

        /*!
         * \brief Comprueba si una celda está ocupada por un muro.
         * \param juego Puntero al juego.
         * \param celda Coordenada de la celda.
         * \return true si está en un muro, false en caso contrario.
         */
        static bool celdaEnMuro    (JuegoMesaBase * juego, Coord celda);

        /*!
         * \brief Comprueba si una celda está ocupada por una ficha.
         * \param juego Puntero al juego.
         * \param celda Coordenada de la celda.
         * \return true si está ocupada, false en caso contrario.
         */
        static bool celdaOcupada   (JuegoMesaBase * juego, Coord celda);

        /*!
         * \brief Valida si una etapa de camino es válida.
         * \param juego Puntero al juego.
         * \param celda_destino_etapa Celda destino de la etapa.
         * \return true si la etapa es válida, false en caso contrario.
         */
        static bool etapaValidaCamino (JuegoMesaBase * juego, Coord celda_destino_etapa);

        /*!
         * \brief Valida si un segmento de camino entre dos celdas es válido.
         * \param juego Puntero al juego.
         * \param celda_origen Celda de origen.
         * \param celda_destino Celda de destino.
         * \return true si el segmento es válido, false en caso contrario.
         */
        static bool segmentoValido    (JuegoMesaBase * juego, Coord celda_origen, Coord celda_destino);

        /*!
         * \brief Calcula el área de celdas centrada en una celda dada y radio.
         * \param juego Puntero al juego.
         * \param celda_central Celda central.
         * \param radio_area Radio del área.
         * \param area_celdas Referencia al área de celdas resultante.
         */
        static void areaCeldas (
                JuegoMesaBase *      juego, 
                Coord                celda_central, 
                int                  radio_area, 
                AreaCentradaCeldas & area_celdas    );

    private:
        /*!
         * \struct EcuacionRecta
         * \brief Representa la ecuación de una recta en el plano.
         */
        struct EcuacionRecta {
            float a; /*!< Coeficiente de x */
            float b; /*!< Coeficiente de y */
            float c; /*!< Término independiente */
            float d; /*!< Magnitud del vector director */
        };

        /*!
         * \brief Calcula la dirección exacta y el cuadrante entre dos celdas.
         * \param celda_origen_etapa Celda de origen.
         * \param celda_destino_etapa Celda de destino.
         * \param direccion_exacta Dirección exacta resultante.
         * \param direccion_cuadrante Dirección de cuadrante resultante.
         */
        static void calculoDireccion (
                Coord celda_origen_etapa, Coord celda_destino_etapa,
                int & direccion_exacta, int & direccion_cuadrante   );

        /*!
         * \brief Valida si una etapa de camino exacto es válida.
         * \param juego Puntero al juego.
         * \param celda_origen_etapa Celda de origen.
         * \param celda_destino_etapa Celda de destino.
         * \param direccion_exacta Dirección exacta.
         * \return true si la etapa es válida, false en caso contrario.
         */
        static bool etapaValidaCaminoExacto (
                JuegoMesaBase * juego, 
                Coord celda_origen_etapa, Coord celda_destino_etapa, 
                int direccion_exacta                                );
        /*!
         * \brief Calcula la celda próxima en un camino exacto.
         * \param celda_sale Celda de salida.
         * \param direccion_exacta Dirección exacta.
         * \param celda_llega Celda de llegada resultante.
         */
        static void celdaProximaCaminoExacto (
                Coord celda_sale, int direccion_exacta,
                Coord & celda_llega                    );
        /*!
         * \brief Valida si una etapa de camino por cuadrante es válida.
         * \param juego Puntero al juego.
         * \param celda_origen_etapa Celda de origen.
         * \param celda_destino_etapa Celda de destino.
         * \param direccion_cuadrante Dirección de cuadrante.
         * \return true si la etapa es válida, false en caso contrario.
         */
        static bool etapaValidaCaminoCuadrante (
                JuegoMesaBase * juego, 
                Coord celda_origen_etapa, Coord celda_destino_etapa, 
                int direccion_cuadrante                             );
        /*!
         * \brief Calcula la celda próxima en un camino por cuadrante.
         * \param celda_sale Celda de salida.
         * \param direccion_cuadrante Dirección de cuadrante.
         * \param recta_etapa Ecuación de la recta de la etapa.
         * \param celda_llega Celda de llegada resultante.
         */
        static void celdaProximaCaminoCuadrante (
                Coord celda_sale, int direccion_cuadrante,
                const EcuacionRecta & recta_etapa, Coord & celda_llega);

        /*!
         * \brief Calcula la ecuación de una recta a partir de un vector director y un punto.
         * \param vector_director Vector director.
         * \param punto_recta Punto por el que pasa la recta.
         * \param recta Ecuación de la recta resultante.
         */
        static void calculaRecta (
                Vector vector_director, Vector punto_recta,
                CalculoCaminos::EcuacionRecta & recta      );
        /*!
         * \brief Calcula la distancia de un punto a una recta.
         * \param recta Ecuación de la recta.
         * \param punto Punto a medir.
         * \return Distancia.
         */
        static float distancia (const EcuacionRecta & recta, Vector punto);

        /*!
         * \brief Agrega un lado al área de celdas centrada.
         * \param juego Puntero al juego.
         * \param celda_central Celda central.
         * \param radio_lado Radio del lado.
         * \param origen_lado Origen del lado.
         * \param director_lado Vector director del lado.
         * \param area_celdas Referencia al área de celdas.
         */
        static void agregaLadoArea (
                JuegoMesaBase * juego, 
                Coord celda_central, int radio_lado, 
                Coord origen_lado, Coord director_lado, 
                AreaCentradaCeldas & area_celdas       );

        /*!
         * \brief Lanza una excepción si la condición no se cumple.
         * \param expresion Expresión booleana a comprobar.
         * \param mensaje Mensaje de error.
         */
        static void aserta (bool expresion, const string & mensaje);

    };


}

