A. Getting the Digits
=====================

Input       | Points
------------|-------
Small       | 11
Large       | 12

Problem
-------

You just made a new friend at an international puzzle conference, and you asked for a way to keep in touch. You found the following note slipped under your hotel room door the next day:

> "Salutations, new friend! I have replaced every digit of my phone number with its spelled-out uppercase English representation ("ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE" for the digits 0 through 9, in that order), and then reordered all of those letters in some way to produce a string S. It's up to you to use S to figure out how many digits are in my phone number and what those digits are, but I will tell you that my phone number consists of those digits in nondecreasing order. Give me a call... if you can!"

You would to like to call your friend to tell him that this is an obnoxious way to give someone a phone number, but you need the phone number to do that! What is it?

Input
-----

The first line of the input gives the number of test cases, T. T test cases follow. Each consists of one line with a string S of uppercase English letters.
Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is a string of digits: the phone number.
Limits

* 1 ≤ T ≤ 100.
* A unique answer is guaranteed to exist.
* Small dataset: 3 ≤ length of S ≤ 20.
* Large dataset: 3 ≤ length of S ≤ 2000.

Sample
------

Input

    4
    OZONETOWER
    WEIGHFOXTOURIST
    OURNEONFOE
    ETHER

  	
Output

    Case #1: 012
    Case #2: 2468
    Case #3: 114
    Case #4: 3


------------

B. Close Match
==============

Input   | Points
--------|---------
Small   | 10	
Large   | 23
	
Problem
-------

You are attending the most important game in sports history. The Oceania Coders are playing the Eurasia Jammers in the Centrifugal Bumble-Puppy world finals. Unfortunately, you were sleep deprived from all the anticipation, so you fell asleep during the game!

The scoreboard is currently displaying both scores, perhaps with one or more leading zeroes (because the scoreboard displays a fixed number of digits). While you were asleep, some of the lights on the scoreboard were damaged by strong ball hits, so one or more of the digits in one or both scores are not being displayed.

You think close games are more exciting, and you would like to imagine that the scores are as close as possible. Can you fill in all of the missing digits in a way that minimizes the absolute difference between the scores? If there is more than one way to attain the minimum absolute difference, choose the way that minimizes the Coders' score. If there is more than one way to attain the minimum absolute difference while also minimizing the Coders' score, choose the way that minimizes the Jammers' score.
Input

The first line of the input gives the number of test cases, T. T cases follow. Each case consists of one line with two non-empty strings C and J of the same length, composed only of decimal digits and question marks, representing the score as you see it for the Coders and the Jammers, respectively. There will be at least one question mark in each test case.
Output

For each test case, output one line containing Case #x: c j, where x is the test case number (starting from 1), c is C with the question marks replaced by digits, and j is J with the question marks replaced by digits, such that the absolute difference between the integers represented by c and j is minimized. If there are multiple solutions with the same absolute difference, use the one in which c is minimized; if there are multiple solutions with the same absolute difference and the same value of c, use the one in which j is minimized.
Limits

* 1 ≤ T ≤ 200.
* C and J have the same length.
* Small dataset: 1 ≤ the length of C and J ≤ 3.
* Large dataset: 1 ≤ the length of C and J ≤ 18.

Sample
------

Input

    4
    1? 2?
    ?2? ??3
    ? ?
    ?5 ?0
	
Output

    Case #1: 19 20
    Case #2: 023 023
    Case #3: 0 0
    Case #4: 05 00

In sample case #4, note that the answer cannot be 15 10; that minimizes the absolute difference, but does not minimize the Coders' score. Nor can the answer be 05 10; that minimizes the absolute difference and the Coders' score, but does not minimize the Jammers' score.



---------------



C. Technobabble
===============

Input  | Points
-------|--------
Small  | 14
Large  | 30

Problem
-------

Every year, your professor posts a blank sign-up sheet for a prestigious scientific research conference on her door. If a student wants to give a lecture at the conference, they choose a two-word topic that is not already on the sheet and write it on the sheet. Once the deadline has passed, the professor has one of her grad students put the topics in a random order, to avoid biasing for or against students who signed up earlier. Then she presents the topics to you for review.

Since the snacks at the conference are excellent, some students try to fake their way into the conference. They choose the first word of some topic already on the sheet and the second word of some topic already on the sheet, and combine them (putting the first word first, and the second word second) to create a new "topic" (as long as it isn't already on the sheet). Since your professor is open-minded, sometimes this strategy actually works!

The fakers are completely unoriginal and can't come up with any new first or second words on their own; they must use existing ones from the sheet. Moreover, they won't try to use an existing first word as their own second word (unless the word also already exists on the sheet as a second word), or vice versa.

You have a list of all N of the submitted topics, in some arbitrary order; you don't know the order in which they were actually written on the sheet. What's the largest number of them that could have been faked?
Input

The first line of the input gives the number of test cases, T. T test cases follow. Each consists of one line with an integer N, followed by N lines, each of which represents a different topic and has two strings of uppercase English letters: the two words of the topic, in order.
Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is an integer: the largest number of topics that could have possibly been faked.
Limits

* 1 ≤ T ≤ 100
* 1 ≤ length of each word ≤ 20
* No topic is repeated within a case
* Small dataset: 1 ≤ N ≤ 16.
* Large dataset: 1 ≤ N ≤ 1000.

Sample
------

Input

    3
    3
    HYDROCARBON COMBUSTION
    QUAIL BEHAVIOR
    QUAIL COMBUSTION
    3
    CODE JAM
    SPACE JAM
    PEARL JAM
    2
    INTERGALACTIC PLANETARY
    PLANETARY INTERGALACTIC
  	
Output

    Case #1: 1
    Case #2: 0
    Case #3: 0

In sample case #1, one possibility is that the topics were added to the sheet in this order:

    QUAIL BEHAVIOR (real)
    HYDROCARBON COMBUSTION (real)
    QUAIL COMBUSTION (fake)

There is no scenario in which more than one of the topics can be fake.

In sample case #2, all of the topics must be real. Whatever order they were written in, at no point would it have been possible to use existing words to create a new topic that was not already on the list.

In sample case #3, neither topic can be fake. For example, if INTERGALACTIC PLANETARY had been the first and only topic written on the sheet, a faker could only have used INTERGALACTIC as the first word of a new topic and could only have used PLANETARY as the second word of a new topic... but the only topic that the faker could have formed would have been INTERGALACTIC PLANETARY, which would have been off limits since it was already on the sheet. So PLANETARY INTERGALACTIC must have also been a real topic.