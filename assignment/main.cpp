#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<sstream>
using namespace std;

tm getTime(string time)
{
		char d;
		int day,month,year;
		tm time_struct;

		istringstream iss(time);
		iss >> day>> d >> month>> d >>year;

		time_struct.tm_year = year ; // Years since 1900
		time_struct.tm_mon = month ;    // Months are 0-based
		time_struct.tm_mday = day; 

		return time_struct;
}

struct Node {
    int data;
	string name,id,course;
	float gpa;
    Node* next;
	tm time;

	Node(string id,string name,float gpa,string course,string timer)
	{
		this->id = id;
		this->name = name;
		this->gpa = gpa;
		this->course = course;
		this->time = getTime(timer);
	}
};

class menu
{
	private:
		Node* head;
		int choice, choice1;
		string *id, *name ,*course,*time;
		float *gpa;
		int size;
	public:
		menu()
		{
			head = NULL;
		}

		void data(string *id, string *name, float *gpa, int size,string *course,string *time)
		{
			this->size = size;
			this->id = id;
			this->name = name;
			this->gpa = gpa;
			this->course = course;
			this->time = time;

				for(int z=0;z<size;z++)
				{
					add_link(id[z],name[z],gpa[z],course[z],time[z]);
				}
		}
		void main_menu()
		{
			cout<<"----------------------------------------"<<endl;
			cout<<"Welcome to student management system"<<endl;
			cout<<"----------------------------------------"<<endl;
			cout<<"1. View/Add students"<<endl;
			cout<<"2. Set 1 - (Cocktail Sort + Ubiquitous Binary Search)"<<endl;
			cout<<"3. Set 2 - (Pancake Sort + Jump Search)"<<endl;
			cin>>choice;
			switch(choice)
			{
				case 1:{
					students();
					break;
				}
				case 2:{
					break;
				}
				case 3:{
					
					break;
				}
			}
		}
		void students()
		{
			cout<<"==========================="<<endl;
			cout<<"Managing the students"<<endl;
			cout<<"==========================="<<endl;
			cout<<"What you want to do..."<<endl;
			cout<<"1. Add new student"<<endl;
			cout<<"2. View students information"<<endl;
			cout<<"3. Back"<<endl;
			cout<<">>>>>";
			cin>>choice1;
			switch(choice1)
			{
				case 1:{
					add_students();
					break;
				}
				case 2:{
					view_students();
					break;
				}
				case 3:{
					return;
					break;
				}
			}
		}

		void add_link(string id,string name,float gpa,string course,string time)
		{
			Node *new_node = new Node(id,name,gpa,course,time);
			if(!head)
			{
				head = new_node;
				return;
			}

			Node *current = head;
			while(current->next)
			{
				current = current->next;
			}
			current->next = new_node;
		}

		void view_students()
		{
			Node *current = head;
			while(current)
			{
				cout<<"Studend id: "<<current->id<<
				"\nStudent Name: "<<current->name<<
				"\nStudent GPA: "<<current->gpa<<
				"\nCourse: "<<current->course<<
				"\nJoin Time: "<<current->time.tm_mday<<"-"<<current->time.tm_mon<<"-"<<current->time.tm_year<<endl<<endl;
				current = current->next;
			}
		}

		void add_students()
		{
			int addnum;
			cout<<"How many student you want to add ? ";
			cin>>addnum;
			string add_id[addnum], n[addnum],gettime[addnum];
			float g[addnum];
			for(int i=0; i<addnum; i++)
			{
				cout<<"Enter new student information"<<endl<<endl;
				cout<<"ID : ";
				cin>>add_id[i];
				cout<<"Name : ";
				cin>>n[i];
				cout<<"GPA : ";
				cin>>g[i];
				cout<<"Course : ";
				cin.ignore();
				getline(cin,course[i]);
				cout<<"Join Time : ";
				cin>>gettime[i];

				add_link(add_id[i],n[i],g[i],course[i],time[i]);
			}
		}
		
		// void view_students()
		// {
		// 	cout<<"ID"<<endl;
		// 	for(int i=0; i<size; i++)
		// 	{
		// 		cout<<id[i]<<" ";
		// 		cout<<name[i]<<" ";
		// 		cout<<gpa[i]<<" "<<endl;
		// 	}
		// 	system("PAUSE");
		// }
	
};
int main()
{

	string i[] = {"1","2","3", "4"};
	string j[] = {"ming","yong","leong", "elysa"};
	float g[] = {1.2, 1.3, 1.4, 1.5};
	string course[] = {"Diploma in IT","Diploma in IT","Diploma in IT","Diploma in IT"};
	string timee[] = {"12-2-2024","14-12-2023","22-5-2024","27-6-2024"};


	int size = sizeof(i) / sizeof(i[0]);
	menu m;
	int choice;

	// for(int z=0;z<size;z++)
	// {
	// 	m.add_link(i[z],j[z],g[z]);
	// }

	m.data(i, j, g, size,course,timee);

	m.main_menu();
	cout<<"Do you want to continue?(1=Yes, Other = No) : ";
	cin>>choice;

	while(choice == 1)
	{
		m.main_menu();
		cout<<"Do you want to continue?(1=Yes, Other = No)";
		cin>>choice;
	}
}
