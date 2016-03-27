#include<iostream>
#include<cstdio>
#include<fstream>
#include<ctime>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

const int MAX_SIZE_WORD=1000000; //���]�@��word�̪���1000000
vector <string> text;//plain text
vector <int> password;//answer
string pat;//pattern
int lenP;//pattern������
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

void match(int index){//�M��Y�ӳ�r�����h�֭�pattern
    string word = text[index];
    int posP=0, posW=0;
    int cnt=0;
    int lenW=word.length();
    while(posW<lenW){
        if(pat[posP]==word[posW]){//character match >> �~����U�@�Ӧr��
            posP++; posW++;
            if(posP==lenP){//���@��pattern�F
                password.push_back(index+1);//�⵪�צs�ipassword��
                posP=0;//posP �k�s
                posW=posW-lenP+1;//posW���^����X�{pattern���Ĥ@�쪺�U�@�� (�Y�U�@��pattern�i��X�{����m)
            }
        }
        else{ //mismatch >> ��failure function����U�@�ӥi�઺��m
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
    int t_start=clock();//�p�ɶ}�l
    ifstream fin(fin_name);
    ofstream fout(fout_name);
    fin.get(document,1000000,'\0');//Ū�i���document (�Ndelimiter�令\0)
    //�ϥ�strtok()�Ndocument���Φ��@�Ӥ@�ӳ�r
    char *a_word = strtok(document," \n.");
    while(a_word != NULL){
        text.push_back(a_word);//�qfile���@��word�@��wordŪ�i�s"text"��vector��
        a_word = strtok(NULL," \n.");
    }
    fin.close();
//------------------Ū���ɮ�-------------------------------
    if(!text.empty()){//�p�Gdocument�O�ťդ��->������X���
        pat=text[0];//pattern ���Ĥ@��word
        lenP=pat.length();
        failure();//create failure table of pattern
        for(i=0;i<text.size();i++)  match(i);//�q�Ĥ@�ӳ�r�I�s match(i)��̫�@�ӳ�r
    }
//--------------��X����--------------------------------------------
    fout <<(clock()-t_start)/(CLOCKS_PER_SEC)<<"ms"<<endl;
    for(i=0;i<password.size();i++) fout << password[i];
    fout.close();
    return 0;
}

