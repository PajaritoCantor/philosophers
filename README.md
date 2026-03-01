# 🍝 Philosophers - 42 Project 🍝

This project has been created as part of the 42 curriculum by @jurodrig.
## 📝 Description

This project is a simulation based on the classic Dining Philosophers problem. It explores the fundamentals of concurrent programming, specifically how to create and manage threads, and how to use mutexes to protect shared resources and avoid data races.

The goal is to keep a set of philosophers alive by ensuring they can eat, sleep, and think without dying from starvation or causing a deadlock.
## ⚙️ Instructions
## 🛠️ Compilation

The project must be compiled with the flags -Wall -Wextra -Werror. To compile the mandatory part, navigate to the philo/ directory and run:
Bash

make

## 🚀 Execution

Run the program with the following arguments in order:
Bash

    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

## 📌 Variables Explained

  * 👥 number_of_philosophers: The total number of philosophers and also the number of forks.

  * ⌛ time_to_die (ms): If a philosopher doesn't start eating time_to_die milliseconds after starting their last meal (or the start of the simulation), they die.
  * 🍝 time_to_eat (ms): The time it takes for a philosopher to eat. During this time, they must hold two forks.

  * 💤 time_to_sleep (ms): The time a philosopher spends sleeping.

  * 🔢 number_of_times_each_philosopher_must_eat (optional): If all philosophers have eaten at least this many times, the simulation stops.

## 💡 Example
Bash

./philo 5 800 200 200

    Note: In this case, there are 5 philosophers. They will die if they don't eat for 800ms. Each eating and sleeping action lasts 200ms.

## 📚 Resources

The implementation relies on the POSIX threads library (pthread) and authorized standard C functions:

  * pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock, etc.

  * gettimeofday and usleep for high-precision time management.

## 🤖 AI Usage Disclosure

As per the requirements in Chapter VII of the 42 subject, here is the description of AI usage in this project:

  * <u>Code Formatting</u>: Assistance in ensuring Norminette compliance for variable alignments and function structures.

  * <u>Debugging</u>: Identifying potential data races and memory leaks during the development of thread synchronization.

  * <u>Makefile Generation</u>: Structuring the build system to handle subdirectories and prevent relinking.

  * <u>Documentation</u>: Drafting the required README file in English as per the subject's requirements.

## ⚠️ Important Rules

  * 🚫 No Global Variables: All shared data is passed via structures to avoid forbidden globals.

  * 🔒 Thread Safety: Each fork is protected by a mutex to prevent duplication.

  * ⏱️ Precision: The system monitor ensures death is reported within 10ms of the actual event.

  * 🧹 Clean Exit: All memory allocated on the heap is properly freed, and all mutexes are destroyed before the program exits.


## 📂 Parsing de Argumentos

El módulo de parsing se encarga de validar y convertir los argumentos de entrada de la línea de comandos en datos estructurados para la simulación.

#### static bool is_digit(char c)

* Descripción: Comprueba si el carácter recibido pertenece al rango numérico de la tabla ASCII.

* Retorno: true si es un dígito ('0'-'9'), false en caso contrario.

#### static bool is_space(char c)

* Descripción: Identifica caracteres de espacio en blanco. Incluye el espacio estándar (' ') y los caracteres de control de salto de línea, tabulaciones y retornos de carro (códigos ASCII del 9 al 13).

* Retorno: true si es un espacio, false en caso contrario.

#### static const char *valid_input(const char *str)

* Descripción: Es el filtro de seguridad principal para las entradas. Realiza cuatro comprobaciones críticas:

  * Ignora espacios iniciales y gestiona el símbolo opcional +.

  * Rechaza números negativos o símbolos inválidos.

  * Asegura que solo contenga dígitos numéricos y detecta caracteres inválidos al final de la cadena (trailing characters).

  * Valida que la longitud del número no exceda los 10 dígitos para prevenir desbordamientos previos a la conversión.

  * Retorno: Un puntero al inicio del número validado dentro de la cadena.

#### static long ft_atol(const char *str)

* Descripción: Convierte una cadena de caracteres validada en un número de tipo long.

* Funcionamiento: Itera sobre los dígitos multiplicando el resultado previo por 10 y sumando el valor del carácter actual. Al finalizar, verifica que el resultado no supere el INT_MAX (2147483647).

* Error: Si el valor excede el límite de un entero de 32 bits, detiene el programa con un mensaje de error.

#### void parse_input(t_table *table, char **av)

* Descripción: Orquestador del parsing que inicializa la estructura principal t_table.

  * Validaciones específicas del proyecto:

  * Límite de Filósofos: Restringe la simulación a un máximo de 200 para evitar sobrecarga del sistema.

  * Límite de Tiempo: Exige que los tiempos de muerte, comida y sueño sean superiores a 60ms para garantizar la estabilidad de los hilos.

  * Comidas opcionales: Si se proporciona el quinto argumento, se asigna como límite de comidas; de lo contrario, se inicializa en -1 (simulación infinita hasta que alguien muera).
 
## 🏗️ Inicialización de Datos e Infraestructura

Este módulo prepara la memoria y los mecanismos de sincronización necesarios para que la simulación sea segura y eficiente.

#### static void assign_forks(t_philo *philo, t_fork *forks, int position)

* **Descripción:** Asigna los dos tenedores correspondientes a cada filósofo.

* **Estrategia Anti-Deadlock:** Implementa una jerarquía de recursos basada en el ID del filósofo:

* **Filósofos Pares:** Intentan tomar primero el tenedor de su derecha y luego el de su izquierda.

* **Filósofos Impares:** Intentan tomar primero el tenedor de su izquierda y luego el de su derecha.

* **Importancia:** Al romper la simetría (que no todos intenten agarrar el mismo lado a la vez), se elimina la posibilidad de un bloqueo circular (Deadlock), donde todos tienen un tenedor y esperan eternamente por el segundo.

#### static void philo_init(t_table *table)

* Descripción: Inicializa individualmente a cada filósofo dentro del array de la mesa.

    * Funcionamiento:

        * Asigna el ID único (ajustado a base 1 para el log).

        * Establece los contadores de comidas y estados iniciales.

* Crea un mutex propio para cada filósofo (philo_mutex), necesario para proteger variables que el monitor leerá (como la hora de la última comida o si está lleno) sin causar Data Races.

  * Llama a la asignación de tenedores.

#### void data_init(t_table *table)

* Descripción: Es la función constructora principal que reserva memoria y prepara los recursos globales.

    * Pasos Críticos:

        * Reserva memoria dinámica para los arrays de filósofos y tenedores.

        * Inicializa los mutexes globales: table_mutex (para control de la simulación) y write_mutex (para evitar que los mensajes en consola se mezclen/solapen).

         * Inicializa cada tenedor como un mutex individual contenido en la estructura t_fork.

       * Llama a la inicialización de filósofos para completar el montaje de la mesa.

## 🛠️ Utilidades de Seguridad y Tiempo

Este módulo contiene funciones de bajo nivel diseñadas para abstraer la complejidad de las librerías de sistema y añadir una capa de gestión de errores crítica para la estabilidad de la simulación.
### void *safe_malloc(size_t bytes)

* Descripción: Un envoltorio (wrapper) para la función malloc estándar.

* Propósito: Automatiza la comprobación de errores. En sistemas con memoria crítica, si malloc falla y devuelve NULL, la función invoca error_exit inmediatamente, evitando que el programa intente acceder a punteros nulos en pasos posteriores.

### void safe_mutex_handle(t_mtx *mutex, t_opcode opcode)

* Descripción: Gestiona de forma centralizada todas las operaciones de los hilos (Pthreads) relacionadas con mutexes.

  * Códigos de Operación (Opcodes): Soporta INIT, LOCK, UNLOCK y DESTROY.

  * Gestión de Errores: Utiliza la función interna handle_mutex_error para interceptar códigos de error específicos de POSIX (como EDEADLK para bloqueos mutuos o EPERM para accesos no autorizados). Esto facilita enormemente el debugging y asegura que el programa se detenga de forma controlada ante un fallo de sincronización.

### long gettime(t_time_code time_code)

* Descripción: Obtiene la hora actual del sistema con alta resolución utilizando gettimeofday.

    * Versatilidad: Permite obtener el tiempo en Milisegundos (para el registro de logs y cálculos de muerte) o en Microsegundos (para la precisión interna del sueño de los filósofos).

    * Fórmula: Convierte los segundos y microsegundos de la estructura timeval a una unidad lineal para facilitar las comparaciones matemáticas de tiempo.

### void precise_usleep(long usec, t_table *table)

* Descripción: Una implementación personalizada de usleep que soluciona la falta de precisión del usleep estándar de la librería de C.

    * Mecanismo:

        * Registra el tiempo inicial.

        * Entra en un bucle de espera activa (busy-waiting) fragmentado con pequeños usleep(100).

        * Sincronización: Comprueba constantemente simulation_finished(table). Si un filósofo muere mientras otro está durmiendo, este último despierta inmediatamente para permitir que el hilo finalice, evitando que el programa se quede colgado esperando a que terminen los tiempos de sueño.

### 🧠 static void assign_forks(t_philo *philo, t_fork *forks, int position)

Esta es la función más crítica para la estabilidad del proyecto, ya que implementa la solución de jerarquía de recursos para evitar el Deadlock (bloqueo mutuo).

* El Problema: Si todos los filósofos intentan agarrar el mismo tenedor (por ejemplo, el izquierdo) al mismo tiempo, todos se quedarían bloqueados esperando por el derecho, que tiene su vecino.

    * La Solución (Asimetría): La función divide a los filósofos en Pares e Impares:

    * Filósofos Impares: Primero intentan tomar su tenedor izquierdo (position) y luego el derecho (position + 1).

    * Filósofos Pares: Invierten el orden; primero intentan tomar su tenedor derecho (position + 1) y luego el izquierdo (position).

    * Cálculo del Tenedor Derecho: Utiliza el operador módulo % table->philo_nbr para que el último filósofo de la mesa tome el tenedor 0 como su tenedor derecho, cerrando así el círculo de la mesa.

### 👥 static void philo_init(t_table *table)

Esta función actúa como el "constructor" de cada filósofo, inicializando sus atributos individuales y vinculándolos con la mesa de simulación.

* Identificación: Asigna a cada filósofo un id único (empezando desde 1 para facilitar la lectura de los logs).

* Estado Inicial: Inicializa el contador de comidas en 0 y el estado full (lleno) en false.

* Sincronización Individual: Inicializa un mutex propio para cada filósofo (philo_mutex).

  * ¿Por qué? Para que el monitor pueda leer datos del filósofo (como cuándo fue su última comida) de forma segura mientras el filósofo está escribiendo en ellos, evitando Data Races.

  * Asignación de Herramientas: Llama a assign_forks para determinar qué punteros a tenedores le corresponden a ese filósofo específico según su posición en la mesa.
 
### 👤 void *lone_philo(void *arg)

Esta función es la rutina específica para el caso excepcional de un único filósofo en la simulación. Está diseñada para cumplir estrictamente con el sujeto del proyecto, donde un filósofo no puede comer si no dispone de dos tenedores.

* **Sincronización Inicial:** Utiliza wait_all_threads para asegurar que el cronómetro de la simulación no empiece hasta que todos los preparativos internos estén listos.

    * **Gestión de Tiempos:** Registra el momento de su "última comida" (last_meal_time) justo al empezar, para que el monitor pueda calcular correctamente cuánto tiempo pasa hasta que muera.

*    **Acción Única**: El filósofo realiza la única acción posible: intentar coger el primer tenedor disponible. Esto se registra mediante write_status(TAKE_FIRST_FORK, philo).

  * **Bucle de Espera**: Dado que nunca podrá obtener un segundo tenedor, el hilo entra en un bucle de espera pasiva (usleep) comprobando constantemente si la simulación ha terminado (es decir, hasta que el Monitor detecte que ha pasado su time_to_die y marque el fin del programa).
