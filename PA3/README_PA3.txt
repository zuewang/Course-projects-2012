/**********************************************************************
 *  readme.txt template                                                   
 **********************************************************************/

Name:       			WANG Ziyu
Nickname or English name: 	James
Major: 				ECE/CSE
Course:				COMP2012H
Email address:			zwangbm@connect.ust.hk
Programming assignment #:	3
OS:        			Linux
Compiler:  			g++ Matrix.h Matrix.cpp tester.cpp -o PA3
Hours spent:      		35


/**********************************************************************
 *  List whatever help (if any) that you received.
 **********************************************************************/
I have sought help from the following people:
I have read the following books:
I have consulted the following websites:

The work included in this program is all my own work (Y/N):	Y


/**********************************************************************
 *  Explain your overall approach and the unique features of your program
 **********************************************************************/
Do operations and some calculations on matrices.

/**********************************************************************
 *  Describe any serious problems your program has, or anything which
 *  you have not implemented successfully
 **********************************************************************/


/**********************************************************************
 *  State the input files you used to test your program
 **********************************************************************/
tester.cpp


/**********************************************************************
 *  Known bugs / limitations of the program
 **********************************************************************/
While running on Linux, sometimes a negative result with small absolute 
value will be showed as -0.(e.g.: If the result is -0.017353 on Windows,
the result on Linux will be -0).

/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, whether    
 *  you like the assignment or not, and how the assignment may be
 *  improved 
 **********************************************************************/

Additional functions added to the program:
1.  Calculate the determinant of a matrix:	A.calDet(n);(n is the 
    row/column of A, the n*n matrix)
    If the matrix A is not a square one, the program will be exited.
2.  Addition of matrices:	 A.add(B,2,3); ---> 2*A+3*B
3.  Calculate A^(n):	Matrix B = A.power(A,-2);(B = A^(-2))
4.  Calculate the solution of Ax = b: Matrix x = A.sol(b);(x is the 
    solution)(A should be a square matrix)
5.  Calculate the trace of a matrix:	A.calTrace();
6.  Transform a matrix to row-echelon form:	A.ref(0);(this will make
    change to the matrix)
7.  Calculate the rank of the matrix:	A.rank();

Other notes:
1.  While doing operation "access the element", if the element of the matrix 
    does not exist, the program will be exited in case of data misused.
2.  A tester.cpp is included to test the program.	