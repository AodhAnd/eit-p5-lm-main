# AAU-EIT5: Lawn mower project core
AAU Electronics and IT students' 5th semester project (2015)

Associated report is there: https://github.com/AodhAnd/eit-p5-lm-report

This resources and report can be of help for people willing to learn basics of system modelling and automation, signal processing or communication in the context of an applied (but simple) project. It is designed and written as if we were designing a lawn mower's trajectory control.

/!\ Disclaimer: please be reminded that this is a scholar project. As such, it is mainly aimed at proving that team members were able to apply knowledge from various courses we had at the university and with tools and material that were available to us.
We are not responsible for anything that could happen, this is just our will to share knowledge we have gained from our experience and gathered in a (not so short) report.

## Repository hierarchy
In this repository stands:
* A LaTeX template for supervisor meetings (under meetings/)
* Tests : plotting and testing code and pictures (under tests/)
* Simulations and values sheet (under simulation/)
* Third party code used in our project (under GoT/ for the Games on Track SDK)
* The project code itself (to be added under drivers/)
* Circuits schematics (under schematics/)

## Drivers
Please don't do "driverxx_old" naming, git is here for version control and history.
A few versions will be saved whenever concrete improvements have been made to the code.

## Rules when running a test :
1 Create a folder under test/ with an explicit name. 
2 The latter should use camel case with first letter being small.
3 Organize this folder as follows :
  * arduino/  -> all the arduino code necessary to run this test including drivers as is at the moment the test is performed
  * matlab/   -> all matlab scripts and extracted data from the test (under matlab/data/)
  * pictures/ -> photos, graphs and drawings related to that test
Main project material can be found [here](https://github.com/AodhAnd/eit-p5-lm-main)

