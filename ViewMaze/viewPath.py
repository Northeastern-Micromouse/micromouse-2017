import tkinter
from tkinter import *
import time

class Cell:
    cellSize = 30
    bufferSize = 10

    def __init__(self, x, y, top = "unknown", left = "unknown",
                 right = "unknown", bot = "unknown"):
        self.top = top
        self.left = left
        self.right = right
        self.bot = bot
        self.col = x
        self.row = y
        self.id = "x" + str(x) + "y" + str(y)

    @staticmethod
    def wallColor(side):
        if (side == "unknown") :
            return "red"
        elif (side == "wall") :
            return "black"
        elif (side == "space") :
            return "white"

    def drawCell(self, c):
        c.delete(self.id)
        c.create_line(Cell.cellSize * self.col + Cell.bufferSize,
                      Cell.cellSize * self.row + Cell.bufferSize,
                      Cell.cellSize * self.col + Cell.bufferSize,
                      Cell.cellSize * (self.row + 1) + Cell.bufferSize,
                      fill = Cell.wallColor(self.left), tags = self.id)

        c.create_line(Cell.cellSize * self.col + Cell.bufferSize,
                      Cell.cellSize * self.row + Cell.bufferSize,
                      Cell.cellSize * (self.col + 1) + Cell.bufferSize,
                      Cell.cellSize * self.row + Cell.bufferSize,
                      fill = Cell.wallColor(self.top), tags = self.id)

        c.create_line(Cell.cellSize * (self.col + 1) + Cell.bufferSize,
                      Cell.cellSize * self.row + Cell.bufferSize,
                      Cell.cellSize * (self.col + 1) + Cell.bufferSize,
                      Cell.cellSize * (self.row + 1) + Cell.bufferSize,
                      fill = Cell.wallColor(self.right), tags = self.id)

        c.create_line(Cell.cellSize * self.col + Cell.bufferSize,
                      Cell.cellSize * (self.row + 1) + Cell.bufferSize,
                      Cell.cellSize * (self.col + 1) + Cell.bufferSize,
                      Cell.cellSize * (self.row + 1) + Cell.bufferSize,
                      fill = Cell.wallColor(self.bot), tags = self.id)
        
class Maze:
    h = 16
    w = 16
    animationSpeed = 1
    
    def __init__(self, can):
        self.curX = 0
        self.curY = 0
        self.maze = [[Cell(x, y) for y in range(Maze.w)] for x in range(Maze.h)]
        #self.truth = truth
        self.truth = self.readMaze()

        self.c = can
        self.pos = self.c.create_oval(
            (self.curX + .2) * Cell.cellSize + .2 + Cell.bufferSize,
            (self.curY + .2) * Cell.cellSize + Cell.bufferSize,
            (self.curX + .8) * Cell.cellSize + Cell.bufferSize,
            (self.curY + .8) * Cell.cellSize + Cell.bufferSize,
            tags="position")
        
    def drawMaze(self):
        for x in range(0, Maze.w):
            for y in range(0, Maze.h):
                self.maze[x][y].drawCell(self.c)

    def updateMaze(self, direction):
        oldX = self.curX
        oldY = self.curY
        if (direction == "up") :
            self.curY = self.curY - 1
        elif (direction == "down") :
            self.curY = self.curY + 1
        elif (direction == "left") :
            self.curX = self.curX - 1
        elif (direction == "right") :
            self.curX = self.curX + 1
        self.lookAround()
        self.c.move(self.pos,
                    (self.curX - oldX) * Cell.cellSize,
                    (self.curY - oldY) * Cell.cellSize)
        
    def lookAround(self) :
        self.maze[self.curX][self.curY].top = self.truth[self.curX][self.curY].top
        self.maze[self.curX][self.curY].bot = self.truth[self.curX][self.curY].bot
        self.maze[self.curX][self.curY].right = self.truth[self.curX][self.curY].right
        self.maze[self.curX][self.curY].left = self.truth[self.curX][self.curY].left
        self.maze[self.curX][self.curY].drawCell(self.c)
        
        if (self.curY < Maze.h - 1) :
            self.maze[self.curX][self.curY + 1].top = self.truth[self.curX][self.curY + 1].top
            self.maze[self.curX][self.curY + 1].drawCell(self.c)

        if (self.curY > 0) :
            self.maze[self.curX][self.curY - 1].bot = self.truth[self.curX][self.curY - 1].bot
            self.maze[self.curX][self.curY - 1].drawCell(self.c)
            
        if (self.curX > 0) :
            self.maze[self.curX - 1][self.curY].right = self.truth[self.curY][self.curX - 1].right
            self.maze[self.curX - 1][self.curY].drawCell(self.c)

        if (self.curX < Maze.w - 1) :
            self.maze[self.curX + 1][self.curY].left = self.truth[self.curX + 1][self.curY].left
            self.maze[self.curX + 1][self.curY].drawCell(self.c)
        

    def animateMaze(self, lod) :
        self.lookAround()
        self.drawMaze()
        self.animateMazeHelp(lod, 0)

    def animateMazeHelp(self, lod, i):
        if (i < len(lod)) :
            self.updateMaze(lod[i])
            self.c.update()
            self.c.after(Maze.animationSpeed, self.animateMazeHelp, lod, (i + 1))

    def instantMaze(self, lod) :
        i = 0
        self.lookAround()
        while (i < len(lod)) :
            oldX = self.curX
            oldY = self.curY
            if (lod[i] == "up") :
                self.curY = self.curY - 1
            elif (lod[i] == "down") :
                self.curY = self.curY + 1
            elif (lod[i] == "left") :
                self.curX = self.curX - 1
            elif (lod[i] == "right") :
                self.curX = self.curX + 1
            self.lookAround()
            i = i + 1

        self.drawMaze()
        self.c.move(self.pos,
            (self.curX) * Cell.cellSize,
            (self.curY) * Cell.cellSize)

    @staticmethod
    def getCoord(coordNum):
        return (2 * coordNum) + 1;

    @staticmethod
    def readMaze():
        truth = [[Cell(x, y) for y in range(Maze.w)] for x in range(Maze.h)]
        
        with open("maze.txt") as f:
            content = f.read()

        content = content.split()

        for j in range(0, Maze.h):
            for i in range(0, Maze.w):
                if (content[i*4 + j*Maze.h * 4] == "space") :
                    (truth[i][j]).top = "space";
                else :
                    (truth[i][j]).top = "wall";
    
                if (content[i*4+1 + j*Maze.h * 4] == "space") :
                    (truth[i][j]).bot = "space";
                else :
                    (truth[i][j]).bot = "wall";

                if (content[i*4+2 + j*Maze.h * 4] == "space") :
                    (truth[i][j].left) = "space";
                else :
                    (truth[i][j]).left = "wall";

                if (content[i*4+3 + j*Maze.h * 4] == "space") :
                    (truth[i][j].right) = "space";
                else :
                    (truth[i][j]).right = "wall";

        return truth


# How to use simulator:
#     1) Create tkinter and Canvas objects
#     2) Create Maze object using the Canvas object
#     3) Call Canvas.pack()
#     4) Use animateMaze(dirs) where dirs is the list of directions
#        you traverse through (instantMaze will show which cells were viewed without
#        the animation)
#     5) Run gui.mainloop()


def main():
    gui = tkinter.Tk()

    c = Canvas(gui, bg="white",
               height=Cell.cellSize * Maze.h + 2 * Cell.bufferSize,
               width=Cell.cellSize * Maze.w + 2 * Cell.bufferSize)

    m = Maze(c)
    
    c.pack()

    dirs = ["down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right",
            "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right",
            "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right",
            "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right",
            "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right",
            "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right",
            "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "right",
            "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "down", "right",
            "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up", "up"]
    
    m.animateMaze(dirs)

    gui.mainloop()
    
main()
