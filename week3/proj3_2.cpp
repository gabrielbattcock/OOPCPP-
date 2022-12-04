//gabriel battcock
//OOPC++ assignment 3
// 

#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include<iterator>
#include<vector>

//define some functions maybe
bool check_for_integer(std::string input_data)
{
    for (std::string::const_iterator i(input_data.begin()); i != input_data.end(); i++)
    {
       if (isdigit(*i)==false)
       {
           return false;
       }
    }
    int positive= atoi(input_data.c_str());
    if(positive<=0)
    {
        return false;
    }
    return true;
}
bool find_year(std::string course_information, char desired_year)
{
size_t find_first_digit = course_information.find(desired_year);
int first_digit_place(find_first_digit);
size_t find_space=course_information.find(' ');
if (first_digit_place!=std::string::npos&&first_digit_place==5)
{
    return true;
}return false;
}

int find_space(std::string input_string)
{
 size_t find_space =input_string.find(' ');
 find_space=input_string.find(' ',find_space+1);
    if (find_space!=std::string::npos){
    return find_space;
    }
}

bool sort_by_name(std::string input_string1, std::string input_string2){
    size_t space1=find_space(input_string1);
    size_t space2=find_space(input_string2);
   std::string sort_by_name1(input_string1.begin()+space1,input_string1.end());
   std::string sort_by_name2(input_string2.begin()+space2,input_string2.end());
    return sort_by_name1<sort_by_name2;
   }

int main(){

    const std::string phys_prefix("PHYS ");
    //get the course data from user
    bool not_finished(true);
    std::vector<std::pair<int,std::string>> course_data;
    do {
        
        std::string course_code_and_name;
        std::cout<<"Enter a course code and name "<<std::endl;
        std::getline(std::cin,course_code_and_name);
        int course_code_sub = course_code_and_name.substr(0,5);
        std::cout<<course_code_sub;
        //while(!check_for_integer(course_code_and_name)||course_code.length()!=5){
          //  std::cout<<"You have entered an incorrect course code, this should be a five digit number."<<std::endl;
          //  std::getline(std::cin,course_code);
        //}
        std::string course_title;
        std::cout<<"Please enter a course name"<<std::endl;
        std::getline(std::cin,course_title);
        std::ostringstream output_stream;
        output_stream<<phys_prefix<<course_code<<" "<<course_title;
        std::string whole_course_name(output_stream.str());
        std::cout<<"The course is called "<<whole_course_name<<std::endl;

        //append to vector
        course_data.push_back(whole_course_name);
        std::cout<<"Press x to stop, or any other key to input another course."<<std::endl;
        std::string another_course_title;
        std::cin>>another_course_title;
        output_stream.str("");
        if(another_course_title[0]=='x'){
            not_finished=false;
            std::cin.clear();
            std::cin.ignore();
        }else{
            std::cin.clear();
            std::cin.ignore();
        }
    
    }while(not_finished==true);

    //print course list
    std::cout<<"The course list is: "<<std::endl;
    for(auto iterator=course_data.begin();iterator!=course_data.end();iterator++){
        std::cout<<*iterator<<std::endl;
    }
    std::string year_of_courses;
    std::cout<<"Please enter a year of which you want to see the course list: "<<std::endl;
    std::getline(std::cin,year_of_courses);
    std::vector<std::string> sorted_by_year;
    
    //use function to sort by year of interest
    for(auto iterator=course_data.begin();iterator!=course_data.end();iterator++){
        if(find_year(*iterator,year_of_courses[0])==true){
        sorted_by_year.push_back(*iterator);
        }
    }
    
    std::cout<<"The course list of year "<<year_of_courses<<" is: "<<std::endl;
    for(auto iterator=sorted_by_year.begin();iterator!=sorted_by_year.end();iterator++){
        std::cout<<*iterator<<std::endl;
    }
    //sort by name or code
    std::string sort_again;
    do{
    std::string sort_by_option;
    std::cout<<"Would you like to sort by code or name?"<<std::endl;
    std::getline(std::cin,sort_by_option);
    while(sort_by_option!="name"&&sort_by_option!="code"){
        std::cout<<"you have not selected an option, please enter code or name"<<std::endl;
        std::getline(std::cin, sort_by_option);
    }

    
    //output of sorting
    if (sort_by_option=="code"){
    sort(course_data.begin(),course_data.end());
    std::cout<<"The course list sorted by code is: "<<std::endl;
    for(auto line:course_data){
        std::cout<<line<<std::endl;
    }
    }else if(sort_by_option=="name"){
    sort(course_data.begin(),course_data.end(),sort_by_name);
    std::cout<<"The course list sorted by name is: "<<std::endl;
        for(auto line:course_data){
            std::cout<<line<<std::endl;
        }
    }
    std::cout<<"Would you like to sort the list again? y/n"<<std::endl;
    std::getline(std::cin,sort_again);
    }while(sort_again[0]=='y');
    return 0;
}