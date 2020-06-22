#include <iostream>

using namespace std;

void bright(int row, int col)
{
    int arr[4][4] = {
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
        {12,13,14,15}
    };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (row < 0 || row > 3)
                break;
            else if (col < 0 || col > 3)
                break;

            if (arr[i][j] == arr[row][col])
            {
                cout << arr[i][j] << " ";
            }
        }
    }
}

void pattern(int but)
{
    int row, col;
    int arr[4][4] = {
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
        {12,13,14,15}
    };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (arr[i][j] == but)
            {
                row = i;
                col = j;
            }
        }
    }

    for(int j = 0; j < 4; j++)
    {
        if (j == 0)
        {
            cout << "P ";
            bright(row, col);
            cout << endl;
        } else {
            cout << "A ";
            bright(row, col+j);
            cout << "B ";
            bright(row, col-j);
            cout << "C ";
            bright(row+j, col);
            cout << "D ";
            bright(row-j, col);
            cout << endl;
        }
    }
}


int main()
{
    int num;


    while(1)
    {
        cout << "Enter : ";
        cin >> num;

        pattern(num);
    }

    return 0;
}