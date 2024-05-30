#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

struct Student {
    string id, name;
    float gpa;
    string course;
    int date, mon, year;
};

class Main {
private:
    int choice, choice1;
    Student* student;
    int size;

public:
    Main(Student* s, int size) {
        this->size = size;
        student = new Student[size];
        for (int i = 0; i < size; i++) {
            student[i] = s[i];
        }
    }

    ~Main() {
        delete[] student;
    }

    void main_menu() {
        cout << "----------------------------------------" << endl;
        cout << "Welcome to student management system" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. View/Add students" << endl;
        cout << "2. Set 1 - (Cocktail Sort + Ubiquitous Binary Search)" << endl; //Leong
        cout << "2. Search student" << endl; // Elysa
        cout << "3. jump search" << endl;
        cout << "3. Set 2 - (Pancake Sort + Jump Search)" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            students();
            break;
        case 2:
            set2menu();
            break;
        case 3:
            jump_search();
            break;
        }
    }

    void students() {
        cout << "===========================" << endl;
        cout << "Managing the students" << endl;
        cout << "===========================" << endl;
        cout << "What you want to do..." << endl;
        cout << "1. Add new student" << endl;
        cout << "2. View students information" << endl;
        cout << "4. Back" << endl;
        cout << ">>>>>";
        cin >> choice1;
        switch (choice1) {
        case 1:
            add_students();
            break;
        case 2:
            view_students();
            break;
        case 3:
            break;
        case 4:
            return;
            break;
        }
    }

    void view_students() {
        cout << "============" << endl << "View students" << endl << "==============" << endl << endl;
        cout << left << setw(10) << "ID"
            << setw(10) << "Name"
            << setw(10) << "GPA"
            << setw(10) << "Course"
            << "Join Time" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        for (int i = 0; i < size; i++) {
            cout << left << setw(10) << student[i].id
                << setw(10) << student[i].name
                << setw(10) << student[i].gpa
                << setw(10) << student[i].course
                << student[i].date << "-" << student[i].mon << "-" << student[i].year
                << endl;
        }
    }

    void add_students() {
        int addnum;
        cout << "How many students you want to add? ";
        cin >> addnum;
        Student* new_s = new Student[addnum];
        cout << "Enter new student information" << endl << endl;
        for (int i = 0; i < addnum; i++) {
            cout << "ID: ";
            cin >> new_s[i].id;
            cout << "Name: ";
            cin >> new_s[i].name;
            cout << "GPA: ";
            cin >> new_s[i].gpa;
            cout << "Course: ";
            cin.ignore();
            getline(cin, new_s[i].course);
            cout << "Join Time: " << endl;
            cout << "Date: ";
            cin >> new_s[i].date;
            cout << "Month: ";
            cin >> new_s[i].mon;
            cout << "Year: ";
            cin >> new_s[i].year;
        }
        add_data(new_s, addnum);
        delete[] new_s;
    }

    void add_data(Student* new_stu, int new_size) {
        Student* temp = new Student[size + new_size];
        for (int i = 0; i < size; i++) {
            temp[i] = student[i];
        }
        for (int i = 0; i < new_size; i++) {
            temp[size + i] = new_stu[i];
        }
        delete[] student;
        student = temp;
        size += new_size;
    }
	
    void search_students() {
        system("cls");
        int search_choice;
        
        cout << "Search by:" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. GPA" << endl;
        cout << "4. Course" << endl;
        cout << "5. Join Time" << endl;
        cout << ">>>>>";
        cin >> search_choice;
        cout << endl;

        int index = -1;

        switch (search_choice) {
        case 1: {
            string search_id;
            cout << "-----------------------" << endl;
            cout << "     Search By ID      " << endl;
            cout << "-----------------------" << endl;
            cout << "Enter ID: ";
            cin >> search_id;
            string* idArray = new string[size];
            for (int i = 0; i < size; i++) {
                idArray[i] = student[i].id;
            }
            index = Search_String(idArray, size, search_id);
            delete[] idArray;
            break;
        }
        case 2: {
            string search_name;
            cout << "-----------------------" << endl;
            cout << "     Search By Name      " << endl;
            cout << "-----------------------" << endl;
            cout << "Enter Name: ";
            cin >> search_name;
            string* nameArray = new string[size];
            for (int i = 0; i < size; i++) {
                nameArray[i] = student[i].name;
            }
            index = Search_String(nameArray, size, search_name);
            delete[] nameArray;
            break;
        }
        case 3: {
            float search_gpa;
            cout << "-----------------------" << endl;
            cout << "     Search By GPA      " << endl;
            cout << "-----------------------" << endl;
            cout << "Enter GPA: ";
            cin >> search_gpa;
            float* gpaArray = new float[size];
            for (int i = 0; i < size; i++) {
                gpaArray[i] = student[i].gpa;
            }
            index = Search_Float(gpaArray, size, search_gpa);
            delete[] gpaArray;
            break;
        }
        case 4: {
            string search_course;
            cout << "-----------------------" << endl;
            cout << "  Search By Course      " << endl;
            cout << "-----------------------" << endl;
            cout << "Enter Course: ";
            cin.ignore();
            getline(cin, search_course);
            string* courseArray = new string[size];
            for (int i = 0; i < size; i++) {
                courseArray[i] = student[i].course;
            }
            index = Search_String(courseArray, size, search_course);
            delete[] courseArray;
            break;
        }
        case 5: {
            string search_time;
            cout << "-----------------------" << endl;
            cout << "  Search By Join Time   " << endl;
            cout << "-----------------------" << endl;
            cout << "Enter Join Time (dd-mm-yyyy): ";
            cin >> search_time;
            string* timeArray = new string[size];
            for (int i = 0; i < size; i++) {
                ostringstream ss;
                ss << student[i].date << "-" << student[i].mon << "-" << student[i].year;
                timeArray[i] = ss.str();
            }
            index = Search_String(timeArray, size, search_time);
            delete[] timeArray;
            break;
        }
        }

        if (index != -1) {
            system("cls");
            cout << "Student found!" << endl;
            display_student(index);
        }
        else {
            cout << "Student not found!" << endl;
        }
    }

    int Search_String(string A[], int size, string key) 
	{
        int left = 0;
        int right = size - 1;

        while (left <= right) 
		{
            int mid = left + (right - left) / 2;

            if (A[mid] == key)
                return mid;
            else if (A[mid] < key)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    int Search_Float(float A[], int size, float key) {
        int left = 0;
        int right = size - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (A[mid] == key)
                return mid;
            else if (A[mid] < key)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    void display_student(int index) {
        cout << "Student ID: " << student[index].id << endl;
        cout << "Student Name: " << student[index].name << endl;
        cout << "Student GPA: " << student[index].gpa << endl;
        cout << "Course: " << student[index].course << endl;
        cout << "Join Time: " << student[index].date << "-" << student[index].mon << "-" << student[index].year << endl;
    }

    //jm
    void jump_search() {
        int schoice;
        cout << "Search by:" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. GPA" << endl;
        cout << "4. Join Time" << endl;
        cout << ">>>>>";
        cin >> schoice;

        switch (schoice) {
        case 1:
            jump_id();
            break;
        case 2:
            jump_name();
            break;
        case 3:
            jump_gpa();
            break;
        case 4:
            // jump_time();
            break;
        }
    }

    void jump_id() {
        string* arr_id = new string[size];
        for (int i = 0; i < size; i++)
            arr_id[i] = student[i].id;

        string j_id;
        cin.ignore();
        cout <<"Enter the id that you want to search: ";
        getline(cin, j_id);
        int j_index = jump_search_string(arr_id, j_id, size);

        if (j_index != -1)
            jump_display(j_index);
        else
            cout << "The student not found" << endl;

        delete[] arr_id;
    }

    void jump_gpa() {
        float* arr_gpa = new float[size];
        for (int i = 0; i < size; i++)
            arr_gpa[i] = student[i].gpa;

        float j_gpa;
        cout << "Enter the gpa that you want to search: ";
        cin >> j_gpa;
        int j_index = jump_search_float(arr_gpa, j_gpa, size);
        if (j_index != -1)
            jump_display(j_index);
        else
            cout << "The student not found" << endl;

        delete[] arr_gpa;
    }

    void jump_name() {
        string* arr_name = new string[size];
        for (int i = 0; i < size; i++)
            arr_name[i] = student[i].name;

        string j_name;
        cin.ignore();
        cout << "Enter the name that you want to search: ";
        getline(cin, j_name);

        int j_index = jump_search_string(arr_name, j_name, size);
        if (j_index != -1)
            jump_display(j_index);
        else
            cout << "The student not found" << endl;

        delete[] arr_name;
    }

    int jump_search_string(string* arr, string x, int n) {
        int start = 0; // the block start
        int end = sqrt(n); // the block end, block jump size

        // check if the target is in the range of blocks
        // if yes, the while loop will stop
        // then do linear search in the block
        while (arr[min(end, n)-1]<x) {
            start = end; // update start to next block
            end += sqrt(n); // update end to next block

            // if current end value is bigger then array size
            // return false
            if (start>= n)
                return -1;
        }
        // do linear search
        for (int i = start; i <= end; i++) 
            if (arr[i] == x) // element found, return index
                return i;
                
        return -1; // not found
    }

    int jump_search_float(float* arr, float x, int n) {
        int start = 0; // the block start 
        int end = sqrt(n); // the block end, block jump size

        // check if the target is in the range of blocks
        // if yes, the while loop will stop
        // then do linear search in the block
        while (arr[end] < x && end < n) {
            start = end; // update start to next block
            end += sqrt(n); // update end to next block

            // if current end value is bigger then array size
            // assign end to the last position of the array
            if (start >= n)
                return -1;
        }
        // do linear search
        for (int i = start; i <= end; i++) {
            if (arr[i] == x) // element found, return index
                return i;
        }
        return -1; // not found
    }

    void jump_display(int result) {
        cout << "----------------" << endl;
        cout << "The result :" << endl;
        cout << student[result].id << endl << student[result].name << endl;
    }
    
    	void printStudents(Student s[], int n) 
	{
		
	    cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "GPA" << setw(10) << "Course" << setw(15) << "Join Time" << endl;
	    
	    for (int i = 0; i < n; ++i) 
		{
	        cout << left << setw(5) << s[i].id << setw(15) << s[i].name << setw(5) << s[i].gpa << setw(10) << s[i].course<<s[i].date<<"-"<<s[i].mon<<"-"<<s[i].year<<endl;
	    }
	    cout<<endl;
	    
        }
        
        void set2menu()
        {
        int choi;
        cout << "Original list of students:\n";
		cout << "******************************\n";
		printStudents(student,size);
        cout << "---------------------------------------------------------------------" << endl;
	    cout<<"1.Cocktail Sorting"<<endl;
	    cout<<"2.Ubiquitous Binary Search"<<endl;
	    cout<<"3.Back to previous menu"<<endl;
	    cout << "---------------------------------------------------------------------" << endl;
	    cin >> choi;

		        switch (choi) 
				{
			        case 1:
			            cocktailSort_Menu();
			            break;
			        case 2:
			            search_students() ;
			            break;
			        case 3:
			            return;
			            break;
				}
	    
	}
		void cocktailSort_Menu()
		{
			char choi;
			cout << "Original list of students:\n";
			cout << "******************************\n";
    		printStudents(student,size);
    		
    		
			cout << "Select the field to sort by:\n";
		    cout << "1. ID\n";
		    cout << "2. Name\n";
		    cout << "3. GPA\n";
		    cout << "4. Join Time\n";
		    cin >> choi;
		    
		    
		    CocktailSort(student, size, choi);
		    
		    cout << "Sorted list of students:\n";
	    	printStudents(student,size);
		}
		
		void CocktailSort(Student s[], int n, char choi) 
		{
			    bool swapped = true;
			    int start = 0;
			    int end = n - 1;

			    while (swapped) 
				{
			        swapped = false;
			
			        for (int i = start; i < end; ++i) 
					{
			            bool condition = false;
			            
				            switch (choi) 
							{
				                case '1': condition = s[i].id > s[i + 1].id; break;
				                case '2': condition = s[i].name > s[i + 1].name; break;
				                case '3': condition = s[i].gpa > s[i + 1].gpa; break;
				                case '4': {
                    
						                    int date1 = s[i].year * 10000 + s[i].mon * 100 + s[i].date;
						                    int date2 = s[i + 1].year * 10000 + s[i + 1].mon * 100 + s[i + 1].date;
						                    condition = date1 > date2;
						                    break;
                					  	  }	
				               
				            }
			            
				            if (condition)
							 {
				                swap(s[i], s[i + 1]);
				                swapped = true;
				             }
			             
			        }
			
			        if (!swapped)
			            break;
			
			        swapped = false;
			        --end;
			
			        for (int i = end - 1; i >= start; --i)
					 {
			            bool condition = false;
			            
			            switch (choi) 
						{
			                case '1': condition = s[i].id > s[i + 1].id; break;
			                case '2': condition = s[i].name > s[i + 1].name; break;
			                case '3': condition = s[i].gpa > s[i + 1].gpa; break;
			                case '4': {
                    
					                    int date1 = s[i].year * 10000 + s[i].mon * 100 + s[i].date;
					                    int date2 = s[i + 1].year * 10000 + s[i + 1].mon * 100 + s[i + 1].date;
					                    condition = date1 > date2;
					                    break;
                					  }
			                
			            }
			            
			            if (condition) 
						{
			                swap(s[i], s[i + 1]);
			                swapped = true;
			            }
			            
			        }
			        ++start;
			    }
		}
};


int main() {
    Student s[] =
    {
        {"1", "a", 1.2, "FIST", 12, 2, 2024},
        {"2", "b", 1.3, "FIST", 14, 12, 2023},
        {"3", "c", 1.4, "FOB", 22, 5, 2024},
        {"4", "d", 1.5, "FOB", 27, 6, 2024},
        {"5", "e", 1.6, "FET", 2, 6, 2024},
        {"6", "f", 1.7, "FET", 21, 6, 2024},
        {"7", "g", 1.8, "FET", 12, 6, 2024},
        {"8", "h", 1.9, "FIST", 13, 6, 2024}
    };

    int size = sizeof(s) / sizeof(s[0]);
    Main m(s, size);
    int choice;
    m.main_menu();
    cout << "Do you want to continue?(1=Yes, Other=No): ";
    cin >> choice;
    while (choice == 1) {
        m.main_menu();
        cout << "Do you want to continue?(1=Yes, Other=No): ";
        cin >> choice;
    }
    return 0;
}
