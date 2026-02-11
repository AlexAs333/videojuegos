cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(mi_juego)

# Estándar C++17 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración de salida
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Buscar archivos fuente recursivamente (src/*.cpp y subcarpetas)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Incluir cabeceras 
target_include_directories(${PROJECT_NAME} PRIVATE include)

# --- DETECCIÓN DE SISTEMA ---
if(WIN32)
    # ---------------- WINDOWS ----------------
    message(STATUS "Sistema detectado: Windows (Modo Portable)")

    # Directorio de librerías (-Llib/windows)
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/windows)

    # Librerías a enlazar (-l...)
    # Nota: El orden importa. SDL2main debe ir antes de SDL2 en MinGW
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        mingw32 
        SDL2main 
        SDL2 
        SDL2_image
    )

    # Flags de compilación (-mwindows -static-libgcc ...)
    target_link_options(${PROJECT_NAME} PRIVATE 
        -mwindows 
        -static-libgcc 
        -static-libstdc++
    )

    # Copiar DLLs a la carpeta bin después de compilar
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/lib/windows
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Copiando DLLs a la carpeta bin..."
    )

elseif(UNIX AND NOT APPLE)
    # ---------------- LINUX ----------------
    message(STATUS "Sistema detectado: Linux (Modo Portable)")

    # Directorio de librerías (-Llib/linux)
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/linux)

    # Librerías a enlazar
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2_image)

    # Flags especiales para runtime path (-Wl,-rpath,'$ORIGIN')
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-rpath,'$ORIGIN'")

    # Copiar .so files a la carpeta bin
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/lib/linux
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Copiando librerias .so a la carpeta bin..."
    )
endif()