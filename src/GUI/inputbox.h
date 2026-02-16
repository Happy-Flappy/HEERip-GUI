#ifndef INPUTBOX_H
#define INPUTBOX_h

#include <cctype>

std::wstring inputMessage(std::string title,int rangeLow,int rangeHigh)
{
	ws::Window window(300,200,title);
	
	ws::Button ok,cancel;
	ok.setSize(50,25);
	cancel.setSize(50,25);
	ok.setText("Ok");
	cancel.setText("Cancel");
	ok.setPosition(window.getSize().x * 0.25,window.getSize().y * 0.70);
	cancel.setPosition(window.getSize().x * 0.55,window.getSize().y * 0.70);
	
	
	window.addChild(ok);
	window.addChild(cancel);
	
	ws::TextBox box;
	box.setSize(70,70/2);
	ws::Font font;
	font.loadFromSystem("Arial");
	ws::Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	
	box.setFont(font,text);
	box.addStyle(ES_NUMBER);
	box.setPosition(window.getSize().x * 0.40,window.getSize().y * 0.4);

	
	window.addChild(box);
	window.removeStyle(WS_THICKFRAME | WS_MAXIMIZEBOX);
	
	while(window.isOpen())
	{
		MSG m;
		while(window.pollEvent(m))
		{
			if(ok.isPressed(m))
			{
				std::string val = box.getText();
				for(int a=0;a<val.length();a++)
				{
					if(!isdigit(val[a]))
					{
						MessageBoxA(NULL,"Invalid Entry! Should have been a number!","Invalid:",MB_OK);
						return L"NULL";
					}
				}
				
				try {
					int number = std::stoi(val); 
					if(number < rangeLow)
						number = 0;
					if(number > rangeHigh)
						number = rangeHigh;
					
					return std::to_wstring(number);
				} catch (const std::invalid_argument& e) {
					std::cerr << "Invalid argument: " << e.what() << std::endl;
				} catch (const std::out_of_range& e) {
					std::cerr << "Out of range: " << e.what() << std::endl;
				}				
				window.close();
			}
			if(cancel.isPressed(m))
			{
				window.close();
				return L"NULL";
			}
		}
	}
	return L"NULL";
}


std::pair<std::wstring,std::wstring> inputMessage2(std::string title)
{
	ws::Window window(300,200,title);
	
	ws::Button ok,cancel;
	ok.setSize(50,25);
	cancel.setSize(50,25);
	ok.setText("Ok");
	cancel.setText("Cancel");
	ok.setPosition(window.getSize().x * 0.25,window.getSize().y * 0.70);
	cancel.setPosition(window.getSize().x * 0.55,window.getSize().y * 0.70);
	
	
	window.addChild(ok);
	window.addChild(cancel);
	
	ws::TextBox box,box2;
	box.setSize(50,25);
	box2.setSize(50,25);
	ws::Font font;
	font.loadFromSystem("Arial");
	ws::Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	
	box.setFont(font,text);
	box2.setFont(font,text);
	
	box.addStyle(ES_NUMBER);
	box2.addStyle(ES_NUMBER);
	box.setPosition(window.getSize().x * 0.25,window.getSize().y * 0.4);
	box2.setPosition(window.getSize().x * 0.55,window.getSize().y * 0.4);
	
	window.addChild(box);
	window.addChild(box2);
	window.removeStyle(WS_THICKFRAME | WS_MAXIMIZEBOX);
	
	while(window.isOpen())
	{
		MSG m;
		while(window.pollEvent(m))
		{
			if(ok.isPressed(m))
			{
				std::string val = box.getText();
				for(int a=0;a<val.length();a++)
				{
					if(!isdigit(val[a]))
					{
						MessageBoxA(NULL,"Invalid Entry! Should have been a number!","Invalid:",MB_OK);
						return std::make_pair(L"NULL",L"NULL");
					}
				}
				
				std::string val2 = box2.getText();
				for(int a=0;a<val2.length();a++)
				{
					if(!isdigit(val2[a]))
					{
						MessageBoxA(NULL,"Invalid Entry! Should have been a number!","Invalid:",MB_OK);
						return std::make_pair(L"NULL",L"NULL");
					}
				}
				
				std::pair<std::wstring,std::wstring> pair;
				pair.first = ws::WIDE(val);
				pair.second = ws::WIDE(val2);
				window.close();
				return pair;
			}
			if(cancel.isPressed(m))
			{
				window.close();
				return std::make_pair(L"NULL",L"NULL");
			}
		}
	}
	return std::make_pair(L"NULL",L"NULL");
}



#endif