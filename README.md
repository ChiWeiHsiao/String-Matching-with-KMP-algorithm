# String-Matching-with-KMP-algorithm
##使用KMP演算法
1. 用get()把整份文件存起來，再用strtok()把文件切成一個一個單字存進一個vector <string>。
2. pattern為此vector中的第一個單字
3. 呼叫failure()把此pattern的failure函數算出來，存到一個int陣列f[]
4.  把第一個到最後一個單字依序丟給一個叫"match"的function。
  * 為pattern和此單字各設一個int posP、posW以記錄當前要比對的位置。
  * 把答案存到一個叫"password"的vector<int>。
5. 把password中的答案輸出到outputfile
