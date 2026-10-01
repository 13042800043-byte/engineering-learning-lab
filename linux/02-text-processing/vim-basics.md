# Vim 模式与基本编辑

> 首次学习日期：2026-10-01
>
> 状态：观看课程，计划在 WSL Ubuntu 中亲手操作；本次尚未完成实操。

## 本次学习与已确认的理解

- 观看课程，学习了 Normal、Insert、Visual 模式，以及进入 Vim 命令行模式的方法。
- 接触了 Normal 模式下的光标跳转，以及 `j`、`v`、`V` 等按键的用法。
- 学习了 Normal 模式下的 `o`：在当前行下方创建新行。
- 能够解释：按 `o` 后已经进入 Insert 模式，因此再按 `j` 会输入字母，而不是向下移动。
- 下一步想在之前搭建的 WSL Ubuntu 环境中亲手操作。

本次没有文件编辑结果或运行结果可记录。下面是代理补充的解释与建议练习，不代表已经掌握或完成。

## 补充解释：先确认模式，再判断按键含义

| 模式 | 主要作用 | 进入方式 | 返回 Normal |
|---|---|---|---|
| Normal | 移动光标、复制、删除等 | 启动 Vim 后通常处于此模式 | — |
| Insert | 输入文字 | `i`、`a`、`o`、`O` | `Esc` |
| Visual | 选择文字，再执行操作 | `v` 按字符选择；`V` 按整行选择 | `Esc` |
| 命令行模式 | 保存、退出、搜索等 | Normal 下按 `:`、`/`、`?` | `Esc` 取消；Enter 执行 |

`j` 在 Normal 中向下移动，在 Insert 中输入字母，在 Visual 中移动选区的活动端点。`j` 本身不是进入 Visual 模式的按键。

Normal 下的 `o` 在当前行下方新建一行并进入 Insert；大写 `O` 在上方新建一行并进入 Insert。大小写不同，操作也不同。[Vim 插入命令参考](https://vimhelp.org/insert.txt.html#o)

Vim 的命令行模式属于编辑器内部。例如 `:w` 保存当前缓冲区到文件；它不是 Ubuntu Shell。

## 补充解释：行首、缩进与跳转

| 按键（Normal 模式） | 作用 |
|---|---|
| `h`、`j`、`k`、`l` | 左、下、上、右 |
| `0` | 移动到本行第一个字符，包括开头的空白 |
| `^` | 移动到本行第一个非空白字符 |
| `$` | 移动到行尾 |
| `w`、`b` | 向后／向前移动到词开头 |
| `gg`、`G` | 移动到文件第一行／最后一行 |
| `5j`、`10G` | 向下移动 5 行／跳到第 10 行 |

例如下面一行开头有四个空格：

```cpp
    return 0;
```

在 Normal 模式中，`0` 停在第一个空格上，`^` 停在字母 `r` 上。编辑带缩进的 C++ 代码时，`^` 可以直接跳过缩进。[Vim 光标移动参考](https://vimhelp.org/motion.txt.html#left-right-motions)

## 补充解释：先选择，再复制

要复制当前行和下面两行，依次按 `Vjjy`（共三行，并假设下面至少还有两行）：

1. `V`：进入整行 Visual 模式，当前行已经被选中。
2. `j`：将选区延伸到下一行，共两行。
3. 再按 `j`：选中第三行。
4. `y`：复制选区并返回 Normal。

然后在 Normal 中按 `p`，将复制的整行内容放到当前行下方。Visual 模式里应先完成范围选择，再按 `y`；第一次 `y` 已经完成复制并退出 Visual，因此 `vyy` 后再按向下键不会继续扩展原来的选区。[Vim Visual 模式参考](https://vimhelp.org/visual.txt.html)

还可以直接在 Normal 模式中按 `3yy` 复制三行。它体现了“次数 + 操作”的组合方式，而 `Vjjy` 可以让人先看到选区。

其他补充操作：`yy` 复制当前行；`dd` 删除当前行；`ciw` 修改光标所在的词并进入 Insert；Normal 下 `u` 撤销，`Ctrl+r` 重做。这些操作尚未由用户实践确认。

## 建议练习（尚未执行）

在 Ubuntu Shell 中创建一个专用练习文件：

```bash
mkdir -p ~/projects/vim-practice
cd ~/projects/vim-practice
vim practice.txt
```

按 `i`，亲手输入以下三行，第一行开头保留四个空格：

```text
    alpha beta gamma
Linux is useful
Vim is interesting
```

随后按 `Esc`，依次练习：

1. 按 `gg`，比较 `0` 与 `^` 的光标位置。
2. 按 `o` 后输入 `j`，观察新行位置和实际插入的字符；按 `Esc` 后再按 `j`，比较区别。
3. 在 Normal 下用 `u` 撤销新增一行的修改，确认文件恢复为原来三行。
4. 按 `gg`，依次按 `Vjjy`，观察三行选区；再按 `G`、`p`，检查是否出现完整的三行副本。
5. 在 Normal 下按 `u` 撤销粘贴，再按 `Ctrl+r` 重做。
6. 输入 `:wq` 并回车，保存退出；在 Shell 中用 `cat practice.txt` 查看保存的内容。

练习后再记录：执行了哪些按键、看到了什么、是否有操作与预期不同。上述内容是预期检查点，当前没有实测结果。

## 编辑器内查帮助

在 Vim 的 Normal 模式中，可以输入 `:help o`、`:help ^`、`:help visual-mode` 并回车查阅帮助。使用 `:q` 关闭帮助窗口。

也可以在 Ubuntu Shell 中运行 `vimtutor` 进行交互练习。[Vim 入门手册](https://vimhelp.org/usr_02.txt.html)
