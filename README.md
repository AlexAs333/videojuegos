# Proyecto

Este proyecto es una plantilla configurada para compilar videojuegos en C++ con SDL 2. Es portable: incluye las librerías necesarias (.dll, .a, .so) localmente, por lo que funciona en Windows y Linux sin configuraciones complejas.

## 1. Instalación de Herramientas (Desde Cero)

Para compilar, necesitas `g++`, `make` y `cmake` (opcional, recomendado).

### En Windows (Si no tienes nada instalado)

Si es tu primera vez, necesitas instalar un gestor de paquetes y las herramientas. Abre **PowerShell como Administrador** y sigue estos pasos:

### Paso 1: Instalar Chocolatey

Copia, pega y pulsa Enter:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; `
[System.Net.ServicePointManager]::SecurityProtocol = `
[System.Net.ServicePointManager]::SecurityProtocol -bor 3072; `
iex ((New-Object System.Net.WebClient).DownloadString('[https://community.chocolatey.org/install.ps1](https://community.chocolatey.org/install.ps1)'))

```

### Paso 2: Instalar Compilador, Make y CMake

Una vez termine el paso anterior, ejecuta este comando actualizado para instalar todo lo necesario:

```powershell
choco install mingw make cmake -y

```

> **IMPORTANTE:** Cierra la terminal y abre una nueva para que los comandos funcionen.

### En Linux (Ubuntu/Debian)

Solo necesitas las herramientas esenciales. Abre una terminal y ejecuta:

```bash
sudo apt update

```

```bash
sudo apt install build-essential cmake -y

```

---

## 2. Compilar y Ejecutar

Tienes dos formas de compilar este proyecto. Elige la que prefieras.

### OPCIÓN A: Usando Make (Clásico)

Abre una terminal en la carpeta raíz del proyecto y usa estos comandos:

**Compilar:**

```powershell
make

```

**Limpiar:**

```powershell
make clean

```

### OPCIÓN B: Usando CMake (Moderno y Recomendado)

Este método es más robusto y usa los scripts automatizados situados en la carpeta `scripts/`.

**Compilar (Windows):**

```powershell
.\scripts\build.bat

```

**Compilar (Linux):**
*Primero da permisos de ejecución (solo una vez): `chmod +x scripts/*.sh*`

```bash
./scripts/build.sh

```

**Limpiar (Windows):**

```powershell
.\scripts\clean.bat

```

**Limpiar (Linux):**

```bash
./scripts/clean.sh

```

---

### Ejecutar el Juego

Independientemente de si usas Make o CMake, el ejecutable se genera automáticamente en la carpeta `bin`.

**Windows:**

```powershell
.\bin\mi_juego.exe

```

**Linux:**

```bash
./bin/mi_juego

```

## 3. Estructura del Proyecto

* **src/**: Código fuente (.cpp y .h). El sistema busca recursivamente en subcarpetas.
* **include/**: Cabeceras de la librería (SDL2).
* **lib/**: Librerías binarias para Windows y Linux.
* **scripts/**: Scripts de automatización para CMake (build y clean).
* **bin/**: Carpeta de salida (se crea sola al compilar).
* **Makefile**: Script de automatización (Legacy/Make).
* **CMakeLists.txt**: Configuración del proyecto para CMake.

