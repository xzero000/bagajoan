#include<iostream>
#include<vector>
using namespace std;

class workshop{
    int ID;
    int n_machine;
    int Con;
    int CD;
    int B;
    int R;
    int cost;
    int w_cost;
};

void cout2D(vector<vector<int>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[i].size(); j++){
	    cout << v[i][j] << " " ;
	}
	cout << endl;
    }
}


int main(){
    int  I,T;
    cin >> I >> T;
    vector<workshop> v_w(I+1);  //include 0 as Cs0
    //cout << " size: " << v_w.size() << endl;
    //TODO
    //cin
    
    vector<vector<int>> openM(I,vector<int>(T,0));
    vector<vector<int>> generateT(I,vector<int>(T,0));
    vector<int> buyT(T,0);
    
    //TODO algorithm
    


    //cout
    cout2D(openM);
    cout2D(generateT);
    for(int i = 0; i < T; i++){
        cout << buyT[i] << " " ; 
    }

    return 0;
}
