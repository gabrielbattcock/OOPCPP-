//  main.cpp
//  Project
//  Created by Gabriel Battcock on 28/03/2020.
//  Using the header files for both board and pieces, I set the pieces on the board and allow for full game play.
//

#include <iostream>
#include <algorithm>
#include <memory>
#include "pieces.hpp"
#include "board.hpp"

std::vector<std::shared_ptr<piece>> set_pieces()
{
    std::vector<std::shared_ptr<piece>> game_board;
    //white pieces
    std::shared_ptr<piece> WQ{new queen{4,8,"WQ",true}};
    std::shared_ptr<piece> WK{new king{5,8,"WK",true}};
    std::shared_ptr<piece> WB1{new bishop{6,8,"WB",true}};
    std::shared_ptr<piece> WB2{new bishop{3,8,"WB",true}};
    std::shared_ptr<piece> WN1{new knight{2,8,"WN",true}};
    std::shared_ptr<piece> WN2{new knight{7,8,"WN",true}};
    std::shared_ptr<piece> WR1{new rook{1,8,"WR",true}};
    std::shared_ptr<piece> WR2{new rook{8,8,"WR",true}};
    
    std::shared_ptr<piece> WP1{new white::pawn{1,7}};
    std::shared_ptr<piece> WP2{new white::pawn{2,2}};
    std::shared_ptr<piece> WP3{new white::pawn{3,7}};
    std::shared_ptr<piece> WP4{new white::pawn{4,7}};
    std::shared_ptr<piece> WP5{new white::pawn{5,7}};
    std::shared_ptr<piece> WP6{new white::pawn{6,7}};
    std::shared_ptr<piece> WP7{new white::pawn{7,7}};
    std::shared_ptr<piece> WP8{new white::pawn{8,7}};
    
    //black
    std::shared_ptr<piece> BQ{new queen{4,1,"BQ",false}};
    std::shared_ptr<piece> BK{new king{5,01,"BK",false}};
    std::shared_ptr<piece> BB1{new bishop{6,1,"BB",false}};
    std::shared_ptr<piece> BB2{new bishop{3,1,"BB",false}};
    //std::shared_ptr<piece> BN1{new knight{2,1,"BN",false}};
    std::shared_ptr<piece> BN2{new knight{7,1,"BN",false}};
    std::shared_ptr<piece> BR1{new rook{1,1,"BR",false}};
    std::shared_ptr<piece> BR2{new rook{8,1,"BR",false}};
    
    std::shared_ptr<piece> BP1{new black::pawn{1,2}};
    //std::shared_ptr<piece> BP2{new black::pawn{2,2}};
    std::shared_ptr<piece> BP3{new black::pawn{3,2}};
    std::shared_ptr<piece> BP4{new black::pawn{4,2}};
    std::shared_ptr<piece> BP5{new black::pawn{5,2}};
    std::shared_ptr<piece> BP6{new black::pawn{6,2}};
    std::shared_ptr<piece> BP7{new black::pawn{7,2}};
    std::shared_ptr<piece> BP8{new black::pawn{8,2}};
    
    //std::shared_ptr<piece> BK{new queen{6,3,"BQ",false}};
    game_board.push_back(WQ);
    game_board.push_back(WK);
    game_board.push_back(WB1);
    game_board.push_back(WB2);
    game_board.push_back(WN1);
    game_board.push_back(WN2);
    game_board.push_back(WR1);
    game_board.push_back(WR2);
    game_board.push_back(BQ);
    game_board.push_back(BK);
    game_board.push_back(BB1);
    game_board.push_back(BB2);
   // game_board.push_back(BN1);
    game_board.push_back(BN2);
    game_board.push_back(BR1);
    game_board.push_back(BR2);
    game_board.push_back(WP1);
    game_board.push_back(WP2);
    game_board.push_back(WP3);
    game_board.push_back(WP4);
    game_board.push_back(WP5);
    game_board.push_back(WP6);
    game_board.push_back(WP7);
    game_board.push_back(WP8);
    game_board.push_back(BP1);
   // game_board.push_back(BP2);
    game_board.push_back(BP3);
    game_board.push_back(BP4);
    game_board.push_back(BP5);
    game_board.push_back(BP6);
    game_board.push_back(BP7);
    game_board.push_back(BP8);
    
    return game_board;
}

void menu()
{
    board a{set_pieces()};
    a.print_board();
    bool play{true};
    do{
    //menu will appear before every go giving the following options
        
    std::cout.fill(' ');
    std::cout<<"Please select an option:\n"<<std::setw(6)<<"Play game (p)\n"<<
    std::setw(6)<<"View moves played (m)\n"<<std::setw(6)<<"View pieces taken (t) \n"<<
    std::setw(6)<<"View possible moves (z)\n"<<
    std::setw(6)<<"Exit (x)\n";
    
        
        
    std::cin.clear();
    char option;
    std::cin>>option;
    
   // try {
        switch (option) {
            case 'p':
            case 'P':
                
                a.make_move();
                //a.print_position();
                a.print_board();
                break;
            case 'm':
            case 'M':
                a.print_moves();
                break;
            case 't':
            case 'T':
                a.print_pieces_taken();
                break;
            case 'z':
            case 'Z':
                a.show_possible_moves();
                break;
            case 'x':
            case 'X':
                play=false;
            default:
                break;
        }
   // }

    }while(play==true);
    return;
}


void play_game()
{
    //
}



int main() {
    //https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode
    std::cout<<"Hello and welcome to the ancient game Chess, now on computers.\n";
    std::cout.fill('-');
    std::cout<<std::setw(50);
    
    menu();
    
    
    return 0;
}


