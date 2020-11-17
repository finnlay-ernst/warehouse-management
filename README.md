# COMP3600 Final Project
Finnlay Ernst u6380455

## File Structure
`bin` - .o files for compilation <br>
`src` - All source code and headers <br>
`test-gen` - Programs used to generate test data (of no use to markers) <br>
`tests` - Test input data files, catagorised under `f1`, `f2`, and `f3` <br>

## Compilation & Execution
Tested on Windows 10 Home edition. <br>

Built using c++11, tested compiling with [MinGW](http://www.mingw.org/) <br>

Can be compiled manually but recommend using [make](https://www.gnu.org/software/make/), in the root directory run:<br>
`make`

Execute the exe passing in run type and file. Valid executions include: <br>
`./main F1 tests/f1/test-f1-1.txt` <br>
`./main F2 tests/f2/test-f2-1.txt` <br>
`./main F3 tests/f3/test-f3-1.txt` <br>
`./main normal data.txt` <br>
Running `main` with F1, F2 or F3 as inputs allows the user to test the 5 provided test files for each of the functionalities.<br>

Any input for the first argument other than F1, F2 or F3 will result in normal execution where the user will interact with the application as an interactive commandline application. `data.txt` has been provided as a starting database, changes to the data will be saved to this file when you exit the program (you must properly exit by pressing esc followed by enter) . In this mode supported interactions are as below.

<br>

---

<br>

## Supported Interactions 
| CMD Input 	| Args 	| Function 	| Example |
|-	|-	|-	|-	|
| `find` 	| SKU: single integer 	| Attempts to find that item and print it out 	| `find 6311000` |
| `insert` 	| SKU: single integer<br> Item Name (with underscores for spaces): string<br> Initial Stock Count: single integer<br> Fixture Location X: single integer<br> Fixture Location Y: single integer 	| Attempts to insert an item into the tree	| `insert 6311000 Colgate_Toothbrush 35 5 10` |
| `update` 	| SKU: single integer<br> New Count: single integer 	| Attempts to find the item and update that items stock count to the provided number 	| `find 6311000` |
| `remove` 	| SKU: single integer 	| Attempts to remove item from tree 	| `remove 6311000` |
| `path` 	| SKUs: up to 20 integers space seperated 	| Returns list of fixture locations in the optimal order for collection 	|  `path 6311000 1234440 2199836 2900114 2733380 6122660` |
| `priority` 	| SKUs: 2 integers representing lower & upper bound of sku range 	| Returns ordered list of items according to stock count (lowest first)	|  `priority 4000000 5000000` |
Entering more arguments than indicate here will result in additional arguments being ignored
