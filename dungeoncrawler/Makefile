# --- Nombres y Directorios ---
APP_NAME := mi_app
SRC_DIR  := src
BIN_DIR  := bin
INC_DIR  := include

# --- Configuración del Compilador ---
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I$(INC_DIR)
SRC      := $(wildcard $(SRC_DIR)/*.cpp)

# --- DETECCIÓN DE SISTEMA OPERATIVO ---
ifeq ($(OS),Windows_NT)
    # ---------------- WINDOWS ----------------
    DETECTED_OS := Windows
    TARGET      := $(BIN_DIR)/$(APP_NAME).exe
    LIB_DIR     := lib/windows
    
    # Flags para Windows
    LDFLAGS     := -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++ -mwindows

    # Comandos AJUSTADOS: Escribimos las rutas "a lo bruto" con \ para que copy no falle
    MKDIR_CMD   := if not exist bin mkdir bin
    # El 1>NUL silencia la salida correcta, el 2>NUL silencia errores (opcional)
    COPY_CMD    := cmd /C "copy /Y lib\windows\*.dll bin 1>NUL"
    CLEAN_CMD   := if exist bin rmdir /s /q bin
    
else
    # ---------------- LINUX / UNIX ----------------
    DETECTED_OS := Linux
    TARGET      := $(BIN_DIR)/$(APP_NAME)
    LIB_DIR     := lib/linux
    
    # Flags para Linux
    LDFLAGS     := -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,'$$ORIGIN/../$(LIB_DIR)'

    # Comandos Bash estándar
    MKDIR_CMD   := mkdir -p $(BIN_DIR)
    COPY_CMD    := echo "Linux: No es necesario copiar DLLs."
    CLEAN_CMD   := rm -rf $(BIN_DIR)
endif

# --- REGLAS ---

all: info $(TARGET)

info:
	@echo ---------------------------------------
	@echo Sistema detectado: $(DETECTED_OS)
	@echo ---------------------------------------

$(TARGET): $(SRC)
	@echo [1/3] Creando directorios...
	@$(MKDIR_CMD)
	@echo [2/3] Compilando codigo fuente...
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)
	@echo [3/3] Configurando librerias...
	@$(COPY_CMD)
	@echo ---------------------------------------
	@echo EXITO. Ejecutable listo en: $(TARGET)
	@echo ---------------------------------------

clean:
	@echo Limpiando proyecto...
	@$(CLEAN_CMD)
	@echo Hecho.

.PHONY: all clean info