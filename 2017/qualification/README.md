Qualification took place all the day Saturday 8 April 2017.


Success
-------

I am qualified obtaining 35 points in three hours.
I spent one hour and half for each of the first two problems (A and B):

* [a.cpp](./a.cpp)
* [b.cpp](./b.cpp)


Fail
----

After, I spent my journey with family thinking about the third puzzle (problem C). I attempted to implement it just before the end of the contest (during the night from Saturday to Sunday) and I was pretty sure to be right, but my implementation failed :(

* [c.cpp](./c.cpp)

For this third puzzle, I searched a formula, a division, to compute the **interval** of empty stalls around the **K**th person like that :

                               Total number of empty stalls
    Interval in empty stalls = ----------------------------
                                 Next power of two after K

My design is available as a spreadsheet file:

* [C-thinking.ods](./C-thinking.ods)

As my formula did not work when `K=3` I added an ugly `if (k==3)` to fix it. But It was not enough because GCJ has rejected my submissions and I never found the other issues. A South Korea contestant, **iskim**, found this solution in 18 minutes!


Contributions
-------------

I have then improved Wikipedia and Stackoverflow about computing **next power of two** using intrinsics:

* Provided a new answer: http://stackoverflow.com/a/43302742/938111
* Revised another answer: http://stackoverflow.com/a/39944307/938111
* Three comments:
    * http://stackoverflow.com/q/21442088/42591491#comment73654971_42591491
    * http://stackoverflow.com/q/1322510/39944307#comment73670247_39944307
    * http://stackoverflow.com/q/466204/10143264#comment73670346_10143264


Rankings
--------

My rank is 11748: https://code.google.com/codejam/contest/3264486/scoreboard?#sp=11748

* 18% over all 64000 registered contestants
* 46% over the 25289 contestants having attempted submission
* 64% over the 18332 qualified contestants


Usage
-----

The following command lines can be used to build and execute my answers:

```bash
cd 2017/qualification/
( mkdir build ; cd build ; cmake .. && cmake --build . )
./a data/A-small-attempt0.in
./b data/B-small-attempt0.in
./c data/C-small-1-attempt0.in
```

The output files are placed on the current directory. In the above command lines, it is in directory `2017/qualification`.


Environment
-----------

* [C++14](https://en.wikipedia.org/wiki/C%2B%2B14)
* [CMake](https://en.wikipedia.org/wiki/CMake) v3.6
* [GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) v6.3
* [GNU Make](https://en.wikipedia.org/wiki/Make_(software)#Derivatives) v4.1
* [Qt Creator](https://en.wikipedia.org/wiki/Qt_Creator) v4.1.0
