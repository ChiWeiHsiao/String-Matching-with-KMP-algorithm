#include<iostream>
#include<cstdio>
#include<fstream>
#include<ctime>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

const int MAX_SIZE_WORD=1000000; //假設一個word最長為1000000
vector <string> text;//plain text
vector <int> password;//answer
string pat;//pattern
int lenP;//pattern的長度
int f[MAX_SIZE_WORD];//failure function table of pattern

void failure(){//compute failure function of pattern
    int len = pat.length();
    f[0]=-1;
    for(int j=1;j<len;j++){//compute f[j]
        int i=f[j-1];
        while(pat[j] != pat[i+1] && i>=0) i = f[i];//recursion
        if(pat[j] == pat[i+1]) f[j] = i+1;
        else f[j] = -1;
    }
}

void match(int index){//尋找某個單字中有多少個pattern
    string word = text[index];
    int posP=0, posW=0;
    int cnt=0;
    int lenW=word.length();
    while(posW<lenW){
        if(pat[posP]==word[posW]){//character match >> 繼續比對下一個字元
            posP++; posW++;
            if(posP==lenP){//找到一個pattern了
                password.push_back(index+1);//把答案存進password中
                posP=0;//posP 歸零
                posW=posW-lenP+1;//posW往回移到出現pattern的第一位的下一個 (即下一個pattern可能出現的位置)
            }
        }
        else{ //mismatch >> 用failure function移到下一個可能的位置
            if(posP==0) posW++;
            else posP = f[posP-1]+1;//f[] has been computed
        }
    }
}

int main(){
    int i;
    char fin_name[25], fout_name[25];
    char document[1000000];
    scanf("%15s%15s",fin_name, fout_name);
    int t_start=clock();//計時開始
    ifstream fin(fin_name);
    ofstream fout(fout_name);
    fin.get(document,1000000,'\0');//讀進整個document (將delimiter改成\0)
    //使用strtok()將document切割成一個一個單字
    char *a_word = strtok(document," \n.");
    while(a_word != NULL){
        text.push_back(a_word);//從file中一個word一個word讀進叫"text"的vector中
        a_word = strtok(NULL," \n.");
    }
    fin.close();
//------------------讀完檔案-------------------------------
    if(!text.empty()){//如果document是空白文件->直接輸出秒數
        pat=text[0];//pattern 為第一個word
        lenP=pat.length();
        failure();//create failure table of pattern
        for(i=0;i<text.size();i++)  match(i);//從第一個單字呼叫 match(i)到最後一個單字
    }
//--------------輸出答案--------------------------------------------
    fout <<(clock()-t_start)/(CLOCKS_PER_SEC)<<"ms"<<endl;
    for(i=0;i<password.size();i++) fout << password[i];
    fout.close();
    return 0;
}

