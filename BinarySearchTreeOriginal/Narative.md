# Overview
I want to improve on my ability to make more efficient code. I believe that there is waste in this code that could be fixed in order to make it parse quicker than it currently does.
# Review
This artifact is  a binary search tree. It is a program that parses through a csv to be able to pull, edit, remove, and add in new information. The biggest part of this program is the switch case method that allows the user to select and review the objects in the binary search tree. The other main part is the ability to load a csv into a custom struct using  vectors. This was created by me around 2 years ago, my second year in college. I would say that I have grown a lot as a developer and person since that time.

This artifact would not build when I had originally submitted it. It had all the necessary methods for the project, but it was missing a few things to get it to compile properly. I chose to redo this artifact because I knew that it could be upgraded in the switch case statement, the commenting was inconsistent and that I wanted to be able to get the program to compile. 

I improved the artifact by adding consistent and detailed comments, adding in a default case in the switch method and changing the methods included in the artifact. I removed the preorder and postorder methods because they were not being utilized, and they were just taking up space. I also added in a removeNode method that allowed the program to compile. Before I did that, I was getting a linker issue that I could not resolve. I did not make any changes to the actual data structure other than making new comments, but I did change several of the methods that utilize the binary search tree structure.

I believe that I did reach the goals that I had set for this artifact. I believe that I have achieved these course outcomes:

- Employ strategies for building collaborative environments that enable diverse audiences to support organizational decision making in the field of computer science
- Design, develop, and deliver professional-quality oral, written, and visual communications that are coherent, technically sound, and appropriately adapted to specific audiences and contexts
- Design and evaluate computing solutions that solve a given problem using algorithmic principles and computer science practices and standards appropriate to its solution, while managing the trade-offs involved in design choices (data structures and algorithms)

To complete this artifact, I actually had to switch from the eclipse IDE to visual studio because of issues that I encountered with the MinGW package that was supposed to have a GCC compiler that it did not. This meant that I had to import the project into visual studio. I had a difficult time trying to understand the linker issue because of the  large scope of that error message. While doing these upgrades, I learned a lot about error messages and compiler issues.
