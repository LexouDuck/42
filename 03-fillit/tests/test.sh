#!/bin/sh

# Color code definitions
RESET='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
# Function to display test names
put() { printf "\n${BLUE}> $@${RESET}\n"; }
# Function to display commands
exe() { echo -e "> $@" ; "$@" ; }

echo -e "\n\n${BLUE}=== Error case tests ===${RESET}"
put "No argument given"
exe ./fillit
put "2 arguments given"
exe ./fillit tests/test_same_piece_diff_pos.txt test_all_pieces.txt
put "Nonexistant file argument given"
exe ./fillit tests/fillit
put "The second example from the 42 pdf (one line missing a char)"
exe ./fillit tests/test_42sample_error.txt
put "Invalid tetramino example from the 42 pdf (one line with too many chars)"
exe ./fillit tests/test_42sample_error1.txt
put "Invalid tetramino example from the 42 pdf (full 4x4 '#' square)"
exe ./fillit tests/test_42sample_error2.txt
put "File with invalid format (2 line-returns)"
exe ./fillit tests/test_invalid_newline.txt
put "File with invalid format (missing line-return)"
exe ./fillit tests/test_invalid_newline2.txt
put "File with invalid tetramino (only '.'s)"
exe ./fillit tests/test_invalid_tminos0.txt
put "File with invalid tetramino (non-connected shape)"
exe ./fillit tests/test_invalid_tminos1.txt
put "File with invalid tetramino (diagonal-connected shape)"
exe ./fillit tests/test_invalid_tminos2.txt
put "File with invalid tetramino (shape of only 3 blocks)"
exe ./fillit tests/test_invalid_tminos3.txt
put "File with 27 tetraminos, that is otherwise valid"
exe ./fillit tests/test_27_tminos.txt

echo -e "\n\n${BLUE}=== Fillit tests ===${RESET}"
put "Single square tetramino (expecting 2x2)"
exe ./fillit tests/test_single_square.txt
put "Single L-shape tetramino (expecting 3x3)"
exe ./fillit tests/test_single_Lnrm_rot0.txt
put "4 T-shaped tetraminos, in each of their 4 rotations (expecting a 4x4)"
exe ./fillit tests/test_4_Tshapes.txt
put "Six rotated L-shape tetraminos (expecting a 6x6 where tetraminos are in a grid pattern)"
exe ./fillit tests/test_same_piece_diff_pos.txt
put "The first example from the 42 pdf, expecting:\n>\tDDAA\n>\tCDDA\n>\tCCCA\n>\tBBBB"
exe ./fillit tests/test_42sample1.txt
put "The last example from the 42 pdf, expecting:\n>\tABBBB.\n>\tACCCEE\n>\tAFFCEE\n>\tA.FFGG\n>\tHHHDDG\n>\t.HDD.G"
exe ./fillit tests/test_42sample2.txt
put "10 tetraminos"
exe ./fillit tests/test_10_tminos.txt
put "11 tetraminos"
exe ./fillit tests/test_11_tminos.txt
put "12 tetraminos"
exe ./fillit tests/test_12_tminos.txt
put "15 tetraminos"
exe ./fillit tests/test_15_tminos.txt
put "Every different tetramino (all 19 types)"
exe ./fillit tests/test_all_pieces.txt
put "26 tetraminos (the maximum allowed amount)"
exe ./fillit tests/test_26_tminos.txt
