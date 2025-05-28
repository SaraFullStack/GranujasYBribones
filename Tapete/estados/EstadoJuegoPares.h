// proyecto: Grupal/Tapete
// archivo:  EstadoJuegoPares.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

class EstadoJuegoPares : public EstadoJuegoComun
{
public:
    /*!
     * \brief Código de estado que marca el inicio de una ronda.
     */
    static constexpr int inicioRonda = finalPartida + 1;

    /*!
     * \brief Código que marca el inicio de turno cuando ningún jugador ha sido elegido.
     */
    static constexpr int inicioTurnoNoElegidos = finalPartida + 2;

    /*!
     * \brief Código que marca el inicio de turno cuando un jugador ha sido elegido.
     */
    static constexpr int inicioTurnoElegidoUno = finalPartida + 3;

    /*!
     * \brief Código que marca el inicio de confirmación de turno.
     */
    static constexpr int inicioTurnoConfirmacion = finalPartida + 4;

    /*!
     * \brief Código que indica que se han agotado los puntos de acción.
     */
    static constexpr int agotadosPuntosAccion = finalPartida + 5;

    /*!
     * \brief Código que marca el final del turno.
     */
    static constexpr int finalTurno = finalPartida + 6;

    /*!
     * \brief Constructor que inicializa el estado con un código específico.
     * \param codigo Código de estado.
     */
    EstadoJuegoPares(int codigo);

    /*!
     * \brief Realiza la transición de este estado al estado destino en modalidad de pares.
     * \param destino Estado destino para la transición.
     */
    void transita(const EstadoJuegoPares &destino);

private:
    /*!
     * \brief Valida que la transición al estado destino sea permitida.
     * \param destino Estado común destino a validar.
     */
    void valida(const EstadoJuegoComun &destino) override;

    /*!
     * \brief Obtiene el nombre textual del estado para logging.
     * \return Nombre del estado.
     */
    const string nombre() const override;
};

}