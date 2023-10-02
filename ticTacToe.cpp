#include <iostream>
#include <vector>
using namespace std;

class Player {
private:
    string name;
    char playerSymbol;

public:
    Player(string& name, char pSym):name(name), playerSymbol(pSym) {}
    string& getName() { return name; }
    char getSymbol() { return playerSymbol; }
};

class Board {
private:
    int boardSize;
    vector<vector<char>> board;
    
public:
    Board(int size):boardSize(size) {
        board = vector<vector<char>>(size, vector<char>(size, '-'));
    }
    
    void printBoard() {
        for(auto& row : board) {
            for(auto& sym : row) {
                cout << " " << sym;
            }
            cout << endl;
        }
    }
    
    bool setPosition(int row,int col, char pSym) {
		if(row>=0 && col>=0 && row<boardSize && col<boardSize && board[row][col]=='-') {
		    board[row][col] = pSym;
			return true;
		}
		return false;
    }
    
    bool checkWinner(char pSym) {
		//check all rows
		for(int i=0; i<boardSize; i++) {
		    bool flag = true;
			for(int j=0; j<boardSize; j++) {
				if(board[i][j] != pSym) {
				    flag = false;
				    break;
			    }
			}
			if(flag)
				return flag;
		}
		
		//check all columns
		for(int i=0; i<boardSize; i++) {
			bool flag = true;
			for(int j=0; j<boardSize; j++) {
				if(board[j][i] != pSym) {
				    flag = false;
				    break;
				}
			}
			if(flag)
				return flag;
		}
		
		//check all diagonals
		bool leftDiag = true, rightDiag = true;
		for(int i=0; i<boardSize; i++) {
			if(board[i][i] != pSym)
			    leftDiag = false;
			if(board[i][boardSize-i-1] != pSym)
			    rightDiag = false;
		}
		if(leftDiag || rightDiag)
			return true;
		
		return false;
	}
};


int main()
{
	int size;
	cout << "Enter the size of board: ";
	cin >> size;
	Board playingBoard(size);
	
	string Name;
	
	cout << "Enter player1 name: ";
	cin >> Name;
	Player player1(Name, 'X');
	
	cout << "Enter player2 name: ";
	cin >> Name;
	Player player2(Name, 'O');
	
	bool player1Turn = true, match_tie = true;
	int totalTurns = size*size, turns = 0;
	
	while(turns < totalTurns) {
		cout << "\nCurrent board situation -->\n";
		playingBoard.printBoard();
		
		if(player1Turn)
			cout << "\nPrompt to player 1\n";
		else
			cout << "\nPrompt to player 2\n";
		
		int row, col;
		cout << "Enter row and column position: ";
		cin >> row >> col;
		bool turn_success;
		
		if(player1Turn) { //Player1
			turn_success = playingBoard.setPosition(row, col, player1.getSymbol());
			if(turn_success) {
				if(playingBoard.checkWinner(player1.getSymbol())) {
					cout << player1.getName() << " wins!\n";
					match_tie = false;
					break;
				}
				player1Turn = !player1Turn;
				turns++;
			}
			else
				cout << "Invalid Move! Try again\n";
		}
		else { //Player2
			turn_success = playingBoard.setPosition(row, col, player2.getSymbol());
			if(turn_success) {
				if(playingBoard.checkWinner(player2.getSymbol())) {
					cout << player2.getName() << " wins!\n";
					match_tie = false;
					break;
				}
				player1Turn = !player1Turn;
				turns++;
			}
			else
				cout << "Invalid Move! Try again\n";
		}
	}
	
	if(match_tie)
		cout << "Match Tied\n";
		
	cout << "Match Finished\n";
	return 0;
}