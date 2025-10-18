
```markdown
![Rating](/_assets/images/header.png)

# FDF [subject](es.fdf.pdf)

<p style="text-align:center">

![FDF](../../assets/fdf/fdf1.png)
</p>

## Table of Contents

- [Description](#Description)
- [Allowed Functions](#allowed-functions)
- [Restrictions](#Restrictions)
- [Key Concepts](#Key-Concepts)
- [BONUS](#BONUS)
- [Main Algorithms for Generating Lines](#Main-Algorithms-for-Generating-Lines)
- [Manipulating the 3D Map](#manipulating-the-3d-map)
- [Tips](#Tips)
- [Resources](#Resources)

## Description
This project involves creating a simple wireframe model of a landscape. Wireframe is a rendering algorithm that results in a semi-transparent image, where only the edges of the mesh that constitutes the modeled object are drawn.

An isometric representation is a type of graphical projection used to represent three-dimensional objects in two dimensions. It is characterized by showing the three dimensions of the object equally, without distorting its size, and maintains the proportions between dimensions. In this projection, parallel lines in the real object remain parallel in the graphical representation, and the angles between the projected axes are equal, typically at 120 degrees.

__Characteristics of Isometric Projection:__

- Equal Scales: In an isometric representation, the three dimensions (x, y, z) of the object are represented using the same scale. This means that distances remain proportional on each axis, making measurements true to scale in all three dimensions.

- Uniform Angles: The angles between the projected axes are equal. Typically, each axis is separated by an angle of 120 degrees in the two-dimensional view, allowing a balanced representation of the object's structure.

- Angle Distortion but not Scale: Although the original angles of the object are not preserved (except for those parallel to the axes), the relative size of the object's parts is maintained. This means the object does not appear deformed or distorted in its scale.

- Simultaneous Display of Three Faces: Allows viewing three faces of the object simultaneously (front, side, and top views), providing a more complete perception of the object's design and structure.

- No Perspective: Unlike perspective projection, where lines converge towards a vanishing point, isometric projection has no vanishing points and does not simulate the decrease in object size with distance.

## Allowed Functions
| Function | Description |
| ------- | ----------- |
| open | Opens a file in the file system and returns a file descriptor used to perform subsequent operations on the file. |
| close | Closes a file descriptor previously opened with open, releasing any associated resources. |
| read | Reads data from a file referenced by a file descriptor and stores it in a buffer. |
| write | Writes data from a buffer to a file referenced by a file descriptor. |
| malloc | Reserves a block of dynamic memory in the heap of the specified size in bytes. |
| free | Frees a block of memory previously allocated by malloc or other dynamic memory allocation functions, allowing its reuse. |
| perror | Prints an error message to stderr based on the last error that occurred, followed by a description of the error associated with the global errno code. |
| strerror | Returns a character string representing the description of a given error code. |
| exit | Terminates program execution in an orderly manner, performing proper cleanup and returning an exit status to the operating system. |

- All functions from the math library (-lm compiler option, man 3 math)
- All functions from the MiniLibX library
- ft_printf and any function that YOU have programmed

## Restrictions
- You must use MiniLibX
- Global variables are prohibited.
- Maps will be passed as the only argument through .fdf files
- Your program must not crash when executed.
- Your program must display the image in a window.
- Window management must remain smooth (changing windows, minimizing, etc).
- Pressing ESC must close the window and terminate the program cleanly.
- Clicking the x on the window frame must close the window and terminate the program cleanly.
- Using MiniLibX images is mandatory.

## Key Concepts
One of the problems when starting this project is not knowing where to start or what to look for. Here are some concepts to research:
- Wireframe
- Isometric projection
- Line segments
- Bresenham line algorithm
- Linear interpolation
- Parallax
- Projection matrix
- Render and rasterize

### Wireframe
    A wireframe is a simplified visual representation of a three-dimensional object using lines and edges that connect the vertices. It is used to show the basic structure of the model without surface details such as textures or shadows. It is a common technique in 3D design and modeling to quickly conceptualize and review the geometry of an object.

### Isometric Projection
    Isometric projection is a method of three-dimensional graphical representation in which the three axes of space (x, y, z) are shown with equal angles of 120 degrees between them. This allows the dimensions of the axes to be maintained in equal proportions, providing a clear and balanced view of objects without perspective distortion. It is frequently used in technical drawings and isometric video games.

### Line Segments
    A line segment is a finite portion of a straight line delimited by two endpoints. Unlike an infinite line, a line segment has a defined length and is used to connect points in graphics and computational geometry.

### Bresenham Line Algorithm
    The Bresenham algorithm is an efficient method for drawing straight lines on a pixel grid. It uses integer calculations to determine which pixels should be activated to represent the line, avoiding floating-point operations. It is widely used in computer graphics for its precision and speed.

### Linear Interpolation
    Linear interpolation is a method for estimating values within an interval between two known points by assuming that the change between the points is linear. It is used in graphics to smooth transitions and calculate intermediate values.

### Parallax
    Parallax is the difference in the apparent position of an object seen from two different viewpoints. In graphics and photography, it is used to create a sense of depth by simulating how closer objects appear to move faster than distant objects.

### Projection Matrix
    A projection matrix is a mathematical tool used to transform coordinates from 3D space to 2D space, such as a computer screen. It defines how 3D objects will be mapped to the 2D view, affecting the perspective and scale of rendered objects.

### Render
	Rendering is the process of generating a final image from a 3D model or scene defined in a computer. It involves calculating lights, textures, shadows, and other visual effects to create a detailed visual representation.

### Rasterize
	Rasterizing is the process of converting a vector image or scene (based on geometry) into a grid of pixels (raster image). It is a key stage in graphic rendering, where graphic primitives are transformed into pixels that can be displayed on a screen.

## FDF Map
Each number represents a point in space:
- The horizontal position corresponds to its X axis.
- The vertical position corresponds to its Y axis.
- The value corresponds to its altitude, Z axis.

## BONUS

![MAP](../../assets/fdf/map1.png)

You will get extra points if you add:
- An extra projection (such as parallel or conical)
- Zoom in and out.
- Translate your model.
- Rotate your model.
- Add one more bonus of your choice.

![MENU](../../assets/fdf/menu.png)

## Main Algorithms for Generating Lines
### 1. Bresenham Algorithm

The Bresenham algorithm is a classic method for drawing lines on a pixel grid. It uses only integer arithmetic operations, making it very efficient.

Advantages:

- Efficiency: Uses addition and subtraction operations, avoiding the use of multiplications or divisions, making it fast and suitable for limited hardware.

- Precision: Generates lines with contiguous pixels without jumps, ensuring an accurate and continuous representation of the line.

- Simplicity: Easy to implement and understand, ideal for real-time applications.

Disadvantages:

- No Anti-aliasing: Does not handle anti-aliasing, so lines may appear with irregular and rough edges.

- Color Limitations: Can only produce solid color lines, without gradients.

### Implementation Example:

``` c
void drawLineBresenham(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x0, y0); // Function to set pixel color

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

### 2. Xiaolin Wu Algorithm

The Xiaolin Wu algorithm is an anti-aliasing line generation method that produces smoother lines by applying color smoothing techniques.

Advantages:

- Anti-aliasing: Smooths line edges, reducing the stair-step effect (aliasing).

- Visual Quality: Produces visually attractive lines, especially useful in high-resolution graphics.

Disadvantages:

- Computational Complexity: More complex and slower than Bresenham due to floating-point operations and color blending.

- Requires Color Buffer: Requires access to a color buffer that allows color blending, which can be costly in resource-limited systems.

### Implementation Example:

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

### 3. DDA Algorithm (Digital Differential Analyzer)

The DDA algorithm is another method for generating lines based on incremental interpolation of points between the two ends of the line.

Advantages:

- Ease of Implementation: Simple to implement and understand, suitable for simple applications.

- Acceptable Quality: Produces reasonably straight and continuous lines in many situations.

Disadvantages:

- Performance: Uses floating-point operations, which can be slower and less efficient than the Bresenham algorithm.

- No Anti-aliasing: Similar to Bresenham, does not apply smoothing to lines.

### Implementation Example:

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
        setPixel(round(x), round(y)); // Function to set pixel color
        x += xIncrement;
        y += yIncrement;
    }
}
```

### 4. Gupta-Sproull Algorithm

The Gupta-Sproull algorithm is a variant of the Bresenham algorithm that includes anti-aliasing to improve the visual quality of lines.

Advantages:

- Enhanced Anti-aliasing: Produces smooth and visually pleasing lines by applying smoothing techniques.

- Superior Quality: Suitable for graphic applications where visual quality is critical.

Disadvantages:

- Complexity: More complex to implement than algorithms without smoothing.

- Computational Cost: Requires more computational resources due to smoothing and additional calculations.

### Implementation Example:

```c
void drawLineGuptaSproull(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int D = 2 * dy - dx;
    int y = y0;
    int thickness = 1; // Line thickness

    for (int x = x0; x <= x1; x++) {
        for (int i = -thickness; i <= thickness; i++) {
            setPixel(x, y + i); // Function to set pixel color
        }
        if (D > 0) {
            y++;
            D = D - 2 * dx;
        }
        D = D + 2 * dy;
    }
}
```

### 5. Bresenham Algorithm with Anti-aliasing

This algorithm is a modification of the Bresenham algorithm that includes anti-aliasing to improve line smoothness.

Advantages:

- Efficiency with Smoothing: Combines Bresenham's efficiency with the ability to smooth line edges.

- Good Visual Quality: Ideal for graphics where smoothness is important but performance remains a priority.

Disadvantages:

- Additional Complexity: More complicated than the original Bresenham.

- Requires Additional Calculations: Uses intensity calculations to smooth lines, which can affect performance in limited systems.

### Implementation Example:

```c
void drawLineBresenhamAA(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x0, y0); // Function to set pixel color
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

### Summary Comparison

| Algorithm | Advantages | Disadvantages |
| --------- | -------- | -------------- |
| Bresenham | Efficient, precise, simple | No anti-aliasing, solid lines |
| Xiaolin Wu | Anti-aliasing, high visual quality | Computational complexity, requires color buffer |
| DDA | Easy to implement, acceptable quality | Lower performance, no anti-aliasing |
| Gupta-Sproull | Enhanced smoothing, superior quality | Complexity, computational cost |
| Bresenham with AA | Efficient with smoothing, good visual quality | Additional complexity, requires additional calculations |

## [Manipulating the 3D Map](Transformaciones_geometricas_3D.pdf)

Manipulating 3D coordinates through transformations such as rotation, translation, and zoom is fundamental in computer graphics, 3D modeling, and virtual reality applications. These transformations can be represented mathematically using matrices, which facilitates their application to sets of 3D coordinates. Below is the mathematical concept of each transformation and how it is represented using matrices.

### 1. Rotation

Rotation in 3D involves rotating a set of points around one or more of the main axes of three-dimensional space: the X-axis, Y-axis, and Z-axis. Each rotation is represented by a transformation matrix that, when multiplied by the coordinate vector, performs the desired rotation.

>Rotation around the X-axis

The rotation matrix for rotating an `angle θ` around the X-axis is:

$Rx(θ)=\begin{bmatrix}
1&0&0&0\\
0&cos⁡(θ)&−sin⁡(θ)&0\\
0&sin⁡(θ)&cos⁡(θ)&0&\\
0&0&0&1
\end{bmatrix}$

>Rotation around the Y-axis

The rotation matrix for rotating an `angle θ` around the Y-axis is:

$Rx​(θ)=\begin{bmatrix}
cos⁡(θ)&0&sin⁡(θ)&0​\\
0&1&0&0​\\
−sin⁡(θ)&0&cos⁡(θ)&0​\\
0&0&0&1​\\
\end{bmatrix}$

>Rotation around the Z-axis

The rotation matrix for rotating an `angle θ` around the Z-axis is:

$Rx​(θ)=\begin{bmatrix}
cos⁡(θ)&−sin⁡(θ)&0&0​\\
sin⁡(θ)&cos⁡(θ)&0&0​\\
0&0&1&0​\\
0&0&0&1​\\
\end{bmatrix}$

>Combination of Rotations

Rotations in the three axes can be combined by multiplying the individual rotation matrices. The multiplication order is important since rotations are not commutative.

$$
R=Rx(α)⋅Ry(β)⋅Rz(γ)
$$


where αα, ββ, and γγ are the rotation angles around the X, Y, and Z axes respectively.

__Rotation Example__

If you have a point `P=(x,y,z)` and want to rotate it `θ degrees` around the Z-axis, the new point `P′` will be:

$P′=Rz(θ)⋅
\begin{bmatrix}
x\\y\\z\\1
\end{bmatrix}$

### 2. Translation

Translation in 3D involves moving a set of points in three-dimensional space by a given distance in the directions of the X, Y, and Z axes. This transformation is also represented with a matrix.

>Translation Matrix

To translate a point in 3D by `tx`​ units on the X-axis, `ty`​ units on the Y-axis and `tz`​ units on the Z-axis, the following matrix is used:

$T(tx,ty,tz)=
\begin{bmatrix}
1&0&0&tx\\
0&1&0&ty\\
0&0&1&tz\\
0&0&0&1
\end{bmatrix}$
>Applying Translation

Given a point `P=(x,y,z)`, the new position `P′` after translation is:

$P′=T(tx,ty,tz)⋅
\begin{bmatrix}
x\\y\\z\\1
\end{bmatrix}=
\begin{bmatrix}
x+tx\\y+ty\\z+tz\\1
\end{bmatrix}$

### 3. Zoom (Scaling)

Scaling, or "zoom", in 3D refers to changing the size of an object in one or more directions. This is done by multiplying the object's coordinates by a scale factor.
Scaling Matrix

To scale a point in 3D by a factor `sx`​ on the X-axis, `sy`​ on the Y-axis, and `sz`​ on the Z-axis, the scaling matrix is:

$S(sx,sy,sz)=
\begin{bmatrix}
sx&0&0&0\\
0&sy&0&0\\
0&0&sz&0\\
0&0&0&1
\end{bmatrix}$

__Applying Scaling__

Given a point `P=(x,y,z)`, the new position `P′` after scaling is:

$P′=S(sx,sy,sz)⋅
\begin{bmatrix}
x\\y\\z\\1
\end{bmatrix}=
\begin{bmatrix}
sx⋅x\\sy⋅y\\sz⋅z\\1
\end{bmatrix}$

>Uniform Zoom

If the zoom is uniform in all directions (i.e., sx = sy = sz = s), the scaling becomes:

$S(s)=
\begin{bmatrix}
s&0&0&0\\
0&s&0&0\\
0&0&s&0\\
0&0&0&1
\end{bmatrix}$
​
This enlarges or reduces the object proportionally in all dimensions.

	3D transformations are powerful tools that allow effective manipulation of objects and scenes. The use of transformation matrices not only simplifies the application of these transformations but also provides a robust mathematical framework for complex graphic operations. With a clear understanding of rotation, translation, and zoom in 3D, impressive and realistic visual effects can be created in computer graphics applications.


### Tips
>Control that you don't have memory leaks

``` bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fdf_bonus maps/42.fdf
```
>Depending on the library you use, it may contain leaks that you cannot control, and of course it will not pass norminette. You can include these libraries once they have passed norminette in the evaluation or run norminette on each of your folders.

### Resources
- [Some key codes](https://anzeljg.github.io/rin2/book2/2405/docs/tkinter/key-names.html)
- [Help with minilibx](https://harm-smits.github.io/42docs/libs/minilibx)
- [MLX42](https://github.com/codam-coding-college/MLX42/blob/master/include/MLX42/MLX42.h)
- [Projection](https://docs.hektorprofe.net/graficos-3d/17-matriz-de-proyeccion/)
- [Wikipedia](https://en.wikipedia.org/wiki/Wire-frame_model)
- [Color tool](https://rgbcolorcode.com/color/008000)
- [Color tool](https://www.rgbtohex.net/)

[$${\color{red}BACK$$}$$](../../README.md)
```
