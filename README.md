# GoD Pokemon Stats Editor

An editor for Pokemon XD: Gale of Darkness's Pokemon Stats.csv table. Intended to be used with StarsMMD's GoD tool: https://github.com/PekanMmd/Pokemon-XD-Code

![Alt text](Screenshots/Default-Layout.png?raw=true "Title")

## Download

1. No installation is required to use this tool. Download the latest release from the releases page on github:
2. Extract the ZIP file and all its contents.
3. Run GoD-Pokemon-Stats-Editor.exe.

You can also build the project yourself with cmake.

## Usage

This tool is intended to be used with StarsMMD's GoD tool.

![Alt text](Screenshots/Usage-Guide.gif?raw=true "Title")

1. Navigate to File>Set Root Folder
2. In the open file dialogue, select the top level folder that the GoD tool creates (It should be the folder named "[your ROM's file name] GoD Tool", and will contain the "Game Files" and "Reference" folders
   -  Note that in order for the tool to load correctly the following CSV files must be encoded via the GoD tool:
      -  Pokemon Stats.csv
      -  Types.csv
      -  Abilites.csv
      -  Items.csv
      -  Moves.csv
3. If all the above CSV files are present and the root folder was set correctly, the Pokemon Stats editor UI will appear and be populated with the data from your Pokemon Stats.csv file
4. Note that this program will only modify the Pokemon Stats.csv file, and does not interface with your ROM at all. You will still need to decode the CSV file back into your ROM.

## Features

- Edit species data, Base Stats, Moves, and Evolution data for any Pokmeon

![Alt text](Screenshots/Beedrill-Example.png?raw=true "Title")

- Works with custom items, abilities, moves, and types

![Alt text](Screenshots/Custom-Moves.png?raw=true "Title")

- Customizable UI layouts and fonts

![Alt text](Screenshots/Customizable-Layouts-and-Fonts.gif?raw=true "Title")

- Dropdown menus are searchable

![Alt text](Screenshots/Filterable-Combo-Boxes.gif?raw=true "Title")

## Limitations

Many of these limitations I intend to fix in the future, but are either time consuming or reletively low priority, so don't expect them to be fixed anytime soon.

- Other CSV files such as the Trainer/Trainer pokemon data cannot be used with this tool. Since a Windows GUI for the original GoD tool is planned for release, I probably will not implement support for these other data tables.
- Although New pokemon, Items, etc are supported, modifying the number of columns per Pokemon, such as for adding custom TM learnset entries, is not supported. This is something I plan to add in the near-ish future.
- Additional Rows for new pokemon must be created outside of the tool, and then loaded in. There is no way to add rows to the Pokemon Stats file inside the tool.
- Although Pokeface portraits are shown, this data cannot be changed as it is not pulled from the game files and is instead packaged with the program. This is something I plan on fixing in the near-ish future.
- Not every field in the Pokemon Stats CSV is editable. I only included the fields that I felt were the ones I modified the most often. If there are any common fields I missed let me know and I will likely add them.
- This project is currently windows only, since OSX already has a GUI tool, and there is no linux release for the command line GoD tool. However, every library used in this project is cross platform, so if there is demand for a release on other platforms I may do so in the future

## Known Issues

- Many of the provided fonts will not display Nidoran♀ and Nidoran♂'s names correctly. This is because most monotype fonts do not include the ♀ and ♂ characters. This does not affect the re-encoded Pokemon Stats.csv file. The the provided CascadiaCode fonts will display this correctly.
- All fonts in the fonts folder are loaded into memory for the entire duration of the tool runtime, so be careful about adding too many fonts to this folder.
