# README.md

GitHub

User: SchponzeePlusPlus

Repository: spp_misc-code

C/Cpp/Exercises/exercise_20250922_1314/README.md

## Exercise Description

### Context

Email received 22-Sept-2024 at 13:15:

Hi (Applicant), 

Thank you for your application for the Software Engineer position advertised on (job ad board).

We would like to progress your application. The next step in our hiring process is to ask suitable candidates to attempt a coding challenge.

Please take your time with it and submit it once you're happy. I would rather see your best work a week from now than something rushed. 

Your code should output a number. If you get the correct number, I will pass your code to the software team to review. If they like your solution, I will arrange a session where you can take us through it in detail. We do this with all our software candidates. The idea is to help us understand how you code, how you approach abstract problems, and how you respond to peer reviews (as well as getting to know you a bit better).

When you submit your solution, please remember to include a brief statement outlining how you approached the problem etc. 

Feel free to reach out if you have any questions about (Company), the role, or the coding challenge etc.

(End of email)

### Exercise: Keyboard Knights Coding Challenge

#### Your challenge

Calculate the total number of valid 10-key sequences, given these constraints:

- sequences can start at any key
- each subsequent move must be a knight move
- no more than 2 vowels per sequence
- repeat keys are allowed
- no topological wrapping of keyboard
 
For example, BKHOHKBILC is one of the many valid 10-key sequences that meets all the constraints.
 
Your challenge is to write a program that prints the total number of valid sequences.
 
Keyboard layout:

[A]  [B]  [C]  [D]  [E]

[F]  [G]  [H]  [I]  [J]

[K]  [L]  [M]  [N]  [O]

     [1]  [2]  [3]

#### How to submit your solution

- (Company)’s preferred language is C++. Please:
    - Use a single .cpp file with compilation command (either GCC or clang) in a comment at the top of the file
    - Compile with -Wpedantic and as recent a version of C++ as you like, e.g., -std=c++23
- Write simple code that is ready to be peer reviewed
- Please include the following in your covering email:
    - Your full name and a mobile phone contact number.
    - Your current citizenship or visa status, e.g., Australian Citizen, Australian Permanent Resident, Temporary work visa etc.
    - An argument, about one paragraph long, describing why your code is correct and fit for peer review.
- Submit your code below


### Email Enquiry for Further Clarification

Answers to some questions that I asked in an email exchange:

Q: When the challenge says 'knight move', does it mean a chess knight move (e.g. 2 up/down/left/right then 1 in a 90 degree turn)?

A: Yes, it does.

Q: When the challenge says 'no topological wrapping of keyboard', does it mean that the program's chess knight moves across the keyboard are constrained by the physical boundaries of the keyboard shown in the challenge?

- The chess move cannot continue across from right-to-left, left-to-right, bottom-to-top, or top-to-bottom boundaries?

A: Yes, pieces are physically constrained.

Q: Should I make any assumptions about the target hardware?

- Is this challenge testing my C++ memory management, or should I just worry about the algorithm itself? 
- E.g. Is the target hardware a theoretical physical keypad security system?
    - Limited volatile and non-volatile memory?

A: No assumptions are necessary. Follow your instincts in developing the solution.

Q: Can I include C++ libraries such as iostream so that I can output text to the console?
- Not anything algorithm related like a mathematics library

A: Yes, you can use any of the standard libraries.