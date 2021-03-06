#pragma once

#include <iostream>
#include <array>
#include <map>
#include <string>
#include "pieces/Piece.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Rook.h"
#include "pieces/Pawn.h"

class Board {
public:
    static const signed int cols{8};
    static const signed int rows{8};

    typedef std::array<std::array<Piece *, cols>, rows> piecesType;

    piecesType pieces_{};

    Board();

    piecesType &get_pieces();

    void generate_horizontal_movements(std::vector<std::string> &possible_moves,
                                       Piece::piece_coordinates &source);

    void generate_vertical_movements(std::vector<std::string> &possible_moves,
                                     Piece::piece_coordinates &source);

    void generate_diagonal_movements(std::vector<std::string> &possible_moves,
                                     Piece::piece_coordinates &source);

    Piece *get_piece_at(int line, int column);

    void add_piece(const std::string &place, Piece *piece);

    void build_board();

    std::vector<std::string> get_all_empty_spots(const std::string &from);

    bool is_valid_move(const std::string &from, const std::string &to);

    bool can_make_move(Piece *source_piece, Player &source_player,
                       const std::string &from, const std::string &to);

    Piece::piece_coordinates find_king(Player &player);

    bool is_king_safe(Player &player);

    bool perform_move(Player &source_player,
                      Piece::piece_coordinates from_piece_coordinates,
                      Piece *source_piece,
                      Piece::piece_coordinates to_piece_coordinates,
                      Piece *destination_piece, bool reset = false);

    bool player_has_valid_move(Player &player);

    std::vector<std::string> get_possible_moves_for(Player &player, const std::string &from);

    bool can_castle(Player &player, Piece *source_piece, const std::string &from, const std::string &to);

    std::vector<Piece::piece_coordinates>
    where_to_castle(Player &player, const std::string &to);

    void swap_castle(Player &source_player, std::string &to);

    std::vector<std::pair<std::string, std::vector<std::string>>> get_all_valid_moves_for(Player &player);
};
