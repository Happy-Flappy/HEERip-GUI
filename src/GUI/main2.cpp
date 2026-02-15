#include "winsimple.h"



int main()
{
	ws::Window window(960,540,"");
	ws::Window window2(300,100,"Message Box");
	
	/*
	ws::TextBox textbox;
	textbox.addStyle(ES_NUMBER);
	textbox.setPosition(0,0);
	textbox.setSize(100,100);
	textbox.removeStyle(ES_MULTILINE);
	*/
	
	ws::ComboBox box;
	window.addChild(box);
	
	
	
	while(window.isOpen())
	{	
		window2.isOpen();
		window.clear();
		window.display();
		window2.clear();
		window2.display();
		
	}
}