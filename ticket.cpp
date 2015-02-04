#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <ctime>
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

//-----------------------------读取车票数据---------------------
void ReadTicketInfo(Ticket * tic,int num){
    cout<<"正在读取数据，请稍等";
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
    cout<<endl<<"数据读取完成"<<endl;
}
//-----------------------------保存车票数据---------------------
void WriteTicketInfo(Ticket * tic,int num){
    cout<<"正在写入数据，请稍后";
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
    cout<<endl<<"数据保存完成"<<endl;
}
//-----------------------------售票-----------------------------
void SellTicket(){
    int num;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\t没有数据文件"<<endl;
	}else{
	    infile.getline(date,2046,'\n');
	    stringstream TicketNum(date);
		TicketNum>>num;
		infile.close();
		Ticket * ticket=new Ticket[num];
		ReadTicketInfo(ticket,num);
		int select;
		cout<<"|========================"<<endl;
		cout<<"|\t1 系统随机出票"<<endl;
		cout<<"|\t2 用户指定座位"<<endl;
		cout<<"|========================"<<endl;
		cout<<"请选择购票方式：";
		cin>>select;
		if(select==1){          //系统随机出票
		    cout<<endl<<"系统正在出票！请稍后"<<endl;
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
                cout<<"|   对不起！车票已经售完！ |"<<endl;
                cout<<"|==========================|"<<endl;
            }else{
                SYSTEMTIME sys;
                GetLocalTime( &sys );
                ticket[i].state=1;
                ticket[i].year=sys.wYear;
                ticket[i].month=sys.wMonth;
                ticket[i].day=sys.wDay;
                ticket[i].hour=sys.wHour;
                ticket[i].minute=sys.wMinute;
                ticket[i].second=sys.wSecond;
                int carriage = ticket[i].number/100;
                int seat = ticket[i].number-carriage*100;
                cout<<endl<<"购票成功！你的车票信息如下"<<endl;
                cout<<endl<<"|============================"<<endl;
                cout<<"| 购票日期:"<<ticket[i].year<<"年"<<ticket[i].month<<"月"<<ticket[i].day<<"日 "<<ticket[i].hour<<":"<<ticket[i].minute<<":"<<ticket[i].second<<endl;
                cout<<"|----------------------------"<<endl;
                cout<<"| 编号:"<<ticket[i].number<<"  车次:"<<ticket[i].train<<endl;
                cout<<"|----------------------------"<<endl;
                cout<<"| 车厢:"<<carriage<<"  座位:"<<seat<<endl;
                cout<<"|============================"<<endl;
                cout<<"请牢记你的车票编号！！！"<<endl;
            }
		}else{                  //用户指定座位
		    int UserCarriage;
            int UserSeat;
            boolean done=false;
            int i=0;
            while(!done){
                cout<<"请选择车厢号：";
                cin>>UserCarriage;
                cout<<"请选择座位号：";
                cin>>UserSeat;
                for(i=0; i<num; ++i){
                    int carriage=ticket[i].number/100;
                    int seat=ticket[i].number-carriage*100;
                    if(UserCarriage==carriage && UserSeat==seat){
                        if(ticket[i].state==1){
                            cout<<"对不起！该票已经出售！"<<endl;
                        }else{
                            SYSTEMTIME sys;
                            GetLocalTime( &sys );
                            ticket[i].state=1;
                            ticket[i].year=sys.wYear;
                            ticket[i].month=sys.wMonth;
                            ticket[i].day=sys.wDay;
                            ticket[i].hour=sys.wHour;
                            ticket[i].minute=sys.wMinute;
                            ticket[i].second=sys.wSecond;
                            ticket[i].state=1;
                            cout<<"购票成功！你的车票信息如下"<<endl;
                            done=true;
                        }
                        break;
                    }
                }
                if(i==num){
                    cout<<"对不起！没有该座位！"<<endl;
                }
            }
            cout<<endl<<"|============================"<<endl;
            cout<<"| 购票日期:"<<ticket[i].year<<"年"<<ticket[i].month<<"月"<<ticket[i].day<<"日 "<<ticket[i].hour<<":"<<ticket[i].minute<<":"<<ticket[i].second<<endl;
            cout<<"|----------------------------"<<endl;
            cout<<"| 编号:"<<ticket[i].number<<"  车次:"<<ticket[i].train<<endl;
            cout<<"|----------------------------"<<endl;
            cout<<"| 车厢:"<<UserCarriage<<"  座位:"<<UserSeat<<endl;
            cout<<"|============================"<<endl;
            cout<<"请牢记你的车票编号！！！"<<endl;
		}
		WriteTicketInfo(ticket,num);
	}
	cout<<"返回主菜单，";
	system("pause");
}
void QueryTicket(){
    int num;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\t没有数据文件"<<endl;
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
                Sleep(30);
                cout<<"| 编号:"<<ticket[i].number<<"  车次:"<<ticket[i].train<<endl;
                Sleep(30);
                cout<<"|----------------------------"<<endl;
                Sleep(30);
                cout<<"| 车厢:"<<carriage<<"  座位:"<<seat<<endl;
                Sleep(30);
                cout<<"|============================"<<endl;
                Sleep(30);
                cout<<endl;
                ++count;
            }
		}
		if(count==0){
            cout<<"票已经全部售完！"<<endl;
		}else{
            cout<<"还有"<<count<<"张票剩余！"<<endl;
		}
	}
	cout<<"返回主菜单，";
	system("pause");
}
void ChangeTicket(){
    int num;
    int number;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\t没有数据文件"<<endl;
	}else{
	    int i;
	    cout<<"请输入要改签的车票编号：";
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
                    cout<<"对不起！该票还没有出售，不能改签"<<endl;
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
            cout<<"对不起！车站没有售出该车票！"<<endl;
		}else{
            cout<<"改签成功"<<endl;
		}
	}
	system("pause");
}
void RefundTicket(){
    int num;
    char date[2046]={'\0'};
    ifstream infile("TicketInfo.txt");
    if(!infile){
        cout<<"没有数据文件"<<endl;
    }else{
        int number;
        int i;
        infile.getline(date,2046,'\n');
        stringstream Num(date);
        Num>>num;
        infile.close();
        Ticket * ticket=new Ticket[num];
        ReadTicketInfo(ticket,num);
        cout<<"请输入要退票的编号：";
        cin>>number;
        for(i=0; i<num; ++i){
            if(ticket[i].number==number){
                if(ticket[i].state==0){
                    cout<<"对不起！该票没有出售，不能退票"<<endl;
                }else{
                    ticket[i].state=0;
                    WriteTicketInfo(ticket,num);
                    cout<<"退票成功！"<<endl;
                }
                break;
            }else{
                continue;
            }
        }
        if(i==num){
            cout<<"对不起，这不是本车站售出的票，不能退票"<<endl;
        }
    }
    cout<<"返回主菜单，";
    system("pause");
}
int main()
{
    int choose;
    boolean exit=false;
    while(!exit){
        cout<<"|==================|"<<endl;
        cout<<"|     功能菜单     |"<<endl;
        cout<<"|==================|"<<endl;
        cout<<"|     1 买票       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     2 查询       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     3 退票       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     4 改签       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     5 退出       |"<<endl;
        cout<<"|==================|"<<endl;
        cout<<"选择功能：";
        cin>>choose;
        switch(choose){
            case 1:SellTicket();break;
            case 2:QueryTicket();break;
            case 3:RefundTicket();break;
            case 4:ChangeTicket();break;
            case 5:exit=true;break;
            default:cout<<"没有该功能"<<endl;system("pause");break;
        }
        system("cls");
    }
    return 0;
}
