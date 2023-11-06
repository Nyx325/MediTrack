cmake_minimum_required(VERSION 3.5)
project(MediTrack)

# Busca el paquete GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Agrega las rutas de inclusión para GTK
# Agrega los archivos .h creo
include_directories(${GTK3_INCLUDE_DIRS})

# Agrega tus archivos fuente
# Cargar todos los archivos .c
file(GLOB SOURCES "src/*.c")

# Crea un ejecutable
add_executable(MediTrack ${SOURCES})

# Vincula tu ejecutable con las bibliotecas de GTK
# Agregar librerias y todo lo que hace a GTK funcionar
target_link_libraries(MediTrack ${GTK3_LIBRARIES})
