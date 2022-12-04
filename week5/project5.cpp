//Gabriel Battcock
//OOPC++
//Project 5
//Complex number machine

#include<iostream>
#include<vector>
#include<cmath>
#include<string>


class complex_number
{

    double real;
    double imaginary;
    //std::string output_number;

public:
    //set constructors
    //default
    complex_number():real{0.},imaginary{0.}
    {}
    complex_number(double real_in,double imag_in):
    real{real_in},imaginary{imag_in}
    {}
    ~complex_number(){std::cout<<"Destroying complex number"<<std::endl;}

    //functions
    void set_real(const double real_in){real=real_in;}
    void set_imag(const double imag_in){imaginary=imag_in;}
    double get_real() const {return real;}
    double get_imaginary() const {return imaginary;}
    friend void display_number();
    friend complex_number input_number();
    
    double modulus(){return sqrt(abs(pow(real,2)+pow(imaginary,2)));}
    double argument(){return atan2(imaginary,real);}

    complex_number conjugate();

    //overloading functions
    complex_number operator+(const complex_number &z)const
    {
        complex_number temp{real+z.real,imaginary+z.imaginary};
        return temp;
    }
    complex_number operator-(const complex_number &z)const
    {
        complex_number temp{real-z.real,imaginary-z.imaginary};
        return temp;
    }
    complex_number operator*(const complex_number &z)const
    {
        complex_number temp{real*z.real-imaginary*z.imaginary,real*z.imaginary+imaginary*z.real};
        return temp;
    }
    complex_number operator/(const complex_number &z)const
    {   
        double prefactor{1/(pow(z.real,2)+pow(z.imaginary,2))};
        complex_number temp{prefactor*(real*z.real+imaginary*z.imaginary),prefactor*(imaginary*z.real-real*z.imaginary)};
        return temp;
    }

};


void display_number(const complex_number &z)
{   
    if (z.get_imaginary()<0){
        
        std::cout<<z.get_real()<<"-i"<<abs(z.get_imaginary())<<std::endl;
        
    }else{
        std::cout<<z.get_real()<<"+i"<<abs(z.get_imaginary())<<std::endl;
    }
}



complex_number input_number()
{  
    complex_number output_number{};
    std::string input_string;
    std::cout<<"Input a complex number of form a±ib. "<<std::endl;
    std::getline(std::cin,input_string);

    double imaginary;
    double real;
    size_t find_i=input_string.find("i");
    size_t find_plus=input_string.find("+");
    size_t find_minus=input_string.find("-");
    if (find_plus!=std::string::npos){
        if(find_i!=0){
            std::string imag_str=input_string.substr(find_i+1,input_string.size()-find_i);
            imaginary=stod(imag_str);
            real=stod(input_string);
        }else{
            real=0;
        }
    }  
    if (find_minus!=std::string::npos){ 
        if(find_i!=0){
            imaginary=-stod(input_string.substr(find_i+1,input_string.size()-find_i));
            real=stod(input_string);
        }else{
            real=0;
        }
        // real=stod(input_string.substr(0,find_minus));
    }
    //imaginary=0; 
    

    output_number.set_imag(imaginary);
    output_number.set_real(real);
    return output_number;
}

complex_number complex_number::conjugate()
{
    complex_number conjugate{real,-imaginary};
    return conjugate;
}

int main()
{
    //set two complex numbers
    complex_number a{3,4};
    complex_number b{1,-2};
    display_number(a);
    display_number(b);
    //return 
    std::cout<<"The modulus of a is "<<a.modulus()<<". The modulus of b is "<<b.modulus()<<std::endl;
    std::cout<<"The argumebt of a is "<<a.argument()<<". The argumebt of b is "<<b.argument()<<std::endl;

    complex_number conjugate_a=a.conjugate();
    complex_number conjusate_b=b.conjugate();
    std::cout<<"The conjugate of a is ";display_number(conjugate_a);std::cout<<std::endl;
    std::cout<<"The conjugate of b is ";display_number(conjusate_b);std::cout<<std::endl;
    //show operators
    complex_number c{a*b};
    std::cout<<"a x b = ";display_number(c);std::cout<<std::endl;

    complex_number d{a/b};
    std::cout<<"a / b = ";display_number(d);std::cout<<std::endl;

    complex_number e{a+b};
    std::cout<<"a + b = ";display_number(e);std::cout<<std::endl;

    complex_number f{a-b};
    std::cout<<"a - b = ";display_number(f);std::cout<<std::endl;
    
    complex_number user_input=input_number();

    display_number(user_input);
    std::cout<<"The modulus of you number is "<<user_input.modulus()<<
    " The argument of your number is "<<user_input.argument()<<std::endl;
    std::cout<<"The conjugate of your number is ";display_number(user_input.conjugate());std::cout<<std::endl;
    return 0;
}