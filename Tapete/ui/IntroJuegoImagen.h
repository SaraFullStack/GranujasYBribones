// archivo IntroJuegoImagen.h 

#pragma once
#include "tapete.h"

#include <UNIR-2D.h>

using namespace unir2d;


/* 
 * \class IntroJuegoImagen
 * \brief Gestiona la animación y visualización de una imagen de introducción en el juego.
 *
 * Permite mostrar imágenes animadas (tilesheet) con desplazamiento vertical y sincronización opcional con sonido.
 * Gestiona la carga de texturas, la animación por fotogramas, la reproducción de sonido y el ciclo de vida de los recursos gráficos.
 * Utilizado para la pantalla de introducción o escenas animadas en el juego.
 */
class IntroJuegoImagen : public ActorBase {
private:
    Textura* textura;                  /*!< Puntero a la textura de la imagen. */
    Imagen* imagen;                    /*!< Puntero al objeto imagen. */

    float posicion_x = 0;              /*!< Posición X actual de la imagen. */
    float posicion_y = 0;              /*!< Posición Y actual de la imagen. */
    float posicionInicialX;            /*!< Posición X inicial de la imagen. */
    float posicionInicialY;            /*!< Posición Y inicial de la imagen. */
    float velocidadDesplazamientoArriba; /*!< Velocidad de desplazamiento vertical. */
    int numeroDeFotogramasColumnas;    /*!< Número de columnas de fotogramas en el tilesheet. */
    int numeroDeFotogramasFilas;       /*!< Número de filas de fotogramas en el tilesheet. */
    int numeroDeFotogramas;            /*!< Número total de fotogramas. */
    int ultimoFotogramaReproducido = 0;/*!< Último fotograma reproducido. */
    bool bucle;                        /*!< Indica si la animación es en bucle. */
    bool conSonido;                    /*!< Indica si la animación tiene sonido asociado. */
    string pathSonido;                 /*!< Ruta del archivo de sonido. */
    Sonido* ptr_sonido;                /*!< Puntero al objeto de sonido. */

    /*!
     * \brief Inicializa la animación y recursos asociados.
     */
    void inicia() override;

    /*!
     * \brief Libera los recursos gráficos y de sonido.
     */
    void termina() override;

    /*!
     * \brief Actualiza la animación y posición de la imagen.
     * \param tiempo_seg Tiempo transcurrido en segundos.
     */
    void actualiza(double tiempo_seg) override;

public:
    /*!
     * \brief Constructor de la clase IntroJuegoImagen.
     * \param pathArchivo Ruta del archivo de imagen.
     * \param posicionInicialX Posición X inicial.
     * \param posicionInicialY Posición Y inicial.
     * \param velocidadDesplazamientoArriba Velocidad de desplazamiento vertical.
     * \param numeroDeFotogramasColumnas Número de columnas de fotogramas.
     * \param numeroDeFotogramasFilas Número de filas de fotogramas.
     * \param bucle Indica si la animación es en bucle.
     * \param pathSonido Ruta del archivo de sonido (opcional).
     */
    IntroJuegoImagen(const string pathArchivo, float posicionInicialX = 0,
        float posicionInicialY = 0, float velocidadDesplazamientoArriba = 0, int numeroDeFotogramasColumnas = 0, int numeroDeFotogramasFilas = 0, bool bucle = false, string pathSonido = "");
};


inline IntroJuegoImagen::IntroJuegoImagen(const string pathArchivo, float posicionInicialX, 
    float posicionInicialY, float velocidadDesplazamientoArriba, int numeroDeFotogramasColumnas, int numeroDeFotogramasFilas, bool bucle, string pathSonido) {
    
    this->posicionInicialX = posicionInicialX;
    this->posicionInicialY = posicionInicialY;
    this->velocidadDesplazamientoArriba = velocidadDesplazamientoArriba;
    this->numeroDeFotogramasColumnas = numeroDeFotogramasColumnas;
    this->numeroDeFotogramasFilas = numeroDeFotogramasFilas;
    this->numeroDeFotogramas = numeroDeFotogramasColumnas * numeroDeFotogramasFilas;
    this->bucle = bucle;
    this->pathSonido = pathSonido;

    textura = new Textura{};
    imagen = new Imagen{};
    textura->carga(pathArchivo);
    imagen->asigna(textura);
    agregaDibujo(imagen);
}

inline void IntroJuegoImagen::inicia() {
    // posicion inicial de la imagen de la pala
    //tenemos en cuenta tamaño pala y tamaño pantalla para que empieze centrada
    posicion_x = posicionInicialX;
    posicion_y = posicionInicialY;
    if(numeroDeFotogramasColumnas > 0 || numeroDeFotogramasFilas > 0)
        imagen->defineEstampas(numeroDeFotogramasFilas, numeroDeFotogramasColumnas);
    ponPosicion(Vector{ posicion_x, posicion_y });

    // comprueba si la imagen ha de ir sincronizada con alguna pista de audio
    if (pathSonido != "") {
        conSonido = true;
        ptr_sonido = new unir2d::Sonido{};
        ptr_sonido->abre(pathSonido);
    }
    else {
        conSonido = false;
    }
}

inline void IntroJuegoImagen::termina() {
    extraeDibujos();
    delete imagen;
    delete textura;
    if (conSonido) {
        delete ptr_sonido;
    }
}

inline void IntroJuegoImagen::actualiza(double tiempo_seg) {
    
    // si se trata de imagen con fotogramas tilesheet, congela el último fotograma hasta que finalize el tiempo
    if (numeroDeFotogramas > 0 && (bucle || (ultimoFotogramaReproducido != numeroDeFotogramas))) {
        int indice = ((int)(tiempo_seg * 10)) % numeroDeFotogramas + 1;
        // dispara pista de sonido a cada inicio de bucle
        if (indice == 1 && conSonido) {
            ptr_sonido->suena();
        }
        ultimoFotogramaReproducido = indice;
        int puntero = indice;
        int fila = 1;
        int columna = indice % numeroDeFotogramasColumnas;
        if (columna == 0)
            columna = numeroDeFotogramasColumnas;
        while (puntero > numeroDeFotogramasColumnas) {
            fila++;
            puntero -= numeroDeFotogramasColumnas;
        }
        imagen->seleccionaEstampa(fila, columna);

    }

    // si es imagen con scroll vertical
    if (velocidadDesplazamientoArriba > 0)
    {
        posicion_y -= velocidadDesplazamientoArriba;
        ponPosicion(Vector{ posicion_x, posicion_y });
    }
}


#pragma once
