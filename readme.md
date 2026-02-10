# HEErip GUI
* A GUI interface(Made by Me) for the commandline utility HEErip(Made by suppertails66).
* HEErip is a Humongous Entertainment File Ripper.
* HEErip GUI offers all of the options available in HEErip console.
## Dropdown menu structure:

### File
* Export - Initiates Concurrent conversion of all files in queue.(This will open up a console process for every file)
* Exit - Quits the program
### Manage
* Add File - Opens OpenFile Dialog and adds the single selected item to your list of queued files. 
* Add Folder - Opens an openfolder dialog and subsearches the selected folder till all relevant sub-files are found.(sometimes slow) 
* Remove All Images - Removes from the file queue all file types that typically contain images for the most part.
* Remove All Sounds - Removes from the file queue all file types that typically contain sounds for the most part.
* Remove All Empty - Removes from the file queue all file types that typically cannot be converted and only output nothing.
* Remove All - Removes all file types from the queue.
### Options - (And equivalent console commands)
* Set Transparency Color
```
	-alttrans <val>
		Specifies an alternate transparency index color (0-255, decimal). This specifies the background color of all extracted images. If not overriden, this will be set to the TRNS value given in the LFLF header, which as far as I know is universally set to 5 and is almost always a shade of medium pink (#AB00AB or something close to it).
```
* Set Last Room Read
```
	-end <val>
		Sets the number of the last room to read and rip. By default, rooms will be read until the end of the file.
```
* Set First Room Read
```
	-start <val>
		Sets the number of the first room to read and rip. Default is 0. Note that under rare circumstances this can affect file decoding -- see notes in (file readmeConsole.txt).
```
* Set Buffer Byte Count
```
	-bufsize <val>, -b <val>
		Sets the size of the file read buffer in bytes. Default value is 64000000 (about 64 megabytes).
```
* Set First Byte Decoder
```
	-decode <val>, -d <val>
		Sets the first byte to try to use to decode the file (0-255, decimal). Default value is 105. Decoding is a simple byte-by-byte XOR against this value. If decoding fails, other known encodings will be tried before giving up.
```
* Set Ignore Trailing Bytes in Sound
```
	-ignoreend <val>
		For audio files, sets the number of trailing sample bytes to ignore. Default is 0.
```
* Set Init Bytes In Sound
```
	-ignorestart <val>
		For audio files, sets the number of initial sample bytes to ignore. Default is 0.
```
* Disable MetaData Ripping
```
	--nometadata
		Disables logging of metadata (TRNS indexes, OBNA object names, SP2C dates, SPLF filenames, CLRS color compression strings, SEQI animation names).
```
* Disable Log File Creation
```
	--disablelog
		Disables writing of the log file.
```
* Disable All Sound Ripping
```
	--nosound
		Disables DIGI, TALK, WSOU, and external DMU file sound ripping.
```
* Disable Talk Subtitle Ripping
```
	--notlke
		Disables TLKE subtitle ripping.
```
* Disable AKOS Image Ripping
```
	--noakos
		Disables AKOS image ripping.
```
* Disable AWIZ Image Ripping
```
	--noawiz
		Disables AWIZ image ripping.
```
* Disable CHAR font Ripping
```
	--nochar
		Disables CHAR font ripping.
```
* Disable DMU Sound Ripping
```
	--noextdmu
		Disables external DMU file sound ripping. When ripping 3DO HE1 files, the program will by default check to see if any files matching the names in the music file list exist in the input directory and try to rip them if they're present. Invoking this parameter disables this behavior.

```
* Disable OBIM Image Ripping
```
	--noobim
		Disables OBIM image ripping.
```
* Disable RMIM Image Ripping
```
	--normim
		Disables RMIM image ripping.
```
* Disable All Ripping
```
	--norip
		Disables all ripping, though the input file will still be read. Primarily for testing.
```
* Normalize Audio Output
```
	--normalize
		Normalizes audio before output (amplification to maximum level, no centering).
```
* Set AKOS Only
```
	--akosonly
		Only rips akos files.
```
* Set AWIZ Only
```
	--awizonly
		Only rips awiz files.
```
* Set CHAR Only
```
	--charonly
		Only rips CHAR files.
```
* Set DMU Only
```
	--extdmuonly
		Only rips DMU files.
		
```
* Set MetaData Only
```
	--metadataonly
		Only rips metadata.
```
* Set OMIM Only
```
	--obimonly
		Only rips OBIM files.
```
* Set RMIM Only
```
	--rmimonly
		Only Rips RMIM files.
```
* Set Sound Only
```
	--soundonly
		Only rips sound files.
```
* Set Subtitles Only
```
	--tlkeonly
		Only rips subtitles.
```
* Force Internal Audio Format
```
	--decodeaudio
		Forces decoding of audio to internal format, even when unnecessary. Specifically, at least one game (Backyard Basketball) uses standard RIFF WAVE files to store its audio data. By default, HEErip will simply copy these as-is. If this parameter is set, the program will instead decode the audio into its internally-used representation before outputting it. This causes a substantial hit to performance and discards any file metadata, so you shouldn't use it unless you need it. Note that this operation is necessary for audio normalization and will be activated automatically if the --normalize parameter is invoked.
```
* Try Decode Only
```
	--decodeonly
		Causes the program to try to detect the input file's encoding, and if successful, to decode and output the file.
```
* Force Lined Run Length Encoding
```
	--force_lined_rle
	--force_unlined_rle
		Force the RLE encoding method hack to a specific setting. In 3DO games, BMAP/SMAP encodings 8 and 9 specify an image with simple 8-bit run-length encoding. In later non-3DO games, however, they instead specify a line-by-line RLE8 format, where each row of the graphic's data starts with a 2-byte line byte count. The program works around this change in semantics by checking the format of the first 10 such images and using the majority encoding, but the checking algorithm is not foolproof. Although this works for all games I've tried, it's theoretically possible that for some game some images might be incorrectly detected, causing them to get ripped using the wrong method. In this case, you should use one of these parameters as appropriate to make sure this data is ripped correctly.
		Long story short, you should never need this, but it's here if you do :)
```
* Force Unlined Run Length Encoding
```
See above...
```
* Force AKOS Lined Run Length Encoding
```
	--force_akos2c_rle
	--force_akos2c_bitmap
		Same as the above, but for pseudo-2-color AKOS encoding used in some games. There are two possible types, one RLE-based and one bitstream-based, with no difference in semantics (that I know of). All games that I've tested rip correctly, though you may see some nasty warning messages -- see "Known Issues".
```
* Force AKOS Unlined Run Length Encoding
```
See Above...
```

```

== Supported Formats ==
HEErip supports the following data file types used in Humongous games:

HE1/(A)/(B): Data file. Contains graphics, sounds, etc. Early games use a .HE1 extension, later games use .(A) and sometimes a secondary .(B) file.
HE2/TLK: Speech file. Contains most or all speech. Early (DOS) games use .TLK; everything else uses .HE2.
HE4: Music file. Contains most or all music.
DMU: 3DO music file. One track per file.

Most of these files contain a dizzying array of sub-formats. HEErip recognizes all of the following and refers to them when naming its output files:

AKOS: animation format used in all games
APAL: palettes; if a room has more than one palette, all of that room's graphics will be ripped using each one
AUXD: actually a subformat of AKOS; used for fullscreen animations in Freddi Fish 1/Putt-Putt Zoo
AWIZ: multipurpose graphics format introduced in Freddi Fish 1/Putt-Putt Zoo
CHAR: fonts
DIGI: sound container (8-bit unsigned PCM)
DMU: music format in 3DO games
OBIM: object image format used heavily in early games, less so in later
RMIM: room backgrounds
SONG: DIGI/WSOU container
TALK: speech container (same as DIGI, differs only by header label)
TLKB: TALK/WSOU container
TLKE: subtitle format used in a few later games
WSOU: general sound container for later games

== Unsupported Formats ==
- MIDI. Used for music in DOS-era games.
- Non-TLKE subtitles. For the vast majority of games, subtitles are embedded directly in the scripts, which I have no intention of trying to deal with.
- CUP files. Apparently some sort of special format for self-playing demos, but I haven't really investigated. If it uses similar formats to regular games, I might add support for it someday.
- Anything from non-SCUMM games (Pajama Sam 4, any Backyard game from the last decade, etc.)

== Known Issues ==
- Miscolored AKOS, AWIZ, etc. in some games; for example, every AKOS in room 0 of Let's Explore the Airport, the AUXD avalanche sequence in Putt-Putt Zoo, and pretty much every AWIZ in room 26 of Backyard Football. To the best of my knowledge, this is caused by the game loading new palettes during gameplay and depending on them to color graphics. There's no way of telling which palette goes with what without running every script, at which point you're essentially running the game. That ain't happening in this program.

- CHAR fonts don't use correct palettes. This is because CHARs don't have their own palette -- in most cases, they're meant to be colored according to the source of a subtitle line, so there's no "default" palette that can be used to represent them. The palette used for ripping consists of arbitrary grayscale colors, but should preserve distinct tones while making the general design of each character obvious in most cases.

- In Freddi Fish 1, using the -start parameter to start ripping at certain high room numbers (at least 30) can cause some graphics to be incorrectly ripped. As discussed under "Usage" in the section on --force_akos2c_rle and --force_akos2c_bitmap, some games contain differences in the semantics of certain formats, and Freddi Fish has the distinction of being the only game to actually use both at the same time. Although the program will usually detect this and switch to the correct encoding as necessary, the wrong default encoding gets set when starting from higher room numbers. To avoid this, always rip from the first room, or use the aforementioned parameters to force the encoding. If everything is working correctly, you should see a slew of warning messages at the very end of the ripping process.

== Notes ==
- When ripping a 3DO HE1 file, the program will check the input directory for any DMU files referenced in the HE1 and rip them automatically if present. However, several games actually contain apparently unused DMU files that aren't referenced by the game data. You should run these through the program separately in order to rip them. 
On top of that, at least one game (Putt-Putt Moon) references a file that's actually not on the disc at all, so you'll get an error message for it no matter what.

- One of the speech clips in Fatty Bear's HE2/TLK file, the line "Dear me" from the Veggie Head minigame (TALK 214 in the Windows version), contains a unique chunk used to clip the line before the whole sound has played. This causes the second part of the line, "I am a sight", to never play in-game despite showing up in the subtitles. The program deals with this by appending the extra data to the rest of the sound, since they're clearly meant to go together. Why this is done exactly once in Fatty Bear and never again is quite beyond me.

- Some games have consistent pops or clicks at the beginning of their music files (e.g. Pajama Sam, most 3DO games). These are part of the sound data and are ripped exactly as they play in-game. If you want to get rid of these, you should run the program with the -ignorestart parameter. Ignoring the first 256 bytes works for Pajama Sam, while 3DO games seem to be either 4 or 8 bytes.

== Compatibility List ==
The following games have been tested and should rip completely and without error (except as noted under "Known Issues"). All entries refer to the original English-language Windows CD release unless otherwise stated.

Backyard series
	Backyard Baseball
	Backyard Soccer
	Backyard Football
	Backyard Basketball

Big Thinkers series
	Big Thinkers Kindergarten
	Big Thinkers First Grade
	
Fatty Bear series
	Fatty Bear's Birthday Surprise (DOS, Windows, 3DO)
	Fatty Bear's Activity Pack (3DO)
	
Freddi Fish series
	Freddi Fish and the Case of the Missing Kelp Seeds
	Freddi Fish 2: The Case of the Haunted Schoolhouse
	Freddi Fish 3: The Case of the Stolen Conch Shell
	Freddi Fish 4: The Case of the Hogfish Rustlers of Briny Gulch
	Freddi Fish 5: The Case of the Creature of Coral Cove
	Freddi Fish and Luther's Maze Madness
	
Let's Explore with Buzzy the Knowledge Bug
	Let's Explore the Airport
	Let's Explore the Farm
	Let's Explore the Jungle
	
Pajama Sam series
	Pajama Sam: No Need to Hide When It's Dark Outside
	Pajama Sam 2: Thunder and Lightning Aren't So Frightening
	Pajama Sam 3: You Are What You Eat From Your Head to Your Feet
	Pajama Sam's Sock Works
	Pajama Sam's Lost and Found

Putt-Putt series
	Putt-Putt Joins the Parade (DOS, Windows, 3DO)
	Putt-Putt Goes to the Moon (DOS, Windows, 3DO)
	Putt-Putt Saves the Zoo
	Putt-Putt Travels through Time
	Putt-Putt and Pep's Balloon-O-Rama
	Putt-Putt and Pep's Dog on a Stick
	Putt-Putt Enters the Race
	Putt-Putt Joins the Circus
	
Spy Fox series
	Spy Fox in Dry Cereal (U.S. and U.K. editions)
	Spy Fox 2: Some Assembly Required
	Spy Fox 3: Operation Ozone
	Spy Fox in Hold the Mustard
	Spy Fox in Cheese Chase
	
Other
	Putt-Putt and Fatty Bear's Activity Pack
	
Demos
	Too many to list, but any non-CUP demo included with any of the above games should work. Note that several demos, such the "updated" Pajama Sam demo included with some newer games, contain incorrectly formatted or incompletely removed data that can result in non-fatal errors.


 
```

#### HEErip GUI uses a queue based list. As such, each file will have it own process. Because it has it's own process, you can apply options specifically to each file by selecting that file(by clicking on it's name in queue) and selecting one of the options on the dropdown menu "Options". 


