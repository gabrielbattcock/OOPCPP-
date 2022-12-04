
#ifndef shapes_h
#define shapes_h

#include <stdio.h>

//gabriel battcock
//week 8
//oopcpp
//Shapes

#include<iostream>
#include<vector>
#include<cmath>
#include<string>



class shape
{
    size_t dimension;
public:
    shape():dimension{}{}
    shape(size_t input_dimension){dimension=input_dimension;}
    virtual ~shape(){}

    virtual void print()=0;
};

class two_dimensional: public shape
{
protected:
    double height;
    double length;
public:

    two_dimensional():shape(2){height=0;length=0;}
    two_dimensional(double input_height,double input_length);
    virtual ~two_dimensional(){}

    double return_height(){return height;}
    double return_length(){return length;}
    virtual double return_area()=0;
    virtual void print()=0;
};

class three_dimensional: public shape
{
protected:
    double height;
    double length;
    double depth;
public:
    three_dimensional():shape(3){height=0 ;length=0;depth=0;}
    three_dimensional(double input_height,double input_length,double input_depth);
    virtual ~three_dimensional(){}
    
    double return_height(){return height;}
    double return_length(){return length;}
    double return_depth(){return depth;}
    virtual double return_volume()=0;
    virtual void print()=0;

};

class rectangle:public two_dimensional
{
public:
    rectangle():two_dimensional(){}
    rectangle(double input_height, double input_length);
    ~rectangle(){std::cout<<"Destroying rectangle"<<std::endl;}

    double return_area();
    void print();
};

class square:public rectangle //square is_a rectangle
{
public:
    square():rectangle(){}
    square(double input_height);
    ~square(){std::cout<<"Destroying square"<<std::endl;}

    void print();
};

class ellipse:public two_dimensional
{
public:
    ellipse():two_dimensional(){}
    ellipse(double input_height,double input_length);
    ~ellipse(){std::cout<<"Destroying ellipse"<<std::endl;}

    double return_area();
    void print();
};

class circle:public ellipse
{
public:
    circle():ellipse(){}
    circle(double input_diameter);
    ~circle(){std::cout<<"Destroying circle"<<std::endl;}

    void print();
};

class cuboid:public three_dimensional
{
public:
    cuboid():three_dimensional(){}
    cuboid(double input_height,double input_length,double input_depth);
    ~cuboid(){std::cout<<"Destroying cuboid"<<std::endl;}

    double return_volume();
    void print();
};

class cube:public cuboid
{
public:
    cube():cuboid(){}
    cube(double input_side_length);
    ~cube(){std::cout<<"Destroying cube"<<std::endl;}

    void print();
};

class ellipsoid:public three_dimensional
{
public:
    ellipsoid():three_dimensional(){}
    ellipsoid(double input_height,double input_length,double input_depth);
    ~ellipsoid(){std::cout<<"Destroying ellipsoid"<<std::endl;}

    double return_volume();
    void print();
};

class sphere:public ellipsoid
{
public:
    sphere():ellipsoid(){}
    sphere(double input_diameter);
    ~sphere(){std::cout<<"Destroying sphere"<<std::endl;}

    void print();
};

class prism:public three_dimensional
{
    two_dimensional* face;
public:
    prism():three_dimensional(){}
    prism(two_dimensional* input_face, double input_depth);
    ~prism(){std::cout<<"Destroying prism"<<std::endl;}

    double return_volume();
    void print();
};




#endif /* shapes_h */

