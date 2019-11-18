#include <iostream>
#include <string>
using namespace std;

bool s1_in_s2(char,string);

int main(){
    string in_line;
    string s1(",");
    string str_space(" ");
    string symbol(",.:;!?");
    getline(cin,in_line);
    cout << "input is : " << in_line << endl;
    int let = 0,sete = 0,let_s = 0;// letters, sentence,letter_size
    int len = in_line.size();
    for(int i =0; i < len; i++){
        if(s1_in_s2(in_line[i],symbol)){
	    if(i !=0)
	        sete++;
	    if(let_s == 0){}
	    else{
	        let += 1;
		let_s = 0;
	    }    
	}
	else{
	    if (in_line[i] != str_space[0]){
	        let_s += 1;
	    }
	    else{
	        if(let_s ==0){}
		else{
		    let += 1;
		    let_s = 0;
		}
	    }
	        
	    if( i == len-1){
		let += 1;
	        let_s = 0;
	        sete++;
	    }
	}
    }
    cout << sete << "," << let/sete << endl;
    cout << " letters: " << let << " setence: " << sete << endl;
    return 0;
}

bool s1_in_s2(char a, string str1){
    int flag = 0;
    for(int i = 0 ; i < str1.size(); i++){
        if(a == str1[i])
	    flag = 1;
    }
    return flag;
}
