# practica-1-pvc++

para compilar el trabajo usando CMake, creas una carpeta llamada "out" o "bin" dentro de este proyecto y escribes el siguient comando

```emcmake cmake -S . -B (la carpeta que creaste) -G Ninja```

una vez que termine, vas a out (o bin) y escribes el siguiente comando

```cmake --build .```

# Importante

antes de ejecutar CMake, asegúrate que el entorno de emscripten esté activo ejecutando el siguiente comando:

```
emsdk_env.bat (en Windows CMD)
emsdk_env.ps1 (en PowerShell)
emsdk_env.sh (si usas linux)
```
