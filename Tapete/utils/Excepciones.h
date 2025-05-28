// proyecto: Grupal/Tapete
// archivo:  Excepciones.h
// versión:  2.1  (Abril-2025)


#pragma once

#include <stdexcept>
#include <string>
#include <exception>

namespace tapete {

/**
 * @brief Localizaciones dentro de la configuración que pueden generar errores.
 */
enum class LocalizaConfigura {
    Seccion_2_Modo_juego,            ///< Errores en sección 2: Modo de juego
    Seccion_3_Tablero_parte_2,       ///< Errores en sección 3: Tablero parte 2
    Seccion_3_Tablero_parte_3,       ///< Errores en sección 3: Tablero parte 3
    Seccion_4_Personajes_parte_1,    ///< Errores en sección 4: Personajes parte 1
    Seccion_4_Personajes_parte_3,    ///< Errores en sección 4: Personajes parte 3
    Seccion_5_Habilidades_parte_2,   ///< Errores en sección 5: Habilidades parte 2
    Seccion_6_Estadisticas_parte_2,  ///< Errores en sección 6: Estadísticas parte 2
    Seccion_7_Grados_efectividad_parte_2, ///< Errores en sección 7: Grados de efectividad parte 2
    Seccion_8_Habilidades_personajes,///< Errores en sección 8: Habilidades de personajes
    Seccion_9_Estadisticas_habilidades, ///< Errores en sección 9: Estadísticas de habilidades
    Seccion_10_Estadisticas_personajes, ///< Errores en sección 10: Estadísticas de personajes
    Seccion_11_Miscelanea           ///< Errores en sección 11: Miscelánea
};

class EstadoJuegoComun;
class ModoJuegoComun;

/**
 * @brief Excepción lanzada durante la fase de configuración.
 */
class ExcepcionConfigura : public std::logic_error {
public:
    /**
     * @brief Constructor indicando mensaje y localización.
     * @param mensaje Mensaje de error detallado (wide string).
     * @param localiza Localización en la configuración donde se produjo la excepción.
     */
    explicit ExcepcionConfigura(
            const std::wstring &mensaje,
            LocalizaConfigura localiza);

    /**
     * @brief Constructor indicando mensaje, descripción de lo que falló y localización.
     * @param mensaje Mensaje de error detallado.
     * @param lo_que Descripción del elemento concreto que falló.
     * @param localiza Localización en la configuración.
     */
    explicit ExcepcionConfigura(
            const std::wstring &mensaje,
            const std::string &lo_que,
            LocalizaConfigura localiza);

    /**
     * @brief Devuelve el mensaje de excepción.
     * @return Cadena de caracteres con la descripción del error.
     */
    const char * what() const noexcept override;

private:
    std::string mensaje; ///< Mensaje interno almacenado en formato narrow string
};

/**
 * @brief Excepción relativa al estado actual del juego.
 */
class ExcepcionEstado : public std::logic_error {
public:
    /**
     * @brief Constructor con estado actual.
     * @param estado Objeto que representa el estado de la máquina de estados.
     */
    explicit ExcepcionEstado(const EstadoJuegoComun &estado);

    /**
     * @brief Devuelve el mensaje de excepción generado.
     * @return Descripción del error.
     */
    const char * what() const noexcept override;

private:
    const EstadoJuegoComun &estado; ///< Referencia al estado que provocó la excepción
    std::string mensaje;           ///< Mensaje generado basándose en el estado
};

/**
 * @brief Excepción de validación de entradas y condiciones.
 */
class ExcepcionValidacion : public std::logic_error {
public:
    /**
     * @brief Constructor para errores de método dentro de un módulo.
     * @param modulo Nombre del módulo donde ocurre la validación.
     * @param metodo Nombre del método que realizó la validación.
     * @param explicacion Descripción de la condición violada.
     */
    explicit ExcepcionValidacion(
            const std::string &modulo,
            const std::string &metodo,
            const std::string &explicacion);

    /**
     * @brief Constructor para errores de atributo con condición.
     * @param atributo Nombre del atributo inválido.
     * @param condicion Condición que no se cumplió.
     */
    explicit ExcepcionValidacion(
            const std::string &atributo,
            const std::string &condicion);

    /**
     * @brief Obtiene el mensaje de error completo.
     * @return Cadena explicativa del fallo de validación.
     */
    const char * what() const noexcept override;

private:
    std::string atributo;  ///< Atributo que falló la validación
    std::string condicion; ///< Condición violada
    std::string mensaje;   ///< Mensaje interno
};

/**
 * @brief Excepción durante el proceso de juego, encapsula otra excepción.
 */
class ExcepcionProcesoJuego : public std::logic_error {
public:
    /**
     * @brief Constructor que envuelve una excepción interna.
     * @param clase Nombre de la clase donde ocurre el error.
     * @param metodo Nombre del método que falló.
     * @param excepcion Excepción original capturada.
     * @param modo   Objeto de modo de juego actual (referencia).
     */
    explicit ExcepcionProcesoJuego(
            const std::string &clase,
            const std::string &metodo,
            const std::exception &excepcion,
            ModoJuegoComun &modo);

    /**
     * @brief Devuelve el mensaje completo formado tras capturar la excepción.
     * @return Mensaje detallado del error.
     */
    const char * what() const noexcept override;

private:
    std::string clase;   ///< Nombre de la clase origen
    std::string metodo;  ///< Nombre del método origen
    std::string estado;  ///< Estado del modo de juego serialized
    const std::exception &excepcion; ///< Excepción interna
    const ModoJuegoComun &modo;       ///< Referencia al modo de juego

    std::string mensaje; ///< Mensaje construido por creaMensaje()

    /**
     * @brief Construye el mensaje completo combinando todos los datos.
     */
    void creaMensaje();
};

} // namespace tapete
