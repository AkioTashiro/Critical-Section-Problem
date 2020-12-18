#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
using namespace std;

int RC, WC, RC2, WC2 = 0;   //RC, WC are for the counter. RC2, WC2 are counter for NCS maybe not gonna use.
int r1(), r2(),r3(), w1(), w2();
int r1pc, r2pc, r3pc, w1pc, w2pc = 0;   //for the switch
//void cs();   //critical section is inside of processors
bool TestAndSet(bool *target);
//bool ReadTandS();
void panicMessage();
bool lockD = false;    //shared boolean variable lock default is false which means door is open

int main() {
    srand((int)time(NULL));
    
    for(int i=0; i<10000; i++){
        int pid = rand()%5;    //for the case 0 through 4
        switch(pid){
            case 0: r1();break;
            case 1: r2();break;
            case 2: r3();break;
            case 3: w1();break;
            case 4: w2();break;
        }
    }
    return 0;
}
/*void cs(){
    for(int i=0; i<100; i++){}
}*/
void panicMessage(){      //if the program break the rule one writer or two reader in the CS each time
    cout<<"Panic!!"<<endl;  //this will print out the message.
    cout<<"R:"<<RC<<" W:"<<WC<<endl<<endl;;
}
bool TestAndSet(bool *target){    //this is the door and key to the CS room. Target take false and return  false first.
    bool rv = *target;
    *target = true;      //then taget aka lockD becomes true which meas locked!
    return rv;   //then return false for the process which just got into the cs.
}    //when another try to come here, the lock is ture, target pass ture to the rv, and return rv which is true(Locked!!)
/*bool ReadTandS(){     //to let 2 readers inside of the cs
    if(RC <2 && WC < 0){
        return false;
    }
    else return true;
}*/
int r1(){
    int i = 0;
    switch(r1pc){
        case 0: cout<<"r1) is in NCS."<<endl; r1pc++; break;   //NCS section
        case 1: cout<<"r1) sees R:"<<RC<<" W:"<<WC<<" in CS."<<endl; r1pc++; break;   //seeing inside of the CS from outside
        case 2: cout<<"r1) is trying to enter CS."<<endl; r1pc++; break;   //processor is ready to enter cs, also where p wait
        case 3: if((TestAndSet(&lockD)&&RC<2&&WC==0)) {r1pc++; break;} else r1pc--; break;
            //if door is open or reader is less then 2 or writer is not there then go ahead and enter the CS. Otherwise go back to teh case2.
        case 4: cout<<"r1) is inside of the CS."<<endl; RC++; r1pc++; break; //now the processor is in side of the CS
        case 5: cout<<"r1) Inside R:"<<RC<<" W:"<<WC<<endl; r1pc++; break;  //seeing inside of the CS from inside.
        case 6: if(RC>2||(RC>0&&WC>0)){panicMessage();} r1pc++; break;  //panic checking.
        case 7: if(i<40) r1pc++; r1pc=9; break;   //loop for the critical section to see if this is working.
        case 8: i++; r1pc--; break;      //same as while loop.
        case 9: cout<<"r1) just got out of the CS. "<<endl; lockD = false; RC--; r1pc++; break; //now exiting the CS and set the LockD to false means door is open for everybody.
        default: break;
            //case 3: if(TestAndSet(&lockD)==true){cout<<"r1)locked!"<<endl; r1pc--;}
            //else cout<<"r1) entered!"<<endl; r1pc++; break;
            //case 7: cout<<"reader1 just got out from CS. "<<endl; rc--; r1pc++; break;
            
    }
    return r1pc;
}
int r2(){
    int i = 0;
    switch(r2pc){
        case 0: cout<<"r2) is in NCS."<<endl; r2pc++; break;
        case 1: cout<<"r2) sees R:"<<RC<<" W:"<<WC<<" in CS."<<endl; r2pc++; break;
        case 2: cout<<"r2) is trying to enter CS."<<endl; r2pc++; break;
        case 3: if((TestAndSet(&lockD)&&RC<2&&WC==0)) {r2pc++; break; } else r2pc--; break;
        case 4: cout<<"r2) is inside of the CS."<<endl; RC++; r2pc++; break;
        case 5: cout<<"r2) Inside R:"<<RC<<" W:"<<WC<<endl; r2pc++; break;
        case 6: if(RC>2||(RC>0&&WC>0)){panicMessage();} r2pc++; break;
        case 7: if(i<40) r2pc++; r2pc=9; break;
        case 8: i++; r2pc--; break;
            //case 9: if(RC>2||(RC>0&&WC>0)){panicMessage();} r2pc++; break;
        case 9: cout<<"r2) just got out of the CS. "<<endl; lockD = false; RC--; r2pc++; break;
        default: break;
    }
    return r2pc;
}
int r3(){
    int i = 0;
    switch(r3pc){
        case 0: cout<<"r3) is in NCS."<<endl; r3pc++; break;
        case 1: cout<<"r3) sees R:"<<RC<<" W:"<<WC<<" in CS."<<endl; r3pc++; break;
        case 2: cout<<"r3) is trying to enter CS."<<endl; r3pc++; break;
        case 3: if((TestAndSet(&lockD)&&RC<2&&WC==0)) {r3pc++; break;} else r3pc--; break;
        case 4: cout<<"r3) is inside of the CS."<<endl; RC++; r3pc++; break;
        case 5: cout<<"r3) Inside R:"<<RC<<" W:"<<WC<<endl; r3pc++; break;
        case 6: if(RC>2||(RC>0&&WC>0)){panicMessage();} r3pc++; break;
        case 7: if(i<40) r3pc++; r3pc=9; break;
        case 8: i++; r3pc--; break;
            //case 9: if(RC>2||(RC>0&&WC>0)){panicMessage();} r3pc++; break;
        case 9: cout<<"r3) just got out of the CS. "<<endl; lockD = false; RC--; r3pc++; break;
        default: break;
    }
    return r3pc;
}
int w1(){
    int i = 0;
    switch(w1pc){
        case 0: cout<<"w1) is in NCS."<<endl; w1pc++; break;
        case 1: cout<<"w1) sees R:"<<RC<<" W:"<<WC<<" in CS."<<endl; w1pc++; break;
        case 2: cout<<"w1) is trying to enter CS."<<endl; w1pc++; break;
        case 3: if((!TestAndSet(&lockD)&&RC==0&&WC==0)){w1pc++; break;} else w1pc--; break;
        case 4: cout<<"w1) is inside of the CS."<<endl; WC++; w1pc++; break;
        case 5: cout<<"w1) Inside R:"<<RC<<" W:"<<WC<<endl; w1pc++; break;
        case 6: if(RC>2||(RC>0&&WC>0)){panicMessage();} w1pc++; break;
        case 7: if(i<40) w1pc++; w1pc=9; break;
        case 8: i++; w1pc--; break;
            //case 9: if(RC>2||(RC>0&&WC>0)){panicMessage();} w1pc++; break;
        case 9: cout<<"w1) just got out of the CS. "<<endl; lockD = false; WC--; w1pc++; break;
        default: break;
    }
    return w1pc;
}
int w2(){
    int i = 0;
    switch(w2pc){
        case 0: cout<<"w2) is in NCS."<<endl; w2pc++; break;
        case 1: cout<<"w2) sees R:"<<RC<<" W:"<<WC<<" in CS."<<endl; w2pc++; break;
        case 2: cout<<"w2) is trying to enter CS."<<endl; w2pc++; break;
        case 3: if((!TestAndSet(&lockD)&&RC==0&&WC==0)){w2pc++; break;} else w2pc--; break;
        case 4: cout<<"w2) is inside of the CS."<<endl; WC++; w2pc++; break;
        case 5: cout<<"w2) Inside R:"<<RC<<" W:"<<WC<<endl; w2pc++; break;
        case 6: if(RC>2||(RC>0&&WC>0)){panicMessage();} w2pc++; break;
        case 7: if(i<40) w2pc++; w2pc=9; break;
        case 8: i++; w2pc--; break;
            //case 9: if(RC>2||(RC>0&&WC>0)){panicMessage();} w2pc++; break;
        case 9: cout<<"w2) just got out of the CS. "<<endl; lockD = false; WC--; w2pc++; break;
        default: break;
    }
    return w2pc;
}

//int p=0; r1pc++; break;
//if(p<100)p++; else r1pc++; break;
