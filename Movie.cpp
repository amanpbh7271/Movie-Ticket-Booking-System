#include<bits/stdc++.h>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////
//this is for parsing input
class Parser{
    unordered_map<string,int> dict;
    void tokenize(string const &, const char,vector<string>&);
    public:
    Parser(){
        dict["add-screen"]=0;
        dict["reserve-seat"]=1;
        dict["get-unreserved-seats"]=2;
        dict["suggest-contigious-seats"]=3;
    }
    pair<int,vector<string>> parse(string s,char delim=' '){
        vector<string> out;
        tokenize(s, delim, out);
        return make_pair(this->dict[out[0]],out);
    }
};

void Parser::tokenize(string const &str, const char delim,vector<string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

///////////////////////////////////////////////////////////////////////////////////
class hall{
    public:
    int row;
    int col;
    vector<vector<bool> > seats;
    hall(int row,int col){
        this->row=row+1;
        this->col=col+1;
        seats.resize(this->row);
        for (int i = 1; i < this->row; ++i){
            seats[i].resize(this->col);
            for(int j=1;j < this->col;++j){
                seats[i][j]=false;
            }   
        }
    }
};

class bookMyShow{
    public:
    unordered_map<int,hall*> screens;
    public:
    void addScreen(vector<string>);
    void reserverSeat(vector<string>);
    void getUnreservedSeat(vector<string>); 
    void suggestContigiousSeats(vector<string>);
};

void bookMyShow::addScreen(vector<string> input){
    //aquiring input
    int screen_number=*(input[1].end()-1)-'0';
    int row=stoi(input[2]);
    int col=stoi(input[3]);
    vector<int> asile_seats;
    for(int i=4;i<input.size();i++){
        asile_seats.push_back(stoi(input[i]));
    }
    if(screens.count(screen_number)>0){
        cout<<"unsuccessull"<<endl;
        return;
    }
    this->screens[screen_number]=new hall(row,col);
    cout<<"successfull"<<endl;
}

void bookMyShow::reserverSeat(vector<string> input){
    //aquiring input
    int screen_number=*(input[1].end()-1)-'0';
    int row=stoi(input[2]);
    vector<int> reserve;
    for(int i=3;i<input.size();i++){
        reserve.push_back(stoi(input[i]));
    }
    
    ////checking boundry condition
    if(screens.count(screen_number)==0 || row>screens[screen_number]->row){
        cout<<"unsuccessful"<<endl;
        return;
    }
    int max_col=screens[screen_number]->col;
    for(int i=0;i<reserve.size();i++){
        if(reserve[i]>max_col){
            cout<<"unsuccessfull"<<endl;
            return;
        }
    }

    //reserving screen
    for(int i=0;i<reserve.size();i++){
        screens[screen_number]->seats[row][reserve[i]]=true;
    }
    cout<<"successfull"<<endl;
}


void bookMyShow::getUnreservedSeat(vector<string> input){
    //aquiring input
    int screen_number=*(input[1].end()-1)-'0';
    int row=stoi(input[2]);


    ////checking boundry condition
    if(screens.count(screen_number)==0 || row>screens[screen_number]->row){
        cout<<"unsuccessful"<<endl;
        return;
    }

    int cnt=0;
    for(int i=1;i<screens[screen_number]->col;i++){
        if(screens[screen_number]->seats[row][i]==false){
            cnt++;
        }
    }

    cout<<"successfull"<<endl;
    cout<<cnt<<endl;

}


void bookMyShow::suggestContigiousSeats(vector<string> input){
    //aquiring input
    int screen_number=*(input[1].end()-1)-'0';
    int requirment=stoi(input[2]);
    int row=stoi(input[3]);
    int eitherEndSeatNumber=stoi(input[4]);

    ////checking boundry condition
    if(screens.count(screen_number)==0 || row>screens[screen_number]->row || requirment>screens[screen_number]->col){
        cout<<"unsuccessful"<<endl;
        return;
    }

    //strat reserving
    vector<int> res;
    for(int i=0;i<requirment && eitherEndSeatNumber+i<=screens[screen_number]->col;i++){
        if(screens[screen_number]->seats[row][eitherEndSeatNumber+i]==false){
            res.push_back(eitherEndSeatNumber+i);
        }
    }
    if(res.size()==requirment){
        for(auto x:res){
            cout<<x<<" ";
        }
        cout<<endl;
        return;
    }

    //if reserving right of requirement is failed 
    //then start reserving from left side
    res.clear();
    for(int i=0;i<requirment && eitherEndSeatNumber-i>=1;i++){
        if(screens[screen_number]->seats[row][eitherEndSeatNumber-i]==false){
            res.push_back(eitherEndSeatNumber-i);
        }
    }
    reverse(res.begin(),res.end());
    if(res.size()==requirment){
        for(auto x:res){
            cout<<x<<" ";
        }
        cout<<endl;
        return;
    }

    //if reserving left side also faied
    //then return unsuccessful
    cout<<"unsuccessfull"<<endl;
}



//////////////////////////////////////////////////////////////////////////////
//just for printing the hall structure
//dont call this  when you submit this in online test
void test(bookMyShow B){
    for(auto x:B.screens){
        for(int i=1;i<x.second->row;i++){
            for(int j=1;j<x.second->col;j++){
                cout<<x.second->seats[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    cout<<"--------------------------"<<endl;
}
//////////////////////////////////////////////////////////////////////
int main()
{
    bookMyShow B;
    Parser p;
    vector<string> vs(9);
	vs[0]= "add-screen screen1 12 10 5 6 7 8 9";
    vs[1]="reserve-seat screen1 4 2 3 4 5 6 9 1";
    vs[2]="get-unreserved-seats screen1 4";
    vs[3]="suggest-contigious-seats screen1 2 4 8";
    vs[4]="add-screen screen2 14 14 5 6 7 8 9";
    vs[5]="reserve-seat screen2 8 2 3 4 5 6 9 14";
    vs[6]="get-unreserved-seats screen2 4";
    vs[7]="suggest-contigious-seats screen2 7 4 8";
    vs[8]="add-screen screen2 14 14 5 6 7 8 9";
    for(auto s:vs){
        pair<int,vector<string> > parsed=p.parse(s);
        int choice=parsed.first;
        vector<string> out=parsed.second;
        cout<<out[0]<<" : "<<endl;
        switch(choice){
            case 0: B.addScreen(out);break;
            case 1: B.reserverSeat(out);break;
            case 2: B.getUnreservedSeat(out);break;
            case 3: B.suggestContigiousSeats(out);break;
            default: cout<<"unsuccessfull"<<endl;break;
        }
        // test(B);
    }
	return 0;
}