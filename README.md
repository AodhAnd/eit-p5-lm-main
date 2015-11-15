# AAU-EIT5: Lawn mower project core
AAU Electronics and IT students' 5th semester project (2015)

## Repository hierarchy
In this repository stands:
* A LaTeX template for supervisor meetings (under meetings/)
* Tests and simulation code and pictures (under tests/)
* Third party code used in our project (under GoT/ for the Games on Track SDK)
* The project code itself (to be added under drivers/)
* Circuits schematics (under schematics/)

## Drivers
Please don't do "driverxx_old" naming, git is here for version control and history.
A few versions will be saved whenever concrete improvements have been made to the code.
[Since a lot of different and obscure folders are present in the drive currently, I will contact every one of you who knows shit about it to chose which should be kept and put into this git repository and which shouldn't. 
Don't worry special rules for drivers will come after that. ;p
Until then, please try to clean up a bit stuff you know aren't useful anymore in the shared drive folder to facilitate the work of everyone.]

## Rules when running a test :
1 Create a folder under test/ with an explicit name. 
2 The latter should use camel case with first letter being small.
3 Organize this folder as follows :
  * arduino/  -> all the arduino code necessary to run this test including drivers as is at the moment the test is performed
  * matlab/   -> all matlab scripts and extracted data from the test (under matlab/data/)
  * pictures/ -> photos, graphs and drawings related to that test
