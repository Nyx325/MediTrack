# MediTrack

## Índice
1. [Introducción](#instalar-lo-necesario)
6. [Compilar](#compilar)

## Instalar lo necesario
### Windows
Primero deben descargar [msys2](https://www.msys2.org/) para tener una terminal
locochona que adem'as nos da los elementos para 
lo grafico (esto no tiene acentos pero es  por el
teclado en ingles xd)

Una vez instalado abriremos la terminan `msys2 mingw64` e instalaremos los siguientes paquetes

```bash
pacman -Syu git mingw-w64-x86_64-gtk3 mingw-w64-x86_64-toolchain base-devel mingw-w64-x86_64-cmake git --needed --noconfirm
```

### Linux
Busca las dependencias de desarrollo en GTK3 de tu distro :D

## Compilar

### Usando comando entero
```bash
cd src/
gcc `pkg-config --cflags gtk+-3.0` -o MediTrack *.c `pkg-config --libs gtk+-3.0`
```

### Usando Cmake
Abriendo su terminal del msys2 y estando en la carpeta del repositorio:
```bash
mkdir build 
cd build
cmake ..
```

Esto es solo para mi:
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

Y dependiendo de su equipo se compila con `ninja` 

```bash
ninja
```

O haciendo uso de `make`

```bash
make
```
## Distribución en Windows

Para que se pueda ejecutar el programa sin necesitar instalar un entorno de desarrollo
al usuario se deben copiar los archivos dll a la carpeta donde se encuentra el ejecutable
(creo) y para eso, se usa este comando para en el ejecutable ya compilado determinar qué
dll necsita y copiarlos al directorio actual

```bash
ldd mygtkapp.exe | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" .
```
