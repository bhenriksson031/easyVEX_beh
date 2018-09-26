#ifndef __easyVex_h__
#define __easyVex_h__

/*
* This Software was originally developed by Dimtiri Shimanovskiy.
* Feel free to use as you wish (http://unlicense.org/). Feedback is appreciated
* Credit and dontations are appreciated. If you credit me in a project, send me a message to dimitri.shima.dev@gmail.com, so I can find out about it.
*
* License:
* This is free and unencumbered software released into the public domain.
*
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
*
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* For more information, please refer to <http://unlicense.org/>
*
*
*
* NAME:	easyVex.h (VEX)
*
* COMMENTS:	This include file contains functions to improve quality of life and geometry editing.
*
* Instrcutions: Include files go into $HFS/houdini/vex/include/ path
* 1. Include files go into
* $HFS/houdini/vex/include/
* file path.
* 2. Type
* #include "easyVex.h"
* in the wrangle to be able to use the functions.
*/

//General utility functions

//This function takes an array of integers and reduces a version that is sorted in ascending order and has no duplicate values. 
function int[] uniquearray(const int numbers[]) {
	int localNumbers[] = {};
	int clean[] = {};
	int temp = 0;

	//fail safe
	if (len(numbers) == 0) {
		warning("Passed empty array into uniquearray function");
		return clean;
	}

	localNumbers = sort(numbers); // sort ascending to simplify the elimination of duplicates

	append(clean, localNumbers[0]); // the first element is always unique 

	for (int i = 1; i<len(numbers); i++) {
		if (clean[temp]<localNumbers[i]) { //if the number is bigger than the previously added, add it
			append(clean, localNumbers[i]);
			temp++; //temp is the last index in the clean array
		}
	}
	return clean;
}

//This function should only add new unique values to an array
function int[] appendunique(int numbers[]; const int num) {
	if (find(numbers, num)<0) {
		append(numbers, num);
	}
	return numbers;
}

//removes all instances of value from array
function void removevalues(int numbers[]; const int remove) {
	while (1) {
		int temp;
		temp = removevalue(numbers, i);
		if (temp == 0) {
			break;
		}
	}
}

//removes all instances of all values in seccond array from first array
function void removevalues(int numbers[]; const int remove[]) {
	foreach(int i; remove){
		while(1) {
			int temp;
			temp = removevalue(numbers, i);
			if (temp == 0) {
				break;
			}
		}
	}
}

//returns int array of unique values of an arbitrary attribute
function int[] uniquevals(string componentType; string attribName){	
	int clean[] = {};
	int count = nuniqueval(0, componentType, attribName);
	for (int i = 0; i < count; i++) {
		int val = uniqueval(0, componentType, attribName, i);
		append(clean,val);
	}
	return clean;
}

//edges 
struct edgeStruct{
	int a,b;

	//print verbose edge description to log 
	void printfVerbose(){
		printf("edge between points %i and %i \n", a,b);
	}

	//returns a string in standard Houdini edge format 
	string getFullName(){
		return sprintf("p%i_%i", this.a, this.b);
	}

	//swaps a and b - reverseing the direction
	void swap(){
	//this method fails for large numbers
		this.a = this.a + this.b;
		this.b = this.a - this.b;
		this.a = this.a - this.b;

	/*  
	//My guess is for most cases the above method is sufficient
	//but a stable (and less efficient) alterantive is the following code.
	//completelye replace the code above with this. 
		int c;
		c = this.a;
		this.a = this.b;
		this.b = c;
	*/
	}

	//returns 0 if a>b and 1 if b>a
	int compare(){
		return this.a>this.b;
	}

	//sorts a and be in increasing order
	void sort(){
		if(compare(this)){
			swap(this);
		}
}

}

#endif
