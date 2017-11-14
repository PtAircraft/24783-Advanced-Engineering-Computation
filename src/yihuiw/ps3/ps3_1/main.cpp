#include <simplebitmap.h>
#include <string>

int main(int argc, char *argv[])
{
	SimpleBitmap bmp;
    int x = 0;
    int y = 0;
    for (int i = 0; i < 200; i++){
        if (argc < 2)
        {
            printf("Usage: testbitmap <png-file>\n");
        }
        else if (false == bmp.LoadPng(argv[1]))
        {
            printf("Falied to read a ,PNG file.");
        }
        else
        {
            std::string name = std::to_string(i) + ".png";
            FILE *fp = fopen(name.c_str(), "wb");
            
            
            if (nullptr != fp)
            {
                SimpleBitmap tmp =bmp.CutOut(x,y,40,40);
                
                tmp.SavePng(fp);
                fclose(fp);
            }
        }
        x = x + 40;
        if (!bmp.IsXInRange(x)){
            x = 0;
            y = y + 40;
        }
        if (!bmp.IsInRange(x,y)) {
            break;
        }
    }
    
    
	return 0;
}
//check out
