# MediTrack

## Índice
1. [Introducción](#instalar-lo-necesario)
2. [Clonar Repositorio](#clonar-repositorio)
    - [La fácil pero latosa](#la-fácil-pero-latosa)
    - [La complicada pero rápida](#la-complicada-pero-rápida)
3. [Configurar git](#configurar-git)    
4. [Uso básico de git](#uso-básico-de-git)
5. [Ramas](#ramas)
6. [Compilar](#compilar)
7. [Distribución en windows](#distribución-en-windows)

## Instalar lo necesario

Primero deben descargar [msys2](https://www.msys2.org/) para tener una terminal
locochona que adem'as nos da los elementos para 
lo grafico (esto no tiene acentos pero es  por el
teclado en ingles xd)

Una vez instalado abriremos la terminan `msys2 mingw64` e instalaremos los siguientes paquetes

```bash
pacman -Syu git mingw-w64-x86_64-gtk3 mingw-w64-x86_64-toolchain base-devel mingw-w64-x86_64-cmake git --needed --noconfirm
```

## Clonar repositorio

Existen 2 formas de clonar o vulgarmente llamao descargar 
el repositorio

### La fácil pero latosa
Para clonar un repositorio basta con simplemente escribir el
comando:
```bash
git clone https://github.com/OmarRoman29/MediTrack.git
```

Sin embargo puesto que es un repositorio privado pedirá una 
contraseña, en usuario que pida tendrán que poner `OmarRoman29`
y una clave propia que tengo para estas cosas.

### La complicada pero rápida
Si ya instalaron los paquetes que les dije en  [Introducción](#instalar-lo-necesario)
reinicien la terminal para que se actualicen los datos, durante
el próximo proceso que les voy a decir se
equivocan durante este proceso solo borren la 
carpeta .ssh en C:\msys64\home\[usuario]\.ssh

Generar la clave rsa (usen el email de su cuenta
de github):
```bash
ssh-keygen -t rsa -b 4096 -C "<email>"
```

y tras aceptar todo lo que les diga ponen una 
contrasenia que *recuerden*

Para mostrar en consola la clave que generaron
```bash
cat /c/msys64/home/{su usuario}/.ssh/id_rsa.pub
```

Copiar la clave completa que les suelta el comando
y pegar en las claves ssh de github

Tambien pueden borrar la carpeta si se equivocaron
desde la terminal esta rara con:
```bash
rm -R /c/msys64/home/{su usuario}/.ssh/
```

Finalmente deben clonar el repositorio de esta forma:
```bash
git clone git@github.com:OmarRoman29/MediTrack.git
```


## Configurar git
### Nombre
No necesariamente debe ser el nombre de la cuenta
pero ps en empresas si usan git pues deben tener
registro de quién hizo qué cambios y git no jala
si no lo ponemos.

```bash
git config --global user.name "Omar Roman"
```

Más de lo mismo
### Correo
Usen su correo con el que tienen la cuenta de github.
```bash
git config --global user.email omar.roman.2828@gmail.com
```

### Autocrlf
En linux y windows se usan caracteres diferentes para
indicar salto de linea en los textos, entonces para que 
no se tengan problemas por esto se usa esta config:

Windows
```bash
git config --global core.autocrlf true
```

Linux
```
git config --global core.autocrlf input
```

### gitignore
Hay un archivo llamado `.gitignore` ahí se escriben los 
archivos y carpetas que queramos que nunca sean consideradas
para guardarlas en el repositorio. 
Las carpetas se agregan como:
```
carpeta/
```

Si esta carpeta no está directamente en la carpeta `MediTrack`
se escribe como:
```
ruta/hacia/carpeta/
```

Con los archivos deberán escribir el nombre y extensión del
archivo y de ser necesario, la ruta del archivo.
```
ruta/archivo/prueba.txt
```

## Uso básico de git

Alch es mucho, por ahora les dejo el video q les dije, 

[Aprende Git - HolaMundo](https://www.youtube.com/watch?v=VdGzPZ31ts8)

- En minuto `16:10` comandos básicos de terminal

- En minuto `24:18` explicación de como funciona git 

- En minuto `28:00` comandos que concuerdan con el punto
anterior

## Ramas
Listar ramas
```bash
git branch
```

Cambiar entre ramas
```bash
git chechout nombre-rama
```
Crear una rama: Se crea de forma local y no se guarda en
el server
```bash
git checkout -b nombre-rama
```

Hacer que la rama esté en github (y así podamos cualquiera
modificar ahí y que no solapemos lo que haga el otro jsjs)
```bash
git push origin nombre-rama
```

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
