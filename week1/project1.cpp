//Gabriel Battcock
//Assessment One, finding the energy gap of bohr model

#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>

const double electron_charge(1.602e-19);
//define functions

double eV_to_joules (double Energy_in_eV)
{
    double energy_in_joules;
    energy_in_joules=Energy_in_eV*electron_charge;
    return energy_in_joules;
}
double calculate_the_energy(int initial_energy, int final_energy, int atomic_number)
{
    double energy_in_ev;
    energy_in_ev=13.6*pow(atomic_number,2)*(1/pow(final_energy,2)-1/pow(initial_energy,2));
    return energy_in_ev;
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


int main()
{       
     std::string repeat;
     do
    
     { 
       
        std::string atomic_number;
        std::cout<<"Thank you, please enter an atomic number: \n";
        std::cin.clear();
        std::cin.ignore();
        std::getline(std::cin,atomic_number);

        while(check_for_integer(atomic_number)==false)
            {
            std::cout<<"Sorry, you did not enter a valid atomic Number, this should be an integer.\n";
            //clear the cin data
            
            std::getline(std::cin,atomic_number);
            }
        //convert to integer
        int int_atomic_number=atoi(atomic_number.c_str());
        std::cout<<int_atomic_number;

        //ask for initial energy
        std::string initial_energy;
        std::cout<<"Thank you, please enter an initial energy level: \n";
        std::getline(std::cin,initial_energy);

        while(check_for_integer(initial_energy)==false)
            {
            std::cout<<"Sorry, you did not enter a valid initial energy, this should be an integer.\n";
            //clear the cin data
            std::getline(std::cin,initial_energy);
            }
        //convert to integer
        int int_initial_energy=atoi(initial_energy.c_str());
        std::cout<<int_initial_energy;

        //ask for final energy
        std::string final_energy;
        std::cout<<"Thank you, please enter an final energy level: \n";
        std::getline(std::cin,final_energy);


        while(check_for_integer(final_energy)==false)
            {
            std::cout<<"Sorry, you did not enter a valid final energy, this should be an integer. \n";
            std::getline(std::cin,final_energy);
            }

        int int_final_energy=atoi(final_energy.c_str());
        std::cout<<int_final_energy;


       // while (int_initial_energy>int_final_energy)
        // {
          //  std::cout<<"sorry, the final energy you have entered is ";

          //  }

       double energy_eV= abs(calculate_the_energy(int_initial_energy,int_final_energy,int_atomic_number));
       double energy_joules=eV_to_joules(energy_eV);


        //ask whether they want energy calculated in ev or joules
        std::string units;
        std::cout<<"Would you like the energy in (e)V or (j)oules? \n";
        std::cin>>units;

        //check for correct input
        while(units!="e" && units !="j")
        {
           std::cout<<"I'm sorry, you have selected units incorrectly, please enter e for eV or j for Joules. \n";
           std :: cin.clear();
           std :: cin.ignore();
           std :: cin>>units;
        }


        
        //display the final energy 
        if(units == "e")
        {if(int_initial_energy>int_final_energy)
            {
            std::cout<<"The emitted photon energy  is "<<energy_eV<<"eV. \n";
            }
        else{
            std::cout<<"The absorbed photon energy  is "<<energy_eV<<"eV. \n";
        }    
        }
        else 
        {
            if (int_initial_energy>int_final_energy)
            {
        std::cout<<"The emitted photon energy  is "<<energy_joules<<"J. \n";
            }
            else{
                std::cout<<"The absorbed photon energy  is "<<energy_joules<<"J. \n";
            }
        }
        
        //ask if ant to do it again 
       
        std::cout<<"Would you like to calculate another energy difference? y, or press any key \n";
        std::cin>>repeat;
     }while(repeat=="y");


    return 0;
}