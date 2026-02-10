# --- PROYECTO PORTABLE TOTAL (WINDOWS Y LINUX) ---

APP_NAME := mi_juego
SRC_DIR  := src
BIN_DIR  := bin
INC_DIR  := include

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I$(INC_DIR)

SRC      := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)

# --- DETECCIÓN DE SISTEMA ---
ifeq ($(OS),Windows_NT)
    # ---------------- WINDOWS ----------------
    DETECTED_OS := Windows
    TARGET      := $(BIN_DIR)/$(APP_NAME).exe
    LIB_DIR     := lib/windows
    
    LDFLAGS     := -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -static-libgcc -static-libstdc++
    
    MKDIR_CMD   := if not exist bin mkdir bin
    # Copia DLLs a bin
    COPY_CMD    := cmd /C "copy /Y lib\windows\*.dll bin 1>NUL"
    CLEAN_CMD   := if exist bin rmdir /s /q bin
    
else
    # ---------------- LINUX (MODO PORTABLE) ----------------
    DETECTED_OS := Linux
    TARGET      := $(BIN_DIR)/$(APP_NAME)
    LIB_DIR     := lib/linux
    
    # 1. -L$(LIB_DIR): Usa las libs de nuestra carpeta lib/linux
    # 2. -Wl,-rpath,'$ORIGIN': Dice al exe "Busca las librerías a tu lado"
    #    IMPORTANTE: Usamos '$$' para escapar el símbolo del dólar en Make
    LDFLAGS     := -L$(LIB_DIR) -lSDL2 -lSDL2_image -Wl,-rpath,'$$ORIGIN'

    MKDIR_CMD   := mkdir -p $(BIN_DIR)
    # CAMBIO IMPORTANTE: Copiamos TODO (*) lo que haya en lib/linux a bin/
    # Esto asegura que se copien los .so, .so.8, .so.16, etc.
    COPY_CMD    := cp -a $(LIB_DIR)/. $(BIN_DIR)/
    CLEAN_CMD   := rm -rf $(BIN_DIR)
endif

# --- REGLAS ---

all: info $(TARGET)

info:
	@echo ---------------------------------------
	@echo Sistema detectado: $(DETECTED_OS)
	@echo Compilando archivos: $(SRC)
	@echo ---------------------------------------

$(TARGET): $(SRC)
	@echo [1/3] Creando bin...
	@$(MKDIR_CMD)
	@echo [2/3] Compilando y Enlazando...
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)
	@echo [3/3] Copiando librerias locales...
	@$(COPY_CMD)
	@echo ---------------------------------------
	@echo LISTO. Ejecutable: $(TARGET)
	@echo ---------------------------------------

clean:
	@$(CLEAN_CMD)
	@echo Limpio.

.PHONY: all clean info