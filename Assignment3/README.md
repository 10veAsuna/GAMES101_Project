# GAMES101 Assignment 3 - Pipeline and Shading

本仓库按提交历史记录 GAMES101 的学习过程。当前工作区已经切换到作业 3 框架，并使用 MSYS2 MinGW64、OpenCV 与 Eigen 配置完成。

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

作业 3 从 `build` 目录运行，因为模型路径相对于该目录：

```bash
cd build
./Rasterizer.exe ../output.png normal
```

第三个参数可选：`normal`、`phong`、`texture`、`bump` 或 `displacement`。

当前提交只完成环境和代码框架配置，作业 TODO 仍保留，尚未实现最终渲染结果。

## 待完成内容

1. 将前两次作业的投影矩阵移植到 `get_projection_matrix`。
2. 在 `rasterize_triangle` 中完成包围盒、覆盖判断、深度测试，并插值颜色、法线、纹理坐标和观察空间位置。
3. 实现 Blinn-Phong 光照模型。
4. 实现纹理映射。
5. 实现凹凸贴图与位移贴图。
6. 可选提高项：更多模型与双线性纹理插值。

## 文件说明

- `main.cpp`：变换矩阵、各类 Fragment Shader 与程序入口。
- `rasterizer.hpp/.cpp`：渲染管线、属性插值、颜色缓冲与深度缓冲。
- `Shader.hpp`：Vertex/Fragment Shader 的 payload 数据结构。
- `Texture.hpp/.cpp`：纹理读取和采样。
- `OBJ_Loader.h`：第三方 OBJ 模型加载器。
- `Triangle.hpp/.cpp`：三角形顶点、颜色、法线和纹理坐标。
- `models/`：作业提供的模型与纹理资源。
- `CMakeLists.txt`：CMake 构建配置。

`build/` 和根目录下生成的 `output*.png` 属于本地构建产物，已由 `.gitignore` 排除；模型目录中的纹理图片会正常提交。
