# GAMES101 Assignment 5 - Ray Tracing

本作业实现了 Whitted-style 光线追踪器中缺失的主光线生成和光线-三角形求交。

## 完成内容

### 1. 主光线生成

在 `Renderer.cpp` 的 `Renderer::Render()` 中，对每个像素中心计算成像平面坐标：

- 横坐标根据图像宽度归一化到 `[-1, 1]`，并乘以视场缩放与宽高比；
- 纵坐标根据图像高度归一化，并翻转上下方向以匹配相机坐标系；
- 使用归一化后的 `(x, y, -1)` 构造主光线方向，再调用 `castRay()` 得到像素颜色。

### 2. 光线与三角形求交

在 `Triangle.hpp` 的 `rayTriangleIntersect()` 中实现 Möller-Trumbore 算法：

- 从 `v0` 构造两条三角形边；
- 通过行列式判断光线是否与三角形平面平行；
- 计算并检查重心坐标 `u`、`v`；
- 返回相机前方的最近交点距离 `tnear`。

## 构建与运行

在 MSYS2 MinGW64 终端中，于本目录执行：

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\build\RayTracing.exe
```

程序会生成 `binary.ppm`。该文件是二进制 PPM 图像，运行输出不纳入版本控制；可查看的结果图见下方。

## 结果

![光线追踪结果：两个球、棋盘地面与阴影](images/result.png)

结果包含两个球体、棋盘三角形地面以及投影，验证了主光线和 Möller-Trumbore 三角形求交均已生效。
