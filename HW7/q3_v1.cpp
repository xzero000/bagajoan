#include <iostream>
using namespace std;

void cout_array(int ** arr, int *oneD_l,int twoD_l);

void setTransactions(int** trans, int* itemCnt, int m); 

bool arr1_in_arr2(int* arr1, int* arr2);

int main(){
    int total_items, total_trades;
    float sup_threshold;
    cin >> total_items >> total_trades >> sup_threshold;
    //cout << total_items << " " << total_trades << " " << sup_threshold << endl;
    
    int **total_arr;
    int *his_buy_no;
    total_arr = new int *[total_trades];
    his_buy_no = new int [total_trades];
    int buy_no = 0;
    for (int i = 0; i < total_trades; i ++){
        cin >> buy_no;
	//cout << " history buy count: " << buy_no << " cin: " ;
	his_buy_no[i] = buy_no; 
	total_arr[i] = new int[buy_no];
	for (int j = 0; j < buy_no; j++){
	    cin >> total_arr[i][j];
	}
	//cout << " array full !" << endl;
    }

    int buy_now = 0;
    cin >> buy_now;
    int *buy_arr = new int[buy_now];
    for (int i = 0; i < buy_now; i++){
        cin >> buy_arr[i];
    }
    //cin end

    cout_array(total_arr,his_buy_no,total_trades); // check cin

    int *all_count = new int[total_items](); // want to count all  f(x|y),

    /*
    for(int i = 0; i < total_items; i++){
        all_count[i] = 0;
    }*/
    
    // count all f(x|y)
    // tmp_count is to count single trade
    // and then add into all_count
    for(int i = 0; i < total_trades; i++){
	int *tmp_count = new int[total_items]();
        for (int j = 0; j < his_buy_no[i]; j++){
	    tmp_count[total_arr[i][j]-1] += 1;
	} //if buy,1,else,0
	// check if this history contain buy_arr
	int flag = 1;
	for(int p = 0; p < buy_now; p++){
	    if(tmp_count[buy_arr[p]-1] == 0){
	    flag = 0;
	    break;
	    }
	}
	if(flag == 1){
            for(int q = 0; q < total_items; q++){
	        all_count[q] = all_count[q] + tmp_count[q];
	    }
	}//if true, the items buyed += 1, else += 0, but we store in tmp_count previous, so += tmp_count
	delete[] tmp_count;  // new&delete
    }
    
    //check
    for(int i =0; i < total_items;i++){
        cout << " " << all_count[i] << "  ";
    }
    cout << endl;

    int max_i = 0;
    int max_c = 0;
    int f_buy = all_count[buy_arr[0]-1]; // f(y)
    for(int i =0; i < buy_now; i++){
        all_count[buy_arr[i]-1] = 0;
    } // we already store f(y) in f_buy, so we set the buy items now to 0, to avoid if there is a f(X) == f(Y)
    
    // max_c: f(X),max_i: X
    for(int i=0; i < total_items; i++){
	if(max_c >= all_count[i]){
	}
	else{
	    max_c = all_count[i];
	    max_i = i;
	}
        //max_c = (max_c>all_count[i])?max_c:all_count[i];
    }

    float sup = float(max_c)/float(total_trades);
    if(sup > sup_threshold){
	cout << max_i+1 << "," << max_c << ","<< f_buy << endl;
    }
    else{
        cout << " nothing: " << sup << "   " << max_i+1 << "," << max_c << "," << f_buy << endl;
    }
    return 0;   
}

/*void count_item(int ** arr, int *oneD_l,int twoD_l){
    for (int i = 0; i < twoD_l; i++){
        for(int j = 0; j < oneD_l[i] ; j++){
            
       	}
    }
}*/


void setTransactions(int** trans, int* itemCnt, int m){
}

void cout_array(int ** arr, int *oneD_l,int twoD_l){
    for (int i = 0; i < twoD_l; i++){
        cout << " a[" << i << "] : " ;
	/*int x = sizeof(arr[i])/sizeof(int);
	cout << " j : "<< x << " -- ";*/
	for(int j = 0; j < oneD_l[i] ; j++){
	//for(int j = 0; j < x; j++){
	    cout << arr[i][j] << " " ;
	}
	cout << endl;
    }
}



