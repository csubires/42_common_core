![Rating](/assets/images/header.png)

# MINITALK

## Indice del proyecto
- [SERVER](#SERVER)
- [CLIENT](#CLIENT)
- [SERVER BONUS](#SERVER_BONUS)
- [CLIENT BONUS](#CLIENT_BONUS)
- [Operadores de manipulación de bits](#Operadores_de_manipulación_de_bits)
- [Info Extra](#Info_Extra)

## Descripción
Crear un servicio clientes / servidor, en el cual los clientes puedan mandar mensajes de texto al servidor mediante señales UNIX del sistema SIGUSR1 y SIGUSR2. Es decir clientes y servidor serán procesos que se envien señales. El servidor se ejecutará primero. Para poder enviar el texto hay que ir carácter a carácter pasando a binario, asociando 0 y 1 a las señales SIGUSR1 y SIGUSR2.

En C, las señales SIGUSR1 y SIGUSR2 son señales definidas por el usuario que se utilizan para la comunicación entre procesos. Estas señales no tienen un comportamiento predeterminado asociado y están disponibles para que los programadores las utilicen según sus necesidades.

## Funciones permitidas

- [ft_printf](#ft_printf)
- [write](#write)
- [signal](#signal)
- [sigemptyset](#sigemptyset)
- [sigaddset](#sigaddset)
- [sigaction](#sigaction)
- [kill](#kill)
- [getpid](#getpid)
- [malloc](#malloc)
- [free](#free)
- [pause](#pause)
- [sleep](#sleep)
- [usleep](#usleep)
- [exit](#exit)

### ft_printf

Para escribir textos por pantalla.

### write

**Descripción:** Escribe datos desde un búfer en un descriptor de archivo.

**Prototipo:** size_t write(int fd, const void *buf, size_t count);

**Uso:** Se utiliza para escribir datos a un archivo o descriptor de archivo. Es una llamada al sistema de bajo nivel que proporciona una interfaz directa con el sistema operativo, a diferencia de funciones de alto nivel como fprintf o fwrite en las bibliotecas estándar de C. Es comúnmente utilizada en sistemas operativos Unix y Unix-like.

### signal

**Descripción:** Establece una rutina de manejo para una señal específica.

**Prototipo:** void (*signal(int signum, void (*handler)(int)))(int);

**Uso:** Define cómo debe comportarse el programa cuando recibe una señal particular (por ejemplo, SIGINT, SIGTERM).

### sigemptyset

**Descripción:** Inicializa un conjunto de señales vacío.

**Prototipo:** int sigemptyset(sigset_t *set);

**Uso:** Prepara un conjunto de señales para que no contenga ninguna señal, útil antes de agregar señales específicas.

### sigaddset

**Descripción:** Añade una señal específica a un conjunto de señales.

**Prototipo:** int sigaddset(sigset_t *set, int signum);

**Uso:** Modifica un conjunto de señales para incluir una señal específica.

### sigaction

**Descripción:** Cambia la acción a tomar cuando se recibe una señal específica.

**Prototipo:** int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

**Uso:** Permite un control más detallado sobre la manipulación de señales que signal.

### kill

**Descripción:** Envía una señal a un proceso o grupo de procesos.

**Prototipo:** int kill(pid_t pid, int sig);

**Uso:** Puede utilizarse para terminar procesos, interrumpirlos o enviarles cualquier otra señal.

### getpid

**Descripción:** Devuelve el ID del proceso del proceso que llama.

**Prototipo:** pid_t getpid(void);

**Uso:** Obtener el identificador único del proceso actual.

### malloc

**Descripción:** Asigna un bloque de memoria de tamaño especificado.

**Prototipo:** void *malloc(size_t size);

**Uso:** Reserva memoria dinámica en el heap.

### free

**Descripción:** Libera un bloque de memoria previamente asignado por malloc, calloc o realloc.

**Prototipo:** void free(void *ptr);

**Uso:** Devuelve la memoria asignada al sistema.

### pause

**Descripción:** Hace que el proceso actual espere hasta recibir una señal.

**Prototipo:** int pause(void);

**Uso:** Suspende la ejecución del programa hasta que se reciba una señal.

### sleep

**Descripción:** Suspende la ejecución del proceso durante un número especificado de segundos.

**Prototipo:** unsigned int sleep(unsigned int seconds);

**Uso:** Pausa la ejecución del programa por un tiempo determinado.

### usleep

**Descripción:** Suspende la ejecución del proceso durante un número especificado de microsegundos.

**Prototipo:** int usleep(useconds_t usec);

**Uso:** Similar a sleep, pero con mayor precisión temporal.

### exit

**Descripción:** Termina la ejecución del proceso y devuelve un valor de estado al sistema operativo.

**Prototipo:** void exit(int status);

**Uso:** Finaliza el programa de manera controlada, permitiendo liberar recursos y devolver un código de salida.

## Más restricciones:

- Puedes utilizar una variable global por programa (una para el cliente y otra para el servidor), pero tendrás que justificar su uso.


Existen dos estructuras por cada proceso en el cual se guardan las señales pendientes y las bloqueadas. Con números de 32 bits se pueden manejar hasta 32 señales.

### Bonus
- El servidor confirma cada señal recibida mandando una señal al cliente.
- Soporta los caracteres Unicode.

<br>

## Operadores de manipulación de bits

### Operador | (OR bit a bit) (server)

**Descripción:** Realiza una operación OR a nivel de bits entre dos números.

**Funcionamiento:** Compara cada bit correspondiente de los operandos. Si al menos uno de los bits es 1, el bit resultante será 1; de lo contrario, será 0.

**Uso típico:** Se utiliza para establecer bits específicos en un valor.

### Operador << (Desplazamiento a la izquierda) (server)

**Descripción:** Desplaza los bits de un número a la izquierda un número especificado de posiciones.

**Funcionamiento:** Cada desplazamiento a la izquierda equivale a multiplicar el número por 2. Los bits desplazados hacia la izquierda salen del número y se insertan ceros por la derecha.

**Uso típico:** Se utiliza para operaciones de multiplicación rápida por potencias de dos o para manipulación de bits específicos en valores binarios.

### Operador & (AND bit a bit) (client)

**Descripción:** Compara cada bit de los operandos. Si ambos bits son 1, el bit resultante es 1. Si alguno de los bits es 0, el bit resultante es 0.

### Operador >> (desplazamiento a la derecha) (client)

**Descripción:** Desplaza los bits del operando a hacia la derecha n posiciones. Los bits desplazados hacia fuera del número se descartan. Si es un entero con signo, el bit de signo puede replicarse para llenar los nuevos bits a la izquierda (desplazamiento aritmético) o se pueden llenar con ceros (desplazamiento lógico, normalmente usado para enteros sin signo).

<br>

## SERVER

### set_signals
``` c
void	set_signals(void)
```
Establecer las señales y asociar SIGUSR1 y SIGUSR2 a la función que va a manejar la señal.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>


### receive_msg
``` c
void	receive_msg(int sig_usr, siginfo_t *info, void *na)
```
Función que maneja las señales y las "traduce" a carácter para ser mostrada.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### main
``` c
int	main(void)
```
Muestra el PID del proceso y espera a recibir señales.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

## CLIENT

### ft_send_char
``` c
static void	ft_send_char(int pid, unsigned char c)
```
"Traduce" un carácter a "binario" haciendo que cada señal corresponda a SIGUSR1 o SIGUSR2.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### ft_send_msg
``` c
static void	ft_send_msg(int pid, const char *str)
```
Simplemente se encarga de ir pasando los carácteres de un texto a la función que los envia (ft_send_char).
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### main
``` c
int	main(int argc, char *argv[])
```
Muestra la ayuda en caso de que se haya utilizado mal el ejecutable, y si todo está correcto manda el texto.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

## BONUS

>Similar a la versión sin bonus. Lo único que cambia es que el servidor debe mandar una señal de vuelta confirmando que la ha recibido.

## SERVER BONUS

### receive_msg
``` c
void	receive_msg(int sig_usr, siginfo_t *info, void *na)
```
Mandar confirmación al cliente.

``` c
	if (sig_usr == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (sig_usr == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
```
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

## CLIENT BONUS

### confirm_handler
``` c
static void	ft_confirm(int sig_usr)
```
Confirmar que la señal a llegado y muestra un mensaje.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>


### main
``` c
int	main(int argc, char *argv[])
```
Establece el manejador de la señal para la confirmación de llegada.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>


## Diferencias signal y sigaction

### signal

**Prototipo:** void (*signal(int signum, void (*handler)(int)))(int);

**Descripción:** Establece una rutina de manejo para una señal específica.

**Uso:** Es una forma más simple y directa de asociar un manejador a una señal.

**Limitaciones:**

Comportamiento menos predecible: Dependiendo de la implementación, la acción para una señal puede restablecerse al comportamiento por defecto después de que la señal sea manejada.

Control limitado: No ofrece la capacidad de especificar más detalles sobre cómo se deben manejar las señales.

Compatibilidad: Es menos portable ya que algunas implementaciones pueden variar su comportamiento entre diferentes sistemas Unix y Unix-like.

### sigaction

**Prototipo:** int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

**Descripción:** Permite establecer una rutina de manejo para una señal específica con más control y flexibilidad.

**Uso:** Es una forma más robusta y controlada de manejar señales, recomendada para aplicaciones serias.

**Ventajas:**

Persistencia del manejador: El manejador establecido con sigaction no se restablece automáticamente al valor por defecto después de manejar una señal, a menos que se indique explícitamente.

Más opciones: Permite especificar opciones adicionales, como enmascarar otras señales mientras se maneja una señal específica y otras configuraciones avanzadas.

Portabilidad: Es más consistente y portable entre diferentes sistemas Unix y Unix-like.

>Para aplicaciones donde se necesita un manejo detallado y fiable de señales, sigaction es la opción recomendada.

## Info Extra


### struct sigaction

	La estructura struct sigaction se utiliza en la función sigaction para especificar cómo se deben manejar las señales en un programa en C. Proporciona un control detallado sobre el comportamiento de las señales.

**Campos de struct sigaction**

sa_handler:

	Puntero a una función que maneja la señal, o una de las constantes:
		SIG_DFL: Utiliza el comportamiento por defecto para la señal.
		SIG_IGN: Ignora la señal.
	Ejemplo: sa.sa_handler = handler;

sa_sigaction:

	Puntero a una función manejadora de señales extendida que proporciona información adicional sobre la señal recibida. Utilizado cuando SA_SIGINFO está establecido en sa_flags.
	Ejemplo: sa.sa_sigaction = extended_handler;

sa_mask:

	Conjunto de señales que se deben bloquear (enmascarar) durante la ejecución del manejador de señales para evitar interrupciones por esas señales.
	Ejemplo: sigemptyset(&sa.sa_mask);

sa_flags:

	Opciones que modifican el comportamiento del manejador de señales. Algunas de las opciones más comunes son:
		SA_RESTART: Hace que ciertas llamadas al sistema que son interrumpidas por esta señal se reinicien automáticamente.
		SA_SIGINFO: Utiliza sa_sigaction en lugar de sa_handler para proporcionar información adicional sobre la señal.
	Ejemplo: sa.sa_flags = SA_RESTART;

sa_restorer:

	Campo obsoleto y generalmente no utilizado en las implementaciones modernas. Se ignora en la mayoría de las plataformas.


---

Cuestiones: Cuando se finaliza un cliente antes de que se mande el texto completo, en la parte del servidor se empieza a corromper el texto porque ya no sabe por que posición va de la cadena de bits de un carácter. Se podría solucionar metiendo el estado en una variable estática como una estructura, por cada PID del cliente distinto.
El problema aparece también al mandar mensajes simultaneamente desde distintos clientes.

Para mostrar el texto completo una vez recibido entero, habría que reservar memoría para dicho texto, pero desde el servidor no se sabe la longitud. Entonces se podría mandar la longitud del texto antes de enviarlo desde el cliente, pero entonces ya no se podría saber si cumple la condición de 1 segundo por cada 100 letras, ya que tendría que esperar a que se mande todo (imagina 1 millón de carácteres)

[$${\color{red}VOLVER}$$](../../README.md)
