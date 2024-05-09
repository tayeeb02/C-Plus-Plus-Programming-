// === Region: Project Overview ===
//
//  COMP2011 Fall 2023
//  PA3: A Simplified Version of USTSPAC
//
//  Your name: KALAM, Tayeeb Bin
//  Your ITSC email:   tbkalam@connect.ust.hk
//
//  Project TA: PAPPAS Christodoulos (cpappas@connect.ust.hk); 
//              XU Shuangjie (shuangjie.xu@connect.ust.hk)
//
//  For code-level questions, please send a direct email to the above TA.
//  Asking questions with code  in a public discussion forum (e.g., Piazza) may
//  cause plagiarism issues Usually, you will get the quickest response via a
//  direct email.
//
// =====================================

// === Region: Header files ===
// Necessary header files are included,
// DO NOT include extra header files
// ============================
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

const int MAX_RANKING_STARS =
    5; // at most a 5-star ranking in coments (from 1-star)
const int MAX_TITLE =
    100; // at most 100 characters (including the NULL character)

// A sorted linked list of StockItem, sorted by its id
struct Student {
  unsigned int sid;     // id is an unique identifier of the Student (e.g., 39)
  char name[MAX_TITLE]; // title is a description of the Course (e.g., History)
  unsigned int ranks_count; // The total number of star_ranks on existing
                               // courses the student did until now
  Student *next;               // The pointer pointing to the next Student
};

struct StarRank {
  unsigned int star; // The star-ranking the student gave to that course
  Student *student;  // The pointer showing to the struct of the student that
                     // made the star_rank
  StarRank *next;     // The pointer pointing to the StarRanks struct
};

// A sorted linked list represents a shopping cart, sorted by item->id
struct Course {
  unsigned int course_id; // course_id is an unique identifier of the Course
                          // (e.g., History)
  char name[MAX_TITLE];   // The course name
  int stars_count[MAX_RANKING_STARS]; // The count of stars from 1 (lowest) to
                                      // MAX_RANK (highest rank) of the course
  StarRank *star_rank_head; // The pointer pointing to the StarRanks struct
};

Student *create_student(const unsigned int sid, const char name[MAX_TITLE]) {
  Student *new_student = new Student;
  new_student->sid = sid;
  strcpy(new_student->name, name);
  new_student->ranks_count = 0;
  new_student->next = nullptr;
  return new_student;
}

Course *create_course(const unsigned int course_id,
                      const char name[MAX_TITLE]) {
  Course *new_course = new Course;
  new_course->course_id = course_id;
  strcpy(new_course->name, name);
  for (int i = 0; i < MAX_RANKING_STARS; i++) {
    new_course->stars_count[i] = 0;
  }
  new_course->star_rank_head = nullptr;
  return new_course;
}

// Given the number of courses, dynamicially creates and initializes the courses
// list array
Course **dynamic_init_course_array(const unsigned int num_courses) {
  Course **ret = nullptr;
  ret = new Course *[num_courses];
  for (int i = 0; i < num_courses; i++)
    ret[i] = nullptr;
  return ret;
}

// Helper function: search student and return prev, current
// return true if found an existing entry
// return false if an existing entry is not found
bool search_student(Student *head, const unsigned int sid, Student *&prev,
                    Student *&current) {
  prev = nullptr;
  for (current = head; current != nullptr; current = current->next) {
    if (current->sid == sid) {
      // found an existing entry
      return true;
    } else if (current->sid > sid) {
      // cannot find an existing entry
      return false;
    }
    prev = current;
  }
  return false;
}

// Helper function: search star_rank and return prev, current
// return true if found an existing entry
// return false if an existing entry is not found
bool search_star_rank(StarRank *head, const unsigned int sid, StarRank *&prev,
                    StarRank *&current) {
  prev = nullptr;
  for (current = head; current != nullptr; current = current->next) {
    if (current->student->sid == sid) {
      // found an existing entry
      return true;
    }
    prev = current;
  }
  return false;
}

// Helper function: search course and return prev, current
// return true if found an existing entry
// return false if an existing entry is not found
bool search_course(Course **&course_array, const unsigned int course_id,
                   const unsigned int num_courses, int &i) {
  Course *course;
  if (course_array != nullptr) {
    for (i = 0; i < num_courses; i++) {
      course = course_array[i];
      if (course == nullptr) {
        break;
      }

      if (course->course_id == course_id) {
        // found an existing entry
        return true;
      }
    }
  }
  return false;
}

// Adds a new course in the courses array of pointers.
// If the course exists (there is a course with the course_id), return false.
// Else if the course does not exist and the array has empty space then insert the course and return true.
// Else if there is no empty space, double the array size (e.g., if the array has size 16, then increase it to size 32), and then add the course. Finally return true.
// The items of stars_count array of a newly added course must be all zero. Moreover, the star_rank_head field should be nullptr because there are no star ranks yet.

// @param: course_array the array of pointers for the Course
// @param: an unsigned integer representing the id of the course the student star ranks (course_id)
// @param: a characters array for the name of the course
// @param: an unsigned integer representing the number of courses until now.
bool add_course(Course **&course_array, const unsigned int course_id,
                const char name[MAX_TITLE], unsigned int &num_courses) {

  // TODO: Write code to implement add_course
  

  //Checking if the course exists. 

  for(int i = 0; i<num_courses; i++){
    if(course_array[i] != nullptr){
      if(course_id == course_array[i]->course_id){
        return false; //Exits the function if there is a match. 
    }
    }
  }

  //Checking if there is enough space in the Array. 
  

  //ARRAY SIZE
  //int array_size = sizeof(course_array)/sizeof(Course);

  //Checking if theres empty space

  bool space_available_in_array = false;
  
  for(int i = 0; i<num_courses; i++){
    if(nullptr == course_array[i]) {
      space_available_in_array = true;
      break; //no need to continue loop after even a single nullptr is discovered; 
    }
  }

  //if there's no space available, double the size. 
  if(false == space_available_in_array){
    num_courses = num_courses*2; //changing the value of the array. 
    cout << "increase course array size to " << num_courses << endl;
    Course **New_Course_Array = dynamic_init_course_array(num_courses); //creating a new course array. 
    for(int i = 0; i <(num_courses/2); i++){ //Copying only the elements of the small array to the larger array. 
      New_Course_Array[i] = course_array[i]; //Copying each element. 
    } 

    //Once each elements are copied, then we delete the previous array. Only the array not the things they point to. 
    delete [] course_array; //becomes a dangling pointer. 

    course_array = New_Course_Array; //Now the main course_array is pointing to the new course. 

  } 

  //Creating the course.
  Course *New_Course_Pointer = create_course(course_id,name);

  for(int i=0; i<num_courses; i++){
    if(nullptr == course_array[i]){
      course_array[i]= New_Course_Pointer; 
      return true; //Course Added to the function and it exits at the first sign of nullptr. 
    }
  }


  
  return false;
}


//Adds the star ranking of a student for a course.
//If the student or the course does not exist, return false.
//Else if the student already has a star ranking for that course then return return false.
//Else, add a star ranking, update the stars_count of the course, and increase by one the ranks_count of the student and return true.

// IMPORTANT: Always add in a new StarRank at the end of the list

// @param: student_head points to the head of Student list
// @param: the id of the student (sid)
// @param: course_array the array of pointers for the Course
// @param: the id of the course the student ranks (course_id)
// @param: the number of courses in the site
// @param: the rating which is a between 1 and MAX_RANKING_STARS
// @out: a boolean value indicating whether the insertion was successful
bool add_star_rank(Student *&student_head, unsigned int sid,
                 Course **&course_array, unsigned int course_id,
                 const unsigned int num_courses, int star) {
  // TODO: Write code to implement add_star_rank
  // use error cout carefully


  //CHECKING if Student Exists or not. 
  Student *Student_Pointer_Prev = nullptr; //Will point to previous node of the student and the current node of the student. 
  Student *Student_Pointer_Current = nullptr;
  bool Student_Exists= search_student(student_head,sid,Student_Pointer_Prev, Student_Pointer_Current);
  if(!Student_Exists){
    cout << "Failed to find student " << sid << " when add a star_rank." << endl;
    return false; 
  }

  //CHECKING if Course exists or not. 
  int CourseIndexCounter = 0;
  bool Course_Exists = search_course(course_array,course_id,num_courses, CourseIndexCounter);
  
  if(!Course_Exists){
    cout << "Failed to find course " << course_id << " when add a star_rank." << endl;
    return false; 
  }
  

  //CHECKING if the student already has a star rank for that course or not. 
  if(nullptr != course_array[CourseIndexCounter]->star_rank_head) {
    for(StarRank *pointer = course_array[CourseIndexCounter]->star_rank_head; pointer; pointer = pointer->next){
      if(sid == pointer->student->sid){ //SID already exists
      cout << "Failed to insert star_rank because the student " << sid
       << " already have a star_rank." << endl;
        return false;
      }
    }

    StarRank *EndPointer = nullptr;
    for(EndPointer = course_array[CourseIndexCounter]->star_rank_head; EndPointer ->next != nullptr; EndPointer = EndPointer->next){
      
    }

    StarRank *New_Star_Rank = new StarRank;
    New_Star_Rank ->star = star;
    New_Star_Rank ->student = Student_Pointer_Current;
    New_Star_Rank ->next = nullptr; //Because it must be added to the end of the list. 

    EndPointer->next = New_Star_Rank;

    course_array[CourseIndexCounter]->stars_count[star-1] +=1; //adding 1 to the stars count. 

    New_Star_Rank ->student ->ranks_count +=1; //updating ranks count for the student. 

    return true; //Once the student is added and the updates are done. 

  }
  else {//That becomes the head Pointer

    StarRank *New_Star_Rank = new StarRank;
    New_Star_Rank ->star = star;
    New_Star_Rank ->student = Student_Pointer_Current;
    New_Star_Rank ->next = nullptr; //Because it must be added to the end of the list. 

    course_array[CourseIndexCounter]->star_rank_head = New_Star_Rank; //Because it is the new Head pointer. 
    
    course_array[CourseIndexCounter]->stars_count[star-1] +=1; //adding 1 to the stars count. 

    course_array[CourseIndexCounter]->star_rank_head ->student ->ranks_count +=1; //updating ranks count for the student.

    return true; //Star Rank is added and the update is done.  

  }

  
  //cout << "Failed to find course " << course_id << " when add a star_rank." << endl;

  return false;
}

//Adds a student to the student's linked list.
//Takes as input the student id and its name and adds the student to the list, in increasing order based on its student id.
//Note that if the student already exists (there is a student with the same sid), then return false.
//Otherwise, add the student (maintaining the increasing order) and return true. A new student always has ranks_count = 0.
bool add_student(Student *&student_head, const unsigned int sid,
                 const char name[MAX_TITLE]) {
  // TODO: Write code to implement add_student


  //CASE 1: The Student List is empty. So create a new Student. student_head pointer will be null. 

  if (nullptr == student_head){
      student_head = create_student(sid,name); //This becomes the new head. 
      return true; //Function returns and exits from here and it does not go to the next parts. 
  }

  //CASE 2: The SID already exists. 
  for(Student *p = student_head; p!=nullptr; p = p->next) {
      if(sid == p->sid){
        return false; //Function returns without creating or adding new SID. 
      }
  }

  //Create a new Student Node using the SID and Name if not already in List. 
  Student *new_Student_Pointer = create_student(sid, name); 

  //CASE 3: the SID is somewhere from the first till last but not the last node

  Student *current = nullptr; //Creating a current pointer for traversing the Linked List. 
  Student *previous = nullptr; //Creating a previous pointer.
  
  for(current = student_head; current->next !=nullptr; previous = current, current = current->next) {
    
    if(current->sid >sid){//Checking if the current SID is larger than the new student SID

      if(nullptr == previous){//This means that it is still the head node.
          new_Student_Pointer->next = current; //the next node for this smaller SID is pointing to the head. 
          student_head = new_Student_Pointer; //Since the new node becomes the head, its address becomes the address of head node.
          return true; //Returns true since change was successfully done. 
      }
      else {
        //if it is anything other than the head node. 
        new_Student_Pointer -> next = current; //Since current SID is bigger than the new student, the new student next points to current. 
        previous->next = new_Student_Pointer; //Previous nodes next points to the new node. 
        return true; //New student added so return true and exit. 

      }
    }
  }


  //CASE 4: Dealing with the last node and comparison with SID. 

  if (current->sid < sid) { //new Student's SID is larger than last node, so it becomes last node. 
      current->next = new_Student_Pointer; //the last node points to new node which becomes the last node. 
      return true; // Function exits after its done. 

  }

  else { //The new student's SID is smaller than the last node. 

     new_Student_Pointer->next = current; //Points to the last one 

     if (nullptr == previous) { //meaning it is the first node. 
      new_Student_Pointer->next = student_head;
      student_head = new_Student_Pointer;
      return true; 

     }
     else {
      new_Student_Pointer->next = current;
      previous->next = new_Student_Pointer;
      return true;
     }

  }

  return false;
}

//Removes the star ranking of a student for a course.
//If the star ranking does not exist, return false.
//Else, delete the star ranking, decrease the ranks_count of the student with id sid, and
// update the new stars_count of the course with id course_id. Finally return true.

// @param: student_head points to the head of Student list
// @param: course_array the array of pointers for the Course
// @param: the id of the student (sid)
// @param: the id of the course the student ranks (course_id)
// @param: the number of courses in the site
// @out: a boolean value indicating whether the removal was successful
bool delete_star_rank(Student *&student_head, Course **&course_array,
                    const unsigned int sid, const unsigned int course_id,
                    const unsigned int num_courses) {
  // TODO: Write code to implement delete_star_rank

  //FIRST: Check if the course exists or not. 
  bool CourseExists = false; 
  int CourseIndexCounter = 0; 

  CourseExists = search_course(course_array, course_id, num_courses, CourseIndexCounter);

  if(!CourseExists){
    // use error cout carefully
        cout << "Failed to delete star_rank, course " << course_id << " not found."
       << endl;
       return false; 
    
  }

  //SECOND: Check if star_rank exists in the array. 

  StarRank *star_rank_previous = nullptr; 
  StarRank *star_rank_current = nullptr;

  bool StarRankExists = search_star_rank(course_array[CourseIndexCounter]->star_rank_head, sid, star_rank_previous, star_rank_current);

  if(!StarRankExists){
        cout << "Failed to delete star_rank, star_rank not found in course "
       << course_id << endl;
       return false; 
  }


  //NOW That the starrank exists in the course. 

  //STEP 1: Reduce the star count in the course rank. 
  int star = star_rank_current ->star; 
  course_array[CourseIndexCounter]->stars_count[star-1] -=1; //The rank got deleted so it gets removed. 


  //STEP 2: Change the rank count for the student. 
  star_rank_current->student->ranks_count -=1; //Decreased because the star rank got deleted. 

  //STEP 3: Delete the star rank. 
  if(nullptr == star_rank_previous){ //this means the one we are removing is the first node of the linked list.

   // nullptr == star_rank_previous is the same as star_rank_current == star_rank_head ie same address.  
    course_array[CourseIndexCounter]->star_rank_head = star_rank_current ->next; //the next node becomes the head. 

    delete star_rank_current; //Deleting that pointer. 
    star_rank_current  = nullptr;

    return true; //Function gets out after deleting the rank. 

  }
  else {
    star_rank_previous ->next = star_rank_current ->next; 

    delete star_rank_current; 
    star_rank_current = nullptr;
    return true; //Deleted. 

  } 

  /* 
  // use error cout carefully
  cout << "Failed to delete star_rank, course " << course_id << " not found."
       << endl;
  cout << "Failed to delete star_rank, star_rank not found in course "
       << course_id << endl;
  
  */
  
  return false;
}

//Takes as input a course_id and deletes the corresponding course.
//If the course does not exist, return false.
//Else if there are any star ranks, delete them, decrease the ranks_count of the corresponding students, and delete the course. Return true.
//If the course array has a size of N and N/2 entries are empty, decrease the array size by half (while maintaining the courses). Return true.

// ****IMPORTANT Notes****
// 1) Whenever you delete a class, you need to swap all the classes
// in the right of that class, one step left.
// For example, if we remove C4 from the array:
// [C1,C2,C3,C4,C5,C6,nullptr,nullptr]
// Then the resulting array will be:
// [C1,C2,C3,C5,C6,nullptr,nullptr,nullptr]

// 2) The minimum size of the array is 2.
// You MUST NOT reduce the size of the array to 1.

// @param: student_head points to the head of Student list
// @param: course_array the array of pointers for the Course
// @param: the id of the course the student ranks (course_id)
// @param: the number of courses in the site
// @out: a boolean value indicating whether the removal was successful
bool delete_course(Student *student_head, Course **&course_array,
                   const unsigned int course_id, unsigned int &num_courses) {
  // TODO: Write code to implement delete_course


   //FIRST: Check if the course exists or not. 
  bool CourseExists = false; 
  int CourseIndexCounter = 0; 

  CourseExists = search_course(course_array, course_id, num_courses, CourseIndexCounter);

  if(!CourseExists){
    // use error cout carefully
       cout << "Failed to delete course, course " << course_id << " not found." << endl;
       return false; 
  }
  else {
     //SECOND: Delete all the star_linked_list inside the code. 

  while(nullptr != course_array[CourseIndexCounter] ->star_rank_head){
    StarRank *first_node_pointer = course_array[CourseIndexCounter] ->star_rank_head; 
    /*
    for(StarRank *last_node_pointer = course_array[CourseIndexCounter]->star_rank_head; 
                                                    last_node_pointer->next != nullptr; 
                                                    last_node_pointer = last_node_pointer ->next) {

    }
    
    */
    

    bool Deletion_Status = delete_star_rank(student_head, course_array, first_node_pointer ->student -> sid, course_id, num_courses);
  }

  // THIRD: Delete the course inside the array. SO first delete the course pointer. Then make it point to the 

  // ---->>> Step 1: Deleting the course. 
  delete course_array[CourseIndexCounter];
  //Setting the array element to nullptr.
  course_array[CourseIndexCounter] = nullptr;

  // FOURTH: Moving each element one step to the left.

  for(int i = 0; i < num_courses-1; i++){
    if(nullptr==course_array[i] && course_array[i+1] != nullptr) {
      Course * temporary_variable = course_array[i];
      course_array[i] = course_array[i+1];
      course_array[i+1] = temporary_variable;
    }

    //All the swapping will be done here no matter what. 
  } 

  //FIFTH: Count the number of elements that are not null in the array. 
  int Array_Elements_Not_Null = 0; 
  for(int i = 0; i<num_courses; i++){
    if(course_array[i] !=nullptr){
      Array_Elements_Not_Null++; //Increase the number of array elements that are not null. 
    }

  }

  //SIXTH: Checking if half the array is empty or not. 

  if((Array_Elements_Not_Null <= (num_courses/2)) && num_courses >2) { //&& num_courses >2 
    //Create a new Array
    Course **New_Array_head = dynamic_init_course_array(num_courses/2);
    //COPY each element to the new array. 
    for(int i = 0; i< (num_courses)/2; i++){
      New_Array_head[i] = course_array[i];
    }

    //After all elements are copied to the new array head;
    delete [] course_array; //Deleting the old array. 

    course_array = New_Array_head; //Changing the address of course array to the new array. 

    

    cout << "reduce course array size to " << num_courses/2 << endl;

    //Change the num_courses variable.
    num_courses = num_courses/2;

  }

 // if (num_courses > 2){
   // num_courses = num_courses/2;
   // cout << "reduce course array size to " << num_courses << endl;
  //}
 // else {
   // cout << "reduce course array size to " << num_courses << endl;
  //}

  return true;



  }

 
}

void clean_up(Student *&student_head, StarRank *&star_rank_head,
              Course **&course_array, unsigned int &num_courses) {
  // delete all courses, be carefully for the memory leak
  while (course_array[0] != nullptr) {
    delete_course(student_head, course_array, course_array[0]->course_id,
                  num_courses);
  }

  if (student_head != nullptr) {
    Student *student;
    while (student_head->next != nullptr) {
      // remove student, need first delete all the star_rank of this student, and
      // then delete star_ranks in course remove_student(student_head, star_rank_head,
      // student_head->sid);
      student = student_head->next;
      student_head->next = student_head->next->next;
      delete student;
    }
    delete student_head;
    student_head = nullptr;
  }

  delete[] course_array; // delete the dynamically allocated 2D array
  course_array = nullptr;
}

// Display the data of all students in increasing order of their sid in the form:
// === Student List ([sid, name, ranks_count]) ===
// [sid, name and ranks_count] -> [...] -> ... -> [...]
// @param: student_head points to the head of Student list
void display_students(Student *student_head) {

  // TODO: Write the code to display students

  //Empty Linked List 
  cout << "=== Student List ([sid, name, star_rank count]) ===" << endl;

  if(nullptr == student_head){
    cout << "No items in the Student list" << endl; // Use this when no student exists
  }
  else{  
    

    for(Student *pointer = student_head; pointer; pointer= pointer->next){

      if(nullptr == pointer->next){ //checking if its the last node.
        cout << "[" << pointer->sid <<", "<< pointer->name << ", " << pointer->ranks_count << "]" << endl;
      }
      else{
        cout << "[" << pointer->sid <<", "<< pointer->name << ", " << pointer->ranks_count  << "]" << " -> ";
      }

    }

  }
  
  
}

//Display star ranks of the course given its id.
// In the form:
// star_ranks in course _COURSE_NAME_ : [star ranker sid : star] -> [...]

// @param: course_array the array of pointers for the Course
// @param: the number of courses in the site
// @param: the id of the course
void display_star_ranks(Course **course_array, const unsigned int num_courses,
                        const unsigned int course_id) {
  // TODO: Write the code to display star ranks
  // If the course exists but no star ranks exist yet,
  // use the following cout:
  // cout << "No StarRanks in the course " << __COURSE_NAME << endl; // __COURSE_NAME represents the name of the course


  //CHECKING IF THE COURSE EXISTS OR NOT IN THE FIRST PLACE. 

  bool Course_Exists = true; 
  int CourseIndexCounter = 0;
  Course_Exists  = search_course(course_array,course_id,num_courses,CourseIndexCounter);
  if (!Course_Exists){
    // If the course does not exist use the following cout:
    cout << "Course not found " << endl; // Display this if course not found
  }
  else{
      if(nullptr == course_array[CourseIndexCounter]->star_rank_head) //This is what happens when it has no star Ranks. star_rank_head is null. 
      {
        cout  << "star_ranks in course " << course_array[CourseIndexCounter]->name << " : " << "No StarRanks in the course " << course_array[CourseIndexCounter]->name << endl;
      }
      else{
        cout << "star_ranks in course " << course_array[CourseIndexCounter]->name << " : " ;
        for(StarRank *Pointer = course_array[CourseIndexCounter]->star_rank_head; Pointer; Pointer = Pointer->next) {
          if(nullptr == Pointer->next){
            cout << "[" << Pointer->student->sid << ": " << Pointer->star << "]" << endl;
          }
          else{
            cout << "[" << Pointer->student->sid << ": " << Pointer->star << "]" << " -> " ;
          }
        }
      }
  }
  


}

//Display all existing courses. For each course display its name and its star-ranking array in the form:
// course_id : _COURSE_ID_, name : _COURSE_NAME, stars_count:
//*     _one_star
//**    _two_stars
//***   _three_stars
//****  _four_stars
//***** _five_stars
// @param: course_array the array of pointers for the Course
// @param: the number of courses in the site
void display_courses(Course **course_array, const unsigned int num_courses) {
  // TODO: Write the code to display students
  bool Empty_Array = true;
  for(int i = 0; i<num_courses; i++){
    if(nullptr != course_array[i]){
      Empty_Array = false;
    }
  }

  if (true == Empty_Array){
    // If there is no course in the list, use the following cout:
    cout << "No course in the list " << endl;
  }
  else {
    for(int i = 0; i< num_courses; i++){
      if (course_array[i] != nullptr){
        cout << "course_id : " << course_array[i] ->course_id << ", name : " << course_array[i]->name << ", " << "stars_count :" << endl;
        cout << "*     " << course_array[i]->stars_count[0] << endl;
        cout << "**    "<< course_array[i] ->stars_count[1] << endl;
        cout << "***   " << course_array[i]->stars_count[2] << endl;
        cout << "****  " << course_array[i] ->stars_count[3] << endl;
        cout << "***** " << course_array[i] ->stars_count[4] << endl;
      }
    }

  }

  
  
}

// === Region: The main function ===
// The main function implementation is given
// DO NOT make any changes to the main function
// ============================
int main() {
  enum MeunOption {
    OPTION_DISPLAY_STUDENT_LIST = 0,
    OPTION_DISPLAY_COURSES,
    OPTION_DISPLAY_COMMENTS,
    // OPTION_DISPLAY_CURRENT_LIST,
    OPTION_INSERT_STUDENT,
    OPTION_INSERT_COURSE,
    OPTION_INSERT_COMMENT,
    OPTION_DELETE_COMMENT,
    OPTION_DELETE_COURSE,
    OPTION_EXIT_SYSTEM,
    MAX_MENU_OPTIONS
  };
  const int MAX_MENU_OPTIONS_LENGTH = 80;
  char menu_options[MAX_MENU_OPTIONS][MAX_MENU_OPTIONS_LENGTH] = {
      "Display student list",
      "Display courses",
      "Display star_ranks of course ",
      "Insert a new student to the student list",
      "Insert a new course to the course list",
      "Insert a new star_rank to the star_rank list",
      "Delete a star_rank by student id and course id",
      "Delete a course by course id",
      "Exit the system"};

  Student *student_head = nullptr;
  StarRank *star_rank_head = nullptr;
  Course **course_array = nullptr;
  unsigned int num_courses = 0;
  int i, option;
  unsigned int sid, course_id, star;
  char name[MAX_TITLE] = "";
  bool ret = false;

  num_courses = 2;
  course_array = dynamic_init_course_array(num_courses);

  cout << "=== Simplified USTSPAC System ===" << endl;
  while (true) {
    cout << "=== Menu ===" << endl;
    for (i = 0; i < MAX_MENU_OPTIONS; i++)
      cout << i + 1 << ": " << menu_options[i]
           << endl; // shift by +1 when display

    cout << "Enter your option: " << endl;
    cin >> option;
    option = option - 1; // shift by -1 after entering the option

    // The invalid menu option handling
    if (option < 0 || option >= MAX_MENU_OPTIONS) {
      cout << "Invalid option" << endl;
      continue;
    }

    // Exit operations handling
    if (option == OPTION_EXIT_SYSTEM) {
      clean_up(student_head, star_rank_head, course_array, num_courses);
      break; // break the while loop
    }

    switch (option) {
    case OPTION_DISPLAY_STUDENT_LIST:
      display_students(student_head);
      break;
    case OPTION_DISPLAY_COURSES:
      display_courses(course_array, num_courses);
      break;
    case OPTION_DISPLAY_COMMENTS:
      course_id = 0;
      cout << "Enter the course id: " << endl;
      cin >> course_id;
      if (course_id <= 0) {
        cout << "Enter a valid course id > 0" << endl;
        break;
      }
      display_star_ranks(course_array, num_courses, course_id);

      break;
    case OPTION_INSERT_STUDENT:
      sid = 0;
      cout << "Enter the student id: " << endl;
      cin >> sid;
      if (sid <= 0) {
        cout << "Enter a valid student id > 0" << endl;
        break;
      }
      cout << "Enter a name: " << endl;
      cin >> name;

      ret = add_student(student_head, sid, name);
      if (ret == false) {
        cout << "Failed to insert student " << sid << endl;
      } else {
        cout << sid << " is successfully inserted" << endl;
      }
      break;
    case OPTION_INSERT_COURSE:
      course_id = 0;
      cout << "Enter the course id: " << endl;
      cin >> course_id;
      if (course_id <= 0) {
        cout << "Enter a valid course id > 0" << endl;
        break;
      }
      cout << "Enter a name: " << endl;
      cin >> name;

      ret = add_course(course_array, course_id, name, num_courses);
      if (ret == false) {
        cout << "Failed to insert course " << course_id << endl;
      } else {
        cout << course_id << " is successfully inserted" << endl;
      }
      break;
    case OPTION_INSERT_COMMENT:
      sid = 0;
      cout << "Enter the student id: " << endl;
      cin >> sid;
      if (sid <= 0) {
        cout << "Enter a valid student id > 0" << endl;
        break;
      }
      course_id = 0;
      cout << "Enter the course id: " << endl;
      cin >> course_id;
      if (course_id <= 0) {
        cout << "Enter a valid course id > 0" << endl;
        break;
      }
      star = 0;
      cout << "Enter the star rank of this course: " << endl;
      cin >> star;
      if (star <= 0 || star > MAX_RANKING_STARS) {
        cout << "Enter a valid course id > 0 && < " << MAX_RANKING_STARS
             << endl;
        break;
      }

      ret = add_star_rank(student_head, sid, course_array, course_id, num_courses,
                        star);
      if (ret == false) {
        cout << "Failed to insert star_rank, sid: " << sid
             << ", course id: " << course_id << endl;
      } else {
        cout << " star_rank is successfully inserted" << endl;
      }
      break;
    case OPTION_DELETE_COMMENT:
      sid = 0;
      cout << "Enter the student id: " << endl;
      cin >> sid;
      if (sid <= 0) {
        cout << "Enter a valid student id > 0" << endl;
        break;
      }
      course_id = 0;
      cout << "Enter the course id: " << endl;
      cin >> course_id;
      if (course_id <= 0) {
        cout << "Enter a valid course id > 0" << endl;
        break;
      }

      ret = delete_star_rank(student_head, course_array, sid, course_id,
                           num_courses);
      if (ret == false) {
        cout << "Failed to delete star_rank, sid: " << sid
             << ", course id: " << course_id << endl;
      } else {
        cout << " star_rank is successfully deleted" << endl;
      }
      break;
    case OPTION_DELETE_COURSE:
      course_id = 0;
      cout << "Enter the course id: " << endl;
      cin >> course_id;
      if (course_id <= 0) {
        cout << "Enter a valid course id > 0" << endl;
        break;
      }

      ret = delete_course(student_head, course_array, course_id, num_courses);
      if (ret == false) {
        cout << "Failed to delete course, course id: " << course_id << endl;
      } else {
        cout << "course is successfully deleted" << endl;
      }
      break;
    default:
      break;
    } // end of switch (option)
  }

  return 0;
}