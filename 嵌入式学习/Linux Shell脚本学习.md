# Linux Shell脚本学习

## 一、基础入门

### 1.1 脚本结构
```bash
#!/bin/bash
# 这是一个注释

echo "Hello, World!"
```

**解释：**
- `#!/bin/bash`：指定脚本解释器（shebang）
- `#`：单行注释
- `echo`：输出命令

### 1.2 执行方式
```bash
# 方式1：赋予执行权限后直接运行
chmod +x script.sh
./script.sh

# 方式2：指定解释器运行
bash script.sh
```

---

## 二、变量与数据类型

### 2.1 变量定义
```bash
# 定义变量（等号两边无空格）
name="John"
age=25

# 使用变量
echo "姓名: $name"
echo "年龄: ${age}岁"  # 花括号可选，但推荐使用

# 只读变量
readonly PI=3.14159

# 删除变量
unset name
```

### 2.2 环境变量
```bash
# 查看环境变量
echo $PATH
echo $HOME

# 设置环境变量（临时生效）
export MY_VAR="hello"

# 设置环境变量（永久生效）
echo 'export MY_VAR="hello"' >> ~/.bashrc
source ~/.bashrc
```

### 2.3 特殊变量
| 变量 | 含义 |
|------|------|
| `$0` | 脚本名称 |
| `$1-$9` | 位置参数 |
| `$@` | 所有位置参数（作为独立字符串） |
| `$*` | 所有位置参数（作为单个字符串） |
| `$#` | 位置参数个数 |
| `$?` | 上一条命令的退出状态 |
| `$$` | 当前进程ID |

---

## 三、条件判断

### 3.1 if语句
```bash
if [ $age -ge 18 ]; then
    echo "成年人"
elif [ $age -ge 12 ]; then
    echo "青少年"
else
    echo "儿童"
fi
```

### 3.2 常用判断条件
| 条件 | 说明 |
|------|------|
| `-eq` | 等于 |
| `-ne` | 不等于 |
| `-gt` | 大于 |
| `-lt` | 小于 |
| `-ge` | 大于等于 |
| `-le` | 小于等于 |
| `-z` | 字符串为空 |
| `-n` | 字符串非空 |
| `-f` | 文件存在且为普通文件 |
| `-d` | 文件存在且为目录 |
| `-x` | 文件可执行 |

### 3.3 case语句
```bash
case $choice in
    1)
        echo "选项1"
        ;;
    2)
        echo "选项2"
        ;;
    *)
        echo "无效选项"
        ;;
esac
```

---

## 四、循环结构

### 4.1 for循环
```bash
# 遍历列表
for fruit in apple banana cherry; do
    echo "水果: $fruit"
done

# 数值循环
for i in {1..5}; do
    echo "数字: $i"
done

# C风格循环
for ((i=0; i<5; i++)); do
    echo "i = $i"
done
```

### 4.2 while循环
```bash
count=0
while [ $count -lt 5 ]; do
    echo "计数: $count"
    count=$((count + 1))
done
```

### 4.3 until循环
```bash
count=0
until [ $count -ge 5 ]; do
    echo "计数: $count"
    count=$((count + 1))
done
```

---

## 五、函数

### 5.1 函数定义与调用
```bash
# 定义函数
my_function() {
    echo "参数1: $1"
    echo "参数2: $2"
    return 0  # 返回值
}

# 调用函数
my_function hello world

# 获取返回值
echo "返回值: $?"
```

### 5.2 函数示例
```bash
# 计算两个数之和
sum() {
    result=$(( $1 + $2 ))
    echo "结果: $result"
}

sum 10 20  # 输出: 结果: 30
```

---

## 六、常用命令

### 6.1 文件操作
```bash
# 创建目录
mkdir -p dir1/dir2

# 复制文件
cp source.txt dest/

# 移动文件
mv old.txt new.txt

# 删除文件
rm -rf temp/

# 查看文件内容
cat file.txt
head -n 10 file.txt
tail -f log.txt
```

### 6.2 文本处理
```bash
# 查找字符串
grep "pattern" file.txt

# 替换字符串
sed 's/old/new/g' file.txt

# 按列切分
cut -d',' -f1,3 data.csv

# 排序
sort -n numbers.txt

# 去重
uniq sorted.txt
```

### 6.3 管道与重定向
```bash
# 管道：将前一个命令的输出作为后一个命令的输入
ls -l | grep ".txt" | wc -l

# 输出重定向
echo "内容" > output.txt    # 覆盖
echo "追加" >> output.txt   # 追加

# 错误重定向
command 2> error.log

# 同时重定向标准输出和错误
command > output.log 2>&1
```

---

## 七、实战案例

### 7.1 备份脚本
```bash
#!/bin/bash

# 备份目录
src_dir="/home/user/data"
dst_dir="/backup"
date=$(date +%Y%m%d_%H%M%S)

# 创建备份目录
mkdir -p $dst_dir

# 压缩备份
tar -czf ${dst_dir}/backup_${date}.tar.gz $src_dir

if [ $? -eq 0 ]; then
    echo "备份成功"
else
    echo "备份失败"
    exit 1
fi
```

### 7.2 文件批量重命名
```bash
#!/bin/bash

# 将所有.txt文件重命名为.bak
for file in *.txt; do
    mv "$file" "${file%.txt}.bak"
done
```

### 7.3 系统监控脚本
```bash
#!/bin/bash

echo "=== 系统信息 ==="
echo "主机名: $(hostname)"
echo "系统版本: $(cat /etc/issue)"
echo "CPU核心数: $(nproc)"
echo "内存使用: $(free -h | grep Mem | awk '{print $3"/"$2}')"
echo "磁盘使用: $(df -h / | grep / | awk '{print $5}')"
```

---

## 八、高级技巧

### 8.1 数组
```bash
# 定义数组
fruits=(apple banana cherry date)

# 访问元素
echo ${fruits[0]}    # apple
echo ${fruits[@]}    # 所有元素
echo ${#fruits[@]}   # 数组长度

# 遍历数组
for fruit in "${fruits[@]}"; do
    echo $fruit
done
```

### 8.2 命令替换
```bash
# 方式1：反引号
files=`ls`

# 方式2：$()（推荐）
date=$(date +%Y%m%d)
```

### 8.3 算术运算
```bash
# 方式1：$(( ))
result=$(( 10 + 5 * 2 ))

# 方式2：let
let result=10+5*2

# 方式3：expr
result=$(expr 10 + 5)
```

---

## 九、调试技巧

```bash
# 1. 添加-x参数启用调试模式
bash -x script.sh

# 2. 在脚本中添加set -x
set -x  # 启用调试
echo "调试中..."
set +x  # 禁用调试

# 3. 使用-n参数检查语法
bash -n script.sh

# 4. 使用-v参数显示脚本内容
bash -v script.sh

# 5. 使用-e参数遇到错误立即退出
set -e
```

---

## 十、注意事项

1. **空格敏感**：变量赋值时等号两边不能有空格
2. **引号区别**：
   - 双引号：允许变量替换
   - 单引号：原样输出
3. **特殊字符转义**：使用`\`转义特殊字符
4. **脚本权限**：确保脚本有执行权限
5. **路径问题**：使用绝对路径或正确设置PATH
6. **错误处理**：检查命令退出状态，使用`set -e`自动退出
7. **变量引用**：数组和特殊变量引用时使用花括号
8. **脚本头部**：始终添加shebang指定解释器