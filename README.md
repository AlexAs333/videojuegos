# videojuegos
.

---

# Proyecto

Este proyecto es una plantilla configurada para compilar videojuegos en C++ con SFML 3.0. Es portable: incluye las librerías necesarias (.dll, .a, .so) localmente, por lo que funciona en Windows y Linux sin configuraciones complejas.

## 1. Instalación de Herramientas (Desde Cero)

Para compilar, necesitas `g++` y `make`.

### En Windows (Si no tienes nada instalado)

Si es tu primera vez, necesitas instalar un gestor de paquetes y las herramientas. Abre **PowerShell como Administrador** y sigue estos pasos:

**Paso 1: Instalar Chocolatey**
Copia, pega y pulsa Enter:

```Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('[https://community.chocolatey.org/install.ps1](https://www.google.com/search?q=https://community.chocolatey.org/install.ps1)'))```

**Paso 2: Instalar Compilador y Make**
Una vez termine el paso anterior, ejecuta:

```choco install mingw make -y```

> **IMPORTANTE:** Cierra la terminal y abre una nueva para que los comandos funcionen.

### En Linux (Ubuntu/Debian)

Solo necesitas las herramientas esenciales. Abre una terminal y ejecuta:

```sudo apt update```
```sudo apt install build-essential -y```

## 2. Compilar y Ejecutar

Abre una terminal en la carpeta de este proyecto (donde está el Makefile) y usa estos comandos:

**Compilar:**
```make```

**Limpiar:**
```make clean```

### Ejecutar el Juego

Una vez compilado, el ejecutable se genera automáticamente en la carpeta bin.

**Windows:**
```.\bin\mi_app.exe```

**Linux:**
```./bin/mi_app```

## 3. Estructura del Proyecto

* **src/**: Código fuente (.cpp y .h). El sistema busca recursivamente en subcarpetas.
* **include/**: Cabeceras de SFML.
* **lib/**: Librerías binarias para Windows y Linux.
* **bin/**: Carpeta de salida (se crea sola al compilar).
* **Makefile**: Script de automatización universal.
