
//gabriel battcock
//week 8
//oopcpp
//Shapes

#include<iostream>
#include<vector>
#include<cmath>
#include<string>

#include"shapes.h"

const double pi{3.14159};

int main()
{
    std::vector <shape*> shape_vector;
    shape_vector.push_back(new rectangle{});
    shape_vector.push_back(new rectangle{2,3});
    shape_vector.push_back(new square{4});
    shape_vector.push_back(new circle{3});
    shape_vector.push_back(new ellipse{2,3});
    shape_vector.push_back(new cuboid{4,3,4});
    shape_vector.push_back(new cube{2.3});
    shape_vector.push_back(new ellipsoid{2,3,4});
    shape_vector.push_back(new sphere{3});
    two_dimensional* a=new ellipse{3,4};
    shape_vector.push_back(new prism{a,3});
    for(auto iterator=shape_vector.begin();iterator<shape_vector.end();iterator++){
        (*iterator)->print();
        delete *iterator;
    }
    return 0;
}

rectangle::rectangle(double input_height, double input_length):two_dimensional()
{
    height=input_height;
    length=input_length;
}
double rectangle::return_area()
{
    return height*length;
}
void rectangle::print()
{
    std::cout<<"Rectangle with height: "<<height<<
    std::endl<<"    length: "<<length<<std::endl<<"      area: "<<return_area()<<std::endl;
}
square::square(double input_height):rectangle()
{
    height=input_height;
    length=input_height;
}
void square::print()
{
    std::cout<<"Square with side length: "<<length<<
    std::endl<<"     area: "<<return_area()<<std::endl;
}
ellipse::ellipse(double input_height, double input_length):two_dimensional()
{
    height=input_height;
    length=input_length;
}
double ellipse::return_area()
{
    return (pi/4)*length*height;
}
void ellipse::print()
{
    double semi_major;double semi_minor;
    if(length>height){
        semi_major=length/2;
        semi_minor=height/2;
    }else{
        semi_major=height/2;
        semi_minor=length/2;
    }

    
    std::cout<<"Ellipse with semi-major axis : "<<semi_major
    <<"\n   semi-minor axis: "<<semi_minor<<"\n      area: "<<return_area()<<std::endl;
}
circle::circle(double input_diameter):ellipse()
{
    height=input_diameter;length=input_diameter;
}
void circle::print()
{
    std::cout<<"Circle with radius: "<<height/2<<"\n     area: "<<return_area()<<std::endl;
}
cuboid::cuboid(double input_height,double input_length,double input_depth):three_dimensional()
{
    height=input_height;
    length=input_length;
    depth=input_depth;
}
double cuboid::return_volume()
{
    return height*length*depth;
}
void cuboid::print()
{
    std::cout<<"Cuboid with height: "<<height<<"\n  length: "<<length<<
    "\n     depth: "<<depth<<"\n     volume: "<<return_volume()<<std::endl;
}
cube::cube(double input_side_length):cuboid()
{
    height=input_side_length;
    length=input_side_length;
    depth=input_side_length;
}
void cube::print()
{
    std::cout<<"Cube with side length: "<<height<<"\n       volume: "<<return_volume()<<std::endl;
}
ellipsoid::ellipsoid(double input_height,double input_length,double input_depth):three_dimensional()
{
    height=input_height;
    length=input_length;
    depth=input_depth;
}
double ellipsoid::return_volume()
{
    return 0.166666666667*pi*height*length*depth;
}
void ellipsoid::print()
{
    std::cout<<"Ellipsoid with principle semi-axes: "<<(height/2)<<", "<<(length/2)<<", "<<(depth/2)<<
    "\n      volume: "<<return_volume()<<std::endl;
}
sphere::sphere(double input_diameter):ellipsoid()
{
    height=input_diameter;
    length=input_diameter;
    depth=input_diameter;
}
void sphere::print()
{
    std::cout<<"Sphere with radius: "<<height/2<<"\n     volume: "<<return_volume()<<std::endl;
}
prism::prism(two_dimensional* input_face,double input_depth):three_dimensional()
{
    face=input_face;
    height=input_face->return_height();
    length=input_face->return_length();
    depth=input_depth;
}
double prism::return_volume()
{
    return face->return_area()*depth;
}
void prism::print()
{
    std::cout<<"Prism with face area: "<<face->return_area()<<"\n     depth: "<<depth<<"\n    volume: "<<return_volume()<<std::endl;
}
