在Linux内核中，原子变量（atomic variable）是一种用于实现无锁同步的机制，确保对变量的操作是原子的，即操作不会被中断，避免竞态条件。Linux内核提供了一组操作函数，用于对原子变量进行各种原子操作。

### 关键结构和操作函数

#### 结构体

1. **原子变量结构体**：`atomic_t`

   ```c
   typedef struct {
       int counter;
   } atomic_t;
   ```

2. **64位原子变量结构体**（如果需要支持64位原子操作）：

   ```c
   typedef struct {
       long long counter;
   } atomic64_t;
   ```

#### 初始化

3. **静态初始化**：

   ```c
   #define ATOMIC_INIT(i) { (i) }
   ```

   使用示例：

   ```c
   atomic_t my_atomic_var = ATOMIC_INIT(0);
   ```

4. **动态初始化**：

   ```c
   void atomic_set(atomic_t *v, int i);
   ```

   使用示例：

   ```c
   atomic_t my_atomic_var;
   atomic_set(&my_atomic_var, 0);
   ```

#### 基本操作函数

5. **读取原子变量值**：

   ```c
   int atomic_read(const atomic_t *v);
   ```

   使用示例：

   ```c
   int value = atomic_read(&my_atomic_var);
   ```

6. **设置原子变量值**：

   ```c
   void atomic_set(atomic_t *v, int i);
   ```

   使用示例：

   ```c
   atomic_set(&my_atomic_var, 5);
   ```

7. **原子加法**：

   ```c
   void atomic_add(int i, atomic_t *v);
   ```

   使用示例：

   ```c
   atomic_add(3, &my_atomic_var);
   ```

8. **原子减法**：

   ```c
   void atomic_sub(int i, atomic_t *v);
   ```

   使用示例：

   ```c
   atomic_sub(2, &my_atomic_var);
   ```

9. **原子自增**：

   ```c
   void atomic_inc(atomic_t *v);
   ```

   使用示例：

   ```c
   atomic_inc(&my_atomic_var);
   ```

10. **原子自减**：

    ```c
    void atomic_dec(atomic_t *v);
    ```

    使用示例：

    ```c
    atomic_dec(&my_atomic_var);
    ```

11. **原子加法并返回新值**：

    ```c
    int atomic_add_return(int i, atomic_t *v);
    ```

    使用示例：

    ```c
    int new_value = atomic_add_return(3, &my_atomic_var);
    ```

12. **原子减法并返回新值**：

    ```c
    int atomic_sub_return(int i, atomic_t *v);
    ```

    使用示例：

    ```c
    int new_value = atomic_sub_return(2, &my_atomic_var);
    ```

13. **原子自增并返回新值**：

    ```c
    int atomic_inc_return(atomic_t *v);
    ```

    使用示例：

    ```c
    int new_value = atomic_inc_return(&my_atomic_var);
    ```

14. **原子自减并返回新值**：

    ```c
    int atomic_dec_return(atomic_t *v);
    ```

    使用示例：

    ```c
    int new_value = atomic_dec_return(&my_atomic_var);
    ```

15. **测试并设置**：

    ```c
    int atomic_cmpxchg(atomic_t *v, int old, int new);
    ```

    使用示例：

    ```c
    int old_value = atomic_cmpxchg(&my_atomic_var, 5, 10);
    ```

    该操作用于将`v`的值从`old`改为`new`，如果`v`的当前值是`old`，则操作成功，并返回原来的值。

16. **测试并修改**：

    ```c
    int atomic_xchg(atomic_t *v, int new);
    ```

    使用示例：

    ```c
    int old_value = atomic_xchg(&my_atomic_var, 10);
    ```

    该操作用于将`v`的值改为`new`，并返回原来的值。

#### 64位原子操作函数

如果需要对64位整数进行原子操作，可以使用类似的函数，但以`atomic64_`开头。例如：

```c
long long atomic64_read(const atomic64_t *v);
void atomic64_set(atomic64_t *v, long long i);
void atomic64_add(long long i, atomic64_t *v);
void atomic64_sub(long long i, atomic64_t *v);
void atomic64_inc(atomic64_t *v);
void atomic64_dec(atomic64_t *v);
long long atomic64_add_return(long long i, atomic64_t *v);
long long atomic64_sub_return(long long i, atomic64_t *v);
long long atomic64_inc_return(atomic64_t *v);
long long atomic64_dec_return(atomic64_t *v);
long long atomic64_cmpxchg(atomic64_t *v, long long old, long long new);
long long atomic64_xchg(atomic64_t *v, long long new);
```

### 总结

原子变量及其操作函数在多线程环境中提供了一种高效的方式来进行无锁同步，避免了复杂的锁机制，减少了上下文切换的开销。正确使用这些原子操作函数，可以确保对共享数据的安全访问，防止竞态条件。