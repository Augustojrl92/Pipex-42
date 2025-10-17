# 🔩 Pipex-42

**Pipex** es un proyecto del cursus 42 cuyo objetivo es recrear el funcionamiento del operador de shell `|` (*pipe*) en C, utilizando **procesos**, **redirecciones de entrada/salida**, y **pipes UNIX**.  
El objetivo es comprender en profundidad cómo se comunican los procesos entre sí en un entorno UNIX/Linux.

---

## 🧠 Teoría detallada

### 🧵 Procesos en UNIX

Un proceso es una instancia en ejecución de un programa.  
Cada vez que ejecutas un comando o un binario, el sistema operativo crea un nuevo proceso que contiene:
- **Espacio de memoria propio** (código, datos, pila, heap).
- **Identificador único (PID)**.
- **Descriptores de archivo** abiertos (stdin, stdout, stderr y otros).

El sistema operativo organiza los procesos en una jerarquía:
- El proceso **padre** crea uno o varios **hijos** mediante `fork()`.
- Cada hijo hereda el entorno del padre (variables, ficheros abiertos, etc.).
- Ambos continúan su ejecución en paralelo, pero de forma independiente.

Ejemplo:
```c
pid_t pid = fork();
if (pid == 0)
    printf("Soy el proceso hijo\n");
else
    printf("Soy el proceso padre\n");
```

---

### 🔁 Comunicación entre procesos

Los procesos son **independientes**, pero pueden comunicarse a través de mecanismos como:
- **Pipes** (unidireccionales)
- **Sockets** (bidireccionales, red)
- **Archivos temporales**
- **Memoria compartida**

---

### 🔄 Pipes

Un **pipe** conecta la salida de un proceso con la entrada de otro.  
En C se crea con:

```c
int fd[2];
pipe(fd);
```

- `fd[0]`: extremo de **lectura**  
- `fd[1]`: extremo de **escritura**

La información escrita en `fd[1]` puede leerse desde `fd[0]`.  
El pipe actúa como un búfer en memoria gestionado por el kernel.

---

### ⚙️ Redirecciones con `dup2()`

`dup2(oldfd, newfd)` copia un descriptor de archivo.  
Se usa para redirigir la entrada o salida de un proceso.

Ejemplo:
```c
dup2(fd_in, STDIN_FILENO);   // la entrada estándar será fd_in
dup2(fd_out, STDOUT_FILENO); // la salida estándar será fd_out
```

Estas redirecciones permiten conectar un proceso con un archivo o con otro proceso a través de un pipe.

---

### 💥 Ejecución de comandos con `execve()`

`execve()` reemplaza el proceso actual por un nuevo programa.  
No crea un nuevo proceso; simplemente sustituye el contenido del proceso hijo por el ejecutable solicitado.

```c
execve(cmd_path, argv, envp);
```

- `cmd_path`: ruta absoluta o relativa al ejecutable.
- `argv`: argumentos del comando.
- `envp`: entorno de ejecución (PATH, variables, etc.).

Si `execve()` tiene éxito, nunca retorna.  
Si falla, retorna `-1` y el proceso continúa.

---

### 🧩 Resumen de funciones del sistema utilizadas

| Función | Propósito |
|----------|------------|
| **fork()** | Crea un proceso hijo que hereda el entorno del padre. |
| **pipe()** | Crea un canal unidireccional de comunicación (lectura/escritura). |
| **dup2()** | Redirige entradas/salidas estándar hacia archivos o pipes. |
| **execve()** | Sustituye el proceso actual por otro programa (ejecución del comando). |
| **waitpid()** | Espera la finalización de un proceso hijo. |
| **close()** | Cierra un descriptor de archivo (imprescindible para evitar fugas). |
| **access()** | Verifica permisos y existencia de un archivo ejecutable. |
| **open()** | Abre un archivo para lectura o escritura (usado para `infile` y `outfile`). |
| **exit()** | Termina el proceso con un código de estado. |

---

## ⚙️ Instalación y compilación

### 🔧 Requisitos
- Sistema operativo: Linux o macOS
- Compilador: `gcc` o `clang`
- `make` instalado
- Acceso a funciones del sistema (`fork`, `pipe`, `dup2`, `execve`, etc.)

### 🏗️ Compilación

```bash
make
```

Esto genera el ejecutable:

```bash
./pipex
```

Versión **bonus** (con `here_doc` y múltiples pipes):

```bash
make bonus
```

### 🧹 Limpieza

```bash
make clean
make fclean
make re
```

---

## 💡 Uso

### 📘 Forma general

```bash
./pipex infile "cmd1" "cmd2" outfile
```

➡️ Ejecuta `cmd1` leyendo desde `infile` y pasa su salida a `cmd2`,  
que finalmente escribe en `outfile`.

### 📙 Ejemplo

```bash
./pipex input.txt "grep 42" "wc -l" output.txt
```

Equivalente a:

```bash
< input.txt grep 42 | wc -l > output.txt
```

---

## 🧱 Estructura del proyecto

```
pipex/
├── Makefile
├── pipex.c               → función principal: control de flujo padre/hijo
├── pipex_children.c      → creación y ejecución de procesos hijo
├── pipex_utils.c         → funciones auxiliares (split, path, etc.)
├── pipex_errors.c        → manejo de errores y mensajes
├── includes/pipex.h      → cabecera principal
├── Aux/
│   ├── aux_1.c
│   ├── aux_2.c
│   ├── aux_3.c
│   └── aux_4.c           → utilidades extra
└── bonus/
    ├── src_bonus/
    │   ├── pipex_bonus.c
    │   ├── pipex_children_bonus.c
    │   ├── pipex_utils_bonus.c
    │   ├── pipex_errors_bonus.c
    │   ├── pipex_here_doc_bonus.c
    │   └── ...
    └── includes_bonus/pipex_bonus.h
```

---

## 🧠 Flujo del programa

### 🔹 Versión obligatoria

```
flowchart TD
    A([Inicio]) --> B[Validar argumentos y abrir archivos]
    B --> C[Crear pipe(fd)]
    C --> D[Crear proceso hijo 1 (cmd1)]
    D --> E[dup2(infile, STDIN_FILENO)]
    E --> F[dup2(fd[1], STDOUT_FILENO)]
    F --> G[execve(cmd1)]
    G --> H[Crear proceso hijo 2 (cmd2)]
    H --> I[dup2(fd[0], STDIN_FILENO)]
    I --> J[dup2(outfile, STDOUT_FILENO)]
    J --> K[execve(cmd2)]
    K --> L[Cerrar pipes y esperar hijos]
    L --> M([Fin])
```

---

### 🔸 Versión bonus (`here_doc` y múltiples pipes)

```
flowchart TD
    A([Inicio here_doc]) --> B[Leer delimitador del here_doc]
    B --> C[Guardar texto hasta encontrar el delimitador]
    C --> D[Crear pipes dinámicamente según número de comandos]
    D --> E[Para cada comando → crear un proceso hijo]
    E --> F{¿Es el primero?}
    F -- Sí --> G[Redirigir STDIN desde here_doc]
    F -- No --> H{¿Es el último?}
    H -- Sí --> I[Redirigir STDOUT al outfile]
    H -- No --> J[Redirigir STDIN/STDOUT a pipes intermedios]
    G --> K[execve(cmd)]
    I --> K
    J --> K
    K --> L[Esperar a todos los procesos hijos]
    L --> M([Fin])
```

---

## 🧩 Errores comunes

- ❌ **Bad file descriptor** → no cerrar correctamente los extremos del pipe.  
- ❌ **Command not found** → fallo en el `PATH` o en `execve()`.  
- ❌ **Segmentation fault** → mal manejo de punteros o `malloc`.  
- ❌ **Bloqueo (deadlock)** → leer y escribir en el mismo pipe sin cerrar extremos.

---

## 🧱 Normas 42

- Cumple **Norminette**.  
- Sin **memory leaks** (`valgrind` recomendado).  
- Sin usar funciones no autorizadas.  
- Gestión correcta de errores y cierres de descriptores.  
- Soporte completo de `here_doc` y pipes encadenados en la versión bonus.

---


