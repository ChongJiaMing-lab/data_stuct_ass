#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib> 
#include <fstream>
#include<string>
#include<conio.h>
#include <ctime>
#include <sstream>
#include<unistd.h>
#include<vector>
#include <cmath>
#define al 5
#define rental 50
#define limit 1000
using namespace std;

string current_user,owner_block;
const int MAX_OWNERS = 100;
 
struct Board
{
	string notice;
	string bullet_TO,bullet_date,bullet_title;
	int num;
};


struct owner_info{
	string owner_name;
	string owner_ic;
	string owner_tel_no;
	string unit;
	string owner_un;
	string owner_pass;
};

struct node
{
  owner_info oi;
  struct node *next;
};

struct nodeTenant
{
	nodeTenant *next;
	string name,ic,tel,block;
};


void owner_login();
void owner_menu();
void inputpasswrd();
void inputPassword1(string &str, int size);
void sendReminderToCustomer(const string &reminder);
void admin_menu();
void tenant_menu();
void bullet_board_display();
void read_board();
void write_board();
void delete_notice();
void inputpasswrd();
void tenants_login();
void admin_passwd();
void sa_login();
void inputPassword(string &str, int size);
void visitor_menu();
void access();
string gettime();


class Search_Admin
{
	protected:
		int i;
		string owner_name, owner_ic, owner_tel_no;
		string unit, owner_un, owner_pass;
		
		string select_name[limit], select_ic[limit], select_tel[limit];
		string select_unit[limit], select_un[limit], select_pass[limit];
		owner_info oi_admin[limit];
	public:
		 void search_owner()
			 {
			 	i=0;
			 	fstream fread("owner.txt");
   				if (!fread)
    			{
        			cout << "Failed to read the file" << endl;
        			return;
  				}
  				
  				string line;
		 		while (getline(fread, line)) 
		 		{
            		istringstream iss(line);

          		  	getline(iss, owner_name);
          		  	getline(fread, owner_ic);
          		  	getline(fread, owner_tel_no);
					getline(fread, unit);
					getline(fread, owner_un);
					getline(fread, owner_pass);
					
					oi_admin[i].owner_name = owner_name;
					oi_admin[i].owner_ic = owner_ic;
					oi_admin[i].owner_tel_no = owner_tel_no;
					oi_admin[i].unit = unit;
					oi_admin[i].owner_un = owner_un;
					oi_admin[i].owner_pass = owner_pass;
					
       				select_name[i] = owner_name;
      		 		select_ic[i] = owner_ic;
      		 		select_tel[i] = owner_tel_no;
      		 		select_unit[i] = unit;
      		 		select_un[i] = owner_un;
      				select_pass[i] = owner_pass;
    				i++;
  			 	}
			fread.close();	
			}
};

class Admin:public Search_Admin
{
	
	public:
		void admin_menu();
		void add_owner()
		{
			system("cls");
			cout<<"==============================="<<endl<<endl;
			cout<<"  Adding a new owner..."<<endl<<endl;
			cout<<"==============================="<<endl; 
			fflush(stdin); 
			cout<<"Enter the name         |";
			getline(cin, owner_name);
			fflush(stdin);
			cout<<"Enter the IC no        |";
			cin>>owner_ic;
			fflush(stdin);
			cout<<"Enter telephone number |";
			cin>>owner_tel_no;
			cout<<"Enter unit           |";
			cin>>unit;
			fflush(stdin);
			cout<<"\nSet a owner username to ["<<owner_name<<"] : ";
			cin>>owner_un;
			cout<<"Set a password to ["<<owner_un<<"] : ";
			cin>>owner_pass;
			
			fstream fwrite("owner.txt", ios::app);
			if(!fwrite)
			{
				cout<<"Failed to add the owner!!!"<<endl; 
			}
			
			fwrite<<owner_name<<endl<<owner_ic<<endl<<owner_tel_no<<endl
			<<unit<<endl<<owner_un<<endl<<owner_pass<<endl;
			cout<<"\nSuccessful add the owner "<<owner_name<<endl<<endl;
			fwrite.close();
			system("pause");
			system("cls");
		}
		
   		void edit_owner() 
		{
			system("cls");
   			string new_record, new_name, new_ic, new_tel;
   			bool found=false;
   			cout<<"==============================="<<endl<<endl;
			cout<<"  Editing owner..."<<endl<<endl;
			cout<<"==============================="<<endl;
    		cin.ignore();  
  		 	cout << "Enter the owner name that you want to edit : ";
  			getline(cin, new_record);
  			for(int a=0; a<i; a++)
  			{
  				if(new_record == select_name[a])
					found = true;
			}
			if(!found)
			{
				cout<<"Didn't found the owner ["<<new_record<<"]"<<endl<<endl;
  					system("pause");
  					system("cls");
  					return;
			}
  			cout<<"Please enter the new info for "<<new_record<<endl;
  			cout<<"------------------------------"<<endl;
  		  	cout << "Enter a new owner name :";
  		  	getline(cin, new_name);
 		  	cout << "Enter a new ic : ";
  		  	cin>>new_ic;
  		 	cout << "Enter a new telephone : ";
  		 	cin>>new_tel;
  		 	cout<<"------------------------------"<<endl;

  			ofstream file_delete("owner.txt", ios::trunc);
   			file_delete.close();

    		fstream fwrite("owner.txt", ios::app);

   		 	for (int j=0; j<i; j++) 
			{
        	if (new_record == select_name[j]) 
			{
            select_name[j] = new_name;//replace select_name with new data 
            select_ic[j] = new_ic;
            select_tel[j] = new_tel;
            cout << "The owner info is edited." << endl;
        	}

        	fwrite << select_name[j] << endl << select_ic[j] << endl << select_tel[j] << endl
			<<select_unit[j]<<endl<<select_un[j]<<endl<<select_pass[j]<<endl;
   		 	}

  	  	fwrite.close();
  	  	system("pause");
  	  	system("cls");
		}

		void delete_owner()
		{
			int delete_choice, found;
			string delete_name;
			bool f=false;
			system("cls");
			cout<<"How you want to delete"<<endl;
			cout<<"Notice : The DELETED owner can't be recovery !!!"<<endl;
			cout<<"So PLEASE be careful when make decision."<<endl;
			cout<<"1. Single owner"<<endl;
			cout<<"2. All owner"<<endl;
			cout<<"3. Back"<<endl;
			cout<<">>>>>>>>>";
			cin>>delete_choice;
			
			if(delete_choice == 1)
			{
				cout<<"Enter the name that you want to delete : ";
				cin>>delete_name;
  					
  			for(int j=0; j<i; j++)
  			{
  				if(delete_name == select_name[j])
  				{
  					found = j;//get the specific name that wanted to delete
  					f= true;//found the specific name
  					continue;
				}		
    		}
    		if(!f)
    		{
				cout<<"Didn't found the owner [\033[33m"<<delete_name<<"\033[0m]"<<endl;
  				system("pause");
  				system("cls");
  				return;
			}
    		
    		for(int k=found; k<i-1; k++)
			{
				select_name[k] = select_name[k+1];
				select_ic[k] = select_ic[k+1];
				select_tel[k] = select_tel[k+1];//let next arr replace with previous arr
			}
			i-=1;//deleted 1 thing
			ofstream file_delete("owner.txt", ios::trunc);//1. empty the file first
			if(!file_delete)
			{
				cout<<"The file is not found !!!"<<endl;
				return;
			}
			file_delete.close();
			
			fstream fopen("owner.txt", ios::app);//after that write the data that stored in array
			for(int l=0; l<i; l++)
			{
				fopen<<select_name[l]<<endl<<select_ic[l]<<endl<<select_tel[l]<<endl
				<<select_unit[l]<<endl<<select_un[l]<<endl<<select_pass[l]<<endl;
			}
			fopen.close();
			cout<<"The admin [\033[33m"<<delete_name<<"\033[0m] has been deleted."<<endl; 
			}//end if delete_choice ==1

			else if(delete_choice == 2)
			{
				ofstream file_delete("owner.txt", ios::trunc);//delete all data in file
				file_delete.close();
				cout<<"All owner is deleted."<<endl;
			}
			
			else if(delete_choice == 3)
			{ system("cls");return;
			}
				
			else
				{
					cout<<"Invalid choice !!!"<<endl;
				}
				system("pause");
				system("cls");
			 }
			 
			 void view_feedback()
			 {
			 	string n, e, m;
				int count;
				string nn[limit], ee[limit], mm[limit];
				int rr[limit];
			 	fstream fread("feedback.txt");
				if(!fread)
				{
					cout<<"Failed to read file!!!"<<endl;
				}
				system("cls");
				cout<<"--------FEEDBACK--------"<<endl;
				string line;
				count =0;
			while (getline(fread, n) && getline(fread, e) && getline(fread, m))
			{
    		cout << n << "(" << e << ") says : " << m << endl;

    		nn[count] = n;
    		ee[count] = e;
    		mm[count] = m;
    		count++;
			}
				fread.close();
				ofstream reset("feedback.txt", ios::trunc);
				reset.close();
				fstream rewrite("feedback.txt", ios::app);
				for(int i=0; i<count; i++)
				{
					rewrite<<nn[i]<<endl<<ee[i]<<endl<<mm[i]<<endl;
				}
				rewrite.close();
				system("pause");
				system("cls");
			 }
			 
			void View_Board()
            {
                system("cls");
				Board b;
				int choice,del;
				bullet_board_display();
				cout<<"1. Read Board"<<endl;
				cout<<"2. Write new notice"<<endl;
				cout<<"3. Delete notice"<<endl;
				cout<<"Enter choice : ";
				cin>>choice;
				if(choice == 1)
				{
					bullet_board_display();
					read_board();
		
				}
				else if(choice == 2)
				{
					bullet_board_display();
					write_board();
				}
				else if(choice == 3)
				{
					bullet_board_display();
					delete_notice();
				}
				
				cout << "\n\nPress any key to continue..." <<endl;
   				 _getch();
             }
             
             void view_visitor()
				{
					fstream fread("visitor_request.txt");
					int count=0;
					string line;
					while(getline(fread,line))
					{
						switch(count)
						{
							case 0:cout<<"Name         : "<<line<<endl;break;
							case 1:cout<<"Phone Number : "<<line<<endl;break;
							case 2:cout<<"IC Number    : "<<line<<endl;break;
							case 3:cout<<"Visit Unit   : "<<line<<endl;break;
							case 4:cout<<"Date         : "<<line<<endl;count=0;break;
						}
						count++;
					}
					fread.close();
				}
				int owner_bubble_sort(int size) 
				{
				    for (int step = 0; step < size - 1; ++step) 
					{
				        for (int i = 0; i < size - step - 1; ++i) 
						{
				            if (oi_admin[i].owner_name > oi_admin[i + 1].owner_name) 
							{
				                owner_info temp = oi_admin[i];
				                oi_admin[i] = oi_admin[i + 1];
				                oi_admin[i + 1] = temp;
				            }
				        }
				    }
				}
   				
				void display_owner()
				{
					cout<<"After sorting"<<endl;
					cout << "------------------------------------" << endl;
					 for (int j = 0;j < i; ++j)
					 {
						cout <<j+1<<endl;
						cout << "------------------------------------" << endl;
					    cout << "Owner Name           |" << oi_admin[j].owner_name << endl;
					    cout << "Owner IC             |" << oi_admin[j].owner_ic<< endl;
					    cout << "Owner Telephone No   |" << oi_admin[j].owner_tel_no  << endl;
					    cout << "Unit                 |" << oi_admin[j].unit<< endl;
					    cout << "------------------------------------" << endl << endl;
					}
				}
				
			int owner_binary(int size, string u) 
			{
			    int low = 0;
			    int high = size;
			    while (low <= high) 
				{
			        int mid = low + (high - low) / 2;
        			if (oi_admin[mid].owner_name == u) 
					{
						cout << "The owner "<<u<<" is found"<<endl;
			            cout << "------------------------------------" << endl;
						cout << "Owner Name           |" << oi_admin[mid].owner_name << endl;
						cout << "Owner IC             |" << oi_admin[mid].owner_ic<< endl;
						cout << "Owner Telephone No   |" << oi_admin[mid].owner_tel_no  << endl;
						cout << "Unit                 |" << oi_admin[mid].unit<< endl;
						cout << "------------------------------------" << endl;
						return 1;
        			} 
					else if (oi_admin[mid].owner_name < u) 
					{
			            low = mid + 1;
			        } 
					else {
			            high = mid - 1;
			        }
				}
			 return -1;
			}
	void view_tenants();
	friend void view_owner();
};

void Admin::view_tenants()
{
	system("cls");
	int tenant_c=1;
	string t_name, t_tel, t_ic, t_unit;
	cout<<"======================"<<endl;
	cout<<"Tenant(s) Info"<<endl;
	cout<<"======================"<<endl<<endl;
	fstream fread("UserInformation.txt");
	if(!fread)
	{
		cout<<"Failed to get the tenant list!!!"<<endl;
	}
	string line;
	while (getline(fread, line)) 
	{
		cout<<"test"<<endl;
		
    	istringstream iss(line);

        getline(iss, t_name);
        getline(fread, t_tel);
        getline(fread, t_ic);
        getline(fread, t_unit);
        cout<<"\\\\\\\\\\\\Tenant "<<tenant_c++<<endl;
		cout<<"------------------------------------"<<endl;
        cout << "Tenant Name           |"<<t_name <<endl;
        cout << "Tenant IC             |"<<t_tel<<endl;
        cout << "Tenant Telephone. No  |"<<t_ic<<endl;
        cout<<"Tenant Unit             |"<<t_unit<<endl;
        cout<<"------------------------------------"<<endl<<endl;
     }
        cout<<"------------------------------------"<<endl;
		fread.close();
		system("pause");
		system("cls");	
}

void view_owner() {
    system("cls");
    int owner_c = 1;
    cout<<"======================"<<endl;
    cout<<"Owner(s) Info" << endl;
    cout<<"======================"<<endl<<endl;

    fstream fread("owner.txt");
    if(!fread) {
        cout<<"Failed to get the admin list"<<endl;
        return;
    }

    node *head = NULL;
    node *current = NULL;

    string line;
    while (getline(fread, line)) {
        owner_info oi;
        oi.owner_name = line;

        if (!getline(fread, oi.owner_ic)) break;
        getline(fread, oi.owner_tel_no);
        getline(fread, oi.unit);
        getline(fread, oi.owner_un);
        getline(fread, oi.owner_pass);

        node *new_node = new node;
        new_node->oi = oi;
        new_node->next = NULL;

        if (!head) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }
    fread.close();

    node *temp = head;
    while (temp != NULL) {
        cout<<"Owner "<<owner_c++<<endl;
        cout<<"------------------------------------"<<endl;
        cout<<"Owner Name           |"<<temp->oi.owner_name<<endl;
        cout<<"Owner IC             |"<<temp->oi.owner_ic<<endl;
        cout<<"Owner Telephone No   |"<<temp->oi.owner_tel_no<<endl;
        cout<<"------------------------------------"<<endl<<endl;
        temp = temp->next;
    }
    cout<<"------------------------------------"<<endl;

    delete head;
	delete temp;
	owner_c -= 1;
	int search_o_choice;
	cout<<"1.Sort owner with name"<<endl;
	cout<<"2.Search owner with name"<<endl;
	cout<<"3.Back"<<endl;
	cin>>search_o_choice;
	Admin a;
	if(search_o_choice == 1)
	{
		a.search_owner();
		a.owner_bubble_sort(owner_c);
		a.display_owner();
	}
	else if(search_o_choice ==2)
	{
		string name;
		cout<<"Enter the name to search:"<<endl;
		cin>>name;
		a.search_owner();
		a.owner_bubble_sort(owner_c);
		int result_b = a.owner_binary(owner_c, name);
		if(result_b == -1)
		       	cout<<"Owner "<<name<<" is not found."<<endl;
	}
    system("pause");
    system("cls");
}

class owner
{
private:
	nodeTenant *head, *temp,*prev,*vhead,*vtemp;
public:
    void editAndViewTenantsInfo();
    string tenant_name, tenant_ic, tenant_tel_no,tenant_block;
    string select_name[al], select_ic[al], select_tel[al];
    int i;
    string visitor_name, visitor_ic, visitor_tel_no, visitor_request_block;

    owner()
    {
        cout << "\033[1;33m----------------------------------\033[0m" << endl << endl;
        cout << "\033[1;33m       Welcome To Owner Menu      \033[0m" << endl << endl;
        cout << "\033[1;33m----------------------------------\033[0m" << endl << endl;
        
        ifstream read("UserInformation.txt");
        while(getline(read,tenant_name))
        {
        	getline(read,tenant_tel_no);
        	getline(read,tenant_ic);
        	getline(read,tenant_block);
        	
        	add_node(tenant_name, tenant_ic, tenant_tel_no,tenant_block);
		}
        read.close();
    }
	void refresh()
	{
		head = NULL;
		
		ifstream read("UserInformation.txt");
        while(getline(read,tenant_name))
        {
        	getline(read,tenant_tel_no);
        	getline(read,tenant_ic);
        	getline(read,tenant_block);
        	
        	add_node(tenant_name, tenant_ic, tenant_tel_no,tenant_block);
		}read.close();
	}
    void ow_menu();
    
    void add_node(string n,string ic,string tel,string block)
    {
    	if (head == NULL)
    	{
    		head = new nodeTenant;
			head->name = n;
			head->tel = tel;
			head->ic = ic;
			head->block = block;
			head->next = NULL;
			temp=head;
		}
		else
		{
			temp->next = new nodeTenant;
			temp = temp->next;
			temp->name = n;
			temp->tel = tel;
			temp->ic = ic;
			temp->block = block;
			temp->next=NULL;
		}
	}
	
	void add_visitor_node(string n,string ic,string tel,string block)
    {
    	if (vhead == NULL)
    	{
    		vhead = new nodeTenant;
			vhead->name = n;
			vhead->tel = tel;
			vhead->ic = ic;
			vhead->block = block;
			vhead->next = NULL;
			vtemp = vhead;
		}
		else
		{
			vtemp->next = new nodeTenant;
			vtemp = vtemp->next;
			vtemp->name = n;
			vtemp->tel = tel;
			vtemp->ic = ic;
			vtemp->block = block;
			vtemp->next=NULL;
		}
	}
	
	int del_node(string target)
	{
		int found = 0;
		temp = head;
		while( temp!=NULL &&temp->name != target)
		{
			prev = temp;
			temp=temp->next;
		}
		if(temp != NULL)
		{
			prev->next = temp->next;
			delete temp;
			found =1;
		}
		if(found == 1)
		{
			rewrite();
		}
		return found;
	}
	
	void rewrite()
	{
		temp = head;
		ofstream accept2("UserInformation.txt");
		while(temp!=NULL)
		{
		accept2<<temp->name<<endl<<temp->tel<<endl<<temp->ic<<endl<<temp->block<<endl;
		temp = temp->next;
		}
		accept2.close();
	}
	
	void read_node()
	{
		temp = head;
		while(temp!=NULL)
		{
			if(temp->block == owner_block)
			{
			cout << "Tenant Name: " << temp->name << endl;
            cout << "Tenant IC: " << temp->ic << endl;
            cout << "Tenant Telephone No: " << temp->tel << endl;
            cout << "-------------------------------------" << endl;
			}
			temp = temp->next;
		}
	}
	
	void read_visitor_node()
	{
		vtemp = head;
		while(temp!=NULL)
		{
			if(vtemp->block == owner_block)
			{
				cout << "Visitor Name: " << vtemp->name << endl;
                cout << "Visitor IC: " << vtemp->ic << endl;
                cout << "Visitor Telephone No: " << vtemp->tel << endl;
                cout << "Visitor Request Block: " << vtemp->block << endl;
                cout << "-------------------------------------" << endl;
			}
			vtemp = vtemp->next;
		}
	}
	
	
    void viewrequest()
    {
        while (true)
        {
            system("CLS");
            ifstream fread("rental_request.txt");

            if (!fread)
            {
                cout << "Error opening the file!" << endl;
                break; // Exit the loop if file opening fails
            }
            else
            {
                while (fread >> visitor_name >> visitor_ic >> visitor_tel_no >> visitor_request_block)
                {
                    add_node(visitor_name,visitor_ic,visitor_tel_no,visitor_request_block);
                }
                
                read_node();
            }
            fread.close();

            cout << "Press 'Y' to go back to the previous page: ";
            char choice;
            cin >> choice;

            if (toupper(choice) == 'Y')
            {
                return;
                break; // Exit the loop to go back
            }
        }
    }

    void viewTenantInformation()
    {
        system("CLS");
        
        cout << "\033[1;33m-------------------------------------\033[0m" << endl << endl;
        cout << "\033[1;33m-----  View Tenant Information  -----\033[0m" << endl << endl;
        cout << "\033[1;33m-------------------------------------\033[0m" << endl << endl;
		refresh();
        read_node();
        system("pause");
    }

      void editTenantInformation()
    {
        system("CLS");
        cout << "\033[1;33m-------------------------------------\033[0m" << endl << endl;
        cout << "\033[1;33m-----      Delete Tenant        -----\033[0m" << endl << endl;
        cout << "\033[1;33m-------------------------------------\033[0m" << endl << endl;

        string targetTenantName;
        read_node();
        cout << "Enter the name of the tenant to Delete: ";
        cin.ignore();
        getline(cin, targetTenantName);

		int found = del_node(targetTenantName);

        if (found == 1)
        {
            cout << "Tenant has been deleted successfully!" << endl;
        }
        else
        {
            cout << "Tenant not found!" << endl;
        }
    }
    
    void read_board()
	{
	system("cls");
	Board b;
	string select;
	b.num=0;
	int i=0,c=0;
	string line;
	ifstream read("bulletin_board.txt");
	if (!read.is_open()) 
	{
        cout << "Error opening the file." << endl;
    }
    
    
    bullet_board_display();
	
	while(getline(read,line))
	{
		istringstream iss(line);
		iss >> b.num;
		getline(iss,b.notice);
		
		if(i != b.num)
		{
			cout<<endl;
			c=0;
			i++;
		}
			
		switch(c)
		{
			case 0: cout<<"&           Ixora Apartment    	&"<<endl<<endl;
				cout<<"======================================================="<<endl<<endl;
				cout<<"                NOTICE "<<b.num<<endl<<endl;
				cout<<"======================================================="<<endl<<endl;
				cout<<"To      : "<<b.notice<<endl;c++;break;
		case 1: cout<<"Date    : "<<b.notice<<endl;c++;break;
		case 2: cout<<"Subject : "<<b.notice<<endl;c++;break;
		default:cout<<b.notice<<endl;break;
		}
			
	}
	read.close();
}

void add_room()
{
	string Unit,Name,PN,line;
	string owner_name,owner_ic,owner_tel_no,owner_unit,owner_username,owner_passwd;
	char choice;
	system("CLS");
        cout << "-------------------------------------" << endl
             << endl;
        cout << "-----    Add room Information   -----" << endl
             << endl;
        cout << "-------------------------------------" << endl;
    ifstream rread("owner.txt");
    ofstream wwrite("room.txt",ios::app);
	cout<<"Do You want to post your name ,phone number and unit to the room rental system?[Y or N]"<<endl;
	cin>>choice;
	if(choice == 'Y' || choice == 'y')	{

	while (getline(rread, line))
		{
            istringstream iss(line);
			
            owner_name = line;
            getline(rread, owner_ic);
            getline(rread, owner_tel_no);
            getline(rread, owner_unit);
            getline(rread, owner_username);
            getline(rread, owner_passwd);

            	if(owner_username == current_user)
            	{
				
				wwrite<<owner_unit<<endl<<owner_name<<endl<<owner_tel_no<<endl;
				cout<<"Your Information has been uploaded successfully."<<endl<<endl;
		}
	}
		}
		wwrite.close();
		rread.close();
		
}
};

class ixora
{
	private:  string name;
	
	public:
			
			ixora()
			{
				cout<<"----------------------------"<<endl<<endl;
				cout<<"Welcome to ixora apartment! "<<endl<<endl;
				cout<<"----------------------------"<<endl<<endl;
			}
			
			 void menu();
			int partition(string owners[], string ic[], string tel[], int low, int high) {
    string pivot = owners[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (owners[j] < pivot) {
            i++;
            // Swap owners[i] and owners[j]
            string temp = owners[i];
            owners[i] = owners[j];
            owners[j] = temp;
            
            // Swap ic[i] and ic[j]
            temp = ic[i];
            ic[i] = ic[j];
            ic[j] = temp;

            // Swap tel[i] and tel[j]
            temp = tel[i];
            tel[i] = tel[j];
            tel[j] = temp;
        }
    }
    // Swap owners[i + 1] and owners[high]
    string temp = owners[i + 1];
    owners[i + 1] = owners[high];
    owners[high] = temp;
    
    // Swap ic[i + 1] and ic[high]
    temp = ic[i + 1];
    ic[i + 1] = ic[high];
    ic[high] = temp;

    // Swap tel[i + 1] and tel[high]
    temp = tel[i + 1];
    tel[i + 1] = tel[high];
    tel[high] = temp;

    return i + 1;
}

// Quick Sort recursive function
void quickSort(string owners[], string ic[], string tel[], int low, int high) {
    if (low < high) {
        int pi = partition(owners, ic, tel, low, high);
        quickSort(owners, ic, tel, low, pi - 1);
        quickSort(owners, ic, tel, pi + 1, high);
    }
}

void owner_Inf() // gives the tenants view of owner information
{
    string owner_names[MAX_OWNERS];
    string owner_ics[MAX_OWNERS];
    string owner_tels[MAX_OWNERS];
    string owner_units[MAX_OWNERS];
    int owner_count = 0;
    string user_units[MAX_OWNERS];
    int user_count = 0;
    string owner_name, owner_ic, owner_tel_no, owner_unit;
    string user_unit, user_name, user_ic, user_tel_no;
    system("CLS");
    cout << "----------------------------" << endl << endl;
    cout << "Owner Information page " << endl << endl;
    cout << "----------------------------" << endl << endl;

    ifstream fread_owner("owner.txt"); // if can't open file, it will display a failure message
    ifstream fread_user("UserInformation.txt"); // if can't open file, it will display a failure message

    if (!fread_owner.is_open()) {
        cout << "Failed to open the owner.txt file!" << endl;
        return;
    }

    if (!fread_user.is_open()) {
        cout << "Failed to open the UserInformation.txt file!" << endl;
        return;
    }

    // Read owner details from the file, including unit number
    while (fread_owner >> owner_name >> owner_ic >> owner_tel_no >> owner_unit && owner_count < MAX_OWNERS) {
        owner_names[owner_count] = owner_name;
        owner_ics[owner_count] = owner_ic;
        owner_tels[owner_count] = owner_tel_no;
        owner_units[owner_count] = owner_unit;
        owner_count++;
    }
    fread_owner.close();

    // Read user booking information from the file
    while (fread_user >> user_name >> user_ic >> user_tel_no >> user_unit && user_count < MAX_OWNERS) {
        user_units[user_count] = user_unit;
        user_count++;
    }
    fread_user.close();

    // Sort owner names using Quick Sort
    quickSort(owner_names, owner_ics, owner_tels, 0, owner_count - 1);

    // Display sorted owner details for matching units
    for (int i = 0; i < owner_count; i++) {
        for (int j = 0; j < user_count; j++) {
            if (owner_units[i] == user_units[j]) 
			{
                cout << "Name : " << owner_names[i] << endl;
                cout << "IC : " << owner_ics[i] << endl;
                cout << "Telephone Number : " << owner_tels[i] << endl;
                cout << "--------------------------------" << endl;
            }
			else
			{
				cout<<"Owner Information not found!!"<<endl;
			}
        }
    }
}
			 
	  		 void feedback()//to give feedback
	  		 {
	  		 	system("CLS");
				cout<<"######################################"<<endl<<endl;
				cout<<"-----	Feedback Page    ------"<<endl<<endl;
				cout<<"######################################"<<endl<<endl;
			
				ofstream fwrite("feedback.txt",ios ::app);
			
				if(!fwrite)
				{
					
					cout<<"File doesnt exist :("<<endl;
					exit(0);
				
				}
				
				else
				{
					string name, email, message;
    
    				cout << "Enter your name: ";
    				fflush(stdin);
    				getline(cin, name);

    				cout << "Enter your email: ";
    				getline(cin, email);

    				cout << "Enter your feedback message: ";
   					getline(cin, message);

    				fwrite<<name<<endl<<email<<endl<<message<<endl;
				}
				
    			fwrite.close();

    			cout << "Feedback has been saved successfully!" << endl<<endl;
			 }
			 
			 void rq_access_card()//request to make the access card
			 {
			 	system("CLS");
				cout<<"############################################################"<<endl<<endl;
				cout<<"-----	request for authorised identify card   ------"<<endl<<endl;
				cout<<"############################################################"<<endl<<endl;
			
				ofstream fwrite("request_accesscard.txt",ios ::app);
				
			if(!fwrite)
			{
				cout<<"File doesnt exist :("<<endl;
				exit(0);
			}
			else
			{
				 string name, email,unit,ic;
				 
    			cout<<"Enter your name: ";
    			fflush(stdin);
    			getline(cin, name);

    			cout<<"Enter your email: ";
    			fflush(stdin);
    			getline(cin, email);

    			cout<<"Enter your IC/Passport: ";
   				getline(cin,ic);
   				
   				cout<<"Enter your unit :";
   				fflush(stdin);
   				getline(cin, unit);

    
    			fwrite<<name<<" "<<email<<" "<<ic<<" "<<unit<<endl;

			}
    			fwrite.close();

    		cout <<"\nYour request has been saved successfully!" << endl;
    		cout<<"the access card will be done in 7days!!!" << endl<<endl;
			}
			 
			 void rq_parking_card()//request to make a parkingcard per month
			 {
			 	string name,car_num,ic,phone_num;
				 float price;
				 int month;
			 	system("CLS");
			cout<<"############################################################"<<endl<<endl;
			cout<<"-----	request for parking card   ------"<<endl<<endl;
			cout<<"############################################################"<<endl<<endl;
			
			ofstream fwrite("request_parkingcard.txt",ios ::app);
			
			if(!fwrite)
			{
				cout<<"File doesnt exist :"<<endl;
				exit(0);
			}
			else
			{
				 
    			//to get input for tenant
    			cout << "Enter your name: ";
    			fflush(stdin);
    			getline(cin, name);

    			cout << "Enter your contact_number: ";
    			fflush(stdin);
    			getline(cin,phone_num);

    			cout << "Enter your IC/Passport: ";
    			fflush(stdin);
   				getline(cin,ic);
   				
   				cout<<"Enter your Car.No :";
   				fflush(stdin);
   				getline(cin, car_num);

    			cout<<"How many months do you need?[RM50 per month] :";
    			cin>>month;
    			//
    			price= rental * month ;
    			
    			fwrite<<name<<" "<<phone_num<<" "<<ic<<" "<<car_num<<" "<<month<<" "<<price<<endl;

			}
    			fwrite.close();//when done request the file will cross
			cout<<"\nYour parkingfee is : RM"<<price<<endl;
    		cout << "Your request has been saved successfully!" << endl;
    		cout<<"the access card will be done in 7days!!!" << endl<<endl;
			 }
};

class visitor
{
	private:
		string name,phone,IC,unit,date;
		
	public:
		friend void visitor_reg();
		
		
	void view_room()
		{
			int count = 0,num=1;
			string* line = new string;
			system("CLS");
			cout<<"***********"<<endl;
			cout<<"----      Rental Room     ----"<<endl;
			cout<<"***********"<<endl;
			
			ifstream read("room.txt");
			
			if(!read.is_open())
			{
				cout<<"No room to rental at this time!"<<endl;
				sleep(2);
				visitor_menu();
				system("CLS");
			}
			
			while(getline(read,*line))
			{
				if(count == 0)
				{
					cout<<"Room "<<num++<<" : "<<endl;
					cout<<"Unit Number          : "<<*line<<endl;
					count++;
				}
				else if(count == 1)
				{
					cout<<"Owner's name         : "<<*line<<endl;
					count++;
				}
				else if(count == 2)
				{
					cout<<"Owner's Phone Number : "<<*line<<endl<<endl;
					count=0;
				}
			}
			
			cout << "Press any key to continue..." << endl;
    		getch();
			delete line;
		}
			
			
		
		void rental_apply()
		{
			cout<<"*********************************"<<endl;
			cout<<"----    Rental Apply     ----"<<endl;
			cout<<"*********************************"<<endl;
		
			view_room();
			
			cout<<"----------------------------------";
			cout<<"\nEnter your name: ";
			cin.ignore();
			getline(cin,name);
			cout<<"\nEnter Phone Number : ";
			cin>>phone;
			cout<<"\nEnter your IC/Passport : ";
			cin>>IC;
			cout<<"\nEnter rental unit : ";
			cin>>unit;
			
			ofstream fwrite("rental_request.txt", ios::app);
	
	        if (!fwrite)
	        	{
	             cout<<"No room to rental at this time!"<<endl;
 				 sleep(2);
				 visitor_menu();
				 system("CLS");
	        	}
	        fwrite<<name<<endl<<phone<<" "<<IC<<" "<<unit<<" "<<endl;	
	        
	        fwrite.close();
	        cout<<"\n\nYour application has been submitted to owner.";
	        sleep(1);
		}
		void check_passwd()
			{
				
				int found;
				int count=0, count_limit=0;
				string ic,storedUsername,storedPassword;
				string ic_found[limit], pass[limit];
				system("CLS");
			//	cout<<"Warning! This is for fist time user only!"<<endl;
				cout<<"Please enter IC Number : ";
				cin>>ic;
				ifstream fread("users.txt");
				while (fread >> storedUsername >> storedPassword) 
				{
	    			ic_found[count] = storedUsername;
	    			pass[count] = storedPassword;
	    			count++;
				}

				for (int i = 0; i < count - 1; ++i) 
				{
				    for (int j = 0; j < count - i - 1; ++j) 
					{
				        if (ic_found[j] > ic_found[j + 1]) 
						{
				            string temp_ic = ic_found[j];
				            ic_found[j] = ic_found[j + 1];
				            ic_found[j + 1] = temp_ic;
				
				            string temp_pass = pass[j];
				            pass[j] = pass[j + 1];
				            pass[j + 1] = temp_pass;
				        }
				    }
				}

				for (int i = 0; i < count; i++) 
				{
				    cout << "ic_found[" << i << "]: " << ic_found[i] << endl;
				    cout << "pass[" << i << "]: " << pass[i] << endl;
				}
				int step = sqrt(count);
				int n = count;
				int prev=0;
				while (ic_found[min(step, count)-1] < ic)
				{
				    prev = step;
				    step += sqrt(n);
				    if (prev >= n)
				    {
				    found = -1;
				    break;
					}    
				}
			    while (ic_found[prev] < ic)
			    {
			        prev++;
			        if (prev == min(step, n))
			            found = -1;
			    }
			    if (ic_found[prev] == ic){
			    	cout<<"Your Password is "<<pass[prev]<<endl;
			    	found = 1;
				}
			 	
				if(found!=1)
				{
					cout<<"Invalid IC, Please make sure you have entered the correct IC."<<endl;
				}
				cout << "Press any key to continue..." << endl;
    			getch();
			}
};

class parking
{
	protected:
		string name;
		string IC;
		string No_car_plate;
		string no_plate;
		string date;
		string month;
		
	
	public:
		void search_parking()
{
	parking p;
	string line,output;
	int count=1,num,founded=0;
	
	cout<<"Enter No Car PLate : ";
	cin>>no_plate;
	
	 ifstream read("parking.txt");
	if (!read.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }
    while(getline(read,line))
	{
		if(count>5)
		{
			count=1;
		}
		stringstream iss(line);
		iss >> num;
		getline(iss,output);
		
		size_t found = output.find(no_plate);
		
		switch(count)
		{
			case 1: name = output;break;
			case 2: IC = output;break;
			case 3: date = output;break;
			case 4: No_car_plate = output;break;
			case 5: month = output;break;
		}
		
		if(count == 5 && found != string::npos)
		{
			cout<<"Car Park User #"<<num<<" :"<<endl;
			cout<<"Name         : "<<name<<endl;
			cout<<"IC Nunber    : "<<IC<<endl;
			cout<<"No.Car Plate : "<<No_car_plate<<endl<<endl;
			cout<<"Month : "<<month<<endl<<endl;
			founded =1;
		}

		count++;
	}
	
	if(founded == 0)
	{
		cout<<"No User Found!"<<endl;
	}
	read.close();
	system("pause");
    system("cls");
}

void read_request_file()
{
    string line, name, phone_num, ic, car_num;
    int month;
    float price;

    ifstream fread("request_parkingcard.txt");
    if (!fread.is_open())
    {
        cout << "Error opening the file." << endl;
        return;
    }

    cout << "Displaying information from request_parkingcard.txt file:" << endl;

    while (getline(fread, line))
    {
        stringstream iss(line);
        iss >> name >> phone_num >> ic >> car_num >> month >> price;

        cout << "Name         : " << name << endl;
        cout << "Contact Num  : " << phone_num << endl;
        cout << "IC/Passport  : " << ic << endl;
        cout << "Car No       : " << car_num << endl;
        cout << "Months       : " << month << endl;
        cout << "Total Price  : RM" << price << endl;
        cout << "-----------------------------" << endl;
    }

    fread.close();
    system("pause");
    system("cls");
}

};

class admin_parking : public parking
{
	public:
	void view_parking()
{
	string line,output;
	int count=1,num=0;
	
	 ifstream read("parking.txt");
	if (!read.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }
    while(getline(read,line))
	{
		if(count>5)
		{
			count=1;
		}
		stringstream iss(line);
		iss >> num;
		getline(iss,output);
		
		switch(count)
		{
			case 1: name = output;break;
			case 2: IC = output;break;
			case 3: date = output;break;
			case 4: No_car_plate = output;break;
			case 5: month = output;break;
		}
		
		if(count == 5)
		{
			cout<<"Car Park User #"<<num<<" :"<<endl;
			cout<<"Name         : "<<name<<endl;
			cout<<"IC Nunber    : "<<IC<<endl;
			cout<<"Date         : "<<date<<endl;
			cout<<"No.Car Plate : "<<No_car_plate<<endl;
			cout<<"Month 		: "<<month<<endl<<endl;
		}
		count++;
	}
	read.close();
	system("pause");
    system("cls");
}

	void add_parking()
{
	system("cls");
	int num=0;
	string line,non;
		
	ofstream write("parking.txt",ios::app);
	if (!write.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }
    
    ifstream read("parking.txt");
	if (!read.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }
    
    while(getline(read,line))
	{
		stringstream iss(line);
		iss >> num;
		getline(iss,non);
	}
    
    cout<<"Enter Name : ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter IC   : ";
    cin>>IC;
    cout<<"Enter Car Plate Number : ";
    cin>>No_car_plate;
    cout<<"Enter Month : ";
    cin>>month;
	
	
	write<<++num<<" "<<name<<endl;
	write<<num<<" "<<IC<<endl;
	write<<num<<" "<<gettime()<<endl;
	write<<num<<" "<<No_car_plate<<endl;
	write<<num<<" "<<month<<endl;
	
	read.close();
	write.close();
	
        system("cls");
}};

class access_card
{
protected:
    string name;
    string IC;
    string email;
    string unit;
    string date;
    

public:
  

    void read_access_card_request_file()
    {
        string line, name, email, ic, unit;

        ifstream fread("request_accesscard.txt");
        if (!fread.is_open())
        {
            cout << "Error opening the file." << endl;
            return;
        }

        cout << "Information from request:" << endl;

        while (getline(fread, line))
        {
            stringstream iss(line);
            iss >> name >> email >> ic >> unit;

            cout << "Name         : " << name << endl;
            cout << "Email        : " << email << endl;
            cout << "IC/Passport  : " << ic << endl;
            cout << "Unit         : " << unit << endl;
            cout << "-----------------------------" << endl;
        }
		
        fread.close();
        system("pause");
        system("cls");
    }

};


class admin_access : public access_card
{
public:
    void view_access_card()
    {
        string line, output;
        int count = 1, num = 0;

        ifstream read("access.txt");
        if (!read.is_open())
        {
            cout << "Error opening the file." << endl;
            return;
        }
        while (getline(read, line))
        {
            if (count > 5)
            {
                count = 1;
            }
            stringstream iss(line);
            iss >> num;
            getline(iss, output);

            switch (count)
            {
            case 1:
                name = output;
                break;
            case 2:
                IC = output;
                break;
            case 3:
                email = output;
                break;
            case 4:
                unit = output;
                break;
            case 5:
                date = output;
                break;
            }

            if (count == 5)
            {
                cout << "Access Card User #" << num << " :" << endl;
                cout << "Name         : " << name << endl;
                cout << "IC Number    : " << IC << endl;
                cout << "email        : " << email << endl;
                cout << "Unit : " << unit << endl;
                cout << "date       : " << date << endl
                     << endl;
                     
            }
            count++;
            
        }
        read.close();
        system("pause");
        system("cls");
    }

    void add_access_card()//help tenant to do the access card
    {
        int num = 0;
        string line, non;
		system("cls");
        ofstream write("access.txt", ios::app);
        if (!write.is_open())
        {
            cout << "Error opening the file." << endl;
            return;
        }

        ifstream read("access.txt");
        if (!read.is_open())
        {
            cout << "Error opening the file." << endl;
            return;
        }

        while (getline(read, line))
        {
            stringstream iss(line);
            iss >> num;
            getline(iss, non);
        }

        cout << "Enter Name : ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter IC   : ";
        cin >> IC;
        cout << "Enter email : ";
        cin >> email;
        cout << "Enter unit : ";
        cin >> unit;
		//it will write inside the file  so you can view in another function
        write << ++num << " " << name << endl;
        write << num << " " << IC << endl;
        write << num << " " << email << endl;
        write << num << " " << unit<< endl;
        write << num << " " << gettime() << endl;

        read.close();
        write.close();
        system("cls");
    }
};

class SuperAdmin:public Admin
{
	private:
		string sa_name, sa_password;
		string check_sn, check_sp;
		string admin_name, admin_pass;
	public:
		SuperAdmin()
		{
			system("cls");
			cout<<"--------------------------------"<<endl;
			cout<<"You are now in Super Admin mode."<<endl;
			cout<<"--------------------------------"<<endl;
		}
		
		int sa_input()
		{
			cout<<"Enter SuperAdmin Name : ";
			cin>>sa_name;
			cout<<"Enter SuperAdmin Password : ";
			cin>>sa_password;
			if(sa_name != check_sn)
			{
				cout<<"Wrong Super Admin Name !"<<endl;
				system("pause");
				return 1;
			}
			else
			{
				if(sa_password != check_sp)
				{
					cout<<"Wrong SuperAdmin Password !"<<endl;
					system("pause");
					return 2;
				}
				else
					return 3;


			}
		}
		
	void admin_menu(){
	
	int admin_choice;
	string name, email, msg;
	int read;
	
    system("cls");

	admin_parking p;
	admin_access a;
	while(true)
	{
	cout<<"=================================="<<endl<<endl;
	cout<<"	       Super Admin mode      	 "<<endl<<endl;
	cout<<"=================================="<<endl<<endl;
	cout<<"What you want to do..."<<endl;
	cout<<"1. Add admin"<<endl;
	cout<<"2. Change password"<<endl;
	cout<<"3. Add new owner"<<endl;
	cout<<"4. View owner"<<endl;
	cout<<"5. Edit owner"<<endl;
	cout<<"6. Delete owner\n";
	cout<<"7. View tenant"<<endl;
	cout<<"8. View Visitor"<<endl;
	cout<<"9. Add a parking slot for tenants"<<endl;
	cout<<"10. View the parking slots"<<endl;
	cout<<"11. Add a access card for tenants"<<endl;
	cout<<"12. View the access card"<<endl;
	cout<<"13. Edit bulletin"<<endl;
	cout<<"14. View feedback"<<endl;
	cout<<"15. Back to Identifier Menu"<<endl;
	cout<<"16. Exit"<<endl;
	cout << "Select [1-16] : ";
	cin>>admin_choice;
	while(admin_choice <1 || admin_choice >16)
		{
			cout<<"Invalid Select"<<endl;
			cout<<"Pls Select again[1-16] :";
			cin>>admin_choice; 
		}
	switch(admin_choice)
	{
		case 1:
			{
				sa_add_admin();
				break;
			}
		case 3:
			{
				void sa_changepass();
				break;
			}
		case 4:
			{
				view_owner();
				break;
			}
		case 5:
			{
				search_owner();
				edit_owner();
				break;
			}
		case 6:
			{	
				search_owner();
				delete_owner();
				break;
			}
		case 7:
			{
				view_tenants();
				break;
			}
		case 8:
			{
				view_visitor();
				break;
			}
		case 9:
			{
				p.add_parking();
				break;
			}
		case 10:
			{
				parking();
				break;
			}
		case 11:{
			a.add_access_card();
			break;
		}
		case 12:
		{
			access();
			break;
		}
		case 13:
			{	
				View_Board();
				break;
			}	
			
		case 14:
			{
				view_feedback();
				break;
			}
		case 15:
			{
				return;
				break;
			} 
		case 16:
			{
				exit(0);
				break;
			}
		default:
			{
				cout<<"Invalid choice !!!"<<endl;
				break;
			}
		}
	}
}
		void check_sa()
		{
			fstream fread("super_admin.txt");
			fread>>check_sn>>check_sp;
			fread.close();
		}
		void sa_add_admin()
		{
			fstream fwrite("admin.txt", ios::app);
			cout<<"Enter a new admin name : ";
			cin>>admin_name;
			cout<<"Set a password to the admin : ";
			cin>>admin_pass;
			cout<<"Successfully add the admin ["<<admin_name<<"]"<<endl;
			fwrite<<admin_name<<endl<<admin_pass<<endl;
			fwrite.close();
		}
		void sa_changepass()
		{
			string new_pass;
			cout<<"Please enter old password : ";
			cin>>new_pass;
			if(new_pass != check_sp)
			{
				cout<<"You need to enter correct old password before you change it!";
				system("pause");
				return;
			}
			cout<<"Then enter new password : ";
			cin>>new_pass;
			ofstream empty("super_admin.txt", ios::trunc);
			empty.close();
			fstream fwrite("super_admin.txt", ios::app);
			fwrite<<check_sn<<endl<<new_pass<<endl;
			fwrite.close();
			cout<<"Successfully change the password !"<<endl;
			system("pause");
			system("cls");
		}
		~SuperAdmin()
		{
			cout<<"\nThanks for using"<<endl;
			system("pause");
			system("cls");
		}
};

int read_request()
{
	int count=0,found=0;
	system("CLS");
	cout<<"*********************************"<<endl;
	cout<<"----    Rental Request     ----"<<endl;
	cout<<"*********************************"<<endl;
	string owner_name,owner_ic,owner_tel_no,owner_unit,owner_username,owner_passwd;
	string name,phone,ic,unit;
		fstream fread("owner.txt");
		fstream fread2("rental_request.txt");
		if(!fread)
			{
				cout<<"Failed to get the owner list!!!"<<endl;
			}
			string line,line2;
		while (getline(fread, line))
		{
            istringstream iss(line);

            getline(iss, owner_name);
            getline(fread, owner_ic);
            getline(fread, owner_tel_no);
            getline(fread, owner_unit);
            getline(fread, owner_username);
            getline(fread, owner_passwd);
            
            	if(owner_username == current_user)
            	{
	            		while(getline(fread2,line2))
	            	{
	            		name = line2;
	            		getline(fread2,line2);
	            		istringstream iss2(line2);
	            		iss2>>phone>>ic>>unit;
	            		
	            		if(owner_unit==unit)
	            		{
	            			cout<<"Request #"<<++count<<endl;
	            			cout<<"Name         : "<<name<<endl;
	            			cout<<"Phone Number : "<<phone<<endl;
	            			cout<<"IC Number    : "<<ic<<endl<<endl;
	            			found =1;
						}
					}
				}
        }
        if(found != 1)
        	cout<<"No Request At This Time.."<<endl;
        
		fread.close();
		fread2.close();
		
		return count;
}

void visitor_reg()
		{
			visitor* v = new visitor;
			cout<<"*********************************"<<endl;
			cout<<"----  Visitor Registor   ----"<<endl;
			cout<<"*********************************"<<endl;
		
			cout<<"\nEnter your name: ";
			cin>>(*v).name;
			cout<<"\nEnter Phone Number : ";
			cin>>(*v).phone;
			cout<<"\nEnter your IC/Passport : ";
			cin>>(*v).IC;
			cout<<"\nEnter visit unit : ";
			cin>>(*v).unit;
			cout<<"\nEnter date to visit : ";
			cin>>(*v).date;
			
			 ofstream fwrite("visitor_request.txt", ios::app);
	
	        if (!fwrite)
	        	{
	            cout << "File doesnt exist :(" << endl;
	            return;
	        	}
	        	
	        fwrite<<(*v).name<<endl<<(*v).phone<<endl<<(*v).IC<<endl<<(*v).unit<<endl<<(*v).date;
	    				
			cout<<"\n\nYour application has been submitted to owner.";
			cout<<"\nWe will notify you once your application is approved.";
			
			fwrite.close();
			delete v;
		}

string gen_passwd()
{
	srand(time(0));
	int passwd=rand()%899999+100000;
	ostringstream oss;
	oss <<passwd;//convert from int to string
    string StorePasswd = oss.str();
	return StorePasswd;
}

void accept_request()
{	
	string line;
	string name,phone,ic,unit;
	string select;
	int count = read_request();
	ifstream fread("rental_request.txt");
	ofstream temp("temp.txt");
	ofstream accept2("UserInformation.txt",ios::app);
	ofstream accept("users.txt",ios::app);
	if(!fread.is_open())
	{
		cout<<"File opening error"<<endl;
	}
	if(!temp.is_open())
	{
		cout<<"Temp File opening error"<<endl;
	}
	cout<<"Enter IC number to Accept (0 to exit) : ";
	cin>>select;

	if(select == "0")
	{
		system("CLS");
		owner_menu();
		return;
	}
	while(getline(fread,line))
	{
	    name = line;
	    getline(fread,line);
	    istringstream iss(line);
	    iss>>phone>>ic>>unit;
	    if(ic == select)
	    {
	    	accept2<<name<<endl<<phone<<endl<<ic<<endl<<unit<<endl;
	    	accept<<endl<<ic<<" "<<gen_passwd();
		}
		else 
		{
			temp<<name<<endl<<phone<<" "<<ic<<" "<<unit<<" "<<endl;
		}
	}
	
	fread.close();
	temp.close();
	accept.close();
	accept2.close();
	remove("rental_request.txt");
	rename("temp.txt", "rental_request.txt");
}

void check_passwd()
{
	int found;
	int count=0, count_limit=0;
	string ic,storedUsername,storedPassword;
	string ic_found[limit], pass[limit];
	system("CLS");
//	cout<<"Warning! This is for fist time user only!"<<endl;
	cout<<"Please enter IC Number : ";
	cin>>ic;
	ifstream fread("users.txt");
	while (fread >> storedUsername >> storedPassword)
	{
		ic_found[count] = storedUsername;
	    			pass[count] = storedPassword;
	    			count++;
				}

				for (int i = 0; i < count - 1; ++i) 
		 for (int j = 0; j < count - i - 1; ++j) 
					{
				        if (ic_found[j] > ic_found[j + 1]) 
						{
				            string temp_ic = ic_found[j];
				            ic_found[j] = ic_found[j + 1];
				            ic_found[j + 1] = temp_ic;

				            string temp_pass = pass[j];
				            pass[j] = pass[j + 1];
				            pass[j + 1] = temp_pass;
				        }
				    }
			
				int step = sqrt(count);
				int n = count;
				int prev=0;
				while (ic_found[min(step, count)-1] < ic)
				{
				    prev = step;
				    step += sqrt(n);
				    if (prev >= n)
				    {
				    found = -1;
				    break;
					}    
				}
			    while (ic_found[prev] < ic)
			    {
			        prev++;
			        if (prev == min(step, n))
			            found = -1;
			    }
			    if (ic_found[prev] == ic){
			    	cout<<"Your Password is "<<pass[prev]<<endl;
			    	found = 1;
				}
	
	if(found!=1)
	{
		cout<<"Invalid IC, Please make sure you have entered the correct IC."<<endl;
	}
}

void parking()
{
	admin_parking p;
	int i;
	cout<<"***********"<<endl;
	cout<<"----      Parking       ----"<<endl;
	cout<<"***********"<<endl;
	
	cout<<"1. View All Parking"<<endl;
	cout<<"2. Search Parking"<<endl;
	cout<<"3. view request "<<endl;
	cout<<"Please Enter Select : ";
	cin>>i;
	
	switch(i)
	{
		case 1: p.view_parking();break;
		case 2: p.search_parking();break;
		case 3: p.read_request_file();break;
	}
}

void access()
{
	system("cls");
	admin_access a;
	int i;
	cout<<"***********"<<endl;
	cout<<"----      access       ----"<<endl;
	cout<<"***********"<<endl;
	
	cout<<"1. View All access card"<<endl;
	cout<<"2. view request "<<endl;
	cout<<"Please Enter Select : ";
	cin>>i;
	
	switch(i)
	{
		case 1: a.view_access_card();break;
		case 2: a.read_access_card_request_file();break;
	}
}
void menu()
{
	
			cout<<"=================================="<<endl<<endl;
			cout<<"Hi!!! Welcome to ixora apartment! "<<endl<<endl;
			cout<<"=================================="<<endl<<endl;

			cout<<"1. Admin"<<endl;
			cout<<"2. Owner"<<endl;
			cout<<"3. Tenant"<<endl;
			cout<<"4. Visitor"<<endl;
			
}


void ixora::menu()
{
			
			cout<<"1. View owner Information"<<endl;
			cout<<"2. View bulletin board"<<endl;
			cout<<"3. given feedback"<<endl;
			cout<<"4. Request for authorised identify card"<<endl;
			cout<<"5. Request for Parking slot"<<endl;
			cout<<"6. Exit"<<endl;
			
}

void visitor_menu()
{
	visitor v;
	int choice;
	cout<<"***********"<<endl;
	cout<<"----    Welcome Visitor     ----"<<endl;
	cout<<"***********"<<endl;
	cout<<"1. View Room to Rent\n2. Apply Rental\n3. Register For Visit\n4. Check Password\n0. Exit"<<endl;
	cin>>choice;
	if(choice == 1) v.view_room();
	else if(choice == 2) v.rental_apply();
	else if(choice == 3) visitor_reg();
	else if(choice == 4) v.check_passwd();
	else if(choice == 0) return;
}


int main()
{
	
	int p;
    
	while(true)
	{
	
	menu();
    cout<<"Please choose your identity : ";
	cin>>p;
	if(p == 1)
	{
	 system("CLS");
	 admin_passwd();
	}
	else if (p == 2)
        {
            system("CLS");
            owner_login();
            owner_menu();
        }
	else if(p == 3)
	{
		system("CLS");
		tenants_login();
		tenant_menu();
	}
	else if(p == 4)
	{
		system("CLS");
		visitor_menu();
	}
	else if(p == 111)
	{
		sa_login();
	}
	system("CLS");
	
	}
	return 0;  
}
    

void Admin :: admin_menu()
{
	int admin_choice;
	string name, email, msg;
	int read;
	
    system("cls");

	admin_parking p;
	admin_access a;
	while(true)
	{
	cout<<"=================================="<<endl<<endl;
	cout<<"	    Admin mode				 "<<endl<<endl;
	cout<<"=================================="<<endl<<endl;
	cout<<"What you want to do..."<<endl;
	cout<<"1. Add new owner"<<endl;
	cout<<"2. View owner"<<endl;
	cout<<"3. Edit owner"<<endl;
	cout<<"4. Delete owner\n";
	cout<<"5. View tenant"<<endl;
	cout<<"6. View Visitor"<<endl;
	cout<<"7. Add a parking slot for tenants"<<endl;
	cout<<"8. View the parking slots"<<endl;
	cout<<"9. Add a access card for tenants"<<endl;
	cout<<"10. View the access card"<<endl;
	cout<<"11. Edit bulletin"<<endl;
			cout<<"12. View feedback"<<endl;
	cout<<"13. Back to Identifier Menu"<<endl;
	cout<<"14. Exit"<<endl;
	cout << "Select [1-14] : ";
	cin>>admin_choice;
	while(admin_choice <1 || admin_choice >15)
		{
			cout<<"Invalid Select"<<endl;
			cout<<"Pls Select again[1-14] :";
			cin>>admin_choice; 
		}
	switch(admin_choice)
	{
		case 1:
			{
				add_owner();
				break;
			}
		case 2:
			{
				view_owner();
				break;
			}
		case 3:
			{
				search_owner();
				edit_owner();
				break;
			}
		case 4:
			{	
				search_owner();
				delete_owner();
				break;
			}
		case 5:
			{
				view_tenants();
				break;
			}
		case 6:
			{
				view_visitor();
				break;
			}
		case 7:
			{
				p.add_parking();
				break;
			}
		case 8:
			{
				parking();
				break;
			}
		case 9:{
			a.add_access_card();
			break;
		}
		case 10:
		{
			access();
			break;
		}
		case 11:
			{	
				View_Board();
				break;
			}	
			
		case 12:
			{
				view_feedback();
				break;
			}
		case 13:
			{
				return;
				break;
			} 
		case 14:
			{
				exit(0);
				break;
			}
		default:
			{
				cout<<"Invalid choice !!!"<<endl;
				break;
			}
		}
	}
}

void tenant_menu()
{
	int choi;
	char ans;
	do
	{

		ixora tenant;
		tenant.menu();
    	cout << "Select [1-6] : ";
    	cin >> choi;  
		
		while(choi <1 || choi >7)
		{
			cout<<"Invalid Select"<<endl;
			cout<<"Pls Select again[1-6] :";
			cin >> choi;  
		}
		switch(choi)
		{
			case 1 : {
				
						tenant.owner_Inf();
					  	break;
				
					 }
					 
			case 2 :{
				
						read_board();
						break;
			        }
			
			
			case 3 :{
						tenant.feedback();
						break;
			        }
			       
			case 4 :{
						tenant.rq_access_card();
						break;
				    }
			
			case 5 :{
						tenant.rq_parking_card();
						break;
			        }
			        
			case 6 :{
						return;
						break;
					}
		}
		
    	cout<<"Back To Previous Page [Press Y] :";
		cin>>ans;
		system("CLS");
	}while(ans == 'Y' || ans == 'y');
}

void bullet_board_display()
{
				cout<<"######################################"<<endl<<endl;
				cout<<"-----	 Ixora Bullet Board    ------"<<endl<<endl;
				cout<<"######################################"<<endl<<endl;
				
}

void read_board()
{
	system("cls");
	Board b;
	b.num=0;
	int i=0,c=0;
	string line;
	ifstream read("bulletin_board.txt");
	if (!read.is_open()) {
        cout << "Error opening the file." << endl;
    }
    
    bullet_board_display();
	
	while(getline(read,line))
	{
		istringstream iss(line);
		iss >> b.num;
		getline(iss,b.notice);
		
		if(i != b.num)
		{
			cout<<endl;
			c=0;
			i++;
		}
			
		switch(c)
		{
			case 0: cout<<"&           Ixora Apartment    	&"<<endl<<endl;
				cout<<"======================================================="<<endl<<endl;
				cout<<"                NOTICE "<<b.num<<endl<<endl;
				cout<<"======================================================="<<endl<<endl;
				cout<<"To      : "<<b.notice<<endl;c++;break;
		case 1: cout<<"Date    : "<<b.notice<<endl;c++;break;
		case 2: cout<<"Subject : "<<b.notice<<endl;c++;break;
		default:cout<<b.notice<<endl;break;
		}
			
	}
	read.close();
}

void write_board()
{
	system("cls");
	Board b ;
	b.num=0;
	
	string line;
	ifstream read("bulletin_board.txt");
	if (!read.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }
    
	while(getline(read,line))
	{
		stringstream iss(line);
		iss >> b.num;
		getline(iss,b.notice);
	}
	read.close();
		
	ofstream write("bulletin_board.txt",ios::app);
	if (!write.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }
    
    cout<<"Enter Notice Object : ";
    cin.ignore();
    getline(cin,b.bullet_TO);
    cout<<"Enter Title : ";
    getline(cin,b.bullet_title);
    write<<b.num+1<<" "<<b.bullet_TO<<endl;
	write<<b.num+1<<" "<<gettime()<<endl;
	write<<b.num+1<<" "<<b.bullet_title<<endl;
	cout<<"Enter Notice (Enter 'Stop' to stop writing)"<<endl;
    while(getline(cin,b.notice) && b.notice != "stop")
    {	
    	write<<b.num+1<<" "<<b.notice<<endl;
	}
    
    cout<<"Notice has been update successfully";
}

void delete_notice()
{
	read_board();
	Board b;
	int del;
	string line;
	cout<<"\nWhich notice would you want to delete? ";
	cin>>del;
	
	ifstream read("bulletin_board.txt");
	if (!read.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }
	ofstream dele("temp.txt");
	if (!dele.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }

		while(getline(read,line))
	{
		stringstream iss(line);
		iss >> b.num;
		getline(iss,b.notice);
		
		if(b.num == del)
			{
				continue;
			}
		else if(b.num > del)
		{
			dele<<--b.num<<" "<<b.notice<<endl;
		}
		else
		{
			dele<<--b.num<<" "<<b.notice<<endl;
		}
	}
		read.close();
		dele.close();
		remove("bulletin_board.txt");
		rename("temp.txt", "bulletin_board.txt");
		cout<<"Notice has been delete successfully"<<endl;
}

string gettime()
{

    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    ostringstream oss; //write things into string
    oss << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday;//convert from int to string
    string StoreTime = oss.str();
    cout<<StoreTime<<endl;

	return StoreTime;
}

void tenants_login()
{
	
	string t_name,storedUsername, storedPassword;
	int i,size=20;
	int h =3;
	string password;
	
	for(int q=0; q<3; q++)
	{i=0;
		cout<<"\nEnter the tenant ic: ";
		fflush(stdin);
		getline(cin, t_name);
		cout<<"Enter the tenant password: ";
		inputPassword(password,size);
	
	cout<<endl;
	
	fstream fread("users.txt");

	if(fread.is_open())
	{
    while (fread >> storedUsername >> storedPassword)
	 {
	 	if (storedUsername == t_name && storedPassword == password)
		{
           	sleep(2);
            cout<<"Success to login "<<endl;
            cout<<"Welcome Back ,"<<storedUsername<<endl;
            sleep(2);
            system("cls");
            return;
		}
    }
    fread.close();
    h--;
    	cout << "\nLogin failed. Incorrect username or password.\n";
    	if(h != 0)
    	cout<<"You still have "<<h<<" time(s) to try !\n"<<endl;
	}
	
	}
	
	exit(0);
}

void admin_passwd()
{
	string admin_name[al], admin_pass[al];
	string n, p;
	string name;
	string pass;
	int size =0;
	int i=0;
	int h=3;
	fstream check("admin.txt");	
	if(!check)
	{
		cout<<"There is no any admin registered yet !!!"<<endl<<endl;
		system("pause"); 
		return;
	}
  	string line;
	while (getline(check, line))
	{
    	istringstream iss(line);

   	 	getline(iss, n);
        getline(check, p);
		admin_name[i] = n;
		admin_pass[i] = p;
      
   		i++;
	}
	check.close();
		
	for(int j=0; j<3 ; j++)
	{
	cout<<"Please enter Admin name : ";
	cin>>name;
	cout<<"Admin Password :";
	inputPassword1(pass,size);
	
	for(int k=0; k<i; k++)
	{
	bool isAdmin = (name == admin_name[k] && pass== admin_pass[k]);
	
	  if (isAdmin) 
	  {
        cout<<"\nChecking.";
		sleep(1);
		cout<<".";
		sleep(1);
		cout<<".";
        cout << "\nLogin Successful! Welcome, " << name << ".";
		sleep(2);
		Admin admin;
        admin.admin_menu(); 
        return;	
      }
     
	}
	 	h--;
    	cout << "\nLogin failed. Incorrect username or password.\n";
    	if(h != 0)
    	cout<<"You still have "<<h<<" time(s) to try !\n"<<endl;
	}
   	 exit(0);
}

void sa_login()
{
	int sa_choice;
	SuperAdmin sa;
	sa.check_sa();
	int get = sa.sa_input();
	if(get == 1 || get == 2)
	{
		return;
	}
	sa.admin_menu();
	cin>>sa_choice;
	switch(sa_choice)
	{
			case 1:
				{
					sa.sa_add_admin();
					break;
				}
			case 2:
				{
					sa.sa_changepass();
					break;
				}
		}

	return;
}

void inputPassword(string &str, int size)
{
    char c;
    int count = 0;
    char *password = new char[size];

    while ((c = getch()) != '\r')
	 {
        if (c == 8) 
		{
            if (count == 0)
			 {
                continue;
            }
            putchar('\b');
            putchar(' ');
            putchar('\b');
            count--;
        }
        if (count == size - 1) {
            continue;
        }
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            putchar('*');
            password[count] = c;
            count++;
        }
    }
    password[count] = '\0';
    str = password;
    delete [] password;
    cout << endl;
}


void owner::ow_menu()
{
    cout << "========== Owner Menu ==========" << endl;
    cout << "1. View and Accept Rental Requests" << endl;
    cout << "2. Edit/View Tenants Information" << endl;
    cout << "3. View Bulletin Board" << endl;
    cout << "4. Add Rental Room Details" << endl;
    cout << "5. Exit" << endl;
    cout << "================================" << endl;
}


void owner::editAndViewTenantsInfo()
{
    char ans2;
    do
    {
        system("CLS");
        cout << "-------------------------------------" << endl
             << endl;
        cout << "-----     Edit/View Tenants     -----" << endl
             << endl;
        cout << "-------------------------------------" << endl
             << endl;

        cout << "1. View Tenant Information" << endl;
        cout << "2. Delete Tenant Information" << endl;
        cout << "3. Go Back to Owner Menu" << endl;

        int option;
        cout << "Enter your choice (1-3): ";
        cin >> option;
        
        while (option < 1 || option > 3)
        {
            cout << "Invalid Select" << endl;
            cout << "Pls Select Again[1-3] :";
            cin >> option;
        }

        switch (option)
        {
        case 1:
            viewTenantInformation();
            break;
        case 2:
            editTenantInformation();
            break;
        case 3:
        	system("CLS");
            owner_menu();
            return;
        default:
        	system("CLS");
            cout << "Invalid choice. Please enter your choice (1-3)..." << endl;
            break;
        }

        cout << "Back To Previous Page [Press B] : ";
        cin >> ans2;

    } while (toupper(ans2) == 'B' || 'b');
}

void owner_menu()
{
    owner owner;
    int option;
    char ans1;

    do
    {
        owner.ow_menu();
        menu;

        cout << "Enter your choice (1-4, 5 to exit): ";
        cin >> option;

        while (option < 1 || option > 5)
        {
            cout << "Invalid Select" << endl;
            cout << "Pls Select Again[1-5] :";
            cin >> option;
        }

        switch (option)
        {
        case 1:
        {
            accept_request();
            break;
        }
        case 2:
        {
            owner.editAndViewTenantsInfo();
            break;
        }
        case 3:
        {
            read_board();
            break;
        }
        case 4:
        {
            owner.add_room();
            break;
        }
        case 5:
        {
            return;
            break;
        }
        default:
        {
            break;
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
        }

        cout << "Back To Previous Page [Press Y] :";
        cin >> ans1;
        system("CLS");
    } while (ans1 == 'Y' || ans1 == 'y');
}


void owner_login()
{

    string t_name, storedUsername, storedPassword;
    int i, size = 20;
    string password;

    for (int q = 0; q < 3; q++)
    {
        i = 0;
        cout << "\nEnter the owner username: ";
        fflush(stdin);
        getline(cin, t_name);
        cout << "Enter the owner password: ";
        inputPassword(password, size);

        cout << endl;

        fstream fread("owner.txt");

        if (fread.is_open())
        {
        	string line;
        	while (getline(fread, line)) 
			{
	            istringstream iss(line);
	
	            getline(fread, line);
	            getline(fread, line);
	            getline(fread, owner_block);
	            getline(fread, storedUsername);
	            getline(fread, storedPassword);
	            if (storedUsername == t_name && storedPassword == password)
                {
                    sleep(2);
                    cout << "Success to login " << endl;
                    cout << "Welcome Back ," << storedUsername << endl;
                    current_user = storedUsername;
                    sleep(2);
                    system("cls");
                    return;
                }
    		}
        }
            fread.close();
            cout << "Please re-enter the username or password !" << endl;
        }
        exit(0);
    }


void inputPassword1(string &str, int size)
{
    char c;
    int count = 0;
    char *password = new char[size];

    while ((c = getch()) != '\r')
    {
        if (c == 8)
        {
            if (count == 0)
            {
                continue;
            }
            putchar('\b');
            putchar(' ');
            putchar('\b');
            count--;
        }
        if (count == size - 1)
        {
            continue;
        }
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            putchar('*');
            password[count] = c;
            count++;
        }
    }
    password[count] = '\0';
    str = password;
    delete[] password;
    cout << endl;
}

