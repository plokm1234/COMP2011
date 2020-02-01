# include "lab7.h"

void _print(const ASCIIImage& img, bool verbose)
{
    if(verbose)
    {
        cout<<"row: "<<img.row<<endl;
        cout<<"col: "<<img.col<<endl;
        cout<<"valid?: "<<(_check_image_size(img)? "True":"False")<<endl;
        cout<<"data: "<<endl;
    }
    for(int i=0; i<img.row; i++)
    {
        for(int j=0; j<img.col; j++)
            cout<<img.data[i][j];
        cout<<endl;
    }
}

bool _check_image_size(const ASCIIImage& img)
{
    // Note:Assume data is initialized with 0, and starts from the top-left corner.
    // TODO: Check Square
    // TODO: Check Left Top
    int row, col;
    for(int i=0; i<MAX_IMAGE_SIZE; i++)
    {
        row = i;
        if(img.data[row][0] == 0)
            break;
    }
    for(int i=0; i<MAX_IMAGE_SIZE; i++)
    {
        col = i;
        if(img.data[0][col] == 0)
            break;
    }
    if(row != img.row || col != img.col)
        return false;
    return true;
}

void plot(const ASCIIImage& img)
{
    cout<<endl;
    _print(img);
    cout<<endl;
}

bool write_image(const ASCIIImage& img, const char path[])
{
    if(_check_image_size(img))
    {
        ofstream ofs; ofs.open(path);
        if (!ofs)
        {
            cerr<<"Error: Can't open " <<path<<endl;
            return false;
        }
        ofs<<img.row; ofs<<endl;
        ofs<<img.col; ofs<<endl;
        for(int i=0; i<img.row; i++)
        {
            for(int j=0; j<img.col; j++)
                ofs<<img.data[i][j];
            ofs<<endl;
        }
        ofs.close();
        return true;
    }
    else
    {
        cerr<<"Error: Image size does not coicide with its data."<<endl;
        return false;
    }
}

bool read_image(ASCIIImage& img, const char path[])
{
    // Note: Assume the space is not an element of the image.
    // TODO: Read with getline.
    ifstream ifs(path);
    if (!ifs)
    {
        cerr << "Error: Can't open " << path << endl;
        return false;
    }
    ifs>>img.row; ifs>>img.col;
    if (img.row > MAX_IMAGE_SIZE || img.col > MAX_IMAGE_SIZE)
    {
        cerr << "Error: The image size > MAX_IMAGE_SIZE."<<endl;
        return false;
    }
    for(int i=0; i<img.row; i++)
        for(int j=0; j<img.col; j++)
            ifs>>img.data[i][j];
    ifs.close();
    return true;
}

void rotate_clockwise(ASCIIImage& img)
{
    // move img data to temp
    char temp[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE] = {0};
    for(int i=0; i<img.row; i++)
        for(int j=0; j<img.col; j++)
            {
                temp[i][j] = img.data[i][j];
                img.data[i][j] = 0;
            }
    // swap row & col
    int col_ = img.col; img.col = img.row; img.row = col_;
    // map value
    for(int i=0; i<img.row; i++)
        for(int j=0; j<img.col; j++)
            img.data[i][img.col-j-1] = temp[j][i];
    // check size
    cout<<"rotate_clockwise: "<<(_check_image_size(img)? "True":"False")<<endl;
}

void flip_horizontally(ASCIIImage& img)
{
    // move img data to temp
    char temp[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE] = {0};
    for(int i=0; i<img.row; i++)
        for(int j=0; j<img.col; j++)
            {
                temp[i][j] = img.data[i][j];
                img.data[i][j] = 0;
            }
    // map value
    for(int i=0; i<img.row; i++)
        for(int j=0; j<img.col; j++)
            img.data[i][j] = temp[i][img.col-j-1];
    // check size
    cout<<"flip_horizontally: "<<(_check_image_size(img)? "True":"False")<<endl;
}
