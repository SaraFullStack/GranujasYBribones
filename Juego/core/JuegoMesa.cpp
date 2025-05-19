// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.cpp
// versión:  2.1  (Abril-2025)


#include "juego.h"
#include <array>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <tuple>
#include <utility>
#include <queue>

namespace juego {


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Primera sección - Los recursos

    En esta sección se establecen las carpetas en las que aparecen los recursos usados por el 
    juego, incluyendo las imágenes que aparecen en pantalla y los sonidos que se escuchan. Hay 
    una carpeta separada para los retratos de los personajes y otra para las imágenes de las 
    habilidades.

    Las carpetas están situadas en la carpeta donde están los archivos de código fuente del 
    proyecto.

    En principio no es necesario hacer ningún cambio en esta sección, si los recursos que se 
    cambian se sitúan en las mismas carpetas.

    *******************************************************************************************/
    string JuegoMesa::carpeta_activos_juego  {"./Assets/activos/"};
    string JuegoMesa::carpeta_retratos_juego {"./Assets/retratos/"};
    string JuegoMesa::carpeta_habilides_juego {"./Assets/habilidades/"};
    string JuegoMesa::carpeta_sonidos_juego  {"./Assets/sonidos/"};
    /*******************************************************************************************
    /******************************************************************************************/


    const std::wstring JuegoMesa::tituloVentana () const {
        return L"UNIR-2D :: Granujas y Bribones";
    }

    using GraficoMuros = char *[51];

    
    JuegoMesa::JuegoMesa () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Segunda sección - El modo del juego

        En esta sección se configura el modo general del juego, es decir como se suceden las 
        jugadas, los turnos y las rondas. Y como se establece el personaje que realiza cada jugada.  

        La configuración del modo del juego se realiza mediante la elección de alguno de los
        modos preestablecidos. Es la única forma de configurar el modo del juego.

        Hay tres modos de juego preestablecidos:

            1) Modo de juego por pares
            2) Modo de juego por equipos
            3) Modo de juego libre de doble jugada

        Las siguientes definiciones se aplican a todos los modos de juego:

        Jugada:   
            Es una acción realizada con uno de los personajes. Puede ser un desplazamiento o la
            aplicación de una habilidad.

        Turno:
            Es una secuencia de jugadas realizadas por un grupo de personajes, normalmente 
            alternando a los dos equipos. los turnos se inician con la elección de los personajes 
            que van a participar en el turno, aunque en algunos modos de juego estos están 
            preestablecidos.

        Ronda:
            Es una secuencia de turnos en las que intervienen todos los personajes y que se 
            prolongan hasta que los personajes no pueden continuar, por haber perdido sus puntos de 
            acción o por haber perdido su vitalidad. Al inicio de la ronda, se recuperan los puntos 
            de acción de todos los personajes.

        Partida:
            Está formada por una secuencia de rondas. La partida termina cuando todos los personajes 
            de un equipo pierden su vitalidad. El otro equipo es el ganador.


        Modo de juego por pares
        --------------------------
        
        En este modo debe haber el mismo número de personajes en cada equipo.

        los turnos comienzan con los jugadores eligiendo un personaje de cada equipo. El primer 
        personaje en jugar es el que tiene más iniciativa, y en caso de tener la misma, se elige al 
        azar. A continuación se suceden las jugadas, alternando los dos personajes. 

        Cuando un personaje pierde sus puntos de acción o su vitalidad, el turno continua solo con 
        el otro. Y cuando lo pierden los dos, el turno termina.

        En el nuevo turno los jugador elige de nuevo a los dos personajes, evitando a los que han
        perdido sus puntos de acción o vitalidad.

        Cuando todos los personajes han perdido sus puntos de acción o su vitalidad, termina la 
        ronda.


        Modo de juego por equipos
        ----------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un orden de juego para los personajes. Se toman los 
        personajes según aparecen en el tablero, de arriba a abajo, alternando los dos equipos. El 
        primero de los personajes será el que tenga más iniciativa de los dos primeros, eligiéndolos 
        al azar si coinciden. 
        
        Un turno consiste en una jugada de cada personaje, tomándolos en el orden de la lista y se 
        prolonga hasta que juega el último de los personajes de la lista. Si un personaje ha perdido 
        sus puntos de acción o su vitalidad, la jugada es nula y se pasa al siguiente personaje de 
        la lista. 
        
        Los turnos se suceden hasta que todos los personajes han perdido sus puntos de acción o su 
        vitalidad, momento en que se inicia el siguiente ronda.


        Modo de juego libre de doble jugada
        --------------------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un equipo inicial, tomando el que tiene el personaje 
        con más iniciativa o eligiéndolo al azar si coinciden. A continuación se alternan turnos de 
        uno y otro equipo. 
        
        Al principio de cada turno, el jugador elije un personaje del equipo correspondiente. El 
        turno consiste en dos jugadas seguidas del mismo personaje, tras las cuales se pasa a el 
        siguiente turno, en la que el jugador elige un personaje del otro equipo. Si un personaje 
        ha perdido sus puntos de acción o su vitalidad, no puede ser elegido.

        Cuando todos los personajes de un equipo han perdido sus puntos de acción o vitalidad, 
        termina el turno (a pesar de que el otro equipo si pueda continuar).


        Programación
        ------------

        Para cambiar el modo del juego es suficiente con cambiar los identificadores usados en 
        las dos líneas de código siguientes. Debe aparecer una de estas tres parejas:

            · ModoJuegoPares       SucesosJuegoPares       
            · ModoJuegoEquipo      SucesosJuegoEquipo    
            · ModoJuegoLibreDoble  SucesosJuegoLibreDoble

        *******************************************************************************************/
        ModoJuegoPares    * modo    = new ModoJuegoPares {this};
        SucesosJuegoPares * sucesos = new SucesosJuegoPares {this, modo};
        /*******************************************************************************************
        /******************************************************************************************/
        //
        JuegoMesaBase::configura (sucesos, modo);
        std::srand(std::time(nullptr));
    }


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Tercera sección - El tablero - Primera parte

    En esta sección se preparan los muros que aparecen en el tablero de juego.

    En el juego aparecen imágenes que muestran muros que ocupan algunas casillas hexagonales
    del tablero. Los jugadores no pueden situar a los personajes sobre los muros, ni 
    atravesarlos. Tampoco pueden realizar ataque a través de los muros (excepto si están 
    marcados como ataques indirectos).  

    Existen muchas posibilidades de diseño para los muros. Es posible que los muros se usen solo
    para delimitar un área del tablero, como ocurre con el ejemplo que aparece a continuación,
    llamado 'grafico_muros_area_central'. Otra posibilidad es diseñar una especie de laberinto
    con pasillos y cámaras, como en el ejemplo: 'grafico_muros_pasillos'. Aunque, lo más 
    aconsejable es crear unos muros que sean simplemente obstáculos para los ataques entre los 
    personajes.

    Especificación de los muros
    ---------------------------

    Para especificar los muros del tablero se debe crear un array similar al que aparece en los 
    ejemplos. Es preferible crear uno nuevo y mantener los ejemplos, en ese caso , la variable 
    debe tener un nombre diferente.

    El array está formado por 51 cadenas de caracteres, cada una de ellas de 145 caracteres de 
    longitud (mas el carácter \0 final, que no es visible). La mayor parte de los caracteres de 
    la cadena son espacios en blanco. En determinadas posiciones, y solo en ellas, puede haber: 
    o bien un guion, o bien la letra O mayúscula. 
        
    Esta disposición está pensada para indicar las posiciones de las celdas de la rejilla del 
    tablero. Al ser celdas hexagonales, no es posible usar una tabla formada por filas y 
    columnas, que, además, no daría una representación visual clara del tablero.

    Si se quiere que en una celda del tablero no aparezca un fragmento del muro, se debe 
    escribir un guion en la posición correspondiente del array. Si, por el contrario, se quiere 
    que si aparezca, se debe escribir la letra o mayúscula.

    El programa es muy sensible a la colocación de los caracteres en el array. Si uno de ellos
    está desplazado (por poco que sea), se producirá una excepción y el programa no se podrá 
    ejecutar.

    Programación
    ------------

    Véase la tercera parte de esta sección.
        
    *******************************************************************************************/
    
 ActorTablero::GraficoMuros& generaMurosAleatorios() {
    static char buf[51][146]; // Buffer estático para representar el tablero de muros

    // Configuración del grid y generación procedural de muros
    constexpr int ROWS = 51;
    constexpr int COLS = 145;
    constexpr int TOKENS = 25;
    constexpr int HALF = TOKENS / 2;
    constexpr int STEP = 6;
    constexpr int BLOCK_H = 4;
    constexpr int OFFSET[BLOCK_H] = {0, 3, 0, 3};

    // Coordenadas protegidas (siempre agua) y margen
    static const std::vector<std::pair<int,int>> coordenadas_protegidas = {
        {35,5},{37,5},{39,5},{35,45},{37,45},{39,45},
        {3,13},{3,33},{5,43},{10,30},
        {25,15},{26,24},{25,33},
        {40,24},{45,15},{45,33}
    };
    constexpr int FORBIDDEN_MARGIN = 1;

    auto isForbidden = [&](int row, int token) {
        for (auto& p : coordenadas_protegidas) {
            if (std::abs(p.first - row) <= FORBIDDEN_MARGIN && std::abs(p.second - token) <= FORBIDDEN_MARGIN)
                return true;
        }
        return false;
    };

    auto isValidToken = [&](int r, int c){
        if (c < 0 || c >= COLS || c % 3 != 0) return false;
        int fila1 = r + 1;
        int tok  = (c/3) + 1;
        return (fila1 % 2) == (tok % 2);
    };

    auto toTokenCoord = [&](int r, int c){
        return std::pair<int,int>{r+1, (c/3)+1};
    };

    // 1) Inicialización: todo token válido es agua '-', no válido es ' '
    for(int r=0;r<ROWS;++r){
        for(int c=0;c<COLS;++c){
            buf[r][c] = (c%3==0 && isValidToken(r,c)) ? '-' : ' ';
        }
        buf[r][COLS]='\0';
    }

    // Plantillas de islas
    using Cell = std::pair<int,int>;
    static const std::vector<Cell> shapes[] = {
        {{0,0},{0,1},{1,0},{1,1}},
        {{0,0},{0,1},{0,2},{0,3},{0,4}},
        {{0,1},{1,0},{1,1},{1,2},{2,1}},
        {{0,0},{1,0},{2,0},{2,1},{2,2}},
        {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2}},
        {{0,1},{0,2},{0,3},{1,0},{1,3},{2,0},{2,3}}
    };
    constexpr int NUM_SHAPES = sizeof(shapes)/sizeof(shapes[0]);

    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> islandCount(1,2);
    std::uniform_int_distribution<> shapeIdx(0,NUM_SHAPES-1);

    // 2) Generación de islas simétricas
    for(int block=0; block<ROWS/BLOCK_H; ++block){
        int count = islandCount(gen);
        int baseRow = block*BLOCK_H;
        for(int i=0;i<count;++i){
            auto const& shape = shapes[shapeIdx(gen)];
            int maxdc=0;
            for(auto& d:shape) maxdc = std::max(maxdc,d.second);
            int w = maxdc+1;
            std::uniform_int_distribution<> colOff(0,HALF-w);
            int obc = colOff(gen);
            int obr = baseRow + (gen()%BLOCK_H);
            int mirror = TOKENS - w - obc;

            // Validar forma completa antes de pintar
            bool valid=true;
            for(auto& d:shape){
                int rr=obr+d.first;
                int cc=obc+d.second;
                int cc2=mirror+d.second;
                if(rr<0||rr>=ROWS||cc<0||cc>=HALF||cc2<HALF||cc2>=TOKENS){ valid=false; break;}                
                int c1=OFFSET[rr%BLOCK_H]+cc*STEP;
                int c2=OFFSET[rr%BLOCK_H]+cc2*STEP;
                if(!isValidToken(rr,c1)||!isValidToken(rr,c2)) {valid=false; break;}
                auto [tr1,tk1]=toTokenCoord(rr,c1);
                auto [tr2,tk2]=toTokenCoord(rr,c2);
                if(isForbidden(tr1,tk1)||isForbidden(tr2,tk2)){ valid=false; break; }
            }
            if(!valid) { --i; continue; }

            // Pintar forma en buf
            for(auto& d:shape){
                int rr=obr+d.first;
                int cc=obc+d.second;
                int cc2=mirror+d.second;
                int c1=OFFSET[rr%BLOCK_H]+cc*STEP;
                int c2=OFFSET[rr%BLOCK_H]+cc2*STEP;
                auto [tr1,tk1]=toTokenCoord(rr,c1);
                auto [tr2,tk2]=toTokenCoord(rr,c2);
                // si protegido deja '-', sino pinta 'O'
                if(!isForbidden(tr1,tk1)) buf[rr][c1]='O';
                if(!isForbidden(tr2,tk2)) buf[rr][c2]='O';
            }
        }
    }

    // Devolver buffer como GraficoMuros
    return reinterpret_cast<ActorTablero::GraficoMuros&>(buf);
}

void JuegoMesa::preparaTablero () {
        agregaTablero (new ActorTablero (this));
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Segunda parte

        En esta sección se configura el fondo del tablero. Para rellenar el fondo del tablero se usa
        un conjunto de imágenes colocadas en una rejilla (en filas y columnas), que ocupan toda la 
        superficie de la ventana.
        
        La imagen usada para rellenar el fondo del tablero no se usa directamente, se divide en 16
        partes, con 4 filas y 4 columnas, y continuación se colocan en el fondo del tablero, 
        seleccionado las partes de manera aleatoria. La razón de este funcionamiento es que se 
        consiguen evitar los patrones visuales que pueden aparecer si se colocan de forma uniforme.

        El tamaño de la imagen usada es de 128x128 px (y cada parte es de 32x32 px). 
        
        Programación
        ------------

        Para cambiar la imagen del fondo es suficiente con situar la imagen nueva en la carpeta de 
        activos del juego y cambiar el nombre en la línea de código siguiente. 
        
        Es conveniente usar un archivo de tipo PNG. Además se deben respetar las medidas indicadas
        previamente.

        *******************************************************************************************/
        tablero ()->ponArchivoBaldosas (carpeta_activos_juego + "estampas_fondo.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Primera parte

        En esta sección se configuran los equipos del juego. 

        Cada equipo tiene un nombre y un escudo que aparece sobre la bandera en la parte superior de
        los paneles laterales del juego. En escudo se superpone a la bandera, sin taparla. El tamaño
        de las dos imágenes es de 40x40 px.
        
        Programación
        ------------

        Para cambiar los nombres de los equipos, se deben cambiar las dos líneas de código 
        siguientes. 
        
        Para cambiar las imágenes de los escudos es suficiente con situar las imágenes nuevas en la 
        carpeta de activos del juego y cambiar los nombres en las líneas de código siguiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        tablero ()->equipa (LadoTablero::Izquierda, L"Granujas", carpeta_activos_juego + "granujas.png");
        tablero ()->equipa (LadoTablero::Derecha,   L"Bribones",   carpeta_activos_juego + "bribones.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Tercera parte

        En esta sección se preparan los muros que aparecen en el tablero de juego. En la primera
        parte de la sección se preparan los muros que aparecen en el tablero, en esta tercera parte 
        se establecen los muros que usará el juego.

        Programación
        ------------

        Para cambiar los muros que aparecen en el tablero de juego es suficiente con cambiar el 
        nombre de la variable que contiene el array que los especifica en la línea de código que 
        aparece a continuación.
        
        *******************************************************************************************/
        // tablero ()->situaMuros (grafico_muros_area_central);
        tablero()->situaMuros(generaMurosAleatorios());

        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaPersonajes () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Tercera parte

        En esta sección se configuran los personajes del juego. En la segunda parte se establecen
        las variables destinadas a almacenar las instancias que definen los personajes. En esta 
        parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los personajes:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. Deben 
                ser evitados los nombres compuestos y los nombres largos.

             b) Equipo: Se establece indicando si el personaje aparece en el panel de la izquierda o 
                en el panel de la derecha en el tablero de juego.

             c) Orden en equipo: Debe ser un índice a partir de 0 y consecutivo.

             d) Iniciativa: Establece que personaje actúa en primer lugar en algunas de las 
                circunstancias del juego. Debe ser positivo.

        Imágenes
        --------

        Cada personaje tiene un retrato con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 75x75 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre un fondo gris oscuro. El retrato se especifica en la creación de la instancia.

        De la misma forma, cada personaje tiene una imagen para la ficha con la que aparece en el 
        tablero. El tamaño de la imagen usada es de 31x31 px.

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de personajes diseñados para el 
        juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        personaje en el diseño del juego.

        Para cambiar las imágenes de los retratos de los personajes es suficiente con situar las 
        imágenes nuevas en la carpeta de retratos del juego y cambiar los nombres de los archivos en 
        las llamadas al método correspondientes. Lo mismo ocurre con las imágenes de las fichas.
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        Edward  = new ActorPersonaje {this, LadoTablero::Izquierda, 0, L"Edward"};
        Balthazar = new ActorPersonaje {this, LadoTablero::Izquierda, 1, L"Balthazar"};
        Buenavida = new ActorPersonaje {this, LadoTablero::Izquierda,   2, L"Buenavida"};
        Victoria  = new ActorPersonaje {this, LadoTablero::Derecha,   0, L"Victoria"};
        Luciana  = new ActorPersonaje {this, LadoTablero::Derecha,   1, L"Luciana"};
        Dorian   = new ActorPersonaje {this, LadoTablero::Derecha, 2, L"Dorian"};
        //
        Edward ->ponArchivoRetrato (carpeta_retratos_juego + "edward.png");
        Dorian  ->ponArchivoRetrato (carpeta_retratos_juego + "dorian.png");
        Balthazar->ponArchivoRetrato (carpeta_retratos_juego + "balthazar.png");
        Buenavida->ponArchivoRetrato (carpeta_retratos_juego + "buenavida.png");
        Luciana ->ponArchivoRetrato (carpeta_retratos_juego + "luciana.png");
        Victoria ->ponArchivoRetrato (carpeta_retratos_juego + "victoria.png");
        //
        Edward ->ponArchivoFicha (carpeta_retratos_juego + "carry.png");
        Dorian  ->ponArchivoFicha (carpeta_retratos_juego + "tanke2.png");
        Balthazar->ponArchivoFicha (carpeta_retratos_juego + "support.png");
        Buenavida->ponArchivoFicha (carpeta_retratos_juego + "tanke.png");
        Luciana ->ponArchivoFicha (carpeta_retratos_juego + "support2.png");
        Victoria ->ponArchivoFicha (carpeta_retratos_juego + "carry2.png");
        //
        Edward ->ponIniciativa (20);
        Dorian  ->ponIniciativa (19);
        Balthazar->ponIniciativa (17);
        Buenavida->ponIniciativa (20);
        Luciana ->ponIniciativa (19);
        Victoria ->ponIniciativa (17);
        //
        agregaPersonaje (Edward);
        agregaPersonaje (Balthazar);
        agregaPersonaje (Buenavida);
        agregaPersonaje (Victoria);
        agregaPersonaje (Luciana);
        agregaPersonaje (Dorian);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaHabilidades () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Segunda parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. En 
        la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen las habilidades. En esta segunda parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de la habilidad correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a las habilidades:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. 

             b) Enfoque: Indica a que esta enfocada la habilidad. Puede ser a un personaje, a un 
                área formada por varias celdas del tablero o hacia el mismo personaje que usa la 
                habilidad. 

             c) Acceso: Indica si el efecto de la habilidad puede atravesar muros. Puede ser directo,
                indirecto o ninguno.

             d) Antagonista: Indica a que grupo de personajes se dirige la habilidad. Puede ser a un
                oponente, a un aliado o a sí mismo.

             e) Descripción: Es un texto largo que describe la habilidad.

        Imágenes
        --------

        Cada habilidad tiene una imagen con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 50x50 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre una imagen de fondo, que puede ser distinta para cada habilidad o la misma para todas. 
        Las dos imágenes de cada habilidad se especifican la misma llamada a un método.

        Sonidos
        -------

        Cada habilidad tiene un sonido que suena cuando el personaje la usa. El sonido se carga de 
        un archivo de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de emisión del sonido
        debe ser corto (escasos segundos).

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de habilidades diseñadas para 
        el juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        habilidad en el diseño del juego.

        Para cambiar las imágenes de las habilidad es suficiente con situar las imágenes nuevas en 
        la carpeta de habilidades del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Para cambiar los sonidos de las habilidad es suficiente con situar los sonidos nuevos en 
        la carpeta de sonidos del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        //ataqueEspadaNormal   = new Habilidad {
        //        L"Ataque cuerpo a cuerpo normal", 
        //        EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        //ataqueArco           = new Habilidad {
        //        L"Ataque a distancia normal",     
        //        EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        //ataqueEspadaPoderoso = new Habilidad {
        //        L"Ataque poderoso",               
        //        EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        //defensaFerrea        = new Habilidad {
        //        L"Defensa férrea",                
        //        EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        //curacionSimple       = new Habilidad {
        //        L"Curación",                      
        //        EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado};
        //curacionGrupo        = new Habilidad {
        //        L"Curación en grupo",             
        //        EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::aliado};
        //proyectilMagico      = new Habilidad {
        //        L"Proyectil mágico",              
        //        EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        //bolaFuego            = new Habilidad {
        //        L"Bola de fuego",                 
        //        EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        ////
        //ataqueEspadaNormal  ->ponDescripcion (
        //        L"El personaje usa su espada para atacar a un enemigo que se encuentra en una casilla próxima.");
        //ataqueArco          ->ponDescripcion (
        //        L"El personaje usa su arco para atacar a un enemigo que se encuentra en una casilla próxima.");
        //ataqueEspadaPoderoso->ponDescripcion (
        //        L"El personaje blande su espada con fuerza para atacar a un enemigo que se encuentra en una casilla próxima.");
        //defensaFerrea       ->ponDescripcion (
        //        L"El personaje aumenta su defensa hasta su próximo ronda.");
        //curacionSimple      ->ponDescripcion (
        //        L"El personaje canaliza poder divino para sanar a un aliado.");
        //curacionGrupo      ->ponDescripcion (
        //        L"El personaje canaliza poder divino para sanar a todos los personajes en un área.");
        //proyectilMagico     ->ponDescripcion (
        //        L"El personaje acumula energía mágica y la lanza contra un enemigo.");
        //bolaFuego           ->ponDescripcion (
        //        L"El personaje acumula energía mágica y la lanza contra un grupo de enemigos.");
        ////
        //ataqueEspadaNormal  ->ponArchivosImagenes (
        //        carpeta_habilides_juego + "espada.png",          carpeta_habilides_juego + "fondo_5.png");
        //ataqueArco          ->ponArchivosImagenes (
        //        carpeta_habilides_juego + "arco_flecha.png",     carpeta_habilides_juego + "fondo_5.png");
        //ataqueEspadaPoderoso->ponArchivosImagenes (
        //        carpeta_habilides_juego + "espada_poderosa.png", carpeta_habilides_juego + "fondo_5.png");
        //defensaFerrea       ->ponArchivosImagenes (
        //        carpeta_habilides_juego + "escudo.png",          carpeta_habilides_juego + "fondo_5.png");
        //curacionSimple      ->ponArchivosImagenes (
        //        carpeta_habilides_juego + "vela.png",            carpeta_habilides_juego + "fondo_5.png");
        //curacionGrupo       ->ponArchivosImagenes (
        //        carpeta_habilides_juego + "vela_triple.png",     carpeta_habilides_juego + "fondo_5.png");
        //proyectilMagico     ->ponArchivosImagenes (
        //        carpeta_habilides_juego + "cristales.png",       carpeta_habilides_juego + "fondo_5.png");
        //bolaFuego           ->ponArchivosImagenes (
        //        carpeta_habilides_juego + "bola_fuego.png",      carpeta_habilides_juego + "fondo_5.png");
        ////
        //ataqueEspadaNormal  ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //ataqueArco          ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //ataqueEspadaPoderoso->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //defensaFerrea       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //curacionSimple      ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //curacionGrupo       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //proyectilMagico     ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //bolaFuego           ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        ////
        //agregaHabilidad (ataqueEspadaNormal);
        //agregaHabilidad (ataqueArco);
        //agregaHabilidad (ataqueEspadaPoderoso);
        //agregaHabilidad (defensaFerrea );
        //agregaHabilidad (curacionSimple);
        //agregaHabilidad (curacionGrupo );
        //agregaHabilidad (proyectilMagico );
        //agregaHabilidad (bolaFuego );
        //
        /*******************************************************************************************
        /******************************************************************************************/

        canionazo = new Habilidad {
            L"Cañonazo",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::indirecto,
            Antagonista::oponente
        };
        canionazo->ponDescripcion(L"Disparo de cañón de largo alcance que causa gran daño.");
        canionazo->ponArchivosImagenes (carpeta_habilides_juego + "canionazo.png",      carpeta_habilides_juego + "fondo_5.png");
        canionazo->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");

        embestida = new Habilidad {
            L"Embestida",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::directo,
            Antagonista::oponente
        };
        embestida->ponDescripcion(L"Ataque cuerpo a cuerpo que empuja al enemigo.");
        embestida->ponArchivosImagenes (carpeta_habilides_juego + "embestida.png",      carpeta_habilides_juego + "fondo_5.png");
        embestida->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");

        abordaje = new Habilidad {
            L"Abordaje",
            EnfoqueHabilidad::personaje,
            AccesoHabilidad::directo,
            Antagonista::oponente
        };
        abordaje->ponDescripcion(L"Permite invadir el barco enemigo y realizar un ataque especial.");
        abordaje->ponArchivosImagenes (carpeta_habilides_juego + "abordaje.png",      carpeta_habilides_juego + "fondo_5.png");
        abordaje->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");


        reparacionBarco = new Habilidad {
            L"Reparación de barco",
            EnfoqueHabilidad::si_mismo,
            AccesoHabilidad::ninguno,
            Antagonista::si_mismo
        };
        reparacionBarco->ponDescripcion(L"Repara pequeños daños en el casco, recuperando 5 puntos de vitalidad.");
        reparacionBarco->ponArchivosImagenes(carpeta_habilides_juego + "reparar.png", carpeta_habilides_juego + "fondo_5.png");
        reparacionBarco->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");

        agregaHabilidad(canionazo);
        agregaHabilidad(embestida);
        agregaHabilidad(abordaje);
        agregaHabilidad(reparacionBarco);

        for (auto * personaje : personajes()) {
            personaje->agregaHabilidad(canionazo);
            personaje->agregaHabilidad(embestida);
            personaje->agregaHabilidad(abordaje);
            personaje->agregaHabilidad(reparacionBarco);
        }
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaTiposEstadisticas () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Segunda parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego. Estos tipos  
        son usados para establecer las estadisticas del juego en los personajes y en las habilidades. 
        En la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. En esta parte se crean las instancias y se 
        configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos y deben comenzar con la palabra 'Ataque', 'Defensa' o 'Daño'.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de tipos diseñados para el juego. El nombre de la clase (por ejemplo 
        'TipoAtaque' para los ataques) establece si es un tipo de ataque, de defensa o de daño.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        tipo en el diseño del juego.

        *******************************************************************************************/
        //
        ataqueCuerpoACuerpo  = new TipoAtaque  {L"Ataque cuerpo a cuerpo"};
        ataqueADistancia     = new TipoAtaque  {L"Ataque a distancia"};
        ataqueMagico         = new TipoAtaque  {L"Ataque mágico"};
        defensaCuerpoACuerpo = new TipoDefensa {L"Defensa cuerpo a cuerpo"};
        defensaADistancia    = new TipoDefensa {L"Defensa a distancia"};
        defensaMagica        = new TipoDefensa {L"Defensa mágica"};
        danoFisico           = new TipoDano    {L"Daño físico"};
        danoMagico           = new TipoDano    {L"Daño mágico"};
        //
        agregaAtaque  (ataqueCuerpoACuerpo );
        agregaAtaque  (ataqueADistancia);
        agregaAtaque  (ataqueMagico);
        agregaDefensa (defensaCuerpoACuerpo);
        agregaDefensa (defensaADistancia );
        agregaDefensa (defensaMagica );
        agregaDano    (danoFisico);
        agregaDano    (danoMagico);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaHabilidadesPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Octava sección - Las habilidades de los personajes

        En esta sección se establecen que habilidades que tiene cada personajes del juego.

        Cada personaje debe tener entre 1 y 10 habilidades.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de habilidades de cada personaje por listas similares, 
        obtenidas a partir del diseño del juego.

        *******************************************************************************************/
        //
        //Edward ->agregaHabilidad (ataqueEspadaNormal);
        //Edward ->agregaHabilidad (ataqueArco);
        //Edward ->agregaHabilidad (ataqueEspadaPoderoso);
        //Edward ->agregaHabilidad (defensaFerrea);
        ////
        //Dorian  ->agregaHabilidad (ataqueEspadaNormal);
        //Dorian  ->agregaHabilidad (curacionSimple);
        //Dorian  ->agregaHabilidad (curacionGrupo);
        //Dorian  ->agregaHabilidad (proyectilMagico);
        ////
        //Balthazar->agregaHabilidad (ataqueEspadaNormal);
        //Balthazar->agregaHabilidad (ataqueArco);
        //Balthazar->agregaHabilidad (ataqueEspadaPoderoso);
        ////
        //Buenavida->agregaHabilidad (ataqueEspadaNormal);
        //Buenavida->agregaHabilidad (ataqueArco);
        //Buenavida->agregaHabilidad (ataqueEspadaPoderoso);
        //Buenavida->agregaHabilidad (defensaFerrea);
        ////
        //Luciana ->agregaHabilidad (ataqueEspadaNormal);
        //Luciana ->agregaHabilidad (curacionSimple);
        //Luciana ->agregaHabilidad (curacionGrupo);
        //Luciana ->agregaHabilidad (proyectilMagico);
        ////
        //Victoria ->agregaHabilidad (ataqueEspadaNormal);
        //Victoria ->agregaHabilidad (ataqueArco);
        //Victoria ->agregaHabilidad (ataqueEspadaPoderoso);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasHabilidades () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Novena sección - Las estadísticas de las habilidades

        En esta sección se establecen diversos atributos y valores para las habilidades del juego,
        incluyendo las estadisticas del juego.

        Estadísticas
        ------------

        Las habilidades se clasifican en habilidades de ataque, de curación y auto-aplicada. Esta 
        clasificación se establece mediante el atributo 'Antagonista' de la habilidad. 

            - Si 'Antagonista' es 'oponente' la habilidad es de ataque. El ataque puede afectar a un 
              personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'aliado' la habilidad es de curación. La curación puede afectar a 
              un personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'si_mismo' la habilidad es auto-aplicada.

        Los valores que se establecen para las habilidades son:

             a) Coste: Es el número de puntos de acción que se gastan al usar la habilidad.

             b) Alcance: En las habilidades de ataque y curación debe estar establecido el alcance 
                de la habilidad. La habilidad solo se puede usar si el alcance lo permite. Es un 
                valor que indica un número de casillas del tablero y debe ser positivo.

             c) Radio de ara de alcance: En las habilidades de ataque y curación que afectan a un 
                área del tablero, debe estar establecido el radio del área. Es un valor que indica 
                un número de casillas del tablero y debe ser positivo. 

             d) Tipo de ataque: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                ataque. El tipo de ataque se usa en el personaje atacante.

             e) Tipo de defensa: Cuando una habilidad es de ataque, debe tener establecido un tipo 
                de defensa. El tipo de defensa se usa en el personaje atacado.

             f) Tipo de daño: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                daño. El tipo de daño se usa en el personaje atacado.

             g) Valor del daño: Cuando una habilidad es de ataque, debe tener establecido un valor 
                para el daño en puntos de vitalidad. El valor del daño se usa con el personaje 
                atacado.

             h) Curación: Cuando una habilidad es de curación, debe tener establecido un valor de 
                curación en puntos.

             i) Efecto en ataque: Cuando una habilidad es auto-aplicada, puede tener establecido uno 
                o más tipos de ataque, asignado como tipo de efecto en ataque. Alternativamente 
                (y excluyentemente) puede tener establecido un efecto en defensa (véase k).

             j) Valor del efecto en ataque: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en ataque establecido (véase i), debe tener establecido un valor del efecto
                en ataque en puntos de vitalidad.

             k) Efecto en defensa: Cuando una habilidad es auto-aplicada, puede tener establecido 
                uno o más tipos de defensa, asignado como tipo de efecto en defensa. Alternativamente 
                (excluyentemente) puede tener establecido un efecto en ataque (véase i).

             l) Valor del efecto en defensa: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en defensa establecido (véase k), debe tener establecido un valor del efecto
                en defensa en puntos de vitalidad.


        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las asignaciones de valores por asignaciones similares, obtenidas a 
        partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si se debe usar un tipo de 
        ataque, de defensa o de daño. Por ejemplo, el método 'asignaAtaque' debe ser llamado con un 
        parámetro del tipo (puntero) 'TipoAtaque'.  

        *******************************************************************************************/
        //
        //ataqueEspadaNormal->ponCoste (3);                                       
        //ataqueEspadaNormal->ponAlcance (1);
        //ataqueEspadaNormal->asignaAtaque  (ataqueCuerpoACuerpo); 
        //ataqueEspadaNormal->asignaDefensa (defensaCuerpoACuerpo); 
        //ataqueEspadaNormal->asignaDano    (danoFisico, 20); 
        ////
        //ataqueArco->ponCoste (5);
        //ataqueArco->ponAlcance (15);
        //ataqueArco->asignaAtaque  (ataqueADistancia);
        //ataqueArco->asignaDefensa (defensaADistancia);
        //ataqueArco->asignaDano    (danoFisico, 20);
        ////
        //ataqueEspadaPoderoso->ponCoste (5);
        //ataqueEspadaPoderoso->ponAlcance (1);
        //ataqueEspadaPoderoso->asignaAtaque  (ataqueCuerpoACuerpo);
        //ataqueEspadaPoderoso->asignaDefensa (defensaCuerpoACuerpo);
        //ataqueEspadaPoderoso->asignaDano    (danoFisico, 50);
        ////
        //defensaFerrea->ponCoste (3);
        //defensaFerrea->agregaEfectoDefensa (defensaCuerpoACuerpo, 30);
        //defensaFerrea->agregaEfectoDefensa (defensaADistancia,    30);
        ////
        //curacionSimple->ponCoste (5);
        //curacionSimple->ponAlcance (3);  
        //curacionSimple->asignaCuracion (40);
        ////
        //curacionGrupo->ponCoste (10);
        //curacionGrupo->ponAlcance (3);  
        //curacionGrupo->ponRadioAlcance (3);
        //curacionGrupo->asignaCuracion (40);
        ////
        //proyectilMagico->ponCoste (7);
        //proyectilMagico->ponAlcance (15);                                            
        //proyectilMagico->asignaAtaque  (ataqueMagico);
        //proyectilMagico->asignaDefensa (defensaMagica);
        //proyectilMagico->asignaDano    (danoMagico, 30);
        ////
        //bolaFuego->ponCoste (10);
        //bolaFuego->ponAlcance (8);
        //bolaFuego->ponRadioAlcance (3);
        //bolaFuego->asignaAtaque  (ataqueMagico);
        //bolaFuego->asignaDefensa (defensaMagica);
        //bolaFuego->asignaDano    (danoMagico, 50);
        //
        /*******************************************************************************************
        /******************************************************************************************/
        canionazo->ponCoste(6);
        canionazo->ponAlcance(12);
        canionazo->asignaAtaque(ataqueADistancia);
        canionazo->asignaDefensa(defensaADistancia);
        canionazo->asignaDano(danoFisico, 40);

        embestida->ponCoste(4);
        embestida->ponAlcance(1);
        embestida->asignaAtaque(ataqueCuerpoACuerpo);
        embestida->asignaDefensa(defensaCuerpoACuerpo);
        embestida->asignaDano(danoFisico, 25);

        abordaje->ponCoste(7);
        abordaje->ponAlcance(1);
        abordaje->asignaAtaque(ataqueCuerpoACuerpo);
        abordaje->asignaDefensa(defensaCuerpoACuerpo);
        abordaje->asignaDano(danoFisico, 50);

        reparacionBarco->ponCoste(3); 
        reparacionBarco->agregaEfectoDefensa(defensaCuerpoACuerpo, 5);
    }


    void JuegoMesa::agregaEstadisticasPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Décima sección - Los tipos de ataque, defensa y reducción de daño de los personajes

        En esta sección se establecen que tipos de ataque, defensa y reducción de daño tiene cada 
        personajes del juego, junto con la correspondiente puntuación.

        Configuración
        -------------

        La configuración de los tipos se debe realizar de la siguiente forma:

             a) Si un personaje tiene una habilidad y esta habilidad tiene un tipo de ataque, el 
                personaje debe tener ese tipo de ataque.

             b) Cada personaje debe tener todos los tipos de defensa.

             c) Cada personaje debe tener todos los tipos de daño, en forma de reducción de daño.

             d) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en ataque,
                que está definido usando un tipo de ataque, el personaje debe tener dicho tipo de 
                ataque.

             e) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en defensa,
                que está definido usando un tipo de defensa, el personaje debe tener dicho tipo de 
                defensa. Esta propiedad está establecida previamente mediante el punto (b)

             f) Cada tipo de ataque, defensa y reducción de daño del personaje debe tener una 
                puntuación. La puntuación no puede ser negativa.        

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de tipos de ataque, defensa y reducción de daño de cada 
        personaje por listas similares, obtenidas a partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si el tipo es ataque, 
        defensa o daño. Por ejemplo, el método 'agregaReduceDano' debe ser llamado con un parámetro 
        del tipo (puntero) 'TipoDano'.  

        *******************************************************************************************/
        //
        // Carries: Edward, Victoria
        Edward->agregaAtaque(ataqueCuerpoACuerpo, 40);
        Edward->agregaAtaque(ataqueADistancia, 75);
        Edward->agregaDefensa(defensaCuerpoACuerpo, 45);
        Edward->agregaDefensa(defensaADistancia, 60);

        Victoria->agregaAtaque(ataqueCuerpoACuerpo, 45);
        Victoria->agregaAtaque(ataqueADistancia, 70);
        Victoria->agregaDefensa(defensaCuerpoACuerpo, 50);
        Victoria->agregaDefensa(defensaADistancia, 60);

        // Soportes: Balthazar, Luciana
        Balthazar->agregaAtaque(ataqueCuerpoACuerpo, 50);
        Balthazar->agregaAtaque(ataqueADistancia, 50);
        Balthazar->agregaDefensa(defensaCuerpoACuerpo, 55);
        Balthazar->agregaDefensa(defensaADistancia, 55);

        Luciana->agregaAtaque(ataqueCuerpoACuerpo, 45);
        Luciana->agregaAtaque(ataqueADistancia, 50);
        Luciana->agregaDefensa(defensaCuerpoACuerpo, 55);
        Luciana->agregaDefensa(defensaADistancia, 60);

        // Tanques: Buenavida, Dorian
        Buenavida->agregaAtaque(ataqueCuerpoACuerpo, 80);
        Buenavida->agregaAtaque(ataqueADistancia, 30);
        Buenavida->agregaDefensa(defensaCuerpoACuerpo, 75);
        Buenavida->agregaDefensa(defensaADistancia, 60);

        Dorian->agregaAtaque(ataqueCuerpoACuerpo, 75);
        Dorian->agregaAtaque(ataqueADistancia, 35);
        Dorian->agregaDefensa(defensaCuerpoACuerpo, 70);
        Dorian->agregaDefensa(defensaADistancia, 60);

        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaSistemaAtaque () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Segunda parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. En la 
        primera parte se establecen las variables destinadas a almacenar las instancias que definen 
        los grados de efectividad. En esta parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos.

             b) Intervalo de puntos: Es el intervalo de puntos al que se aplica la efectividad. 
                Se establece con un valor mínimo y uno máximo. En el primer intervalo el valor 
                mínimo es el número entero mínimo y en el último intervalo, el valor máximo es 
                el número entero máximo.

             c) Efectividad: Es un porcentaje que se aplica a una puntuación para modificar su 
                valor cuando dicha puntuación esta en el intervalo definido por el intervalo
                correspondiente. 
            
        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de grados de efectividad diseñados para el juego. 

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        grados de efectividad en el diseño del juego.

        *******************************************************************************************/
        //
        GradoEfectividad * fallo   = new GradoEfectividad {L"Fallo"};
        GradoEfectividad * roce    = new GradoEfectividad {L"Roce"};
        GradoEfectividad * impacto = new GradoEfectividad {L"Impacto"};
        GradoEfectividad * critico = new GradoEfectividad {L"Impacto crítico"};
        //
        fallo  ->estableceRango (INT_MIN,       9,    0);
        roce   ->estableceRango (     10,      49,   50);
        impacto->estableceRango (     50,      89,  100);
        critico->estableceRango (     90, INT_MAX,  150);
        //
        agregaEfectividad (fallo);
        agregaEfectividad (roce);
        agregaEfectividad (impacto);
        agregaEfectividad (critico);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::configuraJuego () {
        agregaMusica (new ActorMusica {this});
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Undécima sección - Configuración miscelánea del juego.

        En esta sección se establecen varios valores de configuración que no tienen sitio en otras 
        secciones.

        Configuración
        -------------

        La configuración tiene los siguientes aspectos:

                 a) Se establece el consumo de puntos de acción de los desplazamientos de los 
                    personajes. Para ello se indica el número píxeles de desplazamiento que 
                    originan el consumo de un punto de acción.

                 b) Se establece la posición inicial de las fichas de los personajes en el tablero 
                    de juego.
         
                 c) Se establecen los archivos de sonido, que se escuchan en momentos concretos del
                    juego. Se deben especificar los sonidos:

                      - Sonido de una pulsación con el ratón (clic)
                      - Sonido de desplazamiento de una ficha.

                 d) Se establece la música que se escucha con el juego. En un fragmento musical que 
                    se repite en bucle.

                 e) Se almacenan los nombres de los alumnos diseñadores del juego. Estos nombres
                    aparecen en la ayuda del juego.

                 f) Se almacena el curso académico durante el que los alumnos han elaborado el 
                    diseño del juego.

        Sonidos y música
        ----------------

        Los sonidos se cargan de archivos de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de
        emisión del sonido debe ser corto (escasos segundos).
        
        Los sonidos y la música se han tomado de:
                https://opengameart.org/content/metal-click
                https://opengameart.org/content/walking-on-snow-sound
        La licencia aparece en esas mismas páginas.

        La música que suena en momentos determinados del juego también se carga de un archivo. Sin 
        embargo, no es necesario que sea corta, por que se atenúa a los pocos segundos.

        La música se han tomado de:
                https://opengameart.org/content/unused-music
        La licencia aparece en esa misma página.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de personajes por listas similares, obtenidas a partir del 
        diseño del juego.

        *******************************************************************************************/
        //
        modo ()->configuraDesplaza (RejillaTablero::distanciaCeldas);
        //
        Edward ->ponSitioFicha (Coord {35, 5});
        Balthazar->ponSitioFicha (Coord {37, 5});
        Buenavida->ponSitioFicha (Coord {39, 5});
        Victoria ->ponSitioFicha (Coord {35, 45});
        Luciana ->ponSitioFicha (Coord {37, 45});
        Dorian  ->ponSitioFicha (Coord {39, 45});

        Edward->ponSitioFicha(Coord{ 35, 5 });
        Balthazar->ponSitioFicha(Coord{ 37, 5 });
        Buenavida->ponSitioFicha(Coord{ 39, 5 });
        Victoria->ponSitioFicha(Coord{ 35, 45 });
        Luciana->ponSitioFicha(Coord{ 37, 45 });
        Dorian->ponSitioFicha(Coord{ 39, 45 });

        // ─── Tanques ──────────────────────
        Buenavida->ponPuntosAccion(4);

        Dorian->ponPuntosAccion(4);

        // ─── Soportes ─────────────────────
        Balthazar->ponPuntosAccion(6);

        Luciana->ponPuntosAccion(6);

        // ─── Carries ──────────────────────
        Edward->ponPuntosAccion(7);

        Victoria->ponPuntosAccion(7);


        //
        tablero ()->asignaSonidoEstablece (carpeta_sonidos_juego + "Metal Click.wav", 100);
        tablero ()->asignaSonidoDesplaza  (carpeta_sonidos_juego + "SnowWalk.ogg",    100);
        tablero ()->asignaSonidoFracaso  (carpeta_sonidos_juego + "bad.ogg",    100);
        tablero ()->asignaSonidoExito  (carpeta_sonidos_juego + "yar.ogg",    100);
        musica  ()->asignaMusica          (carpeta_sonidos_juego + "Track_1.ogg",     0);
        //
    agregaNombreAlumno (L"Sara Cubero García-Conde");
        agregaNombreAlumno (L"Juan Carlos Jibaja");
        agregaNombreAlumno (L"Nahuel Alejandro Espeche");
        agregaNombreAlumno (L"Carlos Díez Navarro");
        agregaNombreAlumno (L"Oriol Zabala Martínez");
        indicaCursoAcademico (L"2024 - 2025");
        //
        /*******************************************************************************************
        /******************************************************************************************/
  

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> tipoDist(0, 1);  // 0 = Daño, 1 = Curación

        for (int i = 0; i < 10; ++i) {
            tesoros[i] = new ActorObjetoRecolectable(
                this,
                posiciones[i],
                carpeta_activos_juego + "suerte.png"  // misma imagen para todos
            );

            bool esCuracion = tipoDist(gen);

            if (esCuracion) {
                tesoros[i]->ponEfecto(tapete::ActorObjetoRecolectable::TipoEfectoObjeto::Curacion,20);
            }
            else {
                tesoros[i]->ponEfecto(tapete::ActorObjetoRecolectable::TipoEfectoObjeto::Dano,20);
            }

            agregaObjeto(tesoros[i]);
        }

    }

    // En JuegoMesa.cpp
    void JuegoMesa::despuesDeMover(ActorPersonaje* personaje) {
        verificaRecoleccion(personaje);
    }

    void JuegoMesa::verificaRecoleccion(ActorPersonaje* personaje) {
        if (!personaje) return;
        Coord pos = personaje->sitioFicha();

        for (int i = 0; i < NUM_TESOROS; ++i) {
            auto* obj = tesoros[i];
            if (obj && !obj->estaRecogido() && obj->sitioFicha() == pos) {

                using Efecto = tapete::ActorObjetoRecolectable::TipoEfectoObjeto;

                switch (obj->tipoEfecto()) {
                case Efecto::Dano: {
                    int dmg = obj->valorEfecto();
                    personaje->ponVitalidad(personaje->vitalidad() - dmg);
                    personaje->presencia().refrescaBarraVida();
                    tablero()->emiteSonidoFracaso();
                    break;
                }
                case Efecto::Curacion: {
                    int heal = obj->valorEfecto();
                    personaje->ponVitalidad(std::min(personaje->vitalidad() + heal, 100));
                    personaje->presencia().refrescaBarraVida();
                    tablero()->emiteSonidoExito();  
                    break;
                }
                }

                /*if (obj->tipoEfecto() == Efecto::Curacion) {
                    tablero()->emiteSonidoHabilidad
                    unir2d::MotorSonido::emite(sonidoCuracion, 100);
                }
                else {
                    unir2d::MotorSonido::emite(sonidoDano, 100);
                }*/

                tablero()->indicador().desindica();

                obj->termina();
                tesoros[i] = nullptr;

                break;
            }
        }
    }


   

    void JuegoMesa::termina() {
        JuegoMesaBase::termina();  // ¡MUY importante que sea lo primero!

        // Elimina tesoros (estos sí son tuyos)
        for (auto*& t : tesoros) {
            if (t) {
                t->termina();
                delete t;
                t = nullptr;
            }
        }

        // No hagas delete de habilidades globales si ya fueron asignadas a personajes
        canionazo = nullptr;
        embestida = nullptr;
        abordaje = nullptr;
        reparacionBarco = nullptr;

        // Elimina tipos solo si no fueron liberados por el motor (depende de si los pasaste a algún actor)
        ataqueCuerpoACuerpo = nullptr;
        ataqueADistancia = nullptr;
        ataqueMagico = nullptr;
        defensaCuerpoACuerpo = nullptr;
        defensaADistancia = nullptr;
        defensaMagica = nullptr;
        danoFisico = nullptr;
        danoMagico = nullptr;

        // Punteros a personajes
        Buenavida = nullptr;
        Luciana = nullptr;
        Victoria = nullptr;
        Edward = nullptr;
        Dorian = nullptr;
        Balthazar = nullptr;
    }

}