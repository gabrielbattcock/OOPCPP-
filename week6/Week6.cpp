//Gabriel Battcock
//OOPCPP
//Week 6
//Matrix manipulation

#include<iostream>
#include<vector>
#include<cmath>
#include<string>

class matrix
{
private:
    size_t columns{};
    size_t rows{};
    double* data{nullptr};

public:
    
    //constructors
    matrix(){std::cout<<"Default constructor called. "<<std::endl;}
    matrix(size_t columns_input, size_t rows_input);
    matrix(matrix &matrix_copy);
    matrix(matrix &&matrix_copy);
    ~matrix(){delete[] data; std::cout<<"Destructor called. "<<std::endl;}
    //overloading fnctions
    matrix &operator=(const matrix &matrix_input);
    matrix &operator=(matrix &&matrix_input);
    matrix operator+(const matrix &matrix_input);
    matrix operator-(const matrix &matrix_input);
    matrix operator*(const matrix &matrix_input);
    double &operator()(const size_t row, const size_t column)const;
    friend std::istream& operator>>(std::istream &input, matrix& matrix_input);
   ;

    //functions
    void set_rows(size_t input_rows){rows=input_rows;}
    void set_columns(size_t input_columns){columns=input_columns;}
    void set_data(double input_data, size_t i, size_t j){data[position(i,j)]=input_data;}
    
    size_t size(){return rows*columns;}
    size_t position(size_t i, size_t j)const;
    size_t return_rows(){return rows;}
    size_t return_columns(){return columns;}
    matrix remove_row_and_column(matrix& matrix_input);


};


bool find_character(std::string input_string, char character_input)
{
    size_t find_character = input_string.find(character_input);
    if (find_character != std::string::npos){
        return true;
    }else{
        return false;
    }
    
}
size_t character_find(std::string input_string, char character_input, size_t start_position)
{
    size_t find_character = input_string.find(character_input,start_position);
    if (find_character != std::string::npos){
        return find_character;
    }else{
        return std::string::npos;
    }
    
}

size_t count_character(std::string input_string, char input_character)
{
    size_t character_count;
    for(auto iterator=input_string.begin();iterator<input_string.end();iterator++){
        if (*iterator==input_character){
            character_count++;
        }
    }
    return character_count;   
}

int main()
{   
    
    matrix a{};
    std::cin>>a;
    //std::cout<<a;
    
    return 0;
}

size_t matrix::position(size_t i, size_t j) const
{
    return (j-1)+(i-1)*columns;
}

matrix::matrix(size_t columns_input, size_t rows_input)
{
    if(columns_input<1||rows_input<1){
        throw( "Size not positive");
    }
    columns=columns_input;
    rows=rows_input;
    data=new double[columns*rows];
    for (size_t i{};i<rows*columns;i++){
        data[i]=0;
    }
}

//copy constructor
matrix::matrix(matrix &matrix_copy)
{   
     //takes in one matrix and copies it into another
    data=nullptr;
    columns=matrix_copy.columns;
    rows=matrix_copy.rows;
    if (matrix_copy.size()>0){
        data=new double[size()];
        for (int i{0};i<size();i++){
            data[i]=matrix_copy.data[i];
        }
    }
}
//move constuctor
matrix::matrix(matrix&& matrix_copy)
{
    //takes in the first matrix, deletes the info and copies it to another
    columns=matrix_copy.columns;
    rows=matrix_copy.rows;
    data=matrix_copy.data;
    matrix_copy.columns=0;
    matrix_copy.rows=0;
    matrix_copy.data=nullptr;

}
//copy assignment operator
matrix& matrix::operator=(const matrix &matrix_input)
{
    //sets one matrix equal to another
    if(&matrix_input==this){
        return *this;
    }
   delete[] data; 
   data=nullptr; 
   rows=0;
   columns=0;
   //reset the matrix
   columns=matrix_input.columns;
   rows=matrix_input.rows;
    if(size()>0){
        data=new double[size()];
        for (size_t i{};i<size();i++){
            data[i]=matrix_input.data[i];
        }
    }
    return *this;
}
//move assignment operator
matrix& matrix::operator=(matrix &&matrix_input)
{
    //swaps two matrices (? why is this ever needed ?)
    std::swap(rows, matrix_input.rows);
    std::swap(columns, matrix_input.columns);
    std::swap(data, matrix_input.data);
    return *this;
}
//overloading functions
double& matrix::operator()(const size_t row, const size_t column) const 
{
    if (row < 1 || column < 1 || row > rows || column > columns) {
        std::cerr << "matrix element should be in range of matrix"  << std::endl;
    }
    return data[position(row,column)];
}
matrix matrix::operator+(const matrix& matrix_input)
{
    matrix output_matrix;
    if (matrix_input.rows==rows&&matrix_input.columns==columns){
        output_matrix(rows,columns);
        for(int i{0};i<=rows;++i){
            for(int j{0};j<=columns;++j){
                output_matrix(i,j)=data[position(i,j)];
            }
        }
    }else{
        std::cerr<<"The two matrices are incompatable for this operation. "<<std::endl;
    }
    return output_matrix;
}
matrix matrix::operator-(const matrix& matrix_input)
{
    matrix output_matrix;
    if (matrix_input.rows==rows&&matrix_input.columns==columns){
        output_matrix(rows,columns);
        for(int i{0};i<=rows;++i){
            for(int j{0};j<=columns;++j){
                output_matrix(i,j)=data[position(i,j)]-matrix_input(i,j);
            }
        }
    }else{
        std::cerr<<"The two matrices are incompatable for this operation. "<<std::endl;
    }
    return output_matrix;
}
matrix matrix::operator*(const matrix& matrix_input)
{
    if(columns!=matrix_input.rows){
        std::cerr<<"The umber of columns does not equal number of rows, so operation cannot take place"<<std::endl;
    }
        matrix output_matrix(rows, matrix_input.columns);
        for (int i{};i<=rows;i++){
            for(int j{};j<=columns;j++){
                double sum{};
                for (int element{};element<=columns;element++){
                    sum+=data[position(i,element)]*matrix_input(element,j);
                }
                output_matrix(i,j)=sum;
            }
        }
    
  return output_matrix;  
}


std::istream& operator>>(std::istream &input, matrix& matrix_input)
{
    std::cout<<"Please enter a matrix, with columns delineated by a comma, and rows delineated by a forward slash"<<std::endl;
    std::string input_line;
    std::getline(input, input_line);

    //count how many '/' there are, n+1=number of rows
    std::vector <std::string> rows_data;
    size_t counter{};
    size_t number_of_commas{};
    size_t start{};
    size_t position{};
    for (auto iterator=input_line.begin();iterator<=input_line.end();iterator++){
        
        if (*iterator=='/'){
            position=character_find(input_line,'/',start);    
            std::string data_sub=input_line.substr(start,position-start);
            rows_data.push_back(data_sub);
            
            std::cout<<"Printing each row "<<data_sub<<std::endl;
            start=position+1;   
            counter++;
        }else if (iterator==input_line.end()){
            std::string data_sub=input_line.substr(start,input_line.length()-start);
            std::cout<< data_sub;
            rows_data.push_back(data_sub);
            counter++;
        }
        
    }
        
    
    matrix_input.set_rows(counter);
    size_t which_row{};
    size_t position_in_row{};
    size_t start_1{};
    size_t number_of_columns{};
    for(auto iterator=rows_data.begin();iterator<=rows_data.end();iterator++){
        start_1=0;
        for (auto it=iterator->begin();it<=iterator->end();it++){

            if(*it==','){
                position_in_row=character_find(*iterator,',',start_1);    
                std::string data_sub=iterator->substr(start_1,position_in_row-start_1);
                std::cout<< "Printing column from row "<<data_sub<<std::endl;
                //matrix_input.set_data(std::stod(data_sub),which_row,position_in_row);
                
                std::cout<<"pos in row "<<position_in_row<< ". row "<<which_row<<std::endl;
                start_1=position_in_row+1;
                //else all the columns are the same which is good
                
                number_of_columns++;
            }else if (it==iterator->end()){
                std::string data_sub=iterator->substr(start_1,iterator->length()-start_1);
                std::cout<< data_sub;
                
                number_of_columns++;  
            }
           
        } 
         which_row++;
        
    }
    matrix_input.set_columns(number_of_columns);  
    std::cout<<"number of columns "<< matrix_input.return_columns()<<"number of rows"<<matrix_input.return_rows()<<std::endl;
    return input;
}

std::ostream& operator<<(std::ostream output, matrix &matrix_output)
{
    if(matrix_output.return_columns()<1&&matrix_output.return_rows()<1){
        std::cerr<<"This matrix is too small to output "<<std::endl;
        throw("Too small.");
    }
    //std::cout<<matrix_output<<": ";
    for(size_t i{1};i<=matrix_output.return_rows();i++){
        std::cout<<"|";
        for(size_t j{1};j<=matrix_output.return_columns();j++){
            std::cout<<matrix_output(i,j)<<"   ";
        }
        std::cout<<"|"<<std::endl;
    }   

}

