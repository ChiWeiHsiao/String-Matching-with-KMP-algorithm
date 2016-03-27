# String-Matching-with-KMP-algorithm
##使用KMP演算法
1. 用get()把整份文件存起來，再用strtok()把文件切成一個一個單字存進一個vector <string>。
2. pattern為此vector中的第一個單字
3. 呼叫failure()把此pattern的failure函數算出來，存到一個int陣列f[]
4. 把第一個到最後一個單字依序丟給一個叫"match"的function。
-為pattern和此單字各設一個int posP、posW以記錄當前要比對的位置。
-把答案存到一個叫"password"的vector<int>。

while:從此單字的的第一個字元與pattern的字元比對，直到最後一個字元:
	if(字元 pat[posP]等於word[posW]) --> posP、posW往後一格。{
		if( posP等於pattern的長度){  //表示已經找到了一個pattern
		-->讓posP歸零，posW往回移到下一個pattern可能出現的位置(即這次		word中出現pattern的第一位的下一個位置)。並將此單字的編號存到			       password。
		}
	}
	else {//遇到mismatch
		if(posP是0) 直接將posW往後移一位
		else 用已算好的failure function讓posP移到可能與posW配對的字元
	}
5. 把password中的答案輸出到outputfile
