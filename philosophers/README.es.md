![Rating](/assets/images/header.png)

# PHILOSOPHERS

## Descripción
En este proyecto, aprenderás los principios básico de hilar un proceso.
Vas a aprender a como crear hilos y descubrirás los mutex.

>Versión clásica

	El problema de los filósofos comensales es un clásico de la programación concurrente que ilustra problemas de sincronización, donde cinco filósofos alternan entre pensar y comer, pero solo pueden comer si tienen acceso a dos tenedores (uno a su izquierda y otro a su derecha). Esto genera posibles condiciones de carrera, interbloqueo (deadlock) y hambre (starvation) si no se maneja correctamente el acceso concurrente a los recursos compartidos (los tenedores).

> Versión del proyecto
- Uno o más filósofos se sientan en una mesa redonda.
- En el centro de la mesa se encuentra un gran bol de espaguetis.
- Cuándo un filósofo termine de comer, dejará los tenedores en la mesa e inmediatamente empezará a dormir. Una vez se despierte, empezará a pensar nuevamente.
- La simulación se detendrá cuando un filósofo muere por inanición.
- También hay tenedores en la mesa, tantos tenedores como filósofos.
- Todos los filósofos necesitan comer y nunca deben morir de hambre.
- Los filósofos no saben si otro filósofo va a morir.
- Si solo hay un filósofo, solo habrá un tenedor en la mesa.

## Funciones permitidas
| Función | Descripción |
| ------- | ----------- |
|memset | Rellena un bloque de memoria con un valor específico |
|printf | Imprime texto formateado a la salida estándar |
|malloc | Reserva dinámicamente un bloque de memoria en el heap |
|free | Libera un bloque de memoria previamente reservado con malloc |
|write | Escribe datos desde un buffer en un descriptor de archivo |
|usleep | Suspende la ejecución del programa durante un tiempo en microsegundos |
|gettimeofday | Obtiene el tiempo actual del sistema en segundos y microsegundos |
|pthread_create | Crea un nuevo hilo de ejecución |
|pthread_detach | Desvincula un hilo, permitiendo que libere sus recursos automáticamente al terminar |
|pthread_join | Espera a que un hilo termine su ejecución y recoge su valor de retorno |
|pthread_mutex_init | Inicializa un mutex para sincronización de hilos |
|pthread_mutex_destroy | Destruye un mutex, liberando los recursos asociados |
|pthread_mutex_lock | Bloquea un mutex, impidiendo que otros hilos lo adquieran |
|pthread_mutex_unlock | Desbloquea un mutex, permitiendo que otros hilos lo adquieran |

* NO SE PERMITE USAR LIBFT

## Restricciones
- Las variables globales están prohibidas.
- Los filósofos solo pueden comer, pensar, o dormir.
- Mientras están comiendo, no pueden pensar ni dormir;
- Mientras están pensando, no pueden dormir ni comer;
- Mientras están durmiendo, no pueden comer ni pensar.
- Los filósofos deben tomar el tenedor de la derecha y el de la izquierda, uno en cada mano.
- Los filósofos no hablan entre ellos.
- Todos deben evitar morir.
- El estado impreso no debe estar roto o alterado por el estado de otros filósofos.
- No puedes tener más de 10ms entre la muerte de un filósofo y el momento en el que imprimes su muerte.
- Tu programa no debe tener ningún data races.
- Para prevenir que los filósofos dupliquen los tenedores, deberás proteger los estados de los tenedores con un mutex por cada uno de ellos
- Directorio parte obligatoria : philo/
- Directorio parte bonus : philo_bonus/

>Cualquier cambio de estado de un filósofo debe tener el siguiente formato:
- (tiempo actual en milisegundos) (numero del filósofo) has taken a fork
- (tiempo actual en milisegundos) (numero del filósofo) is eating
- (tiempo actual en milisegundos) (numero del filósofo) is sleeping
- (tiempo actual en milisegundos) (numero del filósofo) is thinking
- (tiempo actual en milisegundos) (numero del filósofo) died

## Argumentos del programa
| Posición | Nombre |
| -------- | ------ |
| 1 | number_of_philosophers | es el número de filósofos, pero también el número de tenedores |
| 2 | time_to_die (en milisegundos) si un filósofo no empieza a comer en time_to_die milisegundos desde el comienzo de su ultima comida o desde el principio de la simulación, este morirá |
| 3 | time_to_eat (en milisegundos) es el tiempo que tiene un filósofo para comer. Durante ese tiempo, tendrá los tenedores ocupados |
| 4 | time_to_sleep (en milisegundos) es el tiempo que tiene un filósofo para dormir |
| 5 | number_of_times_each_philosopher_must_eat (argumento opcional) si todos los filósofos comen al menos number_of_times_each_philosopher_must_eat veces, la simulación se detendrá. Si no se especifica, la simulación se detendrá con la muerte de un filósofo |

- Cada filósofo debe ser un hilo.
- Cada filósofo tendrá asignado un número del 1 al number_of_philosophers.
- El filósofo número 1 se sentará al lado del filósofo número number_of_philosophers.
- Cualquier otro filósofo número N se sentarán entre el filósofo número N - 1 y el filósofo número N + 1.

## ¿Cuando es aceptable que muera un filósofo?
- Cuando sólo hay 1; Muere al haber 1 solo tenedor, con lo cual no puede comer.
- Cuando el número de filósofos es par:
	- Si el tiempo hasta que necesita comer es menor al tiempo que tarda en comer más el tiempo para dormir. Muere al no darle tiempo a completar el ciclo.
	- Si el tiempo que tarda en comer es mayor que la mitad del tiempo hasta que necesita volver a comer. Muere mientras come al no darle tiempo a terminar.
- Cuando el número de filósofos es impar:
	- Si el tiempo hasta que necesita comer es menor al tiempo que tarda en comer más el tiempo para dormir. Muere al no darle tiempo a completar el ciclo.
	- Si el tiempo que tarda en comer es mayor que un tercio del tiempo hasta que necesita volver a comer. Muere mientras come al no darle tiempo a terminar.

## BONUS

### Descripción
Philosophers con procesos y semaforos

Las reglas específicas para la parte bonus son:
- Los tenedores están en el centro de la mesa.
- Los tenedores no tienen estados de memoria, pero el numero de disponibilidades está representados por un semaforo.
- Cada filósofo debe ser un proceso, y el proceso principal no debe ser un filósofo.

### Funciones permitidas
| Función | Descripción |
| ------- | ----------- |
| memset | Rellena un bloque de memoria con un valor específico |
| printf | Imprime texto formateado a la salida estándar |
| malloc | Reserva dinámicamente un bloque de memoria en el heap |
| free | Libera un bloque de memoria previamente reservado con malloc |
| write | Escribe datos desde un buffer en un descriptor de archivo |
| fork | Crea un nuevo proceso duplicando el proceso actual |
| kill | Envía una señal a un proceso para realizar una acción, como terminarlo |
| exit | Termina el proceso actual y devuelve un código de estado al sistema |
| pthread_create | Crea un nuevo hilo de ejecución en un programa multihilo |
| pthread_detach | Desvincula un hilo, permitiendo la liberación automática de sus recursos |
| pthread_join | Espera a que un hilo termine y recoge su valor de retorno |
| usleep | Suspende la ejecución del programa durante un tiempo en microsegundos |
| gettimeofday | Obtiene el tiempo actual del sistema en segundos y microsegundos |
| waitpid | Espera a que un proceso hijo específico termine y recoge su estado de salida |
| sem_open | Abre o crea un semáforo POSIX |
| sem_close | Cierra un semáforo POSIX |
| sem_post | Incrementa (libera) el contador de un semáforo |
| sem_wait | Decrementa (bloquea) el contador de un semáforo, esperando si es necesario |
| sem_unlink | Elimina un semáforo POSIX previamente creado |

## Glosario
- Threads: Unidades ligeras de ejecución dentro de un proceso que comparten el mismo espacio de memoria y recursos, permitiendo la ejecución concurrente.
- Mutex: Un mecanismo de sincronización utilizado para evitar condiciones de carrera, permitiendo que solo un hilo acceda a un recurso compartido a la vez.
- Proceso: Una instancia en ejecución de un programa, con su propio espacio de memoria y recursos independientes de otros procesos.
- Inline: En C, la palabra clave inline se utiliza para sugerir al compilador que una función debe ser insertada directamente en el código en lugar de ser llamada mediante la rutina normal de llamadas a funciones. Esto puede mejorar el rendimiento al evitar el overhead de la llamada, pero es solo una sugerencia; el compilador puede ignorarla si lo considera necesario.
- deadlock

## Includes
- limits.h: Define constantes que especifican los límites de los tipos de datos estándar (por ejemplo, INT_MAX, CHAR_MIN).
- memory.h: Declara funciones para manipular bloques de memoria, como memcpy, memset y memmove.
- pthread.h: Proporciona las interfaces para la programación con hilos en POSIX, incluyendo la creación, sincronización y manejo de hilos.
- stdio.h: Declara funciones para la entrada y salida estándar, como printf, scanf, fopen, y fclose.
- stdlib.h: Define funciones para la gestión de memoria dinámica, la conversión de cadenas, y la ejecución de procesos, como malloc, free, atoi, y exit.
- sys/time.h: Proporciona funciones para obtener y manipular tiempos y fechas, como gettimeofday y timercmp.
- unistd.h: Declara funciones para las operaciones básicas del sistema, como read, write, fork, y sleep.
- sys/types.h: Define tipos de datos utilizados en llamadas al sistema, como pid_t, size_t, y off_t.
- sys/wait.h: Declara macros y funciones para manejar la terminación de procesos hijos, como wait, waitpid, y WIFEXITED.
- stdbool.h: Define el tipo booleano bool y los valores true y false para representar la lógica booleana en C.
- fcntl.h: Proporciona funciones y macros para el control de archivos y descriptores, como open, fcntl, y O_RDONLY.
- sys/stat.h: Declara funciones y macros para manejar atributos de archivos, como stat, chmod, y S_IRUSR.
- semaphore.h: Define funciones y tipos para la sincronización basada en semáforos POSIX, como sem_init, sem_wait, y sem_post.
- signal.h: Declara funciones y macros para el manejo de señales, como signal, kill, y raise.

[$${\color{red}VOLVER}$$](../../README.md)

200 filósofos obtengo delays superiores a los 10ms

## ERRORS
### FATAL: ThreadSanitizer: unexpected memory mapping 0x584eeef07000-0x584eeef0b000
- https://stackoverflow.com/questions/77850769/fatal-threadsanitizer-unexpected-memory-mapping-when-running-on-linux-kernels
- https://ziggit.dev/t/threadsanitizer-unexpected-memory-mapping-error/4930
- https://github.com/google/sanitizers/issues/1696

SOLUTCION??SO
https://github.com/google/sanitizers/issues/1716
https://stackoverflow.com/questions/62001623/why-does-helgrind-show-lock-order-violated-error-message



Para implementar un mecanismo que permita saber cuántos procesos hijos han finalizado correctamente o prematuramente, puedes utilizar las funciones y macros proporcionadas por waitpid(), WIFEXITED(status), WEXITSTATUS(status), y kill().
Conceptos clave:

    waitpid(-1, &status, 0): Espera a que cualquier proceso hijo termine y guarda el estado de salida en status.
    WIFEXITED(status): Devuelve verdadero si el proceso hijo terminó normalmente (es decir, hizo una llamada a exit() o regresó del main()).
    WEXITSTATUS(status): Devuelve el código de salida del proceso hijo si terminó normalmente.
    kill(): Sirve para enviar una señal a un proceso específico. Puede utilizarse para terminar hijos prematuramente, por ejemplo, con la señal SIGTERM o SIGKILL.

Mecanismo propuesto:

    El proceso padre creará múltiples hijos (usando fork()).
    Los hijos terminarán de forma normal (exit()) o prematuramente (mediante kill() o señales).
    El padre monitoriza a sus hijos con waitpid(-1, &status, 0) y usa las macros WIFEXITED() y WEXITSTATUS() para contar cuántos hijos terminaron normalmente y cuántos lo hicieron de forma prematura.

Ejemplo de implementación:

``` c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    int num_hijos = 5;
    int hijos_finalizados_correctamente = 0;
    int hijos_finalizados_prematuramente = 0;

    pid_t pid;
    int i;

    // Crear múltiples procesos hijos
    for (i = 0; i < num_hijos; i++) {
        pid = fork();

        if (pid == 0) {
            // Código del hijo
            if (i % 2 == 0) {
                // Los hijos con índices pares terminan normalmente
                printf("Hijo %d: terminando normalmente.\n", getpid());
                exit(0);  // Código de salida 0 indica éxito
            } else {
                // Los hijos con índices impares esperan y son terminados por una señal
                printf("Hijo %d: esperando y finalizado prematuramente.\n", getpid());
                sleep(5);
                // El padre puede matar este proceso después de cierto tiempo
            }
        } else if (pid < 0) {
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        }
    }

    // Proceso padre: controlar la finalización de los hijos
    for (i = 0; i < num_hijos; i++) {
        int status;
        pid_t terminated_pid = waitpid(-1, &status, 0);  // Espera por cualquier hijo

        if (terminated_pid == -1) {
            perror("Error en waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            // El hijo ha terminado normalmente con exit() o return
            printf("Padre: El hijo %d terminó correctamente con código de salida %d.\n", terminated_pid, WEXITSTATUS(status));
            hijos_finalizados_correctamente++;
        } else if (WIFSIGNALED(status)) {
            // El hijo terminó prematuramente debido a una señal
            printf("Padre: El hijo %d fue finalizado prematuramente por la señal %d.\n", terminated_pid, WTERMSIG(status));
            hijos_finalizados_prematuramente++;
        }
    }

    // El padre puede terminar a los hijos que no han finalizado prematuramente
    for (i = 0; i < num_hijos; i++) {
        kill(0, SIGTERM);  // Finaliza todos los hijos que aún no han terminado
    }

    printf("Resumen: %d hijos terminaron correctamente.\n", hijos_finalizados_correctamente);
    printf("Resumen: %d hijos terminaron prematuramente.\n", hijos_finalizados_prematuramente);

    return 0;
}

```


Explicación del código:

    Crear múltiples hijos: El ciclo fork() crea num_hijos procesos hijos. Cada hijo tiene un comportamiento diferente:
        Si el índice del hijo es par, el proceso hijo termina normalmente con exit(0).
        Si el índice es impar, el hijo espera (usando sleep()) y será finalizado prematuramente por el padre después de cierto tiempo.

    Control en el padre:
        El proceso padre usa waitpid(-1, &status, 0) para esperar a que cada hijo termine.
        WIFEXITED(status): Verifica si el hijo terminó normalmente. Si es así, el padre incrementa el contador hijos_finalizados_correctamente.
        WIFSIGNALED(status): Verifica si el hijo fue terminado prematuramente por una señal, en cuyo caso incrementa el contador hijos_finalizados_prematuramente.

    Uso de kill: Después de esperar a todos los hijos, el padre puede utilizar kill(0, SIGTERM) para finalizar cualquier hijo que aún esté en ejecución (en este caso, los hijos que estaban esperando en sleep).

    Contadores: Al final del programa, el padre imprime el número de hijos que finalizaron correctamente o prematuramente.

Notas importantes:

    waitpid(-1, &status, 0): -1 indica que el padre esperará a cualquier hijo que termine.
    WIFEXITED(status) y WEXITSTATUS(status): Estas macros verifican y obtienen el código de salida si el proceso terminó normalmente.
    WIFSIGNALED(status) y WTERMSIG(status): Verifican si el hijo fue terminado por una señal y obtienen la señal que causó su terminación.

Este mecanismo te permite contabilizar cuántos hijos terminaron correctamente y cuántos fueron finalizados prematuramente.

https://nafuka11.github.io/philosophers-visualizer/

### Testear
./philo 1 800 200 200. The philosopher should not eat and should die.
./philo 5 800 200 200. No philosopher should die.
./philo 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
./philo 4 410 200 200. No philosopher should die.
./philo 4 310 200 100. One philosopher should die.
With 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
./philo with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, and so forth.



valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./philo 2 200 10 10 2
valgrind --tool=helgrind --track-fds=yes --history-level=approx  ./philo 2 200 10 10 2
valgrind --tool=drd ./philo 2 200 10 10 2
valgrind --tool=memcheck --leak-check=full ./philo 2 200 10 10 2

[$${\color{red}VOLVER}$$](../../README.md)
