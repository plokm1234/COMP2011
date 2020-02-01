# include "lab7.h"

// Utility functions
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

// Function for ploting the ASCIIImage
void plot(const ASCIIImage& img)
{
    cout<<endl;
    _print(img);
    cout<<endl;
}

// FUNCTION 1
/**
 * TODO:
 * Read the file defined by 'path', and initialize the 'img' with the contents of the file.
 * It should return true if it reads & initializes successfully. Otherwise, it should return False.
 * Note:
 * The row number of the ASCII image locates at the 1st line of the file.
 * The column number of the ASCII image locates at the 2nd line of the file.
 * The following contents are the data of the ASCII image.
 * You can assume the data is square and contains no space.
 **/
bool read_image(ASCIIImage& img, const char path[])
{
ifstream ifs;
ifs.open(path);
if(!ifs.is_open()){return false;}
ifs>>img.row;
ifs>>img.col;
for(int i=0;ifs>>img.data[i];i++){}     
ifs.close();
return true;

}

// FUNCTION 2
/**
 * TODO:
 * Write 'img' into the file defined by 'path' if 'img' is valid.
 * It should return true if it writes successfully. Otherwise, it should return False.
 * The data format should coincide with the notification of FUNCTION 1.
 * Note:
 * You can validate the 'img' with '_check_image_size'.
 * Of course, you can implement your own validation function.
 **/
bool write_image(const ASCIIImage& img, const char path[])
{
    if(_check_image_size(img)){
ofstream ofs;
ofs.open(path);
if(!ofs.is_open()){return false;}
int i=0;
ofs<<img.row<<endl;
ofs<<img.col<<endl;
for(int i=img.row-1;i>=0;i--){
    ofs<<img.data[i]<<endl;}
    return true;
    }

return false;
}

// FUNCTION 3
/**
 * TODO:
 * Rotate the 'img' right by 90 degrees.
 * Note:
 * You have to make sure the result is also a valid ASCIIImage.
 **/
void rotate_clockwise(ASCIIImage& img)
{
    char c[img.col][img.row];
    int temp;

    for(int i=0;i<img.row;i++){
        for(int j =0;j<img.col;j++){
            c[j][img.row-i-1]=img.data[i][j];
        }
    }
    temp=img.col;
    img.col=img.row;
    img.row=temp;
    for(int i=0;i<img.row;i++){
        for(int j=0;j<img.col;j++){
            img.data[i][j]=c[i][j];
        }   
    }
}

// FUNCTION 4
/**
 * TODO:
 * Flip the 'img' horizontally.
 * Note:
 * You have to make sure the result is also a valid ASCIIImage.
 **/
void flip_horizontally(ASCIIImage& img)
{
    if(img.col%2!=0){
        for(int i=0;i<img.row;i++){
        for(int j =0;j<(img.col+1)/2;j++){
            char c;
            c= img.data[i][j];
            img.data[i][j]=img.data[i][(img.col+1)/2+(img.col+1)/2-j-2];
            img.data[i][(img.col+1)/2+(img.col+1)/2-j-2]=c;
        }
    }
    }
    else{
        for(int i=0;i<img.row;i++){
        for(int j =0;j<(img.col)/2;j++){
            char c;
            c= img.data[i][j];
            img.data[i][j]=img.data[i][(img.col)/2+(img.col)/2-j-1];
            img.data[i][(img.col)/2+(img.col)/2-j-1]=c;
        }
    }
    }
}
