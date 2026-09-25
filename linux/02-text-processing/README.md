# 文本搜索与处理命令

> 首次记录：2026-09-24
>
> 实操复盘：2026-09-25

## `grep`

`grep` 适合确定性的字符串或正则表达式搜索：

```bash
grep -rn -- "password" .
```

常见选项：

- `-r`：递归搜索目录；
- `-n`：显示行号；
- `-i`：忽略大小写；
- `-v`：输出不匹配的行；
- `-E`：使用扩展正则表达式；
- `-q`：不输出匹配内容，只使用退出状态表示结果。

在引导练习的数据中，使用 `grep -c` 统计包含 `ERROR` 的行，实际结果为 `3`。

## `sort`、`uniq` 与管道

```bash
grep "ERROR" app.log |
    cut -d' ' -f3 |
    sort |
    uniq -c |
    sort -nr
```

各步骤的作用：

1. `grep` 保留包含 `ERROR` 的行；
2. `cut` 提取第三列错误类型；
3. `sort` 排序，使相同内容相邻；
4. `uniq -c` 合并相邻重复行并计数；
5. `sort -nr` 按次数从大到小排序。

本次最初把 `sort` 理解为“合并同类”，把 `uniq` 理解为“分离不同项”。复盘后明确：`sort` 不会合并内容；`uniq` 只能识别相邻重复行。

## 当前状态

- 已实际得到 `ERROR` 行数为 `3`。
- 已知道这条管道统计的是第三列错误类型，而不是笼统的“模块”。
- `sort` 与 `uniq -c` 的先后关系仍需再次亲手解释和验证。

## 官方资料

- [GNU Grep Manual](https://www.gnu.org/software/grep/manual/grep.html)
- [GNU Coreutils Manual](https://www.gnu.org/software/coreutils/manual/coreutils.html)
