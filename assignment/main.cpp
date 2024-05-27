#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<sstream>
using namespace std;

tm getTime(string time)
{
    char d;
    int day, month, year;
    tm time_struct;

    istringstream iss(time);
    iss >> day >> d >> month >> d >> year;

    time_struct.tm_year = year - 1900; // Years since 1900
    time_struct.tm_mon = month - 1;    // Months are 0-based
    time_struct.tm_mday = day;

    return time_struct;
}

struct Node {
    string name, id, course;
    float gpa;
    Node* next;
    tm time;

    Node(string id, string name, float gpa, string course, string timer)
    {
        this->id = id;
        this->name = name;
        this->gpa = gpa;
        this->course = course;
        this->time = getTime(timer);
        this->next = NULL; // Initialize next to NULL
    }
};

class menu
{
private:
    Node* head;
    int choice, choice1;
    string *id, *name, *course, *time;
    float *gpa;
    int size;
public:
    menu()
    {
        head = NULL;
    }

    void data(string *id, string *name, float *gpa, int size, string *course, string *time)
    {
        this->size = size;
        this->id = id;
        this->name = name;
        this->gpa = gpa;
        this->course = course;
        this->time = time;

        for (int z = 0; z < size; z++)
        {
            add_link(id[z], name[z], gpa[z], course[z], time[z]);
        }
    }

    void main_menu()
    {
        cout << "----------------------------------------" << endl;
        cout << "Welcome to student management system" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. View/Add students" << endl;
        cout << "2. Set 1 - (Cocktail Sort + Ubiquitous Binary Search)" << endl;
        cout << "2. Search student" << endl;//Elysa
        cout << "3. Set 2 - (Pancake Sort + Jump Search)" << endl;
        cin >> choice;
        
        switch (choice)
        {
		    case 1: 
			{
		        students();
		        break;
		    }
		    case 2: 
			{
				search_students();
		        break;
		    }
		    case 3: 
			{
		        break;
		    }
        }
    }

    void students()
    {
        cout << "===========================" << endl;
        cout << "Managing the students" << endl;
        cout << "===========================" << endl;
        cout << "What you want to do..." << endl;
        cout << "1. Add new student" << endl;
        cout << "2. View students information" << endl;
        cout << "4. Back" << endl;
        cout << ">>>>>";
        cin >> choice1;
        switch (choice1)
        {
	        case 1: 
			{
	            add_students();
	            break;
	        }
	        case 2: 
			{
	            view_students();
	            break;
	        }
	        case 3: 
			{
	            break;
	        }
	        case 4: 
			{
	            return;
	            break;
	        }
        }
    }

    void add_link(string id, string name, float gpa, string course, string time)
    {
        Node* new_node = new Node(id, name, gpa, course, time);
        if (!head)
        {
            head = new_node;
            return;
        }

        Node* current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_node;
    }

    void view_students()
    {
        Node* current = head;
        while (current)
        {
            cout << "Student id: " << current->id <<
                "\nStudent Name: " << current->name <<
                "\nStudent GPA: " << current->gpa <<
                "\nCourse: " << current->course <<
                "\nJoin Time: " << current->time.tm_mday << "-" << current->time.tm_mon + 1 << "-" << current->time.tm_year + 1900 << endl << endl;
            current = current->next;
        }
    }

    void add_students()
    {
        int addnum;
        cout << "How many students you want to add? ";
        cin >> addnum;
        string add_id[addnum], n[addnum], gettime[addnum];
        float g[addnum];
        for (int i = 0; i < addnum; i++)
        {
            cout << "Enter new student information" << endl << endl;
            cout << "ID: ";
            cin >> add_id[i];
            cout << "Name: ";
            cin >> n[i];
            cout << "GPA: ";
            cin >> g[i];
            cout << "Course: ";
            cin.ignore();
            getline(cin, course[i]);
            cout << "Join Time: ";
            cin >> gettime[i];

            add_link(add_id[i], n[i], g[i], course[i], gettime[i]);
        }
    }

    void search_students()//Elysa
    {
    	system("cls");
        int search_choice;
        cout << "Search by:" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. GPA" << endl;
        cout << "4. Join Time" << endl;
        cout << ">>>>>";
        cin >> search_choice;
    	cout << endl;


        switch (search_choice)
        {
        case 1: 
		{
            string search_id;
            cout<<"-----------------------"<<endl;
            cout<<"     Search By ID      "<<endl;
            cout<<"-----------------------"<<endl;
            cout << "Enter ID: ";
            cin >> search_id;
            search_by_id(search_id);
            break;
        }
        case 2: 
		{
            string search_name;
            cout<<"-----------------------"<<endl;
            cout<<"     Search By Name      "<<endl;
            cout<<"-----------------------"<<endl;
            cout << "Enter Name: ";
            cin >> search_name;
            search_by_name(search_name);
            break;
        }
        case 3: 
		{
            float search_gpa;
            cout<<"-----------------------"<<endl;
            cout<<"     Search By GPA      "<<endl;
            cout<<"-----------------------"<<endl;
            cout << "Enter GPA: ";
            cin >> search_gpa;
            search_by_gpa(search_gpa);
            break;
        }
        case 4: 
		{
            string search_time;
            cout<<"-----------------------"<<endl;
            cout<<"  Search By Join Time      "<<endl;
            cout<<"-----------------------"<<endl;
            cout << "Enter Join Time (dd-mm-yyyy): ";
            cin >> search_time;
            search_by_time(search_time);
            break;
        }
        }
    }

    void search_by_id(string search_id)
    {
        Node* current = head;
        while (current)
        {
            if (current->id == search_id)
            {
                display_student(current);
                return;
            }
            current = current->next;
        }
        cout << "Student not found!" << endl;
    }

    void search_by_name(string search_name)
    {
        Node* current = head;
        while (current)
        {
            if (current->name == search_name)
            {
                display_student(current);
                return;
            }
            current = current->next;
        }
        cout << "Student not found!" << endl;
    }

    void search_by_gpa(float search_gpa)
    {
        Node* current = head;
        while (current)
        {
            if (current->gpa == search_gpa)
            {
                display_student(current);
                return;
            }
            current = current->next;
        }
        cout << "Student not found!" << endl;
    }

    void search_by_time(string search_time)
    {
        tm search_tm = getTime(search_time);
        Node* current = head;
        while (current)
        {
            if (current->time.tm_year == search_tm.tm_year &&
                current->time.tm_mon == search_tm.tm_mon &&
                current->time.tm_mday == search_tm.tm_mday)
            {
                display_student(current);
                return;
            }
            current = current->next;
        }
        cout << "Student not found!" << endl;
    }

    void display_student(Node* student)
    {
    	system("cls");
    	cout<<"Student Found!"<<endl;
        cout << "\nStudent id: " << student->id <<
            "\nStudent Name: " << student->name <<
            "\nStudent GPA: " << student->gpa <<
            "\nCourse: " << student->course <<
            "\nJoin Time: " << student->time.tm_mday << "-" << student->time.tm_mon + 1 << "-" << student->time.tm_year + 1900 << endl << endl;
    }
};

int main()
{
    string i[] = { "1", "2", "3", "4" };
    string j[] = { "ming", "yong", "leong", "elysa" };
    float g[] = { 1.2, 1.3, 1.4, 1.5 };
    string course[] = { "Diploma in IT", "Diploma in IT", "Diploma in IT", "Diploma in IT" };
    string timee[] = { "12-2-2024", "14-12-2023", "22-5-2024", "27-6-2024" };

    int size = sizeof(i) / sizeof(i[0]);
    menu m;
    int choice;

    m.data(i, j, g, size, course, timee);

    m.main_menu();
    cout << "Do you want to continue?(1=Yes, Other=No): ";
    cin >> choice;

    while (choice == 1)
    {
        m.main_menu();
        cout << "Do you want to continue?(1=Yes, Other=No): ";
        cin >> choice;
    }
    return 0;
}
