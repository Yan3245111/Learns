# 一共5行，插入第二行，从第二行开始重新赋值

a = [[0, 0], [2, 2], [2, 2], [3, 3], [4, 4]]

cur_focus_row = 1
list_row_num = 5
a.insert(cur_focus_row, [6, 6])
list_row_num += 1
# print(a)

for i in range(cur_focus_row, list_row_num):
    print(i)
    a[i] = [i, i]

print(a)