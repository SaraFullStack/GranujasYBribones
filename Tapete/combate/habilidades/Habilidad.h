// proyecto: Grupal/Tapete
// archivo:  Habilidad.h
// versión:  2.1  (Abril-2025)
#pragma once

namespace tapete
{

    enum class EnfoqueHabilidad
    {
        si_mismo,
        personaje,
        area,
    };

    enum class AccesoHabilidad
    {
        ninguno,
        directo,
        indirecto,
    };

    enum class Antagonista
    {
        oponente,
        aliado,
        si_mismo
    };

    class Habilidad
    {
    public:
        /*!
         * \brief Constructor que inicializa la habilidad con su nombre, enfoque, acceso y antagonista.
         * \param nombre Nombre de la habilidad.
         * \param tipo_accion Tipo de enfoque de la habilidad.
         * \param tipo_acceso Tipo de acceso de la habilidad.
         * \param antagonista Antagonista de la habilidad.
         */
        explicit Habilidad(
            const std::wstring &nombre,
            EnfoqueHabilidad tipo_accion,
            AccesoHabilidad tipo_acceso,
            Antagonista antagonista);

        /*!
         * \brief Destructor de la clase Habilidad.
         */
        ~Habilidad();

        /*!
         * \brief Obtiene el nombre de la habilidad.
         * \return Nombre de la habilidad.
         */
        const std::wstring &nombre() const;

        /*!
         * \brief Obtiene el tipo de enfoque de la habilidad.
         * \return Tipo de enfoque.
         */
        EnfoqueHabilidad tipoEnfoque() const;

        /*!
         * \brief Obtiene el tipo de acceso de la habilidad.
         * \return Tipo de acceso.
         */
        AccesoHabilidad tipoAcceso() const;

        /*!
         * \brief Obtiene el antagonista de la habilidad.
         * \return Antagonista.
         */
        Antagonista antagonista() const;

        /*!
         * \brief Obtiene la descripción de la habilidad.
         * \return Descripción.
         */
        const std::wstring &descripcion() const;

        /*!
         * \brief Establece la descripción de la habilidad.
         * \param valor Nueva descripción.
         */
        void ponDescripcion(const std::wstring &valor);

        /*!
         * \brief Obtiene la ruta del archivo de imagen de la habilidad.
         * \return Ruta del archivo.
         */
        const std::string &archivoImagen() const;

        /*!
         * \brief Obtiene la ruta del archivo de fondo de imagen de la habilidad.
         * \return Ruta del archivo.
         */
        const std::string &archivoFondoImagen() const;

        /*!
         * \brief Establece los archivos de imagen y fondo de la habilidad.
         * \param archivo_imagen Ruta del archivo de imagen.
         * \param archivo_fondo Ruta del archivo de fondo.
         */
        void ponArchivosImagenes(const std::string &archivo_imagen, const std::string &archivo_fondo);

        /*!
         * \brief Obtiene la ruta del archivo de sonido de la habilidad.
         * \return Ruta del archivo.
         */
        const std::string &archivoSonido() const;

        /*!
         * \brief Establece el archivo de sonido de la habilidad.
         * \param archivo Ruta del archivo.
         */
        void ponArchivoSonido(const std::string &archivo);

        /*!
         * \brief Obtiene el coste en puntos de acción de la habilidad.
         * \return Coste en puntos de acción.
         */
        int coste() const;

        /*!
         * \brief Establece el coste en puntos de acción de la habilidad.
         * \param valor Nuevo coste.
         */
        void ponCoste(int valor);

        /*!
         * \brief Obtiene el alcance en casillas de la habilidad.
         * \return Alcance en casillas.
         */
        int alcance() const;

        /*!
         * \brief Establece el alcance en casillas de la habilidad.
         * \param valor Nuevo alcance.
         */
        void ponAlcance(int valor);

        /*!
         * \brief Obtiene el radio de área de la habilidad.
         * \return Radio de área.
         */
        int radioAlcance() const;

        /*!
         * \brief Establece el radio de área de la habilidad.
         * \param valor Nuevo radio.
         */
        void ponRadioAlcance(int valor);

        /*!
         * \brief Obtiene el tipo de ataque asociado.
         * \return Puntero al tipo de ataque.
         */
        TipoAtaque *tipoAtaque() const;

        /*!
         * \brief Asigna el tipo de ataque a la habilidad.
         * \param tipo_ataque Puntero al tipo de ataque.
         */
        void asignaAtaque(TipoAtaque *tipo_ataque);

        /*!
         * \brief Obtiene el tipo de defensa asociado.
         * \return Puntero al tipo de defensa.
         */
        TipoDefensa *tipoDefensa() const;

        /*!
         * \brief Asigna el tipo de defensa a la habilidad.
         * \param tipo_defensa Puntero al tipo de defensa.
         */
        void asignaDefensa(TipoDefensa *tipo_defensa);

        /*!
         * \brief Obtiene el tipo de daño asociado.
         * \return Puntero al tipo de daño.
         */
        TipoDano *tipoDano() const;

        /*!
         * \brief Obtiene el valor de daño de la habilidad.
         * \return Valor de daño.
         */
        int valorDano() const;

        /*!
         * \brief Asigna tipo y valor de daño a la habilidad.
         * \param tipo_dano Puntero al tipo de daño.
         * \param valor_dano Valor de daño.
         */
        void asignaDano(TipoDano *tipo_dano, int valor_dano);

        /*!
         * \brief Obtiene el valor de curación de la habilidad.
         * \return Valor de curación.
         */
        int valorCuracion() const;

        /*!
         * \brief Asigna el valor de curación de la habilidad.
         * \param valor Valor de curación.
         */
        void asignaCuracion(int valor);

        /*!
         * \brief Tipo para la lista de efectos de ataque.
         */
        using EfectosAtaque = std::vector<std::pair<TipoAtaque *, int>>;

        /*!
         * \brief Obtiene la lista de efectos de ataque.
         * \return Referencia constante a la lista.
         */
        const EfectosAtaque &efectosAtaque() const;

        /*!
         * \brief Agrega un efecto de ataque a la habilidad.
         * \param tipo_ataque Puntero al tipo de ataque.
         * \param valor Valor del efecto.
         */
        void agregaEfectoAtaque(TipoAtaque *tipo_ataque, int valor);

        /*!
         * \brief Tipo para la lista de efectos de defensa.
         */
        using EfectosDefensa = std::vector<std::pair<TipoDefensa *, int>>;

        /*!
         * \brief Obtiene la lista de efectos de defensa.
         * \return Referencia constante a la lista.
         */
        const EfectosDefensa &efectosDefensa() const;

        /*!
         * \brief Agrega un efecto de defensa a la habilidad.
         * \param tipo_defensa Puntero al tipo de defensa.
         * \param valor Valor del efecto.
         */
        void agregaEfectoDefensa(TipoDefensa *tipo_defensa, int valor);

        /*!
         * \brief Obtiene el índice interno de la habilidad.
         * \return Índice interno.
         */
        int indice() const;

        /*!
         * \brief Establece el índice interno de la habilidad.
         * \param valor Nuevo índice.
         */
        void ponIndice(int valor);

    private:
        std::wstring nombre_{};
        EnfoqueHabilidad tipo_accion{};
        AccesoHabilidad tipo_acceso{};
        Antagonista antagonista_{};

        int coste_{};
        int alcance_{};
        int radio_{};

        std::wstring descripcion_{};
        std::string archivo_imagen{};
        std::string archivo_fondo_imagen{};
        std::string archivo_sonido{};

        TipoAtaque *tipo_ataque{};
        TipoDefensa *tipo_defensa{};
        TipoDano *tipo_dano{};
        int valor_dano{};
        int valor_curacion{};
        EfectosAtaque efectos_ataque{};
        EfectosDefensa efectos_defensa{};

        int indice_{};
    };

}