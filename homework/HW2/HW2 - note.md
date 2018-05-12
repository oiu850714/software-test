# Software-Testing HW2

* 沿用 HW1 的三個問題的實作，故直接開始寫 test

## Triangle Problem
* 先貼 code 才有辦法看 test cover 到什麼程度:
    * 為 code 增加註解，比較好對照
* ![](https://i.imgur.com/WJNsu0Z.png)


### C0
* 跑過所有 statements
* ![](https://i.imgur.com/dJTeDmj.png)
* ![](https://i.imgur.com/HIhLqKv.png)

### C1
* 跑過所有 condition 的 branches
* 我的實作總共有七個 branches
    * 1st 有 2個，2nd 有 2個，3rd 有 3個
* 但我這個 test case 剛好會跟 C0 的一樣(C1 本來就 >=(subsume) C0)
* ![](https://i.imgur.com/9w3fCMc.png)
* ![](https://i.imgur.com/ctG10Y1.png)


### C2
* 因為 triangle problem 沒有 loop，所以 C2 會跟 C1 一樣
* ![](https://i.imgur.com/1CAsU2K.png)
![](https://i.imgur.com/K35scoK.png)


### MCDC
* 要把每個 branch 內的，會**獨立**影響 true/false 的 condition 都執行過一次
* 這裡比較麻煩的是三角形的三邊長彼此會互相依賴，例如 `!(a < b + c && b < c + a && c < a + b)` 這樣的 expression；
* 總之 code 是這樣:
    * ![](https://i.imgur.com/1ibHJrr.png)
    * ![](https://i.imgur.com/NS1fzgL.png)

### gcov 測試
* statement coverage:
    * ![](https://i.imgur.com/44gZHuL.png)
* branch coverage:
    * ![](https://i.imgur.com/TqOLmoS.png)




## NextDate Problem
* 一樣先貼 code:
* ![](https://i.imgur.com/YLtgXvH.png)
* ![](https://i.imgur.com/eMoK0gQ.png)

### C0
![](https://i.imgur.com/hKy4lUR.png)
* 前面三個 tests 把 1st "big" if 都執行過，最後一個則是都會碰到剩下的 branches


### C1
![](https://i.imgur.com/nDNmfoS.png)
* 一樣把所有 branch 的 true/false 都走一次
* ![](https://i.imgur.com/RTFIdjy.png)

### C2
* 因為一樣沒有 loop，所以跟 C1 一樣

### MCDC
* 跟 C1 C2 差不多，因為大部分的 if statements 都是單一一個 condition(或者說只有一個變數)，然後又沒有 loop
* ![](https://i.imgur.com/hfUZAs1.png)
* ![](https://i.imgur.com/Z70Idi0.png)

### gcov 測試
* statement coverage:
    * ![](https://i.imgur.com/10h7EHX.png)
        * 沒 100%...
        * 看了一下，就有一些 corner case 沒確認
            * ![](https://i.imgur.com/QIvAUMq.png)
        * 為它們補上一些測資:
            * ![](https://i.imgur.com/0dhSIM6.png)
    * ![](https://i.imgur.com/AnK6rdu.png)
        * 這樣就 100% 了
* branch coverage:
    * ![](https://i.imgur.com/Pd6As0g.png)




## Commission Problem
* 這題的 decision 就更單純了，而且一樣每個 decision 都只有一個 condition(或者說只有一個變數)，然後一樣沒有 loop

* code:
* ![](https://i.imgur.com/cZ0E3pN.png)

### C0
* ![](https://i.imgur.com/ILbycwk.png)
* ![](https://i.imgur.com/ie3HMcz.png)

### C1
* 在這個題目跟實作之下，C1 剛好會跟 C0 一樣(C1 本來就 >=(subsume) C0)
* ![](https://i.imgur.com/3RQoH6O.png)

### C2
* 沒 loop，跟 C1 一樣

### MCDC
* 因為這個題目很單純，所以 MCDC 幾乎跟 C1 一樣...
* ![](https://i.imgur.com/ZrEbbOT.png)
* ![](https://i.imgur.com/rwBySDm.png)

### gcov 測試
* statement coverage:
    * ![](https://i.imgur.com/5COo4dw.png)
* branch coverage:
    * ![](https://i.imgur.com/TvGfhM2.png)


