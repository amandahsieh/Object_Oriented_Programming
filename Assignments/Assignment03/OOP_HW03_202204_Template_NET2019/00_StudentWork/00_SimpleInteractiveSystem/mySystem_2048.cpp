//********************************************
// Student Name			:¸Ñ¤ß§±
// Student ID			:110550146
// Student Email Address:amandahsieh.926188.cs10@nycu.edu.tw
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    mNX = nx;
    mNZ = nz;
    if (mNX > MAX_2048_NX)   mNX = MAX_2048_NX;
    if (mNZ > MAX_2048_NZ)   mNZ = MAX_2048_NZ;
    //
    // Implement your own stuff
    //
}


void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious( const BASE_SYSTEM *m ){
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[j][i] = ((MY_2048*)m)->mPreviousBoard[ j ][ i ];
        }
    }
}

void MY_2048::Previous(const BASE_SYSTEM* m) {
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            ((MY_2048*)m)->mPreviousBoard[j][i] = mBoard[j][i];
        }
    }
}


//
//reset the game board
//
void MY_2048::reset( )
{
    mEvent = 0;
    for (int i = 0; i < mNZ; i++) {
        for (int j = 0; j < mNX; j++) {
            mBoard[j][i] = 0;
        }
    }
    for (int i = 0; i < mNZ; i++) {
        for (int j = 0; j < mNX; j++) {
            mPreviousBoard[j][i] = 0;
        }
    }
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "r: clear all the cells" << endl;
    cout << " " << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;

}

//
// randomly generate a new number
//
int MY_2048::f() {
    int ff = 1;
    for (int i = 0; i < this->mNX; i++) {
        for (int j = 0; j < this->mNZ; j++) {
            if (this->mBoard[j][i] == 0) {
                ff = 0;
                break;
            }
        }
    }
    return ff;
}
void MY_2048::generateNumber( )
{
    if (this->f() == 1) {
        flg_AutoPlay = 0;
        return;
    }
    bool finish = 0;
    while (!finish) {
        int x = rand() % mNX;
        int z = rand() % mNZ;
        if (mBoard[z][x] == 0) {
            mBoard[z][x] = 2 * (1 + (rand() % 2));
            finish = 1;
        }
    }
    //
    // Implement your own stuff
    //
}

void MY_2048::moveDown( )
{
    Previous(this);
    for (int x = 0; x < mNX; x++) {
        int num = 0;
        for (int z = mNZ - 1; z >= 0; z--) {
            if (mBoard[z][x] != 0) {
                //if (z == mNZ - num) continue;
                if (mBoard[z][x] == mBoard[mNZ - num][x] && z!=mNZ-num &&num>0) {
                    mBoard[mNZ - num][x] *= 2;
                    mBoard[z][x] = 0;
                }
                else {
                    num = num + 1;
                    int tmp = mBoard[z][x];
                    mBoard[z][x] = 0;
                    mBoard[mNZ - num][x] = tmp;
                }
            }
        }
    }

}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
    Previous(this);
    for (int x = 0; x < mNX; x++) {
        int num = -1;
        for (int z = 0; z <mNZ ; z++) {
            //if (z == num) continue;
            if (mBoard[z][x] != 0) {
                if (mBoard[z][x] == mBoard[num][x] && num!=z && num>=0) {
                    mBoard[z][x] = 0;
                    mBoard[num][x] *= 2;
                }
                else {
                    num = num + 1;
                    int tmp = mBoard[z][x];
                    mBoard[z][x] = 0;
                    mBoard[num][x] = tmp;
                }
            }
        }
    }
}

void MY_2048::moveLeft( )
{
    Previous(this);
    for (int z = 0; z < mNZ; z++) {
        int num = -1;
        for (int x = 0; x <mNX; x++) {
            if (mBoard[z][x] != 0) {
                if (mBoard[z][x] == mBoard[z][num] && x!=num && num>=0) {
                    mBoard[z][x] = 0;
                    mBoard[z][num] *= 2;
                }
                else {
                    num = num + 1;
                    int tmp = mBoard[z][x];
                    mBoard[z][x] = 0;
                    mBoard[z][num] = tmp;
                }
            }
        }
    }
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
    Previous(this);
    for (int z = 0; z < mNZ; z++) {
        int num = 0;
        for (int x = mNX - 1; x >= 0; x--) {
            if (mBoard[z][x] != 0) {
                if (mBoard[z][x] == mBoard[z][mNX-num] && num>0 && x!=mNX-num) {
                    mBoard[z][x] = 0;
                    mBoard[z][mNX-num] *= 2;
                }
                else {
                    num = num + 1;
                    int tmp = mBoard[z][x];
                    mBoard[z][x] = 0;
                    mBoard[z][mNX-num] = tmp;   
                }
            }
        }
    }
}

void MY_2048::generateNumbers_All_2to4( )
{
    for (int i = 0; i < mNZ; i++) {
        for (int j = 0; j < mNX; j++) {
            mBoard[i][j] = pow(2, (1 + (rand() % 2)));
        }
    }
    //
    // Implement your own stuff
    //
}

void MY_2048::generateNumbers_All_2to8( )
{
    for (int i = 0; i < mNZ; i++) {
        for (int j = 0; j < mNX; j++) {
            mBoard[i][j] = pow(2, (1 + (rand() % 3)));
        }
    }
    //
    // Implement your own stuff
    //
}

void MY_2048::generateNumbers_All( )
{
    for (int i = 0; i < mNZ; i++) {
        for (int j = 0; j < mNX; j++) {
            mBoard[i][j] = pow(2, (1 + (rand() % 10)));
        }
    }
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;

    case 'a':
    case 'A':
        flg_AutoPlay;
        break;
    case ' ':
        // toggle to auto-play
        flg_AutoPlay = !flg_AutoPlay;
        break;
    }
}

void MY_2048::performAction( unsigned char key ) {
bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;

        break;

    }

    if ( flgDone ) {
        generateNumber( );
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction( key );
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//



void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;

    if (!flg_AutoPlay) return;
    int bestmove = 0;
    bestmove = getBestAction(this, 5);
    switch (bestmove) {
    case 1:
        performAction(GLUT_KEY_UP);
        mEvent = GLUT_KEY_UP;
        break;
    case 0:
        performAction(GLUT_KEY_DOWN);
        mEvent = GLUT_KEY_DOWN;
        break;

    case 2:
        performAction(GLUT_KEY_LEFT);
        mEvent = GLUT_KEY_LEFT;
        break;

    case 3:
        performAction(GLUT_KEY_RIGHT);
        mEvent = GLUT_KEY_RIGHT;
        break;
    }
    //
    // Implement your own stuff
    //
}

int MY_2048::getBestAction(MY_2048* board, int d) {
    int bestscore = 1;
    int bestAction = 0;
    if (d == 0)   return bestAction;
    for (int a = 0; a < 4; a++) {
        MY_2048* tmp = trying(board, a);
        int score = performAction_Recur(a, tmp,d-1);
        if (score > bestscore) {
            bestscore = score;
            bestAction = a;
        }
    }
    return bestAction;
}

int MY_2048::performAction_Recur(int a, MY_2048* tmp, int d) {
    int score = -5;
    int bestScore = -5;
    if (d == 0) {
        score = evaluate(tmp);
        return score;
    }
    for (int a = 0; a < 4; a++) {
        MY_2048* temp = trying(tmp, a);
        score = performAction_Recur(a, temp, d - 1);
        if (score > bestScore) {
            bestScore = score;
        }
    }
    return score;
}

int MY_2048::evaluate(MY_2048* e) {
    int cnt = 0;
    for (int i = 0; i < e->mNX; i++) {
        for (int j = 0; j < e->mNZ; j++) {
            if (e->mBoard[j][i] == 0)    cnt++;
        }
    }
    return cnt;
}

MY_2048* MY_2048::trying(MY_2048* board, int a) {
    MY_2048* tmp = board;
    switch (a) {
    case 0:
        board->moveUp();
        break;
    case 1:
        board->moveDown();
        break;
    case 2:
        board->moveLeft();
        break;
    case 3:
        board->moveRight();
        break;
    }
    return board;
}