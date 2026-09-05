# GAMES101 Assignment 2 - Triangles and Z-buffering

本目录已使用 MSYS2 MinGW64、OpenCV 与 Eigen 配置完成，并保留作业 2 的原始 TODO，供后续自行实现。

## 环境

- 编译器：MSYS2 MinGW64 GCC
- 构建工具：CMake + MinGW Makefiles
- 依赖：OpenCV 5、Eigen 5

## 构建

请在 **MSYS2 MinGW64** 终端中进入本目录后执行：

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

## 运行

将渲染结果保存为 PNG：

```bash
./build/Rasterizer.exe output.png
```

当前框架仍包含未完成的作业代码，因此应先完成下面的任务再检查输出。

## 待完成内容

1. 在 `main.cpp` 中补入作业 1 的 `get_projection_matrix` 实现。
2. 在 `rasterizer.cpp` 中实现 `insideTriangle`。
3. 在 `rasterize_triangle` 中：计算包围盒、遍历像素、计算重心坐标与插值深度。
4. 使用 `depth_buf` 实现 Z-buffer 深度测试；只有更靠近相机的片元才能写入颜色。
5. 可选提高项：使用 2x2 super-sampling 实现抗锯齿。

## 文件说明

- `main.cpp`：场景数据、模型/观察/投影矩阵与程序入口。
- `rasterizer.hpp/.cpp`：光栅化、颜色缓冲与深度缓冲。
- `Triangle.hpp/.cpp`：三角形顶点与颜色数据结构。
- `global.hpp`：预留的全局定义头文件。
- `CMakeLists.txt`：CMake 构建配置。

`build/` 和生成的 PNG 属于本地构建产物，已由 `.gitignore` 排除。
