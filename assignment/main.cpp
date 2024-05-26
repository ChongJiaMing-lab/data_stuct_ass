#include<iostream>
using namespace std;
#include<string>
class menu
{
	private:
		int choice, choice1;
		string *id, *name, time, course;
		float *gpa;
		int size;
	public:
		void data(string *id, string *name, float *gpa, int size)
		{
			this->size = size;
			this->id = id;
			this->name = name;
			this->gpa = gpa;
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
		void add_students()
		{
			int addnum;
			cout<<"How many student you want to add ? ";
			cin>>addnum;
			string add_id[addnum], n[addnum];
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
			}
		}
		
		void view_students()
		{
			cout<<"ID"<<endl;
			for(int i=0; i<size; i++)
			{
				cout<<id[i]<<" ";
				cout<<name[i]<<" ";
				cout<<gpa[i]<<" "<<endl;
			}
			system("PAUSE");
		}
	
};
int main()
{
	string i[] = {"1","2","3", "4"};
	string j[] = {"ming","yong","leong", "elysa"};
	float g[] = {1.2, 1.3, 1.4, 1.5};
	int size = sizeof(i) / sizeof(i[0]);
	menu m;
	m.data(i, j, g, size);
	while(1)
	m.main_menu();
}
