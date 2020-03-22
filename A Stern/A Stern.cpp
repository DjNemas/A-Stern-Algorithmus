#include <iostream>
#include <windows.h>

using namespace std;

int start_x = 0;
int start_y = 0;
int goal_x = 0;
int goal_y = 0;

///Init and Delete Game Field
//
char*** Init_GameField(int grafik_buffer, int game_field_height, int game_field_width);
void Delete_GameField(char*** game_field_array, int grafik_buffer, int game_field_height);

/// Buffer Funktions
//
int Set_Buffer_0(int grafik_buffer);
int Set_Buffer_1(int grafik_buffer);
int Switch_Buffer(int grafik_buffer);
void Copy_Display_Buffer(char*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width);
/// Show Field
//
void Draw_Field(char*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width);
void Show_GameField(string game_field, char*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width, bool show_buffer);

/// User Inputs
//
int User_GameField_Height(int game_field_height);
int User_GameField_Width(int game_field_width);

/// Caluculation Distance
//
double Calculate_Accurate(int start_x,int start_y, int check_field_x, int check_field_y);
double Calculate_Estimat(int check_field_x, int check_field_y);
void Calculate_Closest_Field(char*** game_field_array, int grafik_buffer, bool show_distance);
int main()
{
    int grafik_buffer = 2;
    int game_field_height = 10;
    int game_field_width = 20;
    string game_field;
    /// User Inputs
    //
    game_field_height = User_GameField_Height(game_field_height);
    game_field_width = User_GameField_Width(game_field_width);

    ///Init Game Field and Fill
    //
    char*** game_field_array = Init_GameField(grafik_buffer, game_field_height, game_field_width);
    Draw_Field(game_field_array,grafik_buffer,game_field_height,game_field_width);
    /// Show Map Ones
    grafik_buffer = Set_Buffer_0(grafik_buffer);
    Show_GameField(game_field,game_field_array, grafik_buffer, game_field_height, game_field_width, false);
    /// Game Start
    // 
    while (start_x != goal_x || start_y != goal_y)
    {
        Calculate_Closest_Field(game_field_array, grafik_buffer, false);
        Copy_Display_Buffer(game_field_array, grafik_buffer, game_field_height, game_field_width);
        grafik_buffer = Switch_Buffer(grafik_buffer);
        Show_GameField(game_field, game_field_array, grafik_buffer, game_field_height, game_field_width, false);
    };

    char test = ' ';
    cin >> test;

    Delete_GameField(game_field_array, 2, game_field_height);

}
///Init and Delete Game Field
//
char*** Init_GameField(int grafik_buffer, int game_field_height, int game_field_width)
{
    char*** game_Field = new char** [grafik_buffer];
    for (int i = 0; i < grafik_buffer; i++)
    {
        game_Field[i] = new char*[game_field_height];
        for (int j = 0; j < game_field_height; j++)
        {
            game_Field[i][j] = new char[game_field_width];
        }
    }
    return game_Field;
}

void Delete_GameField(char*** game_field_array, int grafik_buffer, int game_field_height)
{
    for (int i = 0; i < grafik_buffer; i++)
    {
        for (int j = 0; j < game_field_height; j++)
        {
            delete[] game_field_array[i][j];
        }
        delete game_field_array[i];
    }
    delete game_field_array;
}

/// Show Field
//
void Show_GameField(string game_field, char*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width, bool show_buffer)
{
    system("CLS");
    if (show_buffer == true)
    {
        if (grafik_buffer == 0)
        {
            cout << "Grafikbuffer 0" << endl;
        }
        if (grafik_buffer == 1)
        {
            cout << "Grafikbuffer 1" << endl;
        }
    }

    for (int i = 0; i < game_field_height; i++)
    {
        for (int j = 0; j < game_field_width; j++)
        {
            if (grafik_buffer == 0)
            {
                game_field += game_field_array[0][i][j];
            }
            else if (grafik_buffer == 1)
            {
                game_field += game_field_array[1][i][j];
            }
            
        }
        game_field += "\n";
    }
    
    cout << game_field;
    Sleep(10);
}

void Draw_Field(char*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width)
{
    int rnd = 0;
    for (int i = 0; i < game_field_height; i++)
    {
        for (int j = 0; j < game_field_width; j++)
        {
            rnd = rand() % 1000;
            if (i == 0 || i == game_field_height - 1)
            {
                game_field_array[0][i][j] = '#';
                game_field_array[1][i][j] = '#';
            }
            else if (j == 0 || j == game_field_width - 1)
            {
                game_field_array[0][i][j] = '#';
                game_field_array[1][i][j] = '#';
            }
            else if (rnd < 200)
            {
                game_field_array[0][i][j] = '#';
                game_field_array[1][i][j] = '#';
            }
            else
            {
                game_field_array[0][i][j] = '-';
                game_field_array[1][i][j] = '-';
            }
            
        }
        
    }
    
    start_x = rand() % (game_field_height - 2) + 1;
    start_y = rand() % (game_field_width - 2) + 1;
    game_field_array[0][start_x][start_y] = '1';
    game_field_array[1][start_x][start_y] = '1';
    goal_x = rand() % (game_field_height - 2) + 1;
    goal_y = rand() % (game_field_width - 2) + 1;
    game_field_array[0][goal_x][goal_y] = '2';
    game_field_array[1][goal_x][goal_y] = '2';
    
}
/// Buffer Funktions
//
int Set_Buffer_0(int grafik_buffer)
{
   
    if (grafik_buffer == 2 || grafik_buffer == 1)
    {
        grafik_buffer = 0;
    }
    return grafik_buffer;
}
int Set_Buffer_1(int grafik_buffer)
{
    if (grafik_buffer == 2 || grafik_buffer == 0)
    {
        grafik_buffer = 1;
    }
    return grafik_buffer;
}
int Switch_Buffer(int grafik_buffer)
{
    if (grafik_buffer == 1)
    {
        grafik_buffer = 0;
    }
    else if (grafik_buffer == 0)
    {
        grafik_buffer = 1;
    }
    return grafik_buffer;
}

/// User Inputs
//
int User_GameField_Height(int game_field_height)
{
    cout << "Bitte w\x84hle die Map H\x94he: ";
    cin >> game_field_height;
    cout << endl;
    return game_field_height;
}

int User_GameField_Width(int game_field_width)
{
    cout << "Bitte w\x84hle die Map Breite: ";
    cin >> game_field_width;
    cout << endl;
    return game_field_width;
}

/// Calculate Distance
//
double Calculate_Accurate(int start_x, int start_y, int check_field_x, int check_field_y)
{
    double accurate_x = 0;
    double accurate_y = 0;
    double accurate = 0;

    accurate_x = pow(start_x - check_field_x, 2);
    accurate_y = pow(start_y - check_field_y, 2);
    if (accurate_x < 0)
    {
        accurate_x *= -1;
    }
    if (accurate_y < 0)
    {
        accurate_y *= -1;
    }
    return accurate = sqrt(accurate_x + accurate_y);

}

double Calculate_Estimat(int check_field_x, int check_field_y)
{
    double estimat = 0;
    double estimat_x = 0;
    double estimat_y = 0;

    estimat_x = pow(check_field_x - goal_x, 2);
    estimat_y = pow(check_field_y - goal_y, 2);
    if (estimat_x < 0)
    {
        estimat_x *= -1;
    }
    if (estimat_y < 0)
    {
        estimat_y *= -1;
    }
    return estimat = sqrt(estimat_x + estimat_y);
}

void Calculate_Closest_Field(char*** game_field_array,int grafik_buffer,bool show_calculation)
{
    double accurate_distance = 0;
    double estimat_distance = 0;
    double sum_distance = 0;
    double count[8] = {0,0,0,0,0,0,0,0};
    double min = 999999;
    if (game_field_array[grafik_buffer][start_x - 1][start_y - 1] == '#')
    {
        count[0] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x - 1, start_y - 1);
        estimat_distance = Calculate_Estimat(start_x - 1, start_y - 1);
        sum_distance = accurate_distance + estimat_distance;
        count[0] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x - 1][start_y] == '#')
    {
        count[1] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 1 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x - 1, start_y);
        estimat_distance = Calculate_Estimat(start_x - 1, start_y);
        sum_distance = accurate_distance + estimat_distance;
        count[1] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 1 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x - 1][start_y + 1] == '#')
    {
        count[2] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 2 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x - 1, start_y + 1);
        estimat_distance = Calculate_Estimat(start_x - 1, start_y + 1);
        sum_distance = accurate_distance + estimat_distance;
        count[2] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 2 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x][start_y - 1] == '#')
    {
        count[3] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x, start_y - 1);
        estimat_distance = Calculate_Estimat(start_x, start_y - 1);
        sum_distance = accurate_distance + estimat_distance;
        count[3] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x][start_y + 1] == '#')
    {
        count[4] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y + 2 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x, start_y + 1);
        estimat_distance = Calculate_Estimat(start_x, start_y + 1);
        sum_distance = accurate_distance + estimat_distance;
        count[4] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y + 2 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x + 1][start_y - 1] == '#')
    {
        count[5] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x + 1, start_y - 1);
        estimat_distance = Calculate_Estimat(start_x + 1, start_y - 1);
        sum_distance = accurate_distance + estimat_distance;
        count[5] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x + 1][start_y] == '#')
    {
        count[6] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 1 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x + 1, start_y);
        estimat_distance = Calculate_Estimat(start_x + 1, start_y);
        sum_distance = accurate_distance + estimat_distance;
        count[6] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 1 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x + 1][start_y + 1] == '#')
    {
        count[7] = 999999;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 2 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        accurate_distance = Calculate_Accurate(start_x, start_y, start_x + 1, start_y + 1);
        estimat_distance = Calculate_Estimat(start_x + 1, start_y + 1);
        sum_distance = accurate_distance + estimat_distance;
        count[7] = sum_distance;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 2 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        if (count[i] < min)
        {
            min = count[i];
        }
    }    
  
        if (min == count[0])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x - 1][start_y - 1] = '0';
                start_x -= 1;
                start_y -= 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x - 1][start_y - 1] = '0';
                start_x -= 1;
                start_y -= 1;
            }
        }
        else if (min == count[1])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x - 1][start_y] = '0';
                start_x -= 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x - 1][start_y] = '0';
                start_x -= 1;
            }
        }
        else if (min == count[2])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x - 1][start_y + 1] = '0';
                start_x -= 1;
                start_y += 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x - 1][start_y + 1] = '0';
                start_x -= 1;
                start_y += 1;
            }
        }
        else if (min == count[3])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x][start_y - 1] = '0';
                start_y -= 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x][start_y - 1] = '0';
                start_y -= 1;
            }
        }
        else if (min == count[4])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x][start_y + 1] = '0';
                start_y += 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x][start_y + 1] = '0';
                start_y += 1;
            }
        }
        else if (min == count[5])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x + 1][start_y - 1] = '0';
                start_x += 1;
                start_y -= 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x + 1][start_y - 1] = '0';
                start_x += 1;
                start_y -= 1;
            }
        }
        else if (min == count[6])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x + 1][start_y] = '0';
                start_x += 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x + 1][start_y] = '0';
                start_x += 1;
            }
        }
        else if (min == count[7])
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][start_x + 1][start_y + 1] = '0';
                start_x += 1;
                start_y += 1;
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][start_x + 1][start_y + 1] = '0';
                start_x += 1;
                start_y += 1;
            }
        }
        if (start_x == goal_x && start_y == goal_y)
        {
            if (grafik_buffer == 0)
            {
                game_field_array[1][goal_x][goal_y] = '2';
            }
            else if (grafik_buffer == 1)
            {
                game_field_array[0][goal_x][goal_y] = '2';
            }
        }
}

void Copy_Display_Buffer(char*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width)
{
    if (grafik_buffer == 0)
    {
        for (int i = 0; i < game_field_height; i++)
        {
            for (int j = 0; j < game_field_width; j++)
            {
                game_field_array[0][i][j] = game_field_array[1][i][j];
            }
        }
    }
    else if ((grafik_buffer == 1))
    {
        for (int i = 0; i < game_field_height; i++)
        {
            for (int j = 0; j < game_field_width; j++)
            {
                game_field_array[1][i][j] = game_field_array[0][i][j];
            }
        }
    }
}