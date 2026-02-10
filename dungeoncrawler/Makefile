# --- Configuración General ---
APP_NAME := mi_app
SRC_DIR  := src
BIN_DIR  := bin
INC_DIR  := include
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I$(INC_DIR)

# --- Detección del Sistema Operativo ---
ifeq ($(OS),Windows_NT)
    # Detectado Windows
    DETECTED_OS := Windows
    LIB_DIR     := lib/windows
    EXT         := .exe
    
    # Flags de Windows (MinGW)
    # -static-libgcc -static-libstdc++ ayudan a evitar dependencias extra de MinGW
    LDFLAGS := -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++
    
    # Comando para copiar las DLLs necesarias al lado del ejecutable
    COPY_CMD := copy $(LIB_DIR)\*.dll $(BIN_DIR) >NUL
    MKDIR_CMD := if not exist $(BIN_DIR) mkdir $(BIN_DIR)
    CLEAN_CMD := if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
else
    # Detectado Linux (o Unix-like)
    DETECTED_OS := Linux
    LIB_DIR     := lib/linux
    EXT         := 
    
    # Flags de Linux
    # -Wl,-rpath,'$ORIGIN/../lib/linux' le dice al ejecutable dónde buscar las libs sin instalar nada
    LDFLAGS := -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,'$$ORIGIN/../$(LIB_DIR)'
    
    # Comandos Linux
    COPY_CMD := echo "Configuración Linux lista."
    MKDIR_CMD := mkdir -p $(BIN_DIR)
    CLEAN_CMD := rm -rf $(BIN_DIR)
endif

# --- Archivos ---
SRC    := $(wildcard $(SRC_DIR)/*.cpp)
TARGET := $(BIN_DIR)/$(APP_NAME)$(EXT)

# --- Reglas ---

all: info $(TARGET)

info:
	@echo "Sistema detectado: $(DETECTED_OS)"
	@echo "Compilando para $(DETECTED_OS)..."

$(TARGET): $(SRC)
	@$(MKDIR_CMD)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)
	@$(COPY_CMD)
	@echo "----------------------------------------"
	@echo "Compilacion exitosa: $(TARGET)"
	@echo "----------------------------------------"

clean:
	@$(CLEAN_CMD)
	@echo "Limpieza completada."

.PHONY: all clean info