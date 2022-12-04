//Gabriel Battcock
//Week 4
//Planets and playing with objects


#include<iostream>
#include<string>
#include<cmath>
#include<vector>

const double suns_mass{1.989e30};

double random_number(double lower_bound, double upper_bound)
{
     double random_number=(double)rand()/RAND_MAX;
     return lower_bound+random_number*(upper_bound-lower_bound);
}

class galaxy
{
private:
    
    std::string hubble_parameter;//{;//
   // enum std::string {E0,E1,E2,E3,E4,E5,E6,E7,S0,Sa,Sb,Sc,SBa,SBb,Sbc,Irr};
    double redshift;
    double total_mass;
    double stellar_mass_fraction;
    std::vector<galaxy> satellitte;

public:
    //constructors
    galaxy(): hubble_parameter{"Irr"}, redshift{random_number(0.,10.)},
    total_mass{random_number(1e7,1e12)}, stellar_mass_fraction {random_number(0.,0.05)}
    {}

    galaxy(std::string galaxy_hubble_parameter , double galaxy_redshift , 
    double galaxy_total_mass, double galaxy_stellar_mass_fraction ) :
    hubble_parameter{galaxy_hubble_parameter}, redshift{galaxy_redshift}, total_mass{galaxy_total_mass},
     stellar_mass_fraction{galaxy_stellar_mass_fraction}
 {}
 ~galaxy(){std::cout<<"Destroying galaxy "<<std::endl;} // Destructor
    
    //function to print galaxy data
    std::string get_hubble_param()const{return hubble_parameter;}
    double get_redshift()const{return redshift;}
    double get_total_mass() const{return total_mass;}
    double get_stellar_mf() const{return stellar_mass_fraction;}
    std::vector<galaxy> get_satellite() const{return satellitte;}
    void print_data();
    double stellar_mass_return(){return stellar_mass_fraction*total_mass;}
    void add_satellite(galaxy &add_satellite);
    void print_satellite_data();
    //check range of of variables
    std::string change_hubble_parameter(std::string change_of_parameter);
};


std::string galaxy::change_hubble_parameter(std::string change_of_parameter)
{
    return hubble_parameter=change_of_parameter;
}

bool check_variables_range(std::vector<galaxy> &check_data)
{
    
    for(auto iterator=check_data.begin();iterator<check_data.end();++iterator){
    //range of variables: total mass [1e7,1e12], redshift [0,10] f_* [0,0.05]
        if(iterator->get_hubble_param()=="E0"||"E1"||"E2"||"E3"||"E4"||"E5"||"E6"||"E7"||"S0"||"Sa"||"Sb"||"Sc"||"SBa"||"SBb"||"Sbc"||"Irr"){
            if(iterator->get_total_mass() >=1e7 && iterator->get_total_mass() <= 1e12){
                if (iterator->get_redshift()>=0 && iterator->get_redshift() <=10){
                    if(iterator->get_stellar_mf() >=0 && iterator->get_stellar_mf()<=0.05){
                        //std::cout<<"The values are out of range so we have erased this"<<std::endl;
                        return true;
                    }
                }
            } 
        }
    }
    check_data.pop_back();
    std::cout<<"One of the variables is out of range. This has been erased from the vector. "<<std::endl;
    return false;
    
}


//used to print single elements of the vector
void galaxy::print_data()
{
    std::cout.precision(3);

    std::cout<<std::endl<<"Galaxy: [Hubble parameter, redshift, stellar mass fraction, total mass, satellite number]= ["
    <<hubble_parameter<<","<<redshift<<","<<stellar_mass_fraction<<","<<total_mass<<","<<satellitte.size()<<"]"<<std::endl;
    std::cout<<"With stellar mass "<<stellar_mass_return()<<" M_sun. "<<std::endl;
    if(satellitte.size()>0){
    
        for(auto iterator=satellitte.begin();iterator<satellitte.end();++iterator){
            std::cout<<std::endl<<"Satellite:"<<std::endl;
            iterator->print_data();
        }
        
    }
}

void galaxy::add_satellite(galaxy &satellite_galaxy)
{
    satellitte.push_back(satellite_galaxy);
}


int main()
{   
    std::vector<galaxy> galaxy_data;
    galaxy andromeda=galaxy();
    //default constructor
    galaxy_data.push_back(andromeda);
    //andromeda.check_variables_range(galaxy_data);

    galaxy_data[0].print_data();
    //galaxy_data[0].print_data();
    std::cout<<std::endl<<"Deleting default galaxy from vector. "<<std::endl;
    galaxy_data.pop_back();

    //set some galaxy data using the parameterized constructor
    galaxy milky_way{"E0",2,1e8,0.01};
    galaxy_data.push_back(milky_way);
    galaxy_data.push_back(galaxy("E2",5.2,3e9,30));

    if(check_variables_range(galaxy_data)==true){
        for(auto iterator=galaxy_data.begin();iterator<galaxy_data.end();++iterator){
            iterator->print_data();
        }
    }
    
    //showing change of hubble parameter
    std::string new_hubble_parameter{"S0"};
    galaxy_data[0].change_hubble_parameter(new_hubble_parameter);
    std::cout<<std::endl<<"The galaxy has be altered. It is as follows: "<<std::endl;
    galaxy_data[0].print_data();
    
    //create satellite 
    galaxy satellite_1 =galaxy();
    std::string hubble_parameter_sat1{"SBa"};
    satellite_1.change_hubble_parameter(hubble_parameter_sat1);
    galaxy satellite_2 =galaxy();
    std::string hubble_parameter_sat2{"E7"};
    satellite_2.change_hubble_parameter(hubble_parameter_sat2);
    galaxy sat_satellite =galaxy();
    
    std::cout<<std::endl<<"We have now added satellite galaxies to galaxy with parameter S0, and a satellite to one of the satellites."<<std::endl;
    //add satellite to a specific galaxy
    satellite_1.add_satellite(sat_satellite);
    galaxy_data[0].add_satellite(satellite_1);
    galaxy_data[0].add_satellite(satellite_2);
    
    
    for(auto iterator=galaxy_data.begin();iterator<galaxy_data.end();++iterator){
        iterator->print_data();
    }

 return 0;
}