// proyecto: Grupal/Tapete
// archivo:  TipoEstadistica.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class TipoEstadistica
    {
    public:
        /*!
         * \brief Define la categoría de la estadística (sistemaAtaque, defensa, daño, curación).
         */
        enum class Categoria
        {
            sistemaAtaque,
            defensa,
            dano,
            curacion
        };

        /*!
         * \brief Devuelve la categoría de la estadística.
         * \return Categoría de la estadística.
         */
        Categoria categoria() const;

        /*!
         * \brief Devuelve el nombre descriptivo de la estadística.
         * \return Nombre de la estadística.
         */
        const std::wstring &nombre() const;

        /*!
         * \brief Obtiene el índice interno de la estadística.
         * \return Índice interno.
         */
        int indice();

        /*!
         * \brief Establece el índice interno de la estadística.
         * \param valor Nuevo índice.
         */
        void ponIndice(int valor);

    protected:
        /*!
         * \brief Constructor protegido que inicializa la estadística con categoría y nombre.
         * \param categoria Categoría de la estadística.
         * \param nombre Nombre de la estadística.
         */
        explicit TipoEstadistica(Categoria categoria, const std::wstring &nombre);

    private:
        Categoria categoria_;
        std::wstring nombre_;
        int indice_{};
    };

    /*
     * \class TipoAtaqueDefensa
     * \brief Clase base para tipos de ataque o defensa.
     */
    class TipoAtaqueDefensa : public TipoEstadistica
    {
    protected:
        /*!
         * \brief Constructor protegido para tipos de ataque o defensa con categoría y nombre.
         * \param categoria Categoría.
         * \param nombre Nombre.
         */
        explicit TipoAtaqueDefensa(Categoria categoria, const std::wstring &nombre);
    };

    /*
     * \class TipoAtaque
     * \brief Representa un tipo de ataque en el sistema de combate.
     */
    class TipoAtaque : public TipoAtaqueDefensa
    {
    public:
        /*!
         * \brief Constructor que crea un tipo de ataque con un nombre.
         * \param nombre Nombre del tipo de ataque.
         */
        explicit TipoAtaque(const std::wstring &nombre);
    };

    /*
     * \class TipoDefensa
     * \brief Representa un tipo de defensa en el sistema de combate.
     */
    class TipoDefensa : public TipoAtaqueDefensa
    {
    public:
        /*!
         * \brief Constructor que crea un tipo de defensa con un nombre.
         * \param nombre Nombre del tipo de defensa.
         */
        explicit TipoDefensa(const std::wstring &nombre);
    };

    /*
     * \class TipoDanoCuracion
     * \brief Clase base para tipos de daño o curación.
     */
    class TipoDanoCuracion : public TipoEstadistica
    {
    protected:
        /*!
         * \brief Constructor protegido para tipos de daño o curación con categoría y nombre.
         * \param categoria Categoría.
         * \param nombre Nombre.
         */
        explicit TipoDanoCuracion(Categoria categoria, const std::wstring &nombre);
    };

    /*
     * \class TipoDano
     * \brief Representa un tipo de daño en el sistema de combate.
     */
    class TipoDano : public TipoDanoCuracion
    {
    public:
        /*!
         * \brief Constructor que crea un tipo de daño con un nombre.
         * \param nombre Nombre del tipo de daño.
         */
        explicit TipoDano(const std::wstring &nombre);
    };

}