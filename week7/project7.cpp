//gabriel battcock
//OOPCPP
//Week 6
//Matrix manipulation

#include<iostream>
#include<vector>
#include<cmath>
#include<string>

#include"vectorHeader.h"

const double speed_of_light{3e8};

int main()
{
    //show off vector stuff
    vector vec1{3};
    std::cout<<"Default 3-vector constructor:"<<vec1;
    vec1(0)=2.5;
    vec1(1)=4.2;
    vec1(2)=-.85;
    vector vec2{3};
    vec2(0)=5;vec2(1)=0.9;vec2(2)=3;
    vector vec3{3};
    vec3(0)=1;vec3(1)=2;vec3(2)=3;
    //dot product
    double dot=vec1.dot_product(vec2);
    std::cout<<"vec1= "<<vec1;
    std::cout<<"vec2= "<<vec2;
    std::cout<<"vec3= "<<vec3;
    std::cout<<"vec1.vec2= "<<dot<<std::endl;
    vector vec4{3};
    vec4(0)=-2;vec4(1)=12;vec4(2)=-1/12;
    //copy constructor
    vector vec5{vec2};
    std::cout<<"Copy vec2 to vec5= "<<vec5;
    //move constructor
    vector vec6{std::move(vec3)};
    std::cout<<"Move vec 3 to vec6="<<vec6<<"with original "<<vec3;
    //copy assignement 
    vector vec7=vec4;
    std::cout<<"Copy assignment vec4 to vec7 "<<vec7<<"and original "<<vec4;
    //move assignemnt 
    vector vec8=std::move(vec7);
    std::cout<<"Move vec7 to vec8 "<<vec8<<"and original "<<vec7;

    //four vec stuff
    four_vector fv1{};
    std::cout<<fv1;
    fv1(0)=3;fv1(1)=-2;fv1(2)=0.5;fv1(3)=1;
    four_vector fv2{};
    fv2(0)=1;fv2(1)=3;fv2(2)=4;fv2(3)=3.14159;
    four_vector fv3{};
    fv3(0)=.92;fv3(1)=0.82;fv3(2)=1.2;fv3(3)=10;
    std::cout<<"fv1= "<<fv1;
    std::cout<<"fv2= "<<fv2;
    std::cout<<"fv3= "<<fv1;
    
    //copy stuff
    four_vector fv4{fv2};
    four_vector fv5=fv3;
    std::cout<<"Copy constructor fv4{fv2}"<<fv4;
    std::cout<<"Copy assigneknt fv5=fv3"<<fv5;
    //move stuff
    four_vector fv6{std::move(fv3)};
    four_vector fv7=std::move(fv2);
    std::cout<<"move constructor (with original) fv6{fv3}"<<fv6<<fv3;
    std::cout<<"move assignment (with original) fv7=fv2"<<fv7<<fv2;

    vector beta{3};
    beta(0)=0.9;beta(1)=0.1;beta(2)=0.;
    four_vector lorentz=fv6.lorentz_boost(beta);
    std::cout<<"Lorentz boost of fv6 with beta"<<beta<<lorentz;
    std::cout<<"fv1.fv2= "<<fv1.dot_product(fv2)<<std::endl;
    std::cout<<"fv5.fv4= "<<fv5.dot_product(fv4)<<std::endl;
    //particle stuff
    particle proton(0.976,fv5,beta);
    std::cout<<"Particle proton, with known mass, position fv5 and beta previously indicated. "<<std::endl;
    std::cout<<"gamma of the proton is "<<proton.gamma()<<std::endl;
    std::cout<<"The total energy gamma*mass= "<<proton.total_energy()<<"Mev"<<std::endl;
    four_vector momentum{proton.total_momentum()};
    std::cout<<"The total mometum ="<<momentum;

    return 0;

}

double &vector::operator()(const size_t index)const
{
    if(index<0){
        throw("Calling a negative index");
    }else{
        return vector_entries[index];
    }
}

double &four_vector::operator()(const size_t index)const
{
    if(index<0){
        throw("Calling a negative index");
    }else{
        return vector_entries[index];
    }
}
vector::vector(size_t dimension_input)
{
    vector_entries=nullptr;
    if(dimension_input<1){
        throw("Vector does not have size.");
    }else{
        
        dimension=dimension_input;
        vector_entries=new double[dimension];
        for(size_t i{};i<dimension;i++){
            vector_entries[i]=0;
        }
    }
}

vector::vector(vector& vector_copy)
{
    vector_entries=nullptr;
    dimension=vector_copy.dimension;
    //reminder I will always use indexing starting from 0
    if(vector_copy.dimension>0){
        vector_entries=new double[dimension];
        for(size_t i{};i<dimension;i++){
            vector_entries[i]=vector_copy(i);
        }
    }
}
//four_vector(four_vector& )
vector::vector(vector&& vector_move)
{   
    dimension=vector_move.dimension;
    vector_entries=vector_move.vector_entries;
    vector_move.dimension=0;
    vector_move.vector_entries=0;
}

vector& vector::operator=(const vector &vector_input)
{
    if(&vector_input==this){
        return *this;
    }
   delete[] vector_entries; 
   vector_entries=nullptr; 
   dimension=0;
   //reset the matrix
   dimension=vector_input.dimension;

    if(dimension>0){
        vector_entries=new double[dimension];
        for (size_t i{};i<dimension;i++){
            vector_entries[i]=vector_input(i);
        }
    }
    return *this;
}

vector& vector::operator=(vector &&vector_input)
{
    std::swap(dimension, vector_input.dimension);
    std::swap(vector_entries, vector_input.vector_entries);
    return *this;
}

vector vector::operator+(const vector &vector_input)
{
    vector vector_output;
    if(dimension!=vector_input.dimension){
        throw("Vectors are not of same dimension");
    }else{
        vector_output(dimension);
        for(size_t i{};i<dimension;i++){
            vector_output(i)=vector_input(i)+vector_entries[i];
        }
    }
    return vector_output;
}
vector vector::operator*(const double &scalar_multiplier)
{
    vector output{dimension};
    for (size_t i{};i<dimension;i++){
        output(i)=vector_entries[i]*scalar_multiplier;
    }
    return output;

}
double vector::dot_product(const vector& vector_input)
{   
    double sum{};
    if(vector_input.dimension!=dimension||dimension<1){
        throw("Vectors are not of same dimension/too small");
    }else{
        for(size_t i{};i<dimension;i++){
            sum+=vector_entries[i]*vector_input(i);
        }   
    }
    return sum;
}

std::ostream& operator<<(std::ostream& output,const vector& output_vector)
{
    if(output_vector.vector_entries!=nullptr&&output_vector.dimension>0){
        //std::cout<<"Vector of dimension "<<output_vector.dimension<<": \n(";
        std::cout<<"(";
        for(size_t i{};i<output_vector.dimension;i++){
            if(i==output_vector.dimension-1){
                std::cout<<output_vector(i)<<")"<<std::endl;
            }else{
                std::cout<<output_vector(i)<<",";
            }
        }
    }
    return output;
}
//four vector functions
four_vector::four_vector(const double energy_input, const double x_in, const double y_in, const double z_in):vector(4)
{
    vector_entries[0]=energy_input;
    vector_entries[1]=x_in;
    vector_entries[2]=y_in;
    vector_entries[3]=z_in;
}
four_vector::four_vector(const double energy_input, const vector r_in):vector(4)
{
    vector_entries[0]=energy_input;
    vector_entries[1]=r_in(0);
    vector_entries[2]=r_in(1);
    vector_entries[3]=r_in(2);
}
four_vector::four_vector(const four_vector& four_vector_copy):vector(4)
{
    vector_entries=new double[4];
    for(size_t i{};i<4;i++){
        vector_entries[i]=four_vector_copy(i);
    }
}
four_vector::four_vector(four_vector&& four_vector_move):vector(4)
{
    std::swap(vector_entries, four_vector_move.vector_entries);
}

four_vector& four_vector::operator=(const four_vector &four_vector_input)
{
    if(&four_vector_input==this){
        return *this;
    }
   delete[] vector_entries; 
   vector_entries=nullptr; 
   dimension=0;
   //reset the matrix
   dimension=four_vector_input.dimension;

    if(dimension>0){
        vector_entries=new double[dimension];
        for (size_t i{};i<dimension;i++){
            vector_entries[i]=four_vector_input(i);
        }
    }
    return *this;
}

four_vector& four_vector::operator=(four_vector&& four_vector_move)
{
    std::swap(vector_entries,four_vector_move.vector_entries);
    return *this;
}

std::ostream& operator<<(std::ostream& output,const four_vector& output_four_vector)
{
    if(output_four_vector.vector_entries!=nullptr){
        std::cout<<std::endl<<"(" <<output_four_vector(0)<<","<<output_four_vector(1)<<","<<output_four_vector(2)<<","<<
        output_four_vector(3)<<")"<<std::endl;
        
    }
    return output;
}

double four_vector::dot_product(const four_vector& four_vector_input)
{
    double sum{};
    sum=-vector_entries[0]*four_vector_input(0);
    for (size_t i{1};i<four_vector_input.dimension;i++){
        sum+=vector_entries[i]*four_vector_input(i);
    }
    return sum;
}
four_vector four_vector::lorentz_boost(vector& beta)
{
    if(beta.get_dimensions()!=3){
        throw("Beta needs to be a 3d vector");
    }
    double x_0_prime{};
    vector r_prime{3};
    vector r{3};
    r(0)=vector_entries[1];r(1)=vector_entries[2];r(2)=vector_entries[3];
    double scalar_beta=pow(beta.dot_product(beta),0.5);
    //check for physics breaking 
    if(scalar_beta>1){
        throw("Breaking the speed of light");
    }
    double gamma=pow(1-pow(scalar_beta,2),-0.5);
    //calculate the entries
    x_0_prime=gamma*(vector_entries[0]-beta.dot_product(r));
    for(size_t i{1};i<=3;i++){
        r_prime(i)=r(i)+((gamma-1)*r.dot_product(beta)/pow(scalar_beta,2)-gamma*vector_entries[0]);
    }
    four_vector output{x_0_prime,r_prime};
    return output;
}

//particle functions
particle::particle(const double mass_input, const four_vector position_input, const vector beta_input)
{
    mass=mass_input; position=position_input; beta=beta_input;
}

double particle::gamma()
{
    double scalar_beta=pow(beta.dot_product(beta),0.5);
    return pow(1-pow(scalar_beta,2),-0.5);
}
double particle::total_energy()
{
    return mass*gamma();
}
four_vector particle::total_momentum()
{   
    //destructor being called in cout;
    four_vector momentum{total_energy(),beta*mass*gamma()};
    return momentum;
}
