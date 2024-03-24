import sys
import keyword


# print(keyword.kwlist)
# print(type(keyword.kwlist))


def print_keywords():  # 输出python的关键字
    for i in range(0, len(keyword.kwlist)):
        print(i + 1, " : ", keyword.kwlist[i])


if __name__ == '__main__':
    print("main")
    print(sys.version)
    print(sys.path)
    print_keywords()

    n = None
    print(n)
    for i in range(6):
        print(i)

    for i in range(10, 6, -1):
        print(i)
    print(type(range))

    print(5 / 2)
    print(5 // 2)  # round down
    print(-5 / 2)
    print(-5 // 2)
    print(int(-5 / 2))
    print(int(-5 // 2))
