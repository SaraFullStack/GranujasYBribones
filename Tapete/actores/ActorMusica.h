// proyecto: Grupal/Tapete
// archivo:  ActorMusica.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class JuegoMesaBase;

    class ActorMusica : public unir2d::ActorBase
    {
    public:
        /// <summary>
        /// Constructor: vincula este actor de música al juego.
        /// </summary>
        explicit ActorMusica(JuegoMesaBase *juego);

        /// <summary>
        /// Destructor: detiene y libera los recursos de sonido.
        /// </summary>
        ~ActorMusica();

        /// <summary>
        /// Obtiene la ruta del archivo de música actual.
        /// </summary>
        /// <returns>Cadena con la ruta al archivo de música.</returns>
        string archivoMusica();

        /// <summary>
        /// Obtiene el volumen de reproducción actual.
        /// </summary>
        /// <returns>Nivel de volumen (0–100).</returns>
        int volumenMusica();

        /// <summary>
        /// Asigna una nueva pista de música y establece su volumen.
        /// </summary>
        /// <param name="archivo_musica">Ruta al archivo de música.</param>
        /// <param name="volumen">Volumen de reproducción (0–100).</param>
        void asignaMusica(const string &archivo_musica, int volumen);

        /// <summary>
        /// Reduce gradualmente el volumen y detiene la música.
        /// </summary>
        void bajaMusica();

    protected:
        /// <summary>
        /// Inicializa el sistema de audio y comienza la reproducción.
        /// </summary>
        void inicia() override;

        /// <summary>
        /// Finaliza el actor de música y libera el sonido.
        /// </summary>
        void termina() override;

        /// <summary>
        /// Actualiza el actor cada fotograma.
        /// </summary>
        /// <param name="tiempo_seg">Tiempo transcurrido desde la última llamada (segundos).</param>
        void actualiza(double tiempo_seg) override;

    private:
        JuegoMesaBase *juego{};        ///< Contexto del juego.
        string archivo_musica{};       ///< Ruta del archivo de música.
        int volumen_musica{};          ///< Volumen actual.
        unir2d::Sonido *musica{};      ///< Objeto de sonido en reproducción.
        bool iniciada{};               ///< Indica si la música está activa.
    };

} // namespace tapete
