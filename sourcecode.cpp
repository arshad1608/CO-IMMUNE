#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<time.h>

using namespace std;

int slots=0,slotno=10;
class user
{
    public:
    char user_name[25];
    char pword[10];
    char pno[10];
    char email[25];

    void input()
    {
        cout<<"USER NAME:";
        cin>>user_name;
        cout<<"NEW PASSWORD:";
        cin>>pword;
        cout<<"PHONE NUMBER:";
        cin>>pno;
        cout<<"EMAIL ID:";
        cin>>email;
    }
}admin{"admin","admin","098765432","admin@rec.in"};

class date
{
	public:
	int year;
	int month;
	int date;
	
	void checktime()
	{
		if(month== 1 || month== 3 || month== 5 || month== 7 || month== 8 || month== 10 || month== 12)
		{
			if(date>31)
			{
				month++;
				date=date-31;
			}
		}
		else if(month ==2)
		{
			if(date>28)
			{
				month++;
				date=date-28;
			}
		}
		else if(month == 4 || month == 6 || month == 9 || month == 11)
		{
			if(date>30)
			{
				month++;
				date=date-30;
			}
		}
		else if(month>12)
		{
			year++;
			month=month-12;
		}
	}
};

class vaccine
{
    public:
    char name[25];
    int age;
    char gender;
    char bgrp[5];
    char aadhar[12];
	int sno;
	date d;

    void input()
    {
        cout<<"Name:";
        cin>>name;
        cout<<"Age:";
        cin>>age;
        cout<<"Gender:";
        cin>>gender;
        cout<<"Blood Group:";
        cin>>bgrp;
        cout<<"aadhar number:";
        cin>>aadhar;
		time_t now=time(0);
		tm *ltm = localtime(&now);
		d.date=ltm->tm_mday;
		d.month=1+ltm->tm_mon;
		d.year=1900+ltm->tm_year;
    }
	
	void putdata()
	{
		cout<<"\nSLOT NUMBER:"<<sno;
		cout<<"\n-----------------\n";
		cout<<"Name:"<<name<<"\n";
        cout<<"Age:"<<age<<"\n";
        cout<<"Gender:"<<gender<<"\n";
        cout<<"Blood Group:"<<bgrp<<"\n";
        cout<<"aadhar number:"<<aadhar<<"\n";
		cout<<"slot date:"<<d.date<<":"<<d.month<<":"<<d.year<<"\n";
	}
	
}queue[25];

int f=-1,r=-1;

void write_access(char loginboy[25],char accessed[25])
{
	time_t my_time=time(NULL);
	fstream fin("accesslog.txt",ios::app);
	if(!fin)
		cout<<"ERROR OPENING THE FILE";
	else
	{
		fin<<"user:"<<loginboy<<" logged in on "<< ctime(&my_time)<<" accessed "<<accessed<<".\n";
		fin.close();
	}
}

void enqueue(vaccine v)
{
	if(r==slotno)
		cout<<"SLOTS FULL";
	else
	{
		queue[++r]=v;
		if(f==-1)
			f=0;
	}
}

void setdate()
{
	time_t now=time(0);
	tm *ltm = localtime(&now);
	queue[f].d.date+=7;
	queue[f].d.checktime();
}

void displayslots();
void gs()
{
	if(f==-1)
		cout<<"queue empty";
	else
	{
		ofstream fin("slots.dat",ios::binary | ios::app);
		while(f!=-1)
		{
			setdate();
			slots++;
			queue[f].sno=slots;
			fin.write((char*)&queue[f],sizeof(queue[f]));
			if(f==r)
				f=r=-1;
			else
				f++;
		}
		fin.close();
	}
}

void displayslots()
{
	vaccine v;
	ifstream fin("slots.dat",ios::binary);
	if(!fin)
		cout<<"error";
	else
	{
		while(fin.read((char*)&v,sizeof(v)))
		{
			
			v.putdata();
		}
		fin.close();
	}
}

void displayslotsu()
{
	vaccine v;
	ifstream fin("slots.dat",ios::binary);
	if(!fin)
		cout<<"error";
	else
	{
		while(!fin.eof())
			fin.read((char*)&v,sizeof(v));
		v.putdata();
	}
	fin.close();
}

void findslots(char a[25])
{
	vaccine v;
	ifstream f("slots.dat",ios::binary);
	if(!f)
		cout<<"error";
	else
	{
		while(f.read((char*)&v,sizeof(v)))
		{
			if(!strcmpi(a,v.name))
				v.putdata();
		}
	}
}

void signup() //to create user
{
    user u;
    ofstream f("user.dat",ios::binary);
    u.input();
    f.write((char*)&u,sizeof(u));
    f.close();
}

void menu()
{
	cout<<"1. INSERT USER\n2. GENERATE SLOTS\n3. ACCESS LOG\n4. CHANGE NUMBER OF SLOTS\n5. LOG OUT\n";
}

void useraccess()
{
	char text[5000];
	ifstream fin("accesslog.txt");
	if(!fin)
		cout<<"file not found"<<endl;
	else
		{
			while(!fin.eof())
				{
					fin.getline(text,5000,'\0');
					cout<<text;
				}
			fin.close();
		}
}

void change_slotno()
{
	cout<<"CURRENT NUMBER OF SLOTS:"<<slotno;
	cout<<"\nENTER THE NEW NUMBER OF SLOTS:";
	cin>>slotno;
}

int main()
{
	cout<<"DATA STRUCTURES MINI-PROJECT\n";
	cout<<"CO-IMMUNE\n";
	int ch1,ch2;
	char rep='y',x;
	cin>>x;
	top:
	system("cls");
	cout<<"WELCOME!\n\n";
	cout<<"1.LOGIN\n2.SIGNUP\n3.EXIT\n";
	cin>>ch2;
	char uid[25];
	if(ch2==1)
	{
		user u1;
		char pw[25];
		cout<<"USER NAME:";
		cin>>uid;
		cout<<"PASSWORD:";
		cin>>pw;
		
		if(!strcmp(uid,admin.user_name) && !strcmp(pw,admin.pword))
		{	
			while(rep=='y')
			{
				system("cls");
				cout<<"\nMENU\n";
				menu();
				cout<<"ENTER YOUR CHOICE:";
				cin>>ch1;
				if(ch1==1)
				{
					char erep='y';
					vaccine a;
					while(erep=='y')
					{
						a.input();
						enqueue(a);
						cout<<"INSERT ANOTHER PERSON? Y/N:";
						cin>>erep;
					}
					write_access(admin.user_name,"insert user ");
				}
				else if(ch1==2)
				{
					gs();
					displayslots();
					write_access(admin.user_name,"GENERATE SLOTS ");
				}
				else if(ch1==3)
					useraccess();
				else if(ch1==4)
				{
					change_slotno();
					write_access(admin.user_name,"CHANGE NUMBER OF SLOTS ");
				}
				else if(ch1==5)
					goto top;
				cout<<"\nDO YOU WANT TO CONTINUE? Y/N:";
				cin>>rep;
			}
		}
		else
		{
			ifstream fin("user.dat",ios::binary);
			if(!fin)
			cout<<"ERROR.";
			else
			while(!fin.eof())
			{
				fin.read((char*)&u1,sizeof(u1));
				if(!strcmp(uid,u1.user_name) && !strcmp(pw,u1.pword))
				{
					while(rep=='y')
					{
						system("cls");
						cout<<"\nMENU\n";
						cout<<"1.REGISTER SLOT\n2.SEARCH\n3.LOG OUT\n";
						cin>>ch1;
						if(ch1==1)
						{
							vaccine a;
							a.input();
							enqueue(a);
							gs();
							displayslotsu();
							write_access(u1.user_name,"REGISTER SLOTS ");
						}
						else if(ch1==2)
						{
							char name[25];
							cout<<"Enter Name to search:";
							cin>>name;
							findslots(name);
							write_access(u1.user_name,"FIND SLOTS ");
						}
						else if(ch1==3)
							goto top;
						cout<<"\nDO YOU WANT TO CONTINUE? Y/N:";
						cin>>rep;
					}
				}
			}
		}
	}
	else if(ch2==2)
	{
		signup();
		cout<<"\nSIGNED UP SUCCESSFULLY!!\n";
		goto top;
	}
	else if(ch2==3)
		exit(0);
	return 0;
}
