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
        for i in range(5, -1, -1) :
            for j in range(7):
                if(self.pieces[coordinates[i + 6*j]] == BLANK):
                    sys.stdout.write('- ')
                elif (self.pieces[coordinates[i + 6*j]] == BLACK):
                    sys.stdout.write('X ')
                elif(self.pieces[coordinates[i + 6*j]] == WHITE):
                    sys.stdout.write('O ')
            sys.stdout.write('\n')

    def play(self, colour, row):
        if colour == self.turn:
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
                    return 'FAIL'
        return 'FAIL'

    def cont(self):
        for i in rows:
            if self.playable[row] != 'NONE':
                return True

        return False

    def north(self, location, parts):
        if location % 6 < 4:
            for i in range(4):
                parts[i] = self.pieces[coordinates[location + i]]
        return parts

    def south(self, location, parts):
        if location % 6 >= 4:
            for i in range(4):
                parts[i] = self.pieces[coordinates[location - i]]

        return parts

    def east(self, location, parts):
        if location + 6*3 < len(coordinates):
            for i in range(4):
                parts[i] = self.pieces[coordinates[location + 6*i]]

        return parts

    def west(self,location, parts):
        if location - 6*3 >= 0:
            for i in range(4):
                parts[i] = self.pieces[coordinates[location - 6*i]]

        return parts

    def north_east(self, location, parts):
        if location + 7 * 3  < len(coordinates):
            for i in range(4):
                parts[i] = self.pieces[coordinates[location + 7*i]]
        return parts

    def south_east(self, location, parts):
        if location + 5 * 3 < len(coordinates):
            for i in range(4):
                parts[i] = coordinates[location + 5*i]

        return parts

    def north_west(self, location, parts):
        if location - 5*3 >= 0:
            for i in range(4):
                parts[i] = coordinates[location - 5*i]
        return parts

    def south_west(self, location, parts):
        if location - 7*3 >= 0:
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

        location = coordinates.index(coord)
        # north east direction
        parts = self.north_east(location, parts)
        win += self.identical(parts)

        # north west direction
        parts = self.north_west(location, parts)
        win += self.identical(parts)

        # south east direction
        parts = self.south_east(location, parts)
        win += self.identical(parts)

        # south west direction
        parts = self.south_west(location, parts)
        win += self.identical(parts)

        return win

    def check_hor(self, coord):
        parts = []
        for i in range(4):
            parts.append(BLANK)

        win = 0

        # east
        location = coordinates.index(coord)
        win += self.identical(parts)

        # west
        parts = self.west(location, parts)
        win += self.identical(parts)

        return win

    def check_vertical(self, coord):
        parts = []
        for i in range(4):
            parts.append(BLANK)

        win = 0

        # north
        location = coordinates.index(coord)
        parts = self.north(location, parts)
        win += self.identical(parts)

        # south
        parts = self.south(location, parts)
        win += self.identical(parts)

        return win

    def state(self, parts, color):
        same = 0
        dif = 0
        ret = ''
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

        location = coordinates.index(coord)
        # north
        parts = board.north(location, parts)
        state_val += board.state(parts, self.color)

        # south
        parts = board.south(location, parts)
        state_val += board.state(parts, self.color)

        # east
        parts = board.east(location, parts)
        state_val += board.state(parts, self.color)

        # west
        parts = board.west(location, parts)
        state_val += board.state(parts, self.color)

        # north east
        parts = board.north_east(location, parts)
        state_val += board.state(parts, self.color)

        # south east
        parts = board.south_east(location, parts)
        state_val += board.state(parts, self.color)

        # south west
        parts = board.south_west(location, parts)
        state_val += board.state(parts, self.color)

        # north west
        parts = board.north_west(location, parts)
        state_val += board.state(parts, self.color)

        return state_val

def start():
    files = open('moves.txt', 'r')
    print("Working...")
    moves = []
    for line in files.readlines():
        moves.append(line.strip('\n'))

    # initialize board:
    my_board = Board()

    # test if overflow occurs
    for m in moves:
        sup = my_board.play(my_board.turn, m)
        print(sup) # show if fail or success

    # show the board to see if moves can be seen
    my_board.display()

start()
