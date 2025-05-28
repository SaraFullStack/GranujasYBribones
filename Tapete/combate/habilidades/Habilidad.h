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
        /// <summary>Constructor que inicializa la habilidad con su nombre, enfoque, acceso y antagonista.</summary>
        explicit Habilidad(
            const std::wstring &nombre,
            EnfoqueHabilidad tipo_accion,
            AccesoHabilidad tipo_acceso,
            Antagonista antagonista);
        /// <summary>Destructor de la clase Habilidad.</summary>
        ~Habilidad();

        /// <summary>Obtiene el nombre de la habilidad.</summary>
        const std::wstring &nombre() const;
        /// <summary>Obtiene el tipo de enfoque de la habilidad.</summary>
        EnfoqueHabilidad tipoEnfoque() const;
        /// <summary>Obtiene el tipo de acceso de la habilidad.</summary>
        AccesoHabilidad tipoAcceso() const;
        /// <summary>Obtiene el antagonista de la habilidad.</summary>
        Antagonista antagonista() const;

        /// <summary>Obtiene la descripción de la habilidad.</summary>
        const std::wstring &descripcion() const;
        /// <summary>Establece la descripción de la habilidad.</summary>
        void ponDescripcion(const std::wstring &valor);

        /// <summary>Obtiene la ruta del archivo de imagen de la habilidad.</summary>
        const std::string &archivoImagen() const;
        /// <summary>Obtiene la ruta del archivo de fondo de imagen de la habilidad.</summary>
        const std::string &archivoFondoImagen() const;
        /// <summary>Establece los archivos de imagen y fondo de la habilidad.</summary>
        void ponArchivosImagenes(const std::string &archivo_imagen, const std::string &archivo_fondo);

        /// <summary>Obtiene la ruta del archivo de sonido de la habilidad.</summary>
        const std::string &archivoSonido() const;
        /// <summary>Establece el archivo de sonido de la habilidad.</summary>
        void ponArchivoSonido(const std::string &archivo);

        /// <summary>Obtiene el coste en puntos de acción de la habilidad.</summary>
        int coste() const;
        /// <summary>Establece el coste en puntos de acción de la habilidad.</summary>
        void ponCoste(int valor);
        /// <summary>Obtiene el alcance en casillas de la habilidad.</summary>
        int alcance() const;
        /// <summary>Establece el alcance en casillas de la habilidad.</summary>
        void ponAlcance(int valor);
        /// <summary>Obtiene el radio de área de la habilidad.</summary>
        int radioAlcance() const;
        /// <summary>Establece el radio de área de la habilidad.</summary>
        void ponRadioAlcance(int valor);

        /// <summary>Obtiene el tipo de ataque asociado.</summary>
        TipoAtaque *tipoAtaque() const;
        /// <summary>Asigna el tipo de ataque a la habilidad.</summary>
        void asignaAtaque(TipoAtaque *tipo_ataque);

        /// <summary>Obtiene el tipo de defensa asociado.</summary>
        TipoDefensa *tipoDefensa() const;
        /// <summary>Asigna el tipo de defensa a la habilidad.</summary>
        void asignaDefensa(TipoDefensa *tipo_defensa);

        /// <summary>Obtiene el tipo de daño asociado.</summary>
        TipoDano *tipoDano() const;
        /// <summary>Obtiene el valor de daño de la habilidad.</summary>
        int valorDano() const;
        /// <summary>Asigna tipo y valor de daño a la habilidad.</summary>
        void asignaDano(TipoDano *tipo_dano, int valor_dano);

        /// <summary>Obtiene el valor de curación de la habilidad.</summary>
        int valorCuracion() const;
        /// <summary>Asigna el valor de curación de la habilidad.</summary>
        void asignaCuracion(int valor);

        using EfectosAtaque = std::vector<std::pair<TipoAtaque *, int>>;
        /// <summary>Obtiene la lista de efectos de ataque.</summary>
        const EfectosAtaque &efectosAtaque() const;
        /// <summary>Agrega un efecto de ataque a la habilidad.</summary>
        void agregaEfectoAtaque(TipoAtaque *tipo_ataque, int valor);

        using EfectosDefensa = std::vector<std::pair<TipoDefensa *, int>>;
        /// <summary>Obtiene la lista de efectos de defensa.</summary>
        const EfectosDefensa &efectosDefensa() const;
        /// <summary>Agrega un efecto de defensa a la habilidad.</summary>
        void agregaEfectoDefensa(TipoDefensa *tipo_defensa, int valor);

        /// <summary>Obtiene el índice interno de la habilidad.</summary>
        int indice() const;
        /// <summary>Establece el índice interno de la habilidad.</summary>
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
