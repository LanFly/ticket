#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <time.h>
using namespace std;

class Ticket{
public:
    int number;
    int state;
    string train;
    int carriage;
    int seat;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    Ticket(){};
    void TicketInit(int number,int state,string train,int carriage,int seat,int year,int month,int day,int hour,int minute,int second){
        this->number=number;
        this->state=state;
        this->train=train;
        this->carriage=carriage;
        this->seat=seat;
        this->year=year;
        this->month=month;
        this->day=day;
        this->hour=hour;
        this->minute=minute;
        this->second=second;
    }
};

//-----------------------------read ticket info---------------------
void ReadTicketInfo(Ticket * tic,int num){
    cout<<"Reading Ticket Info";
    const char* split="-";
	char* p;
	char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	int number;
    int state;
    string train;
    int carriage;
    int seat;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    infile.getline(date,2046,'\n');
    for(int i=0; i< num; ++i){
        infile.getline(date,2046,'\n');
        p=strtok(date,split);
        stringstream Number(p);
        Number>>number;
        p=strtok(NULL,split);
        stringstream State(p);
        State>>state;
        p=strtok(NULL,split);
        train=p;
        p=strtok(NULL,split);
        stringstream Year(p);
        Year>>year;
        p=strtok(NULL,split);
        stringstream Month(p);
        Month>>month;
        p=strtok(NULL,split);
        stringstream Day(p);
        Day>>day;
        p=strtok(NULL,split);
        stringstream Hour(p);
        Hour>>hour;
        p=strtok(NULL,split);
        stringstream Minute(p);
        Minute>>minute;
        p=strtok(NULL,split);
        stringstream Second(p);
        Second>>second;
        carriage=number/100;
        seat=number-carriage*100;
        tic[i].TicketInit(number,state,train,carriage,seat,year,month,day,hour,minute,second);
        cout<<".";
    }
    infile.close();
    cout<<endl<<"Read Ticket Info succeed"<<endl;
}
//-----------------------------write ticket info---------------------
void WriteTicketInfo(Ticket * tic,int num){
    cout<<"writing ticket info";
    ofstream outfile("TicketInfo.txt");
    outfile<<num<<endl;
    for(int i=0; i<num; ++i){
        outfile<<tic[i].number<<"-";
        outfile<<tic[i].state<<"-";
        outfile<<tic[i].train<<"-";
        outfile<<tic[i].year<<"-";
        outfile<<tic[i].month<<"-";
        outfile<<tic[i].day<<"-";
        outfile<<tic[i].hour<<"-";
        outfile<<tic[i].minute<<"-";
        outfile<<tic[i].second<<endl;
        cout<<".";
    }
    outfile.close();
    cout<<endl<<"writed ticket info succeed"<<endl;
}
//-----------------------------sell ticket-----------------------------
void SellTicket(){
    int num;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\tthere is no data file"<<endl;
	}else{
	    infile.getline(date,2046,'\n');
	    stringstream TicketNum(date);
		TicketNum>>num;
		infile.close();
		Ticket * ticket=new Ticket[num];
		ReadTicketInfo(ticket,num);
		int select;
		cout<<"|========================"<<endl;
		cout<<"|\t1 random ticket"<<endl;
		cout<<"|\t2 seat ticket"<<endl;
		cout<<"|========================"<<endl;
		cout<<"please select method=";
		cin>>select;
		if(select==1){            //random ticket
            int i=0;
            for(i=0; i<num; ++i){
                if(ticket[i].state==0)
                    break;
                else
                    continue;
            }
            if(i==num)
            {
                cout<<"|==========================|"<<endl;
                cout<<"|   there is no ticket     |"<<endl;
                cout<<"|==========================|"<<endl;
            }else{
                time_t now;
                struct tm *timenow;
                time(&now);
                timenow=localtime(&now);
                ticket[i].state=1;
                ticket[i].year=timenow->tm_year+1900;
                ticket[i].month=timenow->tm_mon;
                ticket[i].day=timenow->tm_mday;
                ticket[i].hour=timenow->tm_hour;
                ticket[i].minute=timenow->tm_min;
                ticket[i].second=timenow->tm_sec;
                int carriage = ticket[i].number/100;
                int seat = ticket[i].number-carriage*100;
                cout<<endl<<"this is your ticket info"<<endl;
                cout<<endl<<"|============================"<<endl;
                cout<<"| time:"<<ticket[i].year<<"-"<<ticket[i].month<<"-"<<ticket[i].day<<" "<<ticket[i].hour<<":"<<ticket[i].minute<<":"<<ticket[i].second<<endl;
                cout<<"|----------------------------"<<endl;
                cout<<"| number:"<<ticket[i].number<<"  train:"<<ticket[i].train<<endl;
                cout<<"|----------------------------"<<endl;
                cout<<"| carriage:"<<carriage<<"  seat:"<<seat<<endl;
                cout<<"|============================"<<endl;
            }
		}else{                  //seat ticket
		    int UserCarriage;
            int UserSeat;
            bool done=false;
            int i=0;
            while(!done){
                cout<<"please input carriage=";
                cin>>UserCarriage;
                cout<<"please input seat=";
                cin>>UserSeat;
                for(i=0; i<num; ++i){
                    int carriage=ticket[i].number/100;
                    int seat=ticket[i].number-carriage*100;
                    if(UserCarriage==carriage && UserSeat==seat){
                        if(ticket[i].state==1){
                            cout<<"the ticket has been sold"<<endl;
                        }else{
                            time_t now;
                            struct tm *timenow;
                            time(&now);
                            timenow=localtime(&now);
                            ticket[i].state=1;
                            ticket[i].year=timenow->tm_year+1900;
                            ticket[i].month=timenow->tm_mon;
                            ticket[i].day=timenow->tm_mday;
                            ticket[i].hour=timenow->tm_hour;
                            ticket[i].minute=timenow->tm_min;
                            ticket[i].second=timenow->tm_sec;
                            ticket[i].state=1;
                            cout<<"this is your ticket info"<<endl;
                            done=true;
                        }
                        break;
                    }
                }
                if(i==num){
                    cout<<"there is no such ticket"<<endl;
                }
            }
            cout<<endl<<"|============================"<<endl;
            cout<<"| time:"<<ticket[i].year<<"-"<<ticket[i].month<<"-"<<ticket[i].day<<" "<<ticket[i].hour<<":"<<ticket[i].minute<<":"<<ticket[i].second<<endl;
            cout<<"|----------------------------"<<endl;
            cout<<"| number:"<<ticket[i].number<<"  train:"<<ticket[i].train<<endl;
            cout<<"|----------------------------"<<endl;
            cout<<"| carriage:"<<UserCarriage<<"  seat:"<<UserSeat<<endl;
            cout<<"|============================"<<endl;
		}
		WriteTicketInfo(ticket,num);
	}
	cout<<endl;
    sleep(3);
}
void QueryTicket(){
    int num;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\tthere is no data file"<<endl;
	}else{
	    infile.getline(date,2046,'\n');
	    stringstream TicketNum(date);
		TicketNum>>num;
		infile.close();
		Ticket * ticket=new Ticket[num];
		ReadTicketInfo(ticket,num);
		int i=0;
		int count=0;

		for(i=0; i<num; ++i){
            if(ticket[i].state==0){
                int carriage = ticket[i].number/100;
                int seat = ticket[i].number-carriage*100;
                cout<<endl<<"|============================"<<endl;
                cout<<"| number:"<<ticket[i].number<<"  train:"<<ticket[i].train<<endl;
                cout<<"|----------------------------"<<endl;
                cout<<"| carriage:"<<carriage<<"  seat:"<<seat<<endl;
                cout<<"|============================"<<endl;
                cout<<endl;
                ++count;
            }
		}
		if(count==0){
            cout<<"there is no ticket to sell"<<endl;
		}else{
            cout<<"there have "<<count<<" ticket to sell"<<endl;
		}
	}
	cout<<endl;
    sleep(3);
}
void ChangeTicket(){
    int num;
    int number;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\tthere is no data file"<<endl;
	}else{
	    int i;
	    cout<<"please input ticket number you want to change=";
        cin>>number;
	    infile.getline(date,2046,'\n');
	    stringstream TicketNum(date);
		TicketNum>>num;
		infile.close();
		Ticket * ticket=new Ticket[num];
		ReadTicketInfo(ticket,num);
		for(i=0; i<num; ++i){
            if(ticket[i].number==number){
                if(ticket[i].state==0){
                    cout<<"the ticket has not been sold"<<endl;
                }else{
                    ticket[i].state=0;
                    WriteTicketInfo(ticket,num);
                    SellTicket();
                }
                break;
            }else{
                continue;
            }
		}
		if(i==num){
            cout<<"there is no such ticket"<<endl;
		}else{
            cout<<"your ticket has been change"<<endl;
		}
	}
    cout<<endl;
    sleep(3);
}
void RefundTicket(){
    int num;
    char date[2046]={'\0'};
    ifstream infile("TicketInfo.txt");
    if(!infile){
        cout<<"there is no data file"<<endl;
    }else{
        int number;
        int i;
        infile.getline(date,2046,'\n');
        stringstream Num(date);
        Num>>num;
        infile.close();
        Ticket * ticket=new Ticket[num];
        ReadTicketInfo(ticket,num);
        cout<<"please input the ticket number you want to refund=";
        cin>>number;
        for(i=0; i<num; ++i){
            if(ticket[i].number==number){
                if(ticket[i].state==0){
                    cout<<"the ticket has not been sold"<<endl;
                }else{
                    ticket[i].state=0;
                    WriteTicketInfo(ticket,num);
                    cout<<"your ticket has been refund"<<endl;
                }
                break;
            }else{
                continue;
            }
        }
        if(i==num){
            cout<<"there is no such ticket"<<endl;
        }
    }
    sleep(3);
}
int main()
{
    int choose;
    bool exit=false;
    while(!exit){
        cout<<"|======================|"<<endl;
        cout<<"|   input your choose  |"<<endl;
        cout<<"|======================|"<<endl;
        cout<<"|     1 Sell Ticket    |"<<endl;
        cout<<"|----------------------|"<<endl;
        cout<<"|     2 Query Ticket   |"<<endl;
        cout<<"|----------------------|"<<endl;
        cout<<"|     3 Refund Ticket  |"<<endl;
        cout<<"|----------------------|"<<endl;
        cout<<"|     4 Change Ticket  |"<<endl;
        cout<<"|----------------------|"<<endl;
        cout<<"|     5 exit           |"<<endl;
        cout<<"|======================|"<<endl;
        cout<<"your choose=";
        cin>>choose;
        switch(choose){
            case 1:SellTicket();break;
            case 2:QueryTicket();break;
            case 3:RefundTicket();break;
            case 4:ChangeTicket();break;
            case 5:exit=true;break;
            default:cout<<"there is no such method"<<endl<<endl;break;
        }
    }
    return 0;
}
