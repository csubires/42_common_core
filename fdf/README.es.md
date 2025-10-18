![Rating](/_assets/images/header.png)

# FDF [subject](es.fdf.pdf)

<p style="text-align:center">

![FDF](../../assets/fdf/fdf1.png)
</p>

## Indice de contenidos

- [Descripción](#Descripción)
- [Funciones autorizadas](#funciones-autorizadas)
- [Restricciones](#Restricciones)
- [Conceptos clave](#Conceptos-clave)
- [BONUS](#BONUS)
- [Principales algoritmos para generar líneas](#Principales-algoritmos-para-generar-líneas)
- [Manipulando el mapa 3D](#manipulando-el-mapa-3d)
- [Consejos](#Consejos)
- [Recursos](#Recursos)

## Descripción
Este proyecto se trata de la creación de un simple modelo de estructura alámbrica de un paisaje. Wireframe es un algoritmo de renderización del que resulta una imagen semitransparente, de la cual solo se dibujan las aristas de la malla que constituye al objeto modelado.

Una representación isométrica es un tipo de proyección gráfica utilizada para representar objetos tridimensionales en dos dimensiones. Se caracteriza por mostrar las tres dimensiones del objeto de manera equitativa, sin distorsionar su tamaño, y mantiene las proporciones entre las dimensiones. En esta proyección, las líneas paralelas en el objeto real se mantienen paralelas en la representación gráfica, y los ángulos entre los ejes proyectados son iguales, típicamente a 120 grados.

__Características de la Proyección Isométrica:__

- Escalas Iguales: En una representación isométrica, las tres dimensiones (x, y, z) del objeto se representan utilizando la misma escala. Esto significa que las distancias se mantienen proporcionales en cada eje, haciendo que las medidas sean verdaderas a la escala en las tres dimensiones.

- Ángulos Uniformes: Los ángulos entre los ejes proyectados son iguales. Normalmente, cada eje está separado por un ángulo de 120 grados en la vista bidimensional, permitiendo una representación equilibrada de la estructura del objeto.

- Distorsión de Ángulos pero no de Escalas: Aunque los ángulos originales del objeto no se preservan (a excepción de los paralelos a los ejes), el tamaño relativo de las partes del objeto sí se mantiene. Esto significa que el objeto no parece deformado o distorsionado en su escala.

- Visualización Simultánea de Tres Caras: Permite ver tres caras del objeto simultáneamente (las vistas frontal, lateral y superior), proporcionando una percepción más completa del diseño y estructura del objeto.

- No Perspectiva: A diferencia de la proyección en perspectiva, donde las líneas convergen hacia un punto de fuga, la proyección isométrica no tiene puntos de fuga y no simula la disminución de tamaño de los objetos con la distancia.

## Funciones autorizadas
| Función | Descripción |
| ------- | ----------- |
| open | Abre un archivo en el sistema de archivos y retorna un descriptor de archivo que se utiliza para realizar operaciones posteriores sobre el archivo. |
| close | Cierra un descriptor de archivo previamente abierto con open, liberando cualquier recurso asociado al mismo. |
| read | Lee datos de un archivo referenciado por un descriptor de archivo y los almacena en un búfer. |
| write | Escribe datos desde un búfer en un archivo referenciado por un descriptor de archivo. |
| malloc | Reserva un bloque de memoria dinámica en el heap del tamaño especificado en bytes. |
| free | Libera un bloque de memoria previamente asignado por malloc u otras funciones de asignación dinámica de memoria, permitiendo su reutilización. |
| perror | Imprime un mensaje de error a stderr basado en el último error que ocurrió, seguido de una descripción del error asociado al código global errno. |
| strerror | Devuelve una cadena de caracteres que representa la descripción de un código de error dado. |
| exit | Termina la ejecución de un programa de manera ordenada, realizando una limpieza adecuada y devolviendo un estado de salida al sistema operativo. |

- Todas las funciones de la librería math (-lm opción del compilador, man 3 math)
- Todas las funciones de la librería MiniLibX
- ft_printf y cualquier función que TÚ hayas programado

## Restricciones
- Debes utilizar la MiniLibX
- El uso de variables globales están prohibidas.
- Los mapas se pasarán como unico argumento mediante archivos .fdf
- Tu programa no debe tener ningún tipo de crash cuando se ejecuta.
- Tu programa tiene que mostrar la imagen en una ventana.
- La gestión de su ventana debe permanecer fluida (cambiando de ventanas, mini-
mizando, etc).
- Al presionar ESC se debe cerrar la ventana y terminar el programa de forma limpia.
- Al hacer click en la x en el marco de la ventana se debe cerrar la ventana y terminar el programa de forma limpia.
- El uso de las imágenes de la MiniLibX es obligatoria.

## Conceptos clave
Uno de los problemas al empezar este proyecto es que no sabes por donde empezar, ni que buscar. Ahí van algunos conceptos a investigar:
- Wireframe
- Proyección isométrica
- Segmentos de lineas
- Algoritmo de lineas Bresenham
- Interpolacion lineal
- Paralelaje
- Matriz de proyeccion
- Renderizar y rasterizar

### Wireframe
    Un wireframe es una representación visual simplificada de un objeto tridimensional mediante líneas y aristas que conectan los vértices. Se utiliza para mostrar la estructura básica del modelo sin detalles de superficie como texturas o sombras. Es una técnica común en el diseño y modelado 3D para conceptualizar y revisar rápidamente la geometría de un objeto.

### Proyección Isométrica
    La proyección isométrica es un método de representación gráfica tridimensional en el que los tres ejes del espacio (x, y, z) se muestran con ángulos iguales de 120 grados entre sí. Esto permite que las dimensiones de los ejes se mantengan en proporciones iguales, proporcionando una visión clara y equilibrada de los objetos sin distorsión de perspectiva. Se utiliza frecuentemente en dibujos técnicos y videojuegos isométricos.

### Segmentos de Líneas
    Un segmento de línea es una porción finita de una línea recta delimitada por dos puntos finales. A diferencia de una línea infinita, un segmento de línea tiene una longitud definida y se utiliza para conectar puntos en gráficos y geometría computacional.

### Algoritmo de Líneas de Bresenham
    El algoritmo de Bresenham es un método eficiente para dibujar líneas rectas en una cuadrícula de píxeles. Utiliza cálculos enteros para determinar qué píxeles deben activarse para representar la línea, evitando operaciones de punto flotante. Es ampliamente utilizado en gráficos de computadoras por su precisión y rapidez.

### Interpolación Lineal
    La interpolación lineal es un método para estimar valores dentro de un intervalo entre dos puntos conocidos mediante la suposición de que el cambio entre los puntos es lineal. Se utiliza en gráficos para suavizar transiciones y calcular valores intermedios.

### Paralaje
    El paralaje es la diferencia en la posición aparente de un objeto visto desde dos puntos de vista diferentes. En gráficos y fotografía, se utiliza para crear una sensación de profundidad simulando cómo los objetos más cercanos parecen moverse más rápidamente que los objetos lejanos.

### Matriz de Proyección
    Una matriz de proyección es una herramienta matemática utilizada para transformar coordenadas de un espacio 3D a un espacio 2D, como una pantalla de computadora. Define cómo se mapearán los objetos 3D en la vista 2D, afectando la perspectiva y la escala de los objetos renderizados.

### Renderizar
	Renderizar es el proceso de generar una imagen final a partir de un modelo 3D o una escena definida en una computadora. Involucra calcular luces, texturas, sombras, y otros efectos visuales para crear una representación visual detallada.

### Rasterizar
	Rasterizar es el proceso de convertir una imagen o escena vectorial (basada en geometría) en una cuadrícula de píxeles (imagen raster). Es una etapa clave en la renderización gráfica, donde las primitivas gráficas se transforman en píxeles que se pueden mostrar en una pantalla.

## Mapa FDF
Cada número representa un punto en el espacio:
- La posición horizontal corresponde a su eje X.
- La posición vertical corresponde a su eje Y.
- El valor corresponde a su altitud, eje Z.

## BONUS

![MAP](../../assets/fdf/map1.png)

Obtendrás algunos puntos extras si añades:
- Una proyección extra (como paralela o cónica)
- Acercar y alejar.
- Trasladar tu modelo.
- Rotar tu modelo.
- Añade un bonus más de tu elección.

![MENU](../../assets/fdf/menu.png)

## Principales algoritmos para generar líneas
### 1. Algoritmo de Bresenham

El algoritmo de Bresenham es un método clásico para dibujar líneas en una cuadrícula de píxeles. Utiliza solo operaciones aritméticas enteras, lo que lo hace muy eficiente.

Ventajas:

- Eficiencia: Utiliza operaciones de suma y resta, evitando el uso de multiplicaciones o divisiones, lo que lo hace rápido y adecuado para hardware limitado.

- Precisión: Genera líneas con píxeles contiguos sin saltos, lo que asegura una representación precisa y continua de la línea.

- Simplicidad: Fácil de implementar y comprender, ideal para aplicaciones de tiempo real.

Inconvenientes:

- Sin suavizado: No maneja el anti-aliasing, por lo que las líneas pueden aparecer con bordes irregulares y poco suaves.

- Limitaciones en color: Solo puede producir líneas de un color sólido, sin gradaciones.

### Ejemplo de Implementación:

``` c
void drawLineBresenham(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x0, y0); // Función para establecer el color del píxel

        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
```

### 2. Algoritmo de Xiaolin Wu

El algoritmo de Xiaolin Wu es un método de generación de líneas con anti-aliasing que produce líneas más suaves aplicando técnicas de suavizado de color.

Ventajas:

- Anti-aliasing: Suaviza los bordes de las líneas, reduciendo el efecto de escalera (aliasing).

- Calidad Visual: Produce líneas visualmente atractivas, especialmente útil en gráficos de alta resolución.

Inconvenientes:

- Complejidad Computacional: Más complejo y lento que Bresenham debido a las operaciones de punto flotante y mezcla de colores.

- Requiere Buffer de Color: Necesita acceso a un buffer de color que permita mezclar colores, lo que puede ser costoso en sistemas con recursos limitados.

### Ejemplo de Implementación:

``` c
void drawLineXiaolinWu(int x0, int y0, int x1, int y1) {
    auto ipart = [](float x) { return floor(x); };
    auto round = [](float x) { return ipart(x + 0.5); };
    auto fpart = [](float x) { return x - floor(x); };
    auto rfpart = [](float x) { return 1 - fpart(x); };

    float dx = x1 - x0;
    float dy = y1 - y0;
    bool steep = abs(dy) > abs(dx);

    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }
    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    dx = x1 - x0;
    dy = y1 - y0;
    float gradient = dy / dx;

    int xend = round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = rfpart(x0 + 0.5);
    int xpxl1 = xend;
    int ypxl1 = ipart(yend);

    if (steep) {
        setPixel(ypxl1, xpxl1, rfpart(yend) * xgap);
        setPixel(ypxl1 + 1, xpxl1, fpart(yend) * xgap);
    } else {
        setPixel(xpxl1, ypxl1, rfpart(yend) * xgap);
        setPixel(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
    }

    float intery = yend + gradient;

    xend = round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5);
    int xpxl2 = xend;
    int ypxl2 = ipart(yend);

    if (steep) {
        setPixel(ypxl2, xpxl2, rfpart(yend) * xgap);
        setPixel(ypxl2 + 1, xpxl2, fpart(yend) * xgap);
    } else {
        setPixel(xpxl2, ypxl2, rfpart(yend) * xgap);
        setPixel(xpxl2, ypxl2 + 1, fpart(yend) * xgap);
    }

    if (steep) {
        for (int x = xpxl1 + 1; x < xpxl2; ++x) {
            setPixel(ipart(intery), x, rfpart(intery));
            setPixel(ipart(intery) + 1, x, fpart(intery));
            intery += gradient;
        }
    } else {
        for (int x = xpxl1 + 1; x < xpxl2; ++x) {
            setPixel(x, ipart(intery), rfpart(intery));
            setPixel(x, ipart(intery) + 1, fpart(intery));
            intery += gradient;
        }
    }
}
```

### 3. Algoritmo de DDA (Digital Differential Analyzer)

El algoritmo DDA es otro método para generar líneas basado en la interpolación incremental de puntos entre los dos extremos de la línea.

Ventajas:

- Facilidad de Implementación: Sencillo de implementar y comprender, adecuado para aplicaciones simples.

- Calidad Aceptable: Produce líneas razonablemente rectas y continuas en muchas situaciones.

Inconvenientes:

- Rendimiento: Utiliza operaciones de punto flotante, lo que puede ser más lento y menos eficiente que el algoritmo de Bresenham.

- No Suavizado: Similar a Bresenham, no aplica suavizado a las líneas.

### Ejemplo de Implementación:

```c
void drawLineDDA(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; ++i) {
        setPixel(round(x), round(y)); // Función para establecer el color del píxel
        x += xIncrement;
        y += yIncrement;
    }
}
```

### 4. Algoritmo de Gupta-Sproull

El algoritmo de Gupta-Sproull es una variante del algoritmo de Bresenham que incluye anti-aliasing para mejorar la calidad visual de las líneas.

Ventajas:

- Anti-aliasing Mejorado: Produce líneas suaves y agradables visualmente al aplicar técnicas de suavizado.

- Calidad Superior: Adecuado para aplicaciones gráficas donde la calidad visual es crítica.

Inconvenientes:

- Complejidad: Más complejo de implementar que los algoritmos sin suavizado.

- Costo Computacional: Requiere más recursos computacionales debido al suavizado y cálculos adicionales.

### Ejemplo de Implementación:

```c
void drawLineGuptaSproull(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int D = 2 * dy - dx;
    int y = y0;
    int thickness = 1; // Espesor de la línea

    for (int x = x0; x <= x1; x++) {
        for (int i = -thickness; i <= thickness; i++) {
            setPixel(x, y + i); // Función para establecer el color del píxel
        }
        if (D > 0) {
            y++;
            D = D - 2 * dx;
        }
        D = D + 2 * dy;
    }
}
```

### 5. Algoritmo de Bresenham con Anti-aliasing

Este algoritmo es una modificación del algoritmo de Bresenham que incluye anti-aliasing para mejorar la suavidad de las líneas.

Ventajas:

- Eficiencia con Suavizado: Combina la eficiencia de Bresenham con la capacidad de suavizar los bordes de las líneas.

- Buena Calidad Visual: Ideal para gráficos donde la suavidad es importante pero el rendimiento sigue siendo una prioridad.

Inconvenientes:

- Complejidad Adicional: Más complicado que el Bresenham original.

- Requiere Cálculos Adicionales: Utiliza cálculos de intensidad para suavizar las líneas, lo que puede afectar el rendimiento en sistemas con limitaciones.

### Ejemplo de Implementación:

```c
void drawLineBresenhamAA(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x0, y0); // Función para establecer el color del píxel
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
```

### Comparación Resumida

| Algoritmo | Ventajas | Inconvenientes |
| --------- | -------- | -------------- |
| Bresenham | Eficiente, preciso, simple | Sin suavizado, líneas sólidas |
| Xiaolin Wu | Anti-aliasing, alta calidad visual | Complejidad computacional, requiere buffer de color |
| DDA | Fácil de implementar, calidad aceptable | Rendimiento menor, sin suavizado |
| Gupta-Sproull | Suavizado mejorado, calidad superior | Complejidad, costo computacional |
| Bresenham con AA | Eficiente con suavizado, buena calidad visual | Complejidad adicional, requiere cálculos adicionales |

## [Manipulando el mapa 3D](Transformaciones_geometricas_3D.pdf)

La manipulación de coordenadas en 3D mediante transformaciones como rotación, traslación y zoom es fundamental en gráficos por computadora, modelado 3D, y aplicaciones de realidad virtual. Estas transformaciones se pueden representar matemáticamente utilizando matrices, lo que facilita su aplicación en conjuntos de coordenadas 3D. A continuación, se presenta el concepto matemático de cada transformación y cómo se representa mediante matrices.

### 1. Rotación

La rotación en 3D implica girar un conjunto de puntos alrededor de uno o más de los ejes principales del espacio tridimensional: el eje X, el eje Y y el eje Z. Cada rotación se representa con una matriz de transformación que, al multiplicarse por el vector de coordenadas, efectúa la rotación deseada.

>Rotación alrededor del eje X

La matriz de rotación para girar un `ángulo θ` alrededor del eje X es:

$Rx(θ)=\begin{bmatrix}
1&0&0&0\\
0&cos⁡(θ)&−sin⁡(θ)&0\\
0&sin⁡(θ)&cos⁡(θ)&0&\\
0&0&0&1
\end{bmatrix}$

>Rotación alrededor del eje Y

La matriz de rotación para girar un `ángulo θ` alrededor del eje Y es:

$Rx​(θ)=\begin{bmatrix}
cos⁡(θ)&0&sin⁡(θ)&0​\\
0&1&0&0​\\
−sin⁡(θ)&0&cos⁡(θ)&0​\\
0&0&0&1​\\
\end{bmatrix}$

>Rotación alrededor del eje Z

La matriz de rotación para girar un `ángulo θ` alrededor del eje Z es:

$Rx​(θ)=\begin{bmatrix}
cos⁡(θ)&−sin⁡(θ)&0&0​\\
sin⁡(θ)&cos⁡(θ)&0&0​\\
0&0&1&0​\\
0&0&0&1​\\
\end{bmatrix}$

>Combinación de Rotaciones

Las rotaciones en los tres ejes pueden combinarse multiplicando las matrices de rotación individuales. El orden de multiplicación es importante ya que las rotaciones no son conmutativas.

$$
R=Rx(α)⋅Ry(β)⋅Rz(γ)
$$


donde αα, ββ, y γγ son los ángulos de rotación alrededor de los ejes X, Y, y Z respectivamente.

__Ejemplo de Rotación__

Si tienes un punto `P=(x,y,z)` y deseas rotarlo `θ grados` alrededor del eje Z, el nuevo punto `P′` será:

$P′=Rz(θ)⋅
\begin{bmatrix}
x\\y\\z\\1
\end{bmatrix}$

### 2. Traslación

La traslación en 3D implica mover un conjunto de puntos en el espacio tridimensional por una distancia dada en las direcciones de los ejes X, Y y Z. Esta transformación también se representa con una matriz.

>Matriz de Traslación

Para trasladar un punto en 3D por `tx`​ unidades en el eje X, `ty`​ unidades en el eje Y y `tz`​ unidades en el eje Z, se utiliza la siguiente matriz:

$T(tx,ty,tz)=
\begin{bmatrix}
1&0&0&tx\\
0&1&0&ty\\
0&0&1&tz\\
0&0&0&1
\end{bmatrix}$
>Aplicación de la Traslación

Dado un punto `P=(x,y,z)`, la nueva posición `P′` tras la traslación es:

$P′=T(tx,ty,tz)⋅
\begin{bmatrix}
x\\y\\z\\1
\end{bmatrix}=
\begin{bmatrix}
x+tx\\y+ty\\z+tz\\1
\end{bmatrix}$

### 3. Zoom (Escalado)

El escalado, o "zoom", en 3D se refiere a cambiar el tamaño de un objeto en una o más direcciones. Esto se realiza multiplicando las coordenadas del objeto por un factor de escala.
Matriz de Escalado

Para escalar un punto en 3D por un factor `sx`​ en el eje X, `sy`​ en el eje Y, y `sz`​ en el eje Z, la matriz de escalado es:

$S(sx,sy,sz)=
\begin{bmatrix}
sx&0&0&0\\
0&sy&0&0\\
0&0&sz&0\\
0&0&0&1
\end{bmatrix}$

__Aplicación del Escalado__

Dado un punto `P=(x,y,z)`, la nueva posición `P′` tras el escalado es:

$P′=S(sx,sy,sz)⋅
\begin{bmatrix}
x\\y\\z\\1
\end{bmatrix}=
\begin{bmatrix}
sx⋅x\\sy⋅y\\sz⋅z\\1
\end{bmatrix}$

>Zoom Uniforme

Si el zoom es uniforme en todas las direcciones (es decir, sx = sy = sz = s), el escalado se convierte en:

$S(s)=
\begin{bmatrix}
s&0&0&0\\
0&s&0&0\\
0&0&s&0\\
0&0&0&1
\end{bmatrix}$
​
Esto agranda o reduce el objeto de manera proporcional en todas las dimensiones.

	Las transformaciones en 3D son herramientas poderosas que permiten manipular objetos y escenas de manera efectiva. El uso de matrices de transformación no solo simplifica la aplicación de estas transformaciones, sino que también proporciona un marco matemático robusto para operaciones gráficas complejas. Con una comprensión clara de la rotación, traslación y zoom en 3D, se pueden crear efectos visuales impresionantes y realistas en aplicaciones de gráficos por computadora.


### Consejos
>Controla que no tengas fugas de memoria

``` bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fdf_bonus maps/42.fdf
```
>Dependiendo de la librería que uses es posible que contenga fugas que no podrás controlar, y por supuesto no pasará la norminette. Puedes incluir estas librerías una vez te hayan pasado la norminette en la evaluación o ejecutar la norminette a cada una de tus carpetas.

### Recursos
- [Algunos códigos de tecla](https://anzeljg.github.io/rin2/book2/2405/docs/tkinter/key-names.html)
- [Ayuda con la minilibx](https://harm-smits.github.io/42docs/libs/minilibx)
- [MLX42](https://github.com/codam-coding-college/MLX42/blob/master/include/MLX42/MLX42.h)
- [Proyección](https://docs.hektorprofe.net/graficos-3d/17-matriz-de-proyeccion/)
- [Wikipedia](https://es.wikipedia.org/wiki/Modelo_de_estructura_al%C3%A1mbrica)
- [Herramienta de color](https://rgbcolorcode.com/color/008000)
- [Herramienta de color](https://www.rgbtohex.net/)

[$${\color{red}VOLVER}$$](../../README.md)
