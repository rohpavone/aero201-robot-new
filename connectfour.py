import sys

debug = 1

BLANK = 0
WHITE = 1
BLACK = -1

rows = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
# white is O, black is X
# 'blocked':0,'O3':-600,'O2':-60,'O1':-12,'empty':-2,'X1':10,'X2':50,'X3':500
state_vals = [-600, -60, -12, -2, 10, 50, 500, 0]
coordinates = ['a1','a2','a3','a4','a5','a6','b1','b2','b3','b4','b5','b6','c1','c2','c3','c4','c5','c6','d1','d2','d3','d4','d5','d6','e1','e2','e3','e4','e5','e6','f1','f2','f3','f4','f5','f6','g1','g2','g3','g4','g5','g6']
class Board:
    def __init__(self, board=None):
        if(board == None):
            self.pieces = {}
            self.playable = {}
            for i in coordinates:
                self.pieces[i] = BLANK # this is setting the board to blank all around, at each coordinate

            for r in rows:
                self.playable[r] = r + '1'

            self.score_white = 0
            self.score_black = 0
            self.turn = WHITE
            self.active = True
        else:
            self.pieces = board.pieces # all spots in the board, with either BLANK, WHITE or BLACK
            self.playable = board.playable # all playable spots (top of each stack)
            self.score_white = board.score_white # score of white player according to game rules
            self.score_black = board.score_black # score of black player according to rules
            self.turn = board.turn # turn of player
            self.active = board.active # state of the board. Only inactive is all spots are occupied

    def next_turn(self):
        self.turn *= -1

    def display(self):
        print('  ', end='')
        for i in rows:
            print(i, end=' ')

        print('')
        for i in range(5, -1, -1) :
            print(i+1, end=' ')
            for j in range(7):
                if(self.pieces[coordinates[i + 6*j]] == BLANK):
                    print('- ', end='')
                elif (self.pieces[coordinates[i + 6*j]] == BLACK):
                    print('X ', end='')
                elif(self.pieces[coordinates[i + 6*j]] == WHITE):
                    print('O ', end='')
            print('')

    def play(self, colour, row):
        if colour == self.turn and row in rows:
            if(self.playable[row] != 'NONE'):
                self.pieces[self.playable[row]] = colour
                if(self.playable[row][-1] != '6'):
                    if debug:
                        print("Next playable piece: {0}".format(self.playable[row][0] + self.playable[row][-1]))
                    self.playable[row] = self.playable[row][0] + str(int(self.playable[row][-1]) + 1)
                    self.check_for_win(colour)
                    self.next_turn()
                    return "SUCCESS"
                else:
                    if debug:
                        print('Not playable anymore')
                    self.playable[row] = 'NONE'
                    self.next_turn()
                    return 'SUCCESS'
                
        return 'FAIL'

    def cont(self):
        for i in rows:
            if self.playable[row] != 'NONE':
                return True

        return False

    def north(self, location):
        parts = [-2,-2,-2,-2]
        if location % 6 < 3:
            for i in range(4):
                parts[i] = self.pieces[coordinates[location + i]]
        return parts

    def south(self, location):
        parts = [-2,-2,-2,-2]
        if location % 6 >= 3:
            for i in range(4):
                parts[i] = self.pieces[coordinates[location - i]]

        return parts

    def east(self, location):
        parts = [-2,-2,-2,-2]
        if location + 6*3 < len(coordinates):
            for i in range(4):
                parts[i] = self.pieces[coordinates[location + 6*i]]

        return parts

    def west(self,location):
        parts = [-2,-2,-2,-2]
        if location - 6*3 >= 0:
            for i in range(4):
                parts[i] = self.pieces[coordinates[location - 6*i]]

        return parts

    def north_east(self, location):
        parts = [-2,-2,-2,-2]
        if location + 6 * 3 < len(coordinates) and location % 6 < 3:
            for i in range(4):
                parts[i] = self.pieces[coordinates[location + 7*i]]
        return parts

    def south_east(self, location):
        parts = [-2,-2,-2,-2]
        if location + 6 * 3 < len(coordinates) and location % 6 >= 3:
            for i in range(4):
                parts[i] = coordinates[location + 5*i]

        return parts

    def north_west(self, location):
        parts = [-2,-2,-2,-2]
        if location % 6 < 3 and location - 6*3 >= 0:
            for i in range(4):
                parts[i] = coordinates[location - 5*i]
        return parts

    def south_west(self, location):
        parts = [-2,-2,-2,-2]
        if location - 6*3 >= 0 and location % 6 >= 3 :
            for i in range(4):
                parts[i] = coordinates[location - 7*i]
        return parts

    def identical(self, parts):
        if parts[0] != BLANK:
            if parts[0] == parts[1] and parts[0] == parts[2] and parts[0] == parts[3]:
                return 1
        return 0

    def check_for_win(self, color):
        win = 0
        for i in range(5, -1, -1):
            for j in range(7):
                if(self.pieces[coordinates[i + 6*j]] == color):
                    win += self.check_diag(coordinates[i + 6*j])
                    win += self.check_hor(coordinates[i + 6*j])
                    win += self.check_hor(coordinates[i + 6*j])
        return win

    def check_diag(self, coord):
        parts = []
        for i in range(4):
            parts.append(BLANK)

        win = 0
        if coord in coordinates:
            location = coordinates.index(coord)
            # north east direction
            parts = self.north_east(location)
            win += self.identical(parts)

            # north west direction
            parts = self.north_west(location)
            win += self.identical(parts)

            # south east direction
            parts = self.south_east(location)
            win += self.identical(parts)

            # south west direction
            parts = self.south_west(location)
            win += self.identical(parts)

        return win

    def check_hor(self, coord):
        parts = []
        for i in range(4):
            parts.append(BLANK)

        win = 0

        if coord in coordinates:
            # east
            location = coordinates.index(coord)
            win += self.identical(parts)

            # west
            parts = self.west(location)
            win += self.identical(parts)

        return win

    def check_vertical(self, coord):
        parts = []
        for i in range(4):
            parts.append(BLANK)

        win = 0

        if coord in coordinates:
            # north
            location = coordinates.index(coord)
            parts = self.north(location)
            win += self.identical(parts)

            # south
            parts = self.south(location)
            win += self.identical(parts)

        return win

    def state(self, parts, color):
        same = 0
        dif = 0
        ret = ''
        if -2 in parts: # invalid, was not there
            return 0
        for i in parts:
            same += 1 if i == color else 0
            dif += 1 if i == color*-1 else 0

        if dif:
            if same:
                # both are mixed, this set is considered blocked
                ret = state_vals[-1]
            else:
                ret = state_vals[dif + 3]
        else:
            # no different pieces, only own pieces or empty
            ret = state_vals[same + 3]

        # should I add a part that keeps track of paths that are blocked and
        # ignores them? How could this be done?
        return ret
class Player:

    def __init__(self, color, plies):
        self.color = color
        self.plies = plies

    def utility(self, coord, board):
        # check what is going on in each direction and match it to the state_vals
        # only will evaluate this way if this is a terminal state (end of the
        # plies)
        parts = [0,0,0,0]
        state_val = 0
        max_coords = len(coordinates) - 1
        min_coords = 0
        if coord in coordinates:
            location = coordinates.index(coord)
            # north
            parts = board.north(location)
            state_val += board.state(parts, self.color)

            # south
            parts = board.south(location)
            state_val += board.state(parts, self.color)

            # east
            parts = board.east(location)
            state_val += board.state(parts, self.color)

            # west
            parts = board.west(location)
            state_val += board.state(parts, self.color)

            # north east
            parts = board.north_east(location)
            state_val += board.state(parts, self.color)

            # south east
            parts = board.south_east(location)
            state_val += board.state(parts, self.color)

            # south west
            parts = board.south_west(location)
            state_val += board.state(parts, self.color)

            # north west
            parts = board.north_west(location)
            state_val += board.state(parts, self.color)

            # check the middle, in between parts here
            if location + 6 <= max_coords:
                parts = board.west(location + 6)
                state_val += board.state(parts, self.color)
            if location + 7 <= max_coords:
                parts = board.south_west(location + 7)
                state_val += board.state(parts, self.color)
            if location + 5 <= max_coords:
                parts = board.north_west(location +5)
                state_val += board.state(parts, self.color)
            if location + 1 <= max_coords:
                parts = board.south(location + 1)
                state_val += board.state(parts, self.color)
            if location - 1 >= min_coords:
                parts = board.north(location -1)
                state_val += board.state(parts, self.color)
            if location - 5 >= min_coords:
                parts = board.south_east(location - 5)
                state_val += board.state(parts, self.color)
            if location -6 >= min_coords:
                parts = board.east(location -6)
                state_val += board.state(parts, self.color)
            if location - 7 >= min_coords:
                parts = board.north_east(location -7)
                state_val += board.state(parts, self.color)

        return state_val


if __name__ == "__main__":
    # initialize board:
    white_player = Player(WHITE, 1) # white player, 1 ply
    black_player = Player(BLACK, 1) # black player, 1 ply
    input_string = ""
    my_board = Board()
    utilities = []
    my_board.display()
    while input_string != "STOP" and my_board.playable: # board should be playable and not stop
        utilities = []
        if my_board.turn == WHITE: # player
            input_string = "" # force it to go through loop first
            while not input_string in list(my_board.playable.values()):
                input_string = input("Enter a row to play: ")
                if not input_string in list(my_board.playable.values()):
                    print("Invalid - row not playable")

            # play it now
            my_board.play(WHITE, input_string[0])
            my_board.display() #show the game board
        # black turn now
        else:
            # no input turn here, just let black play
            for value in list(my_board.playable.values()):
                utilities.append(black_player.utility(value, my_board))

            print(utilities)
            print(list(my_board.playable.values()))
            play_me = list(my_board.playable.values())[utilities.index(max(utilities))]
            my_board.play(BLACK, play_me[0])
            my_board.display() #show the game board
            
                                 

            
            

