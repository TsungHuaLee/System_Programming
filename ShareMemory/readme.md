# linux.cs.ccu.edu.tw
#(1) 404410082 資工三 李宗樺
##(2)程式執行結果
![link](https://i.imgur.com/3chvSec.png)
##(3)程式如何執行
  1.  用shmget創造一個share memory

  2.  用shmctl完成對share memory的控制

  3. 按照題目需求印出來

##(4)其他說明，其他說明越詳細越好
1.  shmget 參數
    <pre><code>int shmget(key_t key, size_t size, int shmflg)</code></pre>
    * key = 0 (IPC_PRIVATE) : will create a new share memory object
    * size: size of share memory
    * shmflg = IPC_CREATE|IPC_EXCL|600:如果不存在相同key，會新建一個新的share memory, 有則回報錯誤。600是權限 -> <font color = red>一定要加上權限</font>

2.  shmctl 參數
    <pre><code> int shmctl(int shmid, int cmd, struct shmid_ds *buf)</code></pre>
    * shmid: segment id (the return value of shmget)
    * cmd = IPC_STAT: get the state of share memory, and store in buf  
    * buf: buffer


3.  MODE = 384, 將它轉成二進位制是110,000,000也就是600也就是當初設的權限
