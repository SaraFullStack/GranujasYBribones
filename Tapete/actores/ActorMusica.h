// proyecto: Grupal/Tapete
// archivo:  ActorMusica.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class JuegoMesaBase;

    /**
     * @brief Actor para la gestión de música en el juego.
     */
    class ActorMusica : public unir2d::ActorBase
    {
    public:
        /**
         * @brief Constructor: vincula este actor de música al juego.
         * @param juego Puntero al contexto del juego.
         */
        explicit ActorMusica(JuegoMesaBase *juego);

        /**
         * @brief Destructor: detiene y libera los recursos de sonido.
         */
        ~ActorMusica();

        /**
         * @brief Obtiene la ruta del archivo de música actual.
         * @return Cadena con la ruta al archivo de música.
         */
        string archivoMusica();

        /**
         * @brief Obtiene el volumen de reproducción actual.
         * @return Nivel de volumen (0–100).
         */
        int volumenMusica();

        /**
         * @brief Asigna una nueva pista de música y establece su volumen.
         * @param archivo_musica Ruta al archivo de música.
         * @param volumen Volumen de reproducción (0–100).
         */
        void asignaMusica(const string &archivo_musica, int volumen);

        /**
         * @brief Reduce gradualmente el volumen y detiene la música.
         */
        void bajaMusica();

    protected:
        /**
         * @brief Inicializa el sistema de audio y comienza la reproducción.
         */
        void inicia() override;

        /**
         * @brief Finaliza el actor de música y libera el sonido.
         */
        void termina() override;

        /**
         * @brief Actualiza el actor cada fotograma.
         * @param tiempo_seg Tiempo transcurrido desde la última llamada (segundos).
         */
        void actualiza(double tiempo_seg) override;

    private:
        JuegoMesaBase *juego{};   /**< Contexto del juego. */
        string archivo_musica{};  /**< Ruta del archivo de música. */
        int volumen_musica{};     /**< Volumen actual. */
        unir2d::Sonido *musica{}; /**< Objeto de sonido en reproducción. */
        bool iniciada{};          /**< Indica si la música está activa. */
    };

} /* namespace tapete */
