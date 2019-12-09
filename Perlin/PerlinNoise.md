```c
//https://youtu.be/Or19ilef4wE

// Function call design
// Mathlab
// XYZ hold coordinates of all the points making up the mesh, these are 2D arrays
// funtion [X,Y,Z] = perlin2d(xn,yn,sps)
// C++
// xn: number of cells in the x direction
// yn: number of cells in the y direction
// sps: samples per lattice spacing
void perlin2d(double **X, double **Y, double **Z, int xn, int yn, int sps);

// Memory allocation
//malloc
int m = yn * sps; // number of rows of sample points
int n = xn * sps; // number of cols of sample points
// pointers to the 2d arrays
double **U = new double *[yn + 1]; // holds the x-component of the grad vector G
double **V = new double *[yn + 1]; // holds the y-component of the grad vector G
X = new double *[m];
Y = new double *[m];
Z = new double *[m];

for (int i = 0; i < m; i++) {
	X[i] = new double[n];
	Y[i] = new double[n];
	Z[i] = new double[n];
}

for (int i = 0; i < yn+1; i++) {
	U[i] = new double[xn + 1];
	V[i] = new double[xn + 1];
}

// Variable initialization
for (int i = 0; i < yn + 1; i++) {
	for (int j = 0; j < yn + 1; j++) {
		U[i][j] = randrange(-1, 1);
		V[i][j] = randrange(-1, 1);
	}
}

double hx = xn / (n - 1), hy = yn / (m - 1);
for (int i = 0; i < m; i++) {
	for (int j = 0; j < n; j++) {
		X[i][j] = hx * j;
		Y[i][j] = hy * i;
	}
}
```
