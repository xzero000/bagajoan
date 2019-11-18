#include <iostream>
using namespace std;

void setTransactions(int ** &, int* &, int);
void all_FofX_whenY(int* , int* ,int, int **,int *, int, int);

int main(){
    int total_items, total_trades;
    float sup_threshold;
    cin >> total_items >> total_trades >> sup_threshold;
        
    int ** total_his;
    int *  his_q;
    setTransactions(total_his,his_q,total_trades);
    
    int b_q_now = 0;            // total quantities a customer buy now
    cin >> b_q_now;
    int *buy_arr = new int [b_q_now];   // record what he buy items by items 
    for (int i = 0; i < b_q_now; i++){
        cin >> buy_arr[i];
    }

    // After cin, now consider about the thing buy now, and we want to suggest one thing to the customer.
    // let all items = x1, x2 ,..., xi , ..., xI
    // the set of things bought now is Y , Y may contain not only one item
    // we create a array all_count[I], want to record  [ f(x1|Y), f(x2|Y), ... , f(Y),..., f(xI|Y)]
    // then we scan total_his: 
    // (1):  for each total_his[i] in total_his, we create a array tmp_count[total_items](),
    //       tmp_count record what items been bought, if total_his[i] = [xi1,xi2,...xij], 
    //       then we set tmp_count[xi1] = 1, tmp_count[xi2] = 1,....,tmp_count[xij] = 1,
    // (2):  After this, we can check if Y is in tmp_count, that is, check all y in Y,tmp_count[yi] == 1.
    // (3):  If Y is in tmp_count, we add tmp_count into all_count, so all y in Y, all_count[y] += 1 ,all_count[xi] += 1.
    // (4):  Repeat (1) ~ (3) from i = 0 ---> total_trades
    // (5):  Then we have all_count[ f(x1|Y), f(x2|Y), ... , f(Y),..., f(xI|Y)]
    // (6):  We first store f(Y) into a variable f_buy, then we set all_count[Y] = 0, 
    //       to avoid if there is a x always comes with Y, to simplify our work.
    // (7):  After all, we use two variable to record the biggest f(xi|Y) & i.
    // (8):  Before output ,check threshold.
    
    int *all_count = new int[total_items]();
    all_FofX_whenY(all_count,buy_arr,b_q_now,total_his,his_q,total_trades,total_items);
    int max_c = 0,max_i = 0;
    int f_buy = all_count[buy_arr[0]-1];
    for(int i =0; i < b_q_now; i++){
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
    }

    float sup = float(max_c)/float(total_trades);
    if(sup > sup_threshold){
        cout << max_i+1 << "," << max_c << ","<< f_buy << endl;
    }
    else{
        cout << " nothing: " << sup << "   " << max_i+1 << "," << max_c << "," << f_buy << endl;
    }
    
    delete [] all_count;
    delete [] buy_arr;
    //del_2P(total_his,his_q,total_trades);
    for (int i = 0; i < total_trades; i++){
        delete total_his[i]; 
    }
    delete [] total_his;
    delete [] his_q;

    return 0;
}

void setTransactions(int ** &trans, int * &itemCnt, int m){
    trans = new int * [m];
    itemCnt = new int [m]();
    int buy_amount = 0;
    for ( int i = 0; i < m; i++){
        cin >> buy_amount;
        itemCnt[i] = buy_amount;
        trans[i] = new int [buy_amount];
        for ( int j = 0; j < buy_amount; j++){
            cin >> trans[i][j];
	}
    }
}

void all_FofX_whenY(int* all, int* buy,int buy_n, int ** trans,int * itemCnt, int trades, int items){
    for( int i = 0; i < trades; i++){
        int * tmp_count = new int[items]();
	for(int j = 0; j < itemCnt[i]; j++){
	    tmp_count[trans[i][j]-1] = 1;
	}  // if buy,1, else,0
	// check if buy in this history
	int flag = 1;
	for(int p = 0; p < buy_n; p++){
	    if( tmp_count[buy[p]-1] == 0){
	        flag = 0;
		break;
	    }// not in this history
	}
	if(flag ==1){
	    for(int p = 0; p < items; p++){
	        all[p] = all[p] + tmp_count[p];
	    }
	} //if true, the items buyed += 1, else += 0, but we store in tmp_count previous, so += tmp_count
        delete [] tmp_count;
    }
}

void del_2P(int ** arr, int *&m1, int m2){
    for(int i = 0; i < m2; i++){
        delete [] arr[i];
    }
    delete [] arr;
}
