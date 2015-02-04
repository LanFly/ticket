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

//-----------------------------��ȡ��Ʊ����---------------------
void ReadTicketInfo(Ticket * tic,int num){
    cout<<"���ڶ�ȡ���ݣ����Ե�";
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
    cout<<endl<<"���ݶ�ȡ���"<<endl;
}
//-----------------------------���泵Ʊ����---------------------
void WriteTicketInfo(Ticket * tic,int num){
    cout<<"����д�����ݣ����Ժ�";
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
    cout<<endl<<"���ݱ������"<<endl;
}
//-----------------------------��Ʊ-----------------------------
void SellTicket(){
    int num;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\tû�������ļ�"<<endl;
	}else{
	    infile.getline(date,2046,'\n');
	    stringstream TicketNum(date);
		TicketNum>>num;
		infile.close();
		Ticket * ticket=new Ticket[num];
		ReadTicketInfo(ticket,num);
		int select;
		cout<<"|========================"<<endl;
		cout<<"|\t1 ϵͳ�����Ʊ"<<endl;
		cout<<"|\t2 �û�ָ����λ"<<endl;
		cout<<"|========================"<<endl;
		cout<<"��ѡ��Ʊ��ʽ��";
		cin>>select;
		if(select==1){          //ϵͳ�����Ʊ
		    cout<<endl<<"ϵͳ���ڳ�Ʊ�����Ժ�"<<endl;
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
                cout<<"|   �Բ��𣡳�Ʊ�Ѿ����꣡ |"<<endl;
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
                cout<<endl<<"��Ʊ�ɹ�����ĳ�Ʊ��Ϣ����"<<endl;
                cout<<endl<<"|============================"<<endl;
                cout<<"| ��Ʊ����:"<<ticket[i].year<<"��"<<ticket[i].month<<"��"<<ticket[i].day<<"�� "<<ticket[i].hour<<":"<<ticket[i].minute<<":"<<ticket[i].second<<endl;
                cout<<"|----------------------------"<<endl;
                cout<<"| ���:"<<ticket[i].number<<"  ����:"<<ticket[i].train<<endl;
                cout<<"|----------------------------"<<endl;
                cout<<"| ����:"<<carriage<<"  ��λ:"<<seat<<endl;
                cout<<"|============================"<<endl;
                cout<<"���μ���ĳ�Ʊ��ţ�����"<<endl;
            }
		}else{                  //�û�ָ����λ
		    int UserCarriage;
            int UserSeat;
            boolean done=false;
            int i=0;
            while(!done){
                cout<<"��ѡ����ţ�";
                cin>>UserCarriage;
                cout<<"��ѡ����λ�ţ�";
                cin>>UserSeat;
                for(i=0; i<num; ++i){
                    int carriage=ticket[i].number/100;
                    int seat=ticket[i].number-carriage*100;
                    if(UserCarriage==carriage && UserSeat==seat){
                        if(ticket[i].state==1){
                            cout<<"�Բ��𣡸�Ʊ�Ѿ����ۣ�"<<endl;
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
                            cout<<"��Ʊ�ɹ�����ĳ�Ʊ��Ϣ����"<<endl;
                            done=true;
                        }
                        break;
                    }
                }
                if(i==num){
                    cout<<"�Բ���û�и���λ��"<<endl;
                }
            }
            cout<<endl<<"|============================"<<endl;
            cout<<"| ��Ʊ����:"<<ticket[i].year<<"��"<<ticket[i].month<<"��"<<ticket[i].day<<"�� "<<ticket[i].hour<<":"<<ticket[i].minute<<":"<<ticket[i].second<<endl;
            cout<<"|----------------------------"<<endl;
            cout<<"| ���:"<<ticket[i].number<<"  ����:"<<ticket[i].train<<endl;
            cout<<"|----------------------------"<<endl;
            cout<<"| ����:"<<UserCarriage<<"  ��λ:"<<UserSeat<<endl;
            cout<<"|============================"<<endl;
            cout<<"���μ���ĳ�Ʊ��ţ�����"<<endl;
		}
		WriteTicketInfo(ticket,num);
	}
	cout<<"�������˵���";
	system("pause");
}
void QueryTicket(){
    int num;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\tû�������ļ�"<<endl;
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
                cout<<"| ���:"<<ticket[i].number<<"  ����:"<<ticket[i].train<<endl;
                Sleep(30);
                cout<<"|----------------------------"<<endl;
                Sleep(30);
                cout<<"| ����:"<<carriage<<"  ��λ:"<<seat<<endl;
                Sleep(30);
                cout<<"|============================"<<endl;
                Sleep(30);
                cout<<endl;
                ++count;
            }
		}
		if(count==0){
            cout<<"Ʊ�Ѿ�ȫ�����꣡"<<endl;
		}else{
            cout<<"����"<<count<<"��Ʊʣ�࣡"<<endl;
		}
	}
	cout<<"�������˵���";
	system("pause");
}
void ChangeTicket(){
    int num;
    int number;
    char date[2046]={'\0'};
	ifstream infile("TicketInfo.txt");
	if(!infile)
	{
		cout<<"\tû�������ļ�"<<endl;
	}else{
	    int i;
	    cout<<"������Ҫ��ǩ�ĳ�Ʊ��ţ�";
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
                    cout<<"�Բ��𣡸�Ʊ��û�г��ۣ����ܸ�ǩ"<<endl;
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
            cout<<"�Բ��𣡳�վû���۳��ó�Ʊ��"<<endl;
		}else{
            cout<<"��ǩ�ɹ�"<<endl;
		}
	}
	system("pause");
}
void RefundTicket(){
    int num;
    char date[2046]={'\0'};
    ifstream infile("TicketInfo.txt");
    if(!infile){
        cout<<"û�������ļ�"<<endl;
    }else{
        int number;
        int i;
        infile.getline(date,2046,'\n');
        stringstream Num(date);
        Num>>num;
        infile.close();
        Ticket * ticket=new Ticket[num];
        ReadTicketInfo(ticket,num);
        cout<<"������Ҫ��Ʊ�ı�ţ�";
        cin>>number;
        for(i=0; i<num; ++i){
            if(ticket[i].number==number){
                if(ticket[i].state==0){
                    cout<<"�Բ��𣡸�Ʊû�г��ۣ�������Ʊ"<<endl;
                }else{
                    ticket[i].state=0;
                    WriteTicketInfo(ticket,num);
                    cout<<"��Ʊ�ɹ���"<<endl;
                }
                break;
            }else{
                continue;
            }
        }
        if(i==num){
            cout<<"�Բ����ⲻ�Ǳ���վ�۳���Ʊ��������Ʊ"<<endl;
        }
    }
    cout<<"�������˵���";
    system("pause");
}
int main()
{
    int choose;
    boolean exit=false;
    while(!exit){
        cout<<"|==================|"<<endl;
        cout<<"|     ���ܲ˵�     |"<<endl;
        cout<<"|==================|"<<endl;
        cout<<"|     1 ��Ʊ       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     2 ��ѯ       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     3 ��Ʊ       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     4 ��ǩ       |"<<endl;
        cout<<"|------------------|"<<endl;
        cout<<"|     5 �˳�       |"<<endl;
        cout<<"|==================|"<<endl;
        cout<<"ѡ���ܣ�";
        cin>>choose;
        switch(choose){
            case 1:SellTicket();break;
            case 2:QueryTicket();break;
            case 3:RefundTicket();break;
            case 4:ChangeTicket();break;
            case 5:exit=true;break;
            default:cout<<"û�иù���"<<endl;system("pause");break;
        }
        system("cls");
    }
    return 0;
}
