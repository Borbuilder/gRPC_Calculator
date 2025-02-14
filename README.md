# 🚀 gRPC Calculator

Этот проект реализует калькулятор с использованием **gRPC** для взаимодействия между клиентом и сервером.

---

## 📦 Сборка проекта

### 🔹 Необходимые зависимости
- **CMake** (версия **3.14** или выше)
- **Компилятор C++** (**GCC/MinGW**, **MSVC** или **Clang**)
- **vcpkg** (менеджер пакетов)
- **Git**

---

### 🔹 Установка зависимостей через vcpkg
1. Установите **gRPC** и **Protobuf**:
   ```bash
   vcpkg install grpc protobuf --triplet=x64-mingw-dynamic  # Динамическая линковка
   ```

---

## 📥 Клонирование репозитория
1. Откройте терминал или командную строку.
2. Выполните команду для клонирования репозитория:
   ```bash
   git clone https://github.com/Borbuilder/gRPC_Calculator.git
   ```
3. Перейдите в папку проекта:
   ```bash
   cd gRPC_Calculator
   ```

---

## 🛠️ Сборка через CMake
1. Создайте папку `build` и перейдите в неё:
   ```bash
   mkdir build && cd build
   ```
2. Запустите **CMake**, указав путь к `toolchain`-файлу **vcpkg** и триплет:
   ```bash
   cmake .. -DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg>/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic
   ```
3. Соберите проект:
   ```bash
   cmake --build . --config Release
   ```

---

## ❗ Решение ошибки `grpc_cpp_plugin`  
Если **CMake** не может найти `grpc_cpp_plugin`, укажите путь к нему явно в `CMakeLists.txt`:

```cmake
find_program(GRPC_CPP_PLUGIN_EXECUTABLE
    NAMES grpc_cpp_plugin
    PATHS "<path_to_vcpkg>/vcpkg/installed/x64-mingw-dynamic/tools/grpc"
    REQUIRED
)
```

---

## ▶️ Запуск

### 🔹 Сервер
Перейдите в папку с исполняемыми файлами и запустите сервер:
```bash
cd build/bin
./server.exe
```

### 🔹 Клиент
В отдельном терминале запустите клиент:
```bash
cd build/bin
./client.exe
```

