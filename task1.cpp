#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student{
    int student_id;
    string name;
    string major;
    int total_credits;
    double gpa;
    Student* next;
};

struct Course{
    string course_code;
    string course_name;
    int credits;
    int capacity;
    int enrolled_count;
    string* prerequisites;
    int prereq_count;
    Course* next;
};

struct Enrollment{                          
    int student_id;
    string course_code;
    char grade;
    string semester;
    Enrollment* next;
};            

void add_student(Student*& student_list, int id, const string& name, const string& major){
    Student* s=new Student{id, name, major, 0, 0.0, nullptr};          
    s->next=student_list;
    student_list=s;                  
    // move on to next student                
}


Student* find_student(Student* student_list, int student_id){
    while(student_list){
        if(student_list->student_id == student_id) 
            return student_list;
        student_list=student_list->next;                      
        // move onto next if not at start
    } 
    return nullptr;                    
    // nullptr if not found
}

bool update_major(Student* student_list, int student_id, const string& new_major){
    Student* s=find_student(student_list, student_id);
    if(!s) 
        return false;         // doesnt exist
    s->major=new_major;       
    return true;
}


void remove_student(Student *& student_list, Enrollment *& enrollment_list, int student_id){
    Student* prev=nullptr;
    Student* current=student_list;
    while(current){
        if(current->student_id == student_id){
            if(prev) 
                prev->next=current->next;               //find id of student in list then delete   
            else 
                student_list=current->next;
            delete current;
            break;
        }
        prev=current;
        current=current->next;
    }
    Enrollment* en_prev=nullptr;
    Enrollment* en_current=enrollment_list;
    while(en_current){
        if(en_current->student_id == student_id){
            if(en_prev) 
                en_prev->next=en_current->next;
            else 
                enrollment_list=en_current->next;
            delete en_current;
            en_current=(en_prev ? en_prev->next : enrollment_list);
        } 
        else{
            en_prev=en_current;
            en_current=en_current->next;
        }
    }
}

void add_course(Course*& course_list, const string& code, const string& name, int credits, int capacity){
    Course* c=new Course{code, name, credits, capacity, 0, nullptr, 0, nullptr};
    c->next=course_list;
    course_list=c;
}

Course* find_course(Course* course_list, const string& code){
    while(course_list){
        if(course_list->course_code == code) 
            return course_list;
        course_list=course_list->next;
    }
    return nullptr;
}

void add_prerequisite(Course* course, const string& prereq_code){
    string* arr=new string[course->prereq_count + 1];
    for(int i=0; i<course->prereq_count; i++){ 
        arr[i]=course->prerequisites[i];      //make array for prereqs
    }
    arr[course->prereq_count]=prereq_code;
    delete[] course->prerequisites;
    course->prerequisites=arr;
    course->prereq_count++;
}

bool remove_course(Course*& course_list, Enrollment* enrollment_list, const string& course_code){
    Enrollment* e=enrollment_list;
    while(e){
        if(e->course_code == course_code) 
            return false;
        e=e->next;
    }
    Course* prev=nullptr;
    Course* current=course_list;
    while(current){
        if(current->course_code == course_code){
            if(prev) 
                prev->next=current->next;
            else 
                course_list=current->next;
            if(current->prerequisites) 
                delete[] current->prerequisites;
            delete current;
            return true;
        }
        prev=current;
        current=current->next;
    }
    return false;
}
// check if alr enrolled
bool already_enrolled(Enrollment* enrollment_list, int student_id, const string& course_code){
    while (enrollment_list) {
        if (enrollment_list->student_id == student_id && enrollment_list->course_code == course_code) 
            return true;
        enrollment_list=enrollment_list->next;
    }
    return false;
}
bool check_prerequisites(Enrollment* enrollment_list, Course* c, int id){
    for (int i=0; i<c->prereq_count; i++) {
        bool meets=false;
        Enrollment* e=enrollment_list;

        while (e) {
            if (e->student_id == id && e->course_code == c->prerequisites[i]) {
                if (e->grade == 'A' || e->grade == 'B' || e->grade == 'C' || e->grade == 'D') {
                    meets=true;
                    break;
                }
            }
            e=e->next;
        }
        if (!meets) 
            return false;
    }
    return true;
}
      
// check cred hour limit (max 18 for given semester)
bool check_credit_limit(Enrollment * enrollment_list, Course* course_list, int student_id, const string& semester, int new_course_credits){
    int sum=0;
    Enrollment* e=enrollment_list;
    while(e){
        if(e->student_id == student_id && e->semester == semester){
            Course* c=find_course(course_list, e->course_code);
            if(c) 
                sum+=c->credits;
        }
        e=e->next;
    }
    return (sum+new_course_credits) < 19;
}

// enroll in course with validation
bool enroll_student(Student* student_list, Course* course_list, Enrollment*& enrollment_list, int student_id, const string& course_code, const string& semester){
    Student* s=find_student(student_list, student_id);
    if(!s) 
        return false;
    Course* c=find_course(course_list, course_code);
    if(!c) 
        return false;
    if(already_enrolled(enrollment_list, student_id, course_code)) 
        return false;
    if(!check_prerequisites(enrollment_list, c, student_id)) 
        return false;
    if(!check_credit_limit(enrollment_list, course_list, student_id, semester, c->credits))
        return false;
    if(c->enrolled_count >= c->capacity) 
        return false;
    Enrollment* e=new Enrollment{student_id, course_code, 'P', semester, enrollment_list};
    enrollment_list=e;
    c->enrolled_count++;
    return true;
}

// drop course
bool drop_course(Enrollment *& enrollment_list, Course* course_list, int student_id, const string& course_code){
    Enrollment* prev=nullptr;
    Enrollment* current=enrollment_list;
    while(current){
        if(current->student_id == student_id && current->course_code == course_code) {
            if(prev) 
                prev->next=current->next;
            else 
                enrollment_list=current->next;
            Course* c=find_course(course_list, course_code);
            if(c) 
                c->enrolled_count--;
            delete current;
            return true;
        }
        prev=current;
        current=current->next;
    }
    return false;
}

// assign grade to an enrollment
bool assign_grade(Enrollment* enrollment_list, int student_id, const string& course_code, char grade){
    while(enrollment_list){
        if(enrollment_list->student_id == student_id && enrollment_list->course_code == course_code){
            enrollment_list->grade=grade;
            return true;
        }
        enrollment_list=enrollment_list->next;
    }
    return false;
}

// update GPA based on all enrollments
void update_gpa(Student* student_list, Enrollment* enrollment_list, int student_id){
    Student* s=find_student(student_list, student_id);
    if(!s) 
        return;
    double sum = 0;
    int credits = 0;
    Enrollment* e=enrollment_list;
    while(e){
        if(e->student_id == student_id){
            double gpa=0;
            if(e->grade == 'A') 
                gpa=4;
            else if(e->grade == 'B') 
                gpa=3;
            else if(e->grade == 'C') 
                gpa=2;
            else if(e->grade == 'D') 
                gpa=1;
            else if(e->grade == 'F') 
                gpa=0;
            Course* c=nullptr;
            Course* temp=nullptr;
            temp=temp;
            credits+=(gpa > 0 ? find_course(temp, e->course_code)->credits : 0);
            if(gpa>0){
                Course* c2=find_course(temp, e->course_code);
                if(c2){
                    sum+=gpa * c2->credits;
                }
            }
        }
        e=e->next;
    }
    if(credits>0){
        s->gpa=sum / credits;
    } 
    else{
        s->gpa=0;
    }
    s->total_credits=credits;
}

void list_student_courses(Enrollment* enrollment_list, Course* course_list, int student_id, const string& semester) {
    Enrollment* e=enrollment_list;
    while(e){
        if(e->student_id == student_id && e->semester == semester){
            Course* c=find_course(course_list, e->course_code);
            if(c)
                cout<<c->course_code<<" - "<<c->course_name<<endl;
        }
        e=e->next;
    }
}

void list_course_students(Enrollment* enrollment_list, Student* student_list, const string& course_code) {
    Enrollment* e=enrollment_list;
    while(e){
        if(e->course_code == course_code){
            Student* s=find_student(student_list, e->student_id);
            if(s) 
                cout<<s->name<<endl;
        }
        e=e->next;
    }
}

void generate_transcript(Student* student_list, Enrollment* enrollment_list, Course* course_list, int student_id) {
    Student* s=find_student(student_list, student_id);
    if(!s){
        cout<<"Student could not be found!"<<endl;
        return;
    }
    cout<<"Transcript for "<<s->name<<" "<<s->student_id<<endl;
    Enrollment* e=enrollment_list;
    while(e){
        if(e->student_id == student_id){
            Course* c=find_course(course_list, e->course_code);
            if(c){
                cout<<c->course_code<<" - "<<c->course_name<<" ("<<c->credits<<" credits) "<<"Grade: "<<e->grade<<" Semester: "<<e->semester<<endl;
            }
        }
        e=e->next;
    }
    cout<<"Total Credits: "<<s->total_credits<<" GPA: "<<s->gpa<<endl;
}
// overload << for Student

ostream& operator<<(ostream& out, const Student& s){
    out<<"ID: "<<s.student_id<<", Name: "<<s.name<<", Major: "<<s.major<<", Credits: "<<s.total_credits<<", GPA: "<<s.gpa<<endl;
    return out;
}


void save_system(Student* student_list, Course* course_list, Enrollment* enrollment_list){
    ofstream file_student("students.txt");
    while(student_list){
        file_student<<student_list->student_id<<","<<student_list->name<<"," <<student_list->major<<","<<student_list->total_credits<<","<<student_list->gpa<<endl;
        student_list=student_list->next;
    }
    file_student.close();
// save courses
    ofstream file_course("courses.txt");
    while(course_list){
        file_course<<course_list->course_code<<","<<course_list->course_name<<","<<course_list->credits<<","<<course_list->capacity;
        for(int i=0; i<course_list->prereq_count; i++){
            file_course<<","<<course_list->prerequisites[i];
        }
        file_course<<endl;
        course_list=course_list->next;
    }
    file_course.close();
// save enrollments
    ofstream file_enrol("enrollments.txt");
    while(enrollment_list){
        file_enrol<<enrollment_list->student_id<<","<<enrollment_list->course_code<<","<<enrollment_list->grade<<","<<enrollment_list->semester<<endl;
        enrollment_list=enrollment_list->next;
    }
    file_enrol.close();
}

// load system from files
void load_system(Student*& student_list, Course*& course_list, Enrollment*& enrollment_list){
    student_list=nullptr; 
    course_list=nullptr; 
    enrollment_list=nullptr;
    ifstream file_student("students.txt");
    int id, credits; 
    double gpa; 
    string name, major;
    while(file_student >> id){
        char comma;
        file_student>>comma;
        getline(file_student, name, ',');
        getline(file_student, major, ',');
        file_student>>credits>>comma>>gpa;
        add_student(student_list, id, name, major);
        Student* s=find_student(student_list, id);
        s->total_credits=credits;
        s->gpa=gpa;
    }
    file_student.close();
// load courses
    ifstream file_course("courses.txt");
    string code, cname;
    int ccredits, cap;
    while(getline(file_course, code, ',')){
        getline(file_course, cname, ',');
        file_course>>ccredits; 
        file_course.ignore();
        file_course>>cap; 
        file_course.ignore();
        add_course(course_list, code, cname, ccredits, cap);
    }
    file_course.close();
// load enrollments
    ifstream file_enrol("enrollments.txt");
    int sid; 
    string ccode, sem; 
    char grade;
    while(file_enrol >> sid){
        char comma;
        file_enrol>>comma; 
        getline(file_enrol, ccode, ',');
        file_enrol>>grade>>comma; // this reads the grade and the comma
        getline(file_enrol, sem);
        Enrollment* e=new Enrollment{sid, ccode, grade, sem, enrollment_list};
        enrollment_list=e;
    }
    file_enrol.close();
}

int main(){
    Student* students=nullptr;
    Course* courses=nullptr;
    Enrollment* enrollments=nullptr;

    int choice;
    while(choice != 12){
        cout<<"\n=== University Course Registration System ==="<<endl;
        cout<<"\n1. Load data from files"<<endl;
        cout<<"2. Save data to files"<<endl;
        cout<<"3. Add student"<<endl;
        cout<<"4. Add course"<<endl;
        cout<<"5. Enroll student in course"<<endl;
        cout<<"6. Drop course"<<endl;
        cout<<"7. Assign grade"<<endl;
        cout<<"8. List student courses (by semester)"<<endl;
        cout<<"9. List course students"<<endl;
        cout<<"10. Generate transcript"<<endl;
        cout<<"11. Remove student"<<endl;
        cout<<"12. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;

        if(choice == 1) 
            load_system(students, courses, enrollments);
        else if(choice == 2) 
            save_system(students, courses, enrollments);
        else if(choice == 3){
            int id; 
            string name, major;
            cout<<"Enter ID, Name, Major: ";
            cin>>id; 
            cin.ignore(); 
            getline(cin, name); 
            getline(cin, major);
            add_student(students, id, name, major);
        }
        else if(choice == 4){
            string code, name; 
            int credits, cap;
            cout<<"Enter Code, Name, Credits, Capacity: ";
            cin>>code; 
            cin.ignore(); 
            getline(cin, name); 
            cin>>credits>>cap;
            add_course(courses, code, name, credits, cap);
        }
        else if(choice == 5){
            int id; 
            string code, sem;
            cout<<"Enter Student ID, Course Code, Semester: ";
            cin>>id>>code>>sem;
            if(enroll_student(students, courses, enrollments, id, code, sem))
                cout<<"Enrolled successfully"<<endl;
            else 
                cout<<"Enrollment failed"<<endl;
        }
        else if(choice == 6){
            int id; 
            string code;
            cout<<"Enter Student ID, Course Code: ";
            cin>>id>>code;
            drop_course(enrollments, courses, id, code);
        }
        else if(choice == 7){
            int id; 
            string code; 
            char g;
            cout<<"Enter Student ID, Course Code, Grade: ";
            cin>>id>>code>>g;
            assign_grade(enrollments, id, code, g);
            update_gpa(students, enrollments, id);
        }
        else if(choice == 8){
            int id; 
            string sem;
            cout<<"Enter Student ID, Semester: ";
            cin>>id>>sem;
            list_student_courses(enrollments, courses, id, sem);
        }
        else if(choice == 9){
            string code;
            cout<<"Enter Course Code: ";
            cin>>code;
            list_course_students(enrollments, students, code);
        }
        else if(choice == 10){
            int id;
            cout<<"Enter Student ID: ";
            cin>>id;
            generate_transcript(students, enrollments, courses, id);
        }
        else if(choice == 11){
            int id;
            cout<<"Enter Student ID: ";
            cin>>id;
            remove_student(students, enrollments, id);
        }
    }
return 0;
}
