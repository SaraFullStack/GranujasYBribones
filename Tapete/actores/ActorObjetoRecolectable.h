/**
 * @file ActorObjetoRecolectable.h
 * @brief Definición de ActorObjetoRecolectable para objetos recolectables en el tablero.
 * @project Grupal/Tapete
 * @version 2.2 (Mayo-2025)
 */

#pragma once

#include "tapete.h"
#include "../ui/PresenciaFicha.h"

namespace tapete {

    /**
     * @class ActorObjetoRecolectable
     * @brief Actor que representa un objeto en el tablero que el jugador puede recolectar.
     *
     * Hereda de unir2d::ActorBase y gestiona su presencia gráfica mediante PresenciaFicha.
     * Puede otorgar curación o daño al personaje que lo recolecte.
     */
    class ActorObjetoRecolectable : public unir2d::ActorBase {
    public:
        /**
         * @enum TipoEfectoObjeto
         * @brief Tipos de efecto que puede tener el objeto recolectable.
         */
        enum class TipoEfectoObjeto {
            Dano,     /**< Inflige daño al recolectar. */
            Curacion  /**< Recupera vitalidad al recolectar. */
        };

        /**
         * @brief Constructor.
         * @param juego Puntero al juego base para contexto y gestión.
         * @param posicion Coordenada inicial del objeto en el tablero.
         * @param archivo Ruta al sprite que representa el objeto.
         */
        ActorObjetoRecolectable(JuegoMesaBase* juego, Coord posicion, const std::string& archivo);

        /**
         * @brief Destructor. Libera recursos gráficos y lógicos.
         */
        ~ActorObjetoRecolectable();

        /**
         * @brief Inicializa el actor: carga sprite y presencia.
         */
        void inicia() override;

        /**
         * @brief Actualiza el actor cada fotograma.
         * @param tiempo_seg Tiempo transcurrido desde la última actualización (s).
         */
        void actualiza(double tiempo_seg) override;

        /**
         * @brief Finaliza el actor: libera recursos.
         */
        void termina() override;

        /**
         * @brief Define el efecto que tendrá al recolectarse.
         * @param tipo_ Tipo de efecto (daño o curación).
         * @param valor_ Magnitud del efecto.
         */
        void ponEfecto(TipoEfectoObjeto tipo_, int valor_);

        /**
         * @brief Obtiene el tipo de efecto asignado.
         * @return TipoEfectoObjeto actual.
         */
        TipoEfectoObjeto tipoEfecto() const;

        /**
         * @brief Obtiene el valor del efecto asignado.
         * @return Valor numérico del efecto.
         */
        int valorEfecto() const;

        /**
         * @brief Indica si el objeto ya ha sido recolectado.
         * @return true si está recogido, false en caso contrario.
         */
        bool estaRecogido() const;

        /**
         * @brief Obtiene la posición actual de la ficha en el tablero.
         * @return Coordenada de la ficha.
         */
        Coord sitioFicha() const;

    private:
        JuegoMesaBase* juego{};            /**< Contexto del juego. */
        Coord pos{};                       /**< Posición en el tablero. */
        std::string archivo_ficha;         /**< Ruta al sprite del objeto. */
        bool recogido{ false };            /**< Estado de recolección. */

        TipoEfectoObjeto tipo{ TipoEfectoObjeto::Dano }; /**< Tipo de efecto. */
        int valor{ 20 };                                 /**< Magnitud del efecto. */

        PresenciaFicha ficha{ this };      /**< Gestor de presencia gráfica en el tablero. */
    };

} // namespace tapete