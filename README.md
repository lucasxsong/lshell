# Command Shell Program

## Getting Started:

To start using this simple bash clone, simply clone the repository into your desktop. Simply cd into the folder and run the precompiled executable through your machine's terminal/command prompt.

```
cd assignment-1-raya-playa
./rshell
```

If this command doesn't work, you might need to recompile the object file.

```
cd src
g++ Shell.cpp Input.cpp -o rshell
```

This will cd into the src directory to recompile the program with files Input.cpp and Shell.cpp into executable rshell, which can be run by the command below (same as above)

```
./rshell
```

Once the program has successfully compiled, you should see an updated command prompt with your local system and current user logged in. This means that you have successfully compiled and run the rshell program. Feel free to experiment with basic bin commands that will be covered in the next section.

However, if the program does not successfully compile, check the repo to make sure that all files have been properly cloned and that you 

## Summary:

This program attempts to recreate a command shell with a handful of basic executable commands. These commands include: `echo`, `cd`, `ls`, `mkdir`. as well as any other commands that are located in bin. In addition, our R'shell has added implementation for `test`, a function to check if the path to a file or directory exists. 

The user is capable of inputting a command along with an argument, and the program should output a proper response. Not only this, commands can be linked together with a number of symbols (`&&`, `||`, `;`, `()`) each with their own functionality.


- `&&` - executes the following command if the previous command succeeds
- `||` - executes the following command if the previous command fails
- `;` - executes the following command regardless of whether or not the previous command has failed or succeeded
- `#` - marks any text up to the next connector as a comment. The system will not execute any "executables" that is tagged as a comment.
- `()` - executes the command enclosed in the parenthesis before other commanmds.

For the instance where there are multiple arguments separated by multiple connectors, the program constructs an argument tree with the executables acting as the leaf nodes and the connectors acting as nodes with two children. These children either point to other connectors or executables. The tree is constructed as a right oriented binary tree, and calling execute on the head of the tree will call execution of the child nodes based upon the connectors binding them.

This structure allows for the ability to easily add custom executables to your custom preferences by creating new baseExec* objects in BaseNode.h and adding a section in Input.cpp to match userInput with your new function.

## User's Manual

### Test
This command allows you to test if a particular path or file exists in the repository that is it called in.

### Usage
Call the function by typing `test` followed by any flags you wish to call and the file/path you wish to test.
`-e` checks if the file/directory exists
`-f` checks if the file/directory exists and is a regular file
`-d` checks if the file/directory exists and is a directory

The function returns `(True)` if the file/path exists and `(False)` if the file/path does not exist.

*Note:* You can also call the test function by encapsulating the flag and file/path you wish to test as follows [ -e file/path]

## Known Bugs:
"Out of order"
- Known bug that when flags might be entered out of order, rshell will not be able to compile the command successfully as the flags intended.
- Ex: rm dirName -r != rm -r dirName

"Calling Exit"
- The current exit object, when executed, just modifies a global variable "extern bool exitBool" to stop the input loop. This is a little bit of a shortcut that will be changed to a more graceful call in following versions.

~~"Comments"~~
- ~~As of current release, rshell does not store comments as a specific data member. We are working a solution to have comments parsed separately and stored in a data member of the baseExec function.~~
- Bug has been fixed as of release assn3


## Note from the author:
As of the current state of the Command Shell Program, it is limited in its functionality. **HOWEVER** we have planned and designed it in such a way that allows for additional functionality to be implemented as we are given feedback in the future.

**[Thanks for reading!](https://humorside.com/wp-content/uploads/2017/12/thank-you-meme-02-1.jpg)**
