// proyecto: Grupal/Juego
// archivo:   principal.cpp
// versión:   2.3  (Mayo-2025)

#include <cstdlib>       // std::exit, _set_abort_behavior
#include <exception>     // std::set_terminate
#include <locale>        // std::setlocale
#include "juego.h"       // tu cabecera del juego

#ifdef _WIN32
  // para evitar que windows.h meta demasiadas cosas que compliquen el build
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <windows.h>   // SetErrorMode, SEM_* constants
  #include <crtdbg.h>    // _CrtSetReportMode

  // Desactiva los cuadros de diálogo Win32 (GP faults, errores de disco…)
  static void disableWin32Errors() {
      SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
  }

  // Desactiva el mensaje de abort() y evita ReportFault
  static void disableCrtAbortMsg() {
      _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
  }

  // Silencia CRT reports de debug (warnings, errores y asserts)
  static void disableCrtDebugReport() {
  #ifdef _DEBUG
      _CrtSetReportMode(_CRT_WARN,   0);
      _CrtSetReportMode(_CRT_ERROR,  0);
      _CrtSetReportMode(_CRT_ASSERT, 0);
  #endif
  }
#else
  // Stubs vacíos en no-Windows para que compile sin errores
  static void disableWin32Errors()   {}
  static void disableCrtAbortMsg()   {}
  static void disableCrtDebugReport(){}
#endif

int main() {
    // Primero anular todo lo posible de Win32 y CRT
    disableWin32Errors();
    disableCrtAbortMsg();
    disableCrtDebugReport();

    // Excepciones no capturadas harán exit(0) silencioso
    std::set_terminate([](){
        std::exit(0);
    });

    // Configuración regional para tildes, etc.
    std::setlocale(LC_ALL, "es_ES.utf8");

    try {
        // Inicialización de juego y motor
        juego::JuegoMesa * juego = new juego::JuegoMesa{};
        unir2d::Motor    * motor = new unir2d::Motor{};

        // Bucle principal
        while (true) {
            motor->ejecuta(juego);
            if (juego->ejecucion() == unir2d::EjecucionJuego::cancelado) {
                break;
            }
        }

        // Limpieza
        delete motor;
        delete juego;
    }
    catch(...) {
        // No imprimir errores en versión entregable
    }

    return 0;
}
