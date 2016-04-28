#include <iostream>

#include "CPP/a10.h"

using namespace std;

//void makeIntoPainting(char *s) {
void makeIntoPainting(){
    Image texture("ron_output/longBrush.png");
    //Image im(s);
    Image im("ron_output/output.png");

    Image output = orientedPaint(im, texture, 130000, 40, .1);
    output.write("morris_output/out.png");
}

int main()
{
    makeIntoPainting();
    return EXIT_SUCCESS;
}

/*int main(int argc, char* argv[])
{
	char *s1 = "Input/morris.png";
    makeIntoPainting(s1);
    return EXIT_SUCCESS;
}*/
