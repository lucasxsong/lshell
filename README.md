# Command Shell Program

## Summary:

This program attempts to recreate a command shell with a handful of basic executable commands. These commands include: `echo`, `cd`, `ls`, `mkdir`. The user is capable of inputting a command along with an argument, and the program should output a proper response. Not only this, commands can be linked together with a number of "connectors," (`&&`, `||`, `;`) each with their own functionality.


- `&&` - executes the following command if the previous command succeeds
- `||` - executes the following command if the previous command fails
- `;` - executes the following command regardless of whether or not the previous command has failed or succeeded


## Known Bugs:
//follow this structure for now:
-Short description of bug-

**Solution:** (if there is one)


## Note from the author:
As of the current state of the Command Shell Program, it is limited in its functionality. **HOWEVER** we have planned and designed it in such a way that allows for additional functionality to be implemented as we are given feedback in the future.

**[Thanks for reading!](https://humorside.com/wp-content/uploads/2017/12/thank-you-meme-02-1.jpg)**

# ----- END OF NEW README... for now...

# Assignment 1 -- Creating a Design Document

**Note: All assignments must be done with *exactly* one partner.**

## Introduction
As programmers it is tempting for us to get our hands dirty with code immediately after receiving the specs. In any complex software development, there are many moving parts and pieces that can quickly turn out project into spaghetti code. It is imperative that before we open vim we take a step back, plan out the code we are going to write, and create a design to follow. One tool software engineers use for this is Unified Modeling Language (UML) which help visualize our project’s architecture. In this assignment you will create a design document to map out your first coding assignment, Assignment 2. This will include a simple UML diagram to represent your components and their dependencies. You can [read more about creating UML diagrams from this slide deck](https://docs.google.com/presentation/d/12gFQDxn4T0sXfXiuGIiW5OlUfgKW85e86UbnR59gMdc/edit?usp=sharing).

## Assignment
Your assignment is to write a design document that you will use for reference when developing your Assignment 2 submission. It’s purpose is as an exercise to get you to start designing before you start coding. Like any good agile method, what you write in the design document is a starting point for your design, not a road map that you must rigidly follow (because that would be waterfall development, and this is not a government project). You should create a document with the following sections

- **Title Page:** including the title “Assignment 1: Design”, the date, the quarter and year, and the authors names
- **Introduction:** Give a brief overview of your design
- **Diagram:** This will be the UML diagram for your system, and should show all classes you plan on developing. This diagram can take up multiple pages if necessary.
- **Classes/Class Groups:** descriptions of each class/class group that you plan on developing, this can be as simple as a description of what each class accomplishes and how, or a pseudo code level class definition. A class group would be a group of classes that all inherit from a single base class (composite classes are an example). For class group give a description of the base class, as well as the subtle differences between the child classes. Make sure to describe any key design choices, such as why you chose certain containers for key data members, why a class needs to pointer member to another class, or how a key function will generally be written
- **Coding Strategy:** how you and your partner plan to break up the work, who will be in charge of which segments and how you will integrate the segments together
- **Roadblocks:** issues that you think will arise during development and what strategy you will use to overcome them

When you create your design document, do not think only about the current assignment. Think about how you would also extend the assignment to have new functionality (an important exercise in software construction, as new functionality is almost always necessary).

Please  use some drawing program to create your UML diagram. UML diagrams that are drawn by hand and scanned/photographed and added to your design document will not be allowed. Programs such as GIMP, GraphViz, or even Google Docs should be capable of creating these diagrams.

## Submission
Submit your design document as a single PDF to your groups GitHub repo.

## Grading
Your documents will be graded using the following breakdown

|Points|Section|
|:---:|:---|
| 40 | UML Diagram |
| 30 | Class Descriptions |
| 20 | All Other Sections |
| 10 | Structure |
|**100** | **Total** |
