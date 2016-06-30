#Testing NGL

The test directory contains different test for NGL, it is split into directries for  each of the elements under test and these will mainly be the mathematical types.

These tests are designed to be run when NGL is updated to flag up any code changes from the previous version that break the backward compatability.

There are two types of source file. 

* Generators
* Testers

#Generators

The generators are used to generate the test case outputs for comparison, for example the Mat4 generator will add two Mat4s together and generate the result which is printed to the screen.

This value should then be used in the Tester for the comparison.

#Testers

The testers run google test against the code used in the generator and see if the result is the same as the previous version.
