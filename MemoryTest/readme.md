# 404410082 資工三 李宗樺
## 題目
![題目](https://i.imgur.com/iWPB0LW.png)
## 第一個實驗
### 說明你實驗的依據
1. malloc 40MB<br>
<pre><code>int *mem = (int*)malloc(sizeof(int)*10*1024*1024);</code></pre>

2. 對每一個位置做存取
<pre><code>memset(mem, 0, sizeof(int)* 10* 1024 * 1024);</code></pre>

3. 用 command "top -p pid" 觀察
### 說明你所設計的程式是否有特別之處
1.  用getpid()得到process id，方便觀察。

2.  記憶體存取直接使用memset()。

3.  用getchar()等待，方便觀察。
### 你觀察 Linux 中那些檔案或者資訊，以驗證你的論述
用 top 指令，觀察process的RES(anything occupying physical memory)。<br>
觀察只有malloc，卻還沒對記憶體操作時，RES 只有 752 KB。
![圖](https://i.imgur.com/Rtephrc.png)

觀察對每個記憶體做存取後，RES 42268 KB。
![圖](https://i.imgur.com/i4aioGW.png)

## 第二個實驗
### 說明你的程式花費了多少時間，釋放了多少記憶體
![圖](https://i.imgur.com/x9BDZ2S.png)
### 說明你的 free_mem 對於 swap space 的影響（即：是否額外造成 page-out 及 page-in），如何觀察？
在程式開始前，先用free -h 觀察資訊，發現Mem free 11G。
![圖](https://i.imgur.com/H5ZLmab.png)

開始執行程式，宣告大量的記憶體 malloc 14G，，迫使 system 做 swap。<br>
發現Swap used 1GB。
![圖](https://i.imgur.com/sD5V4XO.png)

程式結束後, Mem free 13G，比值前多。<br>
Swap used 依然是1G
![圖](https://i.imgur.com/qPIgrPn.png)
