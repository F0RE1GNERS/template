Pandoc 生成 PDF 流程（以 Linux 为例）：

+ 确保 `algo.latex` 文件置于 `~/.pandoc/templates/` 下
+ 在项目目录下运行 `sh pandoc/gen.sh`

注：

+ 字体选择放在了 `gen.sh` 中，请根据需要自行替换
+ 封面放在了 `algo.latex` 中，可自行修改
+ 需要安装 `pandoc`, `latex`, `python` 相关依赖

