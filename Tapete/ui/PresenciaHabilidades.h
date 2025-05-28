// proyecto: Grupal/Tapete
// archivo:  PresenciaHabilidades.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete {

/*!
 * \class PresenciaHabilidades
 * \brief Gestiona la visualización y los recursos gráficos y sonoros de las habilidades de los personajes.
 *
 * Permite obtener las imágenes de las habilidades y sus fondos para un personaje dado, así como gestionar
 * los recursos asociados (texturas, imágenes y sonidos). Facilita la preparación y liberación de recursos,
 * y asegura la correcta visualización e interacción de las habilidades en la interfaz del tablero.
 */
class PresenciaHabilidades {
public:
    /*!
     * \brief Devuelve las imágenes de las habilidades del personaje.
     * \param personaje Puntero al personaje.
     * \return Vector de punteros a las imágenes de las habilidades.
     */
    std::vector <unir2d::Imagen *> imagenesHabilidades(ActorPersonaje *personaje);

    /*!
     * \brief Devuelve las imágenes de los fondos de las habilidades del personaje.
     * \param personaje Puntero al personaje.
     * \return Vector de punteros a las imágenes de los fondos de habilidades.
     */
    std::vector <unir2d::Imagen *> imagenesFondosHabilidad(ActorPersonaje *personaje);

private:
    /*!
     * \brief Puntero al actor del tablero asociado.
     */
    ActorTablero *actor_tablero;

    /*!
     * \brief Vector de texturas de las habilidades.
     */
    std::vector <unir2d::Textura *> texturas_habilidades {};

    /*!
     * \brief Vector de texturas de los fondos de habilidades.
     */
    std::vector <unir2d::Textura *> texturas_fondos {};

    /*!
     * \brief Matriz de imágenes de habilidades por personaje.
     */
    std::vector <std::vector <unir2d::Imagen *>> imagenes_habilidades {};

    /*!
     * \brief Matriz de imágenes de fondos de habilidades por personaje.
     */
    std::vector <std::vector <unir2d::Imagen *>> imagenes_fondos {};

    // std::vector <unir2d::BuzonSonido *> buzones_sonidos_habilds {};

    /*!
     * \var sonidos_habilidades
     * \brief Vector de punteros a los sonidos asociados a las habilidades.
     *
     * Almacena los sonidos que se reproducen al activar o seleccionar cada habilidad del personaje,
     * permitiendo la gestión y reproducción de efectos sonoros específicos para cada habilidad en la interfaz.
     */
    std::vector <unir2d::Sonido *> sonidos_habilidades {};

    /*!
     * \brief Constructor explícito, solo accesible por clases amigas.
     * \param actor_personaje Puntero al actor del tablero asociado.
     */
    explicit PresenciaHabilidades(ActorTablero *actor_personaje);

    /*!
     * \brief Destructor.
     */
    ~PresenciaHabilidades();

    /*!
     * \brief Prepara los recursos gráficos y sonoros de las habilidades.
     */
    void prepara();

    /*!
     * \brief Libera los recursos gráficos y sonoros de las habilidades.
     */
    void libera();

    /*!
     * \brief Lanza una excepción si la condición no se cumple.
     * \param expresion Expresión booleana a comprobar.
     * \param mensaje Mensaje de error.
     */
    static void aserta(bool expresion, const string &mensaje);

    friend class ActorTablero;
};

}
