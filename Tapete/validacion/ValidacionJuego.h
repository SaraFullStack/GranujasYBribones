// proyecto: Grupal/Tapete
// archivo   ValidacionJuego.h
// versión:  2.1  (Abril-2025)


#pragma once


namespace tapete {


    /*!
     * \class ValidacionJuego
     * \brief Realiza la validación de la configuración y los datos del juego.
     *
     * Comprueba la accesibilidad de archivos, la validez de cadenas, la unicidad y pertenencia de elementos,
     * y la coherencia de los datos de personajes, habilidades, estadísticas y sistema de ataque.
     * Proporciona utilidades para detectar duplicados, valores nulos, pertenencia y restricciones en listas y pares.
     * Lanza excepciones detalladas en caso de errores de validación.
     */
    class ValidacionJuego {
    public:
        /*!
         * \brief Constructor de la clase ValidacionJuego.
         * \param juego Puntero al juego a validar.
         */
        explicit ValidacionJuego (JuegoMesaBase * juego);

        /*!
         * \brief Destructor de la clase ValidacionJuego.
         */
        ~ValidacionJuego ();

        /*!
         * \brief Valida la construcción general del juego.
         */
        void Construccion            ();

        /*!
         * \brief Valida la configuración del tablero.
         */
        void Tablero                 ();

        /*!
         * \brief Valida la configuración de los personajes.
         */
        void Personajes              ();

        /*!
         * \brief Valida la configuración de las habilidades.
         */
        void Habilidades             ();

        /*!
         * \brief Valida los tipos de estadísticas.
         */
        void TiposEstadisticas       ();

        /*!
         * \brief Valida la asignación de habilidades a personajes.
         */
        void HabilidadesPersonajes   ();

        /*!
         * \brief Valida las estadísticas de las habilidades.
         */
        void EstadisticasHabilidades ();

        /*!
         * \brief Valida las estadísticas de los personajes.
         */
        void EstadisticasPersonajes  ();

        /*!
         * \brief Valida el sistema de ataque.
         */
        void SistemaAtaque           ();

        /*!
         * \brief Valida la configuración general del juego.
         */
        void ConfiguraJuego          ();

    private:
        /*!
         * \brief Puntero al juego a validar.
         */
        JuegoMesaBase * juego {}; 

        /*!
         * \brief Comprueba si un archivo es accesible y tiene una extensión válida.
         * \param archivo Ruta del archivo.
         * \param extensiones Lista de extensiones válidas.
         * \return true si es accesible y válido, false en caso contrario.
         */
        bool archivoAccesible (const string  & archivo, std::initializer_list <string> extensiones);

        /*!
         * \brief Comprueba si una cadena es válida.
         * \param nombre Cadena a validar.
         * \return true si es válida, false en caso contrario.
         */
        bool cadenaValida     (const wstring & nombre);


        /*!
         * \brief Comprueba si un elemento pertenece a un conjunto.
         * \param elemento Elemento a buscar.
         * \param conjunto Vector de elementos.
         * \return true si pertenece, false en caso contrario.
         */
        template <typename E>
        static bool pertenece (const E & elemento, const std::vector <E> & conjunto) {
            for (int indc_conjt = 0; indc_conjt < conjunto.size (); ++ indc_conjt) {
                if (elemento == conjunto [indc_conjt]) {
                    return true;
                }
            }
            return false;
        }        

        /*!
         * \brief Devuelve el índice del primer elemento nulo en una lista.
         * \param lista Vector de punteros.
         * \return Índice del primer elemento nulo, o -1 si no hay nulos.
         */
        template <typename E>
        static int no_nulos (const std::vector <E> & lista) {
            for (int indc = 0; indc < lista.size (); ++ indc) {
                if (lista [indc] == nullptr) {
                    return indc;
                }
            }
            return -1;
        }

        /*!
         * \brief Devuelve el índice del primer par cuyo primer elemento es nulo.
         * \param lista Vector de pares.
         * \return Índice del primer par con primer elemento nulo, o -1 si no hay nulos.
         */
        template <typename E>
        static int no_nulos_pares (const std::vector <std::pair <E, int>> & lista) {
            for (int indc = 0; indc < lista.size (); ++ indc) {
                if (lista [indc].first == nullptr) {
                    return indc;
                }
            }
            return -1;
        }

        /*!
         * \brief Devuelve el índice del primer elemento que no pertenece al conjunto.
         * \param elementos Vector de elementos a comprobar.
         * \param conjunto Vector de elementos válidos.
         * \return Índice del primer elemento no perteneciente, o -1 si todos pertenecen.
         */
        template <typename E>
        static int pertenecen (const std::vector <E> & elementos, const std::vector <E> & conjunto) {
            for (int indc_elemt = 0; indc_elemt < elementos.size (); ++ indc_elemt) {
                bool esta = false;
                for (int indc_conjt = 0; indc_conjt < conjunto.size (); ++ indc_conjt) {
                    if (elementos [indc_elemt] == conjunto [indc_conjt]) {
                        esta = true;
                        break;
                    }
                }
                if (! esta) {
                    return indc_elemt;
                }
            }
            return -1;
        }

        /*!
         * \brief Devuelve el índice del primer par cuyo primer elemento no pertenece al conjunto.
         * \param elementos Vector de pares.
         * \param conjunto Vector de elementos válidos.
         * \return Índice del primer par no perteneciente, o -1 si todos pertenecen.
         */
        template <typename E>
        static int pertenecen_pares (const std::vector <std::pair <E, int>> & elementos, const std::vector <E> & conjunto) {
            for (int indc_elemt = 0; indc_elemt < elementos.size (); ++ indc_elemt) {
                bool esta = false;
                for (int indc_conjt = 0; indc_conjt < conjunto.size (); ++ indc_conjt) {
                    if (elementos [indc_elemt].first == conjunto [indc_conjt]) {
                        esta = true;
                        break;
                    }
                }
                if (! esta) {
                    return indc_elemt;
                }
            }
            return -1;
        }

        /*!
         * \brief Devuelve el índice del primer elemento duplicado en la lista.
         * \param lista Vector de elementos.
         * \return Índice del primer duplicado, o -1 si no hay duplicados.
         */
        template <typename E>
        static int duplicados (const std::vector <E> & lista) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (lista [indc_elemt] == lista [indc_prev]) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }

        /*!
         * \brief Devuelve el índice del primer par duplicado (por el primer elemento) en la lista.
         * \param lista Vector de pares.
         * \return Índice del primer duplicado, o -1 si no hay duplicados.
         */
        template <typename E>
        static int duplicados_pares (const std::vector <std::pair <E, int>> & lista) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (lista [indc_elemt].first == lista [indc_prev].first) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }

        /*!
         * \brief Devuelve el índice del primer par cuyo valor es menor o igual a cero.
         * \param lista Vector de pares.
         * \return Índice del primer par con valor no válido, o -1 si todos son válidos.
         */
        template <typename E>
        static int tiene_valor_pares (const std::vector <std::pair <E, int>> & lista) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (lista [indc_elemt].second <= 0) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }

        /*!
         * \brief Devuelve el índice del primer par cuyo valor supera la cota dada.
         * \param lista Vector de pares.
         * \param cota Valor máximo permitido.
         * \return Índice del primer par fuera de cota, o -1 si todos cumplen la cota.
         */
        template <typename E>
        static int valor_acotado_pares (const std::vector <std::pair <E, int>> & lista, int cota) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (cota < lista [indc_elemt].second) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }


        /*!
         * \brief Lanza una excepción si la condición no se cumple.
         * \param condicion Condición a comprobar.
         * \param mensaje Mensaje de error.
         * \param localiza Sección de configuración donde se produce el error.
         */
        void aserta (bool condicion, wstring mensaje, const LocalizaConfigura localiza);

    };


}