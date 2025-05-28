/// @file PresenciaTablero.h
/// @brief Definición de la presencia visual y lógica del tablero en el proyecto "Tapete".
/// @project Grupal/Tapete

#pragma once

#include <vector>
#include <array>
#include "Vector.h"
#include "Region.h"

namespace tapete {

class ActorTablero;

/**
 * @brief Clase que encapsula las regiones, texturas y elementos de interfaz del tablero.
 *
 * Gestiona la disposición y recursos gráficos del tablero, paneles y HUD.
 */
class PresenciaTablero {
public:
    /** @name Tamaños base del tablero y paneles */
    ///@{
    static constexpr Vector tamanoTablero{1710, 1010};        ///< Dimensiones totales del tablero
    static constexpr Vector tamanoPanelVertcl{110, 880};       ///< Tamaño de los paneles verticales
    static constexpr Vector tamanoRejilla{1480, 885};          ///< Tamaño de la rejilla de juego
    static constexpr Vector tamanoPanelAbajo{619, 120};        ///< Tamaño del panel inferior
    static constexpr float  margenPanelVertcl = 5.0f;          ///< Margen entre panel y borde
    ///@}

    /** @name Posicionamiento de panel vertical izquierdo */
    ///@{
    static constexpr Vector posicionPanelIzqrd{margenPanelVertcl, margenPanelVertcl};
    static constexpr Region regionPanelVertclIzqrd{posicionPanelIzqrd, tamanoPanelVertcl};
    ///@}

    /** @name Banda de acción superior */
    ///@{
    static constexpr Vector tamanoBandaAccion{tamanoPanelVertcl.x() * 2 + tamanoRejilla.x(), tamanoPanelAbajo.y()};
    static constexpr float filaBandaSuperior = -10.0f;         ///< Offset vertical de la banda
    static constexpr Vector posicionBandaSuperior{margenPanelVertcl, filaBandaSuperior};
    static constexpr Region regionBandaSuperior{posicionBandaSuperior, tamanoBandaAccion};
    ///@}

    /** @name Rejilla de celdas */
    ///@{
    static constexpr float columnaRejilla = regionPanelVertclIzqrd.x() + regionPanelVertclIzqrd.ancho();
    static constexpr float filaRejilla = regionBandaSuperior.y() + regionBandaSuperior.alto() - 10.0f;
    static constexpr Vector posicionRejilla{columnaRejilla, filaRejilla};
    static constexpr Region regionRejilla{posicionRejilla, tamanoRejilla};
    ///@}

    /** @name Panel vertical derecho */
    ///@{
    static constexpr float columnaPanelVertclDerch = columnaRejilla + tamanoRejilla.x();
    static constexpr Vector posicionPanelDerch{columnaPanelVertclDerch, margenPanelVertcl};
    static constexpr Region regionPanelVertclDerch{posicionPanelDerch, tamanoPanelVertcl};
    ///@}

    /** @name HUD - Display, Monitor y Ayuda */
    ///@{
    static constexpr Vector tamanoDisplay{90, tamanoBandaAccion.y()};    ///< Tamaño del display de PA
    static constexpr Vector tamanoMonitor{282, tamanoBandaAccion.y()};   ///< Tamaño del monitor de texto
    static constexpr Vector tamanoAyuda{90, tamanoBandaAccion.y()};       ///< Tamaño del botón de ayuda

    static constexpr Vector posicionDisplay = regionBandaSuperior.posicion();
    static constexpr Region regionDisplay{posicionDisplay, tamanoDisplay};

    static constexpr float columnaPanelAbajoIzqrd = regionDisplay.x() + regionDisplay.ancho();
    static constexpr Region regionPanelAbajoIzqrd{Vector{columnaPanelAbajoIzqrd, regionBandaSuperior.y()}, tamanoPanelAbajo};

    static constexpr float columnaMonitor = regionPanelAbajoIzqrd.x() + regionPanelAbajoIzqrd.ancho();
    static constexpr Region regionMonitor{Vector{columnaMonitor, regionBandaSuperior.y()}, tamanoMonitor};

    static constexpr float columnaPanelAbajoDerch = regionMonitor.x() + regionMonitor.ancho();
    static constexpr Region regionPanelAbajoDerch{Vector{columnaPanelAbajoDerch, regionBandaSuperior.y()}, tamanoPanelAbajo};

    static constexpr float columnaAyuda = regionPanelAbajoDerch.x() + regionPanelAbajoDerch.ancho();
    static constexpr Region regionAyuda{Vector{columnaAyuda, regionBandaSuperior.y()}, tamanoAyuda};
    ///@}

    /**
     * @brief Banda de acción inferior, no visible en pantalla por defecto.
     */
    static constexpr float filaBandaAbajo = tamanoTablero.y() + 100.0f;
    static constexpr Vector posicionBandaAbajo{margenPanelVertcl, filaBandaAbajo};
    static constexpr Region regionBandaAbajo{posicionBandaAbajo, tamanoBandaAccion};

private:
    static constexpr int estampasTexturaMuros = 5;    ///< Número de estampas en la textura de muros

    ActorTablero* actor_tablero;                    ///< Puntero al actor principal del tablero

    // Recursos gráficos del fondo y muros
    unir2d::Textura* textura_fondo{};               ///< Textura de fondo del tablero
    unir2d::Baldosas* baldosas_fondo{};            ///< Objeto de baldosas para el fondo
    unir2d::Textura* textura_muros{};               ///< Textura de muros
    unir2d::Malla* malla_muros{};                   ///< Malla de muros en el tablero

    // Paneles izquierdo y derecho
    unir2d::Textura* textura_panel_vertcl{};        ///< Textura genérica de panel vertical
    unir2d::Imagen* imagen_panel_vertcl_izqrd{};    ///< Imagen del panel vertical izquierdo
    unir2d::Imagen* imagen_panel_vertcl_derch{};    ///< Imagen del panel vertical derecho

    // Panel inferior
    unir2d::Textura* textura_panel_abajo{};         ///< Textura del panel inferior
    unir2d::Imagen* imagen_panel_abajo_izqrd{};     ///< Imagen izquierda panel inferior
    unir2d::Imagen* imagen_panel_abajo_derch{};     ///< Imagen derecha panel inferior

    // Banderas y escudos de los bandos
    unir2d::Textura* textura_bandera_izqrd{};       ///< Textura de la bandera izquierda
    unir2d::Imagen* imagen_bandera_izqrd{};         ///< Imagen de la bandera izquierda
    unir2d::Textura* textura_bandera_derch{};       ///< Textura de la bandera derecha
    unir2d::Imagen* imagen_bandera_derch{};         ///< Imagen de la bandera derecha
    unir2d::Textura* textura_escudo_izqrd{};        ///< Textura del escudo izquierdo
    unir2d::Imagen* imagen_escudo_izqrd{};          ///< Imagen del escudo izquierdo
    unir2d::Textura* textura_escudo_derch{};        ///< Textura del escudo derecho
    unir2d::Imagen* imagen_escudo_derch{};          ///< Imagen del escudo derecho

    static constexpr Color rojo_oxido{255, 50, 0};    ///< Color rojo óxido para acentos

    // Monitor de texto inferior
    unir2d::Textura* textura_fondo_monitor{};        ///< Textura de fondo del monitor
    unir2d::Imagen* imagen_fondo_monitor{};          ///< Imagen de fondo del monitor
    static constexpr int lineas_texto_monitor = 7;    ///< Número de líneas de texto en el monitor
    std::array<unir2d::Texto*, lineas_texto_monitor> texto_monitor{}; ///< Líneas de texto

    // Display de PA
    unir2d::Textura* textura_marco_display{};        ///< Textura del marco del display
    unir2d::Imagen* imagen_marco_display{};          ///< Imagen del marco del display
    unir2d::Textura* textura_digitos_display{};      ///< Textura de dígitos de display
    static constexpr int cuentaDigitosDisplay = 2;    ///< Dígitos mostrados en el display
    std::array<unir2d::Imagen*, cuentaDigitosDisplay> imagenes_digitos_display{}; ///< Dígitos individuales

    // Botón de ayuda
    static constexpr Vector posicion_ayuda{regionAyuda.posicion() + Vector{10, 26}}; ///< Posición del indicador de ayuda
    static constexpr float  radio_ayuda{33};                                           ///< Radio del área interactiva
    static constexpr Vector centro_ayuda{posicion_ayuda + Vector{radio_ayuda, radio_ayuda}}; ///< Centro del botón de ayuda
    unir2d::Textura* textura_boton_ayuda{};     ///< Textura del botón de ayuda
    unir2d::Imagen* imagen_boton_ayuda{};       ///< Imagen del botón de ayuda
    unir2d::Textura* textura_interroga{};       ///< Textura del icono de interrogación
    unir2d::Imagen* imagen_interroga{};         ///< Imagen del icono de interrogación

    // Sonidos de interacción
    unir2d::Sonido* sonido_establece{};         ///< Sonido al colocar elemento
    unir2d::Sonido* sonido_desplaza{};          ///< Sonido al desplazar elemento
    unir2d::Sonido* sonido_fracaso{};           ///< Sonido en caso de fallo
    unir2d::Sonido* sonido_exito{};             ///< Sonido en caso de éxito

    /// Índices de estampas para cada hexágono del muro
    using IndicesEstampas = std::vector<std::array<int, 6>>;
    /// Puntos de textura para mapeo en celdas hexagonales
    using PuntosHexagonos = std::vector<std::array<std::array<Vector, 3>, 6>>;

    /**
     * @brief Constructor privado, establece el actor asociado.
     * @param actor_tablero Puntero al actor del tablero
     */
    explicit PresenciaTablero(ActorTablero* actor_tablero);

    /**
     * @brief Destructor, libera todos los recursos gráficos y de sonido.
     */
    ~PresenciaTablero();

    /** @name Ciclo de vida de recursos */
    ///@{
    void prepara();      ///< Carga texturas, mallas y paneles
    void reprepara();    ///< Vuelve a preparar recursos tras un reinicio
    void libera();       ///< Libera texturas, mallas, imágenes y sonidos
    ///@}

    /** @name Preparación de componentes */
    ///@{
    void preparaBaldosas();  ///< Inicializa y configura las baldosas de fondo
    void preparaMuros();     ///< Crea y configura la malla de muros
    void preparaPaneles();   ///< Carga imágenes de los paneles
    void preparaMonitor();   ///< Configura el monitor de texto
    void preparaDisplay();   ///< Configura el display de PA
    void preparaAyuda();     ///< Prepara el botón de ayuda y su icono
    void preparaSonidos();   ///< Carga los sonidos de interacción
    ///@}

    /** @name Liberación de componentes */
    ///@{
    void liberaBaldosas();   ///< Libera recursos de baldosas
    void liberaMuros();      ///< Libera malla y texturas de muros
    void liberaPaneles();    ///< Libera texturas e imágenes de paneles
    void liberaMonitor();    ///< Libera recursos del monitor
    void liberaDisplay();    ///< Libera recursos del display
    void liberaAyuda();      ///< Libera recursos de ayuda
    void liberaSonidos();    ///< Libera sonidos de interacción
    ///@}

    /**
     * @brief Calcula los índices de estampas para los muros según posiciones.
     * @param posiciones_rejilla Lista de coordenadas de celdas en la rejilla
     * @param indices_estampas Vector de salida con índices de textura
     */
    void calculaEstampasMuros(
        const std::vector<Coord>& posiciones_rejilla,
        IndicesEstampas& indices_estampas);

    /**
     * @brief Determina el índice de estampado de muro según vecinos.
     * @param previo Indica si hay muro previo
     * @param adjunto Indica si hay muro adyacente
     * @param postrer Indica si hay muro posterior
     * @return Índice dentro de la textura
     */
    int estampaMuros(bool previo, bool adjunto, bool postrer);

    /**
     * @brief Crea puntos de textura para las celdas hexagonales.
     * @param puntos_textura Salida con coordenadas de los vértices texturizados
     */
    void punteaTexturaMuros(PuntosHexagonos& puntos_textura);

    /**
     * @brief Crea puntos de rejilla para las celdas hexagonales.
     * @param posiciones_rejilla Coordenadas de las celdas libres
     * @param puntos_rejilla Salida con coordenadas de malla hexagonal
     */
    void punteaRejillaMuros(
        const std::vector<Coord>& posiciones_rejilla,
        PuntosHexagonos& puntos_rejilla);

    /**
     * @brief Combina mallas y texturas para generar la malla final de muros.
     * @param puntos_rejilla Coordenadas de vértices en rejilla
     * @param indices_estampas Índices de textura asociados
     * @param puntos_textura Coordenadas de textura para cada vértice
     */
    void estableceMallaMuros(
        const PuntosHexagonos& puntos_rejilla,
        const IndicesEstampas& indices_estampas,
        const PuntosHexagonos& puntos_textura);

    friend class ActorTablero;  ///< ActorTablero puede acceder a la construcción privada
};

} // namespace tapete