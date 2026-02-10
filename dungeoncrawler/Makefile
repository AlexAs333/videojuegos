# --- PROYECTO SDL2 UNIVERSAL ---

# Configuración
APP_NAME := mi_juego
SRC_DIR  := src
BIN_DIR  := bin
INC_DIR  := include

# Compilador
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I$(INC_DIR)

# Búsqueda Recursiva: Encuentra .cpp en src/ y en subcarpetas (src/Entities/...)
SRC      := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)

# --- DETECCIÓN DE SISTEMA OPERATIVO ---
ifeq ($(OS),Windows_NT)
    # ---------------- WINDOWS ----------------
    DETECTED_OS := Windows
    TARGET      := $(BIN_DIR)/$(APP_NAME).exe
    LIB_DIR     := lib/windows
    
    # Flags OBLIGATORIOS para SDL2 en Windows (El orden importa):
    # 1. mingw32 (necesario para el sistema)
    # 2. SDL2main (maneja el punto de entrada WinMain)
    # 3. SDL2 (la librería en sí)
    # -mwindows: Oculta la consola negra (quítalo si quieres ver std::cout)
    LDFLAGS     := -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 -mwindows -static-libgcc -static-libstdc++

    # Comandos CMD para Windows
    MKDIR_CMD   := if not exist bin mkdir bin
    # Copia la DLL automáticamente al compilar
    COPY_CMD    := cmd /C "copy /Y lib\windows\SDL2.dll bin 1>NUL"
    CLEAN_CMD   := if exist bin rmdir /s /q bin
    
else
    # ---------------- LINUX ----------------
    DETECTED_OS := Linux
    TARGET      := $(BIN_DIR)/$(APP_NAME)
    
    # En Linux usamos la librería del sistema (más estable)
    LDFLAGS     := -lSDL2

    MKDIR_CMD   := mkdir -p $(BIN_DIR)
    COPY_CMD    := echo "Linux: Listo."
    CLEAN_CMD   := rm -rf $(BIN_DIR)
endif

# --- REGLAS (NO TOCAR) ---

all: info $(TARGET)

info:
	@echo ---------------------------------------
	@echo Sistema: $(DETECTED_OS) (Modo SDL2)
	@echo Archivos: $(SRC)
	@echo ---------------------------------------

$(TARGET): $(SRC)
	@echo [1/3] Creando carpetas...
	@$(MKDIR_CMD)
	@echo [2/3] Compilando...
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)
	@echo [3/3] Instalando DLLs...
	@$(COPY_CMD)
	@echo ---------------------------------------
	@echo EXITO. Ejecuta: $(TARGET)
	@echo ---------------------------------------

clean:
	@$(CLEAN_CMD)
	@echo Limpieza completada.

.PHONY: all clean info