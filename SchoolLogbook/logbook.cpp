#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

class Student
{
private:
    void fillOutGrades(string s)
    {
        string sg; //I dont know how many digits do number representing number of grades has, so first I save it as a string
        int i = 1;
        while(s[i]!=' ')
        {
            sg = sg + s[i];
            i++;
        }
        int numOfGrades = stoi(sg); //I convert it to int
        grades = new int[numOfGrades]; //dynamically allocated array of grades

        //I save the grades in the int array
        //Grade is one digit number and I know that my grades are separated by space, hence the structure of for
        int r = 1;
        for(int j = 0; j < numOfGrades; j++)
        {
            grades[j] = s[i+r] - 48;
            r += 2;
        }
        this->numOfGrades = numOfGrades;
    }

public:
    int ID; //unique number for each Student
    int gradeBehavior; //in range 1-6 grade representing Student behavioural
    int numOfPrices; //number of Prices
    int *grades; //dynamically allocated array of grades
    int numOfGrades; //number of grades

    //unargumented contructor
    Student()
    {
        ID = -1;
        gradeBehavior = -1;
        numOfPrices = 0;
        numOfGrades = 0;
        grades = nullptr;
    }

   //two-argument contructor
    Student(int ID, string s)
    {
        this -> ID = ID;
        gradeBehavior = -1;
        numOfPrices = 0;
        fillOutGrades(s);
    }

    //copying contructor
    Student(const Student &oryginal)
    {
        this -> ID = oryginal.ID;
        this -> gradeBehavior = oryginal.gradeBehavior;
        this -> numOfPrices = oryginal.numOfPrices;
        this -> numOfGrades = oryginal.numOfGrades;
        this -> grades = new int[numOfGrades];
        for(int i = 0; i < oryginal.numOfGrades; i++)
        {
            this->grades[i] = oryginal.grades[i];
        }
    }

    //method assigns a bevavior grade
    void newBehavior(string gr)
    {
        int grade = stoi(gr);
        this -> gradeBehavior = grade;
    }

    //method increases number of student's prices by 1
    void givePrice()
    {
        if(numOfPrices == -1)
            this -> numOfPrices = 1;
        else
            this -> numOfPrices += 1;
    }

    //metod checking if a Student has at least 5 grades >= 5
    bool goodGrades()
    {
        int s = 0;
            for(int i = 0; i < numOfGrades; i++)
            {
                if(grades[i] >=5 )
                    s++;
            }
        if(s >= 5)
            return true;
        return false;
    }

    //method return the average of student's grades
    float avgGrade()
    {
        int s = 0;
        for(int i = 0; i < numOfGrades; i++)
        {
            s += grades[i];
        }
        return s/(float)numOfGrades;
    }

    //function prints out information about a Student
    void StudentInfo()
    {
        cout << "Student with ID " << ID << endl;
        cout << "behavior: " << gradeBehavior << endl;
        cout << "number of prices: " << numOfPrices << endl;
        cout << "grades: ";
        for(int i = 0; i < numOfGrades; i++)
            cout << grades[i] << " ";
        cout << endl << endl;
    }

    //destructor
    ~Student()
    {
        delete []grades;
    }
};

class Group
{
private:
    static int ID; //ID generates new ID for a Student or a candidate for a Student in the Group
    static int nowyID()
    {
        ID += 5;
        return ID;
    }

public:
    Student *arr[30]; //an array of indicators stores indicators on Students in the Group
    int numOfStudents; //current number of Students in the Group
    int GID; //ID of the Group

    //unargumented contructor
    Group()
    {
        for(int i = 0; i < 30; i++)
            arr[i] = nullptr;
        numOfStudents = 0;
        GID = -1;
    }

    //two-argumented contructor
    Group(int GID)
    {
      this->GID = GID;
      numOfStudents = 0;
      for(int i = 0; i < 30; i++)
            arr[i] = nullptr;
    }

    //method adds a new Student to the Group
    void newStudent(string s, string behavior)
    {
       if(numOfStudents < 30) //the maximum number of Students in the Group is 30
       {
           arr[numOfStudents] = new Student(nowyID(),s);
           arr[numOfStudents] -> newBehavior(behavior);
           numOfStudents +=1;
           this -> numOfStudents = numOfStudents;
       }
       else //if the Group is full, the Student with the lowest average is replaced with the new Student. (If they have higher average grade)
       {
           float lowest = arr[0]->avgGrade(); //I am looking for the lowest average of grades in the Group
           int index = 0;
           for(int i = 1; i < 30; i++)
           {
               if(arr[i]->avgGrade() < lowest)
               {
                   lowest = arr[i]->avgGrade();
                   index = i;
               }
           }

           Student *u = new Student(nowyID(), s); //the indicator on a new candidate for a Student in the Group
           if(u->avgGrade() < lowest)
                delete u;
           else //I replace the candidate for a Student in the Group with a Student with the lowest grades
           {
                delete arr[index];
                arr[index] = u;
                arr[index] -> newBehavior(behavior);
           }
       }
    }

    //method returns the best average of grades in the Group
    float avgBest()
    {
        float maxs = arr[0]->avgGrade();
        for(int i = 0; i < numOfStudents; i++)
            if(arr[i]->avgGrade() > maxs)
                maxs = arr[i]->avgGrade();
        return maxs;
    }

    //destructor
    ~Group()
    {
        for(int i = 0; i < numOfStudents; i++)
            delete arr[i];
    }

    //method prints information about the group
    void thisGroup()
    {
        cout << "Group ID " << GID << endl;
        cout << "Number of students: " << numOfStudents << endl;
        cout << "Students in the group: " << endl;
        for(int i = 0; i < numOfStudents; i++)
            cout << arr[i]->ID << " ";
        cout << endl << endl;
    }
};
int Group::ID = 0;

//Main function reads the file with the information about the students, and adds the students to the groups
//based on average grade, highest number of grades >= 5 and best behavior special prices are granted to the students
int main()
{
    Group school[8]; //array of 8 Groups
    for(int i = 0; i < 8; i++)
        school[i] = Group(i+1); //with ID numbers in range 1-6

    //obtaining information about the students from a file
    fstream file;
    file.open("students.txt");
    if(!file.good())
        {
            return -1;
        }

    else
    {
        string GID, beh, grad; //variables for: groups ID, behavior grade, list of grades for a given student
        while(file.good())
        {
            file >> GID >> beh;
            int index = stoi(GID)-1;
            getline(file, grad);
            school[index].newStudent(grad, beh);
        }

       //in this for loop special prices are granted to the Students
       float best = -1; //variable stores the highest average of grades
       for(int j = 0; j < 8; j++)
       {
            for(int i = 0; i < school[j].numOfStudents; i++)
            {
                if(school[j].arr[i]->avgGrade() == school[j].avgBest()) //price granted for students with the best average grade in their group
                    {
                        if(school[j].arr[i]->avgGrade() > best)
                            best = school[j].arr[i]->avgGrade();
                        school[j].arr[i]->givePrice();
                    }

                if(school[j].arr[i]->gradeBehavior == 6) //price granted for students with behavior grade = 6
                        school[j].arr[i]->givePrice();

                if(school[j].arr[i]->goodGrades()) //price granted for students with the over 5 number of grades >= 5
                    school[j].arr[i]->givePrice();
            }
        }

        //in this for loop number of special prices are summed up
        int s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0;
        for(int j = 0; j < 8; j++)
        {
            for(int i = 0; i < school[j].numOfStudents; i++)
            {
                if(school[j].arr[i]->avgGrade() == best) //price granted for student with the best overall average grades
                {
                    school[j].arr[i]->givePrice();
                    cout << "Student with the highest avg grade of: " << setprecision(3) << best << " is:" << endl;
                    school[j].arr[i]->StudentInfo();
                }
                if(school[j].arr[i] -> numOfPrices == 0)
                    s0++;

                else if(school[j].arr[i] -> numOfPrices == 1)
                    s1++;

                else if(school[j].arr[i]->numOfPrices == 2)
                    s2++;

                else if(school[j].arr[i]->numOfPrices == 3)
                    s3++;

                else if(school[j].arr[i]->numOfPrices == 4)
                    s4++;
            }
        }
        cout << s0 << " students got no special prices" << endl;
        cout << s1 << " students got 1 special price" << endl;
        cout << s2 << " students got 2 special prices" << endl;
        cout << s3 << " students got 3 special prices" << endl;
        cout << s4 << " students got 4 special prices" << endl;
    file.close();

    return 0;
    }
}
