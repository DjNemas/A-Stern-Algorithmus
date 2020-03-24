#include <iostream>
#include <windows.h>


using namespace std;


////////////////////////////////////////////////////////////////////////////
//////////////////////////Development Variables/////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Set Sleeptime in ms
int sleep = 0;
// Set Seed
int rnd_value = 150;
// Set Start Goal only if true
bool user_set_start_goal = true;
int user_start_x = 10;
int user_start_y = 5;
int user_goal_x = 65;
int user_goal_y = 250;
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


int start_x = 0;
int start_x_fix;
int start_y = 0;
int start_y_fix;
int goal_x = 0;
int goal_y = 0;

struct Field
{
    char zeichen;
    bool checkt;
    bool pre_checkt;
    bool wall;
    double accurate_distance;
    double estimat_distance;
    double sum_distance;
    int parent_x;
    int parent_y;
};

///Init and Delete Game Field
///
Field*** Init_GameField(int grafik_buffer, int game_field_height, int game_field_width);
void Fill_3D_Struct_Array(Field*** sname, int grafik_buffer, int game_field_height, int game_field_width, bool b, char c,
    double accurate_distance, double estimat_distance, double sum_distance, int parent_x, int parent_y, bool pre_checkt);
void Delete_GameField(Field*** game_field_array, int grafik_buffer, int game_field_height);

/// Buffer Funktions
//
inline int Set_Buffer_0(int grafik_buffer);
inline int Set_Buffer_1(int grafik_buffer);
inline int Switch_Buffer(int grafik_buffer);
inline void Copy_Display_Buffer(Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width);
/// Show Field
//
void Draw_Field(Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width);
void Show_GameField(string game_field, Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width, bool show_buffer);

/// User Inputs
//
int User_GameField_Height(int game_field_height);
int User_GameField_Width(int game_field_width);

/// Caluculation Distance
//
double Calculate_Accurate(int start_x,int start_y, int check_field_x, int check_field_y);
double Calculate_Estimat(int check_field_x, int check_field_y);
void Calculate_Closest_Field(Field*** game_field_array, int grafik_buffer,bool show_distance);
void Check_Field(Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width);

int main()
{

    
    char test;

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
    Field*** game_field_array = Init_GameField(grafik_buffer, game_field_height, game_field_width);

    Fill_3D_Struct_Array(game_field_array,grafik_buffer,game_field_height,game_field_width, false, ' ',0,0,99999,0,0,false);    

    Draw_Field(game_field_array,grafik_buffer,game_field_height,game_field_width);
    /// Show Map Ones
    grafik_buffer = Set_Buffer_0(grafik_buffer);
    Show_GameField(game_field,game_field_array, grafik_buffer, game_field_height, game_field_width, false);
    /// Game Start
    // 
    
    while (game_field_array[grafik_buffer][goal_x][goal_y].checkt != true)
    {
        Calculate_Closest_Field(game_field_array, grafik_buffer, false);
        Check_Field(game_field_array, grafik_buffer, game_field_height, game_field_width);

        Copy_Display_Buffer(game_field_array, grafik_buffer, game_field_height, game_field_width);
        grafik_buffer = Switch_Buffer(grafik_buffer);
        Show_GameField(game_field, game_field_array, grafik_buffer, game_field_height, game_field_width, false);
    };

    
    /*if (game_field_array[grafik_buffer][goal_x][goal_y].checkt == true)
    {
        
        int parent_x = game_field_array[grafik_buffer][start_x_fix][start_y_fix].parent_x;
        int parent_y = game_field_array[grafik_buffer][start_x_fix][start_y_fix].parent_y;
        cout << parent_x << " : " << parent_y << endl;
        Sleep(2000);
        while (true)
        {
            cout << parent_x << " : " << parent_y << endl;
            game_field_array[grafik_buffer][parent_x][parent_y].zeichen = 'X';


            cout << game_field_array[grafik_buffer][parent_x][parent_y].parent_x << endl;
            Sleep(2000);
            parent_x = game_field_array[grafik_buffer][parent_x][parent_y].parent_x;
            cout << game_field_array[grafik_buffer][parent_x][parent_y].parent_x << endl;
            Sleep(2000);
            cout << game_field_array[grafik_buffer][parent_x][parent_y].parent_y << endl;
            Sleep(2000);
            parent_y = game_field_array[grafik_buffer][parent_x][parent_y].parent_y;
            cout << game_field_array[grafik_buffer][parent_x][parent_y].parent_y << endl;
            Sleep(2000);
            
            Show_GameField(game_field, game_field_array, grafik_buffer, game_field_height, game_field_width, true);
            
        }
    }*/

    

    
    cin >> test;

    Delete_GameField(game_field_array, 2, game_field_height);

}
///Init and Delete Game Field
//
Field*** Init_GameField(int grafik_buffer, int game_field_height, int game_field_width)
{
    Field*** game_Field = new Field**[grafik_buffer];
    for (int i = 0; i < grafik_buffer; i++)
    {
        game_Field[i] = new Field* [game_field_height];
        for (int j = 0; j < game_field_height; j++)
        {
            game_Field[i][j] = new Field[game_field_width];
        }
    }
    return game_Field;
}

void Fill_3D_Struct_Array(Field*** sname, int grafik_buffer, int game_field_height, int game_field_width, bool b, char c,
    double accurate_distance, double estimat_distance, double sum_distance, int parent_x, int parent_y, bool pre_checkt)
{
    for (int i = 0; i < grafik_buffer; i++)
    {    
        for (int j = 0; j < game_field_height; j++)
        {
            for (int k = 0; k < game_field_width; k++)
            {                
                sname[i][j][k].checkt = b;
                sname[i][j][k].zeichen = c;
                sname[i][j][k].wall = b;
                sname[i][j][k].accurate_distance = accurate_distance;
                sname[i][j][k].estimat_distance = estimat_distance;
                sname[i][j][k].sum_distance = sum_distance;
                sname[i][j][k].parent_x = parent_x;
                sname[i][j][k].parent_y = parent_y;
                sname[i][j][k].pre_checkt = pre_checkt;
            }
        }
    }
}

void Delete_GameField(Field*** game_field_array, int grafik_buffer, int game_field_height)
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
void Show_GameField(string game_field, Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width, bool show_buffer)
{
    
    Sleep(sleep);
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
                game_field += game_field_array[0][i][j].zeichen;
            }
            else if (grafik_buffer == 1)
            {
                game_field += game_field_array[1][i][j].zeichen;
            }
            
        }
        game_field += "\n";
    }
    
    system("CLS");
    cout << game_field;
    
}

void Draw_Field(Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width)
{
    int rnd = 0;
    for (int i = 0; i < game_field_height; i++)
    {
        for (int j = 0; j < game_field_width; j++)
        {
            rnd = rand() % 1000;
            if (i == 0 || i == game_field_height - 1)
            {
                game_field_array[0][i][j].zeichen = '#';
                game_field_array[1][i][j].zeichen = '#';
            }
            else if (j == 0 || j == game_field_width - 1)
            {
                game_field_array[0][i][j].zeichen = '#';
                game_field_array[1][i][j].zeichen = '#';
            }
            else if (rnd < rnd_value)
            {
                game_field_array[0][i][j].zeichen = '#';
                game_field_array[1][i][j].zeichen = '#';
            }
            else
            {
                game_field_array[0][i][j].zeichen = ' ';
                game_field_array[1][i][j].zeichen = ' ';
            }
            
        }
        
    }
    
    if (user_set_start_goal == true)
    {
        start_x = user_start_x;
        start_y = user_start_y;
        goal_x = user_goal_x;
        goal_y = user_goal_y;
    }
    else
    {
        start_x = rand() % (game_field_height - 2) + 1;
        start_y = rand() % (game_field_width - 2) + 1;
        goal_x = rand() % (game_field_height - 2) + 1;
        goal_y = rand() % (game_field_width - 2) + 1;
    }
    start_x_fix = start_x;
    start_y_fix = start_y;    

    game_field_array[0][start_x][start_y].zeichen = '1';
    game_field_array[1][start_x][start_y].zeichen = '1';
    game_field_array[0][start_x][start_y].checkt = true;
    game_field_array[1][start_x][start_y].checkt = true;
    
    game_field_array[0][goal_x][goal_y].zeichen = '2';
    game_field_array[1][goal_x][goal_y].zeichen = '2';
    game_field_array[0][goal_x][goal_x].checkt = true;
    game_field_array[1][goal_x][goal_x].checkt = true;
    
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

    accurate_x = abs(pow(start_x - check_field_x, 2));
    accurate_y = abs(pow(start_y - check_field_y, 2));
    return accurate = sqrt(accurate_x + accurate_y);

}

double Calculate_Estimat(int check_field_x, int check_field_y)
{
    double estimat = 0;
    double estimat_x = 0;
    double estimat_y = 0;

    estimat_x = abs(pow(check_field_x - goal_x, 2));
    estimat_y = abs(pow(check_field_y - goal_y, 2));
    return estimat = sqrt(estimat_x + estimat_y);
}

void Calculate_Closest_Field(Field*** game_field_array,int grafik_buffer, bool show_calculation)
{
    double accurate_distance = 0;
    double estimat_distance = 0;
    double sum_distance = 0;
    bool show_precheck_field = false;
    

    if (game_field_array[grafik_buffer][start_x - 1][start_y - 1].zeichen == '#')
    {
        game_field_array[0][start_x - 1][start_y - 1].wall = true;
        game_field_array[1][start_x - 1][start_y - 1].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x - 1][start_y - 1].accurate_distance = Calculate_Accurate(start_x, start_y, start_x - 1, start_y - 1) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x - 1][start_y - 1].estimat_distance = Calculate_Estimat(start_x - 1, start_y - 1);
            game_field_array[i][start_x - 1][start_y - 1].sum_distance = game_field_array[i][start_x - 1][start_y - 1].accurate_distance +
                game_field_array[i][start_x - 1][start_y - 1].estimat_distance;
            game_field_array[i][start_x - 1][start_y - 1].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x - 1][start_y - 1].zeichen = 'X';
            }        
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x - 1][start_y].zeichen == '#')
    {
        game_field_array[0][start_x - 1][start_y].wall = true;
        game_field_array[1][start_x - 1][start_y].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 1 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x - 1][start_y].accurate_distance = Calculate_Accurate(start_x, start_y, start_x - 1, start_y) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x - 1][start_y].estimat_distance = Calculate_Estimat(start_x - 1, start_y);
            game_field_array[i][start_x - 1][start_y].sum_distance = game_field_array[i][start_x - 1][start_y].accurate_distance +
                game_field_array[i][start_x - 1][start_y].estimat_distance;
            game_field_array[i][start_x - 1][start_y].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x - 1][start_y].zeichen = 'X';
            }
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 1 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x - 1][start_y + 1].zeichen == '#')
    {
        game_field_array[0][start_x - 1][start_y + 1].wall = true;
        game_field_array[1][start_x - 1][start_y + 1].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 2 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x - 1][start_y + 1].accurate_distance = Calculate_Accurate(start_x, start_y, start_x - 1, start_y + 1) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x - 1][start_y + 1].estimat_distance = Calculate_Estimat(start_x - 1, start_y + 1);
            game_field_array[i][start_x - 1][start_y + 1].sum_distance = game_field_array[i][start_x - 1][start_y + 1].accurate_distance +
                game_field_array[i][start_x - 1][start_y + 1].estimat_distance;
            game_field_array[i][start_x - 1][start_y + 1].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x - 1][start_y + 1].zeichen = 'X';
            }
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x << " Y:" << start_y + 2 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x][start_y - 1].zeichen == '#')
    {
        game_field_array[0][start_x][start_y - 1].wall = true;
        game_field_array[1][start_x][start_y - 1].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x][start_y - 1].accurate_distance = Calculate_Accurate(start_x, start_y, start_x, start_y - 1) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x][start_y - 1].estimat_distance = Calculate_Estimat(start_x, start_y - 1);
            game_field_array[i][start_x][start_y - 1].sum_distance = game_field_array[i][start_x][start_y - 1].accurate_distance +
                game_field_array[i][start_x][start_y - 1].estimat_distance;
            game_field_array[i][start_x][start_y - 1].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x][start_y - 1].zeichen = 'X';
            }
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x][start_y + 1].zeichen == '#')
    {
        game_field_array[0][start_x][start_y + 1].wall = true;
        game_field_array[1][start_x][start_y + 1].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y + 2 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x][start_y + 1].accurate_distance = Calculate_Accurate(start_x, start_y, start_x, start_y + 1) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x][start_y + 1].estimat_distance = Calculate_Estimat(start_x, start_y + 1);
            game_field_array[i][start_x][start_y + 1].sum_distance = game_field_array[i][start_x][start_y + 1].accurate_distance +
                game_field_array[i][start_x][start_y + 1].estimat_distance;
            game_field_array[i][start_x][start_y + 1].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x][start_y + 1].zeichen = 'X';
            }
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 1 << " Y:" << start_y + 2 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x + 1][start_y - 1].zeichen == '#')
    {
        game_field_array[0][start_x + 1][start_y - 1].wall = true;
        game_field_array[1][start_x + 1][start_y - 1].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x + 1][start_y - 1].accurate_distance = Calculate_Accurate(start_x, start_y, start_x + 1, start_y - 1) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x + 1][start_y - 1].estimat_distance = Calculate_Estimat(start_x + 1, start_y - 1);
            game_field_array[i][start_x + 1][start_y - 1].sum_distance = game_field_array[i][start_x + 1][start_y - 1].accurate_distance +
                game_field_array[i][start_x + 1][start_y - 1].estimat_distance;
            game_field_array[i][start_x + 1][start_y - 1].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x + 1][start_y - 1].zeichen = 'X';
            }
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x + 1][start_y].zeichen == '#')
    {
        game_field_array[0][start_x + 1][start_y].wall = true;
        game_field_array[1][start_x + 1][start_y].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 1 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x + 1][start_y].accurate_distance = Calculate_Accurate(start_x, start_y, start_x + 1, start_y) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x + 1][start_y].estimat_distance = Calculate_Estimat(start_x + 1, start_y);
            game_field_array[i][start_x + 1][start_y].sum_distance = game_field_array[i][start_x + 1][start_y].accurate_distance +
                game_field_array[i][start_x + 1][start_y].estimat_distance;
            game_field_array[i][start_x + 1][start_y].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x + 1][start_y].zeichen = 'X';
            }
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 1 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }
    if (game_field_array[grafik_buffer][start_x + 1][start_y + 1].zeichen == '#')
    {
        game_field_array[0][start_x + 1][start_y + 1].wall = true;
        game_field_array[1][start_x + 1][start_y + 1].wall = true;
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 2 << endl;
            cout << "Is a Wall" << endl;
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            game_field_array[i][start_x + 1][start_y + 1].accurate_distance = Calculate_Accurate(start_x, start_y, start_x + 1, start_y + 1) +
                game_field_array[i][start_x][start_y].accurate_distance;
            game_field_array[i][start_x + 1][start_y + 1].estimat_distance = Calculate_Estimat(start_x + 1, start_y + 1);
            game_field_array[i][start_x + 1][start_y + 1].sum_distance = game_field_array[i][start_x + 1][start_y + 1].accurate_distance +
                game_field_array[i][start_x + 1][start_y + 1].estimat_distance;
            game_field_array[i][start_x + 1][start_y + 1].pre_checkt = true;
            if (show_precheck_field == true)
            {
                game_field_array[i][start_x + 1][start_y + 1].zeichen = 'X';
            }
        }
        if (show_calculation == true)
        {
            cout << "Field X:" << start_x + 2 << " Y:" << start_y + 2 << endl;
            cout << "Accurate Distance: " << accurate_distance << " Estimat Distance: " << estimat_distance << " Sum Distance: " << sum_distance << endl;
        }
    }    
}

void Check_Field(Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width)
{    
    double min = 999999;
    for (int i = 0; i < game_field_height; i++)
    {
        for (int j = 0; j < game_field_width; j++)
        {
            if (min > game_field_array[grafik_buffer][i][j].sum_distance &&
                game_field_array[grafik_buffer][i][j].checkt != true &&
                game_field_array[grafik_buffer][i][j].pre_checkt == true &&
                game_field_array[grafik_buffer][i][j].wall == false)
            {
                min = game_field_array[grafik_buffer][i][j].sum_distance; 
                
            }
            
        }
    }
    
      
    
    for (int i = 0; i < game_field_height; i++)
    {
        for (int j = 0; j < game_field_width; j++)
        {
            if (min == game_field_array[grafik_buffer][i][j].sum_distance)
            {
                

                if (grafik_buffer == 0)
                {
                    game_field_array[0][i][j].checkt = true;
                    game_field_array[1][i][j].checkt = true;
                    game_field_array[0][i][j].parent_x = start_x;
                    game_field_array[0][i][j].parent_y = start_y;
                    game_field_array[1][i][j].parent_x = start_x;
                    game_field_array[1][i][j].parent_y = start_y;
                    if (game_field_array[grafik_buffer][goal_x][goal_y].checkt != true)
                    {
                    game_field_array[1][i][j].zeichen = '0';
                    }
                    start_x = i;
                    start_y = j;
                }
                else if (grafik_buffer == 1)
                {
                    game_field_array[0][i][j].checkt = true;
                    game_field_array[1][i][j].checkt = true;
                    game_field_array[0][i][j].parent_x = start_x;
                    game_field_array[0][i][j].parent_y = start_y;
                    game_field_array[1][i][j].parent_x = start_x;
                    game_field_array[1][i][j].parent_y = start_y;
                    if (game_field_array[grafik_buffer][goal_x][goal_y].checkt != true)
                    {
                        game_field_array[0][i][j].zeichen = '0';
                    }
                    start_x = i;
                    start_y = j;
                }
                
                
            }
        }
    }
}

void Copy_Display_Buffer(Field*** game_field_array, int grafik_buffer, int game_field_height, int game_field_width)
{
    if (grafik_buffer == 0)
    {
        for (int i = 0; i < game_field_height; i++)
        {
            for (int j = 0; j < game_field_width; j++)
            {
                game_field_array[0][i][j].zeichen = game_field_array[1][i][j].zeichen;
            }
        }
    }
    else if ((grafik_buffer == 1))
    {
        for (int i = 0; i < game_field_height; i++)
        {
            for (int j = 0; j < game_field_width; j++)
            {
                game_field_array[1][i][j].zeichen = game_field_array[0][i][j].zeichen;
            }
        }
    }
}