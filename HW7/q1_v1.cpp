#include<iostream>
using namespace std;

//TODO:
//use vector to replace array

void input_arr(int* &, int );
void dele_int_Arr(int* );
void input_2D_arr(int** &, int, int);

int main(){
    int I_w;         // I workshops on production line
    int T_days;      // T days
    int *M_mach;         // numbers of machines perworkshop
    int *C_on;       // each machine cost C_on per day
    int *C_D;        // each machine cost C_D per kg when producing
    int *B;          // each machine produces at most B kg per day
    int *R;          // raw material to product change rate
    int C_s_0;       // store material cost C_s_0 per kg per day
    int *C_s_1;      // store product cost C_s_1 per kg per day
    int S_0;         // initial stock of material (kg)
    int *S_1;        // initial stock of product (kg)
    int * Dt;        // product demand each day
    int * Pt;        // material price each day
    int ** xt;       // production amount per day in production plan
    int * wt;        // material need to buy per day in production plan
    int ** R_p_t;    // remained products after selling each day
    int * R_m_t;     // remained materials after produce each dat


    // -----input phase start ----- //
    cin >> I_w;
    cin >> T_days;
    input_arr(M_mach, I_w);
    input_arr(C_on, I_w);
    input_arr(C_D, I_w);
    input_arr(B, I_w);
    input_arr(R, I_w);
    cin >> C_s_0;
    input_arr(C_s_1, I_w);
    cin >> S_0;
    input_arr(S_1,I_w);
    input_arr(Dt, T_days);
    input_arr(Pt, T_days);
    input_2D_arr(xt, I_w, T_days);
    input_arr(wt, T_days);
    // -----input phase end   -----//
    
    // -----output phase start-----// // just used to check if input are all stored and correct//
    /*
    cout << endl << " --- input ok --- " << endl << endl;
    cout << I_w << " " << T_days << endl  << M_mach[0] << " " << M_mach[1] << endl <<  C_on[0] << " " << C_on[1] << endl;
    cout << C_D[0] << " " << C_D[1] << endl;
    cout << B[0] << " " << B[1] << endl;
    cout << R[0] << " " << R[1] << endl;
    cout << C_s_0 << " " << C_s_1[0] << " " << C_s_1[1] << endl;
    cout << S_0 << " " << S_1[0] << " " << S_1[1] << endl;
    //cout << " &Dt: " << &Dt << endl;
    cout << " Dt: " << Dt[0] << " " << Dt[1] << " " << Dt[2] << " & " << &Dt[0] << endl;
    cout << " Pt: " << Pt[0] << " " << " " << Pt[1] <<" " << Pt[2] << endl;
    cout << " xt: " << xt[0][0] << " " << xt[0][1] << " " << xt[0][2] << endl;
    cout << " xt: " << xt[1][0] << " " << xt[1][1] << " " << xt[1][2] << endl;
    cout << " wt: " << wt[0] << " " << wt[1] << " " << wt[2]<< endl;
    */
    // -----output phase end  -----//
    
    
    //first we check condition 2 , all xt[i][j] <= M[i]B[i]

    int flag_x = 1;
    for(int i =0; i < I_w; i++){
        for (int j = 0; j < T_days; j++){
            if(xt[i][j] > (M_mach[i]*B[i])){
	        flag_x = 0;
                break;
	    }
	}
	if(flag_x == 0)
            break;
    }
    //TODO:
    //1.R_p_t[][]
    //
    //
    // count every days remain product and material, and also check condition 1 & 3
    // condition 1 , (remained product + production plan product (xt)) achieve demand(Dt) or not
    // condition 3 , (remained materials + buy materials(wt)) forfilled production plan product (xt) or not
    R_p_t = new int*[I_w];
    for(int i = 0; i < I_w; i++){
        R_p_t[i] = new int[T_days]();
    }
    R_m_t = new int[T_days]();

    R_p_t[0][0] = S_1[0] + xt[0][0] - xt[1][0]*R[1];
    R_p_t[1][0] = S_1[1] + xt[1][0] - Dt[0];
    R_m_t[0] = S_0 + wt[0] - xt[0][0]*R[0];

    int flag_p_0 = 1;
    int flag_p_1 = 1;
    int flag_m = 1;

    for(int i = 1; i < T_days; i++){
        R_p_t[0][i] = R_p_t[0][i-1] + xt[0][i] - xt[1][i]*R[1];
	R_p_t[1][i] = R_p_t[1][i-1] + xt[1][i] - Dt[i];
	if( R_p_t[0][i] < 0 ){
	    flag_p_0 = 0;
	    break;
	}
	if( R_p_t[1][i] < 0){
	    flag_p_1 = 0;
	    break;
	}
	R_m_t[i] = R_m_t[i-1] + wt[i] - xt[0][i]*R[0]; ///   should be xt[i]*R;
	if( R_m_t[i] < 0){
	    flag_m = 0;
	    break;
	}
    }
    
    if (flag_x * flag_p_0 * flag_p_1 * flag_m == 0){
        cout << "-1";
    }
    else{
        //TODO:
	// if I != 2
	// output variable name
        int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int t4 = 0;
	int t5 = 0;
	int t6 = 0;
        
	for(int i = 0; i < T_days; i++){
	    int Num_0 = xt[0][i]/B[0];
	    if( Num_0*B[0] < xt[0][i] )
	        Num_0 += 1;
	    int Num_1 = xt[1][i]/B[1];
	    if(Num_1*B[1] < xt[1][i])
	        Num_1 +=1;
	    t1 = t1 + (C_on[0] * Num_0) + (C_on[1] * Num_1);
	    t2 = t2 + (C_D[0] * xt[0][i]) + (C_D[1] * xt[1][i]);
	    t3 = t3 + (R_m_t[i] * C_s_0);
	    t4 = t4 + (R_p_t[0][i] * C_s_1[0]);
	    t5 = t5 + (R_p_t[1][i] * C_s_1[1]);
	    t6 = t6 + (wt[i] * Pt[i]);
	}
        cout << t1 << "," << t2 << "," << t3 << "," << t4 << "," << t5 <<","<< t6 ;
    }

    
    
    dele_int_Arr(Dt);
    dele_int_Arr(Pt);
    //dele_int_Arr(xt);
    dele_int_Arr(wt);
    //dele_int_Arr(R_p_t);
    dele_int_Arr(R_m_t);
    
    return 0;
}

void input_arr(int* &arr, int T){
    //cout << " void &arr: " << &arr << endl;
    arr = new int[T]();
    for(int i=0; i < T; i++){
        cin >> arr[i];
    }
    
    /*
    cout << " test output: ";
    for( int i = 0; i < T ; i++){
        cout << arr[i] << " & " << & arr[i] << " ";
    }
    cout << endl;
    cout << " &arr: " << &arr << endl;*/
}

void input_2D_arr(int** &arr, int I, int T){
    arr = new int *[I];
    for( int i = 0; i < I; i++){
        input_arr(arr[i],T);
    }
}

void dele_int_Arr(int * arr){
	delete [] arr;
}
