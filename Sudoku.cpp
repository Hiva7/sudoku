#include<iostream>
#include<time.h>
#define NOMINMAX
#include<windows.h>
#include<limits>
#include<cstring>
#include<cctype>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::numeric_limits;
using std::streamsize;

void CheckInput(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class Sudoku{
    public:
    int value;
    bool vb; //visibility
    int note;
};

const int boardsize=81;
Sudoku arr[boardsize+1];
int difficulty;



//randomizing the board
void randomizeboard_vb(){
    int random=rand()%(boardsize+1);
    for(int i=0; i<=difficulty; i++){
        while(arr[random].vb==true){
            random=rand()%(boardsize+1);
        }
        arr[random].vb=true;
    }
}
bool check_column(int I){
    for(int x=0; x<I; x+=9){
        for(int y=1; y<=9; y++){
            if(arr[I+y].value==arr[x+y].value){
                return false;
            }
        }
    }
    return true;
}
bool check_box(int I){
    for(int x=I%27; x>0; x-=9){
        for(int y=1; y<=9; y++){
            for(int z=((y-1)/3)*3+1; z<=(((y-1)/3)*3)+3; z++){
                if(arr[I+y].value==arr[I-x+z].value){
                    return false;
                }
            }
        }
    }
    return true;
}
void randomizeboard_value(){
    int random=rand()%9;
    for(int i=0; i<boardsize; i+=9){
        int temp1[9]={1,2,3,4,5,6,7,8,9};
        for(int j=1; j<=9; j++){
            while(temp1[random]==0){
                random=rand()%9;
            }
            arr[i+j].value=temp1[random];
            temp1[random]=0;
        }
        while(check_column(i)==false||check_box(i)==false){
            int temp2[9]={1,2,3,4,5,6,7,8,9};
            for(int j=1; j<=9; j++){
                while(temp2[random]==0){
                    random=rand()%9;
                }
                arr[i+j].value=temp2[random];
                temp2[random]=0;
            }
        }
    }
}

//board display
void display(int highlight){
    int h=1;
    cout<<"    a | b | c | d | e | f | g | h | i"<<endl;
    cout<<"  -------------------------------------"<<endl;
    for(int i=1; i<=boardsize; i++){
        if(i%9==1&&i!=1){
            if(i%27==1){
                cout<<"\033[31m  -------------------------------------\033[0m"<<endl;
            }
            else{
                cout<<"  ------------\033[31m-\033[0m-----------\033[31m-\033[0m------------"<<endl;
            }
        }
        if(i%9==1){
            cout<<h<<" |";
            h++;
        }
        if(arr[i].vb==true){
            if(arr[i].value==highlight){
                cout<<" "<<"\033[32m"<<arr[i].value<<"\033[0m";
            }
            else{
                cout<<" "<<arr[i].value;
            }
            if(i%9==3 || i%9==6){
                cout<<"\033[31m |\033[0m";
            }
            else{
                cout<<" |";
            }
        }
        else{
            if(i%9==3 || i%9==6){
                cout<<"\033[31m   |\033[0m";
            }
            else{
                cout<<"   |";
            }
        }
        if(i%9==0){
            cout<<endl;
        }
    }
    cout<<"  -------------------------------------"<<endl;
}

// //the game
bool win_condition(){
    for(int i=1; i<=81; i++){
        if(arr[i].vb==0){
            return false;
        }
    }
    return true;
}
void game(){
    int tile_value;
    int tile_int;
    string tile_string;
    string difficulty_pick;
    cout<<"-----Choose difficulty-----"<<endl;
    cout<<"1: \033[032mEasy\033[0m"<<endl;
    cout<<"2: \033[036mMedium\033[0m"<<endl;
    cout<<"3: \033[033mHard\033[0m"<<endl;
    cout<<"4: \033[035mExpert\033[0m"<<endl;
    cout<<"5: \033[031mEvil\033[0m"<<endl;
    cout<<"---------------------------"<<endl;
    while(true){
        cout<<"Pick: ";
        cin>>difficulty_pick;
        CheckInput();
        if(difficulty_pick=="Easy"||difficulty_pick=="easy"||difficulty_pick=="1"){
            difficulty=rand()%6+55;
            break;
        }
        else if(difficulty_pick=="Medium"||difficulty_pick=="medium"||difficulty_pick=="2"){
            difficulty=rand()%6+48;
            break;
        }
        else if(difficulty_pick=="Hard"||difficulty_pick=="hard"||difficulty_pick=="3"){
            difficulty=rand()%6+41;
            break;
        }
        else if(difficulty_pick=="Expert"||difficulty_pick=="expert"||difficulty_pick=="4"){
            difficulty=rand()%6+32;
            break;
        }
        else if(difficulty_pick=="Evil"||difficulty_pick=="evil"||difficulty_pick=="5"){
            difficulty=rand()%6+22;
            break;
        }
        else{
            cout<<"Cannot find difficulty, please try again."<<endl;
        }
    }
    int num;
    randomizeboard_vb();
    randomizeboard_value();
    int hl=0;
    while(win_condition()==false){
        display(hl);
        cout<<"Enter tile: ";
        cin>>tile_string;
        CheckInput();
        for (int i=0; i<tile_string.length(); i++) {
            tile_string[i]=toupper(tile_string[i]);
        }
        tile_int=int(tile_string[0]-64)+((tile_string[1]-'0'-1)*9);
        if(tile_string.length()!=2||tile_int<1||tile_int>81){
            system("cls");
            cout<<"Invalid tile, please try again."<<endl<<endl;
            continue;
        }
        if(arr[tile_int].vb==true){
            system("cls");
            hl=arr[tile_int].value;
            continue;
        }
        cout<<"Enter value: ";
        cin>>tile_value;
        CheckInput();
        if(tile_value<1||tile_value>9){
            system("cls");
            cout<<"Value can only be between 1 to 9, please try again."<<endl<<endl;
            continue;
        }
        if(arr[tile_int].value==tile_value){
            arr[tile_int].vb=true;
            system("cls");
        }
        else{
            system("cls");
            cout<<"Incorrect value!"<<endl<<endl;
        }
        hl=0;
    }
    display(0);
    cout<<"You Win!"<<endl;
}

int main(){
    
    srand(time(0));
    game();
    
    return 0;
}