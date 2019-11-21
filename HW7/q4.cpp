#include <iostream>
#include <string>
using namespace std;

bool s1_in_s2(char,string);   // test if char in string, return TRUE/FALSE

int main(){
    string in_line;
    //string s1(",");
    string str_space(" ");
    string symbol(",.:;!?");
    getline(cin,in_line);
    cout << "input is : " << in_line << endl;     // check how getline work
    int let = 0,sete = 0,let_s = 0;               // letters, sentence,letter_size
    int len = in_line.size();                     // str.size() can get string length
    
    // ------- main for loop ------- //
    // IDEA: 
    // Set three variables let,sete, let_s, our idea is, record letter size, if meet space or symbols, 
    // letters count +1, initialize letter size( to record another letter), then consider exception.
    // 
    // Implement:
    // We have in_line, check each in_line[i] from i = 0 --> end,
    // if in_line[i] is one of ,.:;!? , means we have a new sentence, sete +1, and then check this sentence have letters or not,
    //     1) let_s == 0 : let += 0, let_s = 0 .
    //     2) let_s !=0  : let += 1, let_s = 0 .
    // Exception:  if ,.:;!? is at the begin of in_line, we don't regard it as a new sentence, in this situation, we use exception to handle it.
    // If in_line[i] == space , check letters, 1) let_s ==0 :....... same as above,
    // if in_line[i] != space & symbols , let += 1, let_s = 0. 
    // ( Actually, we have to check in_line[i] is A to Z or a to z or - ' some symbols by ASCII code to confirm this is really letters,
    // but in this case , we can skip this step.)
    // Exception: if in_line[end] != symbols, we still need to consider it as a sentence, so let += 1, sete ++ 1.
    // 

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

    // -------------------------- //

    cout << sete << "," << let/sete << endl;
    cout << " letters: " << let << " setence: " << sete << endl;    // check sentences and letters 
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
