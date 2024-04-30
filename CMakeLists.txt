cmake_minimum_required(VERSION 3.5)
project(MediTrack)

# Opciones de compilación con y sin información de depuración
option(DEBUG_MODE "Compilar con información de depuración" ON)

# Establecer las flags de depuración y optimización

# cmake -DDEBUG_MODE=ON .
# cmake -DDEBUG_MODE=OFF .

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")
if(DEBUG_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")  # Agrega información de depuración
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")  # Agrega optimizaciones
endif()

# Agrega tus archivos fuente
# Cargar todos los archivos .c
file(GLOB ENTIDAD "src/datos/entidad/*.c")
file(GLOB REPOSITORIO "src/datos/repositorio/*.c")
file(GLOB LOGICA "src/logica/*.c")
file(GLOB VISTA "src/vista/*.c")
file(GLOB MAIN "src/main.c")

# Incluir archivos de cabecera
# file(GLOB VISTA_HEADERS "src/vista/*.h")  

# Agrega tus archivos fuente y de cabecera al ejecutable
add_executable(MediTrack ${MAIN} ${ENTIDAD} ${REPOSITORIO} ${LOGICA} ${VISTA})
#add_executable(MediTrack ${MAIN} ${ENTIDAD} ${REPOSITORIO} ${LOGICA} ${VISTA} ${VISTA_HEADERS})

# Busca el paquete GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Agrega las rutas de inclusión para GTK
# Agrega los archivos .h creo
include_directories(${GTK3_INCLUDE_DIRS})

# Vincula tu ejecutable con las bibliotecas de GTK
# Agregar librerias y todo lo que hace a GTK funcionar
target_link_libraries(MediTrack ${GTK3_LIBRARIES})
