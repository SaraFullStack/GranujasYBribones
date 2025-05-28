// PresenciaFicha.h
#pragma once

#include <Textura.h>
#include <Imagen.h>
#include <ActorBase.h>
#include <Vector.h>

namespace tapete {

    /*!
     * \class PresenciaFicha
     * \brief Gestiona la visualización y manipulación de la ficha de un personaje en el tablero.
     *
     * Permite cargar la textura de la ficha, posicionarla en el tablero, mostrarla, ocultarla y ajustar su centro.
     * Gestiona los recursos gráficos asociados a la ficha y su ciclo de vida visual durante la partida.
     */
    class PresenciaFicha {
    public:
        /*!
         * \brief Constructor de la clase PresenciaFicha.
         * \param actor Puntero al actor base asociado a la ficha.
         */
        explicit PresenciaFicha(unir2d::ActorBase* actor);

        /*!
         * \brief Destructor de la clase PresenciaFicha.
         */
        ~PresenciaFicha();

        /*!
         * \brief Establece el archivo de textura de la ficha.
         * \param archivo Ruta del archivo de textura.
         */
        void ponArchivoFicha(const std::string& archivo);

        /*!
         * \brief Establece el centro de la ficha.
         * \param centro Vector con la posición del centro.
         */
        void ponCentro(const Vector& centro);

        /*!
         * \brief Muestra la ficha en el tablero.
         */
        void muestra();

        /*!
         * \brief Oculta la ficha del tablero.
         */
        void oculta();

        /*!
         * \brief Posiciona la ficha en una celda del tablero.
         * \param celda Coordenada de la celda.
         * \param offset Desplazamiento opcional respecto al centro de la celda (por defecto {16, 16}).
         */
        void posicionaEnCelda(Coord celda, const Vector& offset = Vector{ 16, 16 });

    private:
        unir2d::ActorBase* actor_base{};   /*!< Puntero al actor base asociado. */
        unir2d::Textura* textura_ficha{};  /*!< Puntero a la textura de la ficha. */
        unir2d::Imagen* imagen_ficha{};    /*!< Puntero a la imagen de la ficha. */
    };

}
