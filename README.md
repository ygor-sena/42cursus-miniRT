# 42-cursus-miniRT
The eleventh project of 42's curriculum is an introduction to the beautiful world of Raytracing and asks students to render simple Computer-Generated-Images so that they will never be afraid of implementing mathematical formulas again.

## 🚀 Optimizations

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
