# --- PROYECTO SDL2 + SDL2_IMAGE UNIVERSAL ---

# 1. Configuración del Proyecto
APP_NAME := mi_juego
SRC_DIR  := src
BIN_DIR  := bin
INC_DIR  := include

# 2. Compilador
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I$(INC_DIR)

# 3. Búsqueda de Archivos Fuente (Recursiva)
# Busca archivos .cpp en 'src/' y en cualquier subcarpeta (ej: 'src/Entities/Enemy.cpp')
SRC      := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)

# --- DETECCIÓN DE SISTEMA OPERATIVO ---
ifeq ($(OS),Windows_NT)
    # ---------------- WINDOWS ----------------
    DETECTED_OS := Windows
    TARGET      := $(BIN_DIR)/$(APP_NAME).exe
    LIB_DIR     := lib/windows
    
    # Flags de Enlace (Linker) para Windows:
    # IMPORTANTE: El orden es vital. 
    # 1. -lmingw32      (Sistema)
    # 2. -lSDL2main     (Entrada Main)
    # 3. -lSDL2         (Librería base)
    # 4. -lSDL2_image   (Librería de imágenes)
    # -mwindows: Oculta la consola negra (quítalo si quieres ver std::cout para depurar)
    LDFLAGS     := -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -static-libgcc -static-libstdc++

    # Comandos para Windows (usando cmd /C para compatibilidad)
    MKDIR_CMD   := if not exist bin mkdir bin
    # Copia TODAS las DLLs (*.dll) porque SDL2_image necesita zlib1.dll, libpng16.dll, etc.
    COPY_CMD    := cmd /C "copy /Y lib\windows\*.dll bin 1>NUL"
    CLEAN_CMD   := if exist bin rmdir /s /q bin
    
else
    # ---------------- LINUX ----------------
    DETECTED_OS := Linux
    TARGET      := $(BIN_DIR)/$(APP_NAME)
    LIB_DIR     := lib/linux
    
    # Flags de Enlace para Linux
    LDFLAGS     := -L$(LIB_DIR) -lSDL2 -lSDL2_image -Wl,-rpath,'$$ORIGIN/../$(LIB_DIR)'

    # Comandos para Linux
    MKDIR_CMD   := mkdir -p $(BIN_DIR)
    COPY_CMD    := echo "Linux: Librerías listas."
    CLEAN_CMD   := rm -rf $(BIN_DIR)
endif

# --- REGLAS DE COMPILACIÓN ---

all: info $(TARGET)

info:
	@echo ---------------------------------------
	@echo Sistema detectado: $(DETECTED_OS)
	@echo Compilando archivos: $(SRC)
	@echo ---------------------------------------

$(TARGET): $(SRC)
	@echo [1/3] Creando carpeta bin...
	@$(MKDIR_CMD)
	@echo [2/3] Compilando y Enlazando...
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)
	@echo [3/3] Copiando librerias dinamicas (DLLs)...
	@$(COPY_CMD)
	@echo ---------------------------------------
	@echo EXITO. Ejecutable listo en: $(TARGET)
	@echo ---------------------------------------

clean:
	@$(CLEAN_CMD)
	@echo Limpieza completada.

.PHONY: all clean info