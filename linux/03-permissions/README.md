# 用户、权限与 `sudo`

> 首次记录：2026-09-24
>
> 学习检测：2026-09-25

## 权限字符串

```text
-  rwx  r-x  r--
│   │    │    └── 其他用户 other
│   │    └─────── 文件所属组 group
│   └──────────── 文件所有者 user
└──────────────── 文件类型
```

在学习检测中，已经能够正确解释：

```text
-rw-r-----
```

- 所有者：可读、可写、不可执行；
- 所属组：只读；
- 其他用户：没有权限。

## 数字权限

```text
r = 4
w = 2
x = 1
```

因此：

```text
7 = rwx
5 = r-x
4 = r--
1 = --x
```

学习检测中曾把 `chmod 751` 的最后一组理解为 `r--`，复盘后明确正确结果是：

```text
rwx r-x --x
```

同时明确：

```bash
chmod u+x file  # 给所有者增加执行权限
chmod u-x file  # 删除所有者的执行权限
```

目录的 `x` 表示可以进入或穿过目录，并不是“执行目录”。

## `sudo` 与重定向

`sudo` 用来根据系统安全策略，以另一个用户身份执行一条命令。它不会自动让当前 Shell 的所有操作都获得 root 权限。

```bash
sudo echo 1 > /root/test
```

这条命令可能失败，因为当前 Shell 会在启动命令前处理 `>`，并以当前用户身份尝试打开目标文件。可以让提权后的 `tee` 负责写入：

```bash
echo 1 | sudo tee /root/test
```

本次最初把这个现象理解为程序会优先执行 `>`，复盘后明确问题在于重定向由哪个 Shell 处理。

## 当前状态

- 已理解基础权限分组和 `u+x` 的含义。
- 数字权限的快速转换和目录权限仍需继续练习。
- 本次没有确认实际使用 `sudo` 修改系统文件。

## 官方资料

- [GNU Coreutils：文件权限](https://www.gnu.org/software/coreutils/manual/coreutils.html)
- [sudo Linux Manual Page](https://man7.org/linux/man-pages/man8/sudo.8.html)
