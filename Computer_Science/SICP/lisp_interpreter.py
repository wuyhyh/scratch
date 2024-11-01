import math
import operator as op


# 定义全局环境，包含基本的算术和数学函数
def standard_env():
    env = {}
    env.update(vars(math))  # 导入 math 模块的所有函数
    env.update({
        '+': op.add,
        '-': op.sub,
        '*': op.mul,
        '/': op.truediv,
        'abs': abs,
        'max': max,
        'min': min,
        '>': op.gt,
        '<': op.lt,
        '>=': op.ge,
        '<=': op.le,
        '=': op.eq,
        'pi': math.pi,
        'round': round,
    })
    return env


# 解析输入的 Lisp 程序
def parse(program):
    return read_from_tokens(tokenize(program))


def tokenize(chars):
    return chars.replace('(', ' ( ').replace(')', ' ) ').split()


def read_from_tokens(tokens):
    if len(tokens) == 0:
        raise SyntaxError('意外的 EOF')
    token = tokens.pop(0)
    if token == '(':
        L = []
        while tokens[0] != ')':
            L.append(read_from_tokens(tokens))
        tokens.pop(0)  # 移除 ')'
        return L
    elif token == ')':
        raise SyntaxError('意外的 )')
    else:
        return atom(token)


def atom(token):
    try:
        return int(token)
    except ValueError:
        try:
            return float(token)
        except ValueError:
            return token


# 求值
def eval(x, env):
    if isinstance(x, str):  # 变量引用
        return env[x]
    elif not isinstance(x, list):  # 常量
        return x
    elif x[0] == 'define':  # 定义变量
        (_, var, exp) = x
        env[var] = eval(exp, env)
    elif x[0] == 'if':  # 条件判断
        (_, test, conseq, alt) = x
        exp = (conseq if eval(test, env) else alt)
        return eval(exp, env)
    else:  # 函数调用
        proc = eval(x[0], env)
        args = [eval(arg, env) for arg in x[1:]]
        return proc(*args)


# REPL 循环
def repl():
    env = standard_env()
    while True:
        try:
            program = input('lisp> ')
            if program.lower() in ('exit', 'quit'):
                print("退出 Lisp 解释器。")
                break
            val = eval(parse(program), env)
            if val is not None:
                print(val)
        except Exception as e:
            print(f'错误: {e}')


if __name__ == '__main__':
    repl()
