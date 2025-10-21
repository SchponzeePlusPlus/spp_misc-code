# Notes_Gen.md

## Log

### 2025

#### 2025/10

##### 2025/10/21

###### 08:00

Things i can do to further clean the code:
- note: do easier stuff first before more significant changes
- any simple unassign functions, like for enums, replace with = 0; when it would be called
- condense the shift from 2 move check to 1 move check (refer to local issue #18)
- instead of creating possibilities raw array and then copying valid combos to possibilities vector, just make the possibilities vector, and erase any nonvalid combos as they are processed
- put i and j loop before k loop (when k is index 2 or beyond) when resizing and refilling combo list array 
- merge resize and fill operations if possible?
- instead of the combo count objects, just resd size of l dimension when needed
- combo list vector does not need that enum and therefore doesn't need a struct, so data type can be simplified
- can i make i and j in the multi dim vectors std array instead of vector? i can define size during declaration and not worry about i and j resizing, the only concern is where the memory gets stored?
- do i need enums at all? i think structs and enums might not be necessary for this challenge as per company software engineering manager saying that this problem doesn't need object oriented programming
  - saying that, do i need the enum and safe check when checking shift in array?
- delete print procedures at the end of this solution attempt, when diagnostics is no longet needed
- would classes help clean my code?

##### 2025/10/18

###### 13:53

- Make a vector for list
- vector of a struct, struct which contains char pos and enum to say whether current combo has been calculated
- make a vector for 2 pos buffer
- maybe an i x j (2d) array of counts of combos for each combo

#### 2025/09

##### 2025/09/29

###### 15:10

- Things I can do going forward with attempt no. 2:
	- check memory available, especially in functions (stack) and heap usage
	- reduce reliance on large arrays that consume so much memory, rely more on a "real-time" buffer
	- advanced data structures and algorthms, would using them be more efficient (e.g. linked lists)?
	- conform sw dev conventions to make code readable and peer-reviewable, this includes modularity and naming conventions
	- maybe output results to a .csv and/or log file, reduce noise in the console and save results better!
	- Other C++ things I could do for improved quality code?
		- Better memory management? (garbage collection?)

##### 2025/09/27

###### 18:17

...
	AAAA
	AAAB
	AAAC
	AAAD
	AAAE
	AAAF
	AAAH
	AAAI
	AAAJ
	AAAK
	AAAL
	AAAM
	AAAN
	AAAO
	AAA1
	AAA2
	AAA3
	AABA

	kind of like a base 17 numbering system

##### 2025/09/22

###### 16:58

Approach:

- Maybe start out with something quick and easy, like an array of all possible combinations, then filter as needed
- Follow up with a linked-list attempt or some other advanced data structure and algorithm