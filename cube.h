#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <set>
#include <cstdint>
#include <string>
#include <vector>

// Cube state in the given orientation. When you rotate the faces it is done relative to this orientation. 
// When you rotate the entire cube the face contents are preserved but the order is shuffled.

enum Color {
    WHITE = 1,
    YELLOW = 2,
    RED = 4,
    ORANGE = 8,
    BLUE = 16,
    GREEN = 32,
    BLACK = 0
};
class CubeState {
    public:
    Color FRONT[3][3];
    Color LEFT[3][3];
    Color RIGHT[3][3];
    Color UP[3][3];
    Color DOWN[3][3];
    Color BACK[3][3];
    
    int ex[4] = {00, 01, 02, 01};
    int ey[4] = {01, 02, 01, 00};
    
    int cx[4] = {00, 00, 02, 02};
    int cy[4] = {00, 02, 02, 00};
    
    std::vector<bool> edges(Color face[3][3], Color c) {
        std::vector<bool> res = {false, false, false, false};
        for (int i = 0; i < 4; i++) {
            if (face[ex[i]][ey[i]] == c) res[i] = true;
        }
        return res;
    }
    
    std::vector<bool> corners(Color face[3][3], Color c) {
        std::vector<bool> res = {false, false, false, false};
        for (int i = 0; i < 4; i++) {
            if (face[cx[i]][cy[i]] == c) res[i] = true;
        }
        return res;
    }
    
    char colchar(Color c) {
        Color cs[7] = {WHITE, YELLOW, RED, ORANGE, BLUE, GREEN, BLACK};
        char ch[7] = {'W', 'Y', 'R', 'O', 'B', 'G', '.'};
        for (int i = 0; i < 7; i++) {
            if (c == cs[i]) return ch[i];
        }
        return '?';
    }
    
    
    CubeState() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                UP[i][j] = WHITE;
                FRONT[i][j] = GREEN;
                RIGHT[i][j] = RED;
                DOWN[i][j] = YELLOW;
                BACK[i][j] = BLUE;
                LEFT[i][j] = ORANGE;
            }
        }
    }
    
    CubeState(const CubeState& other) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                UP[i][j] = other.UP[i][j];
                FRONT[i][j] = other.FRONT[i][j];
                RIGHT[i][j] = other.RIGHT[i][j];
                DOWN[i][j] = other.DOWN[i][j];
                BACK[i][j] = other.BACK[i][j];
                LEFT[i][j] = other.LEFT[i][j];
            }
        }
    }
    
    // COORDINATE SYSTEM - The X axis is the first index and the Y axis the second.
    // For the front and back faces, (0, 0) is the bottom left. The X axis goes to the right and the Y axis goes up.
    // For the left and right faces, (0, 0) is bottom front. The X axis goes behind and the Y axis up.
    // For the top and bottom faces, (0, 0) is the left front. The X axis goes right and the Y axis back.
    // Essentially we are aligning axes to the 3-dimensional axes of the cube itself.
    
    // Cube Rotations. The axes are a bit different - right handed Y up. Think Minecraft.
    // All rotations are clockwise relative to the positive side/face.
    
    // Rotates an array clockwise, assuming the X axis goes right and the Y axis goes up.
    void clockwise(Color (&x)[3][3]) {
        Color temp = x[0][0];
        x[0][0] = x[2][0];
        x[2][0] = x[2][2];
        x[2][2] = x[0][2];
        x[0][2] = temp;
        
        temp = x[0][1];
        x[0][1] = x[1][0];
        x[1][0] = x[2][1];
        x[2][1] = x[1][2];
        x[1][2] = temp;
    }
    
    void counterclockwise(Color (&x)[3][3]) {
        clockwise(x);
        clockwise(x);
        clockwise(x);
    }
    
    // The two faces normal to the rotation axis are rotated directly. 
    // However since the axes are reversed for one of them both faces technically rotate in the same direction.
    
    void X() {
        clockwise(RIGHT);
        clockwise(LEFT);
        
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                Color temp = FRONT[x][y];
                
                FRONT[x][y] = DOWN[x][2 - y];
                DOWN[x][2 - y] = BACK[x][2 - y];
                BACK[x][2 - y] = UP[x][y];
                UP[x][y] = temp;
            }
        }
    }
    
    void Y() {
        clockwise(UP);
        clockwise(DOWN);
        
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                Color temp = FRONT[x][y];
                
                FRONT[x][y] = RIGHT[x][y];
                RIGHT[x][y] = BACK[2 - x][y];
                BACK[2 - x][y] = LEFT[2 - x][y];
                LEFT[2 - x][y] = temp;
            }
        }
    }
    
    void Z() {
        clockwise(FRONT);
        clockwise(BACK);
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                Color temp = UP[x][y];
                
                UP[x][y] = LEFT[y][x];
                LEFT[y][x] = DOWN[2 - x][y];
                DOWN[2 - x][y] = RIGHT[y][2 - x];
                RIGHT[y][2 - x] = temp;
            }
        }
    }
    
    // Face rotations. Each face is rotated clockwise relative to looking at the face from the outside. (This means faces such as back are rotated inversely.)
    // Pieces on adjacent sides are also rotated
    
    void F() {
        clockwise(FRONT);
        for (int x = 0; x < 3; x++) {
            int y = 0;
            Color temp = UP[x][y];
                
            UP[x][y] = LEFT[y][x];
            LEFT[y][x] = DOWN[2 - x][y];
            DOWN[2 - x][y] = RIGHT[y][2 - x];
            RIGHT[y][2 - x] = temp;
        }
    }
    
    void B() {
        counterclockwise(BACK);
        for (int x = 0; x < 3; x++) {
            int y = 2;
            Color temp = UP[x][y];
            
            UP[x][y] = RIGHT[y][2 - x];
            RIGHT[y][2 - x] = DOWN[2 - x][y];
            DOWN[2 - x][y] = LEFT[y][x];
            LEFT[y][x] = temp;
        }
    }
    
    void U() {
        clockwise(UP);
        for (int x = 0; x < 3; x++) {
            int y = 2;
            Color temp = FRONT[x][y];
            
            FRONT[x][y] = RIGHT[x][y];
            RIGHT[x][y] = BACK[2 - x][y];
            BACK[2 - x][y] = LEFT[2 - x][y];
            LEFT[2 - x][y] = temp;
        }
    }
    
    void D() {
        counterclockwise(DOWN);
        for (int x = 0; x < 3; x++) {
            int y = 0;
            Color temp = FRONT[x][y];
            FRONT[x][y] = LEFT[2 - x][y];
            LEFT[2 - x][y] = BACK[2 - x][y];
            BACK[2 - x][y] = RIGHT[x][y];
            RIGHT[x][y] = temp;
        }
    }
    
    void R() {
        clockwise(RIGHT);
        for (int y = 0; y < 3; y++) {
            int x = 2;
            Color temp = FRONT[x][y];
                
            FRONT[x][y] = DOWN[x][2 - y];
            DOWN[x][2 - y] = BACK[x][2 - y];
            BACK[x][2 - y] = UP[x][y];
            UP[x][y] = temp;
        }
    }
    
    void L() {
        counterclockwise(LEFT);
        for (int y = 0; y < 3; y++) {
            int x = 0;
            Color temp = FRONT[x][y];
                
            FRONT[x][y] = UP[x][y];
            UP[x][y] = BACK[x][2 - y];
            BACK[x][2 - y] = DOWN[x][2 - y];
            DOWN[x][2 - y] = temp;
        }
    }
    
    std::string toString() {
        std::string res = "";
        for (int y = 0; y < 3; y++) {
            res = res + "    ";
            for (int x = 0; x < 3; x++) res = res + colchar(UP[x][2 - y]);
            res = res + "\n";
        }
        res = res + "\n";
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) res = res + colchar(LEFT[2 - x][2 - y]);
            res = res + " ";
            for (int x = 0; x < 3; x++) res = res + colchar(FRONT[x][2 - y]);
            res = res + " ";
            for (int x = 0; x < 3; x++) res = res + colchar(RIGHT[x][2 - y]);
            res = res + " ";
            for (int x = 0; x < 3; x++) res = res + colchar(BACK[2 - x][2 - y]);
            res = res + "\n";
        }
        res = res + "\n";
        for (int y = 0; y < 3; y++) {
            res = res + "    ";
            for (int x = 0; x < 3; x++) res = res + colchar(DOWN[x][y]);
            res = res + "\n";
        }
        return res;
    }
    
    void disp() {
        std::cout << toString() << "\n";
    }
    
    bool isSolved() {
        std::set<Color> faces;
        
        faces.clear();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) faces.insert(FRONT[i][j]);
        }
        if (faces.size() != 1) return false;
        
        faces.clear();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) faces.insert(LEFT[i][j]);
        }
        if (faces.size() != 1) return false;
        
        faces.clear();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) faces.insert(UP[i][j]);
        }
        if (faces.size() != 1) return false;
        
        faces.clear();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) faces.insert(BACK[i][j]);
        }
        if (faces.size() != 1) return false;
        
        faces.clear();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) faces.insert(RIGHT[i][j]);
        }
        if (faces.size() != 1) return false;
        
        faces.clear();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) faces.insert(DOWN[i][j]);
        }
        if (faces.size() != 1) return false;
        return true;
    }
    
    int randr(int x) {
        double bleep = (double)(rand()) / (double)(RAND_MAX);
        return (int)(bleep * x);
    }
    
    void scramble(int moves = 256) {
        for (int i = 0; i < moves; i++) {
            int beep = randr(9);
            if (beep == 0) F();
            if (beep == 1) R();
            if (beep == 2) U();
            if (beep == 3) B();
            if (beep == 4) L();
            if (beep == 5) D();
            if (beep == 6) X();
            if (beep == 7) Y();
            if (beep == 8) Z();
        }
    }
};

#endif