# Analysis
This project stretched my brain. Here you'll find not just who John and I think wrote Federalist 63, but our methodology and the path we took to get there.

> The TL;DR of this is that **James Madison** (probably) wrote Federalist 63, just by three data points: total words, average word length, and average sentence length.

View the Google Sheet here: https://docs.google.com/spreadsheets/d/14jEY0wjBN-VcWAcNzmfbiVKwPVVSViz5tG9Z6xe8yso/edit?usp=sharing

## 1. In the beginning...
The project requirements were simple. Find out who wrote Federalist 63, since it has been long disputed who actually did. Reading the files into memory was easy: create a buffer, `fscanf` each word into the buffer, then perform operations on that string. I started out easy, only analyzing a single Federalist paper, just so I could have a good grasp on what I needed to repeat for each paper in the `papers/` folder. First: who wrote the thing? I did a quick `strcmp` on each string being parsed to see if it equaled `Author`. If it did, I read the next two strings and set them as the author's first and last names. Easy. Next up was seeing how many words were in the average sentence. For that, I needed something more capable than just an integer array of a fixed size. I knew that I needed it to be flexible. I knew I needed it to grow and shrink to my needs. For that, I was going to have to create my own structure.

## 2. Enter: [IntArray](./util/IntArray.c)
I started with an Integer Array. I decided that if I was going to do this project I needed some practical way of learning how dynamic memory allocation worked. So, I did what every other modern developer does: [I googled it](https://stackoverflow.com/a/3536261/8916706). Stack overflow had a very promising answer, and so I copied it, modified it to fit my needs, and voilà! I had a working dynamic array I could manipulate! Now I could push all of my integer data points and average them out. 

I decided this wasn't enough, and that I wanted to also create a Linked List structure that could hold dynamic-length strings. [And so I made it](https://github.com/bdotsamir/federalist_papers/blob/f379bcde2afa29d40c9a99f1d7e68baed16ab5bc/util/LinkedList.c), this time *without* help from Stack Overflow.\
(I ended up not using the linked list structure in the final draft, so you won't see it on the latest commit of the repo.)

Now, these structures were great! I thought the project was almost done! I was movin' and grovin' faster and faster now that I had the basis for most of the project completed.

And then I emailed Dr. Crotty.

![](https://i.imgur.com/xP0RwmZ.png)

"Well. Shit." I thought to myself.

We didn't cover sorting at all in class, and I wasn't about to implement a sorting algorithm myself. Back to the drawing board.

## 3. Binary Trees
These seemed to be the answer to all of my prayers. Wonderful, mythical, mystical binary trees. Inherently sorted in alphabetical order. Printing in order is easy! Just a couple of recursive functions and you're good to go. As I read through the project description, I actually saw that Dr. Crotty _already had_ a Binary Tree implementation ready to go for this specific use case. Albeit, it was only for integers, so I did have to modify it just a little bit so that it could handle strings, but that was as simple as the modifications to the Linked List structure, so I didn't struggle too much.

Great! So I had a structure I could write strings to in any order, and it would spit back those strings in _alphabetical_ order. A little bit of code here and there and I could parse out some quantitative information on word frequency.

Everything was back on track! I had the first Federalist Paper all parsed out and ready to go. Now, I could just create a loop through all the files in the `papers/` directory, and run each of them through the analyzing function, and the project would essentially be done!

Oh, but it was very much not almost done.

## 4. Lessons in Stack Smashing
There's this thing that GCC and Clang do, where they'll place what's called a "canary" value at the end of a string or stack value. The name "canary" comes from the phrase ["canary in a coal mine,"](https://en.wiktionary.org/wiki/canary_in_a_coal_mine) referring to the small bird that coal miners would bring down with them into the coal mines. If the canary stopped singing, it meant that the concentration of carbon monoxide had gotten too high, and that the miners had to leave **immediately** for their own safety, as carbon monoxide poisoning is potentially **fatal.** Well, in GCC/Clang's case, if there's a bit of rouge code trying to read or write past the end of a value, string, or stack variable, it'll trigger the canary, and signal an abort. This will show up in your console as "smashing the stack," or more universally known as a **buffer overflow.** These overflows can be extremely dangerous to whoever is using the program. If a malicious actor got a hold of a victim's computer, they could use this vulnerability to read past the end of a buffer into *undefined* territory. That undefined territory *could possibly* contain some pretty sensitive data, like passwords or credit cards if the program was created to handle such things.

Everywhere I turned, the stack was being smashed. Valgrind continuously complained that there were invalid reads and invalid writes happening in the `BinaryTree` file, all throughout. Strcmp, strlen, all reading and writing uninitialized values. I stayed up until *2 in the morning* one night trying to debug which values were actually uninitialized. 

To my credit, I did actually find some invalid values. My [`parsenstr`](./util/strutils.c) function sometimes returned an empty string. Why? Not entirely certain, but I added a check at the end of that function that if the reallocated string is of length zero, it gets freed and returns NULL, but that ended up not being the problem.

I wake up the next morning frustrated beyond belief. I had spent the _entirety_ of the day prior trying to squash that damn stack smashing bug to no avail. But, with a fresh brain and a fresh pot of coffee, I was determined. It occurred to me: "Hang on, every paper get analyzed, and *then* the program crashes." I placed a final "Goodbye!" message at the very last line of the program, right before it returned zero to exit, and it printed. Then crashed. 

I was befuddled. How could it possibly be that the ***ENTIRE*** program executes, start to finish, ***THEN*** it crashes? It's at this point that I throw in the towel and ask for help. I head to a popular programming Discord server, The Coding Den and express my frustration. I send a link to this repo. Within minutes, **Retson!ne** replies: 

[![](https://i.imgur.com/99JnKIK.png)](https://github.com/bdotsamir/federalist_papers/blob/f379bcde2afa29d40c9a99f1d7e68baed16ab5bc/main.c#L45)

When analyzing each federalist paper, I had written a while loop that looped through the contents of the `papers/` directory, because I didn't want to sit there and manually type in the path of each individual paper. What I didn't realize was that `strncat` (and its sister `strcat`) doesn't create a new string with the contents of `src` appended to `dest`. It just appends `src` *to* `dest` and returns a pointer to `dest`. But, without enough room for the source string to be pasted onto the destination string, it will overflow the buffer and start writing into undefined memory. **Turns out that undefined memory was actually *stack* memory, which is why, when at the end of the program where the stack is unwinding, it aborted with a stack smashing error.** [Needless to say, my mind was blown](https://i.imgur.com/U96Ni0i.png).

## So, who wrote Federalist 63?
Probably **James Madison**. Across all the papers, the average total word count for him was `3193` words per paper. Fed 63 had `3057` words. Hamilton and Jay had only `1844` and `1785` average total words respectively. See the table below for the full values, and you can match the averages to the unknown data points.

| Author                 | Average Total Words | Average Average Word Length | Average Average Sentence Length |
|------------------------|---------------------|-----------------------------|---------------------------------|
| **Alexander Hamilton** | 1844.833            | 4.769                       | 41.541                          |
| **James Madison**      | 3193.000            | 4.885                       | 34.427                          |
| **John Jay**           | 1785.250            | 4.844                       | 41.471                          |

#### Full data table:

| Paper             | 	Author              | 	Total Words | 	Average Word Length | 	Average Sentence Length |
|-------------------|----------------------|--------------|----------------------|--------------------------|
| **Federalist 63** | **Unknown**          | **3057**     | **4.892**            | **36.381**               |
| Federalist 1      | 	Alexander Hamilton  | 	1603	       | 4.746                | 	32.694                  |                          |
| Federalist 65     | 	Alexander Hamilton  | 	2043	       | 4.749	               | 40.840                   |                          |
| Federalist 59     | Alexander Hamilton	  | 1933	        | 4.750	               | 41.106                   |                          |
| Federalist 67     | 	Alexander Hamilton	 | 1663         | 	4.881               | 	42.590                  |                          |
| Federalist 61	    | Alexander Hamilton	  | 1553         | 	4.688	              | 45.647                   |                          |
| Federalist 60	    | Alexander Hamilton   | 	2274	       | 4.799	               | 46.367                   |                          |
| Federalist 41	    | James Madison	       | 3576	        | 4.811	               | 30.288                   |                          |
| Federalist 43	    | James Madison	       | 3465         | 	4.886               | 	32.046                  |                          |
| Federalist 42	    | James Madison	       | 2807         | 	4.949	              | 37.413                   |                          |
| Federalist 44	    | James Madison	       | 2924         | 	4.894               | 	37.961                  |                          |
| Federalist 3	     | John Jay	            | 1467	        | 4.914	               | 37.590                   |                          |
| Federalist 2	     | John Jay	            | 1687         | 	4.918               | 	40.143                  |                          |
| Federalist 64	    | John Jay	            | 2332         | 	4.730	              | 40.895                   |                          |
| Federalist 4	     | John Jay	            | 1655         | 	4.812	              | 47.257                   |                          |

# Special Thanks
(in no particular order)

| Avatar                                           | Username           | Description                                                                                                                                                                                     |
|--------------------------------------------------|--------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <img height="50" src="./assets/adler.png" />     | **Adler**          | Thank you tremendously for helping me with my Valgrind `InvalidRead` and `InvalidWrite` problems, and for teaching me that everything in C is actually pass by copy. Even pointers, annoyingly. |
| <img height="50" src="./assets/retson!ne.png" /> | **Retson!ne**      | Thank you for pointing me in the right direction regarding my stack smashing bug.                                                                                                               |
| <img height="50" src="./assets/so.png" />        | **Stack Overflow** | To everybody who had similar problems and were gracious enough to share their solutions, I cannot thank you enough.                                                                             |
