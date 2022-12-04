//
//  board.hpp
//  Project
//
//  Created by Gabriel Battcock on 11/04/2020.
//  Copyright © 2020 Gabriel Battcock. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include "board.hpp"
#include "pieces.hpp"
#include <stdio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<optional>
#include<memory>
#include<map>
#include<string>
#include<utility>
#include<list>
#include<vector>
#include<algorithm>
#include<complex>


class piece;
class queen;
class king;
class bishop;
class rook;
namespace white{
    class pawn;
}
namespace black{
    class pawn;
}



typedef std::vector<std::pair<int,int>> int_pairs;
class board
{
    friend class piece;
    friend class queen;
    friend class king;
    friend class bishop;
    friend class rook;
    friend class white::pawn;
    friend class black::pawn;
protected:
    //maybe look into making a map of index A B C etc and position, like a real chess board
    std::vector<std::shared_ptr<piece>> on_board;
    std::list<std::shared_ptr<piece>> black_pieces_taken;
    std::list<std::shared_ptr<piece>> white_pieces_taken;
    bool turn{true};
    std::list<std::string> previous_moves;
    
public:
    board(){}
    board(std::vector<std::shared_ptr<piece>> input_vector);
    board(board& board_copy);
    board(board&& board_move);
    ~board(){on_board.clear(); std::cout<<"Destroying board"<<std::endl;}
    
    board& operator=(const board& input_board);
    void make_move();
    //std::vector<std::shared_ptr<piece>> return_board(){return on_board;}
    void print_position();//need to delete this as should be irrelevent when I have a board set up
    void print_board(const int_pairs& possible_moves=int_pairs());//std::optional<std::vector<std::pair<int,int>>> show_moves
    void print_moves();
    void print_pieces_taken();
    void show_possible_moves();
    board load_game();
    void save_game();
    void print();
    //bool change_turn(bool change_turn){turn=change_turn;}
    //friend bool hori_vert_move(int x_position, int x_user, int y_position, int y_user, board& board);
    template <class c_type>
    friend  bool any_move(std::complex<c_type> user, std::complex<c_type> position,bool piece_colour, board& board);

};

#endif /* board_hpp */
