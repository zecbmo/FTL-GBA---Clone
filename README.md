# FTL-GBA---Clone

The Code here is old First year work and horrible to look at these days.
But anyone interested in seeing how GBA programming works might value from it.

#Old Readme

FTL: A GBA SLIMLINE Clone Author: Zecbmo version 0.1
TLDNR: This is a quick game I made for a school project after only coding for 6 months. It in no way lives up to the real FTL but serves as an example of a port on to an old bit of hardware. This old hardware caused its fair share of problems to solve and hindered in ways what I wanted to do/emulate of the real FTL.
Contents

1A. Game info and differences 1B. Controls 2. Reading the source code/Making the GBA rom yourself 3. Future 4. Credits


1A. /////////////////// Game info and differences //////////////////////////////////////////////////////////


So anyone playing this sound have a good grasp of FTL and the way it is played.
For this port, it has some differences: You only have 2 weapons. Instead of getting new ones these can be upgraded. You no longer control power, rather you can upgrade the rooms instead. (if they are damaged, they still will lose power) Currently there is only a Captain on each ship. There is no map. You jump automatically from one encounter to the next. You visit the shop/upgrade screen after every encounter. There is no fuel/missles to worry about.... yet. There is only one encounter, which is fighting (no random encounters with rock people or Giant spiders)
Some of these differences were due to not having long enough to implement them. Some were related to the GBA hardware. (mostly this was not having enough. most GBA hardware problems could be overcome with some tinkering/inginuity)
Alot of the issues were caused by my inexperience as a programmer. I have only been programming a total of 6 month so still getting the hang of it.


1B. Controls ///////////////////////////////////////////////////


A controller or real GBA is reccomended as you need shoulder keys

D-pad controls the main cursor A moves player to where the cursor is pointed at

L/R controls the missle and plasma cursor respectively A to fire whilst L/R is held and the weapon is charged

In the upgrade menu. A to buy upgrade B to upgrade health start to move to next encounter

2.//////////////// Reading the source code/Making the GBA rom yourself /////////////////////////////////////////////////////////


If you want to have a look/edit the source code start off with looking at the main.cpp Files are labed as approrpriate and you should be able to find everything within the source folder.

To compile this, you need to use devKitPro. It is included as /gba700. Move this folder to the root of your c drive i.e c:\gba700

To compile using notepad++. Whilst the source code is open e.g main.cpp or functions.cpp hit run and type C:\gba700\RunMake "$(CURRENT_DIRECTORY)" run

To compile using other methods please read the read me file within the gba700 folder


///////////// Credits ///////////////////////////////////////////////

Within this game i have used Adam Sampsons gba.h/template and makefile with expressed permission to share and edit freely.
