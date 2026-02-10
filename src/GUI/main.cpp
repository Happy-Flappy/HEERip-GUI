#include "winsimple.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<PROCESS_INFORMATION> processes;

void cancel()
{
	for(int a=0;a<processes.size();a++)
	{
        if (processes[a].hProcess != NULL)
        {
            TerminateProcess(processes[a].hProcess, 1);  // 1 is exit code
            WaitForSingleObject(processes[a].hProcess, INFINITE);  // Wait for termination
        }
        
        //close the handles
        if (processes[a].hProcess != NULL)
            CloseHandle(processes[a].hProcess);
        if (processes[a].hThread != NULL)
            CloseHandle(processes[a].hThread);
	}
	processes.clear();
}



struct File
{
	fs::path path;
	std::vector<std::wstring> options;
};


int selected = -1;
std::vector<File> list;




void startRip(File file)
{
	
    std::string stem = file.path.stem().string();
    std::string extension = file.path.extension().string();
 

 
    // Create output directory structure
    fs::path output_dir = fs::path("output") / stem / extension;
    fs::create_directories(output_dir);
    
    fs::path output_path = output_dir / stem;
    
    std::wstring cmdLine = L"heerip.exe ";
    cmdLine += L"\"" + file.path.wstring() + L"\" ";
    cmdLine += L"-o \"" + output_path.wstring() + L"\"";
	
	
	for(int a=0;a<file.options.size();a++)
	{
		cmdLine += L" ";
		cmdLine += file.options[a];
	}
	
	
	std::wcout << cmdLine << L"\n";
	
	
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi = {0};
    
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;
    
    if(CreateProcessW(
        NULL,                    // application name (NULL = use command line)
        &cmdLine[0],             // command line
        NULL,                    // process security attributes
        NULL,                    // thread security attributes
        FALSE,                   // inherit handles
        CREATE_NEW_CONSOLE,      // creation flags
        NULL,                    // environment
        NULL,                    // current directory
        &si,                     // startup info
        &pi))                    // process info
		{
//       WaitForSingleObject(pi.hProcess, INFINITE);
		//backup handles to close them if cancelled.
		processes.push_back(pi);
    }
    else
    {
        DWORD error = GetLastError();
        std::wcerr << L"CreateProcess failed: " << error << std::endl;
    }
}











void displayList(int &left,int &top,int &lastItem,ws::Vec2i &MPosition,bool &mousedown,ws::Text &text,int &screenWidth,int &screenHeight,ws::Text &removal,ws::Window &window,int shift)
{
	
	for(int a=lastItem; a < list.size(); a++)
	{
		int resultY = 50 + (30 * top) - shift;
		
		text.setPosition(left,resultY);
		text.setString(list[a].path.filename().string());
		window.draw(text);
		
		removal.setPosition(text.getPosition().x + text.width + 30,resultY);

		if(removal.contains(MPosition))
			removal.setCharacterSize(20 + 2);
		else
			removal.setCharacterSize(20);

		window.draw(removal);
		
		if(removal.contains(MPosition) && mousedown)
		{
			list.erase(list.begin() + a);
			lastItem = 10000000;
			mousedown = false;
			break;
		}
		
		
		if(text.contains(MPosition) && mousedown)
		{
			selected = a;
			mousedown = false;
		}
		
		
		if(selected == a)
		{
			//draw rectangle around it
			Gdiplus::Pen pen(Gdiplus::Color(255,0,255,0), 2);
			window.canvas->DrawRectangle(&pen, int(text.getPosition().x), int(text.getPosition().y), int(text.getVisualWidth()),int(text.getVisualHeight()));			
		}
		
		
		lastItem = a+1;
		if(resultY > screenHeight - (text.height * 5))
		{
			top = 0;
			left += 300;
			break;
		}
		top++;
	}
}




int main()
{
	
	int screenHeight = 480*2;
	int screenWidth = 640 * 2;
	ws::Window window(screenWidth,screenHeight,"");
	
	ws::Texture tback;
	tback.loadFromFile("GUIBack2.png");
	
	ws::Sprite back;
	back.setTexture(tback);
	back.setScale(2,2);
	
	
	ws::Dropdown fileMenu(1000,"File");
	
	fileMenu.addItem(1001,MF_STRING,"Export");
	fileMenu.addItem(1002,MF_SEPARATOR,"");
	fileMenu.addItem(1003,MF_STRING,"Exit");
	
	ws::Dropdown manageMenu(1009,"Manage");
	
	manageMenu.addItem(1010,MF_STRING,"Add File");
	manageMenu.addItem(1011,MF_STRING,"Add Folder");
	manageMenu.addItem(1012,MF_STRING,"Remove All Images");
	manageMenu.addItem(1013,MF_STRING,"Remove All Sounds");
	manageMenu.addItem(1014,MF_STRING,"Remove All Empty");
	manageMenu.addItem(1015,MF_STRING,"Remove All");


	ws::Dropdown optionsMenu(1050,"Options");	
	
	optionsMenu.addItem(1051,MF_STRING,"Set Transparency Color"); //-alttrans <val>
	optionsMenu.addItem(1052,MF_STRING,"Set Last Room Read");//-end <val>
	optionsMenu.addItem(1053,MF_STRING,"Set First Room Read");//-start <val>

//BOOKMARK

	optionsMenu.addItem(1054,MF_SEPARATOR,"");
	
	optionsMenu.addItem(1055,MF_STRING,"Set Buffer Byte Count"); //-bufsize <val>, -b <val>
	optionsMenu.addItem(1056,MF_STRING,"Set First Byte Decoder");//-decode <val>, -d <val>
	optionsMenu.addItem(1057,MF_STRING,"Set Ignore Trailing Bytes in Sound");//-ignoreend <val>
	optionsMenu.addItem(1058,MF_STRING,"Set Ignore Init Bytes in Sound");//-ignorestart <val>

	optionsMenu.addItem(1059,MF_SEPARATOR,"");

		
	optionsMenu.addItem(1060,MF_STRING,"Disable MetaData Ripping");//--nometadata
	optionsMenu.addItem(1061,MF_STRING,"Disable Log File Creation");//--disablelog
	optionsMenu.addItem(1062,MF_STRING,"Disable All  Sound Ripping");//--nosound
	optionsMenu.addItem(1063,MF_STRING,"Disable Talk Subtitle Ripping");//--notlke
	
	optionsMenu.addItem(1064,MF_STRING,"Disable AKOS Image Ripping");//--noakos
	optionsMenu.addItem(1065,MF_STRING,"Disable AWIZ Image Ripping");//--noawiz
	optionsMenu.addItem(1066,MF_STRING,"Disable CHAR Font  Ripping");//--nochar
	optionsMenu.addItem(1067,MF_STRING,"Disable DMU  Sound Ripping");//--noextdmu
	
	optionsMenu.addItem(1068,MF_STRING,"Disable OBIM Image Ripping");//--noobim
	optionsMenu.addItem(1069,MF_STRING,"Disable RMIM Image Ripping");//--normim
	

	optionsMenu.addItem(1070,MF_SEPARATOR,"");

	optionsMenu.addItem(1071,MF_STRING,"Disable All Ripping");//--norip
	
	optionsMenu.addItem(1072,MF_SEPARATOR,"");
	
	optionsMenu.addItem(1073,MF_STRING,"Normalize Audio Output");//--normalize
	
	optionsMenu.addItem(1074,MF_SEPARATOR,"");
	
	
	optionsMenu.addItem(1075,MF_STRING,"Set AKOS Only");//--akosonly
	optionsMenu.addItem(1076,MF_STRING,"Set AWIZ Only");//--awizonly
	optionsMenu.addItem(1077,MF_STRING,"Set CHAR Only");//--charonly
	optionsMenu.addItem(1078,MF_STRING,"Set DMU Only");//--extdmuonly
	optionsMenu.addItem(1079,MF_STRING,"Set MetaData Only");//--metadataonly
	optionsMenu.addItem(1080,MF_STRING,"Set OBIM Only");//--obimonly
	optionsMenu.addItem(1081,MF_STRING,"Set RMIM Only");//--rmimonly
	optionsMenu.addItem(1082,MF_STRING,"Set Sound Only");//--soundonly
	optionsMenu.addItem(1083,MF_STRING,"Set Subtitles Only");//--tlkeonly
	
	optionsMenu.addItem(1084,MF_SEPARATOR,"");
	
	optionsMenu.addItem(1085,MF_STRING,"Force Internal Audio Format");//--decodeaudio
	optionsMenu.addItem(1086,MF_STRING,"Try Decode Only");//--decodeonly
	optionsMenu.addItem(1087,MF_STRING,"Force Lined Run Length Encoding");//--force_lined_rle
	optionsMenu.addItem(1088,MF_STRING,"Force UnLined Run Length Encoding");//--force_unlined_rle
	optionsMenu.addItem(1089,MF_STRING,"Force AKOS Lined Run Length Encoding");//--force_akos2c_rle
	optionsMenu.addItem(1090,MF_STRING,"Force AKOS Unlined Run Length Encoding");//--force_akos2c_bitmap
	
	
	
	
	
	
	ws::Menu menu;
	menu.setWindow(window);
	menu.addDropdown(fileMenu);
	menu.addDropdown(manageMenu);
	menu.addDropdown(optionsMenu);

	
	//resize the window because the menu bar currently has a glitch that does not allow it to be visible immediately.
	window.setSize(window.getSize());
	
	
	ws::FileWindow fileWindow;
	ws::FolderWindow folderWindow;
	
	ws::Font font;
	font.loadFromSystem("Sans Serif");
	
	ws::Text text;
	text.setFont(font);
	text.setPosition(50,50);
	text.setCharacterSize(20);
	text.setFillColor(ws::Hue::white);
	text.setBorderColor(ws::Hue::black);
	text.setBorderWidth(4);
	
	
	
	ws::Button cancelBtn;
	cancelBtn.setText("Cancel");
	cancelBtn.setPosition(screenWidth - 75,screenHeight - 75 - 75);
	cancelBtn.setSize(50,50);
	
	
	ws::Text removal;
	removal.setFont(font);
	removal.setCharacterSize(20);
	removal.setFillColor(ws::Hue::red);
	removal.setBorderColor(ws::Hue::black);
	removal.setBorderWidth(4);
	removal.setString("X");
	
	
	bool startedExport = false;
	bool mousedown = false;
	
	
	
	ws::Slider slider;
	slider.setPosition(screenWidth - 30,0);
	slider.setSize(20,screenHeight);
	slider.setRange(0,screenHeight * 3);
	slider.setVertical();
	slider.setSlidePosition(0);
	
	
	
	int shift = 0;




	
	while(window.isOpen())
	{
		
		
		
		
		ws::Vec2i MPosition;
		shift = slider.getSlidePosition();		
		
		
		MSG m;
		while(window.pollEvent(m))
		{
			
			slider.getScroll(m);
			

			if(m.message == WM_KEYDOWN)
			{
				if(m.wParam == VK_DELETE)
				{
					if(selected != -1 && selected < list.size())
					{
						list.erase(list.begin() + selected);
					}
				}
				if(m.wParam == VK_UP)
				{
					if(selected > 0)
						selected --;
				}
				
				if(m.wParam == VK_DOWN)
				{
					if(selected < list.size()-1)
						selected ++;
				}
				
			}
			
			if(m.message == WM_MOUSEMOVE)
			{
				int x = GET_X_LPARAM(m.lParam);
				int y = GET_Y_LPARAM(m.lParam);
				MPosition = window.toWorld(x,y);
			}
			
			if(m.message == WM_LBUTTONDOWN)
			{
				mousedown = true;
			}
			if(m.message == WM_LBUTTONUP)
			{
				mousedown = false;
			}

		
			if(cancelBtn.isPressed(m))
			{
				cancel();
			}
			
			
			
			int ID = menu.getEvent(m);




			
			if(ID == 1001)//export
			{
				if(MessageBox(window.hwnd,L"Are you sure you want to export?",L"Confirm your action...",MB_YESNO) == IDYES)
				{
					startedExport = true;
					for(int a=0;a<list.size();a++)
					{
						startRip(list[a]);
					}
					
				}
				while(window.pollEvent(m))
				{}
			}

			if(ID == 1003)//quit
			{
				if(MessageBox(window.hwnd,L"Are you sure you want to quit this program? The currently queued files will not be queued when you open the program again.",L"Are you sure?",MB_YESNO) == IDYES)
				{
					window.close();
				}
				while(window.pollEvent(m))
				{}	
			}

			
			if(ID == 1010)//Add Files
			{
				fileWindow.open(&window);
				std::string name = fileWindow.getFileName();
				if(name != "")
				{
					fs::path path = name;
					File file;
					file.path = path;
					list.push_back(file);
				}
				while(window.pollEvent(m))
				{}
			}

			if(ID == 1011)
			{
				folderWindow.open(&window);
				std::string name = folderWindow.getFolderName();
				
				if(name != "")
				{
					std::vector<std::string> targetExtensions = {
						".(a)", ".HE1", ".HE2", ".HE4",
					};
					
					try {
						
						for (const auto& entry : fs::recursive_directory_iterator(name)) 
						{
							if(!entry.is_regular_file())  
								continue;
								
							std::string ext = entry.path().extension().string();
							
							bool extensionMatches = false;
							for(const auto& targetExt : targetExtensions) {
								if(ext == targetExt) {
									extensionMatches = true;
									break;
								}
							}
							
							if(extensionMatches) {
								File file;
								file.path = entry.path();
								list.push_back(file);
							}
						}
					}
					catch(const fs::filesystem_error& e) {
						MessageBox(window.hwnd, L"Failed to open the specified folder!", L"Error", MB_OK | MB_ICONERROR);
					}
				}
				while(window.pollEvent(m))
				{}				
			}
			
			
			if(ID == 1012)//Remove all images
			{
				if(MessageBox(window.hwnd,L"Are you sure you want to remove all image based files from your queue list?",L"Are you sure?",MB_YESNO) == IDYES)
				{
					for(int a=0;a<list.size();a++)
					{
						if(list[a].path.filename().extension().string() == ".HE1" || list[a].path.filename().extension().string() == ".(a)")
						{
							list.erase(list.begin() + a);
							a--;
							
						}							
					}
					
				}	
				while(window.pollEvent(m))
				{}					
			}
			
			if(ID == 1013)//Remove all sounds
			{
				if(MessageBox(window.hwnd,L"Are you sure you want to remove all sound based files from your queue list?",L"Are you sure?",MB_YESNO) == IDYES)
				{
					for(int a=0;a<list.size();a++)
					{
						if(list[a].path.extension().string() == ".HE2" || list[a].path.filename().extension().string() == ".HE4")
						{
							list.erase(list.begin() + a);
							a--;
							
						}							
					}
					
				}	
				while(window.pollEvent(m))
				{}					
			}
	
			if(ID == 1014)//Remove all empty
			{
				if(MessageBox(window.hwnd,L"Are you sure you want to remove all empty files from your queue list?",L"Are you sure?",MB_YESNO) == IDYES)
				{
					for(int a=0;a<list.size();a++)
					{
						if(list[a].path.filename().extension().string() == ".HE3" || list[a].path.filename().extension().string() == ".HE0" || list[a].path.filename().extension().string() == ".HE7")
						{
							list.erase(list.begin() + a);
							a--;
							
						}							
					}
					
				}				
				while(window.pollEvent(m))
				{}	
			}
			
			if(ID == 1015)//Remove all
			{
				if(MessageBox(window.hwnd,L"Are you sure you want to remove all files from your queue list?",L"Are you sure?",MB_YESNO) == IDYES)
				{
					list.clear();
				}
				while(window.pollEvent(m))
				{}						
			}
			
			
			
			
			
			if(ID == 1051)//Set transparency Color
			{
				if(selected < list.size() && selected >=0)
				{
					//list[selected].options.push_back(L"");
				}
				
			}
			
			if(ID == 1052) // Set last room read
			{
				if(selected < list.size() && selected >=0)
				{
					
			//		list[selected].options.push_back(L"-end 80");
				}				
			}
			if(ID == 1053) // set first room read
			{
				if(selected < list.size() && selected >=0)
				{
			//		list[selected].options.push_back(L"-start 80");
				}				
			}
			
			///ETC.......
			
			
			//NON PARAMETER COMMANDS <><><><><><><><><><><><><><><><>
			if(ID == 1060)//Disable MetaData Ripping
			{
				list[selected].options.push_back(L"--nometadata");
			}
			if(ID == 1061)//Disable Log File Creation
			{
				list[selected].options.push_back(L"--disablelog");
			}
			if(ID == 1062)//Disable All Sound Ripping
			{
				list[selected].options.push_back(L"--nosound");
			}
			if(ID == 1063)//Disable Talk Subtitle Ripping
			{
				list[selected].options.push_back(L"--notlke");
			}
			if(ID == 1064)//Disable AKOS Image Ripping
			{
				list[selected].options.push_back(L"--noakos");
			}
			if(ID == 1065)//Disable AWIZ Image Ripping
			{
				list[selected].options.push_back(L"--noawiz");
			}
			if(ID == 1066)//Disable CHAR Font Ripping
			{
				list[selected].options.push_back(L"--nochar");
			}
			if(ID == 1067)//Disable DMU Sound Ripping
			{
				list[selected].options.push_back(L"--noextdmu");
			}
			if(ID == 1068)//Disable OBIM Image Ripping
			{
				list[selected].options.push_back(L"--noobim");
			}
			if(ID == 1069)//Disable RMIM Image Ripping
			{
				list[selected].options.push_back(L"--normim");
			}
			if(ID == 1071)//Disable All Ripping
			{
				list[selected].options.push_back(L"--norip");
			}
			if(ID == 1073)//Normalize Audio Output
			{
				list[selected].options.push_back(L"--normalize");
			}
			if(ID == 1075)//AKOS ONLY
			{
				list[selected].options.push_back(L"--akosonly");
			}
			if(ID == 1076)//AWIZ ONLY
			{
				list[selected].options.push_back(L"--awizonly");
			}
			if(ID == 1077)//CHAR ONLY
			{
				list[selected].options.push_back(L"--charonly");
			}
			if(ID == 1078)//DMU ONLY
			{
				list[selected].options.push_back(L"--dmuonly");
			}
			if(ID == 1079)//METADATA ONLY
			{
				list[selected].options.push_back(L"--metadataonly");
			}
			if(ID == 1080)//OBIM ONLY
			{
				list[selected].options.push_back(L"--obimonly");
			}
			if(ID == 1081)//RMIM ONLY
			{
				list[selected].options.push_back(L"--rmimonly");
			}
			if(ID == 1082)//SOUND ONLY
			{
				list[selected].options.push_back(L"--soundonly");
			}
			if(ID == 1083)//TLKE ONLY
			{
				list[selected].options.push_back(L"--tlkeonly");
			}
			if(ID == 1085)//Force internal audio format
			{
				list[selected].options.push_back(L"--decodeaudio");
			}
			if(ID == 1086)//Try Decode Only
			{
				list[selected].options.push_back(L"--decodeonly");
			}
			if(ID == 1087)//Force lined run length encoding
			{
				list[selected].options.push_back(L"--force_lined_rle");
			}
			if(ID == 1088)//Force unlined run length encoding
			{
				list[selected].options.push_back(L"--force_unlined_rle");
			}
			if(ID == 1089)//Force AKOS lined run length encoding
			{
				list[selected].options.push_back(L"--force_akos2c_rle");
			}
			if(ID == 1090)//Force AKOS unlined run length encoding
			{
				list[selected].options.push_back(L"--force_akos2c_bitmap");
			}
			
			


			
		}
		
		
		if(startedExport)
		{
			bool finishedExport = true;
			for(int a=0;a<processes.size();a++)
			{
				if(WaitForSingleObject(processes[a].hProcess, 0) != WAIT_OBJECT_0)
					finishedExport = false;
			}
			if(finishedExport)
			{
				MessageBox(window.hwnd,L"Export Complete!",L"Completion!",MB_OK);
				processes.clear();
				startedExport = false;
			}
		}
		
		
		
		
		window.clear();
		window.draw(back);
		int left = 50;
		int top = 0;
		int lastItem = 0;
		
		displayList(left,top,lastItem,MPosition,mousedown,text,screenWidth,screenHeight,removal,window,shift);
		displayList(left,top,lastItem,MPosition,mousedown,text,screenWidth,screenHeight,removal,window,shift);
		displayList(left,top,lastItem,MPosition,mousedown,text,screenWidth,screenHeight,removal,window,shift);
		displayList(left,top,lastItem,MPosition,mousedown,text,screenWidth,screenHeight,removal,window,shift);
		
		
		
		window.display();
	}
	return 0;
}