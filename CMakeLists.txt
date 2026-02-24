cmake_minimum_required(VERSION 3.15)
project(Gioco VERSION 1.0 LANGUAGES CXX)

# Forza l'uso dello standard C++17 o superiore (consigliato per SFML 3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Trova il pacchetto SFML 3
# Assicurati che SFML sia installato nel sistema o che il percorso sia in CMAKE_PREFIX_PATH
set(SFML_DIR "C:/sfml/SFML-3.0.0/lib/cmake/SFML")
find_package(SFML 3 COMPONENTS System Window Graphics Audio REQUIRED)

# 2. Aggiungi l'eseguibile
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp
    include/Game.hpp
)

# 3. Collega le librerie di SFML
# Nota: Con SFML 3 i target usano il namespace SFML::
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics 
    SFML::Audio 
    SFML::Window 
    SFML::System
)

# 4. (Opzionale) Copia le DLL su Windows dopo la compilazione
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin" # Percorso tipico delle DLL in SFML
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()