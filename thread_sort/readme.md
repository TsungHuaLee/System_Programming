#404410082 資工三 李宗樺
##題目
![題目](https://i.imgur.com/0DBN8Nx.png)

##(1)如何利用平行化提高運算速度
1.  include <pthread.h> <br>
    don't forget to include the POSIX library in your code
    <pre><code>$gcc -l pthread hw2 -o hw2</code></pre>
***
2.  pthread_create -> create a new thread
    <pre><code>int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);</code></pre>
    參數1. pthread_t *tid為pthread的指標，在使用Thread之前必須要先宣告一個pthread_t的變數。<br>
    參數2. const pthread_attr_t *attr為該Thread的屬性，預設是NULL，如果沒有其他特殊的需求直接填入NULL即可。<br>
    參數3. void *(*function)(void *)為Function pointer，這邊要放入你要執行的Function。<br>
    參數4. void *argument為Function pointer所要帶的參數。 回傳值: 如果執行成功則回傳0，如果執行失敗則回傳錯誤代碼。<br>
***
3.  pthread_join -> join with a terminated thread
    <pre><code>int pthread_join(pthread_t thread, void **retval);</code></pre>
    pthread_join 做兩件事
    1.  等待thread結束
    2.  回收resource
    參數1. pthread_t tid為pthread的指標，在使用Thread之前必須要先宣告一個pthread_t的變數。注意！這邊不需要用pointer.<br>
    參數2. void **value_ptr用來取得目標Thread的回傳值。<br>
***
4.  include <semaphore.h>
***
5.  sem_init ->初始化一個semaphore
    <pre><code>int sem_init(sem_t *sem, int pshared, unsigned int value)</code></pre>
    參數1.sem：要初始化的semaphore的物件指標
    參數2.pshared：0該semaphore給執行緒使用，1給行程使用
    參數3.value：允許幾個process進入critical section
***
6.  sem_wait -> lock
    <pre><code>int sem_wait(sem_t *sem);</code></pre>
***
7.  sem_post -> unlock
    <pre><code>int sem_post(sem_t *sem);</code></pre>

##(2)如何確保多個 thread 間不會產生 race condition
&emsp;&emsp;同時對一個地方做讀寫就有可能造成race condition，因此應該要減少thread對全域變數total的寫入，所以我先在local variable 做完計算，才將答案寫入total。<br>
&emsp;&emsp;用semaphore將存進全域變數的地方做成critical section，只允許一個process操作
##(3)使用圖形說明你的程式碼是很有效率的，與簡述使用的演算法
![圖](https://i.imgur.com/3kn7Ea3.jpg)

##(4)結果
real time ->程式從開始到結束的時間。<br>
user time ->程式在 user mode 所佔用的 CPU 時間總和，會將每顆CPU的時間加起來。<br>
sys time ->kernel mode 所佔用的 CPU 時間總和。<br>
可以看到user time幾乎是user time 的兩倍
![圖](https://i.imgur.com/pQlDANZ.png)
