/// @file ListadoAyuda.h
/// @brief Clase para gestionar y mostrar un listado de ayuda con desplazamiento y estilos.
/// @project Grupal/Tapete
/// @version 2.1 (Abril-2025)

#pragma once

namespace tapete {

class ActorTablero;

/**
 * @brief Muestra un panel de ayuda desplazable con estilos de texto.
 *
 * Permite escribir líneas de ayuda en negrita o claro, gestionar saltos de línea,
 * borrar contenido, desplazar el listado y mostrar/ocultar el panel.
 */
class ListadoAyuda {
public:
    static constexpr int lineasTextoListado = 56; ///< Número máximo de líneas de ayuda

    /**
     * @brief Activa el estilo de texto en negrita.
     */
    void enNegrita();

    /**
     * @brief Activa el estilo de texto claro (no negrita).
     */
    void enClaro();

    /**
     * @brief Escribe un texto y avanza a la siguiente línea.
     * @param texto Cadena de texto C wide string.
     */
    void escribe(const wchar_t* texto);

    /**
     * @brief Escribe un texto y avanza a la siguiente línea.
     * @param texto Cadena de texto wstring.
     */
    void escribe(const std::wstring& texto);

    /**
     * @brief Inserta un salto de línea sin escribir texto.
     */
    void saltaLinea();

    /**
     * @brief Borra todo el contenido del listado.
     */
    void borra();

    /**
     * @brief Obtiene la línea actual donde se escribirá el siguiente texto.
     * @return Índice de la línea actual.
     */
    int linea();

    /**
     * @brief Desplaza el listado hacia arriba.
     */
    void deslizaArriba();

    /**
     * @brief Desplaza el listado hacia abajo.
     */
    void deslizaAbajo();

    /**
     * @brief Hace visible el panel de ayuda.
     */
    void muestra();

    /**
     * @brief Oculta el panel de ayuda.
     */
    void oculta();

private:
    static constexpr Vector tamano{600, 800}; ///< Tamaño del panel de ayuda
    static constexpr Vector posicion{PresenciaTablero::regionRejilla.posicion() +
                                     0.5f * PresenciaTablero::tamanoRejilla -
                                     0.5f * tamano};                  ///< Posición centrada en la rejilla
    static constexpr Region region{posicion, tamano}; ///< Región completa del panel de ayuda
    static constexpr int cuentaBoquetes = 40;         ///< Número de boquetes en bordes
    static constexpr int cuentaTrazos = 80;           ///< Número de trazos para sombreado

    ActorTablero* actor_tablero; ///< Puntero al actor del tablero para coordinación

    bool visible{}; ///< Indica si el panel está visible

    unir2d::Rectangulo* papel;                                 ///< Fondo del listado
    std::array<unir2d::Circulo*, cuentaBoquetes> boquetes_izqrd;///< Boquetes en borde izquierdo
    std::array<unir2d::Circulo*, cuentaBoquetes> boquetes_derch;///< Boquetes en borde derecho
    unir2d::Trazos* trazos_izqrd;                               ///< Sombreado izquierdo
    unir2d::Trazos* trazos_derch;                               ///< Sombreado derecho
    unir2d::Rectangulo* sombra_derch;                           ///< Sombra lateral derecha
    unir2d::Rectangulo* sombra_abajo;                           ///< Sombra inferior

    std::array<unir2d::Texto*, lineasTextoListado> texto_claro; ///< Texto en estilo claro
    std::array<unir2d::Texto*, lineasTextoListado> texto_oscuro;///< Texto en estilo negrita
    unir2d::Texto* sigue_arriba;                                ///< Indicador de más arriba
    unir2d::Texto* sigue_abajo;                                 ///< Indicador de más abajo

    std::vector<bool> negrita_linea; ///< Estado de negrita de cada línea
    std::vector<std::wstring> cadena_linea; ///< Contenido de cada línea

    int linea_actual{};   ///< Índice de línea donde escribir
    bool negrita_actual{};///< Estilo de escritura actual
    int bajante{};        ///< Offset de desplazamiento vertical

    /**
     * @brief Constructor privado, inicializa con el actor de tablero.
     * @param actor_tablero Puntero al actor del tablero.
     */
    explicit ListadoAyuda(ActorTablero* actor_tablero);

    /**
     * @brief Destructor, libera todos los recursos gráficos.
     */
    ~ListadoAyuda();

    /**
     * @brief Carga recursos gráficos e inicializa estructuras.
     */
    void prepara();

    /**
     * @brief Libera recursos gráficos e imágenes.
     */
    void libera();

    /**
     * @brief Renderiza todas las líneas en pantalla.
     */
    void escribeLineas();

    /**
     * @brief Renderiza indicadores de desplazamiento si aplica.
     */
    void escribeSigue();

    friend class ActorTablero; ///< ActorTablero gestiona la creación y destrucción
};

} // namespace tapete
