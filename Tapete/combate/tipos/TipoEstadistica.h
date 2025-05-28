// proyecto: Grupal/Tapete
// archivo:  TipoEstadistica.h
// versión:  2.1  (Abril-2025)

#pragma once

namespace tapete
{

    class TipoEstadistica
    {
    public:
        /// <summary>Define la categoría de la estadística (sistemaAtaque, defensa, daño, curación).</summary>
        enum class Categoria
        {
            sistemaAtaque,
            defensa,
            dano,
            curacion
        };

        /// <summary>Devuelve la categoría de la estadística.</summary>
        Categoria categoria() const;
        /// <summary>Devuelve el nombre descriptivo de la estadística.</summary>
        const std::wstring &nombre() const;

        /// <summary>Obtiene el índice interno de la estadística.</summary>
        int indice();
        /// <summary>Establece el índice interno de la estadística.</summary>
        void ponIndice(int valor);

    protected:
        /// <summary>Constructor protegido que inicializa la estadística con categoría y nombre.</summary>
        explicit TipoEstadistica(Categoria categoria, const std::wstring &nombre);

    private:
        Categoria categoria_;
        std::wstring nombre_;

        int indice_{};
    };

    class TipoAtaqueDefensa : public TipoEstadistica
    {
    protected:
        /// <summary>Constructor protegido para tipos de ataque o defensa con categoría y nombre.</summary>
        explicit TipoAtaqueDefensa(Categoria categoria, const std::wstring &nombre);
    };

    class TipoAtaque : public TipoAtaqueDefensa
    {
    public:
        /// <summary>Constructor que crea un tipo de ataque con un nombre.</summary>
        explicit TipoAtaque(const std::wstring &nombre);
    };

    class TipoDefensa : public TipoAtaqueDefensa
    {
    public:
        /// <summary>Constructor que crea un tipo de defensa con un nombre.</summary>
        explicit TipoDefensa(const std::wstring &nombre);
    };

    class TipoDanoCuracion : public TipoEstadistica
    {
    protected:
        /// <summary>Constructor protegido para tipos de daño o curación con categoría y nombre.</summary>
        explicit TipoDanoCuracion(Categoria categoria, const std::wstring &nombre);
    };

    class TipoDano : public TipoDanoCuracion
    {
    public:
        /// <summary>Constructor que crea un tipo de daño con un nombre.</summary>
        explicit TipoDano(const std::wstring &nombre);
    };

}