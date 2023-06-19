<p align="center">
    <img src="https://github.com/ygor-sena/42cursus-minishell/assets/102881479/fecbff37-09c8-4f18-b55d-c96cb423d34f">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/OS-Linux-blue" alt="OS">
    <img src="https://img.shields.io/badge/Language-C%20%7C%20C%2B%2B-blue.svg" alt="Language">
    <img src="https://img.shields.io/badge/Grade-125%2F100-brightgreen.svg" alt="Grade">
    <img src="https://img.shields.io/badge/Status-Completed-brightgreen.svg" alt="Status">
</p>

📣 Introduction
---------------

The 11th project of 42's curriculum is an introduction to the beautiful world of Raytracing and it asks students to render simple Computer-Generated-Images so that they will never be afraid of implementing mathematical formulas again. This project makes possible to create scenes such as the one below, an image of our beautiful pale blue bot called Earth.

🚨🚨 [The detailed Doxygen documentation of this project can be read here](https://ygor-sena.github.io/42cursus-miniRT/). 🚨🚨

![](https://github.com/ygor-sena/42cursus-miniRT/assets/102881479/402e660f-3ca7-4b66-a49a-fee296dc60cb)

⚒️ How to compile and run the project
-------------------------------------

#### 1) Copy this repository to your local workstation

```
git@github.com:ygor-sena/42cursus-miniRT.git
```

#### 2) Install the required libraries to run the project and the unit tests

```
sudo apt-get install libcriterion-dev libbsd-dev -y
```

#### 3) Compile the project with Makefile

```
make
```

#### 4) Launch the executable file with a configuration file of extension .rt

```
./miniRT configuration\_sample.rt
```

If you want to run the scenes we've used to defend the project, it's possible to use any file between `img00.rt` and `img19.rt` located inside the folder `images`. For example:

```
./miniRT images/img18.rt
```

⚙️ How to configure a `.rt` file to render an image
----------------------------------------------------

Every line will have an `<id>`, an `<object_type>` and one or more corresponding `<parameters>` to the given object type, in this order. The following table sums up how to build and render images and provides usage examples.

|ID|Object type|Parameter (arguments)|Usage example|
|:--|:--|:--|:--|
|`A`|Ambient lighting|Lighting ratio (0-1)| `1`|
|||RGB color (red, green, blue)(0-255)| `255,255,255`|
|`C`|Camera|Coordinates of the view point (x, y, z)|`0,15,-5`|
|||3D normalized orientation vector (x, y, z)(-1-1)| `1,0,0`|
|||Horizontal point of view in degrees (x, y, z)(0-180)| `10`
|`L`|Light source|Coordinates of the light point (x, y, z)|`0,0,5`|
|||Brightness ratio (0-1)| `0.5`|
|||RGB color (red, green, blue)(0-255)| `0,255,0`|
|`sp`|Sphere|Coordinates of the sphere center (x, y, z)|`0,0,0`|
|||The sphere diameter (greater than 0)|`2`|
|||RGB color (red, green, blue)(0-255)| `255,55,255`|
|`pl`|Plane|Coordinates of a point in the plane (x, y, z)|`0,0,0`|
|||3D normalized origin vector (x, y, z)(-1-1)|`0,1,0`|
|||RGB color (red, green, blue)(0-255)| `98,130,229`|
|`cy`|Cylinder|Coordinates of the center of the cylinder (x, y, z)|`1,3,1`|
|||3D normalized vector of axis of cylinder (x, y, z)(-1-1)| `0,1,0`|
|||The cylinder diameter (greater than 0)|`4`|
|||The cylinder height|`2`|
|||RGB color (red, green, blue)(0-255)| `40,220,55`|
|`cn`|Cone|Coordinates of the center of the cone (x, y, z)|`1,3,1`|
|||3D normalized vector of axis of cone (x, y, z)| `0,1,0`|
|||The cone diameter (greater than 0)|`4`|
|||The cone height|`2`|
|||RGB color (red, green, blue)(0-255)| `122,23,230`|

If the user wants to create a blue (`0,0,255`) light source (`L`) located at `-10,10-10` with maximum brightness (`1`), the configuration as follows:
```
L   -10,10,-10    1   0,0,255
```

<b>‼️Important notes:</b> after the mandatory parameters above, it's possible to pass some extra parameters to any given shape (sphere, cylinder, cone or plane) so that it can have a checkerboard pattern or a bumpmap applied to its surface. To assign a checkerboard pattern to a given shape, the extra parameters are:

|Pattern type| 1st color square | 2nd color square|
|:--|:--|:--|
|`checkered`|`0,0,0`|`255,255,255`|

For example, to render a sphere (`sp`) at origin position (`0,0,0`), with diameter value of `1` and a black-white checkerboard applied to its surface, the setting is:
```
sp   1.5,0.5,-0.5   1   255,255,255   checkered   0,0,0   255,255,255
```
Note that when a bumpmap or a pattern is applied, the fourth parameter (RGB value) is ignored. 

|Pattern type| Path to `.xpm` file|
|:--|:--|
|`bumpmap`|`textures/earth.xpm`|

For instance, to render a sphere with the same configurations and a bumpmap applied to its surface instead, the setting is:
```
sp   1.5,0.5,-0.5   1   255,255,255   bumpmap textures/earth.xpm
```

📜 Requirements
---------------

<details>
  <summary>This project has a lot of requeriments that needs to be stricly followed. To easily remember them all, we created a diagram that sums up both mandatory and bonus project features with the help of [Effie](https://www.effie.pro/), an amazing software for ideas annotation. To visualize the diagram, just click on this paragraph.</summary>

![miniRT](https://github.com/ygor-sena/42cursus-miniRT/assets/102881479/708fa7d4-f6fe-4272-9f14-d9b443ddcd80)
</details>

📈 About how we implemented the project
---------------------------------------

To develop this project, we closely followed the book [The Ray Tracer Challenge: a test-driven guide to your first 3D Renderer](http://raytracerchallenge.com/). The unit tests were created using [Criterion](https://github.com/Snaipe/Criterion), a dead-simple, yet extensible, C and C++ unit testing framework. Lastly, to generate an automated documentation we used Doxygen, which is the _de facto_ standard tool for generating documentation from annotated C sources and many other languages.

There are seven main folders at projects's root directory, they are:

*   `include`: contains all the necessary headers for the project
*   `images`: contains the scenes used to defend the project during the final evaluation
*   `lib`: stores our own C library with some helpful auxiliary functions, such as ft\_strlen. Thus, it contains miniLibX files, which is the X-window programming API in C used at School 42
*   `textures`: contains bump map files that can be applied to the surface of geometric shapes during renderization process
*   `tests`: contains unit tests created with [Criterion](https://github.com/Snaipe/Criterion) testing framework to evaluate functions in `src`
*   `documentation`: contains the Doxygen documentation of the project generated from header comments
*   `src`: contains the whole project implementation
    *   `camera`: contains all functions regarding camera implementation
    *   `canvas`: contains all functions that works directly or indirectly with graphic data and MLX's library manipulation
    *   `helpers`: contains utils function used on the project as a whole
    *   `lights`: stores all the necessary files to render a light source
    *   `materials`: stores all the necessary files to render a material that has a surface color, shininess and some other characteristics
    *   `matrices`: contains the files that are responsible for matrix calculations
    *   `parser`: consists of functions that implement an analyzer of .rt file extension and its syntax validation
    *   `patterns`: stores files that apply a striped pattern, a checkerboard pattern or a bumpmap texture on a given geometric shape
    *   `rays`: stores all the necessary files for ray calculations and intersections
    *   `shapes`: consists all files that stores and calculates every operation regarding the geometric shapes implemented in the project
    *   `tuples`: contains the files that are responsible for vector and point calculations
    *   `world`: contains everything related to the building of a ray tracing's world. The world has objects (or shapes), point lights and an ambient color. Together, these elements makes the scene rendering possible

🚀 Optimizations
----------------

The program underwent several optimizations to improve performance and efficiency. Two of these optimizations include:

### Memory Pool for Intersection Storage

#### Problem

Previously, the linked list of ray intersections with objects was dynamically allocated using `malloc` and freed with `free` when no longer needed. This approach resulted in repeated system calls, negatively impacting the program's performance.

#### Solution

To avoid the repeated calls to `malloc` and `free`, we implemented a memory pool. The memory pool consists of a pre-allocated block of memory used to store the nodes of the linked list. When a new list of intersections needs to be stored, the corresponding nodes are obtained from the memory pool, eliminating the need for additional memory allocation.

#### Result

This optimization significantly reduced the time spent on memory allocation and deallocation. In a test using a standard image containing a sphere, ambient light, and a focal point light, the intersection recording was called an average of 149,000 times. Prior to the optimization, each call resulted in a `malloc` and `free` call for each node, negatively impacting the program's performance. With the implementation of the memory pool, the `malloc` and `free` calls were eliminated, resulting in a significant performance improvement.

### Matrix Cache for Object Transformations

#### Problem

Matrix operations, such as inverse and transpose calculations, accounted for a significant portion of the program's execution time, consuming approximately 40% of the total time. This resulted in a high performance cost, especially considering that the object transformation matrices remain constant during the rendering of static images.

#### Solution

To optimize performance, we implemented a matrix cache. When assigning a transformation matrix to an object, we immediately perform the necessary calculations, such as matrix inverse and transpose, and store the results in the cache. This eliminates the need to recalculate these matrices repeatedly during the rendering process.

#### Result

With the implementation of the matrix cache, the time spent on matrix calculations was significantly reduced. The calculations are now performed only once, and the results are stored in the cache, improving the efficiency of object transformation calculations. This optimization contributed to an overall improvement in program performance, especially in scenes with multiple transformations.

📖 References:
--------------

*   General references:
    *   [BUCK, Jamis. The Ray Tracer Challenge: a test-driven guide to your first 3D Renderer](http://raytracerchallenge.com/).
    *   [BUCK, Jamis. Bonus chapter: Texture Mapping](http://raytracerchallenge.com/bonus/texture-mapping.html).
    *   Forum discussion of the book above: both the [the new forum on DevTalk](https://devtalk.com/books/the-ray-tracer-challenge) and the [old one](https://forum.raytracerchallenge.com/).
*   References that complement mathematical background presented by the aforementioned book:
    *   The wonderful free educational site [Scratchapixel](https://www.scratchapixel.com/index.html).
    *   [The Ray Tracer Challenge in Rust](https://www.youtube.com/watch?v=xGEDQXBMdV4&list=PLy68GuC77sUTyOUvDhVboQoOlHoa4XrSO) by [MrJacob](https://www.youtube.com/@MrJakob).
*   Other interesting references:
    *   About bump mapping: [Interactive Graphics 19 - Bump, Normal, Displacement, and Parallax Mapping](https://www.youtube.com/watch?v=cM7RjEtZGHw) by Professor [Cem Yuksel](https://www.youtube.com/@cem_yuksel) from School of Computing, University of Utah.
    *   About miniLibX: [My unnoficial documentation of 42's miniLibX](https://github.com/andreyvdl/MiniLibX_my_docs) by [andreyvdl](https://github.com/andreyvdl).
    *   [miniRT: stack vs. heap](https://private-tungsten-357.notion.site/miniRT-stack-vs-heap-eaab52ce792047b5b71e2fcb59074ffb) by [Matheus Oliveira](https://github.com/araggohnxd).
    *   [The Ray Tracer Challenge (traduced to Brazilian Portuguese)](https://github.com/marceFrasson/The-Ray-Tracer-Challenge-Pt/blob/main/Jamis%20Buck%20-%20The%20Ray%20Tracer%20Challenge%20Traduzido.pdf) by [Marce Frasson](https://github.com/marceFrasson).
*   Important specific references:
    *   [The Phong Model, Introduction to the Concepts of Shader, Reflection Models and BRDF](https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF/phong-illumination-models-brdf.html) by [Scratchapixel](https://www.scratchapixel.com/index.html).
    *   Jamis Buck's book various errata: [The Ray Tracer Challenge: various errata](https://forum.devtalk.com/t/the-ray-tracer-challenge-various-errata/3554) in [DevTalk](https://devtalk.com/books/the-ray-tracer-challenge).
*   Doxygen references:
    *   [Doxygen Official Documentation](https://www.doxygen.nl/manual/starting.html) by Doxygen.
    *   [Complete Guide On Using Doxygen To Document C Source Code](https://embeddedinventor.com/guide-to-configure-doxygen-to-document-c-source-code-for-beginners/) by Balaji Gunasekaran.
    *   [Document your source code with Doxygen on Linux](https://opensource.com/article/22/5/document-source-code-doxygen-linux) by Stephan Avenwedde.
*   Other miniRT done by fellow students at 42 São Paulo:
    *   [miniRT](https://github.com/rodrigo-br/miniRT_42) by [rodrigo-br](https://github.com/rodrigo-br) and [araggonhnxd](https://github.com/araggohnxd).
    *   [miniRT](https://github.com/appinha/42cursus-02-miniRT) by [appinha](https://github.com/appinha).

🫂 Acknowledgements
-------------------

Thanks to [Larissa Silva](https://github.com/leaozim), [Rodrigo Alves](https://github.com/rodrigo-br) and [Matheus Oliveira](https://github.com/araggohnxd) for being so helpful when we needed it. Last but not least, a huge thanks to [Jamis Buck](https://github.com/jamis), who wrote the amazing book [The Ray Tracer Challenge](http://raytracerchallenge.com/) and made the development of this project joyful.
