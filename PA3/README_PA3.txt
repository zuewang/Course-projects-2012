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
