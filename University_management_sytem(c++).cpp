//___Header Files_____
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

// ________Prototypes_____
void mainHeader();
char adminMenu();
void clearScreen();
string loginMenu();
void addStudent();
void viewAllStudents();
void subheader();
char studentMenu();
void addStudentIntoArray(string name, int matric, int fsc, int ecat, string p1, string p2, string p3);
int seatManagementMenu();
void viewSeatsDetails();
void addUser(string name, string pass, string role);
void print_Recd();
int getMaxIndex(int);
float aggregate(float mMarks, float fMarks, float eMarks);
void generate_Mlist();
int studentInfo();
void swap(int, int);
bool isEligible(string);
void load();
void save();

//________Data Structures________
const int MAX_RECORDS = 20;
string usernameA[MAX_RECORDS];
string passwordsA[MAX_RECORDS];
string rolesA[MAX_RECORDS];
int userCount = 0;
int count = 0;

string student_name[MAX_RECORDS];
float student_ecat[MAX_RECORDS];
float student_matric[MAX_RECORDS];
float student_fsc[MAX_RECORDS];
string student_pref1[MAX_RECORDS];
string student_pref2[MAX_RECORDS];
string student_pref3[MAX_RECORDS];
string mDepartments[MAX_RECORDS];
float aggr[MAX_RECORDS];
int entry_count = 0;

string department[] = {"CS", "CE", "EE"};
int seats[] = {0, 0, 0};
int capacity = 0;
bool announce = false;

string username;
//_____ Main function_____
main()
{
    void load();
    addUser("admin", "123", "ADMIN"); //___DEFAULT VALUE SET___

   string who = " ";
   while (true)
   {
      who = loginMenu();
      if (who == "ADMIN")
      {
         char option = ' ';
         while (true)
         {
            system("cls");
            option = adminMenu();
            if (option == '1')
            {
               addStudent();
            }
            else if (option == '2')
            {
               viewAllStudents();
            }
            else if (option == '3')
            {
               //----------Print the record in merit order
               print_Recd();
               viewAllStudents();
            }
            else if (option == '4')
            {
               //------------ Generate merit list
               generate_Mlist();
            }
            else if (option == '5')
            {
               //------------ Add Users
               cout << "Enter username........ ";
               string username;
               cin >> username;

               cout << "Enter password........ ";
               string pass;
               cin >> pass;

               cout << "Enter role........";
               string role;
               cin >> role;
               addUser(username, pass, role);
            }
            else if (option == '6')
            {
               while (true)
               {
                    system("cls");
                    int dpIndex = seatManagementMenu();
                    if (dpIndex == 1 || dpIndex == 2 || dpIndex == 3)
                    {
                        cout << "Enter New Capacity for " << department[dpIndex - 1] << endl;
                        cin >> capacity;
                        seats[dpIndex - 1] = capacity;
                    }
                    else if (dpIndex == 4)
                    {
                        viewSeatsDetails();
                        clearScreen();
                    }
                    else if (dpIndex == 5)
                    {
                        break;
                    }
                    else
                    {
                        cout << "You chose wrong option!" << endl;
                        clearScreen();
                    }
               } //end of seats management
            }
            else if (option == '7')
            {
               cout << "Press 2 to Announce the Result ";
               int annouce;
               cin >> annouce;
               if (annouce == 2)
               {
                  announce = true;
               }
            }
            else if (option == '8')
            {
               save();
               break;
            }
            else
            {
               cout << "You Chose Wrong option " << endl;
            }
            clearScreen();
         } //end of admin wile loop
      }
      else if (who == "STUDENT")
      {
         char studentOption = ' ';
         while (true)
         {
            system("cls");
            studentOption = studentMenu();
            if (studentOption == '1')
            {
               // View student information
               int st_index = studentInfo();
               cout << student_name[st_index] << "\t" << student_matric[st_index] << "\t" << student_fsc[st_index] << "\t" << student_ecat[st_index] << "\t" << aggr[st_index] << endl;
            }
            else if (studentOption == '2')
            {
               if (announce)
               {
                    int st_index = studentInfo();
                    if(mDepartments[st_index] != ""){
                        cout << "You are eligible for admission in " << mDepartments[st_index] << " department" << endl;
                    }
                    else {
                        cout << "You are not eligible for admission" << endl;
                    }
               }
               else
               {
                    cout << "Result is not announced yet " << endl;
               }
            }
            else if (studentOption == '3')
            { //___logout option___
               break;
            }
            else
            {
               cout << "Wrong selection! Try again";
            }
            clearScreen();
         } //end of student menu while loop
      }
      else if (who == "EXIT")
      {
         cout << "choose correct option" << endl;
      }
      else
      {
         cout << "You entered wrong option " << endl;
      }
      clearScreen();
   } //end of while

} //end of main function

//_________ Function definitions____
void mainHeader()
{
   cout << "----------------------------------------------" << endl;
   cout << "--- University Admission Management System ---" << endl;
   cout << "----------------------------------------------" << endl;
}

string loginMenu()
{ //___Get user credentials and check whether user is present in array or not__
   mainHeader();

   string uName, password;

   cout << "Enter username: ";
   cin >> uName;
   cout << "Enter password: ";
   cin >> password;

   for(int i = 0; i < userCount; i++){
       if(uName == usernameA[i]){
           if(password == passwordsA[i]){
               username = uName;
               return rolesA[i];
           }
           else {
               cout << "Invalid password" << endl;
               return "";
           }
       }
   }

   cout << "Username does not exist" << endl;
   return "";
}

int seatManagementMenu()
{ //___Discipline with capacity of student. this data should store in variable int seats[] = {0,0,0};__
   mainHeader();
   int option;

   cout << "Seat Management Menu > " << endl;
   cout << "1- Edit CS Capacity " << endl;
   cout << "2- Edit CE Capacity " << endl;
   cout << "3- Edit EE Capacity " << endl;
   cout << "4- View Seats Details " << endl;
   cout << "5- Back " << endl;

   cout << "Choose option: ";
   cin >> option;

   return option;
}

void viewSeatsDetails()
{ //___View total seats according to discipline____
    for(int i = 0; i < sizeof(department)/sizeof(department[0]); i++){
        cout << "Capacity for students in " << department[i] << ": " << seats[i] << endl;
    }
}

char adminMenu()
{ //__Administrator level menu goes here___
   mainHeader();
   char opt;

   cout << "Admin Main Menu > " << endl;
   cout << "1- Add New Student " << endl;
   cout << "2- View All Students" << endl;
   cout << "3- Print the record in merit order " << endl;
   cout << "4- Generate Merit " << endl;
   cout << "5- Add Users " << endl;
   cout << "6- Seat Management " << endl;
   cout << "7- Announce Result " << endl;
   cout << "8- Logout " << endl;
   cout << " Choose Your Option : ";
   
   cin >> opt;
   return opt;
}

char studentMenu()
{ //____Student or user menu, what user can choose____
   mainHeader();
   char opt;

   cout << "Student Main Menu > " << endl;
   cout << "1- View Your Profile " << endl;
   cout << "2- Check Admission Status " << endl;
   cout << "3- Logout " << endl;
   cout << " Choose Your Option : ";
   cin >> opt;

    return opt;
}

void clearScreen()
{ //_clear screen__
   cout << "Press any key to continue " << endl;
   getch();
   system("CLS");
}

void addStudent()
{ //___Get student data and their preferences___
    string sName, pref1, pref2, pref3;
    int sFsc, sMatric, sEcat;

    cout << "Enter name: ";
    cin >> sName;
    cout << "Enter matric marks: ";
    cin >> sMatric;
    cout << "Enter fsc marks: ";
    cin >> sFsc;
    cout << "Enter ecat marks: ";
    cin >> sEcat;

    // cout << "Departments available:" << endl;
    // for(int i = 0; i < sizeof(department)/sizeof(department[0]); i++){
    //     cout << department[i] << "\t";
    // }
    // cout << endl;

    subheader();

    cout << "Enter first preference: ";
    cin >> pref1;
    cout << "Enter second preference: ";
    cin >> pref2;
    cout << "Enter third preference: ";
    cin >> pref3;

    addStudentIntoArray(sName, sMatric, sFsc, sEcat, pref1, pref2, pref3);
}

void addStudentIntoArray(string name, int matric, int fsc, int ecat, string p1, string p2, string p3)
{ //___Store student data into array___each time addStudent() function is called. it will store into global array
    student_name[entry_count] = name;
    student_matric[entry_count] = matric;
    student_fsc[entry_count] = fsc;
    student_ecat[entry_count] = ecat;
    aggr[entry_count] = aggregate(matric, fsc, ecat);
    student_pref1[entry_count] = p1;
    student_pref2[entry_count] = p2;
    student_pref3[entry_count] = p3;
    entry_count++;
}
void viewAllStudents()
{ //__Retrieve student data and show on screen__
    cout << "Name\tMatric\tFSc\tECat\tAggregate\t1st pref\t2nd pref\t3rd pref" << endl;
    for(int i = 0; i < entry_count; i++){
        cout << student_name[i] << "\t" << student_matric[i] << "\t" << student_fsc[i] << "\t" << student_ecat[i] << "\t" << aggr[i] << "\t" << student_pref1[i] << "\t" << student_pref2[i] << "\t" << student_pref3[i] << endl;
    }
}

void subheader()
{ //___header for preference___
   cout << "   Enter the Name for Preferences    " << endl;
   cout << "****************" << endl;
   cout << "Choose between these disciplines " << endl;
   cout << "1- CS for Compter Science" << endl;
   cout << "2- CE for Compter Engineering" << endl;
   cout << "3- EE for Electrical Engineering" << endl;
   cout << "****************" << endl;
}

void addUser(string name, string pass, string role)
{ //___Add user, only admin can add____
    usernameA[userCount] = name;
    passwordsA[userCount] = pass;
    rolesA[userCount] = role;
    userCount++;
}

float aggregate(float mMarks, float fMarks, float eMarks)
{
    float obtained = mMarks * 0.25 + fMarks * 0.25 + eMarks * 0.5;
    return obtained;
}

void print_Recd()
{ //____calculate & sort in merit order____
    for(int i = 0; i < entry_count; i++){
        swap(i, getMaxIndex(i));
    }
}

void generate_Mlist()
{ //______Generate merit according to discipline a student get admit_____
    for(int i = 0; i < entry_count; i++){
        if(isEligible(student_pref1[i])){
            mDepartments[i] = student_pref1[i];
            cout << student_name[i] << " is eligible for admission in " << student_pref1[i] << endl;
        }
        else if(isEligible(student_pref2[i])){
            mDepartments[i] = student_pref2[i];
            cout << student_name[i] << " is eligible for admission in " << student_pref2[i] << endl;
        }
        else if(isEligible(student_pref3[i])){
            mDepartments[i] = student_pref3[i];
            cout << student_name[i] << " is eligible for admission in " << student_pref3[i] << endl;
        }
        else {
            mDepartments[i] = "";
        }
    }
}

int studentInfo()
{ //_____Student as user info___
    for(int i = 0; i < userCount; i++){
        if(username == student_name[i]){
            return i;
        }
    }

    return -1;
}

int getMaxIndex(int start){
    int max = start;

    for(int i = start + 1; i < entry_count; i++){
        if(aggr[i] > aggr[max]){
            max = i;
        }
    }

    return max;
}

void swap(int idx1, int idx2){
    float tmpFloat = aggr[idx1];
    aggr[idx1] = aggr[idx2];
    aggr[idx2] = tmpFloat;

    tmpFloat = student_matric[idx1];
    student_matric[idx1] = student_matric[idx2];
    student_matric[idx2] = tmpFloat;

    tmpFloat = student_fsc[idx1];
    student_fsc[idx1] = student_fsc[idx2];
    student_fsc[idx2] = tmpFloat;

    tmpFloat = student_ecat[idx1];
    student_ecat[idx1] = student_ecat[idx2];
    student_ecat[idx2] = tmpFloat;

    string tmpString   = student_name[idx1];
    student_name[idx1] = student_name[idx2];
    student_name[idx2] = tmpString;

    tmpString = student_pref1[idx1];
    student_pref1[idx1] = student_pref1[idx2];
    student_pref1[idx2] = tmpString;

    tmpString = student_pref2[idx1];
    student_pref2[idx1] = student_pref2[idx2];
    student_pref2[idx2] = tmpString;

    tmpString = student_pref3[idx1];
    student_pref3[idx1] = student_pref3[idx2];
    student_pref3[idx2] = tmpString;
}

bool isEligible(string dept){
    if(dept == "CS" && seats[0] > 0){
        seats[0]--;
        return true;
    }
    else if(dept == "CE" && seats[1] > 0){
        seats[1]--;
        return true;
    }
    else if(dept == "EE" && seats[2] > 0){
        seats[2]--;
        return true;
    }

    return false;

}

void save()
{
    fstream file;
    file.open("studentdata.txt", ios::in);    
    for (int i = 0 ; i < entry_count ; i++)
    {
        file << student_name[i] << " " << student_matric[i] << " " << student_fsc[i] << " " << student_ecat[i] << " " << aggr[i] << " " << student_pref1[i] << " " << student_pref2[i] << " " << student_pref3[i] << endl;
    }
    file.close();
}


void load()
{
    fstream file;
    string ch;
    file.open("studentdata.txt", ios::in);    
    for (int i = 0 ; !file.eof();  i++)
    {
        file >> student_name[i];
        file >> student_matric[i]; 
        file >> student_fsc[i];
        file >> student_ecat[i];
        file >> aggr[i];
        file >> student_pref1[i];
        file >> student_pref2[i]; 
        file >> student_pref3[i];
        count++ ;
    }
    file.close();
}