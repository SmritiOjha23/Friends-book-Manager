//**

// PROJECT FRIEND BOOK MANAGER
 
//**


//**

// INCLUDED HEADER FILES 

//**

#include <iomanip>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Friend
{
	private:
		char name[100];
		char email[50];
		int no_of_friends;
		int profile;
	public:
		Friend()
		{
			strcpy(name," ");
			strcpy(email," ");
			no_of_friends=0;
			profile=0;
		}
		void create();
		void view();
		void add();
		int search(char n[100]);
		void remove(char n[100]);
};
//**

// MAIN MENU FUNCTION

//**
void mainmenu()
{
	Friend obj;
	system("cls");

	system("Color 0E");
	char ch;
	while(1)
	{
		cout<<"\n\n\n\n\n\n\n";
		cout<<setw(50);
		for(int i=0;i<=99;i++)
			cout<<"*";
		cout<<"\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\tC:Create your profile\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\tS:Search a profile\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\tV:View your profile\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\tA:Add friend\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\tR:Remove friend\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\tQ:Quit\n\n";
		cout<<setw(50);
		for(int i=0;i<=99;i++)
		cout<<"*";
		
		cout<<"\n\n\n\n\n\n\n";
		cout<<setw(110)<<"Please enter your choice ";
		cin>>ch;
		switch(ch)
		{
			case 'C':
					obj.create();
					break;
			case 'S':
					char nn[100];
					cout<<"\n\n\tEnter friend to be searched: ";
					fflush(stdin);
					gets(nn);
					if(obj.search(nn)==1)
					{
						cout<<"\n\n\tFound\n";
						ifstream in ("friendlist.txt");
						while(in.eof()==0)
						{
							string st;
							getline(in,st);
							string word="";
							for(int i=0;i<st.size();i++)
							{
								if(st[i]==' ')
								{
									if(word==nn)
									{
										in.close();
										cout<<"\n\n\t"<<st<<"\n";
										break;
									}
									word="";
								}
								else
								{
									word=word+st[i];
								}
							}
						}
						in.close();
					}
					else if(obj.search(nn)==0)
						cout<<"\n\n\tNot Found\n";
					else
						cout<<"\n\n\tNo friends to search\n";
					break;
			case 'V':obj.view();
					break;				
			case 'A':obj.add();
					break;
			case 'R':
					char n[100];
					cout<<"\n\n\tEnter friend to be removed: ";
					fflush(stdin);
					gets(n);
					obj.remove(n);
					break;
			case 'Q':
					exit(0);
			default : cout<<"\n\n"<<setw(110)<<"INVALID CHOICE!!\n\n";
		}
	}		
}
//**

// CREATE PROFILE FUNCTION 

//**
void Friend::create()
{
	if(profile==0)
	{
		system("cls");
		fflush(stdin);
		cout<<"\n\n\tEnter your name: ";
		gets(name);
		fflush(stdin);
		cout<<"\n\n\tEnter your email: ";
		cin>>email;
		ofstream out ("friendlist.txt",ios::app | ios::out);
		if(no_of_friends==0)
		{
		out<<"S.No Name email-address\n";
		}
		out.close();
		profile++;
	}
	else
	{
		cout<<"\n\n"<<setw(110)<<"Profile can only be created once !!";
	}
}
//**

// FUNCTION TO ADD FRIEND 

//**
void Friend::add()
{
	char fname[100];
	char femail[50];
	system("cls");
	fflush(stdin);
	cout<<"\n\n\tEnter your Friend's name: ";
	gets(fname);
	fflush(stdin);
	if(search(fname)==1)
	{
		cout<<"\n\n"<<setw(110)<<"You cannot add friends with same initial name\n";
	}
	else
	{
		cout<<"\n\n\tEnter your friend's email: ";
		cin>>femail;
		ofstream out ("friendlist.txt",ios::app | ios::out);
		no_of_friends++;
		out<<no_of_friends<<" "<<fname<<" "<<femail<<endl;
		out.close();
	}	
}
//**

// FUNCTION TO VIEW PROFILE 

//**
void Friend::view()
{
	system("cls");
	string st;
	cout<<"\n\n\tYour Profile:";
	cout<<"\n\n\tName: "<<name<<endl;
	cout<<"\n\n\tEmail: "<<email<<endl;
	cout<<"\n\n\tNo of Friends: "<<no_of_friends<<endl;
	
	if(no_of_friends!=0)
	{
		cout<<"\n\n\tFriendlist: \n";
		ifstream in ("friendlist.txt");
		while(in.eof()==0)
		{
			getline(in,st);
			cout<<"\t"<<st<<endl;
		}
		in.close();
	}
}
//**

// FUNCTION TO SEARCH FRIEND 

//**
int Friend::search(char nn[100])
{
	system("cls");
	if(no_of_friends!=0)
	{
		ifstream in ("friendlist.txt");
		while(in.eof()==0)
		{
			string st;
			getline(in,st);
			string word="";
			for(int i=0;i<st.size();i++)
			{
				if(st[i]==' ')
				{
					if(word==nn)
					{
						in.close();
						return 1;
					}
					word="";
				}
				else
				{
					word=word+st[i];
				}
			}
		}
		in.close();
		return 0;
	}
	else
	{
		return -1;
	}	
}
//**

// FUNCTION TO REMOVE FRIEND 

//**
void Friend::remove(char nn[100])
{
	system("cls");
	if(search(nn)==1)
	{
		if(no_of_friends!=0)
		{
			ifstream in ("friendlist.txt");// read
			ofstream out ("temp.txt");// write
			while(in.eof()==0)
			{
				string st;
				getline(in,st);
				string word="";
				int flag=0;
				for(int i=0;i<st.size();i++)
				{
					if(st[i]==' ')
					{
						if(strcmp(nn,word.c_str())==0)
						{
							flag=1;
							cout<<"\n\n\tFRIEND REMOVED!!!";
							break;
						}
						word="";
					}
					else
					{
						word=word+st[i];
					}
				}
				if(flag==1)
				{
					getline(in,st);
				}
				out<<st<<"\n";
			}
			out.close();//temp close
			in.close();//friendlist close
			ofstream out1 ("friendlist.txt");
			out1.clear();
			ifstream in1 ("temp.txt");
			int count=0;
			while(in1.eof()==0)
			{
				string st;
				string word;
				getline(in1,st);
				if(count==0)
				{
					out1<<st<<"\n";
				}
				else if(count>0)
				{
					st=st+" ";
					if(st==" ")
						break;
					int c=0;
					for(int i=0;i<st.size();i++)
					{
						if(st[i]==' ')
						{
							c++;
							if(c==1)
							{
								out1<<count<<" ";
							}
							else
							{
								out1<<word<<" ";
							}
							word="";
						}
						else
						{
							word=word+st[i];
						}
					}
					out1<<"\n";
				}
				count++;
			}
			out1.close();
			in1.close();
			ofstream out2 ("temp.txt");
			out2.clear();
			out2.close();
			
			no_of_friends-=1;
		}
		else
		{
			cout<<"\n\n\tYou don't have any friends to delete\n";
		}
	}
	else if(search(nn)==0)
	{
		cout<<"\n\n\tThis friend is not present\n";
	}
	else
	{
		cout<<"\n\n\tNo friends to delete\n";
	}
}
//**

// MAIN FUNCTION

//**
int main()
{
	system("cls");

	system("Color 0A");
	cout<<"\n\n\n\n\n\n\n";
	
	cout<<setw(50);
	for(int i=0;i<=99;i++)
		cout<<"*";
		
	cout<<"\n\n";
		
    cout<<setw(110)<<"WELCOME TO FINDERRR\n\n";
    
    cout<<setw(125)<<"Designed and Coded By : Sparshi Gupta and Smriti Ojha\n\n\n";
    
    cout <<setw(105)<<"Submitted To:\n";
    cout <<setw(108)<<"Dr. Vaibhav Vyas\n\n";
 
   	cout<<setw(50);
	for(int i=0;i<=99;i++)
		cout<<"*";
		
	cout<<"\n\n\n\n\n\n\n\n\n";  
    cout <<setw(110)<<"Press any key to continue....."<<endl;
    getch();	
	mainmenu();
	return 0;
}