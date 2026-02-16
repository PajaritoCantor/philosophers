# 🍝 philosophers 

Este proyecto aborda el clásico problema de sincronización de Edsger Dijkstra. A través de la implementación de hilos y mutex, simulamos un ecosistema donde la gestión del tiempo y los recursos (tenedores) es la única frontera entre la vida y la muerte de un filósofo.

## **🏗️ Fase 1:** *Arquitectura y Fundamentos*
La base de este proyecto reside en una configuración estricta y una estructura de datos robusta para evitar el uso de variables globales, las cuales están prohibidas.

### 1. El Motor de Concurrencia (**Threads & Mutex**)
Para resolver la simulación, implementamos un sistema multihilo donde cada filósofo actúa de forma independiente. Las herramientas clave son:

* **pthread_create / pthread_join:** Gestión del ciclo de vida de los hilos.
* **pthread_mutex:** Implementamos "cerrojos" para garantizar que solo un filósofo posea un tenedor a la vez, evitando *Data Races*.

* **usleep / gettimeofday:** Control de precisión milimétrica para los tiempos de ejecución (time_to_eat, time_to_die, time_to_sleep).

### 2. Estándares de Ingeniería (Makefile)
* **Compilador:** ***cc***
* **Flags:** **-Wall -Werror -Wextra**
* **Reglas:** **all, clean, fclean, re**
  
## 📊 Diseño de Datos (No-Global Architecture)
Para cumplir con la restricción de zero global variables, hemos diseñado una jerarquía de estructuras que se pasan por referencia a cada hilo:


### Estructura Global (t_data)
Contiene los parámetros de entrada y herramientas de sincronización general:
* **int nb_philo:** Número de filósofos y tenedores.
* **size_t t_die**, **t_eat**, **t_sleep:** Tiempos críticos en ms.
* **pthread_mutex_t write_lock**: Mutex para que los logs no se superpongan.
* **pthread_mutex_t** ***forks**: Array de mutex que representan los tenedores físicos.

* **Especificaciones de los Argumentos**

Para ejecutar el programa **./philo**, se deben proporcionar los siguientes parámetros, asegurando que todos sean enteros positivos:

* **number_of_philosophers:** Define la cantidad total de filósofos sentados a la mesa y, por consiguiente, el número de hilos independientes y mutex (tenedores) que el programa debe orquestar simultáneamente.

* **time_to_die (ms):** Establece el umbral de supervivencia de cada filósofo, representando el tiempo máximo permitido entre el inicio de una comida y la siguiente antes de que el hilo monitor registre una defunción y detenga la simulación.

* **time_to_eat (ms):** Determina el periodo de ocupación de recursos, durante el cual un filósofo mantiene bloqueados los mutex de sus dos tenedores adyacentes para completar su ciclo de alimentación.

* **time_to_sleep (ms):** Especifica la duración del estado de reposo obligatorio que el filósofo debe cumplir inmediatamente después de liberar sus tenedores, antes de transicionar de nuevo al estado de pensamiento.

* **number_of_times_each_philosopher_must_eat (Opcional):** Actúa como una condición de salida por éxito, donde la simulación finaliza limpiamente si todos los hilos alcanzan este contador de comidas; de lo contrario, el programa solo termina ante la muerte de un filósofo.

### Estructura de Filósofo (t_philo)
Cada filósofo conoce su entorno inmediato:
* **int id:** Identificador único (1 a N).
* **pthread_t thread**: El hilo que ejecuta la rutina.
* **pthread_mutex_t** ***left_fork**: Puntero al tenedor de su izquierda.
* **pthread_mutex_t** ***right_fork**: Puntero al tenedor de su derecha.
* **t_data** ***data**: Referencia a los parámetros globales.
