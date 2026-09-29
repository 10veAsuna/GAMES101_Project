# GAMES101 Assignment 6 - BVH Acceleration

This assignment adds Bounding Volume Hierarchy (BVH) acceleration to the ray tracer from the previous assignments.

## Completed work

- Generated one normalized primary ray for every pixel in `Renderer::Render` and used `Scene::castRay` to obtain its color.
- Completed `Triangle::getIntersection` with Moller-Trumbore ray-triangle intersection data.
- Implemented `Bounds3::IntersectP` with the slab method for ray-AABB intersection.
- Implemented recursive BVH traversal in `BVHAccel::getIntersection`, returning the nearest valid hit.

## Build and run

Run the following commands in an MSYS2 MinGW64 terminal from this directory:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\build\RayTracing.exe
```

The renderer writes `build/binary.ppm`. The displayed result was rendered at 1280 x 960 and shows the bunny model.

## Result

![Rendered bunny](images/result.png)
