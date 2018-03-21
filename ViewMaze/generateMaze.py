import random

import tkinter
from tkinter import *
import time
import random

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

    def __init__(self, truth, can):
        self.curX = 0
        self.curY = 0
        self.maze = [[Cell(x, y) for x in range(Maze.w)] for y in range(Maze.h)]
        self.truth = truth

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
        self.maze[self.curY][self.curX].top = self.truth[self.curY][self.curX].top
        self.maze[self.curY][self.curX].bot = self.truth[self.curY][self.curX].bot
        self.maze[self.curY][self.curX].right = self.truth[self.curY][self.curX].right
        self.maze[self.curY][self.curX].left = self.truth[self.curY][self.curX].left
        self.maze[self.curY][self.curX].drawCell(self.c)

        if (self.curY < Maze.h - 1) :
            self.maze[self.curY + 1][self.curX].top = self.truth[self.curY + 1][self.curX].top
            self.maze[self.curY + 1][self.curX].drawCell(self.c)

        if (self.curY > 0) :
            self.maze[self.curY - 1][self.curX].bot = self.truth[self.curY - 1][self.curX].bot
            self.maze[self.curY - 1][self.curX].drawCell(self.c)

        if (self.curX > 0) :
            self.maze[self.curY][self.curX - 1].right = self.truth[self.curY][self.curX - 1].right
            self.maze[self.curY][self.curX - 1].drawCell(self.c)

        if (self.curX < Maze.w - 1) :
            self.maze[self.curY][self.curX + 1].left = self.truth[self.curY][self.curX + 1].left
            self.maze[self.curY][self.curX + 1].drawCell(self.c)


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
        truth = [[Cell(x, y) for x in range(Maze.w)] for y in range(Maze.h)]

        with open("C:\\Users\\Justin\\Documents\\Micromouse\\maze.txt") as f:
            content = f.readlines()

        for i in range(0, Maze.w):
            for j in range(0, Maze.h):
                if (content[Maze.getCoord(i) + 1][Maze.getCoord(j)] != '#') :
                    (truth[i][j]).bot = "space";
                else :
                    (truth[i][j]).bot = "wall";

                if (content[Maze.getCoord(i) - 1][Maze.getCoord(j)] != '#') :
                    (truth[i][j]).top = "space";
                else :
                    (truth[i][j]).top = "wall";

                if (content[Maze.getCoord(i)][Maze.getCoord(j) - 1] != '#') :
                    (truth[i][j].left) = "space";
                else :
                    (truth[i][j]).left = "wall";

                if (content[Maze.getCoord(i)][Maze.getCoord(j) + 1] != '#') :
                    (truth[i][j].right) = "space";
                else :
                    (truth[i][j]).right = "wall";

        return truth


class Vertex:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Edge:
    def __init__(self, v1, v2):
        self.e = set([v1, v2])
        self.weight = random.randint(1, 100)

    def __lt__(self, other):
        return self.weight < other.weight

class MST:
    Size = 16 

    def __init__(self):
        maze = []
        for x in range(0, MST.Size):
            col = []
            for y in range(0, MST.Size):
                col.append(Vertex(x, y))
            maze.append(col);

        edges = []
        for x in range(0, MST.Size - 1):
            for y in range(0, MST.Size):
                edges.append(Edge(maze[x][y], maze[x+1][y]))

        for x in range(0, MST.Size):
            for y in range(0, MST.Size - 1):
                edges.append(Edge(maze[x][y], maze[x][y+1]))

        edges.sort()

        connectedVertices = set([maze[0][0]])
        self.mst = set()
        rmEdge = 0

        while len(connectedVertices) != MST.Size * MST.Size:
            for e in edges:
                if (len(connectedVertices.intersection(e.e)) == 1):
                    self.mst.add(e)
                    connectedVertices = connectedVertices.union(e.e)
                    rmEdge = e
                    break
            edges.remove(rmEdge)

    # Why reverse y and x???
    def convertToMaze(self):
        maze = [[Cell(x, y, "wall", "wall", "wall", "wall")
                 for x in range(MST.Size)] for y in range(MST.Size)]

        for e in self.mst:
            l = list(e.e)
            if (l[0].x == l[1].x):
                if (l[0].y > l[1].y):
                    maze[l[0].x][l[0].y].top = "space"
                    maze[l[1].x][l[1].y].bot = "space"
                else:
                    maze[l[0].x][l[0].y].bot = "space"
                    maze[l[1].x][l[1].y].top = "space"
            else:
                if (l[0].x > l[1].x):
                    maze[l[0].x][l[0].y].left = "space"
                    maze[l[1].x][l[1].y].right = "space"
                else:
                    maze[l[0].x][l[0].y].right = "space"
                    maze[l[1].x][l[1].y].left = "space"

        return maze


    def export(self):
        maze = self.convertToMaze()
        fh = open("maze.txt", "w+")
        for y in range(0, MST.Size):
            for x in range(0, MST.Size):
                fh.write(maze[x][y].top + " ")
                fh.write(maze[x][y].bot + " ")
                fh.write(maze[x][y].left + " ")
                fh.write(maze[x][y].right + " ")
        fh.close()

def main():
    MST().export()

main()
