//
//  MyClass.cpp
//  Project
//
//  Created by Gabriel Battcock on 28/03/2020.
//  Here we create all the functions defined in the header file
//

#include"pieces.hpp"
#include"board.hpp"
#include<iostream>
#include<cmath>

const std::complex<double> ip(-1,0);
const double pi{std::arg(ip)};
const int range_flag{1};
const int invalid_move{2};

typedef std::map<int,char> character_ref;
////////////////do next////////////



void range_of_board(int x_in,int y_in)
{
    //checks if position is in range of board
    if(x_in<1||x_in>8||y_in<1||y_in>8){
        throw(range_flag);
    }
}
bool check_can_take(bool user_piece, bool other_piece)
{
    //move can only take if of opposite colour. refer to truth table for more info.
    return user_piece^other_piece;
}

template <class c_type> c_type difference(c_type x,c_type y)
{
    //template as need to use it for complex numbers as well
    return x-y;
}

int x_y_to_position(int x_in,int y_in)
{//also might be irrelevant but don't remove just incase.
    try{
        range_of_board(x_in, y_in);
    }
    catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    return (x_in-1)+(y_in-1)*8;
}

template <class c_type> bool any_move(std::complex<c_type> user, std::complex<c_type> position,bool piece_colour, board& board)
{
    //iterates through vector to seach for any piece between piece and desired square. will only return true if there is
    //if desired square has piece of oposite colour, will give option to take.
    
    std::complex<c_type> change=difference(position,user);
    
    std::vector<std::shared_ptr<piece>>::iterator it =
    std::find_if(board.on_board.begin(), board.on_board.end(), [&](const std::shared_ptr<piece> &search_piece){
        std::complex<c_type> it_cplx(static_cast<c_type>(search_piece->return_x()),static_cast<c_type>(search_piece->return_y()));
        std::complex<c_type> it_change=difference(position,it_cplx);
        
        if (std::arg(change)==std::arg(it_change)&&std::abs(it_change)<std::abs(change)){
            if (std::abs(it_change)==0){return false;}
            //above is needed so it doesn't count itself as a piece inbetween
            std::cout<<"Another piece is in the way. "<<std::endl;
            return true;
        }
        else if ((std::arg(change)==std::arg(it_change)&&std::abs(it_change)==std::abs(change))
                  &&check_can_take(piece_colour,search_piece->return_colour())==false){
            if(search_piece->return_value()==1){return true;}//specific only for pawn
            std::cout<<"Piece at chosen position is of opposite colour, would you like to take it? y,n"<<std::endl;
            char take;
            std::cin>>take;
            switch (take) {
                case 'y':
                    return false;
                    break;
                case 'n':
                    return true;
                    break;
                default:
                    return true;
                    break;
            }
            std::cin.clear();
        }
        return false;
    });
    if(it!=board.on_board.end()){
        return false;
    }else{
        return true;
    }
    return true;
}

size_t piece::operator()(int x_position,int y_position)
{
    return x_y_to_position(x_position,y_position);
}

void piece::set_x_y(int x_in, int y_in, board& playing_board)
{
    try{
        if(move(x_in, y_in, playing_board)==false){
            throw(invalid_move);
        }else{
            x_position=x_in;
            y_position=y_in;
        }
    }catch(int error_flag){
        if (error_flag==invalid_move){
            std::cerr<<"Invalid move "<<std::endl;
        }
    }
}
piece& piece::operator=(const piece &input_piece)
{
    if(&input_piece==this){
        return *this;
    }
    x_position=input_piece.x_position;
    y_position=input_piece.y_position;
    colour=input_piece.colour;
    symbol=input_piece.symbol;
    value=input_piece.value;
    return *this;
}

std::ostream& operator<<(std::ostream &output, piece& piece_output)
{
    try{
        range_of_board(piece_output.return_x(), piece_output.return_y());
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Piece not on board "<<std::endl;
        }
    }
    std::cout<<piece_output.return_symbol();
    return output;
}

//white pieces
//QUEEN
bool queen::move(int x_in,int y_in, board& board)
{
    /*
     NEED TO CHANGE, NOT TRUE ANYMORE
     all posible moves are anywhere in range in line or on a diagonal. If space is filled with piece of own colour, can only move until before it. If opposite colour in the way, it can move to its place
     all horizontal and vertical moves have to either have x_in==x_pos or y.
     all diagonal moves have to have the same chage in x as in y.
     These are used and adapted for all pieces except knight.
     */
    
    try{
        range_of_board(x_in,y_in);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    std::complex<int> user{x_in,y_in};
    std::complex<int> position{x_position, y_position};
    if(x_in==x_position||y_in==y_position){
        return any_move(user,position,colour, board);
    }
    
    if(x_in!=x_position&&y_in!=y_position){
        int change_x=difference<int>(x_position, x_in);
        int change_y=difference<int>(y_position, y_in);
        if(std::abs(change_x)==std::abs(change_y)){
            return any_move( user, position, colour, board);
        }
    }
    return false;
}
queen::queen(const int start_x,const int start_y,const std::string symbol_in,const bool colour_in)
{
    try {
        range_of_board(start_x, start_y);
    }catch(int error_flag){
        std::cerr<<"Position out of range of board "<<std::endl;
        exit(error_flag);
    }
    x_position=start_x;
    y_position=start_y;
    symbol=symbol_in;
    colour=colour_in;
}

//KING
king::king(const int start_x,const int start_y, const std::string symbol_in, const bool colour_in)
{
    try {
        range_of_board(start_x, start_y);
    }catch(int error_flag){
        std::cerr<<"Position out of range of board "<<std::endl;
        exit(error_flag);
    }
    x_position=start_x;
    y_position=start_y;
    symbol=symbol_in;
    colour=colour_in;
}
bool king::move(int x_in, int y_in,board& board)
{
    try{
        range_of_board(x_in,y_in);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    int change_x=std::abs(difference<int>(x_position, x_in));
    int change_y=std::abs(difference<int>(y_position, y_in));
    std::complex<int> user{x_in,y_in};
    std::complex<int> position{x_position, y_position};
    if((change_x==1 && change_y==1)||(change_y==1||change_x==1)){
        return any_move(user,position,colour,board);
    }
    return false;
}
//ROOK
rook::rook(const int start_x,const int start_y, const std::string symbol_in, const bool colour_in)
{
    try {
        range_of_board(start_x, start_y);
    }catch(int error_flag){
        std::cerr<<"Position out of range of board "<<std::endl;
        exit(error_flag);
    }
    x_position=start_x;
    y_position=start_y;
    symbol=symbol_in;
    colour=colour_in;
}
bool rook::move(int x_in, int y_in,board& board)
{
    //all moves are explained in white queen
    try{
        range_of_board(x_in,y_in);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    std::complex<int> user{x_in,y_in};
    std::complex<int> position{x_position, y_position};
    if(x_in==x_position||y_in==y_position){
        return any_move(user,position,colour,board);
    }
    return false;
}
//BISHOP
bishop::bishop(const int start_x,const int start_y, const std::string symbol_in, const bool colour_in)
{
    try {
        range_of_board(start_x, start_y);
    }catch(int error_flag){
        std::cerr<<"Position out of range of board "<<std::endl;
        exit(error_flag);
    }
    x_position=start_x;
    y_position=start_y;
    symbol=symbol_in;
    colour=colour_in;
}
bool bishop::move(int x_in, int y_in,board& board)
{
    try{
        range_of_board(x_in,y_in);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    std::complex<double> user{static_cast<double>(x_in),static_cast<double>(y_in)};
    std::complex<double> position{static_cast<double>(x_position), static_cast<double>(y_position)};
    if(x_in!=x_position&&y_in!=y_position){
        //abs difference in real =abs diff img means on a diagonal
        if(std::abs(difference(x_position,x_in))==std::abs(difference(y_position,y_in))){
            return any_move(user,position,colour,board);
        }
    }
    return false;
}
//KNIGHT
knight::knight(const int start_x,const int start_y, const std::string symbol_in, const bool colour_in)
{
    try {
        range_of_board(start_x, start_y);
    }catch(int error_flag){
        std::cerr<<"Position out of range of board "<<std::endl;
        exit(error_flag);
    }
    x_position=start_x;
    y_position=start_y;
    symbol=symbol_in;
    colour=colour_in;
}
bool knight::move(int x_in, int y_in, board &board)
{
    try{
        range_of_board(x_in,y_in);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    std::complex<double> user{static_cast<double>(x_in),static_cast<double>(y_in)};
    std::complex<double> position{static_cast<double>(x_position), static_cast<double>(y_position)};
    std::complex<double> change=difference(position, user);
    if(std::abs(change)==sqrt(5)){
        return true;
    }
    return false;  
}
//PAWNS
//user of namespace valid as black and white do almost the same thing just in opposite directions
white::pawn::pawn(const int start_x,const int start_y)
{
    try {
        range_of_board(start_x, start_y);
    }catch(int error_flag){
        std::cerr<<"Position out of range of board "<<std::endl;
        exit(error_flag);
    }
    x_position=start_x;
    y_position=start_y;
}





piece* white::pawn::change_piece()
{
    std::cout<<"You can now change your pawn to another piece: \n Queen (q), Rook (r), Bishop (b), Knight (n) \n";
    std::cin.clear();
    char option;
    std::cin>>option;
     
    // try {
     switch (option) {
         case 'Q':
         case 'q':
              return dynamic_cast<queen*>(this);
             break;
         case 'r':
         case 'R':
             return dynamic_cast<rook*>(this);
             break;
         case 'b':
         case 'B':
             return dynamic_cast<bishop*>(this);
             break;
         case 'n':
         case 'N':
             return dynamic_cast<knight*>(this);
             break;
        
         default:
             return this;
             break;
     }
}


bool white::pawn::move(int x_in, int y_in,board& board)
{
    try{
        range_of_board(x_in,y_in);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    std::complex<double> user{static_cast<double>(x_in),static_cast<double>(y_in)};
    std::complex<double> position{static_cast<double>(x_position), static_cast<double>(y_position)};
    std::complex<double> change=difference(position, user);
    //these magic number can be explained due to their moving on a board
    if(y_position==7&&(std::arg(change)==pi/2&&std::abs(change)==2)){
        return any_move(user, position, colour, board);
    }
    if (std::arg(change)==pi/2&&std::abs(change)==1){
        if (y_in==1){
            change_piece();
        }
        return true;
    }else if((std::arg(change)==pi/4||std::arg(change)==3*pi/4)&&std::abs(change)==sqrt(2.)){
        for(auto it=board.on_board.begin();it<board.on_board.end();it++){
            if ((*it)->return_x()==x_in&&(*it)->return_y()==y_in){
                set_value(0);//so can take
                if( any_move(user, position, colour, board)==true){
                    set_value(1);
                    if (y_in==1){
                        change_piece();
                    }
                    return true;
                }else{
                    set_value(1);
                    return false;
                }
            }
        }
    }

    return false;
}
black::pawn::pawn(const int start_x,const int start_y)
{
    try {
        range_of_board(start_x, start_y);
    }catch(int error_flag){
        std::cerr<<"Position out of range of board "<<std::endl;
        exit(error_flag);
    }
    x_position=start_x;
    y_position=start_y;
}

bool black::pawn::move(int x_in, int y_in,board& board)
{
    try{
        range_of_board(x_in,y_in);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"Position out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    std::complex<double> user{static_cast<double>(x_in),static_cast<double>(y_in)};
    std::complex<double> position{static_cast<double>(x_position), static_cast<double>(y_position)};
    std::complex<double> change=difference(position, user);
    
    
    if(y_position==2&&(std::arg(change)==-pi/2&&std::abs(change)==2)){
        return any_move(user, position,colour,board);
    }
    if (std::arg(change)==-pi/2&&std::abs(change)==1){
        return true;
    }else if((std::arg(change)==-pi/4||std::arg(change)==-3*pi/4)&&std::abs(change)==sqrt(2.)){
        for(auto it=board.on_board.begin();it<board.on_board.end();it++){
                if ((*it)->return_x()==x_in&&(*it)->return_y()==y_in){
                    set_value(0);//so can take
                    if( any_move(user, position, colour, board)==true){
                        set_value(1);
                        return true;
                    }else{
                        set_value(1);
                        return false;
                    }
                }
            }
        }
    
    return false;
}
//typedef std::pair<size_t,std::unique_ptr<piece> > pairs;
