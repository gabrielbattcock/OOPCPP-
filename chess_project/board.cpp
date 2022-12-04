//
//  board.cpp
//  Project
//
//  Created by Gabriel Battcock on 11/04/2020.
//  Where functions for the board class are stored. This is where things like making the move on the board, constructing the board,
//  and storing move are defined
//

#include "board.hpp"
#include "pieces.hpp"
const int range_flag{1};
void range_of_board(int x_in,int y_in);
bool check_can_take(bool user_piece, bool other_piece);

board::board(std::vector<std::shared_ptr<piece>> input_vector)
{
    for(auto iterator=input_vector.begin();iterator<input_vector.end();iterator++){
        on_board.push_back(*iterator);
    }

}
board::board(board& board_copy)
{
    on_board.clear();
    for(auto iterator=board_copy.on_board.begin();iterator<board_copy.on_board.end();iterator++){
        on_board.push_back(*iterator);
         
    }
}
board::board(board&& board_move)
{
    on_board.clear();
    for(auto iterator=board_move.on_board.begin();iterator<board_move.on_board.end();iterator++){
        on_board.push_back(*iterator);
    }
    board_move.on_board.clear();
}
board& board::operator=(const board& input_board)
{
    if(&input_board==this){
        return *this;
    }
    on_board.clear();
    black_pieces_taken.clear();
    white_pieces_taken.clear();
    previous_moves.clear();
    for(auto iterator=input_board.on_board.begin();iterator<input_board.on_board.end();iterator++){
        on_board.push_back(*iterator);

    }
    for(auto li=input_board.black_pieces_taken.begin();li!=input_board.black_pieces_taken.end();li++){
        black_pieces_taken.push_front((*li));
    }
    for(auto li=input_board.white_pieces_taken.begin();li!=input_board.white_pieces_taken.end();li++){
         white_pieces_taken.push_front((*li));
     }
    for(auto li=input_board.previous_moves.begin();li!=input_board.previous_moves.end();li++){
        previous_moves.push_front((*li));
    }
    turn=input_board.turn;
    return *this;
}
void board::make_move()
{
    if (turn==true){
        std::cout<<"White turn: \n";
    }
    else{
        std::cout<<"Black turn: \n";
    }
    std::cout<<"Please enter a move, from position to position in for ##,##:"<<std::endl;
    std::cin.clear();
    std::string input_line;
    std::getline(std::cin,input_line);
    
    while(input_line.find(',')!=2||input_line.length()!=5){
        std::cerr<<"Error: wrong input. "<<std::endl;
        std::cin.clear();
        std::getline(std::cin,input_line);
    }
    int x_currently; int y_currently;
    int x_user; int y_user;
    
    x_currently=std::stoi(input_line.substr(0,1));
    y_currently=std::stoi(input_line.substr(1,1));
    x_user=std::stoi(input_line.substr(3,1));
    y_user=std::stoi(input_line.substr(4,1));
    
    try{
        range_of_board(x_currently, y_currently);
        range_of_board(x_user, y_user);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"One position is out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    
    std::shared_ptr<piece> moving_piece{nullptr};
    std::shared_ptr<piece> taking_piece{nullptr};
    //check that there is a piece at initial conidition
    for(auto iterator=on_board.begin();iterator<on_board.end();iterator++){
        if((*iterator)->return_x()==x_currently&&(*iterator)->return_y()==y_currently){
            moving_piece=*iterator;
        }else if((*iterator)->return_x()==x_user&&(*iterator)->return_y()==y_user){
            taking_piece=*iterator;
        }
    }
    if(moving_piece==nullptr){
        std::cout<<"You have not selected a piece "<<std::endl;
        return;
    }
    if(moving_piece->return_colour()!=turn){
        std::cerr<<"You cannot move piece of opposite colour "<<std::endl;
        return;
    }
    //to check if they are different colours, I am using and XOR gate (a^b)
    
    if(taking_piece!=nullptr){
        if((taking_piece->return_colour()^moving_piece->return_colour())==false){
            std::cout<<"Cannot move to square with piece of same colour. "<<std::endl;
            return;
        }
        std::vector<std::shared_ptr<piece>>::iterator it =
        std::find_if(on_board.begin(), on_board.end(), [&](const std::shared_ptr<piece> &search_piece){
            if (search_piece == taking_piece){
                return true;
            }else{
            return false;
            }
        });
            if (it != on_board.end()&&moving_piece->move(x_user, y_user, *this)==true){
                //std::cout<<*it<<std::endl;
                if((*it)->return_colour()==true){
                    white_pieces_taken.push_back(*it);
                }else{
                    black_pieces_taken.push_back(*it);
                }
                moving_piece->set_x_y(x_user, y_user, *this);
                previous_moves.push_back(input_line);
                turn=!turn;
                on_board.erase(it);
                return;
                //store taken pieces
            }
            else{
                std::cout<<"Could not take piece. ";
                return;
            }
    }
    
    moving_piece->set_x_y(x_user, y_user, *this);
    previous_moves.push_back(input_line);
    turn=!turn;
}

void board::print()
{
    for (auto iterator{on_board.begin()};iterator<on_board.end();iterator++){
        (*iterator)->print();
    }
}
void board::print_board(const int_pairs& possible_moves)//std::optional<std::vector<std::pair<int,int>>> show_moves
{
    std::string WHITE_SQUARE {u8"\u2B1C"};
    std::string BLACK_SQUARE {u8"\u2B1B"};
    
    
    std::cout.fill(' ');
    std::cout<<std::setw(5)<<'A'<<std::setw(8)<<'B'<<std::setw(8)<<'C'<<std::setw(8)<<'D'<<std::setw(8)<<'E'<<std::setw(8)<<'F'<<std::setw(8)<<'G'<<std::setw(8)<<'H'<<std::endl;
    //std::cout<<std::setfill('-')<<std::setw(50)<<"="<<std::endl;
    for(int i{8};i>0;i--){
        std::cout<<i<<'|';
        for(int j{1};j<9;j++){
            
            if((i+j)%2==0){
                std::shared_ptr<piece> iterator_piece{nullptr};
                //search for piece
                for(auto iterator=on_board.begin();iterator<on_board.end();iterator++){
                    if((*iterator)->return_x()==j&&(*iterator)->return_y()==i){
                        iterator_piece=*iterator;
                        }
                }
                //only for showing possible moves, look for square which you can move
                bool possible{false};
                for(auto iterator=possible_moves.begin();iterator!=possible_moves.end();iterator++){
                    if((*iterator).first==j&&(*iterator).second==i){
                        possible=true;
                    }
                }
                if(iterator_piece!=nullptr){
                        std::cout.fill('#');
                        std::cout << std::setw(4)<<iterator_piece->return_symbol();
                        std::cout<<std::setw(3)<<'#'<<'|';
                    
                }else if(possible==true){
                        std::cout.fill('#');
                        std::cout << std::setw(4)<<"MOVE";
                        std::cout<<std::setw(3)<<'#'<<'|';
                }
                else{
                        std::cout.fill('#');
                        std::cout << std::setw(7)<<'#'<<'|';
                        }
            }
            else{
            
                std::shared_ptr<piece> iterator_piece{nullptr};
                for(auto iterator=on_board.begin();iterator<on_board.end();iterator++){
                    if((*iterator)->return_x()==j&&(*iterator)->return_y()==i){
                        iterator_piece=*iterator;
                    }
                }
                bool possible{false};
                for(auto iterator=possible_moves.begin();iterator!=possible_moves.end();iterator++){
                    if((*iterator).first==j&&(*iterator).second==i){
                        possible=true;
                    }
                }
                if(iterator_piece!=nullptr){
                        std::cout.fill(' ');
                        std::cout << std::setw(4)<<iterator_piece->return_symbol();
                        std::cout<<std::setw(3)<<' '<<'|';
                }else if(possible==true){
                        std::cout.fill(' ');
                        std::cout << std::setw(4)<<"MOVE";
                        std::cout<<std::setw(3)<<' '<<'|';
                }
                else{
                        std::cout.fill(' ');
                        std::cout << std::setw(7)<<' '<<'|';
                        }
            }
        }
        std::cout<<std::endl;
        //std::cout.fill('-');
        //std::cout<<std::setw(64);
        }
}
void board::print_position()
{
    for (auto iterator{on_board.begin()};iterator<on_board.end();iterator++){
        std::cout<<(*iterator)->return_x()<<','<<(*iterator)->return_y()<<std::endl;
    }
}

void board::print_pieces_taken()
{
    std::cout<<"White pieces taken: ";
    
    for(auto iterator= white_pieces_taken.begin();iterator!=white_pieces_taken.end();iterator++){
        std::cout<<(*iterator)->return_symbol();
    }std::cout<<std::endl;
    std::cout<<"black pieces taken: ";
    
    for(auto iterator= black_pieces_taken.begin();iterator!=black_pieces_taken.end();iterator++){
        std::cout<<(*iterator)->return_symbol();
    }std::cout<<std::endl;
    
}

void board::print_moves()
{
    std::cout<<"Previous moves played:  \n";
    std::cout.fill(' ');
    for(auto iterator=previous_moves.begin();iterator!=previous_moves.end();iterator++){
        std::cout<<std::setw(6)<<*iterator;
    }std::cout<<std::endl;
}

void board::show_possible_moves()
{
    if (turn==true){
        std::cout<<"White turn: \n";
    }
    else{
        std::cout<<"Black turn: \n";
    }
    std::cout<<"Please enter a piece for which you'd like to see the possible moves in form ##:"<<std::endl;
    std::cin.clear();
    std::string input_line;
    std::getline(std::cin,input_line);
    
    while(input_line.length()!=2){
        std::cerr<<"Error: wrong input. "<<std::endl;
        std::cin.clear();
        std::getline(std::cin,input_line);
    }
    int x_currently; int y_currently;
   // int x_user; int y_user;
    
    x_currently=std::stoi(input_line.substr(0,1));
    y_currently=std::stoi(input_line.substr(1,1));
    
    try{
        range_of_board(x_currently, y_currently);
    }catch(int error_flag){
        if(error_flag==range_flag){
            std::cerr<<"One position is out of range of board "<<std::endl;
            exit(error_flag);
        }
    }
    
    std::shared_ptr<piece> moving_piece{nullptr};
    //check that there is a piece at initial conidition
    for(auto iterator=on_board.begin();iterator<on_board.end();iterator++){
        if((*iterator)->return_x()==x_currently&&(*iterator)->return_y()==y_currently){
            moving_piece=*iterator;
        }
    }
    if(moving_piece==nullptr){
        std::cout<<"You have not selected a piece "<<std::endl;
        return;
    }
    if(moving_piece->return_colour()!=turn){
        std::cerr<<"You cannot choose piece of opposite colour "<<std::endl;
        return;
    }
    //push all true coordinates to vector
    int_pairs possible_moves;
    for(int i{1};i<9;i++){
        for (int j{1};j<9;j++){
            if (moving_piece->move(i,j,*this)==true){
                possible_moves.push_back(std::make_pair(i, j));
            }
        }
    }
    print_board(possible_moves);
    return;
}

void board::save_game()
{
    std::ofstream game;
    
    try{
        game.open("saved_game.txt",std::ios::app);
        for(auto it=on_board.begin();it<on_board.end();it++){
            game<<(*it);
        }
        for(auto li=white_pieces_taken.begin();li!=white_pieces_taken.end();li++){
            game<<(*li);
        }for(auto li=black_pieces_taken.begin();li!=black_pieces_taken.end();li++){
            game<<(*li);
        }for(auto li=previous_moves.begin();li!=previous_moves.end();li++){
            game<<(*li);
        }
        game<<turn;
        game.close();
    }catch(const std::ifstream::failure& except){
        std::cerr<<"Could not save game "<<std::endl;
    }
   
    game.close();
    return;

}
/*
board board::load_game()
{
    std::ifstream game;
    try{
        game.open("saved_game.txt",std::ios::in);
        board input_game;
        
        input_game
        game.read((char*)&input_game,sizeof(input_game));
        *this=input_game;
    }catch(const std::ifstream::failure& except)
    {
        std::cerr<<"Could not load game "<<std::endl;
    }
    game.close();
    return *this;
}
 
*/
   /* for(int j{};j<8;j++){
    if(i%4==0){
        std::cout<<' ';
        std::cout.fill('-');
        std::cout<<std::setw(8)<<' ';
    }
    else if(i%2==0){
        std::cout.fill(' ');
        std::cout<<'|'<<std::setw(8)<<' ';
    }
    else{std::cout.fill(' ');
        std::cout.fill(' ');
        std::cout<<'|'<<std::setw(8)<<' ';

    }
    }
    
    std::cout<<'|'<<std::endl;
}
std::cout<<' ';
std::cout.fill('-');
std::cout<<std::setw(72)<<' '<<std::endl;*/
//}
    /*
    std::cout<<"  "<<std::flush;
    std::cout<<"  ||"<<std::flush;
    std::cout<<i<<"||"<<std::flush;
    std::cout<<"  ||"<<std::flush;
    std::cout<<"  "<<std::flush;
     */
