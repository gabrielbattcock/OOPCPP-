//
//  MyClass.hpp
//  Project
//
//  Created by Gabriel Battcock on 28/03/2020.
//  Copyright © 2020 Gabriel Battcock. All rights reserved.
//

#ifndef pieces_hpp
#define pieces_hpp

#include "board.hpp"
#include <stdio.h>
#include<iostream>
#include<iomanip>
#include<cmath>
#include<memory>
#include<map>
#include<string>
#include<utility>
#include<list>
#include<complex>
#include<vector>
#include<algorithm>



size_t x_y_to_position(size_t x_in,size_t y_in);

typedef std::map<int,char> character_ref;//NEED TO PUT THIS IN


class board;

//base class
class piece
{
    friend class board;
protected:
    //p=1,n&b=3,r=5,Q=10,K=inf, but shall say 1000 to keep it a real value
    size_t value{};
    //true for white, false for black
    bool colour;
    int x_position;
    int y_position;
    std::string symbol;//TRY FOR CHESS PIECES?
    
public:
    piece(){}//value{0}
    virtual ~piece(){std::cout<<"Destroying piece"<<std::endl;}
    
    piece& operator=(const piece& piece);
    virtual bool move(int x_in, int y_in,board& board)=0;
    void set_x_y(int x_in, int y_in, board& playing_board);
    virtual bool return_colour()=0;
    virtual size_t return_value()=0;
    virtual int return_x()=0;
    virtual int return_y()=0;
    virtual void set_value(const size_t input_value)=0;
    void print(){std::cout<<symbol;}
    //virtual size_t position()=0;
    virtual std::string return_symbol()=0;
    size_t operator()(const int x_position,const int y_position);
    friend std::ostream& operator<<(std::istream &output, piece& piece_output);
    
};

namespace white
{
    class pawn:public piece
    {
    protected:
        size_t value{1};
        const bool colour{true};
        const std::string symbol{"WP"};
    public:
        pawn(){}
        pawn(const int start_x,const int start_y);
        ~pawn(){std::cout<<"Destroying pawn"<<std::endl;}
        
        bool move(int x_in, int y_in,board& board);
        bool return_colour(){return colour;}
        size_t return_value(){return value;}
        void print(){std::cout<<symbol;}
        int return_x(){return x_position;}
        int return_y(){return y_position;}
        void set_value(const size_t input_value){value=input_value;}
        std::string return_symbol(){return symbol;}
        piece* change_piece();
        piece& operator=(const piece& piece);
    };
}
namespace black
{
    class pawn:public piece
    {
    protected:
        size_t value{1};
        const bool colour{false};
        const std::string symbol{"BP"};
    public:
        pawn(){}
        pawn(const int start_x,const int start_y);
        ~pawn(){std::cout<<"Destroying pawn"<<std::endl;}
        
        bool move(int x_in, int y_in, board& board);
        bool return_colour(){return colour;}
        size_t return_value(){return value;}
        void print(){std::cout<<symbol;}
        int return_x(){return x_position;}
        int return_y(){return y_position;}
        void set_value(const size_t input_value){value=input_value;}
        std::string return_symbol(){return symbol;}
        
    };
}
class queen:public piece
{
    //size_t value{10};
public:
    
    queen(){}
    queen(const int start_x,const int start_y,const std::string symbol_in,const bool colour_in);
    ~queen(){std::cout<<"Destroying queen"<<std::endl;}
    
    bool move(int x_in, int y_in, board& board);
    void set_x_y(int x_in, int y_in, board& playing_board);
    bool return_colour(){return colour;}
    size_t return_value(){return value;}
    void print(){std::cout<<symbol;}
    void set_value(const size_t input_value){value=input_value;}
    int return_x(){return x_position;}
    int return_y(){return y_position;}
    std::string return_symbol(){return symbol;}
};

class king:public piece
{
    size_t value{1000};
public:
    king(){}
    king(const int start_x,const int start_y, const std::string symbol_in, const bool colour_in);
    ~king(){std::cout<<"Destroying king"<<std::endl;}
    
    bool move(int x_in, int y_in, board& board);
    bool return_colour(){return colour;}
    void print(){std::cout<<symbol;}
    size_t return_value(){return value;}
    void set_value(const size_t input_value){value=input_value;}
    int return_x(){return x_position;}
    int return_y(){return y_position;}
    std::string return_symbol(){return symbol;}
};
class rook:public piece
{
    size_t value{5};
public:
    rook(){}
    rook(const int start_x,const int start_y,const std::string symbol_in,const bool colour_in);
    ~rook(){std::cout<<"Destroying rook"<<std::endl;}
    
    bool move(int x_in, int y_in, board& board);
    bool return_colour(){return colour;}
    void print(){std::cout<<symbol;}
    size_t return_value(){return value;}
    void set_value(const size_t input_value){value=input_value;}
    int return_x(){return x_position;}
    int return_y(){return y_position;}
    std::string return_symbol(){return symbol;}
};

class bishop:public piece
{
    size_t value{3};
public:
    bishop(){}
    bishop(const int start_x,const int start_y,const std::string symbol_in,const bool colour_in);
    ~bishop(){std::cout<<"Destroying bishop"<<std::endl;}
    
    bool move(int x_in, int y_in, board& board);
    bool return_colour(){return colour;}
    void print(){std::cout<<symbol;}
    size_t return_value(){return value;}
    void set_value(const size_t input_value){value=input_value;}
    int return_x(){return x_position;}
    int return_y(){return y_position;}
    std::string return_symbol(){return symbol;}
};

class knight:public piece
{
    size_t value{3};
public:
    knight(){}
    knight(const int start_x,const int start_y,const std::string symbol_in,const bool colour_in);
    ~knight(){std::cout<<"Destroying bishop"<<std::endl;}
    
    bool move(int x_in, int y_in, board& board);
    bool return_colour(){return colour;}
    void print(){std::cout<<symbol;}
    size_t return_value(){return value;}
    void set_value(const size_t input_value){value=input_value;}
    int return_x(){return x_position;}
    int return_y(){return y_position;}
    std::string return_symbol(){return symbol;}
};

//defining a type, pairs, as the use of many << >> gets difficult to read
//typedef std::pair<size_t,std::unique_ptr<piece> > pairs;





#endif /* pieces */
