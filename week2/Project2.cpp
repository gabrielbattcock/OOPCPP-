//gabriel battcock
//OOPC++ assignment 2
// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <iomanip>
#include<iterator>
#include<cctype>

double mean(int data_number, double data_point[])
{
    double mean;
    
    for(int i(0);i<(data_number-1);i++)
    {
        mean=1/data_number*(data_point[i]+data_point[i+1]);
    }
    return mean;
}

    

double standard_deviation(int data_number, double data_point[], double mean_of_data)
{
    double standard_deviation;
    for(int i(0);i<data_number;i++)
    {
        standard_deviation=pow(1/(data_number-1)*(data_point[i]+data_point[i+1]),0.5);
    }
    return standard_deviation;

}

//int count_for_input_data()
//{
    //for (int i(0); i<std::strlen(array););
    //{

   // }
//}

bool check_for_digit(std::string input_data)
{
    for (std::string::const_iterator i(input_data.begin());i != input_data.end();)
    {
       if (isdigit(*i)==false)
       {
           return false;
       }

    }return true;
}
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

//function for lenth of array but cant seem to actually write it as a function
//int length_my_data=std::distance(std::begin(),std::end());

int main(){

    //ask for file name
    std::string file_name;
    std::cout<<"Please enter a file name:\n";
    std::getline(std::cin,file_name);

    //ask for number of data points
    std::string number_of_data_points;
    std::cout<<"How many data points would you like:\n";
    std::getline(std::cin,number_of_data_points);

    //check this is an integer
    while(check_for_integer(number_of_data_points)==false){
            std::cout<<"Sorry, you did not enter a number of data points, this should be an integer. \n";
            std::getline(std::cin,number_of_data_points);
            }
    
    //make number of data points constant

    const int const_number_of_data_points=stoi(number_of_data_points);

    //open the data file
    std::fstream milikan_data("xys_data.txt"); // Check file opened successfully
    if(milikan_data.fail()) {
        // Print error message and exit
        std::cerr <<"Error: file could not be opened"<<std::endl;
    return(true);}
        

    //allocate data
    double* single_data_point= new double;
    double* array_of_data=new double[const_number_of_data_points];

    if(milikan_data.is_open()){
        while(!milikan_data.eof()){
            std::string line;
            double data_from_file;
            std::getline(milikan_data,line);
            if (check_for_digit(line)==true){
                data_from_file=stod(line);
            }else{
                std::cout<<"there was an error detected in the input file, we have ignored this. \n";
            }
            array_of_data[i]=data_from_file;
            
        }milikan_data.close();
    }else{
        std::cout<<"File is not open, so could not process\n";
    }


   
  
    return 0;
}